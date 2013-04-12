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
#include "GuiManager.h"

GuiManager::GuiManager(Game* myGame)
{
	this->myGame 		= myGame ;	// The game to interact with
	this->baseSmgr 		= this->myGame->myGraphicEngine->getSceneManager()->createNewSceneManager() ;
	this->page 			= 0 ;		// No page created
}

GuiManager::~GuiManager()
{
	delete this->page ;
}

void GuiManager::render()
{
	if (this->page)
	{
		this->page->render() ;
	}
}

void GuiManager::performAction(ACTION_TYPE action, int value)
{
	if (this->page)
	{
		this->page->performAction(action, value) ;
		
		// Special case of song selection
		if (this->myGame->state == GS_SONG_SELECTION)
		{
			if (value == FRET_5)
			{
				if (this->myGame->mySongManager->isPlaying())
				{
					this->myGame->mySongManager->pause() ;
				}
				else
				{
					this->myGame->mySongManager->resume() ;
				}
			}
			else if (((GuiSongSelectPage*)(this->page))->shouldPreview())
			{
				this->myGame->mySongManager->setDirectory(((GuiSongSelectPage*)(this->page))->getSequence()->getDirectory(), true) ;
			}
		}
	}
}

void GuiManager::setState(GAME_STATE newState)
{
	GuiPage*  newPage = 0 ;
	
	switch(newState)
	{
		case GS_PAUSE :
		{
			newPage = new GuiPausePage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources) ;	
			break ;
		}
		case GS_SONG_STATISTIC :
		{
			newPage = new GuiStatisticsPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources, this->myGame->myGameMode) ;
			break ;
		}
		case GS_MAIN:
		{
			if (this->myGame->state == GS_SONG_SELECTION && this->page != 0)
			{
				this->myGame->myGameMode->setSequence(((GuiSongSelectPage*)(this->page))->getSequence()) ; // Get selected sequence back
			}
			else if (this->myGame->state == GS_SONG_STATISTIC && this->page != 0)
			{
				this->myGame->myGameMode->getSequence()->getSeqInfos()->addPlayer(((GuiStatisticsPage*)(this->page))->getName(), this->myGame->myGameMode->getStats()[0]->getScore(), 5, this->myGame->myGameMode->getLevel()) ;
				this->myGame->myGameMode->getSequence()->getSeqInfos()->saveInformationsFile() ;
			}

			newPage = new GuiMainPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources) ;	
			break ;
		}
		case GS_CREDITS :
		{			
			newPage = new GuiCreditsPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources) ;	
			break ;
		}
		case GS_SONG_SELECTION :
		{
			if (this->myGame->state == GS_SONG_STATISTIC && this->page != 0)
			{
				this->myGame->myGameMode->getSequence()->getSeqInfos()->addPlayer(((GuiStatisticsPage*)(this->page))->getName(), this->myGame->myGameMode->getStats()[0]->getScore(), 5, this->myGame->myGameMode->getLevel()) ;
				this->myGame->myGameMode->getSequence()->getSeqInfos()->saveInformationsFile() ;
			}
			
			newPage = new GuiSongSelectPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources, this->myGame->myJukebox, this->myGame->myGameMode) ;	
			this->myGame->mySongManager->setDirectory(((GuiSongSelectPage*)(newPage))->getSequence()->getDirectory()) ;
			this->myGame->mySongManager->play() ; // Even if setDirectory did nothing, start preview
			break ;
		}
		case GS_MODE_SELECTION :
		{
			if (this->myGame->state == GS_SONG_SELECTION && this->page != 0)
			{
				this->myGame->myGameMode->setSequence(((GuiSongSelectPage*)(this->page))->getSequence()) ; // Get selected sequence back
				this->myGame->myGameMode->getSequence()->loadMidFile() ; // Init the sequence
			}
			
			newPage = new GuiModeSelectPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources, this->myGame->myGameMode) ;
			break ;
		}
		case GS_SPECIAL_MODE_S :
		{
			if (this->page != 0)
			{
				this->myGame->myGameMode->setLevel(((GuiModeSelectPage*)(this->page))->getSelectedLevel()) ;
				this->myGame->myGameMode->setNbPlayer(((GuiModeSelectPage*)(this->page))->getSelectedNbPlayers()) ;
				newPage = new GuiSModeSelectPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources, this->myGame->myGameMode->getNbPlayer()) ;	
			}
			
			break ;
		}
		case GS_NO_LEVELS_AFTER_MODE_S :
		{
			newPage = new GuiNoLevelsPage(this->baseSmgr, this->myGame->myDriver, this->myGame->myRessources) ;
			break ;
		}
		case GS_RESTART_GAME :
		case GS_RESUME_GAME :
		case GS_GAME :
		{
			if (this->myGame->state == GS_SPECIAL_MODE_S && this->page != 0)
			{
				this->myGame->myGameMode->setMode(((GuiSModeSelectPage*)(this->page))->getSelectedMode()) ;
			}
		
			break ;
		}
	}

	// Manage page and store actual state and new page
	delete this->page ;
	this->page = newPage ;
}
