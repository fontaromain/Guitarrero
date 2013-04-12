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

#ifndef _GRIDMANAGER_H_
#define _GRIDMANAGER_H_

#include "include.h"
#include "Irrlicht.h"
#include "NotesLine.h"
#include "Ressources.h"
#include "ScoreCounter.h"
#include "InputReceiver.h"
#include "SongManager.h"
#include "SceneManager.h"
#include <deque>

#define UNDERLINES_LENGTH 	8 	// The underlines texture length
#define SPRITE_INDEX 		100 // For getting texture
#define NOTE_END_WIDTH		10 	// Note end width


class GridManager
{
	friend class ScoreCounter ;
	
	public :
		GridManager(irr::scene::ISceneManager* smgr, Ressources* myRessources, Statistics* stats, std::deque<NotesLine*>* lines, int* keyMap, int pos, int scale, int rot, int camFarVal, int xStats, int yStats, bool sustainMode, bool player = false) ;
		~GridManager() ;

		ScoreCounter* 						getScoreCounter() ;
		void 								render() ;
		void 								nextLineToDraw() ;
		void 								nextLineToPlay() ;
		bool 								hasMoreLineToDraw() ;
		bool 								hasMoreLineToPlay() ;
		void 								drawNewLine(int timeElapsed) ;
		void								moveKey(int key, bool pushed) ;
		bool 								checkLine(InputReceiver* myReceiver, SongManager* mySongManager, SceneManager* mySceneManager, int time, int lastTime, int player) ;

	private :
		NotesLine* 							getLineToDraw() ;
		NotesLine* 							getLineToPlay() ;
		void 								setCurrentLineEffect(bool successPlaying, int timeDiff = 0) ;
		void 								setProperties(irr::scene::ISceneNode* node) ;
		void 								drawSLine(int i) ;
		void 								drawULine(int i) ;
		void 								drawKey(int i) ;
		void 								drawGrid() ;

		std::deque<NotesLine*>::iterator	posInFile ;				// Iterator pointing to the next line to be PLAYED	
		std::deque<NotesLine*>::iterator	posDraw ;				// Iterator pointing to the next line to be DRAWED
		irr::scene::IBillboardSceneNode*	nodesSprites[NB_NOTES] ;// Sprites of this grid
		irr::scene::ICameraSceneNode* 		cam ;					// The camera that see the grid
		irr::scene::ISceneManager* 			smgrFront ;				// Scene manager
		irr::scene::ISceneManager* 			smgrMed ;				// Scene manager
		irr::scene::ISceneManager* 			smgrBack ;				// Scene manager
		irr::scene::ISceneManager*			guiTextSmgr ;			// Scene manager for gui texts only 
		irr::scene::ISceneManager* 			guiSmgr ;				// Scene manager for gui elements (scores, messages)
		irr::video::IVideoDriver* 			driver ;				// 3D Driver
		std::deque<NotesLine*>* 			notesLines ;			// Deque which contains all the lines of the song		
		ScoreCounter*						myScoreCounter ;		// The score counter
		Ressources*							myRessources ;			// Ressource bundle
		const float							animOffset ;			// When using rotation we should adapt animators
		const int 							camFarVal ;				// Camera far value
		const int 							rotation ;				// Grid rotation (in degrees)
		const int 							distEcart ;				// Scale of the grid (ecart between two notes)
		const int 							yOffset ;				// Grid YOffset
		int* 								keyMap ;				// User keyMap
		bool 								player ;				// Is this player 1 or 2 ?
		bool								sustainMode ;			// Whether if frets are released early on a sustain note we cut the audio or not
		int 								spriteAnim ;			// End line sprite
};

#endif
