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

#ifndef _CEREALIZER_H_
#define _CEREALIZER_H_

#include "Player.h"
#include "include.h"

class Cerealizer
{
	public :		
		irr::core::array<Player*>	parse(irr::core::stringc str) ;
		irr::core::stringc 			serialize(irr::core::array<Player*> list) ;

	private :
		int 						getIntVal(int val) ; 					// Hex ascii to int
		char 						getHexVal(int val) ;
		Player* 					parseTuple(irr::core::stringc tuple) ;	// Parse a tuple
};

#endif
