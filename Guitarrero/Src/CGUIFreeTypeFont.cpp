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

#include "CGUIFreetypeFont.h"
#include <cassert>

using namespace irr;
using namespace gui;



// --------------------------------------------------------
CGUITTGlyph::CGUITTGlyph()
: IReferenceCounted()
    ,cached(false)
    ,size(0)
	,top(0)
	,left(0)
	,texw(0)
	,texh(0)
	,imgw(0)
	,imgh(0)
	,offset(0)
{
}

CGUITTGlyph::~CGUITTGlyph()
{
}

void CGUITTGlyph::cache(u32 idx_, FT_Face face_, video::IVideoDriver* driver_)
{
	FT_Set_Pixel_Sizes(face_, 0, size) ;
	
	if (!FT_Load_Glyph(face_, idx_, FT_LOAD_NO_HINTING|FT_LOAD_NO_BITMAP))
	{
		FT_GlyphSlot glyph = face_->glyph ;
		FT_Bitmap bits ;

		if (glyph->format == ft_glyph_format_outline)
		{
			if (!FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL))
			{
				bits 	= glyph->bitmap ;
				u8 *pt 	= bits.buffer ;
				top 	= glyph->bitmap_top ;
				left 	= glyph->bitmap_left ;
				imgw 	= 1 ;
				imgh 	= 1 ;
				texw 	= bits.width ;
				texh 	= bits.rows ;
				
				for(;;)
				{
					if (imgw > texw)
					{
						break;
					}
					else
					{
						imgw <<= 1 ;
					}
				}
				for(;;)
				{
					if (imgh > texh)
					{
						break ;
					}
					else
					{
						imgh <<= 1 ;
					}
				}
				if (imgw > imgh)
				{
					imgh = imgw ;
				}
				else
				{
					imgw = imgh ;
				}
								
				u32 *texd 	= new u32[imgw * imgh] ;	
				u32 *texp 	= texd ;
				offset 		= size - bits.rows ;
				memset(texd, 0, imgw * imgh * sizeof(u32)) ; // Init memory

				bool cflag = (driver_->getDriverType() == video::EDT_DIRECT3D8) ;
	
				for (int i = 0 ; i < bits.rows ; i++)
				{
					u32 *rowp = texp ;
					
					for (int j = 0 ; j < bits.width ; j++)
					{
						if (*pt)
						{
							if (cflag)
							{
								*rowp = *pt ;
								*rowp *= 0x01010101 ;
							}
							else
							{
								*rowp = *pt << 24 ;
								*rowp |= 0xffffff ;
							}
						}
						else
						{
                            *rowp = 0 ;
						}
						
						pt++ ;
						rowp++ ;
					}
					texp += imgw ;
				}
				
				img 	= driver_->createImageFromData(video::ECF_A8R8G8B8, core::dimension2d<s32>(imgw, imgh), texd) ;
				cached 	= true ;
				
				delete[] texd ;
			}
		}
	}
}

// --------------------------------------------------------
FT_Library	CGUITTFace::library  = 0;
int CGUITTFace::countClassObjects = 0;

CGUITTFace::CGUITTFace(const irr::core::stringw& filename)
: face(0)
{
	++countClassObjects ;

	this->load(filename) ;
}

CGUITTFace::~CGUITTFace()
{
	if ( face )
		FT_Done_Face( face );

	--countClassObjects;
	assert(countClassObjects >= 0 );
	if ( !countClassObjects && library )
	{
		FT_Done_FreeType( library );
		library = 0;
	}
}

//! loads a font file
bool CGUITTFace::load(const irr::core::stringw& filename)
{
    if ( !library )
    {
        if (FT_Init_FreeType( &library ))
        {
            return	false;
        }
    }
    
    core::stringc ansiFilename(filename);
    
	if (FT_New_Face( library,ansiFilename.c_str(),0,&face ))
	{
		return	false;
	}
	
	return	true;
}

// --------------------------------------------------------
//! constructor
CGUIFreetypeFont::CGUIFreetypeFont(video::IVideoDriver* driver, bool Transparency)
: Driver(driver), Transparency(Transparency)
, tt_face(0)
{
	#ifdef _DEBUG
	setDebugName("CGUIFreetypeFont");
	#endif

	if (Driver)
		Driver->grab();
}

//! destructor
CGUIFreetypeFont::~CGUIFreetypeFont()
{
    if ( tt_face )
    {
        //tt_face->drop();
        delete tt_face ;
	}
	if (Driver)
	{
		Driver->drop();
	}

    for (unsigned int i=0; i < Glyphs.size(); ++i)
    {
        delete Glyphs[i];
        Glyphs[i] = 0;
    }
}

bool CGUIFreetypeFont::attach(CGUITTFace *Face,u32 size)
{
	if (!Driver || !Face)
		return false;

    if ( tt_face )
        tt_face->drop();
        
	tt_face = Face;
	
	if ( !tt_face )
        return false;
        
    if ( !tt_face->face)
    {
		return false ;
	}

	tt_face->grab();

    for (unsigned int i = 0; i < Glyphs.size(); ++i)
    {
        delete Glyphs[i];
        Glyphs[i] = 0;
    }

	Glyphs.reallocate(tt_face->face->num_glyphs);
	Glyphs.set_used(tt_face->face->num_glyphs);

	for (int i = 0;i < tt_face->face->num_glyphs;i++)
	{
        CGUITTGlyph * glyph = new CGUITTGlyph();

		glyph->size = size;

        Glyphs[i] = glyph;
	}
	
	return	true;
}

