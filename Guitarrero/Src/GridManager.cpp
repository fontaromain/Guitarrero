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

#include "GridManager.h"

GridManager::GridManager(irr::scene::ISceneManager* smgr, Ressources* myRessources, Statistics* stats, std::deque<NotesLine*>* lines, int* keyMap, int pos, int scale, int rot, int camFarVal, int xStats, int yStats, bool sustainMode, bool player)
: yOffset(pos), distEcart(scale), rotation(rot), camFarVal(camFarVal), animOffset(sin((irr::core::PI * rot) / 180.0)), player(player), sustainMode(sustainMode)
{
	// Init members
	this->smgrFront 		= smgr->createNewSceneManager() ; 	// Get scenes managers to draw in
	this->smgrMed 			= smgr->createNewSceneManager() ; 	// Get scenes managers to draw in
	this->smgrBack 			= smgr->createNewSceneManager() ; 	// Get scenes managers to draw in
	this->guiSmgr			= smgr->createNewSceneManager() ;	// The scene manager for gui elements
	this->guiTextSmgr		= smgr->createNewSceneManager() ;	// The scene manager for text gui elements only
	this->myRessources		= myRessources ;					// Ressources to get textures and texts
	this->keyMap 			= keyMap ;							// The keymap of the user
	this->spriteAnim 		= 0 ; 								// Sprite texture index
	this->notesLines 		= lines ;							// The lines to play
	this->posInFile			= this->notesLines->begin() ;		// Iterator to the next line to be played
	this->posDraw 			= this->notesLines->begin() ;		// Iterator to the next line to be drawed
	this->driver 			= smgr->getVideoDriver() ;			// Video driver
	this->myScoreCounter 	= new ScoreCounter(this, stats, xStats, yStats) ;	// The score counter

	for (int i = 0 ; i < NB_NOTES ; i++) // For each sprites
	{
		this->nodesSprites[i] = 0 ;
	}

	this->drawGrid() ;	// Create the grid
}

GridManager::~GridManager()
{
    for (int i = 0 ; i < NB_NOTES ; i++)
    {
        if (this->nodesSprites[i])
        {
            this->nodesSprites[i]->drop() ;
        }
    }

	delete 	this->notesLines ;
	delete 	this->myScoreCounter ;
	
	this->smgrFront->drop() ;
	this->smgrMed->drop() ;
	this->smgrBack->drop() ; 
	this->guiSmgr->drop() ;
	this->guiTextSmgr->drop() ;
}


//////////////
// DRAWINGS //
//////////////
void GridManager::render()
{
	this->smgrBack->drawAll() ;
	this->driver->clearZBuffer() ;
	this->smgrMed->drawAll() ;
	this->driver->clearZBuffer() ;
	this->smgrFront->drawAll() ;
	this->driver->clearZBuffer() ;
	this->guiSmgr->drawAll() ;
	this->driver->clearZBuffer() ;
	this->guiTextSmgr->drawAll() ;
	this->driver->clearZBuffer() ;
}

void GridManager::drawSLine(int i)
{
	int pos = (this->distEcart * 2 - (this->distEcart * i)) + this->distEcart / 2 + this->yOffset ;
	if (i == 0)
	{
		pos += 8 ;
	}
	else if(i == 5)
	{
		pos -= 8 ;
	}
	
	irr::scene::IMeshSceneNode* line = this->smgrMed->addCubeSceneNode(1, 0, -1,
									irr::core::vector3df(0, 0, pos),
									irr::core::vector3df(0, this->rotation, 0),
									irr::core::vector3df(this->camFarVal * 2, 0, (i == 0 || i == 5) ? 30 : 10)) ;
	line->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(LINES))) ;
	this->setProperties(line) ;
}

