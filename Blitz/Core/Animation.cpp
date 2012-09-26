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
			this->_duration = float(this->_state->duration) + duration;
			this->_delay = delay;
			this->_step = step;
			this->_infinite = infinite;
			this->_oldColor = this->_state->clear;
			this->_terminal = false;
		}

		bool Animation::animate(const float& delta)
		{			
			if(this->_enabled)
			{
				if(this->_state->duration >= this->_delay)
				{
					if(this->_infinite || this->_state->duration < (this->_delay + this->_duration))
					{
						this->animateDelta(delta);
						std::cout<<"-> "<<this->_state->current.toString()<<std::endl;
					}
					else
					{					
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

		bool Animation::isInfinite() const
		{
			return this->_infinite;
		}
		
		bool Animation::isTerminal() const
		{
			return this->_terminal;
		}

		bool Animation::setTerminal(bool value)
		{
			return this->_terminal = value;
		}
		
	}
}