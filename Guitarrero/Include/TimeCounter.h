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

#ifndef _TIMECOUNTER_H_
#define _TIMECOUNTER_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"

class TimeCounter
{
	public :
		TimeCounter(irr::scene::ISceneManager* smgr, Ressources* myRessources) ;
		~TimeCounter() ;
		
		void 									setTime(int msLeft) ;
		void									render() ;
		
	private :
		void									create() ;

		irr::scene::IBillboardTextSceneNode* 	timeSeparator ;
		irr::scene::IBillboardTextSceneNode* 	timeDigitA ;
		irr::scene::IBillboardTextSceneNode* 	timeDigitB ;
		irr::scene::IBillboardTextSceneNode* 	timeDigitD ;
		irr::scene::IBillboardTextSceneNode* 	timeDigitE ;
		irr::scene::IBillboardSceneNode* 		counter ;	
		irr::scene::ISceneManager* 				smgr ;			// Scene manager
		irr::video::IVideoDriver* 				driver ;		// 3D Driver
		irr::gui::IGUIFont*						textFont ;		// The text font
		Ressources*								myRessources ;	// Ressource bundle
};

#endif
