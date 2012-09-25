/*
 * Object.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <GL\glfw.h>
#include "Point.hpp"
#include "State.hpp"
#include "Animation.hpp"
#include <iostream>

namespace blitz {
	namespace unit {
		class Object
		{
		protected:
			state::State* _state;	
			std::vector<state::Animation*> _animation;

		public:
			Object();
			virtual ~Object();

			state::State* getState() const;

			virtual void updateState(float delta);
			virtual bool isComplete(void) const;

			virtual void draw(void) = 0;		
			virtual void tick(float delta) = 0;
			virtual void addAnimation(state::Animation *anim);
			virtual state::Animation* removeAnimation(const int &index);
			virtual void animateAll(float delta);

			virtual bool collision(const Object& obj)
			{
				float dp = this->_state->normal.dotProduct(obj._state->normal);
				if(dp < 0.0f && dp > -0.0f)
					return false;
				float l = obj._state->normal.dotProduct(obj._state->start)/dp;
				//std::cout << "Collision in :" << l << ", " << dp <<std::endl;
				if (l < -0.0f)
					return false;
				else
					return true;
			}
		};
	}
}