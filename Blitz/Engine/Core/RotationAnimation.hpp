/*
 * RotationAnimation.hpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "Animation.hpp"

namespace blitz {
	namespace state {
		class RotationAnimation :	public Animation
		{
		public:
			RotationAnimation(state::State* state, const geometry::Vector& step, const float& duration);
			RotationAnimation(state::State* state, const geometry::Vector& step);
			RotationAnimation(state::State* state, const geometry::Vector& step, const float& duration, const float& delay);
			virtual ~RotationAnimation(void);
			virtual void init(state::State* state, const geometry::Vector& step, const float& duration, const float& delay, const bool& infinite);

			virtual void animateDelta(const float& delta);
			virtual void animateEnd();
		};
	}
}