u32 CGUIFreetypeFont::getGlyphByChar(wchar_t c) const
{
	u32 idx = FT_Get_Char_Index( tt_face->face, c );
	
	if (idx == 0)
	{
        idx = 1 ;
    }
	
	if ( idx && !Glyphs[idx - 1]->cached )
        Glyphs[idx - 1]->cache(idx, tt_face->face, Driver);
	return	idx;
}

//! returns the dimension of a text
core::dimension2d<s32> CGUIFreetypeFont::getDimension(const wchar_t* text) const
{
	core::dimension2d<s32> dim(0, Glyphs[0]->size);

	for(const wchar_t* p = text; *p; ++p)
	{
		dim.Width += getWidthFromCharacter(*p);
	}

	return dim;
}

irr::video::ITexture* CGUIFreetypeFont::makeTexEn(std::deque<irr::core::stringw> textLines, irr::core::dimension2d<irr::s32> clip, irr::video::SColor wantedColor)
{
	irr::video::ITexture* texture 	= 0 ; // The texture to be returned

	// Calculate the texture size
	irr::core::dimension2d<irr::s32> texSize(0, 0) ;
	
	for (int i = 0 ; i < textLines.size() ; i++)
	{
		irr::core::dimension2d<irr::s32> lineSize = this->getDimension(textLines[i].c_str()) ;
		
		if (lineSize.Width > texSize.Width)
		{
			texSize.Width = lineSize.Width ;
		}
		
		texSize.Height += lineSize.Height ;
	}

	texSize.Width 	+= 2 ; 	// Workaround (sinon bogue des textes avec les bords noirs)
	texSize.Height 	+= 2 ;	// Workaround
	
	irr::video::IImage* img = Driver->createImage(irr::video::ECF_A8R8G8B8, texSize);
	img->fill(irr::video::SColor(0, 0, 0, 0)) ;
	
	int xOffset 		= 0 ;
	int xSpecialOffset 	= 0 ;
	int yOffset 		= 0 ;
	int ySpecialOffset 	= 0 ;

	for (int line = 0 ; line < textLines.size() ; line++)
	{		
		// Update position
		xOffset = (texSize.Width - this->getDimension(textLines[line].c_str()).Width) / 2 ; // CENTER
		
		for (int i = 0 ; i < textLines[line].size() ; i++) // For each wchar_t
		{
			CGUITTGlyph* gl = this->getGlyph(textLines[line][i]) ;
			
			if (gl && gl->img)
			{
				// Update offsets for this char
				ySpecialOffset 	= gl->size - gl->top - (gl->size / 4) /*CENTER*/ ;
				xSpecialOffset  = gl->left ;
				
				// Lets have some fun code (hum) copyToWithAlpha from IImage should be more efficient with some tweaks
				int imgW = gl->img->getDimension().Width ;
				int imgH = gl->img->getDimension().Height ;
				for (int w = 0 ; w < imgW ; w++)
				{
					for (int h = 0 ; h < imgH ; h++)
					{
						irr::video::SColor color = gl->img->getPixel(w, h) ;
						
						if(color != irr::video::SColor(0, 0, 0, 0))
						{	
							int currentAlpha 	= color.getAlpha() ;
						//	int wantedAlpha 	= wantedColor.getAlpha() ; HOW TO GET ALPHA WORKING ?!
			
							wantedColor.setAlpha(currentAlpha) ;
						
							int pX = xOffset + xSpecialOffset + w ;
							int pY = yOffset + ySpecialOffset + h ;
							
							if (pX < img->getDimension().Width && pY < img->getDimension().Height)
							{
								img->setPixel(pX, pY, wantedColor) ;
							}
						}
					}
				}
			}
			
			// Update position
			xOffset += this->getWidthFromCharacter(textLines[line][i]) ;
		}
		
		// Update position
		yOffset += this->Glyphs[0]->size ;
	}

	// Make the texture
	texture = Driver->addTexture("", img) ;
	
	// Cleanup
	img->drop() ;
	
	// Return it !
	return texture ;
}

inline u32 CGUIFreetypeFont::getWidthFromCharacter(wchar_t c) const
{
	u32 n = getGlyphByChar(c);
	if ( n > 0)
	{
		int w = Glyphs[n - 1]->texw;
		s32 left = Glyphs[n - 1]->left;
		if (w + left > 0)
            return w + left;
	}
	if (c >= 0x2000)
	{
		return	Glyphs[0]->size;
	}
	else
	{
		return	Glyphs[0]->size / 2;
	}
}

//! Calculates the index of the character in the text which is on a specific position.
s32 CGUIFreetypeFont::getCharacterFromPos(const wchar_t* text, s32 pixel_x) const
{
	s32 x = 0;
	s32 idx = 0;

	while (text[idx])
	{
		x += getWidthFromCharacter(text[idx]);

		if (x >= pixel_x)
			return idx;

		++idx;
	}

	return -1;
}


CGUITTGlyph* CGUIFreetypeFont::getGlyph(const wchar_t c)
{
    int idx = this->getGlyphByChar(c) ;
    
    if (idx == 0)
    {
        idx = 1 ;
    }
    
	return this->Glyphs[idx - 1] ;
}
