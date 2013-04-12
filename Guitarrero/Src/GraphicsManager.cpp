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
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(Game* myGame, bool use3D, bool sustainMode)
: myTimeCounter(0), mySceneManager(0), lastTime(0), rState(RS_NOT_DRAWED)
{
	// Init members
	this->myGame 		= myGame ;
	this->frontSmgr 	= this->myGame->myGraphicEngine->getSceneManager() ;
	this->use3D			= use3D ;
	this->sustainMode 	= sustainMode ;
	this->created 		= false ;
}

void GraphicsManager::create()
{
	if (!this->created)
	{
		Sequence* mySeq			= this->myGame->myGameMode->getSequence() ;										// Get the sequence back		
		this->mySceneManager	= new SceneManager(this->frontSmgr, this->myGame->myRessources, this->use3D) ;	// The scene behind the neck
		this->lastTime 			= 0 ;																			// Set back to 0 for the loop
		this->myGame->mySongManager->setDirectory(mySeq->getDirectory()) ;

		// Look how many players we have
		switch(this->myGame->myGameMode->getNbPlayer())
		{
			case 1 :
			{
				std::deque<NotesLine*>* lines = mySeq->getLines(this->myGame->myGameMode->getLevel()) ;
				Statistics*	stats = new Statistics() ;
				this->prepareLines(lines) ;
				
				irr::core::position2d<irr::s32> p1Pos = this->myGame->myRessources->getPosition(PLAYER_1_1P_COUNTERPOS) ;

				this->gridManagers.push_back(new GridManager(this->frontSmgr, this->myGame->myRessources, stats, lines, this->myGame->myReceiver->getKeyMap(0), 0, 200, 0, 4000, p1Pos.X, p1Pos.Y, this->sustainMode)) ;
				this->myGame->myReceiver->reInit(0) ;
				break ;
			}
			case 2 :
			{
				std::deque<NotesLine*>* linesP1 = mySeq->getLines(this->myGame->myGameMode->getLevel()) ;
				Statistics*	statsP1 = new Statistics() ;
				this->prepareLines(linesP1) ;
								
				std::deque<NotesLine*>* linesP2 = mySeq->getLines(this->myGame->myGameMode->getLevel()) ;
				Statistics*	statsP2 = new Statistics() ;
				this->prepareLines(linesP2, 1) ;
			
				irr::core::position2d<irr::s32> p1Pos = this->myGame->myRessources->getPosition(PLAYER_1_2P_COUNTERPOS) ;
				irr::core::position2d<irr::s32> p2Pos = this->myGame->myRessources->getPosition(PLAYER_2_2P_COUNTERPOS) ;

			
				this->gridManagers.push_back(new GridManager(this->frontSmgr, this->myGame->myRessources, statsP1, linesP1, this->myGame->myReceiver->getKeyMap(0), 400, 130, 0, 2000, p1Pos.X, p1Pos.Y, this->sustainMode, true)) ;
				this->myGame->myReceiver->reInit(0) ;
				this->gridManagers.push_back(new GridManager(this->frontSmgr, this->myGame->myRessources, statsP2, linesP2, this->myGame->myReceiver->getKeyMap(1), -400, 130, 0, 2000, p2Pos.X, p2Pos.Y, this->sustainMode, true)) ;
				this->myGame->myReceiver->reInit(1) ;
				break ;
			}
		}

		// Add created users statistics to gameMode
		this->myGame->myGameMode->clearStats() ;
		for (int i = 0 ; i < this->gridManagers.size() ; i++)
		{
			this->myGame->myGameMode->addStats(this->gridManagers[i]->getScoreCounter()->getStats()) ;
		}

        // Avoid some unknow bug that make the font texture white
		this->myTimeCounter	  = new TimeCounter(this->frontSmgr, this->myGame->myRessources) ; // The upper time counter 
		this->created         = true ;
	}
}

