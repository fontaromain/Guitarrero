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

#include "SongManager.h"

SongManager::SongManager(irrklang::ISoundEngine* soundEngine)
{
	// Init members
	this->mySoundEngine = soundEngine ;
	this->directory 	= "" ;
	this->playbackSpeed	= DEFAULT_PLAYBACK_SPEED ;
	this->guitar		= 0 ;
	this->song			= 0 ;
	this->rhythm		= 0 ;
	this->playing 		= false ;
}

void SongManager::setDirectory(irr::core::stringc directory, bool playNow)
{
	if (directory != this->directory) // Really need to update
	{
		this->directory = directory ;
		
		this->loadFile(GUITAR_FILE) ;
		this->loadFile(SONG_FILE) ;	
		this->loadFile(RHYTHM_FILE) ;
		
		if (playNow)
		{
			this->play() ;	
		}
	}
}

void SongManager::releaseRessources()
{
	// Drop current if they exists (no more needed)
	if (this->guitar) 	{this->guitar->drop() ;}
	if (this->song) 	{this->song->drop() ;}
	if (this->rhythm) 	{this->rhythm->drop() ;}
	
	this->guitar 	= 0 ;
	this->song 		= 0 ;
	this->rhythm 	= 0 ;
	this->playing 	= false ;
}

void SongManager::pause()
{
	// Set all sounds paused 
	// (we don't remove them because if resume we need getPlayPosition)
	this->mySoundEngine->setAllSoundsPaused(true) ;
	this->playing = false ;
}

void SongManager::resume()
{
	if (this->guitar)
	{
		this->play(this->guitar->getPlayPosition()) ;
	}
}

void SongManager::play(int msPos)
{
	// Remove all sounds
	this->mySoundEngine->removeAllSoundSources() ;

	// Drop current if they exists (no more needed)
	if (this->guitar) 	{this->guitar->drop() ;}
	if (this->song) 	{this->song->drop() ;}
	if (this->rhythm) 	{this->rhythm->drop() ;}

	// Add to soundEngine song files
	this->guitar 	= this->mySoundEngine->play2D(this->loadFile(GUITAR_FILE), 	false, true) ;
	this->song 		= this->mySoundEngine->play2D(this->loadFile(SONG_FILE), 	false, true) ;	
	this->rhythm 	= this->mySoundEngine->play2D(this->loadFile(RHYTHM_FILE), 	false, true) ;
	
	// Set good play position
	if(this->guitar) 	{this->guitar->setPlayPosition(msPos) ;}
	if(this->song)		{this->song->setPlayPosition(msPos) ;}
	if(this->rhythm)	{this->rhythm->setPlayPosition(msPos) ;}
	
	// Speed
	if (this->guitar) 	{this->guitar->setPlaybackSpeed(this->playbackSpeed) ;}
	if (this->song) 	{this->song->setPlaybackSpeed(this->playbackSpeed) ;}
	if (this->rhythm) 	{this->rhythm->setPlaybackSpeed(this->playbackSpeed) ;}
	
	// Now play
	this->mySoundEngine->setAllSoundsPaused(false) ;
	
	// Set that we're palying yet
	this->playing = true ;
}

int SongManager::getTimeLeft()
{
	if (this->guitar)
	{
		return this->guitar->getPlayLength() - this->guitar->getPlayPosition() ;
	}
	
	return 0 ;
}

irrklang::ISoundSource* SongManager::loadFile(char* file)
{
	return this->mySoundEngine->addSoundSourceFromFile(irr::core::stringc(this->directory + file).c_str(), irrklang::ESM_STREAMING, true) ;
}

void SongManager::setPlaybackSpeed(float speed)
{
	if (speed > 0)
	{
		this->playbackSpeed = speed ;	
	}
}

bool SongManager::hasFinished()
{
	if (this->guitar)
	{
		return this->guitar->isFinished() ;
	}
	
	return true ;
}

void SongManager::muteGuitar(bool mute)
{
	if (this->guitar)
	{
		this->guitar->setVolume(mute) ;
	}
}

void SongManager::playSound(irr::core::stringc file)
{
	this->mySoundEngine->play2D(file.c_str()) ;
}

bool SongManager::isPlaying()
{
	return this->playing ;	
}
