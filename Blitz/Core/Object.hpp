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
			bool _completed;

		public:
			Object();
			virtual ~Object();

			state::State* getState() const;

			virtual bool updateState(float delta);
			virtual bool isComplete(void) const;
			bool hasCompleted();

			virtual void draw(void) = 0;		
			virtual void tick(float delta) = 0;
			virtual void addAnimation(state::Animation *anim);
			virtual state::Animation* removeAnimation(const int &index);
			virtual bool animateAll(float delta);

			virtual bool collision(Object& obj) { return false; }
			virtual void hit(Object& obj) {}
		};
	}
}