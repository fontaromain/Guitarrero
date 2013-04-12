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

#ifndef _GUIMODESELECTPAGE_H_
#define _GUIMODESELECTPAGE_H_

#include "include.h"
#include "GuiPage.h"
#include "GameMode.h"

class GuiModeSelectPage : public GuiPage
{
	public :
		GuiModeSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, GameMode* myGameMode) ;
		
		void				performAction(ACTION_TYPE at, int val) ;
		int					getSelectedNbPlayers() ;
		LEVEL				getSelectedLevel() ;

	private :
		void				switchNbPlayer() ;
		void				switchLevel() ;
		void 				drawPlayers() ;
		void 				drawLevels() ;
		void 				destroyGui() ;
		void 				createGui() ;

		std::deque<irr::core::stringw> levels ;
		std::deque<irr::core::stringw> players ;
		int 				selectedLevel ;
		int 				selectedPlayer ;
};

#endif
