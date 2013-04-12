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

#include "GuiMainPage.h"

GuiMainPage::GuiMainPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources)
: GuiPage(baseSmgr, driver, ressources, MAIN_FONT)
{
	this->createGui() ;
}

void GuiMainPage::performAction(ACTION_TYPE at, int val)
{
	// Nothing	
}

void GuiMainPage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addSimpleText(irr::core::dimension2d<irr::s32>(192, 64), TEXT_GAME_VERSION, irr::video::SColor(128, 255, 255, 255), -200, -220, true) ;
	this->addButton(BUTTON1_MAIN, ID_TEXT_BTN_GO_SELECT_SONG_FROM_MENU) ;
	this->addButton(BUTTON2_MAIN, ID_TEXT_BTN_GO_CREDITS_FROM_MENU) ;
	this->addButton(BUTTON3_MAIN, ID_TEXT_BTN_EXIT_GAME_FROM_MENU) ; 
	this->addSimpleImage(BACK_TOP_MAIN) ;
	this->addBackground(BACK_MAIN) ;
}

void GuiMainPage::destroyGui()
{

}