void GridManager::drawULine(int i)
{
	float a 	= (this->animOffset * (i * (this->distEcart * UNDERLINES_LENGTH))) ;
	float b 	= (this->animOffset * (this->distEcart * UNDERLINES_LENGTH)) - a ;
	float len 	= sqrt((this->distEcart * UNDERLINES_LENGTH)*(this->distEcart * UNDERLINES_LENGTH) + irr::core::abs_(a + b) * irr::core::abs_(a + b)) ;

	irr::scene::IMeshSceneNode* node = this->smgrBack->addCubeSceneNode(1, 0, -1,
									irr::core::vector3df(0, 0, 0),
									irr::core::vector3df(0, this->rotation, 0),
									irr::core::vector3df(len, 0, this->distEcart * 5)) ;
	node->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(NECK))) ;		
	node->addAnimator(this->smgrBack->createFlyStraightAnimator(
		irr::core::vector3df(i * (this->distEcart * UNDERLINES_LENGTH), 0, this->yOffset - a),
		irr::core::vector3df(i * (this->distEcart * UNDERLINES_LENGTH) - (this->distEcart * UNDERLINES_LENGTH), 0, this->yOffset + b),
		this->distEcart * UNDERLINES_LENGTH + (this->player ? 52 : 80),
		true)) ;

	this->setProperties(node) ;
}

void GridManager::drawKey(int i)
{
	if (i != 5)
	{
		irr::scene::ISceneNode* key = this->smgrFront->addBillboardSceneNode(
											0,
											irr::core::dimension2d<irr::f32>((96 * this->distEcart) / 100, (128 * this->distEcart) / 100), 
											irr::core::vector3df(0, 0, this->distEcart*2-(this->distEcart*i) + this->yOffset),
											this->keyMap[i]) ; 
		key->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(KEY_DESEL))) ;
		this->setProperties(key) ;
	}
}

void GridManager::drawGrid()
{
	// Create game grid in one loop
	for (int i = 0 ; i < 6 ; i++)
	{
		this->drawSLine(i) ;	// Draw separator lines
		this->drawULine(i) ;	// Draw moving underlines
		this->drawKey(i) ;		// Draw playing keys

		if (i == 5)
		{
			// Line to play notes
			irr::scene::IMeshSceneNode* tempoLine = this->smgrBack->addCubeSceneNode(1, 0, -1,
											irr::core::vector3df(0, 0, this->yOffset), 
											irr::core::vector3df(0, 0, 0), 
											irr::core::vector3df(2, 2, this->distEcart*5)) ;
			tempoLine->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			tempoLine->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(LINES))) ;
		}
	}

	// Add a camera to see it
	this->cam = this->smgrFront->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1000, 0, 0)) ;
	this->cam->setFarValue(this->camFarVal) ;
	this->cam->addAnimator(this->smgrFront->createFlyStraightAnimator(irr::core::vector3df(-500, time(NULL)%2 == 0 ? 1500 : 500, 0),
																	irr::core::vector3df(-500, 1000, 0),
																	PAUSE_BEFORE - 500,
																	false));

	this->cam = this->smgrMed->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1000, 0, 0)) ;
	this->cam->setFarValue(this->camFarVal) ;
	this->cam->addAnimator(this->smgrMed->createFlyStraightAnimator(irr::core::vector3df(-500, time(NULL)%2 == 0 ? 1500 : 500, 0),
																	irr::core::vector3df(-500, 1000, 0),
																	PAUSE_BEFORE - 500,
																	false));

	this->cam = this->smgrBack->addCameraSceneNode(0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1000, 0, 0)) ;
	this->cam->setFarValue(this->camFarVal) ;
	this->cam->addAnimator(this->smgrBack->createFlyStraightAnimator(irr::core::vector3df(-500, time(NULL)%2 == 0 ? 1500 : 500, 0),
																	irr::core::vector3df(-500, 1000, 0),
																	PAUSE_BEFORE - 500,
																	false));
}

void GridManager::setProperties(irr::scene::ISceneNode* node)
{
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL) ;
	node->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, true) ;
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false) ;	
}

