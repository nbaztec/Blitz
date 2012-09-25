/*
 * LinearAnimation.hpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "Animation.hpp"

namespace blitz {
	namespace state {
		class LinearAnimation :	public Animation
		{
		protected:
			geometry::Triad _stepT;
		public:
			LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration);
			LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step);
			LinearAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration, const float& delay);
			virtual ~LinearAnimation(void);

			virtual void init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Triad& step, const float& duration, const float& delay, const bool& infinite);

			virtual void animateDelta(const float& delta);
			virtual void animateEnd();
		};
	}
}