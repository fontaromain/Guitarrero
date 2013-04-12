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

#include "SceneManager.h"

SceneManager::SceneManager(irr::scene::ISceneManager* smgr, Ressources* myRessources, bool use3D)
{
	// Init members
	this->smgr 			= smgr->createNewSceneManager() ;
	this->driver		= this->smgr->getVideoDriver() ;
	this->myRessources	= myRessources ;
	this->lastTime		= 0 ;
	this->lastTimeCam	= 0 ;
	this->lastTimeCrowd = 0 ;
	t = 0 ;
	
	// Create the scene
	if (use3D)
	{
		this->create3D() ;
	}
	else
	{
		this->create2D() ;	
	}
}

SceneManager::~SceneManager()
{
	this->smgr->drop() ;
}

void SceneManager::render()
{
	this->smgr->drawAll() ;
	this->driver->clearZBuffer() ;
}

void SceneManager::create2D()
{
	// Add background
	irr::scene::ISceneNode* scene = this->smgr->addCubeSceneNode(1, 0, SCENE_ID, irr::core::vector3df(200, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 290, 390)) ;
	scene->setMaterialTexture(0, this->driver->getTexture(this->myRessources->getFile(BACK_GAME))) ;
	scene->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	// Add a camera to see it
	this->smgr->addCameraSceneNode(	0, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0)) ;
}

void SceneManager::create3D()
{
	// Get the original working directory
	irr::core::stringc originalDir 	= this->smgr->getGUIEnvironment()->getFileSystem()->getWorkingDirectory() ;
	
	// Change the directory to the one containing the scene (for getting texture correctly
	this->smgr->getGUIEnvironment()->getFileSystem()->changeWorkingDirectoryTo(irr::core::stringc(SCENES_DIR).c_str()) ;

	irr::io::IFileList* scenesList = this->smgr->getGUIEnvironment()->getFileSystem()->createFileList() ;
	std::deque<irr::core::stringc> scenes ;

	for (int i = 0 ; i < scenesList->getFileCount() ; i++) // Get's all the songs
	{
		if (strcmp(scenesList->getFileName(i), "..") && strcmp(scenesList->getFileName(i), ".") && scenesList->isDirectory(i))
		{
			if (this->smgr->getGUIEnvironment()->getFileSystem()->existFile(irr::core::stringc(scenesList->getFileName(i)) + "/"SCENE_FILE))
			{
				scenes.push_back(irr::core::stringc(scenesList->getFileName(i))) ;
			}
		}
	}
	
	this->smgr->getGUIEnvironment()->getFileSystem()->changeWorkingDirectoryTo(scenes[rand() % scenes.size()].c_str()) ;
	this->smgr->loadScene(SCENE_FILE) ;

	// Rectore original directory
	this->smgr->getGUIEnvironment()->getFileSystem()->changeWorkingDirectoryTo(originalDir.c_str()) ;

	// Clean up
	scenesList->drop() ;

	// Init the whole scene
	this->initCameras() ;
	this->initLights() ;
	this->initCrowd() ;
	this->initGroup() ;
}

void SceneManager::initCameras()
{
	for (int i = CAMERAS_ID_START ; i < CAMERAS_ID_END ; i++)
	{
		irr::scene::ISceneNode* node = this->smgr->getSceneNodeFromId(i) ;
		
		if (node && node->getType() == irr::scene::ESNT_CAMERA)
		{
			this->cameras.push_back((irr::scene::ICameraSceneNode*)node) ;	
		}
	}
}

void SceneManager::initLights()
{
	for (int i = LIGHTS_ID_START ; i < LIGHTS_ID_END ; i++)
	{
		irr::scene::ISceneNode* node = this->smgr->getSceneNodeFromId(i) ;
		
		if (node && node->getType() == irr::scene::ESNT_LIGHT)
		{
			this->lights.push_back((irr::scene::ILightSceneNode*)node) ;	
		}
	}
}

