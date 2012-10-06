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
			this->_camera = NULL;
		}

		Stage::~Stage()
		{
			delete this->_camera;
			for(std::map<std::string, std::vector<view::Level*>>::iterator ito = this->_levels.begin(); ito != this->_levels.end(); ito++)
				for(std::vector<view::Level*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					delete *it;
		}

		void Stage::setTextureManager(TextureManager* texMgr)
		{
			this->_texMgr = texMgr;
		}

		void Stage::setModelManager(ModelManager* mdlMgr)
		{
			this->_mdlMgr = mdlMgr;
		}

		void Stage::setSoundManager(SoundManager* sndMgr)
		{
			this->_sndMgr = sndMgr;
		}

		void Stage::setCamera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, bool fixed)
		{
			this->_camera = this->_camera = new Camera(current, screen, bounds, fixed);
		}

		Camera* Stage::getCamera() const
		{
			return this->_camera;
		}

		void Stage::addLevel(const std::string& key, view::Level* level)
		{
			level->setTextureManager(this->_texMgr);
			level->setModelManager(this->_mdlMgr);
			level->setSoundManager(this->_sndMgr);
			level->setCamera(this->_camera);
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

		Level* Stage::getCurrentLevel()
		{
			return this->_currentLevel;
		}

		void Stage::screenChanged(int width, int height)
		{
			this->_camera->setScreen(width, height);
		}

		void Stage::mousePressed(int button)
		{
			this->_currentLevel->mousePressed(button);
		}

		void Stage::mouseReleased(int button)
		{
			this->_currentLevel->mouseReleased(button);
		}

		void Stage::mouseMoved(int x, int y)
		{
			this->_camera->updateNormalized(x, y);
			this->_currentLevel->mouseMoved(x, y);
		}

		void Stage::mouseWheelMoved(int pos)
		{
			this->_currentLevel->mouseWheelMoved(pos);
		}

		void Stage::keyPressed(int key)
		{
			this->_currentLevel->keyPressed(key);
		}

		void Stage::keyReleased(int key)
		{
			this->_currentLevel->keyReleased(key);
		}

		void Stage::keyCharPressed(int character)
		{
			this->_currentLevel->keyCharPressed(character);
		}

		void Stage::keyCharReleased(int character)
		{
			this->_currentLevel->keyCharReleased(character);
		}
	}
}