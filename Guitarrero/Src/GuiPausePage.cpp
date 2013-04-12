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

#include "GuiPausePage.h"

GuiPausePage::GuiPausePage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources)
: GuiPage(baseSmgr, driver, ressources, PAUSE_FONT)
{
	// Create the gui
	this->createGui() ;
}

void GuiPausePage::performAction(ACTION_TYPE at, int val)
{
	// Nothing
}

void GuiPausePage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addBackground(BACK_PAUSE) ;
	this->addButton(BUTTON1_PAUSE, ID_TEXT_BTN_RESUME_FROM_PAUSE) ; 
	this->addButton(BUTTON2_PAUSE, ID_TEXT_BTN_GO_RESTART_FROM_PAUSE) ; 
	this->addButton(BUTTON3_PAUSE, ID_TEXT_BTN_GO_MENU_FROM_PAUSE) ;
}

void GuiPausePage::destroyGui()
{

}