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

#include "Ressources.h" 

Ressources::Ressources(irr::core::stringc skinDir, irr::core::stringc languageFile)
{
	this->parseLangFile(languageFile.c_str()) ; // Parse file to get texts
	this->parseSkinPath(skinDir.c_str()) ; 		// Parse file to get skin
}

void Ressources::parseLangFile(const char* langFile)
{
	// Clear actual map
	this->texts.clear() ;
	
	// Create the parser
  	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(langFile) ;

	// While there is data
	while(xml && xml->read())
	{
		// Get the node type
    	switch(xml->getNodeType())
    	{
			// If it's an element
			case irr::io::EXN_ELEMENT :
			{
				if (xml->getAttributeCount() == 1)
				{
					this->addText(xml->getNodeName(), xml->getAttributeValue("value")) ;
				}

				break ;
			}
		}
	}
	delete xml ; // Delete parser
}

void Ressources::parseSkinPath(const char* skinPath)
{
	// Clear actual maps
	this->positions.clear() ;
	this->files.clear() ;
	this->colors.clear() ;

	// Retrieve file path
	irr::core::stringc file 	= irr::core::stringc(skinPath) + SKIN_FILE ;

	// Create the parser
  	irr::io::IrrXMLReader* xml 	= irr::io::createIrrXMLReader(file.c_str()) ;

	// While there is data
	while(xml && xml->read())
	{
		// Get the node type
    	switch(xml->getNodeType())
    	{
			// If it's an element
			case irr::io::EXN_ELEMENT :
			{
				// Some variables to parse
				irr::core::stringc 	name 				= xml->getNodeName() ;
				int 				attrCount 			= xml->getAttributeCount() ;
				bool 				shouldAddColor 		= false ;
				bool 				shouldAddPosition	= false ;
			
				// Default parameters
				irr::video::SColor				color(0, 0, 0, 0) ;
				irr::core::position2d<irr::s32> position(0, 0) ;
				
				for (int i = 0 ; i < attrCount ; i++)
				{
					// Get the name
					irr::core::stringc attrName = xml->getAttributeName(i) ;
					
					if (attrName == "file") // A file
					{
						this->files[name] = irr::core::stringw(skinPath) + xml->getAttributeValue(attrName.c_str()) ;
					}
					else if (attrName == "x") // Etc.
					{
						position.X = xml->getAttributeValueAsInt(attrName.c_str()) ;
						shouldAddPosition = true ;
					}
					else if (attrName == "y")
					{
						position.Y = xml->getAttributeValueAsInt(attrName.c_str()) ;
						shouldAddPosition = true ;
					}
					else if (attrName == "a")
					{
						color.setAlpha(xml->getAttributeValueAsInt(attrName.c_str())) ;
						shouldAddColor = true ;
					}
					else if (attrName == "r") 
					{
						color.setRed(xml->getAttributeValueAsInt(attrName.c_str())) ;
						shouldAddColor = true ;
					}
					else if (attrName == "g") 
					{
						color.setGreen(xml->getAttributeValueAsInt(attrName.c_str())) ;
						shouldAddColor = true ;
					}
					else if (attrName == "b") 
					{
						color.setBlue(xml->getAttributeValueAsInt(attrName.c_str())) ;
						shouldAddColor = true ;
					}
					else
					{
						std::cout << "Attribute ignored : " << name.c_str() << "\n" ;	
					}
				}
				
				if (shouldAddPosition)
				{
					this->positions[name] = position ;
				}
				if (shouldAddColor)
				{
					this->colors[name] = color ;
				}
				
				break ;
			}
		}
	}
	
	delete xml ; // Delete parser
}

irr::core::stringw Ressources::getText(const char* index)
{
	// Iterator pointing the desired value if founded
	std::map<irr::core::stringc, irr::core::stringw>::iterator iter = this->texts.find(index) ;
	
    if (iter != this->texts.end()) // Value founded
    {
		return (*iter).second ; // Return it      
    }
    return index ;
}

irr::core::position2d<irr::s32> Ressources::getPosition(const char* index)
{	
	// Iterator pointing the desired value if founded
	std::map<irr::core::stringc, irr::core::position2d<irr::s32> >::iterator iter = this->positions.find(index) ;
	
    if (iter != this->positions.end()) // Value founded
    {
		return (*iter).second ; // Return it      
    }
    
	return irr::core::position2d<irr::s32>(0, 0) ;
}

irr::core::stringw Ressources::getFile(const char* index)
{	
	// Iterator pointing the desired value if founded
	std::map<irr::core::stringc, irr::core::stringw>::iterator iter = this->files.find(index) ;
	
    if (iter != this->files.end()) // Value founded
    {
		return (*iter).second ; // Return it      
    }
    
    return index ;
}

irr::video::SColor Ressources::getColor(const char* index)
{	
	// Iterator pointing the desired value if founded
	std::map<irr::core::stringc, irr::video::SColor>::iterator iter = this->colors.find(index) ;
	
    if (iter != this->colors.end()) // Value founded
    {
		return (*iter).second ; // Return it      
    }
    
    return irr::video::SColor(255, 0, 0, 0) ; //Return black by default
}

void Ressources::preloadAllTextures(irr::video::IVideoDriver* videoDriver)
{
	// For all the map, load the data
	for (std::map<irr::core::stringc, irr::core::stringw>::iterator iter = this->files.begin() ; iter != this->files.end() ; ++iter)
	{
		if(strcmp(iter->first.c_str(), MENU_BUTTONS_SOUND) 
		&& strcmp(iter->first.c_str(), PLAYING_ERROR_SOUND)
		&& strcmp(iter->first.c_str(), MENU_SELECT_SOUND)
		&& strcmp(iter->first.c_str(), MAIN_FONT)
		&& strcmp(iter->first.c_str(), CREDITS_FONT)
		&& strcmp(iter->first.c_str(), SONG_FONT)
		&& strcmp(iter->first.c_str(), MODE_FONT)
		&& strcmp(iter->first.c_str(), PAUSE_FONT)
		&& strcmp(iter->first.c_str(), STATS_FONT)
		&& strcmp(iter->first.c_str(), SMODE_FONT)
		&& strcmp(iter->first.c_str(), NOLEVELS_FONT)
		&& strcmp(iter->first.c_str(), ENTRY_3D_SOUND))
		{
			videoDriver->getTexture(iter->second) ;
		}
	}
}

void Ressources::addText(irr::core::stringc name, irr::core::stringw text)
{
	text.replace('é', 233) ;
	text.replace('è', 232) ;
	text.replace('ç', 231) ;
	text.replace('à', 224) ;
	text.replace('â', 226) ;
	text.replace('ô', 244) ;

	this->texts[name] = text ;
}
