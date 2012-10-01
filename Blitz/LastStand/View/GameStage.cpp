/*
 * GameStage.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "GameStage.hpp"

namespace game {
	namespace view {
		GameStage::GameStage()	
		{
			
		}

		GameStage::~GameStage()
		{			
		}			

		void GameStage::tick(const float &delta)
		{
			this->_currentLevel->tick(delta);
			this->_mdlMgr->updateModels(delta);			
		}

		void GameStage::draw(void)
		{
			this->_currentLevel->draw();
		}
	}
}