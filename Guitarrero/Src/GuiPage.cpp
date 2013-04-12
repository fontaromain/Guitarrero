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

#include "GuiPage.h"

GuiPage::GuiPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, const char* font)
{
	// Init class members
	this->guiFrontSmgr 	= baseSmgr->createNewSceneManager() ;
	this->guiMedSmgr	= baseSmgr->createNewSceneManager() ;
	this->guiBackSmgr 	= baseSmgr->createNewSceneManager() ;
	this->myDriver 		= driver ;
	this->myRessources 	= ressources ;
	
	// Load font
	this->loadFont(font) ;
}

GuiPage::~GuiPage()
{
	this->clear() ;
	this->guiBackSmgr->drop() ;
	this->guiMedSmgr->drop() ;
	this->guiFrontSmgr->drop() ;
	this->font->drop() ;
	this->cleanUpTextures() ;
}

void GuiPage::cleanUpTextures()
{
	for (int i = 0 ; i < this->textures.size() ; i++)
	{
		this->myDriver->removeTexture(this->textures[i]) ;
	}
	
	this->textures.clear() ;	
}

irr::scene::ICameraSceneNode* GuiPage::addCamera(irr::core::vector3df pos, irr::core::vector3df lookAt)
{
	this->guiFrontSmgr->addCameraSceneNode(0, pos, lookAt) ;
	this->guiMedSmgr->addCameraSceneNode(0, pos, lookAt) ;
	this->guiBackSmgr->addCameraSceneNode(0, pos, lookAt) ;
}

void GuiPage::clear()
{
	this->guiFrontSmgr->clear() ;
	this->guiMedSmgr->clear() ;
	this->guiBackSmgr->clear() ;
} 

void GuiPage::render()
{
	this->guiBackSmgr->drawAll() ;
	this->myDriver->clearZBuffer() ;
	this->guiMedSmgr->drawAll() ;
	this->myDriver->clearZBuffer() ;
	this->guiFrontSmgr->drawAll() ;
}

irr::scene::ISceneNode* GuiPage::addBackground(const char* name)
{
	// Get texture
	irr::video::ITexture* texture = this->myDriver->getTexture(this->myRessources->getFile(name)) ;

	// Add background
	irr::scene::ISceneNode* background = this->addImage(this->guiBackSmgr, texture, 0, 0) ;
	if (background)
	{
		background->setPosition(irr::core::vector3df(500, 0, 0)) ;
	}

	// Return the node
	return background ;
}

irr::scene::ISceneNode* GuiPage::addButton(const char* name, const char* text)
{
	// Where we want the button to be drawed
	irr::core::position2d<irr::s32> origin 	= this->myRessources->getPosition(name) ;
	irr::video::ITexture* 			texture = this->myDriver->getTexture(this->myRessources->getFile(name)) ;

	// In first get the texture
	irr::scene::ISceneNode* 		button	= this->addImage(this->guiMedSmgr, texture, origin.X, origin.Y) ; 

	// Then, add text centered
	if (texture)
	{
		irr::scene::ISceneNode* 		txt 	= this->addText(texture->getSize(), this->guiFrontSmgr, this->myRessources->getText(text).c_str(), this->myRessources->getColor(name)) ;
		txt->setPosition(irr::core::vector3df(330, origin.X, origin.Y)) ;
	}

	// Return the node
	return button ;
}

irr::scene::ISceneNode* GuiPage::addSimpleImage(const char* name, bool front)
{
	// Where we want the button to be drawed
	irr::core::position2d<irr::s32> origin 	= this->myRessources->getPosition(name) ;
	irr::video::ITexture* 			texture = this->myDriver->getTexture(this->myRessources->getFile(name)) ;

	// Add the image
	irr::scene::ISceneNode* img = this->addImage(this->getSceneManager(front), texture, origin.X, origin.Y) ;	
	
	// Return the node
	return img ;
}

irr::scene::ISceneNode* GuiPage::addSimpleText(irr::core::dimension2d<irr::s32> square, const wchar_t* text, irr::video::SColor color, int x, int y, bool front)
{
	// Create the node
	irr::scene::ISceneNode* txt = this->addText(square, this->getSceneManager(front), text, color) ;
	txt->setPosition(irr::core::vector3df(330, x, y)) ;

	// Return the node
	return txt ;
}

irr::scene::ISceneNode* GuiPage::addImage(irr::scene::ISceneManager* smgr, irr::video::ITexture* texture, int x, int y) 
{
	if (!texture)
	{
		return 0 ;	
	}
	
	// Add the image
	irr::scene::ISceneNode* img	= smgr->addCubeSceneNode(1, 0, -1, irr::core::vector3df(330, x, y), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, texture->getSize().Height, texture->getSize().Width)) ;

	// Set Params
	img->setMaterialTexture(0, texture) ;
	img->getMaterial(0).getTextureMatrix(0).setRotationDegrees(irr::core::vector3d<irr::f32>(0, 180, 0)) ; // Rotate
	img->setMaterialFlag(irr::video::EMF_LIGHTING, false) ;
	img->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL) ;
	
	// Return node	
	return img ;
}

