/*
 * LinearAnimation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#include "LinearAnimation.hpp"

namespace blitz {
	namespace state {

		LinearAnimation::LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration)
		{
			this->init(state, type, step, duration, 0.0f, duration <= 0.0f);
		}

		LinearAnimation::LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step)
		{
			this->init(state, type, step, 0.0f, 0.0f, true);
		}		

		LinearAnimation::LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration, const float& delay)
		{
			this->init(state, type, step, duration, delay, duration <= 0.0f);
		}

		LinearAnimation::~LinearAnimation(void)
		{
		}

		void LinearAnimation::init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration, const float& delay, const bool& infinite)
		{
			this->_enabled = true;
			this->_type = type;
			this->_state = state;	
			this->_duration = duration;
			this->_delay = delay;
			this->_stepT = step;
			this->_infinite = infinite;
			this->_oldColor = this->_state->color;			
		}

		void LinearAnimation::animateDelta(const float& delta)
		{
			this->_state->current += this->_stepT * delta;
		}

		void LinearAnimation::animateEnd()
		{
		}
	}
}