void GraphicsManager::prepareLines(std::deque<NotesLine*>* lines, int player)
{
	switch(this->myGame->myGameMode->getMode())
	{
		case GM_NORMAL :
		{
			this->myGame->myGameMode->setlineToDraw(100) ;
			break ;
		}
		case GM_REFLEX :
		{
			this->myGame->myGameMode->setlineToDraw(10) ;
			break ;
		}
		case GM_DUEL :
		{
			this->myGame->myGameMode->setlineToDraw(100) ;
			break ;
		}
		case GM_DUEL_P :
		{
			this->myGame->myGameMode->setlineToDraw(100) ;
			break ;	
		}
		case GM_DUEL_REFLEX :
		{
			this->myGame->myGameMode->setlineToDraw(10) ;
			break ;
		}
		case GM_DUEL_P_REFLEX :
		{
			this->myGame->myGameMode->setlineToDraw(6) ;
			break ;
		}
	}
}

void GraphicsManager::destroy()
{
	// Delete objects
	for (int i = 0 ; i < this->gridManagers.size() ; i++)
	{
		delete this->gridManagers[i] ;
		this->gridManagers[i] = 0 ;
	}
	delete this->myTimeCounter ;
	this->myTimeCounter = 0 ;
	delete this->mySceneManager ;
	this->mySceneManager = 0 ;

	// Clear deques
	this->gridManagers.clear() ;

	this->created 	= false ;			// Set to false the creation
	this->rState 	= RS_NOT_DRAWED ;	// Reinit render state
}

void GraphicsManager::render()
{
	if (this->created)
	{
		this->mySceneManager->render() ;

		for (int i = 0 ; i < this->gridManagers.size() ; i++)
		{
			this->gridManagers[i]->render() ;
		}
		
		this->myTimeCounter->render() ;
	}
}

bool GraphicsManager::update(int time)
{
	/////////////
	// UPDATES
	/////////////
	for (int i = 0 ; i < this->gridManagers.size() ; i++)
	{
		this->gridManagers[i]->getScoreCounter()->update() ;
	}

	this->myTimeCounter->setTime(this->myGame->mySongManager->getTimeLeft()) ;
	this->mySceneManager->update(time) ;

	/////////////
	// PLAY
	/////////////
	switch(this->rState)
	{
		case RS_NOT_DRAWED :
		{
			for (int i = 0 ; i < this->gridManagers.size() ; i++)
			{
				for (int loop = 0 ; this->gridManagers[i]->hasMoreLineToDraw() && loop < this->myGame->myGameMode->getLineToDraw() ; loop++)
				{
					this->gridManagers[i]->drawNewLine(time) ;
					this->gridManagers[i]->nextLineToDraw() ;
				}
			}

			this->rState = RS_NOT_STARTED ;			
			break ;
		}
		case RS_NOT_STARTED :
		{
			if (time >= PAUSE_BEFORE)
			{
				this->rState = RS_READY ;
				this->myGame->mySongManager->play() ;
				this->myGame->mySongManager->playSound(irr::core::stringc(this->myGame->myRessources->getFile(ENTRY_3D_SOUND))) ;
			}
			
			break ;
		}
		case RS_READY :
		{
			for (int i = 0 ; i < this->gridManagers.size() ; i++)
			{
				if (this->gridManagers[i]->hasMoreLineToPlay())
				{
					if (this->gridManagers[i]->checkLine(this->myGame->myReceiver, this->myGame->mySongManager, this->mySceneManager, time, this->lastTime, i))
					{
						this->myGame->myReceiver->reInit(i) ; 		// Get ready to input again (when we go next line reinit receiver)
						this->gridManagers[i]->nextLineToPlay() ;	// Next line to play now

						if(this->gridManagers[i]->hasMoreLineToDraw()) // While there is still lines to draw
						{
							this->gridManagers[i]->nextLineToDraw() ;
							this->gridManagers[i]->drawNewLine(time) ;
						}
					}
				}
			}

			if (this->myGame->mySongManager->hasFinished()) // Wait for the end
			{
				this->destroy() ; // Destroy 3D Scene
				return true ;
			}

			break ;
		}
	}
	
	// Update lastTime
	this->lastTime = time ;
	
	// Return that we have not reached the end of the song
	return false ;
}

void GraphicsManager::moveKey(int key, bool pushed)
{
	if (this->created)
	{
		for (int i = 0 ; i < this->gridManagers.size() ; i++)
		{	
			this->gridManagers[i]->moveKey(key, pushed) ;
		}
	}
}
