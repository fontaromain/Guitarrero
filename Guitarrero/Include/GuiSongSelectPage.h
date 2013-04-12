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

#ifndef _GUISONGSELECTPAGE_H_
#define _GUISONGSELECTPAGE_H_

#include "include.h"
#include "GuiPage.h"
#include "Jukebox.h"
#include "GameMode.h"

/* PARAMS */
#define MAX_LIST_SCORES_COUNT 	5				// How many scores drawed per level
#define MAX_CHAR_PER_NAME		10				// How many char drawed per player name 
#define STITLE_X				100				// Position of selected seq title
#define STITLE_Y				0				// Position of selected seq title
#define SSCORES_X				STITLE_X - 22 	// Position of selected seq scores


class GuiSongSelectPage : public GuiPage
{
	public :
		GuiSongSelectPage(irr::scene::ISceneManager* baseSmgr, irr::video::IVideoDriver* driver, Ressources* ressources, Jukebox* jukebox, GameMode* myGameMode) ;

		void					performAction(ACTION_TYPE at, int val) ;
		bool					shouldPreview() ;
		Sequence*				getSequence() ;	

	private :
		void 					drawScores(irr::core::stringw title, irr::core::array<Player*> scores, int x, int y, irr::video::SColor color) ;		
		void					drawTitle(irr::core::stringc name, Sequence* seq, irr::video::SColor color, int x, int y) ;
		bool					updateIterator(std::map<irr::core::stringc, Sequence*>::iterator &iter, bool direction) ;
		void 					drawSequence(irr::core::stringc name, Sequence* seq) ;
		void					updateSelection(bool direction) ;
		void 					inputFilter(char val) ;
		void 					drawSongList() ;
		void 					destroyGui() ;
		void 					createGui() ;
		void 					draw() ;

		std::map<irr::core::stringc, Sequence*>::iterator 	it ;
		std::map<irr::core::stringc, Sequence*>* 			songsSeq ;
		irr::core::stringw									filter ;
		Jukebox*											myJukebox ;
		bool												preview ; // False if we reach the border of selection (prevent restarting over and over preview) 
};

#endif
