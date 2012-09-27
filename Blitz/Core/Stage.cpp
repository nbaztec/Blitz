/*
 * Stage.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "Stage.hpp"

namespace blitz {

	Stage::Stage()	
	{
		this->_hitPlayer = 0;
		this->_lastHitDuration = 0.0f;
	}

	Stage::~Stage()
	{
		for(std::map<std::string, std::vector<unit::Object*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
			for(std::vector<unit::Object*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
				delete *it;
	}

	void Stage::setTextureManager(TextureManager* texMgr)
	{
		this->_texMgr = texMgr;
	}

	inline float Stage::frand(float min, float max)
	{
		return min + float(rand())/(float(RAND_MAX)/(max-min));
	}

	void Stage::tick(const float &interpolate)
	{
		unit::Object *_t;
		for(std::map<std::string, std::vector<unit::Object*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
		{
			for(std::vector<unit::Object*>::iterator it = ito->second.begin(); it != ito->second.end();)
			{
				unit::Enemy* e = dynamic_cast<unit::Enemy*>(*it);
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
		for(std::vector<unit::Object*>::iterator itb = this->_objects["player_fire"].begin(); itb != this->_objects["player_fire"].end(); itb++)
		{
			for(std::vector<unit::Object*>::iterator ite = this->_objects["enemy"].begin(); ite != this->_objects["enemy"].end(); ite++)
			{
				unit::Enemy* e = dynamic_cast<unit::Enemy*>(*ite);
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

	void Stage::draw(void)
	{
		for(std::map<std::string, std::vector<unit::Object*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
		{
			glBindTexture(GL_TEXTURE_2D, this->_texMgr->operator[](ito->first.c_str()).first());
			if(ito->first == "enemy")
			{
				for(std::vector<unit::Object*>::reverse_iterator it = ito->second.rbegin(); it != ito->second.rend(); it++)
					(*it)->draw();		
			}
			else
			{
				for(std::vector<unit::Object*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
					(*it)->draw();		
			}
		}		
	}

	void Stage::spawnEnemy(const geometry::Triad &start, Model* model)
	{
		this->_objects["enemy"].push_back(new unit::SkeletonEnemy(start, model));
	}

	void Stage::playerFire(const geometry::Triad &start)
	{
		this->_objects["player_fire"].push_back(new unit::PlasmaBullet(start));
	}

	long Stage::getPlayerHits() const
	{
		return this->_hitPlayer;
	}
	
	long Stage::decPlayerHits()
	{
		return this->_hitPlayer > 0? --this->_hitPlayer: 0;
	}
	
	void Stage::resetPlayerHits()
	{
		this->_hitPlayer = 0;
	}

	bool Stage::persistHitDraw(float delta)
	{
		this->_lastHitDuration += delta;
		std::cout << "ALLOW: " << this->_lastHitDuration << " < " << 2.0f <<std::endl;
		if(this->_lastHitDuration < 1.5f)		
			return true;
		return false;
	}

	void Stage::hitDrawReset()
	{
		this->_lastHitDuration = 0.0f;
	}
}