void GridManager::drawNewLine(int timeElapsed)
{
	// Get the current line to draw
	NotesLine* line = this->getLineToDraw() ;

	if (line == 0)
	{
		return ;
	}

	// Init
	int noteStart 								= line->getStartTime() - timeElapsed ; 
	int noteLength 								= line->getLength() ;
	int noteEndTime 							= line->getEndTime() - timeElapsed ;
	irr::scene::ISceneNodeAnimator* deleteAnim 	= this->smgrFront->createDeleteAnimator(noteEndTime + 200) ;

	for (int i = 0 ; i < 5 ; i++) // For a line
	{
		if (line->getNote(i) != 0) // If we need to add a note
		{
			// Create the note start
			irr::scene::ISceneNode* nodeStart = this->smgrFront->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>((96 * this->distEcart) / 100, (128 * this->distEcart) / 100)) ; 

			// Parameters
			nodeStart->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(irr::core::stringc(line->isTapping() ? i + 5 : i ).c_str()))) ; // Apply texture			
			nodeStart->addAnimator(deleteAnim) ; // The note will be deleted after playing it
			this->setProperties(nodeStart) ;
			nodeStart->addAnimator(this->smgrFront->createFlyStraightAnimator( 
						irr::core::vector3df(noteStart, 0, (this->distEcart * 2) - (this->distEcart * i) + this->yOffset - (this->animOffset * noteStart)),
						irr::core::vector3df(-200, 0, (this->distEcart * 2) - (this->distEcart * i) + this->yOffset + (this->animOffset * 200)),
						noteStart + 200,
						false));

			// Add note end
			irr::scene::ISceneNode* nodeEnd = 0 ;
			if (noteLength != 1)
			{
				float a 	= this->animOffset * (noteStart + (noteLength / 2.0)) ;
				float b 	= this->animOffset * ((noteLength / 2.0 ) + 200) ;

				double aa = (irr::core::abs_(a + b) * irr::core::abs_(a + b)) ;
				double bb = (noteLength * noteLength) ;
				double len 	= sqrt(aa + bb) ;
				
//				std::cout << "nl = " << noteLength << " bb = " << bb << " len = " << len << "\n" ;

				nodeEnd = this->smgrMed->addCubeSceneNode(1, 0, -1, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, this->rotation, 0), irr::core::vector3df(noteLength, 0, NOTE_END_WIDTH)) ;
				nodeEnd->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(irr::core::stringc(i+10).c_str()))) ; // Apply texture
				deleteAnim->createClone(nodeEnd) ; // The note will be deleted after playing it	
				this->setProperties(nodeEnd) ;			
				nodeEnd->addAnimator(this->smgrMed->createFlyStraightAnimator( 
							irr::core::vector3df(noteStart + (noteLength / 2), 0, (this->distEcart * 2) - (this->distEcart * i) + this->yOffset - a),
							irr::core::vector3df(0 - (noteLength / 2) - 200, 0, (this->distEcart * 2) - (this->distEcart * i) + this->yOffset + b),
							noteEndTime + 200,
							false));
			}

			// Finally store the node for effects when playing
			line->setNode(i, nodeStart, nodeEnd) ;
		}
	}
}

