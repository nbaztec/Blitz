/*
 * HUD.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <cmath>
#include <vector>
#include <GL/glfw.h>

#include "../../Engine/Core/Interface/TickedPainter.hpp"
#include "../../Engine/Unit/UnitObject.hpp"

namespace game {
	namespace view {

		namespace Alignment{
			enum EnumAlignment{
				alLeft = 1,
				alRight = 2,
				alTop = 4,
				alBottom = 8
			};
		}

		class HUD : public blitz::TickedPainter {
		protected:
			float _xLow;
			float _yLow;
			float _xHigh;
			float _yHigh;
			float _padX;
			float _padY;
			float _width;
			float _height;
			float _realWidth;
			float _realHeight;

		public:			
			HUD();
			virtual ~HUD();
			
			virtual void setMetrics(const float& xl, const float& yl, const float& xh, const float& yh, const float& padX, const float& padY);

			virtual void tick(const float &delta);
			virtual void draw(void);			
			
			virtual void renderBox();
			virtual void renderHealthBar(const float& health);
			virtual void renderEnergyBar(const float& energy);
			virtual void renderRadar(GLuint texture, const float& width, const float& height);
			virtual void renderEnemyMap(std::vector<blitz::unit::UnitObject*>& enemyList, const float& mapWidth, const float& mapHeight, const float& radarWidth, const float& radarHeight);
			virtual void renderMarkers(const float& x, const float& y);

			void align(int direction);
		};
	}
}