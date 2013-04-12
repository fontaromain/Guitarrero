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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Irrlicht.h" 
#include "Include.h"

class Player
{
	public :
		Player(irr::core::stringc name, irr::core::stringc stars, irr::core::stringc score)
		{
			this->score = score ;
			this->stars = stars ;
			this->level = LEVEL_EASY ;
			this->name	= name ;	
		}
		
		void				setLevel(LEVEL level) 	{ this->level = level ;}
		irr::core::stringc 	getScore() 				{ return this->score ;}
		irr::core::stringc 	getStars() 				{ return this->stars ;}
		LEVEL			 	getLevel() 				{ return this->level ;}
		irr::core::stringc 	getName() 				{ return this->name ;}
		
	private :
		irr::core::stringc 	name ;
		irr::core::stringc 	score ;
		irr::core::stringc 	stars ;
		LEVEL			 	level ;
};

#endif
