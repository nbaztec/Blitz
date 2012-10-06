/*
 * FightLevel.hpp
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
#include "../../Engine/View/Level.hpp"
#include "../../Engine/Unit/UnitObject.hpp"
#include "../../Engine/Unit/Player.hpp"
#include "../../Engine/Util/ImageFactory.hpp"
#include "../../Engine/Util/TextureManager.hpp"
#include "../../Engine/Util/LogManager.hpp"
#include "../../Engine/Unit/UnitObject.hpp"

#include "../Unit/SpacePlayer.hpp"
#include "../Unit/PlasmaBullet.hpp"
#include "../Unit/Enemy.hpp"
#include "../Unit/SkeletonEnemy.hpp"

#include "HUD.hpp"

namespace game {
	namespace view {

		class FightLevel : public blitz::view::Level {
		protected:			
			HUD* _hud;
			bool _screenHit;
			//long _hitPlayer;
			float _lastHitDuration;

			virtual void tickCamera(const float& delta);
			virtual void tickOverlay(const float& delta);
			virtual void tickPlayers(const float& delta);

			virtual void renderCamera();
			virtual void renderBackground();
			virtual void renderCrosshair();
			virtual void renderHUD();
			virtual void renderOverlay();
			virtual void renderPlayers();

			virtual void onFirstRender();
		public:			
			FightLevel();
			virtual ~FightLevel();
			
			virtual void tick(const float &interpolate);
			virtual void draw(void);

			void spawnEnemy(const blitz::geometry::Triad& start, Model* model);			

			long getPlayerHits() const;
			long decPlayerHits();
			void resetPlayerHits();

			bool persistHitDraw(float delta);
			void hitDrawReset();
			
			virtual void mouseReleased(int button);
			virtual void mouseMoved(int x, int y);
			virtual void keyPressed(int key);
			virtual void keyReleased(int key);
		};
	}
}