/*
 * Painter.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

namespace blitz {
	class Painter
	{
	private:
		bool _firstRender;
	protected:
		
		inline void callFirstRender()
		{
			if(this->_firstRender)
			{
				this->onFirstRender();
				this->_firstRender = false;
			}
		}

		virtual void onFirstRender(){}
	public:
		Painter(){ this->_firstRender = true; }
		virtual void draw(void) = 0;
	};
}