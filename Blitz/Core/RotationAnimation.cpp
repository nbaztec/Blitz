/*
 * RotationAnimation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#include "RotationAnimation.hpp"

namespace blitz {
	namespace state {

		RotationAnimation::RotationAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Vector& step, const float& duration)
		{
			this->init(state, type, step, duration, 0.0f, duration <= 0.0f);
		}

		RotationAnimation::RotationAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Vector& step)
		{
			this->init(state, type, step, 0.0f, 0.0f, true);
		}		

		RotationAnimation::RotationAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Vector& step, const float& duration, const float& delay)
		{
			this->init(state, type, step, duration, delay, duration <= 0.0f);
		}		

		RotationAnimation::~RotationAnimation(void)
		{
		}

		void RotationAnimation::init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Vector& step, const float& duration, const float& delay, const bool& infinite)
		{
			this->_enabled = true;
			this->_type = type;
			this->_state = state;	
			this->_duration = duration;
			this->_delay = delay;
			this->_step.set(step.direction.x, step.direction.y, step.direction.z, step.magnitude);
			this->_infinite = infinite;
			this->_oldColor = this->_state->color;			
		}

		void RotationAnimation::animateDelta(const float& delta)
		{
			this->_state->rotation.direction.set(this->_step.a,this->_step.b, this->_step.c);
			this->_state->rotation.magnitude = this->_step.d;
			this->_state->angle += this->_step.d * delta;
		}

		void RotationAnimation::animateEnd()
		{
		}
	}
}