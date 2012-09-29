/*
 * Stage.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "Stage.hpp"

namespace blitz {
	namespace view {
		Stage::Stage()	
		{
			this->_currentLevel = NULL;
			this->_texMgr = NULL;
		}

		Stage::~Stage()
		{
			for(std::map<std::string, std::vector<view::Level*>>::iterator ito = this->_levels.begin(); ito != this->_levels.end(); ito++)
				for(std::vector<view::Level*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					delete *it;
		}

		void Stage::setTextureManager(TextureManager* texMgr)
		{
			this->_texMgr = texMgr;
		}

		void Stage::addLevel(const std::string& key, view::Level* level)
		{
			level->setTextureManager(this->_texMgr);
			this->_levels[key].push_back(level);
		}

		view::Level* Stage::removeLevel(const std::string& key, const int& index)
		{
			view::Level* _t = this->_levels[key][index];
			this->_levels[key].erase(this->_levels[key].begin() + index);
			return _t;
		}

		Level* Stage::setLevel(const std::string& key, const int& index)
		{
			return this->_currentLevel = this->_levels[key][index];
		}

		Level* Stage::setLevel(const std::string& key, const Level* level)
		{
			std::vector<Level*> l = this->_levels[key];			
			std::vector<Level*>::iterator it = std::find(l.begin(), l.end(), level);
			if(it != l.end())
				return this->_currentLevel = *it;
			else
				return NULL;
		}
	}
}