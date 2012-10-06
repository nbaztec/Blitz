/*
 * Camera.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#include "Camera.hpp"

namespace blitz {

	Camera::Camera()
	{
		this->_current = geometry::Triad();
		this->_screen = geometry::Dyad();
		this->_bounds = geometry::Quad();
		this->_fixed = false;
	}

	Camera::Camera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, const bool& fixed)
	{
		this->_current = current;
		this->_screen = screen;
		this->_bounds = bounds;
		this->_fixed = fixed;
		this->_boundWidth = this->_bounds.c - this->_bounds.a;
		this->_boundHeight = this->_bounds.b - this->_bounds.d;
	}


	Camera::~Camera(void)
	{
	}

	inline void Camera::setFixed(const bool& value)
	{
		this->_fixed = value;
	}

	inline bool Camera::isFixed(void) const
	{
		return this->_fixed;
	}

	void Camera::setScreen(const int& width, const int& height)
	{
		this->_screen.set(float(width), float(height));
	}

	void Camera::setBounds(const geometry::Quad& bounds)
	{
		this->_bounds = bounds;
		this->_boundWidth = this->_bounds.c - this->_bounds.a;
		this->_boundHeight = this->_bounds.b - this->_bounds.d;
	}

	void Camera::updateAbsolute(const blitz::geometry::Triad& position)
	{
		this->_current = position;
	}

	void Camera::updateNormalized(const blitz::geometry::Triad& normalized)
	{
	}

	void Camera::updateNormalized(const int& x, const int& y)
	{
		float nx = 2*(float(x)/this->_screen.x - 0.5f);
		float ny = 2*(0.5f - float(y)/this->_screen.y);
		//std::cout << x << ", " << y << "\t|\t" << nx << ", " << ny  << std::endl;
		bool change = false;
		if(nx <= this->_bounds.a || nx >= this->_bounds.c)
		{
			nx = nx < 0.0f? this->_bounds.a: this->_bounds.c;
			change = true;
		}
		if(ny <= this->_bounds.d || ny >= this->_bounds.b)
		{
			ny = ny < 0.0f? this->_bounds.d: this->_bounds.b;
			change = true;
		}
		if(change)
		{
			float rx = (nx/2 + 0.5f) * this->_screen.x;
			float ry = (0.5f- ny/2 ) * this->_screen.y;
			//std::cout << rx << ", " << ry << std::endl;
			glfwSetMousePos(int(rx), int(ry));
		}
		this->_current.x = nx;
		this->_current.y = ny;
	}

	void Camera::updateNormalized(const float& relx, const float& rely)
	{
		this->_current.x += relx;
		this->_current.y += rely;
		int rx = int((this->_current.x/2 + 0.5f) * this->_screen.x);
		int ry = int((this->_current.y/2 + 0.5f) * this->_screen.y);
		glfwSetMousePos(rx, ry);
	}

	geometry::Dyad Camera::getScreen() const
	{
		return this->_screen;
	}

	geometry::Quad Camera::getBounds() const
	{
		return this->_bounds;
	}

	float Camera::getBoundWidth() const
	{
		return this->_boundWidth;
	}

	float Camera::getBoundHeight() const
	{
		return this->_boundHeight;
	}

	geometry::Triad Camera::getCurrent() const
	{
		return this->_current;
	}

	geometry::Triad Camera::getCurrentNormalized() const
	{
		return geometry::Triad(2*this->_current.x/this->_boundWidth, 2*this->_current.y/this->_boundHeight, 0.0f);
	}
}
