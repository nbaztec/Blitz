/*
 * SpacePlayer.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <cmath>

#include "../../Engine/Unit/Player.hpp"
#include "../../Engine/Unit/EnergyObject.hpp"

#include "PlasmaBullet.hpp"


namespace game {
	namespace unit {
	
		class SpacePlayer : public virtual blitz::unit::Player, public virtual blitz::unit::EnergyObject {
		protected:
			bool _isCrouched;
			float _strafeStep;
			long _numHits;
			float _regenEnergy;
			float _regenHealth;

		public:
			SpacePlayer(void);
			virtual ~SpacePlayer(void);

			virtual void draw(void);
			virtual void tick(const float& delta);
			virtual bool collision(blitz::unit::UnitObject& obj);
			virtual void hit(UnitObject& obj);
			
			long numHits() const;
			long decHit();
			void resetHits();

			virtual void fireBullet();
			virtual void moveLeft();
			virtual void moveRight();
			virtual void doCrouch(const bool& action);
			virtual void doJump();

			virtual void mousePressed(int button);
			virtual void mouseReleased(int button);
			virtual void mouseMoved(int x, int y);
			virtual void keyPressed(int key);
			virtual void keyReleased(int key);
		};
	}
}