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

#include "Jukebox.h"

Jukebox::Jukebox(irr::IrrlichtDevice* irrDevice, int delay, irr::core::stringc songsDirectory)
{
	// Get the original working directory
	irr::core::stringc originalDir 	= irrDevice->getGUIEnvironment()->getFileSystem()->getWorkingDirectory() ;
	
	// Change the directory to the one containing the songs
	irrDevice->getGUIEnvironment()->getFileSystem()->changeWorkingDirectoryTo(songsDirectory.c_str()) ;

    // Get the directory list
	irr::io::IFileList* songsList	= irrDevice->getFileSystem()->createFileList() ;
	
	// Restore original directory
	irrDevice->getGUIEnvironment()->getFileSystem()->changeWorkingDirectoryTo(originalDir.c_str()) ;

	// Create the map and a temp sequence ptr 
	this->songsMap 	= new std::map<irr::core::stringc, Sequence*>() ; 
	Sequence* seq 	= 0 ;
	
	for (int i = 0 ; i < songsList->getFileCount() ; i++) // Get's all the songs
	{
		if (strcmp(songsList->getFileName(i), "..") && strcmp(songsList->getFileName(i), ".") && songsList->isDirectory(i))
		{
			if (irrDevice->getFileSystem()->existFile(songsDirectory + songsList->getFileName(i) + MIDI_FILE))
			{
				// Create the sequence for the selected subdir
				Sequence* seq = new Sequence(songsDirectory + songsList->getFileName(i), delay) ;
				(*this->songsMap)[seq->getSeqInfos()->getSeqArtist()+ " - " + seq->getSeqInfos()->getSeqName()] = seq ;
			}
		}
	}
	
	// Clean up
	songsList->drop() ;
}

Jukebox::~Jukebox()
{
	delete this->songsMap ; // Delete the map
}


std::map<irr::core::stringc, Sequence*>* Jukebox::getSequences(irr::core::stringc filter)
{
	std::map<irr::core::stringc, Sequence*>* returnMap = new std::map<irr::core::stringc, Sequence*>() ;
	
	for (std::map<irr::core::stringc, Sequence*>::iterator it = this->songsMap->begin() ; it != this->songsMap->end() ; ++it)
	{
		if (filter.size() != 0) // Something to filter
		{
			irr::core::stringc name = it->first ;
			name.make_upper() ;
			
			if (filter.size() != 0 && name.find(filter.c_str()) != -1) // We've found
			{
				(*returnMap)[it->first] = it->second ; // Store
			}
		}
		else
		{
			(*returnMap)[it->first] = it->second ; // Store
		}
	}
	
	if (returnMap->size() == 0) // Nothing match
	{
		for (std::map<irr::core::stringc, Sequence*>::iterator it = this->songsMap->begin() ; it != this->songsMap->end() ; ++it)
		{
			(*returnMap)[it->first] = it->second ; // Store
		}		
	}
	
	return returnMap ; // Return it
}
