///////////////////////////////////////////////////////////////////////////////
// This file is part of Guitarrero. Copyright (C) 2009-2012 FONTA Romain
//
// Guitarrero is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Guitarrero is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Guitarrero.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////

#include "Game.h"

Game::Game(GameParams &params)
{
	// 3D engine
	this->myGraphicEngine = irr::createDeviceEx(params.irrParams) ;						// Create the engine
	this->myGraphicEngine->setWindowCaption(TEXT_CAPTION) ;								// Update windows caption
	this->drawSplashScreen() ; 															// Draw splash screen
	
	// Game objects
	this->myRessources		= new Ressources(params.skinDir, params.languageFile) ; 				// Ressources
	this->myGameMode 		= new GameMode() ;														// Default game mode
	this->myReceiver 		= new InputReceiver(params.player1KeysMap, params.player2KeysMap, this) ; // Event receiver
	this->myTimer			= this->myGraphicEngine->getTimer() ;									// Get the game timer
	this->mySoundEngine		= irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT) ;     		// Sound engine in separated thread
	this->myJukebox 		= new Jukebox(this->myGraphicEngine, params.delay, params.songsDir) ; 	// Instanciate jukebox
	this->mySongManager		= new SongManager(this->mySoundEngine) ;								// Song manager (hold methods to start pause... song)
	this->myGraphicsManager = new GraphicsManager(this, params.use3DScenery, params.sustainMode) ;	// Graphics Manager	
	this->myGuiManager		= new GuiManager(this) ; 												// Gui Manager
	this->myDriver 			= this->myGraphicEngine->getVideoDriver() ;								// Video driver (begin endscene)
	this->state 			= GS_UNDEFINED ;														// Default game state
	this->newState 			= GS_UNDEFINED ;														// For being thread safe
	this->changeState		= false ;																// Just init
	this->guiAction 		= ACTION_NONE ;															// By default no gui action
	this->guiActionValue 	= 0 ;																	// No value too
	this->doGuiAction 		= false ;																// So no need to propagate
	this->graphicAction 	= 0 ;																	// By default no 3D action
	this->graphicActionValue = 0 ;																	// No value too
	this->doGraphicAction 	= false ;																// So no need to propagate
	
	// Preload textures and register game for receiver
	this->myRessources->preloadAllTextures(this->myGraphicEngine->getVideoDriver()) ;	// Preload all needed files
	this->myGraphicEngine->setEventReceiver(this->myReceiver) ; 						// Register receiver for game
	this->myGraphicEngine->getCursorControl()->setVisible(false) ;						// Set cursor invisible

	// Set to go to game menu and launch
	this->setState(GS_MAIN) ;
	this->gameLoop() ;
}

Game::~Game()
{
	delete this->myGraphicsManager ;
	delete this->myGuiManager ;
	delete this->mySongManager ;
	delete this->myRessources ;
	delete this->myGameMode ;
	delete this->myJukebox ;
	delete this->myGraphicEngine ;
	delete this->myReceiver ;
}

void Game::gameLoop()
{
	int delta 	= 0 ; // If delta time runned, draw a frame
	//int fps 	= 0 ;

	while (this->myGraphicEngine->run()) 
	{
		if (this->myGraphicEngine->isWindowActive())
		{		
			//////////////////////////////////////////////////////////////////
			// GAME UPDATES													//
			//////////////////////////////////////////////////////////////////			
			if (this->state == GS_GAME) // If we are ingame
			{
				if (this->myGraphicsManager->update(this->myTimer->getTime())) // If the game is over
				{
					this->setState(GS_SONG_STATISTIC) ; // Go song statistics
					this->updateState() ;
				}
			}
			else
			{
				// Don't use ressources when not needed
				this->myGraphicEngine->yield() ;	
			}
			
			//////////////////////////////////////////////////////////////////
			// DRAWINGS														//
			//////////////////////////////////////////////////////////////////
			if (++delta == DELTA) // Game loop runned DELTA times, so draw a frame
			{
				// DISPATCH GUI ACTIONS
				if (this->doGuiAction)
				{
					this->propagateGuiAction() ;
				}

				// DISPATCH GRAPHIC ACTIONS
				if (this->doGraphicAction)
				{
					this->propagateGraphicAction() ;
				}

				// DISPATCH NEW GAME STATE
				if (this->changeState)
				{
					this->updateState() ;
				}

				// NOW DRAW
				this->myDriver->beginScene(true, true, irr::video::SColor(255, 0, 255, 0)) ; // Begin the frame
				
				if(this->state == GS_GAME || this->state == GS_PAUSE)
				{
					this->myGraphicsManager->render() ;	// Draw 3D
				}
				
				this->myGuiManager->render() ; 	// Draw GUI
				this->myDriver->endScene() ; 	// End the frame
				delta = 0 ; 					// Reinit delta counter

				/*int nFps = this->myDriver->getFPS() ;
				if (nFps != fps)
				{
					this->myGraphicEngine->setWindowCaption((irr::core::stringw(nFps) + " " + irr::core::stringw(this->myDriver->getTextureCount())).c_str()) ;
					fps = nFps ;
				}*/
			}
		}
		else // Do special things
		{
			switch(this->state)
			{
				case GS_GAME :
					this->setState(GS_PAUSE) ;	// Go Pause
					this->updateState() ;
					break ;
			}
			
			// Don't use ressources when not needed
			this->myGraphicEngine->yield() ;
		}
	}
}

