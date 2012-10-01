/*
 * Level.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "Level.hpp"

namespace blitz {
	namespace view {		

		Randomizer Level::RAND;

		Level::Level()
		{
			this->_texMgr = NULL;
		}

		Level::~Level()
		{
			for(std::map<std::string, std::vector<unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
				for(std::vector<unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					delete *it;
		}

		void Level::setTextureManager(TextureManager* texMgr)
		{
			this->_texMgr = texMgr;
		}	

		void Level::setModelManager(ModelManager* mdlMgr)
		{
			this->_mdlMgr = mdlMgr;
		}

		void Level::setCamera(Camera* camera)
		{
			this->_camera = camera;
		}		
	}
}