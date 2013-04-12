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

#ifndef _SCORECOUNTER_H_
#define _SCORECOUNTER_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"
#include "Statistics.h"

/* Informations on screen type */
#define ERROR_LINE		0	// Missed line
#define ERROR_IDLE		1	// Playing when should not
#define PRECISION		2	// Precision when playing

class GridManager ;

class ScoreCounter
{
	public :
		ScoreCounter(GridManager* grid, Statistics* stats, int xStats, int yStats) ;
		~ScoreCounter() { }

		Statistics*								getStats() { return this->myStats ; }
		void									addMessage(int type, int precision = 0) ;
		void 									update() ;

	private :
		void									create(int xStats, int yStats) ;

		irr::scene::IBillboardTextSceneNode* 	lineStreakDigitA ;
		irr::scene::IBillboardTextSceneNode* 	lineStreakDigitB ;
		irr::scene::IBillboardTextSceneNode* 	lineStreakDigitC ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitA ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitB ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitC ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitD ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitE ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitF ;
		irr::scene::IBillboardTextSceneNode* 	scoreDigitG ;
		irr::scene::IBillboardSceneNode* 		counterMultiplicator ;
		irr::scene::IBillboardSceneNode* 		counter ;
		irr::scene::ISceneNode*					precision ;
		irr::gui::IGUIFont* 					textFont ;
		GridManager* 							myGrid ;
		Statistics*								myStats ;
};

#endif
