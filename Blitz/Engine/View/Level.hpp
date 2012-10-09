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
#include "../Core/Interface/TickedPainter.hpp"
#include "../Core/Interface/InputListener.hpp"
#include "../Core/Interface/SoundGenerator.hpp"
#include "../Core/Coordinate.hpp"
#include "../Core/Camera.hpp"
#include "../Unit/UnitObject.hpp"
#include "../Unit/Player.hpp"
#include "../Util/ImageFactory.hpp"
#include "../Util/TextureManager.hpp"
#include "../Util/ModelManager.hpp"
#include "../Util/SoundManager.hpp"
#include "../Util/Randomizer.hpp"

namespace blitz {
	namespace unit {
		class Player;
	}
}


namespace blitz {
	namespace view {
		class Level : virtual public TickedPainter, virtual public InputListener, virtual public SoundGenerator{
		protected:			
			std::map<std::string, std::vector<unit::UnitObject*>> _objects;
			std::vector<blitz::unit::Player*> _players;
			TextureManager* _texMgr;
			ModelManager* _mdlMgr;
			SoundManager* _sndMgr;
			blitz::unit::Player* _currentPlayer;

			Camera* _camera;
			static Randomizer RAND;			

		public:
			Level();			
			virtual ~Level();
			void setCamera(Camera* camera);
			Camera* getCamera();

			virtual void tick(const float& delta);
			void setTextureManager(TextureManager* texMgr);
			void setModelManager(ModelManager* mdlMgr);
			void setSoundManager(SoundManager* sndMgr);			
			void setCurrentPlayer(const int& index);

			void addUnit(const char* key, unit::UnitObject* unit);
			void addPlayer(blitz::unit::Player* player);

			virtual void mousePressed(int button);
			virtual void mouseReleased(int button);
			virtual void mouseMoved(int x, int y);
			virtual void mouseWheelMoved(int pos);

			virtual void keyPressed(int key);
			virtual void keyReleased(int key);
			virtual void keyCharPressed(int character);
			virtual void keyCharReleased(int character);
		};
	}
}