void GridManager::setCurrentLineEffect(bool successPlaying, int timeDiff)
{
	NotesLine* 	notesLine 			= this->getLineToPlay() ;
	bool		shouldRemoveSprite	= false ;

	if (!notesLine) // No line
	{
		return ;
	}
	
	// For each notes in the line
	for (int i = 0 ; i < NB_NOTES ; i++)
	{
		/////////////////////////////////
		// Node start
		/////////////////////////////////
		irr::scene::ISceneNode* nodeStart = notesLine->getNodeStart(i) ;

		if (nodeStart)
		{
			if (successPlaying)
			{
				nodeStart->setVisible(false);
			}
			else
			{
				nodeStart->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(MISSED_NOTE).c_str())) ;		
			}
		}
		
		/////////////////////////////////
		// Node end
		/////////////////////////////////
		irr::scene::ISceneNode* nodeEnd	= notesLine->getNodeEnd(i) ;			

		if (nodeEnd)
		{
			irr::core::vector3df vect 	= nodeEnd->getScale() ;
			int lenghtToGo				= (int)vect.X ;
				
			if (successPlaying)
			{
				/////////////////////////////////
				// Draw the sprites
				/////////////////////////////////				
				if (!this->nodesSprites[i]) // The sprite don't exists so create it
				{
					this->nodesSprites[i] = this->smgrFront->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(this->distEcart, 200.0f), irr::core::vector3df(0, 1, this->distEcart*2 - (this->distEcart*i) + this->yOffset)) ;
					this->setProperties(this->nodesSprites[i]) ;
				}
				
				// Texture it (if exist or when creating)
				this->nodesSprites[i]->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(irr::core::stringc(SPRITE_INDEX+this->spriteAnim).c_str()))) ; // Apply texture	
				this->spriteAnim = (this->spriteAnim + 1) % 5 ; // Next note will not have the same texture

				/////////////////////////////////
				// Manage the node itself
				/////////////////////////////////
				if (vect.X > 20) // At the end of the maintaining
				{
					vect.X 	= vect.X - timeDiff - 1 ; // Burn
					
					if(vect.Z != 40)
					{
						vect.Z = 40 ; // We played correctly so update the node width
					}
				}
				else
				{
					nodeEnd->setVisible(false) ;
					shouldRemoveSprite = true ;
				}
				
				/////////////////////////////////
				// Animators part
				/////////////////////////////////
				
				// Workaround for animators bogue (grabed twice)
				irr::core::list<irr::scene::ISceneNodeAnimator*> ls = nodeEnd->getAnimators() ;
				nodeEnd->removeAnimators() ; // First drop
				irr::core::list<irr::scene::ISceneNodeAnimator*>::Iterator it = ls.begin();
				for (; it != ls.end(); ++it)
				{
					(*it)->drop() ; // Second drop
				}
				// End workaround
		
				float a = this->animOffset * ((lenghtToGo / 2) - timeDiff) ;
				float b = this->animOffset * ((lenghtToGo / 2) - timeDiff + 200) ;

				irr::scene::ISceneNodeAnimator* anim = this->smgrMed->createFlyStraightAnimator( 
						irr::core::vector3df((lenghtToGo/2) - timeDiff, 0, this->distEcart*2-(this->distEcart*i) + this->yOffset - a),
						irr::core::vector3df(0-(lenghtToGo/2) - 200 - timeDiff, 0, this->distEcart*2-(this->distEcart*i) + this->yOffset + b),
						lenghtToGo + 200,
						false) ;
						
				irr::scene::ISceneNodeAnimator* anim2 = this->smgrMed->createDeleteAnimator(lenghtToGo + 200) ;

				nodeEnd->addAnimator(anim) ;
				nodeEnd->addAnimator(anim2) ;
			}
			else	// We screwed
			{
				/////////////////////////////////
				// Manage the node itself
				/////////////////////////////////
				shouldRemoveSprite 	= true ;
				vect.Z 				= NOTE_END_WIDTH ; // Set the new scale and texture for the node
				nodeEnd->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(MISSED_LINE))) ; // Swap texture
			}
			
			nodeEnd->setScale(vect) ; // Set the node scale
		}
			
		if (shouldRemoveSprite)
		{
			/////////////////////////////////
			// Remove the sprites
			/////////////////////////////////
			if (this->nodesSprites[i])
			{
				this->nodesSprites[i]->remove() ;
				this->nodesSprites[i] = 0 ;
			}
			
			shouldRemoveSprite = false ;
		}
	}
}

