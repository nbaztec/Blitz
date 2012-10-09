/*
 * UnitObject.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <GL/glfw.h>
#include "../Core/Interface/TickedPainter.hpp"
#include "../Core/Interface/SoundGenerator.hpp"
#include "../Core/Point.hpp"
#include "../Core/State.hpp"
#include "../Core/Animation.hpp"
#include "../Util/SoundManager.hpp"

#include <iostream>

namespace blitz {
	namespace unit {
		class UnitObject : public blitz::TickedPainter, public blitz::SoundGenerator
		{		
		protected:
			SoundManager* _sndMgr;
			state::State* _state;	
			std::vector<state::Animation*> _animation;
			bool _completed;			

		public:
			UnitObject();
			virtual ~UnitObject();

			state::State* getState() const;
			void setSoundManager(SoundManager* sndMgr);			

			void drawBoundingBox() const;

			virtual bool markCompleted();
			virtual bool updateState(const float& delta);
			virtual bool isComplete(void) const;	
			virtual void draw(void) = 0;
			virtual void applyTransforms();
			virtual void tick(const float& delta) = 0;
			virtual void addAnimation(state::Animation *anim);
			virtual state::Animation* removeAnimation(const int &index);
			virtual bool animateAll(const float& delta);

			virtual bool collision(UnitObject& obj) { return false; }
			virtual void hit(UnitObject& obj) {}

			virtual void terminalComplete(){}
		};
	}
}