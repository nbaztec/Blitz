/*
 * Animation.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "Coordinate.hpp"
#include "State.hpp"
#include <iostream>

namespace blitz {
	namespace state {
		namespace AnimationType {
			enum enumAnimationType 
			{
				atTranslate, 
				atRotate,
				atColorBlink,
				atColorRGB,
				atColorRGBA,
			};
		}

		class Animation
		{
		protected:
			bool _enabled;
			AnimationType::enumAnimationType _type;
			state::State* _state;
			geometry::Quad _step;
			float _delay;
			float _duration;
			bool _infinite;
			geometry::Quad _oldColor;

		public:			
			virtual void init(state::State* state, const AnimationType::enumAnimationType& type, const geometry::Quad& step, const float& duration, const float& delay, const bool& infinite);
			virtual bool animate(const float& delta);
			virtual void animateDelta(const float& delta) = 0;
			virtual void animateEnd() = 0;
			virtual geometry::Quad stateStep() const;
			virtual bool isInfinite();
		};
	}
}