/*
 * UnitObject.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "UnitObject.hpp"
#include <iostream>

namespace blitz {
	namespace unit {
		UnitObject::UnitObject()
		{
			this->_state = new state::State();
			this->_completed = false;
		}

		UnitObject::~UnitObject()
		{
			delete this->_state;			
			for(std::vector<state::Animation*>::iterator it = this->_animation.begin(); it != this->_animation.end(); it++)
				delete *it;
		}


		/*
		 * PUBLIC METHODS
		 */

		bool UnitObject::markCompleted()
		{
			return this->_completed = true;
		}

		void UnitObject::addAnimation(state::Animation *anim)
		{	
			this->_animation.push_back(anim);	
		}

		state::Animation* UnitObject::removeAnimation(const int &index)
		{
			state::Animation* _t = this->_animation[index];
			this->_animation.erase(this->_animation.begin() + index);
			return _t;
		}

		bool UnitObject::animateAll(const float& delta)
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

		state::State* UnitObject::getState() const
		{
			return this->_state;
		}

		bool UnitObject::updateState(const float& delta)
		{			
			this->_state->duration += delta;
			this->_state->current += this->_state->velocity * delta;
			this->_state->angle += this->_state->rotation.magnitude * delta;
			return this->animateAll(delta);
		}

		void UnitObject::applyTransforms()
		{
			blitz::geometry::Triad t = this->_state->current;
			blitz::geometry::Triad r = this->_state->rotation.direction;
			glTranslatef(t.x, t.y, t.z);
			glRotatef(this->_state->angle, r.x, r.y, r.z);
			glColor4f(this->_state->color.a, this->_state->color.b, this->_state->color.c, this->_state->color.d);
		}

		bool UnitObject::isComplete(void) const
		{
			return false;
		}
	}
}
