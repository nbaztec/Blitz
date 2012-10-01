/*
 * TickedPainter.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once
#include "Ticker.hpp"
#include "Painter.hpp"

namespace blitz {
	class TickedPainter : virtual public Ticker, virtual public Painter
	{					
	};
}