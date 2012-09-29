/*
 * Coordinate.hpp
 *
 *  Created on: Sep 17, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <string>
#include <sstream>

namespace blitz {
	namespace geometry {

		class Dyad
		{
		public:
			float x;
			float y;

			Dyad()
			{
				this->set(0.0f, 0.0f);
			}

			Dyad(const float& x, const float& y)
			{
				this->set(x, y);
			}

			Dyad(const Dyad &rhs)
			{
				this->x = rhs.x;
				this->y = rhs.y;
			}

			Dyad* set(const float& x, const float& y)
			{
				this->x = x;
				this->y = y;
				return this;
			}

			Dyad operator+(const Dyad& rhs) const
			{
				return Dyad(this->x + rhs.x, this->y + rhs.y);
			}

			Dyad operator+=(const Dyad& rhs)
			{
				this->x += rhs.x;
				this->y += rhs.y;
				return *this;
			}

			Dyad operator+(const float& rhs) const
			{
				return Dyad(this->x + rhs, this->y + rhs);
			}	

			Dyad operator+=(const float& rhs)
			{
				this->x += rhs;
				this->y += rhs;
				return *this;
			}

			Dyad operator-(const Dyad& rhs) const
			{
				return Dyad(this->x - rhs.x, this->y - rhs.y);
			}

			Dyad operator-=(const Dyad& rhs)
			{
				this->x -= rhs.x;
				this->y -= rhs.y;
				return *this;
			}

			Dyad operator-(const float& rhs) const
			{
				return Dyad(this->x - rhs, this->y - rhs);
			}	

			Dyad operator-=(const float& rhs)
			{
				this->x -= rhs;
				this->y -= rhs;
				return *this;
			}

			Dyad operator*(const Dyad& rhs) const
			{
				return Dyad(this->x * rhs.x, this->y * rhs.y);
			}

			Dyad operator*=(const Dyad& rhs)
			{
				this->x *= rhs.x;
				this->y *= rhs.y;
				return *this;
			}

			Dyad operator*(const float& rhs) const
			{
				return Dyad(this->x * rhs, this->y * rhs);
			}	

			Dyad operator*=(const float& rhs)
			{
				this->x *= rhs;
				this->y *= rhs;
				return *this;
			}

			Dyad operator/(const Dyad& rhs) const
			{
				return Dyad(this->x / rhs.x, this->y / rhs.y);
			}

			Dyad operator/=(const Dyad& rhs)
			{
				this->x /= rhs.x;
				this->y /= rhs.y;
				return *this;
			}

			Dyad operator/(const float& rhs) const
			{
				return Dyad(this->x / rhs, this->y / rhs);
			}	

			Dyad operator/=(const float& rhs)
			{
				this->x /= rhs;
				this->y /= rhs;
				return *this;
			}

			std::string toString() const
			{
				std::stringstream oss;
				oss << this->x << ', ' << this->y;
				return oss.str();
			}
		};

		class Triad
		{
		public:
			float x;
			float y;
			float z;

			Triad()
			{
				this->set(0.0f, 0.0f, 0.0f);
			}

			Triad(const float &x, const float &y, const float &z)
			{
				this->set(x, y, z);
			}

			Triad(const Triad &rhs)
			{
				this->x = rhs.x;
				this->y = rhs.y;
				this->z = rhs.z;
			}

			Triad* set(const float &x, const float &y, const float &z)
			{
				this->x = x;
				this->y = y;
				this->z = z;
				return this;
			}

			Triad operator+(const Triad &rhs) const
			{
				return Triad(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
			}

			Triad operator+=(const Triad& rhs)
			{
				this->x += rhs.x;
				this->y += rhs.y;
				this->z += rhs.z;
				return *this;
			}

			Triad operator+(const float& rhs) const
			{
				return Triad(this->x + rhs, this->y + rhs, this->z + rhs);
			}	

			Triad operator+=(const float& rhs)
			{
				this->x += rhs;
				this->y += rhs;
				this->z += rhs;
				return *this;
			}

			Triad operator-(const Triad &rhs) const
			{
				return Triad(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
			}

			Triad operator-=(const Triad& rhs)
			{
				this->x -= rhs.x;
				this->y -= rhs.y;
				this->z -= rhs.z;
				return *this;
			}

			Triad operator-(const float& rhs) const
			{
				return Triad(this->x - rhs, this->y - rhs, this->z - rhs);
			}	

			Triad operator-=(const float& rhs)
			{
				this->x -= rhs;
				this->y -= rhs;
				this->z -= rhs;
				return *this;
			}

			Triad operator*(const Triad &rhs) const
			{
				return Triad(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
			}

			Triad operator*=(const Triad& rhs)
			{
				this->x *= rhs.x;
				this->y *= rhs.y;
				this->z *= rhs.z;
				return *this;
			}

			Triad operator*(const float& rhs) const
			{
				return Triad(this->x * rhs, this->y * rhs, this->z * rhs);
			}	

			Triad operator*=(const float& rhs)
			{
				this->x *= rhs;
				this->y *= rhs;
				this->z *= rhs;
				return *this;
			}

			Triad operator/(const Triad &rhs) const
			{
				return Triad(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
			}

			Triad operator/=(const Triad& rhs)
			{
				this->x /= rhs.x;
				this->y /= rhs.y;
				this->z /= rhs.z;
				return *this;
			}

			Triad operator/(const float& rhs) const
			{
				return Triad(this->x / rhs, this->y / rhs, this->z / rhs);
			}	

			Triad operator/=(const float& rhs)
			{
				this->x /= rhs;
				this->y /= rhs;
				this->z /= rhs;
				return *this;
			}

			std::string toString() const
			{
				std::stringstream oss;
				oss << this->x << ', ' << this->y << ', ' << this->z;
				return oss.str();
			}
			
			inline float dotProduct(const Triad& rhs) const
			{
				return (this->x*rhs.x) + (this->y*rhs.y) + (this->z*rhs.z);
			}
		};

		class Quad
		{
		public:
			float a;
			float b;
			float c;
			float d;

			Quad()
			{
				this->set(0.0f, 0.0f, 0.0f, 0.0f);
			}

			Quad(const float& a, const float& b, const float& c, const float& d)
			{
				this->set(a, b, c, d);
			}

			Quad(const Quad &rhs)
			{
				this->a = rhs.a;
				this->b = rhs.b;
				this->c = rhs.c;
				this->d = rhs.d;
			}

			Quad* set(const float& a, const float& b, const float& c, const float& d)
			{
				this->a = a;
				this->b = b;
				this->c = c;
				this->d = d;
				return this;
			}

			Quad operator+(const Quad &rhs) const
			{
				return Quad(this->a + rhs.a, this->b + rhs.b, this->c + rhs.c, this->d + rhs.d);
			}

			Quad operator+=(const Quad& rhs)
			{
				this->a += rhs.a;
				this->b += rhs.b;
				this->c += rhs.c;
				this->d += rhs.d;
				return *this;
			}

			Quad operator+(const float &rhs) const
			{
				return Quad(this->a + rhs, this->b + rhs, this->c + rhs, this->d + rhs);
			}		

			Quad operator+=(const float& rhs)
			{
				this->a += rhs;
				this->b += rhs;
				this->c += rhs;
				this->d += rhs;
				return *this;
			}			

			Quad operator-(const Quad &rhs) const
			{
				return Quad(this->a - rhs.a, this->b - rhs.b, this->c - rhs.c, this->d - rhs.d);
			}

			Quad operator-=(const Quad& rhs)
			{
				this->a -= rhs.a;
				this->b -= rhs.b;
				this->c -= rhs.c;
				this->d -= rhs.d;
				return *this;
			}

			Quad operator-(const float &rhs) const
			{
				return Quad(this->a - rhs, this->b - rhs, this->c - rhs, this->d - rhs);
			}		

			Quad operator-=(const float& rhs)
			{
				this->a -= rhs;
				this->b -= rhs;
				this->c -= rhs;
				this->d -= rhs;
				return *this;
			}

			Quad operator*(const Quad &rhs) const
			{
				return Quad(this->a * rhs.a, this->b * rhs.b, this->c * rhs.c, this->d * rhs.d);
			}

			Quad operator*=(const Quad& rhs)
			{
				this->a *= rhs.a;
				this->b *= rhs.b;
				this->c *= rhs.c;
				this->d *= rhs.d;
				return *this;
			}

			Quad operator*(const float &rhs) const
			{
				return Quad(this->a * rhs, this->b * rhs, this->c * rhs, this->d * rhs);
			}		

			Quad operator*=(const float& rhs)
			{
				this->a *= rhs;
				this->b *= rhs;
				this->c *= rhs;
				this->d *= rhs;
				return *this;
			}

			Quad operator/(const Quad &rhs) const
			{
				return Quad(this->a / rhs.a, this->b / rhs.b, this->c / rhs.c, this->d / rhs.d);
			}

			Quad operator/=(const Quad& rhs)
			{
				this->a /= rhs.a;
				this->b /= rhs.b;
				this->c /= rhs.c;
				this->d /= rhs.d;
				return *this;
			}

			Quad operator/(const float &rhs) const
			{
				return Quad(this->a / rhs, this->b / rhs, this->c / rhs, this->d / rhs);
			}		

			Quad operator/=(const float& rhs)
			{
				this->a /= rhs;
				this->b /= rhs;
				this->c /= rhs;
				this->d /= rhs;
				return *this;
			}

			std::string toString() const
			{
				std::stringstream oss;
				oss << this->a << ', ' << this->b << ', ' << this->c;
				return oss.str();
			}
			
			inline float dotProduct(const Quad& rhs) const
			{
				return (this->a*rhs.a) + (this->b*rhs.b) + (this->c*rhs.c);
			}
		};
	}
}