bool GridManager::checkLine(InputReceiver* myReceiver, SongManager* mySongManager, SceneManager* mySceneManager, int time, int lastTime, int player)
{   	
	NotesLine* line = this->getLineToPlay() ;

	if (line == 0)
	{
		return false ;	
	}

	int lineStart 	= line->getStartTime() ;	// Get line start time
	int lineEnd 	= line->getEndTime() ;		// Get line end time
	int lineLength 	= line->getLength() ;		// Get line length
	int timeDiff 	= time - lineStart ; 		// For drawing 3D effects
	bool nextLine	= true ;					// Go next line until we shouldn't (to be sure that we can't stay here for a while)

	///////////////////////////////////////////////////////////////////////////////
	// Could we play the line ? (startTime +- MS_DELAY and not played well yet)  //
	///////////////////////////////////////////////////////////////////////////////
	if ((time >= (lineStart - MS_DELAY)) && (time <= (lineStart + MS_DELAY)) && !myReceiver->hasPlayedNotesLine(player))
	{
		if (myReceiver->checkInputsFor(STATE_PLAY, line, player))
		{
			this->setCurrentLineEffect(true, timeDiff) ;
			this->myScoreCounter->getStats()->linePlayed(LINE_PLAYED, line->getNotesCount()) ;
			this->myScoreCounter->addMessage(PRECISION, timeDiff) ;
			mySceneManager->setLight() ;
			
			if(!this->player)
			{
				mySongManager->muteGuitar(1) ;
			}
		}
		
		nextLine = false ;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// We can't play the line anymore, look if we played well when we could and if the line isn't outdated //
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	else if ((time < lineEnd) && myReceiver->hasPlayedNotesLine(player))
	{
		if (lineLength > 1) // It's a maintainable one
		{
			if (myReceiver->checkInputsFor(STATE_MAINTAIN, line, player))
			{
				for (int i = 0 ; i < time - lastTime ; i++)	// For being fps independant
				{
					this->myScoreCounter->getStats()->linePlayed(LINE_STILL_PLAYED, line->getNotesCount()) ;
					this->setCurrentLineEffect(true) ;
				}
				
				// If we are close to the end of the line go next line
				nextLine = (time > lineEnd) ;
			}
			else // We stopped maintaining
			{
				this->setCurrentLineEffect(false) ;
				
				if (!this->sustainMode && (lineStart + lineLength - MS_DELAY * 2) - time > 0)
				{
					if(!this->player)
					{
						mySongManager->muteGuitar(0) ;
					}
				}
			}
		}
	}

	//////////////////////////////////////////////////
	// The time is not to play, should do nothing ! //
	//////////////////////////////////////////////////
	else if (time < lineStart)
	{
		if(!myReceiver->checkInputsFor(STATE_NOTHING, 0, player))
		{
			this->myScoreCounter->addMessage(ERROR_IDLE, timeDiff) ;
			mySongManager->playSound(irr::core::stringc(this->myRessources->getFile(PLAYING_ERROR_SOUND))) ;
			
			if(!this->player) // Single player mode, take care of errors
			{
				mySongManager->muteGuitar(0) ;
			}
		}
		
		nextLine = false ;
	}

	//////////////////////////////
	// Should we go next line ? //
	//////////////////////////////
	if (nextLine)
	{
		if (!myReceiver->hasPlayedNotesLine(player))
		{
			this->myScoreCounter->getStats()->linePlayed(LINE_MISSED, line->getNotesCount()) ;
			this->myScoreCounter->addMessage(ERROR_LINE, timeDiff) ;
			this->setCurrentLineEffect(false, timeDiff) ;
			
			if(!this->player) // Single player mode, take care of errors
			{
				mySongManager->muteGuitar(0) ;
			}
		}
		else
		{
 			this->setCurrentLineEffect(false) ;
		}
	}

	// Return to gameLoop if we should go next line or not
	return nextLine ;
}

ScoreCounter* GridManager::getScoreCounter()
{
	return this->myScoreCounter ;	
}

void GridManager::nextLineToDraw()
{
	if (this->hasMoreLineToDraw())
	{
		this->posDraw++ ;	
	}
}

void GridManager::nextLineToPlay()
{
	if (this->hasMoreLineToPlay())
	{
		this->posInFile++ ;
	}
}

bool GridManager::hasMoreLineToDraw()
{
	if (this->posDraw != this->notesLines->end())
	{
		return true ;
	}

	return false ;
}

bool GridManager::hasMoreLineToPlay()
{
	if (this->posInFile != this->notesLines->end())
	{
		return true ;
	}
	
	return false ;
}

NotesLine* GridManager::getLineToDraw()
{
	if (this->hasMoreLineToDraw())
	{
		return (*this->posDraw) ;
	}
	
	return 0 ;
}

NotesLine* GridManager::getLineToPlay()
{
	if (this->hasMoreLineToPlay())
	{
		return (*this->posInFile) ;
	}
	
	return 0 ;
}

void GridManager::moveKey(int key, bool pushed)
{
	irr::scene::ISceneNode* node = this->smgrFront->getSceneNodeFromId(key) ;
	
	for(int i = 0 ; i < 6 && node ; i++)
	{
		if (key == this->keyMap[i])
		{
			if (pushed)
			{	
				node->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(irr::core::stringc(15 + i).c_str()))) ; // Apply texture
			}
			else
			{
				node->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(KEY_DESEL))) ; // Apply texture			
			}

			return ;
		}
	}
}
