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

#ifndef _GUISMODESELECTPAGE_H_
#define _GUISMODESELECTPAGE_H_

#include "include.h"
#include "GuiPage.h"

#define TEXT_MODE_NORMAL 			L"Normal"
#define TEXT_MODE_REFLEX 			L"Reflex"
#define TEXT_MODE_DUEL				L"Duel"
#define TEXT_MODE_DUEL_P			L"Duel Pro"
#define TEXT_MODE_DUEL_REFLEX		L"Duel Reflex"
#define TEXT_MODE_DUEL_P_REFLEX		L"Duel Pro Reflex"


class GuiSModeSelectPage : public GuiPage
{
	public :
		GuiSModeSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, int nbPlayer) ;

		void				performAction(ACTION_TYPE at, int val) ;
		GMODE				getSelectedMode() ;

	private :
		void				switchMode() ;
		void 				drawModes() ;
		void 				destroyGui() ;
		void 				createGui() ;

		std::deque<irr::core::stringw> modes ;
		int 				selectedMode ;
};

#endif
