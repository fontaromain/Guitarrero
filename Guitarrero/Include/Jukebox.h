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

#ifndef _JUKEBOX_H_
#define _JUKEBOX_H_

#include "include.h"
#include "Sequence.h"
#include "GraphicsManager.h"
#include "irrlicht.h"
#include "irrklang.h"
#include <map>

class Jukebox
{
	public :
		Jukebox(irr::IrrlichtDevice*, int delay, irr::core::stringc songsDirectory) ;
		~Jukebox() ;

		std::map<irr::core::stringc, Sequence*>*	getSequences(irr::core::stringc index) ;
		
	private :
		std::map<irr::core::stringc, Sequence*>* 	songsMap ;	// All available song (ordered by name)
};

#endif
