/*
 * GameStage.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include <GL/glfw.h>
#include "../../Engine/Core/Coordinate.hpp"
#include "../../Engine/View/Stage.hpp"
#include "../../Engine/Unit/UnitObject.hpp"
#include "../../Engine/Unit/PlasmaBullet.hpp"
#include "../../Engine/Unit/Enemy.hpp"
#include "../../Engine/Unit/SkeletonEnemy.hpp"
#include "../../Engine/Util/ImageFactory.hpp"
#include "../../Engine/Util/TextureManager.hpp"

namespace game {
	namespace view {

		class GameStage : public blitz::view::Stage {
		protected:
			long _hitPlayer;
			float _lastHitDuration;
		public:			
			GameStage();
			virtual ~GameStage();
			
			virtual void tick(const float &interpolate);
			virtual void draw(void);

			void spawnEnemy(const blitz::geometry::Triad& start, Model* model);
			// Fire
			void playerFire(const blitz::geometry::Triad &start);

			long getPlayerHits() const;
			long decPlayerHits();
			void resetPlayerHits();

			bool persistHitDraw(float delta);
			void hitDrawReset();
		};
	}
}