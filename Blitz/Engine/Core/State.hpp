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
			geometry::Quad clear;
			geometry::Triad start;
			geometry::Quad box;
			geometry::Triad normal;
			geometry::Triad velocity;
			geometry::Vector rotation;
			geometry::Triad gravity;

			State()
			{				
				this->duration = 0.0;
				this->angle = 0.0f;
				this->clear = this->color = geometry::Quad(1.0f, 1.0f, 1.0f, 1.0f);
				this->start = geometry::Triad();
				this->box = geometry::Quad();
				this->normal = geometry::Triad();
				this->current = geometry::Triad();
				this->velocity = geometry::Triad();
				this->rotation = geometry::Vector();
				this->gravity = geometry::Triad();
			}

			~State()
			{
			}

			void setColorClear(const geometry::Quad& color)
			{
				this->clear = this->color = color;
			}
	
			void setColorClear(const float& r, const float& g, const float& b, const float& a)
			{
				this->clear = this->color = geometry::Quad(r, g, b, a);
			}

		};
	}
}