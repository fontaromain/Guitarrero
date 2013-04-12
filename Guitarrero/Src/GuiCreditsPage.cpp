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

#include "GuiCreditsPage.h"

GuiCreditsPage::GuiCreditsPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources)
: GuiPage(baseSmgr, driver, ressources, CREDITS_FONT)
{
	this->createGui() ;
}

void GuiCreditsPage::performAction(ACTION_TYPE at, int val)
{
	// Nothing
}

void GuiCreditsPage::createGui()
{
	this->clear() ;
	this->addCamera(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;

	this->addSimpleText(irr::core::dimension2d<irr::s32>(580, 400), TEXT_CREDITS, irr::video::SColor(255, 255, 255, 255), 35, 0, true) ;
	this->addButton(BUTTON1_CREDITS, ID_TEXT_BTN_GO_MENU_FROM_CREDITS) ; 
	this->addBackground(BACK_CREDITS) ;	
}

void GuiCreditsPage::destroyGui()
{

}
