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

#ifndef _GUIMAINPAGE_H_
#define _GUIMAINPAGE_H_

#include "include.h"
#include "GuiPage.h"

/* STATIC TEXTS */
#define TEXT_GAME_VERSION 	GAME_VERSION"\nBy "GAME_AUTHOR


class GuiMainPage : public GuiPage
{
	public :
		GuiMainPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources) ;

		void	performAction(ACTION_TYPE at, int val) ;
		
	private :
		void 	destroyGui() ;
		void 	createGui() ;
};

#endif
