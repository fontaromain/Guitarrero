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

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "include.h"
#include "Irrlicht.h"
#include "Ressources.h"
#include <deque>

/* FOR DRAWINGS */
#define SCENE_ID 1

/* FILE TO LOAD */
#define SCENE_FILE 			"scene.irr"

/* FOR PARSING SCENE FILE */
#define CAMERAS_ID_START	0
#define CAMERAS_ID_END		9
#define LIGHTS_ID_START		10
#define LIGHTS_ID_END		29
#define CROWD_ID_START		30
#define CROWD_ID_END		59
#define GROUP_ID_START		60
#define GROUP_ID_END		64


class SceneManager
{
	public :
		SceneManager(irr::scene::ISceneManager* smgr, Ressources* myRessources, bool use3D) ;
		~SceneManager() ;
		
		void setLight() ;
		void render() ;
		void update(int time) ;
		
	private :
		void create3D() ;		
		void create2D() ;		
		void initCameras() ;
		void initLights() ;
		void initCrowd() ;
		void initGroup() ;

		std::deque<irr::scene::ICameraSceneNode*>	cameras ;
		std::deque<irr::scene::ILightSceneNode*>	lights ;
		std::deque<irr::scene::IMeshSceneNode*> 	group ;
		std::deque<irr::scene::IMeshSceneNode*> 	crowd ;
		irr::scene::ISceneManager* 					smgr ;			// Scene manager
		irr::video::IVideoDriver* 					driver ;		// 3D Driver
		Ressources*									myRessources ;	// Ressource bundle
		int 										lastTime ;		// For calculating the lightning velocity
		int											lastTimeCam ;	// The lastTime when we changed cam
		
		int lastTimeCrowd ;
		int t ;
};

#endif
