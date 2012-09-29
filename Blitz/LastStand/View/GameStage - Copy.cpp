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
			this->_hitPlayer = 0;
			this->_lastHitDuration = 0.0f;
		}

		GameStage::~GameStage()
		{
			for(std::map<std::string, std::vector<blitz::unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
				for(std::vector<blitz::unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					delete *it;
		}

		void GameStage::setTextureManager(TextureManager* texMgr)
		{
			this->_texMgr = texMgr;
		}

		inline float GameStage::frand(float min, float max)
		{
			return min + float(rand())/(float(RAND_MAX)/(max-min));
		}

		void GameStage::tick(const float &interpolate)
		{
			blitz::unit::UnitObject *_t;
			for(std::map<std::string, std::vector<blitz::unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
			{
				for(std::vector<blitz::unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end();)
				{
					blitz::unit::Enemy* e = dynamic_cast<blitz::unit::Enemy*>(*it);
					if(e != NULL && e->hasHitPlayer())
					{
						e->hasCompleted();
						this->_hitPlayer++;
					}

					if((*it)->isComplete())
					{
						_t = *it;
						it = ito->second.erase(it);			
						delete _t;
					}
					else
					{
						(*it)->tick(interpolate);
						it++;
					}
				}
			}

			// Player-Plasma Hit
			for(std::vector<blitz::unit::UnitObject*>::iterator itb = this->_objects["player_fire"].begin(); itb != this->_objects["player_fire"].end(); itb++)
			{
				for(std::vector<blitz::unit::UnitObject*>::iterator ite = this->_objects["enemy"].begin(); ite != this->_objects["enemy"].end(); ite++)
				{
					blitz::unit::Enemy* e = dynamic_cast<blitz::unit::Enemy*>(*ite);
					if(e && (*itb)->collision(*(*ite)))
					{
						(*itb)->hasCompleted();
						(*ite)->hit(**itb);

						std::cout << "Collided" << std::endl;
						break;
					}
				}
			}		
		}

		void GameStage::draw(void)
		{
			for(std::map<std::string, std::vector<blitz::unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
			{
				glBindTexture(GL_TEXTURE_2D, this->_texMgr->operator[](ito->first.c_str()).first());
				if(ito->first == "enemy")
				{
					for(std::vector<blitz::unit::UnitObject*>::reverse_iterator it = ito->second.rbegin(); it != ito->second.rend(); it++)
						(*it)->draw();		
				}
				else
				{
					for(std::vector<blitz::unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
						(*it)->draw();		
				}
			}		
		}

		void GameStage::spawnEnemy(const blitz::geometry::Triad &start, Model* model)
		{
			this->_objects["enemy"].push_back(new blitz::unit::SkeletonEnemy(start, model));
		}

		void GameStage::playerFire(const blitz::geometry::Triad &start)
		{
			this->_objects["player_fire"].push_back(new blitz::unit::PlasmaBullet(start));
		}

		long GameStage::getPlayerHits() const
		{
			return this->_hitPlayer;
		}
	
		long GameStage::decPlayerHits()
		{
			return this->_hitPlayer > 0? --this->_hitPlayer: 0;
		}
	
		void GameStage::resetPlayerHits()
		{
			this->_hitPlayer = 0;
		}

		bool GameStage::persistHitDraw(float delta)
		{
			this->_lastHitDuration += delta;
			std::cout << "ALLOW: " << this->_lastHitDuration << " < " << 2.0f <<std::endl;
			if(this->_lastHitDuration < 1.5f)		
				return true;
			this->hitDrawReset();
			return false;
		}

		void GameStage::hitDrawReset()
		{
			this->_lastHitDuration = 0.0f;
		}
	}
}