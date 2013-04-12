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

#ifndef CGUIFREETYPEFONT_H
#define CGUIFREETYPEFONT_H

#include <ft2build.h>
#include <freetype/freetype.h>
#include <irrlicht.h>
#include <deque>

class CGUITTFace : public irr::IReferenceCounted
{
	public:
		CGUITTFace(const irr::core::stringw& filename) ;
		virtual ~CGUITTFace() ;

		bool 	load(const irr::core::stringw& filename) ;

		FT_Face	face ;					// handle to face

	private:
		static int			countClassObjects ;
		static FT_Library	library ;	// handle to library
};

class CGUITTGlyph : public irr::IReferenceCounted
{
	public:
		CGUITTGlyph() ;
		virtual ~CGUITTGlyph() ;
	
	    bool 				cached ;
		void 				cache(irr::u32 idx_, FT_Face face_, irr::video::IVideoDriver* driver_) ;
		
		irr::u32 			size ;
		irr::u32 			top ;
		irr::u32 			left ;
		irr::u32 			texw ;
		irr::u32 			texh ;
		irr::u32 			imgw ;
		irr::u32 			imgh ;
		irr::s32 			offset ;
		irr::video::IImage 	*img ;
};

class CGUIFreetypeFont : public irr::gui::IGUIFont
{
	public:
		//! constructor
		CGUIFreetypeFont(irr::video::IVideoDriver* Driver, bool Transparency = false) ;
	
		//! destructor
		virtual ~CGUIFreetypeFont() ;
	
		//! loads a truetype font file
		bool attach(CGUITTFace *Face,irr::u32 size) ;
	
		//! returns the dimension of a text
		virtual irr::core::dimension2d<irr::s32> getDimension(const wchar_t* text) const ;
	
		//! Calculates the index of the character in the text which is on a specific position.
		virtual irr::s32 getCharacterFromPos(const wchar_t* text, irr::s32 pixel_x) const ;
	
		//! Not yet supported
		virtual void draw(const wchar_t* text, const irr::core::rect<irr::s32>& position, irr::video::SColor color, bool hcenter = false, bool vcenter = false, const irr::core::rect<irr::s32>* clip = 0) {}
	
		//! Not yet supported
		virtual void setKerningWidth(irr::s32 kerning) {}
	
		//! Not yet supported
		virtual void setKerningHeight(irr::s32 kerning) {}
	
		//! Not yet supported
		virtual irr::s32 getKerningWidth(const wchar_t* thisLetter = 0, const wchar_t* previousLetter = 0)	const { return 0 ; }
	
		//! Not yet supported
		virtual irr::s32 getKerningHeight()	const { return 0 ; }
	
		//! Not yet supported
	    virtual void setInvisibleCharacters(const wchar_t *s) {}
	
		//! Create a texture from a deque of strings
		irr::video::ITexture* makeTexEn(std::deque<irr::core::stringw> textLines, irr::core::dimension2d<irr::s32> clip, irr::video::SColor wantedColor) ;
	 
	private:
		CGUITTGlyph* 					getGlyph(const wchar_t c) ;	
		irr::u32 						getWidthFromCharacter(wchar_t c) const ;
		irr::u32 						getGlyphByChar(wchar_t c) const ;

		irr::core::array<CGUITTGlyph*> 	Glyphs ;
		irr::video::IVideoDriver* 		Driver ;
		CGUITTFace*						tt_face ;
		bool 							Transparency ;
};

#endif
