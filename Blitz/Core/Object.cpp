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
			this->_completed = false;
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

		bool Object::hasCompleted()
		{
			return this->_completed = true;
		}

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

		bool Object::animateAll(float delta)
		{
			bool terminal = false;
			for(std::vector<state::Animation*>::iterator it = this->_animation.begin(); it != this->_animation.end(); )
			{
				if((*it)->animate(delta))
					it++;
				else
				{					
					state::Animation* _t = *it;					
					it = this->_animation.erase(it);
					if(_t->isTerminal())
					terminal |= _t->isTerminal();					
					delete _t;
				}
			}
			return terminal;
		}

		state::State* Object::getState() const
		{
			return this->_state;
		}

		bool Object::updateState(float delta)
		{			
			this->_state->duration += delta;
			this->_state->current += this->_state->velocity * delta;
			this->_state->angle += this->_state->rotation.magnitude * delta;
			return this->animateAll(delta);
		}

		bool Object::isComplete(void) const
		{
			return false;
		}
	}
}
