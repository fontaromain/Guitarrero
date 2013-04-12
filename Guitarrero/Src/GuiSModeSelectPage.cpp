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

#include "GuiSModeSelectPage.h"

GuiSModeSelectPage::GuiSModeSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, int nbPlayer)
: GuiPage(baseSmgr, driver, ressources, SMODE_FONT)
{
	// Init class members
	this->selectedMode = 0 ;

	// Init mode deque
	switch (nbPlayer)
	{
		case 1 :
			this->modes.push_back(TEXT_MODE_NORMAL) ;
			this->modes.push_back(TEXT_MODE_REFLEX) ;
			break ;
			
		case 2 :
			//this->modes.push_back(TEXT_MODE_DUEL) ;
			this->modes.push_back(TEXT_MODE_DUEL_P) ;
			//this->modes.push_back(TEXT_MODE_DUEL_REFLEX) ;
			this->modes.push_back(TEXT_MODE_DUEL_P_REFLEX) ;
			break ;
	}
	
	// Create the gui
	this->createGui() ;
}

void GuiSModeSelectPage::performAction(ACTION_TYPE at, int val)
{
	switch(at)
	{
		case ACTION_P1_KEY_PRESSED :
		{
			switch(val)
			{
				case FRET_3 : // Change Mode
				{
					this->switchMode() ;
					break ;
				}
			}
			
			break ;		
		}
	}
}

void GuiSModeSelectPage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addBackground(BACK_SMODE) ;
	this->addButton(BUTTON1_SMODE, ID_TEXT_BTN_GO_GAME_FROM_SMODE_SELECTION) ; 
	this->addButton(BUTTON2_SMODE, ID_TEXT_BTN_GO_SONG_FROM_SMODE_SELECTION) ; 
	this->addButton(BUTTON3_SMODE, ID_TEXT_BTN_CHANGE_MODE_FROM_SMODE_SELECTION) ; 		
	
	this->drawModes() ;
}

void GuiSModeSelectPage::destroyGui()
{

}

void GuiSModeSelectPage::switchMode()
{
	if (++this->selectedMode >= this->modes.size())
	{
		this->selectedMode = 0 ;
	}
	
	this->createGui() ;	
}

void GuiSModeSelectPage::drawModes()
{
	irr::core::position2d<irr::s32> pos = this->myRessources->getPosition(SMODELIST_POSITION) ;
	for (int i = 0 ; i < this->modes.size() ; i++)
	{
		this->addSimpleText(irr::core::dimension2d<irr::s32>(160, 160), this->modes[i].c_str(), (i == this->selectedMode ? this->myRessources->getColor(SELECTED_SMODE_COLOR) : this->myRessources->getColor(SMODELIST_COLOR)), pos.X - i * 20, pos.Y) ;
	}
}

GMODE GuiSModeSelectPage::getSelectedMode()
{
	GMODE modeSelected = GM_NORMAL ;
	
	if (wcscmp(this->modes[this->selectedMode].c_str(), TEXT_MODE_REFLEX) == 0)
	{
		modeSelected = GM_REFLEX ;
	}
	else if (wcscmp(this->modes[this->selectedMode].c_str(), TEXT_MODE_DUEL) == 0)
	{
		modeSelected = GM_DUEL ;
	}
	else if (wcscmp(this->modes[this->selectedMode].c_str(), TEXT_MODE_DUEL_P) == 0)
	{
		modeSelected = GM_DUEL_P ;
	}
	else if (wcscmp(this->modes[this->selectedMode].c_str(), TEXT_MODE_DUEL_REFLEX) == 0)
	{
		modeSelected = GM_DUEL_REFLEX ;
	}
	else if (wcscmp(this->modes[this->selectedMode].c_str(), TEXT_MODE_DUEL_P_REFLEX) == 0)
	{
		modeSelected = GM_DUEL_P_REFLEX ;
	}

	return modeSelected ;	
}
