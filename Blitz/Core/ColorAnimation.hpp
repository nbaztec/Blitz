/*
 * ColorAnimation.hpp
 *
 *  Created on: Sep 25, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "Animation.hpp"

namespace blitz {
	namespace state {
		class ColorAnimation :	public Animation
		{
		public:
			ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration);
			ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step);
			ColorAnimation(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration, const float& delay);

			virtual ~ColorAnimation(void);

			virtual void animateDelta(const float& delta);
			virtual void animateEnd();
		};
	}
}