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

#ifndef _GUIMANAGER_H_
#define _GUIMANAGER_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"
#include "GameMode.h"
#include "Jukebox.h"
#include "GuiMainPage.h"
#include "GuiCreditsPage.h"
#include "GuiSongSelectPage.h"
#include "GuiModeSelectPage.h"
#include "GuiSModeSelectPage.h"
#include "GuiPausePage.h"
#include "GuiStatisticsPage.h"
#include "GuiNoLevelsPage.h"


class Game ;

class GuiManager
{
	public :
		GuiManager(Game* game) ;
		~GuiManager() ;

		void						performAction(ACTION_TYPE action, int value) ;
		void 						setState(GAME_STATE newState) ;
		void						render() ;

	private :
		irr::scene::ISceneManager* 	baseSmgr ;		// For creating smgr
		GuiPage* 					page ;			// The current gui page
		Game*						myGame ;
};

#endif
