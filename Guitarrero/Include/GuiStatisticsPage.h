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

#ifndef _GUISTATISTICSPAGE_H_
#define _GUISTATISTICSPAGE_H_

#include "include.h"
#include "GuiPage.h"
#include "GameMode.h"

class GuiStatisticsPage : public GuiPage
{
	public :
		GuiStatisticsPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, GameMode* myGameMode) ;

		void				performAction(ACTION_TYPE at, int val) ;
		irr::core::stringw 	getName() ;

	private :
		void 				inputName(char val) ;
		void 				destroyGui() ;
		void 				createGui() ;
		
		irr::core::stringw	name ;
		GameMode*			myGameMode ;
};

#endif
