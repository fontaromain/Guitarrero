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

#include "GuiModeSelectPage.h"

GuiModeSelectPage::GuiModeSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, GameMode* myGameMode)
: GuiPage(baseSmgr, driver, ressources, MODE_FONT)
{
	// Init class members
	this->levels 			= myGameMode->getSequence()->getAvLevels(this->myRessources) ;
	this->selectedPlayer	= myGameMode->getNbPlayer() - 1 ;
	this->selectedLevel		= 0 ;

	// Init listbox for players selection
	this->players.push_back(this->myRessources->getText(ID_TEXT_P1_FROM_MODE_SELECTION)) ;
	this->players.push_back(this->myRessources->getText(ID_TEXT_P2_FROM_MODE_SELECTION)) ;

	// Create the gui
	this->createGui() ;
}

void GuiModeSelectPage::performAction(ACTION_TYPE at, int val)
{
	switch(at)
	{
		case ACTION_P1_KEY_PRESSED :
		{
			switch(val)
			{
				case FRET_3 : // Change Level
				{
					this->switchLevel() ;
					break ;
				}
				case FRET_4 : // Change Nb Player
				{
					this->switchNbPlayer() ;
					break ;
				}
			}
			
			break ;		
		}
	}
}

void GuiModeSelectPage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addBackground(BACK_MODE) ;
	this->addButton(BUTTON1_MODE, ID_TEXT_BTN_GO_GAME_FROM_MODE_SELECTION) ; 
	this->addButton(BUTTON2_MODE, ID_TEXT_BTN_GO_SONG_FROM_MODE_SELECTION) ; 
	this->addButton(BUTTON3_MODE, ID_TEXT_BTN_CHANGE_LVL_FROM_MODE_SELECTION) ; 		
	this->addButton(BUTTON4_MODE, ID_TEXT_BTN_CHANGE_P_FROM_MODE_SELECTION) ;
	
	this->drawLevels() ;
	this->drawPlayers() ;
}

void GuiModeSelectPage::destroyGui()
{

}

void GuiModeSelectPage::switchLevel()
{
	if (++this->selectedLevel >= this->levels.size())
	{
		this->selectedLevel = 0 ;
	}
	
	this->createGui() ;	
}

void GuiModeSelectPage::switchNbPlayer()
{
	if (++this->selectedPlayer >= this->players.size())
	{
		this->selectedPlayer = 0 ;
	}
	
	this->createGui() ;		
}

void GuiModeSelectPage::drawPlayers()
{
	irr::core::position2d<irr::s32> pos = this->myRessources->getPosition(PLAYERLIST_POSITION) ;
	for (int i = 0 ; i < this->players.size() ; i++)
	{
		this->addSimpleText(irr::core::dimension2d<irr::s32>(160, 160), this->players[i].c_str(), (i == this->selectedPlayer ? this->myRessources->getColor(SELECTED_PLAYER_COLOR) : this->myRessources->getColor(PLAYERLIST_COLOR)), pos.X - i * 20, pos.Y) ;	
	}
}

void GuiModeSelectPage::drawLevels()
{
	irr::core::position2d<irr::s32> pos = this->myRessources->getPosition(LEVELLIST_POSITION) ;
	for (int i = 0 ; i < this->levels.size() ; i++)
	{
		this->addSimpleText(irr::core::dimension2d<irr::s32>(160, 160), this->levels[i].c_str(), (i == this->selectedLevel ? this->myRessources->getColor(SELECTED_LEVEL_COLOR) : this->myRessources->getColor(LEVELLIST_COLOR)), pos.X - i * 20, pos.Y) ;	
	}
}

LEVEL GuiModeSelectPage::getSelectedLevel()
{
	LEVEL levelToParse = LEVEL_EASY ;

	if (wcscmp(this->levels[this->selectedLevel].c_str(), this->myRessources->getText(ID_TEXT_LEVEL_HARD_FROM_MODE_SELECTION).c_str()) == 0)
	{
		levelToParse = LEVEL_HARD ;
	}
	else if (wcscmp(this->levels[this->selectedLevel].c_str(), this->myRessources->getText(ID_TEXT_LEVEL_NORMAL_FROM_MODE_SELECTION).c_str()) == 0)
	{
		levelToParse = LEVEL_NORMAL ;
	}
	else if (wcscmp(this->levels[this->selectedLevel].c_str(), this->myRessources->getText(ID_TEXT_LEVEL_MEDIUM_FROM_MODE_SELECTION).c_str()) == 0)
	{
		levelToParse = LEVEL_MEDIUM ;
	}

	return levelToParse ;	
}

int GuiModeSelectPage::getSelectedNbPlayers()
{
	return this->selectedPlayer + 1 ;	
}
