/*
 * ColorAnimation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#include "ColorAnimation.hpp"

namespace blitz {
	namespace state {

		ColorAnimation::ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration)
		{
			this->init(state, type, step, duration, 0.0f, duration <= 0.0f);
		}

		ColorAnimation::ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step)
		{
			this->init(state, type, step, 0.0f, 0.0f, true);
		}		

		ColorAnimation::ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration, const float& delay)
		{
			this->init(state, type, step, duration, delay, duration <= 0.0f);
		}		

		ColorAnimation::~ColorAnimation(void)
		{
		}

		void ColorAnimation::init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration, const float& delay, const bool& infinite)
		{
			Animation::init(state, type, step, duration, delay, infinite);
			if(type == AnimationType::atColorRGB)
			{
				if(duration != 0.0f)
					this->_step = (step - state->color) / duration;
				else
					this->_step.set(0.0f, 0.0f, 0.0f, 0.0f);
			}
		}

		void ColorAnimation::animateDelta(const float& delta)
		{
			switch(this->_type)
			{				
				case AnimationType::atColorBlink:
					this->_state->color.set(this->_step.a, this->_step.b, this->_step.c, this->_step.d);
					break;
				case AnimationType::atColorRGB:
					this->_state->color += geometry::Quad(this->_step.a * delta, this->_step.b * delta, this->_step.c * delta, 0.0f);
					break;
				case AnimationType::atColorRGBA:
					this->_state->color += geometry::Quad(this->_step.a * delta, this->_step.b * delta, this->_step.c * delta, this->_step.d * delta);
					break;
			}
		}

		void ColorAnimation::animateEnd()
		{
			this->_state->color = this->_oldColor;
		}
	}
}