/*
 * Camera.hpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <GL/glfw.h>
#include <iostream>
#include "Coordinate.hpp"

namespace blitz {

	class Camera
	{
	private:
		geometry::Dyad _screen;
		geometry::Quad _bounds;
		geometry::Triad _current;
		bool _fixed;
	
	public:
		Camera();
		Camera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, bool fixed);
		virtual ~Camera(void);

		void setScreen(int width, int height);
		void setBounds(const geometry::Quad bounds);
		inline void setFixed(bool value);
		inline bool isFixed(void) const;

		void updateAbsolute(const geometry::Triad& position);
		void updateNormalized(const geometry::Triad& normalized);
		void updateNormalized(int x, int y);
		void updateNormalized(float x, float y);

		geometry::Triad getCurrent() const;
	};
}