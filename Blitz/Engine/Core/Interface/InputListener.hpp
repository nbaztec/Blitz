/*
 * Painter.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

namespace blitz {
	class InputListener
	{
	public:
		virtual void mousePressed(int button) = 0;
		virtual void mouseReleased(int button) = 0;
		virtual void mouseMoved(int x, int y) = 0;
		virtual void mouseWheelMoved(int pos) = 0;						

		virtual void keyPressed(int key) = 0;
		virtual void keyReleased(int key) = 0;
		virtual void keyCharPressed(int character) = 0;
		virtual void keyCharReleased(int character) = 0;
	};
}