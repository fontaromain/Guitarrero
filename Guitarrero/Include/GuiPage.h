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

#ifndef _GUIPAGE_H_
#define _GUIPAGE_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"
#include <deque>

/* TEXTS SQUARE MARGIN */
#define H_MARGIN 8

class GuiPage
{
	public :
		GuiPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressource, const char* font) ;
		virtual ~GuiPage() ;
		
		virtual void					performAction(ACTION_TYPE at, int val) 	= 0 ;
		virtual void 					destroyGui()							= 0 ;
		virtual void 					createGui()								= 0 ;
		void							render() ;

	protected :
		irr::scene::ICameraSceneNode* 	addCamera(irr::core::vector3df pos, irr::core::vector3df lookAt) ;
		irr::scene::ISceneNode* 		addBackground(const char* name) ;
		irr::scene::ISceneNode* 		addButton(const char* name, const char* name) ;
		irr::scene::ISceneNode* 		addSimpleImage(const char* name, bool front = false) ;
		irr::scene::ISceneNode* 		addSimpleText(irr::core::dimension2d<irr::s32> square, const wchar_t* text, irr::video::SColor color, int x = 0, int y = 0, bool front = false) ;
		void 							cleanUpTextures() ;
		void							clear() ;

		Ressources*						myRessources ;		// Ressources (textures, texts ...)
		irr::scene::ISceneManager* 		guiFrontSmgr ;		// Scene manager to use
		irr::scene::ISceneManager* 		guiBackSmgr ;		// Scene manager to use
		irr::scene::ISceneManager* 		guiMedSmgr ;		// Scene manager to use
		irr::video::IVideoDriver* 		myDriver ;			// Driver to use
		CGUIFreetypeFont*				font ;				// Font to use
		irr::core::array<irr::video::ITexture*> textures ;	// To cleanup textures

	private :
		irr::scene::ISceneNode* 		addText(irr::core::dimension2d<irr::s32> square, irr::scene::ISceneManager* smgr, const wchar_t* text, irr::video::SColor color) ;
		irr::scene::ISceneNode* 		addImage(irr::scene::ISceneManager* smgr, irr::video::ITexture* texture, int x, int y) ;		
		std::deque<irr::core::stringw>	getTextLines(irr::core::stringw text) ;
		irr::scene::ISceneManager* 		getSceneManager(bool front) ;
		void							loadFont(const char* font) ;
};

#endif
