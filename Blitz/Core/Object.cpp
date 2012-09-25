/*
 * Object.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "Object.hpp"
#include "State.hpp"
#include <iostream>

namespace blitz {
	namespace unit {
		Object::Object()
		{
			this->_state = new state::State();
		}

		Object::~Object()
		{
			delete this->_state;			
			for(std::vector<state::Animation*>::iterator it = this->_animation.begin(); it != this->_animation.end(); it++)
				delete *it;
		}


		/*
		 * PUBLIC METHODS
		 */

		void Object::addAnimation(state::Animation *anim)
		{	
			this->_animation.push_back(anim);	
		}

		state::Animation* Object::removeAnimation(const int &index)
		{
			state::Animation* _t = this->_animation[index];
			this->_animation.erase(this->_animation.begin() + index);
			return _t;
		}

		void Object::animateAll(float delta)
		{
			for(std::vector<state::Animation*>::iterator it = this->_animation.begin(); it != this->_animation.end(); )
			{
				if((*it)->animate(delta))
					it++;
				else
				{
					state::Animation* _t = *it;
					it = this->_animation.erase(it);
					delete _t;
				}
			}
		}

		state::State* Object::getState() const
		{
			return this->_state;
		}

		void Object::updateState(float delta)
		{			
			this->_state->duration += delta;
			this->_state->current += this->_state->velocity * delta;
			this->_state->angle += this->_state->rotation.magnitude * delta;
			this->animateAll(delta);
		}

		bool Object::isComplete(void) const
		{
			return false;
		}
	}
}
