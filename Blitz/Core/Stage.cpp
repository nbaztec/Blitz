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

		for(std::vector<unit::Object*>::iterator itb = this->_objects["player_fire"].begin(); itb != this->_objects["player_fire"].end(); itb++)
		{
			for(std::vector<unit::Object*>::iterator ite = this->_objects["enemy"].begin(); ite != this->_objects["enemy"].end(); ite++)
				if((*itb)->collision(*(*ite)))
					std::cout << "Collided" << std::endl;			
		}
		/*
		for(std::map<std::string, std::vector<Object*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
		{
			for(std::vector<Object*>::iterator it = ito->second.begin(); it != ito->second.end();)
			{
				if((*it)->collision(*(this->_objects["enemy"][0])))
					std::cout << "Collided" << std::endl;
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
		}*/
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

	void Stage::spawnEnemy(const geometry::Triad &start)
	{
		this->_objects["enemy"].push_back(new unit::Enemy(start));
	}

	void Stage::playerFire(const geometry::Triad &start)
	{
		this->_objects["player_fire"].push_back(new unit::PlasmaBullet(start));
	}

}