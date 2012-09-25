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

#include <GL\glfw.h>
#include "Coordinate.hpp"
#include "Object.hpp"
#include "..\Units\PlasmaBullet.hpp"
#include "..\Units\Enemy.hpp"
#include "..\Util\ImageFactory.hpp"
#include "..\Util\TextureManager.hpp"

namespace blitz {

	class Stage {
	private:
		std::map<std::string, std::vector<unit::Object*>> _objects;
		TextureManager* _texMgr;

	protected:
		inline float frand(float min, float max);		
	public:
		// Player
		// Mutalisks
		// Base

		Stage();
		virtual ~Stage();
		void setTextureManager(TextureManager* texMgr);

		void tick(const float &interpolate);
		void draw(void);

		void spawnEnemy(const geometry::Triad& start);
		// Fire
		void playerFire(const geometry::Triad &start);
	};

}