/*
 * Point.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include "Coordinate.hpp"

namespace blitz {
	namespace geometry {

		struct Color
		{
			float r;
			float g;
			float b;
			float a;

			Color()
			{
				this->set(1.0f, 1.0f, 1.0f, 1.0f);
			}

			Color(const float &r, const float &g, const float &b, const float &a)
			{
				this->set(r, g, b, a);
			}

			void set(const float &r, const float &g, const float &b, const float &a)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}
		};

		struct Point
		{
			Triad value;
			Color color;

			Point()
			{
				this->value = Triad();
				this->color = Color();
			}

			Point(const float &x, const float &y, const float &z)
			{
				this->value = Triad(x, y, z);
			}

			Point(const float &x, const float &y, const float &z, const float &r, const float &g, const float &b, const float &a)
			{
				this->value = Triad(x, y, z);
				this->color = Color(r, g, b, a);
			}
		};

		struct Vector
		{
			Triad direction;
			float magnitude;	

			Vector()
			{
				this->magnitude = 0.0f;
				this->direction = Triad();
			}

			Vector(const Vector& v)
			{
				this->magnitude = v.magnitude;
				this->direction = v.direction;
			}

			Vector(const Triad& direction, const float& magnitude)
			{
				this->magnitude = magnitude;
				this->direction = direction;
			}

			Vector(const float& x, const float& y, const float& z, const float& magnitude)
			{
				this->magnitude = magnitude;
				this->direction = Triad(x, y, z);
			}
		};
	}
}