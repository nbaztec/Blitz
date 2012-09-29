/*
 * Ticker.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once
namespace blitz {
	class Ticker
	{
	public:
		virtual void tick(const float &delta) = 0;
	};	
}