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

	Camera::Camera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, bool fixed)
	{
		this->_current = current;
		this->_screen = screen;
		this->_bounds = bounds;
		this->_fixed = fixed;
	}


	Camera::~Camera(void)
	{
	}

	inline void Camera::setFixed(bool value)
	{
		this->_fixed = value;
	}

	inline bool Camera::isFixed(void) const
	{
		return this->_fixed;
	}

	void Camera::setScreen(int width, int height)
	{
		this->_screen.set(float(width), float(height));
	}

	void Camera::updateAbsolute(const blitz::geometry::Triad& position)
	{
		this->_current = position;
	}

	void Camera::updateNormalized(const blitz::geometry::Triad& normalized)
	{
	}

	void Camera::updateNormalized(int x, int y)
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

	void Camera::updateNormalized(float relx, float rely)
	{
		this->_current.x += relx;
		this->_current.y += rely;
		int rx = int((this->_current.x/2 + 0.5f) * this->_screen.x);
		int ry = int((this->_current.y/2 + 0.5f) * this->_screen.y);
		glfwSetMousePos(rx, ry);
	}
	
	geometry::Triad Camera::getCurrent() const
	{
		return this->_current;
	}
}
