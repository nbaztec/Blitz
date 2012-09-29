/*
 * Level.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include <GL/glfw.h>
#include "../Core/Coordinate.hpp"
#include "../Unit/UnitObject.hpp"
#include "../Core/TickedPainter.hpp"
#include "../Util/ImageFactory.hpp"
#include "../Util/TextureManager.hpp"

namespace blitz {
	namespace view {
		class Level : public TickedPainter{
		protected:
			std::map<std::string, std::vector<unit::UnitObject*>> _objects;
			TextureManager* _texMgr;
		
		public:
			Level();			
			virtual ~Level();
			void setTextureManager(TextureManager* texMgr);			
		};
	}
}