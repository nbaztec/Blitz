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
			this->_currentPlayer = NULL;
		}

		Level::~Level()
		{
			for(std::map<std::string, std::vector<unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
				for(std::vector<unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					delete *it;

			for(std::vector<unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end();)
			{
				delete *itp;
				itp = this->_players.erase(itp);	
			}
		}

		void Level::setCurrentPlayer(const int& index)
		{
			this->_currentPlayer = this->_players[index];
		}

		void Level::setTextureManager(TextureManager* texMgr)
		{
			this->_texMgr = texMgr;
		}	

		void Level::setModelManager(ModelManager* mdlMgr)
		{
			this->_mdlMgr = mdlMgr;
		}

		void Level::setSoundManager(SoundManager* sndMgr)
		{
			this->_sndMgr = sndMgr;
		}

		void Level::setCamera(Camera* camera)
		{
			this->_camera = camera;
		}

		Camera* Level::getCamera()
		{
			return this->_camera;
		}

		void Level::addUnit(const char* key, unit::UnitObject* unit)
		{
			unit->setSoundManager(this->_sndMgr);
			this->_objects[key].push_back(unit);
		}

		void Level::addPlayer(unit::Player* player)
		{
			player->setSoundManager(this->_sndMgr);
			player->setLevel(this);
			this->_players.push_back(player);
			if(!this->_currentPlayer)
				this->_currentPlayer = player;
		}
	}
}