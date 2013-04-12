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

#ifndef _SONGMANAGER_H_
#define _SONGMANAGER_H_

#include "irrlicht.h"
#include "irrklang.h"

/* SONG FILES */
#define SONG_FILE 				"/song.ogg"
#define GUITAR_FILE 			"/guitar.ogg"
#define RHYTHM_FILE				"/rhythm.ogg"
#define PREVIEW_FILE			"/preview.ogg"

/* DEFAULT VALUES */
#define DEFAULT_PLAYBACK_SPEED 	1.0f // Normal Speed, 2 = 2* speed, 0.5 = half...

class SongManager
{
	public :
		SongManager(irrklang::ISoundEngine* soundEngine) ;

		void 						setDirectory(irr::core::stringc directory, bool playNow = false /* Useful for songslection preview */) ;
		void 						playSound(irr::core::stringc file) ;
		void						setPlaybackSpeed(float speed) ;
		void						muteGuitar(bool mute) ;
		void 						play(int msPos = 0) ;
		void						releaseRessources() ;
		bool						hasFinished() ;	
		int 						getTimeLeft() ;
		bool						isPlaying() ;
		void 						resume() ;
		void 						pause() ;
	
	private :
		irrklang::ISoundSource* 	loadFile(char* file) ;

		irrklang::ISoundEngine*		mySoundEngine ;
		irr::core::stringc			directory ;
		irrklang::ISound* 			guitar ;
		irrklang::ISound* 			rhythm ;
		irrklang::ISound* 			song ;
		float 						playbackSpeed ;
		bool 						playing ; // If playing yet true else false
};

#endif