// Propagate an action to graphics manager
void Game::setGraphicAction(int action, int value)
{
	if(!this->doGraphicAction) 
	{
		this->graphicAction 		= action ;
		this->graphicActionValue	= value ;
		this->doGraphicAction 		= true ;	// Tell other thread that he could propagate
	}
}

// Propagate an action to gui manager
void Game::setGuiAction(ACTION_TYPE action, int value)
{
	if (!this->doGuiAction)
	{
		this->guiAction 		= action ;
		this->guiActionValue 	= value ;
		this->doGuiAction 		= true ;	// Tell other thread that he could propagate
		
		// Play action sound
		this->mySoundEngine->play2D(irr::core::stringc(this->myRessources->getFile(MENU_SELECT_SOUND)).c_str()) ;
	}
}

void Game::propagateGuiAction()
{
	this->myGuiManager->performAction(this->guiAction, this->guiActionValue) ;	
	this->doGuiAction = false ;
}

void Game::propagateGraphicAction()
{
	this->myGraphicsManager->moveKey(this->graphicAction, this->graphicActionValue) ;
	this->doGraphicAction = false ;
}

// Method to change the state of the game
void Game::setState(GAME_STATE nState)
{
	if (this->newState == nState)
	{
		return ;
	}
	
	this->newState 		= nState ;	// What state to set now
	this->changeState 	= true ;	// Tell other thread that he could update
}

// When other thread has setted a new state, the primary thread change it
void Game::updateState()
{
	this->myGuiManager->setState(this->newState) ; // Update gui
	
	switch(this->newState)
	{
		case GS_PAUSE :
		{
			if (this->state == GS_GAME) 					// We can go pause only if ingame
			{
				this->mySongManager->pause() ;
				this->myTimer->stop() ;
			}
			break ;
		}
		case GS_MAIN :
		{
			this->mySoundEngine->removeAllSoundSources() ;
			this->mySongManager->releaseRessources() ;
			
			if (this->state == GS_PAUSE) 					// If we come to the menu after an ingame pause
			{
				this->myGraphicsManager->destroy() ;
				this->myTimer->start() ;
			}

			break ;
		}
		case GS_RESTART_GAME :
		case GS_RESUME_GAME :
		case GS_GAME :
		{
			switch (this->newState)
			{
				case GS_RESTART_GAME :
				{
					this->myGraphicsManager->destroy() ;
					this->myTimer->setTime(0) ; 			// Set time to 0 for inputs checks
					this->myGraphicsManager->create() ;
					break ;
				}	
				case GS_RESUME_GAME :
				{
					this->mySongManager->resume() ;
					break ;
				}
				case GS_GAME :
				{
					this->myTimer->stop() ;
					this->myTimer->setTime(0) ;
					this->setSpeed(this->myGameMode->getSpeed()) ;
					this->myGraphicsManager->create() ;
					break ;
				}
			}

			this->myTimer->start() ;
			this->newState = GS_GAME ;
			break ;
		}
		case GS_MODE_SELECTION :
		{
			this->mySoundEngine->removeAllSoundSources() ;	// Stop all sounds (preview from song selection)
			
			if (!this->myGameMode->getSequence()->hasLevels()) // No levels to play !
			{
				this->newState = GS_NO_LEVELS_AFTER_MODE_S ;
				this->myGuiManager->setState(newState) ; // Update gui
			}
			
			break ;
		}
		case GS_EXIT :
		{
			this->myGraphicEngine->closeDevice() ;
			break ;
		}
	}

	this->state 		= this->newState ;	// Update game state
	this->changeState 	= false ;

	this->mySoundEngine->play2D(irr::core::stringc(this->myRessources->getFile(MENU_BUTTONS_SOUND)).c_str()) ;
}

// Set game speed
void Game::setSpeed(float speed)
{
	this->myTimer->setSpeed(speed) ;
	this->mySongManager->setPlaybackSpeed(speed) ;
}

// Draw a splash screen
void Game::drawSplashScreen()
{
	#include "splashScreen.h" // Retrieve file array
	
	// Load image from memory
	irr::io::IReadFile* memoryFile 	= this->myGraphicEngine->getFileSystem()->createMemoryReadFile(splashScreen, splashSize, "SplashScreen.png") ;
	irr::video::IImage* image 		= this->myGraphicEngine->getVideoDriver()->createImageFromFile(memoryFile) ; 
	irr::video::ITexture* texture 	= this->myGraphicEngine->getVideoDriver()->addTexture("SplashScreen.png", image) ;

	// Draw splashScreen frame
	this->myGraphicEngine->getVideoDriver()->beginScene() ;	
	this->myGraphicEngine->getGUIEnvironment()->addImage(texture, irr::core::position2d<int>((this->myGraphicEngine->getVideoDriver()->getScreenSize().Width/2)-256, 10))->draw() ;
	this->myGraphicEngine->getVideoDriver()->endScene() ;
	
	// Remove everything that's not needed anymore
	memoryFile->drop() ;
	image->drop() ;
	this->myGraphicEngine->getGUIEnvironment()->clear() ;
	this->myGraphicEngine->getVideoDriver()->removeTexture(texture) ;
}
