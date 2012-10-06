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
		float _boundWidth;
		float _boundHeight;
	
	public:
		Camera();
		Camera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, const bool& fixed);
		virtual ~Camera(void);

		void setScreen(const int& width, const int& height);
		void setBounds(const geometry::Quad& bounds);
		inline void setFixed(const bool& value);
		inline bool isFixed(void) const;

		void updateAbsolute(const geometry::Triad& position);
		void updateNormalized(const geometry::Triad& normalized);
		void updateNormalized(const int& x, const int& y);
		void updateNormalized(const float& x, const float& y);
		
		geometry::Dyad getScreen() const;
		geometry::Quad getBounds() const;
		float getBoundWidth() const;
		float getBoundHeight() const;
		geometry::Triad getCurrent() const;
		geometry::Triad getCurrentNormalized() const;
	};
}