void SceneManager::initCrowd()
{
	for (int i = CROWD_ID_START ; i < CROWD_ID_END ; i++)
	{
		irr::scene::ISceneNode* node = this->smgr->getSceneNodeFromId(i) ;
		
		if (node && node->getType() == irr::scene::ESNT_ANIMATED_MESH)
		{
			this->crowd.push_back((irr::scene::IMeshSceneNode*)node) ;	
		}
	}
}

void SceneManager::initGroup()
{
	for (int i = GROUP_ID_START ; i < GROUP_ID_END ; i++)
	{
		irr::scene::ISceneNode* node = this->smgr->getSceneNodeFromId(i) ;
		
		if (node && node->getType() == irr::scene::ESNT_ANIMATED_MESH)
		{
			this->group.push_back((irr::scene::IMeshSceneNode*)node) ;	
		}
	}
}

void SceneManager::setLight()
{
	int strength = 1000 ;
	
	// Manage the lights
	for (std::deque<irr::scene::ILightSceneNode*>::iterator it = this->lights.begin() ; it != this->lights.end() ; ++it)
	{
		(*it)->setRadius(strength) ;
	}
}

void SceneManager::update(int time)
{
	// Manage the lights
	if (time - lastTime)
	{
		for (std::deque<irr::scene::ILightSceneNode*>::iterator it = this->lights.begin() ; it != this->lights.end() ; ++it)
		{
			float radius = (*it)->getRadius() ;
			
			for (int i = 0 ; i < (time - lastTime) ; i++)
			{
				if (radius > 100)
				{
					(*it)->setRadius(radius - 10) ;
				}
			}
		}
	}
	
	// Manage the cameras
	if (time > (this->lastTimeCam + 10000))
	{		
		if (this->cameras.size() != 0)
		{
			//srand(time(NULL)) ;
			int val = rand() % this->cameras.size() ;
			this->smgr->setActiveCamera(this->cameras[val]) ;
		}
		
		this->lastTimeCam = time ;
	}
	
	// Manage the crowd
	if (time > (this->lastTimeCrowd + 15000))
	{
		if (this->crowd.size() == 1)
		{
			irr::scene::IAnimatedMeshSceneNode* nd ;
			nd = (irr::scene::IAnimatedMeshSceneNode*)this->crowd[0] ;
			
			switch(t)
			{
				case 0 :
					nd->setMD2Animation(irr::scene::EMAT_STAND) ;
					break ;
				case 1 :
					nd->setMD2Animation(irr::scene::EMAT_RUN) ;
					break ;
				case 2 :
					nd->setMD2Animation(irr::scene::EMAT_ATTACK) ;
					break ;
				case 3 :
					nd->setMD2Animation(irr::scene::EMAT_PAIN_A) ;
					break ;
				case 4 :
					nd->setMD2Animation(irr::scene::EMAT_PAIN_B) ;
					break ;
				case 5 :
					nd->setMD2Animation(irr::scene::EMAT_PAIN_C) ;
					break ;
				case 6 :
					nd->setMD2Animation(irr::scene::EMAT_JUMP) ;
					break ;
				case 7 :
					nd->setMD2Animation(irr::scene::EMAT_FLIP) ;
					break ;
				case 8 :
					nd->setMD2Animation(irr::scene::EMAT_SALUTE) ;
					break ;
				case 9 :
					nd->setMD2Animation(irr::scene::EMAT_FALLBACK) ;
					break ;
				case 10 :
					nd->setMD2Animation(irr::scene::EMAT_WAVE) ;
					break ;
				case 11 :
					nd->setMD2Animation(irr::scene::EMAT_POINT) ;
					break ;
				case 12 :
					nd->setMD2Animation(irr::scene::EMAT_BOOM) ;
					break ;
			}
			
			std::cout << t++ << "\n" ;
		}
		
		this->lastTimeCrowd = time ;
	}

	
	// Save last time
	this->lastTime = time ;
}
