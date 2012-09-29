/*
 * Stage.hpp
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
#include "../Util/TextureManager.hpp"
#include "Level.hpp"

namespace blitz {
	namespace view {
		class Stage : public TickedPainter {
		protected:
			std::map<std::string, std::vector<view::Level*>> _levels;
			TextureManager* _texMgr;			
			view::Level* _currentLevel;
		public:			
			Stage();
			virtual ~Stage();
			void setTextureManager(TextureManager* texMgr);
			void addLevel(const std::string& key, view::Level* level);		
			Level* removeLevel(const std::string& key, const int& index);
			virtual Level* setLevel(const std::string& key, const int& index);
			virtual Level* setLevel(const std::string& key, const Level* level);			
		};
	}
}