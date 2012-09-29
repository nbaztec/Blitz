/*
 * UnitObject.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <GL/glfw.h>
#include "../Core/TickedPainter.hpp"
#include "../Core/Point.hpp"
#include "../Core/State.hpp"
#include "../Core/Animation.hpp"
#include <iostream>

namespace blitz {
	namespace unit {
		class UnitObject : public virtual blitz::TickedPainter
		{
		protected:
			state::State* _state;	
			std::vector<state::Animation*> _animation;
			bool _completed;

		public:
			UnitObject();
			virtual ~UnitObject();

			state::State* getState() const;

			virtual bool updateState(float delta);
			virtual bool isComplete(void) const;
			bool hasCompleted();

			virtual void draw(void) = 0;		
			virtual void tick(float delta) = 0;
			virtual void addAnimation(state::Animation *anim);
			virtual state::Animation* removeAnimation(const int &index);
			virtual bool animateAll(float delta);

			virtual bool collision(UnitObject& obj) { return false; }
			virtual void hit(UnitObject& obj) {}
		};
	}
}