/*
 * State.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include "Coordinate.hpp"
#include "Point.hpp"

namespace blitz {
	namespace state {

		struct State
		{
			double duration;
			geometry::Quad color;
			geometry::Triad current;
			float angle;
			geometry::Triad start;
			geometry::Dyad box;
			geometry::Triad normal;
			geometry::Triad velocity;
			geometry::Vector rotation;
			geometry::Triad gravity;

			State()
			{				
				this->duration = 0.0;
				this->angle = 0.0f;
				this->color = geometry::Quad(1.0f, 1.0f, 1.0f, 1.0f);
				this->start = geometry::Triad();
				this->box = geometry::Dyad();
				this->normal = geometry::Triad();
				this->current = geometry::Triad();
				this->velocity = geometry::Triad();
				this->rotation = geometry::Vector();
				this->gravity = geometry::Triad();
			}

			~State()
			{
			}
		};
	}
}