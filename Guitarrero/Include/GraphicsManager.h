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

#ifndef _GRAPHICSMANAGER_H_
#define _GRAPHICSMANAGER_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"
#include "GameMode.h"
#include "SongManager.h"
#include "InputReceiver.h"
#include "Statistics.h"
#include <deque>
#include "NotesLine.h"
#include "ScoreCounter.h"
#include "TimeCounter.h"
#include "GridManager.h"
#include "SceneManager.h"


class Game ;

class GraphicsManager
{
	public :
		GraphicsManager(Game* myGame, bool use3D, bool sustainMode) ;
		~GraphicsManager() 	{ this->destroy() ; }

		void						moveKey(int key, bool pushed) ;
		bool 						update(int time) ;
		void						destroy() ;
		void 						create() ;
		void 						render() ;

	private :
		void						prepareLines(std::deque<NotesLine*>* lines, int player = 0) ;

		irr::scene::ISceneManager* 	frontSmgr ;
		std::deque<GridManager*>	gridManagers ;
		SceneManager*				mySceneManager ;
		TimeCounter*				myTimeCounter ;
		RENDER_STATE				rState ;			// Which render state the game is
		Game*						myGame ;
		bool						sustainMode ;
		bool						created ;
		bool						use3D ;
		int							lastTime ;
};

#endif