irr::scene::ISceneManager* GuiPage::getSceneManager(bool front)
{
	return (front ? this->guiFrontSmgr : this->guiBackSmgr) ;	
}

std::deque<irr::core::stringw> GuiPage::getTextLines(irr::core::stringw text)
{
	// To store lines
	std::deque<irr::core::stringw> 	textLines ;
	irr::core::stringw 				line ;
	
	// Split lines
	while(text.size() != 0)
	{
		int pos = text.findFirst('\n') ; 				// Get the first return (to split)
		if (pos == -1)									// Check if return was founded
		{
			pos = text.size() ;
		}

		line = text.subString(0, pos) ; 				// Get the word
		if (line.size() == 0)							// If word if empty add space (useful for two return)
		{
			line = " " ;
		}
				
		text = text.subString(pos + 1, text.size()) ; 	// Remove the word from the text (don't take return)
		textLines.push_back(line) ; 					// Store the line
	}

	// Return the lines
	return textLines ;	
}


irr::scene::ISceneNode* GuiPage::addText(irr::core::dimension2d<irr::s32> square, irr::scene::ISceneManager* smgr, const wchar_t* text, irr::video::SColor color)
{	
	// Convert text to a stringw and create a deque for storing lines
	std::deque<irr::core::stringw> 	textBreakedLines ;	
	std::deque<irr::core::stringw> 	textLines ;	
	
	// Look if we should break lines of this text
	textBreakedLines = this->getTextLines(irr::core::stringw(text)) ;
	
/*	// For all real lines in the text, fit them into the square
	for (std::deque<irr::core::stringw>::iterator it = textBreakedLines.begin() ; it != textBreakedLines.end() ; ++it)
	{	
		irr::core::stringw 	lineToParse = (*it) ; 	// The line to parse
		irr::core::stringw 	line ;					// The line parsed
		irr::core::stringw 	word ;					// Word to add

		// While there is words in text
		while(lineToParse.size() != 0)
		{
			int pos = lineToParse.findFirst(' ') ; // Get the first text space (to split)
			if (pos == -1)
			{
				pos = lineToParse.size() ;
			}
			
			word 		= lineToParse.subString(0, pos) ; 						// Get the word
			lineToParse = lineToParse.subString(pos + 1, lineToParse.size()) ; 	// Remove the word from the text
	
			// Get the current width of the strings
			irr::core::dimension2d<irr::s32> dimWord = this->font->getDimension(word.c_str()) ;
			irr::core::dimension2d<irr::s32> dimLine = this->font->getDimension(line.c_str()) ;
	
			if ((dimWord.Width + dimLine.Width) > square.Width - H_MARGIN) // If the word can be in the destination rect
			{
				line = line.subString(0, line.size() - 1) ; // Remove the last space
				textLines.push_back(line) ; 				// Store the line
				line = word ; 								// New line
			}
			else
			{
				line += word ; // Store the word in the line
			}
			
			// Special case if we've just finished the text -> store
			if (lineToParse.size() == 0) 
			{
				textLines.push_back(line) ; // Store the line
			}
			else
			{
				line += " " ; // Add space
			}
		}
	}*/

	irr::video::ITexture* t = this->font->makeTexEn(/*textLines*/textBreakedLines, square, color) ;
	
	irr::core::dimension2d<irr::s32> tDim = t->getOriginalSize() ;
	irr::core::dimension2d<irr::f32> cDim = irr::core::dimension2d<irr::f32>(0, 0) ;

	if (tDim.Width < square.Width && tDim.Height < square.Height)
	{
		cDim.Width 	= tDim.Width ;
		cDim.Height = tDim.Height ;
	}
	else
	{
		float reducePercentage = (float)square.Height / (float)tDim.Height ;

		cDim.Width 	= tDim.Width * reducePercentage * 0.95 ;
		cDim.Height = tDim.Height * reducePercentage * 0.95 ;
		
		if (cDim.Width > square.Width)
		{
			float reducePercentage = (float)square.Width / (float)cDim.Width ;

			cDim.Width 	*= reducePercentage * 0.95 ;
			cDim.Height *= reducePercentage * 0.95 ;	
		}
	}

	irr::scene::IBillboardSceneNode* node = smgr->addBillboardSceneNode(0, cDim) ;
	node->setMaterialTexture(0, t) ;
				
// DEBUG TEST
//	irr::scene::IBillboardSceneNode* node = smgr->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(square.Width, square.Height)) ;
//	node->setMaterialTexture(0, 0) ;				
	
	node->setMaterialFlag(irr::video::EMF_LIGHTING, false) ;
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL) ;

	this->textures.push_back(t) ;	// Register texture
	
	return node ;					// Return what we've created
}

void GuiPage::loadFont(const char* font)
{
	this->font = new CGUIFreetypeFont(this->myDriver, true) ;	
	this->font->attach(new CGUITTFace(this->myRessources->getFile(font)), 18) ;	
}
