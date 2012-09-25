/*
 * Animation.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "Animation.hpp"
//#include <iostream>

namespace blitz {
	namespace state {
		
		void Animation::init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration, const float& delay, const bool& infinite)
		{
			this->_enabled = true;
			this->_type = type;
			this->_state = state;	
			this->_duration = duration;
			this->_delay = delay;
			this->_step = step;
			this->_infinite = infinite;
			this->_oldColor = this->_state->color;			
		}

		bool Animation::animate(const float& delta)
		{			
			if(this->_enabled)
			{
				//this->_duration -= delta;
				if(this->_state->duration >= this->_delay)
				{
					if(this->_infinite || this->_state->duration < (this->_delay + this->_duration))
					{/*
					switch(this->_type)
					{
						case AnimationType::atTranslate:
							this->_state->current += this->_step.direction * delta;
							break;
						case AnimationType::atRotate:
							this->_state->rotation.direction = this->_step.direction;
							this->_state->rotation.magnitude = this->_step.magnitude;
							this->_state->angle += this->_step.magnitude * delta;
							break;
						case AnimationType::atColorBlink:
							this->_state->color.set(this->_step.direction.x, this->_step.direction.y, this->_step.direction.z, this->_step.magnitude);
							break;
						case AnimationType::atColorRGB:
							this->_state->color += geometry::Quad(this->_step.direction.x * delta, this->_step.direction.y * delta, this->_step.direction.z * delta, this->_step.magnitude);
							break;
					}*/	
						this->animateDelta(delta);
						std::cout<<"-> "<<this->_state->current.toString()<<std::endl;
					}
					else
					{
						//if(this->_type == AnimationType::atColorBlink)
						//	this->_state->color = this->_oldColor;
						this->animateEnd();
						this->_enabled = false;
					}
				}				
			}
			return this->_enabled;
		}

		geometry::Quad Animation::stateStep() const
		{
			return this->_step;
		}

		bool Animation::isInfinite()
		{
			return this->_infinite;
		}
		
	}
}