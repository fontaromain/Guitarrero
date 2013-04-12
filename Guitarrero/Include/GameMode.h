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

#ifndef _GAMEMODE_H_
#define _GAMEMODE_H_

#include "include.h"
#include "Sequence.h"
#include "Statistics.h"
#include "Ressources.h"

/* DEFAULT VALUES */
#define DEFAULT_LINE_TO_DRAW	100
#define DEFAULT_NUMBER_PLAYER	1
#define DEFAULT_MODE	 		GM_NORMAL
#define DEFAULT_SPEED			1.0f
#define DEFAULT_LEVEL			LEVEL_EASY


class GameMode
{
	public :
								GameMode() ;
		std::deque<Statistics*> getStats() ;
		irr::core::stringw		getLevelStr(Ressources* res) ;
		Sequence*				getSequence() ;
		GMODE 					getMode() ;
		LEVEL					getLevel() ;
		void					setSequence(Sequence* seq) ;	
		void 					setlineToDraw(int nltd) ;
		void 					setNbPlayer(int nbPl) ;
		void					setSpeed(float speed) ;
		void					setLevel(LEVEL lvl) ;
		void	 				setMode(GMODE mode) ;
		int 					getLineToDraw() ;
		int 					getNbPlayer() ;
		float 					getSpeed() ;
		void 					addStats(Statistics* stat) ;
		void 					clearStats() ;

	private :		
		std::deque<Statistics*>	stats ;			// Players stats
		Sequence* 				seq ;			// Sequence to play
		LEVEL 					level ;			// Game level to parse
		GMODE 					mode ;			// Special game mode
		float 					speed ;			// Game speed
		int						lineToDraw ;	// How many line drawed on the neck
		int 					nbPlayer ;		// How many players
};

#endif
