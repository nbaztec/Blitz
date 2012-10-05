/*
 * main.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

// Diable Macro-redefinition warning from windef.h
#pragma warning (disable: 4005)

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Engine/Core/Camera.hpp"
#include "Engine/Core/Coordinate.hpp"
#include "Engine/Core/Point.hpp"
#include "Engine/Util/TextureManager.hpp"
#include "Engine/Util/ModelManager.hpp"
#include "Engine/Util/SoundManager.hpp"
#include "Engine/Util/Randomizer.hpp"
#include "Engine/Util/cal3d/model.h"
#include "Engine/Util/LogManager.hpp"

#include "LastStand/View/GameStage.hpp"
#include "LastStand/View/FightLevel.hpp"

#include <GL/glfw.h>

// Helpers
void logStatus(const char* message, const bool& value)
{
	Log.print(message, -20, '.'); 
	Log << (value ? "Done" : "Failed");
}

// Global Functions
void quit(void);
void init(int argc, char **argv);
void gameLoop(void);

// GLFW Handlers
void GLFWCALL windowResize(int w, int h);
void GLFWCALL renderScene(void);
void GLFWCALL processKeys(int key, int action);
void GLFWCALL processKeyChar(int character, int action);
void GLFWCALL processMousePos(int x, int y);
void GLFWCALL processMouseButton(int button, int action);

// Global Objects
int resolutions[][2] = {
	{640, 480},
	{800, 600},
	{1024, 768},
	{1280, 720},
	{1366, 768},
	{1920, 1080}	
};
int resIdx = 3;
int winWidth = resolutions[resIdx][0];
int winHeight = resolutions[resIdx][1];
game::view::GameStage stage;
blitz::Camera camera;
//blitz::Triad origin = blitz::Triad();
GLfloat strafeStep = 0.1f;

// Randomizers
Randomizer fRand;

// Resources
//std::map<std::string, GLuint> textures;
TextureManager texMgr;
ModelManager mdlMgr;
SoundManager sndMgr;

// Framerate Control
const int TICKS_PER_SECOND = 25;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 5;

// Temporary State Flags
bool screenHit = false;

// Temp
std::vector<blitz::geometry::Dyad> starMap;

// Other Functions
blitz::geometry::Dyad getNRC(const int &x, const int &y);
blitz::geometry::Dyad revNRC(const blitz::geometry::Dyad &point);

int main(int argc, char **argv) {

	// init GLFW and create window
	init(argc, argv);
	gameLoop();
	quit();	
	return 0;
}

Model* pModel;

float delta = 0.0f;		 // Game Delta
void gameLoop()
{
	DWORD next_game_tick = GetTickCount();
	int loops;
	unsigned long now = 0;
	double old_time = GetTickCount();
	float t = 0;	

	while(glfwGetWindowParam(GLFW_OPENED))
	{		
		loops = 0;		
		while((now = GetTickCount()) > next_game_tick && loops < MAX_FRAMESKIP)
		{
			delta = float(now - old_time)/1000.0f;
			if(delta)
				old_time = now;			
			stage.tick(delta);
			//pModel->onUpdate(delta);
			next_game_tick += SKIP_TICKS;
			loops++;

		}
		renderScene();
		glfwSwapBuffers();
	}
}

void quit(void)
{	
	Log << "Performing Cleanup:";
	Log.print("\t[*] OpenAL", -20, '.');
	if(alutExit())
		Log << "Done";
	else
		Log << "Failed";
	Log.print("\t[*] OpenGL", -20, '.');
	glfwTerminate();
	Log << "Done";

	Log.newline();
	Log << "Exiting";
	exit(0);
}

void init(int argc, char **argv)
{	
	// Init OpenAL
	Log << "Loading Libraries:";
	Log.print("\t[*] OpenAL", -20, '.');
	if(alutInit(&argc, argv))
		Log << "Done";
	else
		Log << "Failed";	
	
	// Init OpenGL
	Log.print("\t[*] OpenGL", -20, '.');
	if (glfwInit() != GL_TRUE)
	{
		Log << "Failed";
		quit();
	}
	else
		Log << "Done";	

	// Launch GLFW
	Log.newline();
	Log << "Launching:";
	Log.print("\t[*] GLFW Window", -20, '.');
	if (glfwOpenWindow(winWidth, winHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
	{
		Log << "Failed";
		quit();
	}
	else
		Log << "Done";

	Log.print("\t[*] Window State", -20, '.');
	glfwSetWindowTitle("Last Stand - Powered by Blitz");
	glfwSetWindowPos(0, 0);
	Log << "Done";

	// Init Stage
	Log.newline();
	Log << "Intializing Stage:";
	Log.print("\t[*] Attaching Texture Manager", -40, '.'); 
	stage.setTextureManager(&texMgr);
	Log << "Done";
	Log.print("\t[*] Attaching Model Manager", -40, '.'); 
	stage.setModelManager(&mdlMgr);
	Log << "Done";
	Log.print("\t[*] Attaching Sound Manager", -40, '.'); 
	stage.setSoundManager(&sndMgr);
	Log << "Done";
	Log.print("\t[*] Attaching Camera", -40, '.'); 
	stage.setCamera(blitz::geometry::Triad(), blitz::geometry::Dyad(float(winWidth), float(winHeight)), blitz::geometry::Quad(-5.0f, 0.5f, 5.0f, -2.0f), false);
	Log << "Done";
	Log.print("\t[*] Adding Level", -40, '.'); 
	stage.addLevel("mission", new game::view::FightLevel());	
	stage.setLevel("mission", 0);		
	Log << "Done";
	
	
	// Load Textures/Models
	Log.newline();
	Log << "Loading Game Textures:";
	logStatus("\t[*] Background", texMgr.load("background", "./res/images/space.png"));	
	logStatus("\t[*] Player Fire", texMgr.load("player_fire", "./res/images/star.png"));
	logStatus("\t[*] Crosshair", texMgr.load("crosshair", "./res/images/crosshair.png"));
	logStatus("\t[*] Enemy", texMgr.load("enemy", "./res/images/enemy.png"));
		
	Log.newline();
	Log << "Loading Game Models:";
	logStatus("\t[*] Skeleton", mdlMgr.load("skeleton", "./res/models/skeleton"));
	
	Log.newline();
	Log << "Loading Game Media:";
	logStatus("\t[*] Player Fire", sndMgr.load("player_fire", "./res/media/player_fire.wav"));
	logStatus("\t[*] Player Hit", sndMgr.load("player_hit", "./res/media/player_hit.wav"));
	logStatus("\t[*] Enemy Die", sndMgr.loadOgg("enemy_die", "./res/media/enemy_die.ogg"));
	logStatus("\t[*] Enemy Hit", sndMgr.load("enemy_hit", "./res/media/enemy_hit.wav"));	
	logStatus("\t[*] Level Score", sndMgr.loadOgg("fight", "./res/media/fight_level.ogg"));


	Log.newline();
	Log.print("Setting up GL State", -30, '.');
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	
	/*
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	*/

	glAlphaFunc(GL_GREATER, 0.0f);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	Log << "Done";

	Log.print("Attaching Mouse", -30, '.');
	glfwDisable(GLFW_MOUSE_CURSOR);	
	Log << "Done";
	
	
	// Callbacks
	Log.print("Setting-up Callbacks", -30, '.');
	glfwSetWindowSizeCallback(windowResize);
	glfwSetKeyCallback(processKeys);
	glfwSetCharCallback(processKeyChar);
	glfwSetMousePosCallback(processMousePos);
	glfwSetMouseButtonCallback(processMouseButton);
	Log << "Done";

	Log.print("Setting up GLFW State", -30, '.');
	glfwEnable(GLFW_KEY_REPEAT);	
	Log << "Done";	
}

// Handler for window resizes
void GLFWCALL windowResize(int w, int h)
{
	winWidth = w;
	winHeight = h;	
	if(h == 0)							// Check for zero division
		h = 1;	
	stage.screenChanged(w, h);
	float ratio =  float(w)/h;			// Set aspect ratio	
	glMatrixMode(GL_PROJECTION);		// Use the Projection Matrix	
	glLoadIdentity();					// Reset Matrix	
	glViewport(0, 0, w, h);				// Set the viewport to be the entire window	
	gluPerspective(45,ratio,1,100);		// Set the correct perspective.
	glMatrixMode(GL_MODELVIEW);			// Get Back to the Modelview
}

void renderScene(void)
{
	// Clear Color and Depth Buffers
	//glClearColor(0.1f,0.1f,0.1f,1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	stage.draw();	
}

bool isCrouched = false;
bool hasCursor = false;
void GLFWCALL processKeys(int key, int action)
{
	action == GLFW_PRESS? stage.keyPressed(key) : stage.keyReleased(key);
	
	if(action == GLFW_RELEASE)
	{
		switch(key)
		{
		case GLFW_KEY_ESC:			
			quit();
			break;
		case GLFW_KEY_F2:		
			Log.print("+ Mouse Attached: ");
			Log << hasCursor;
			hasCursor ? glfwDisable(GLFW_MOUSE_CURSOR): glfwEnable(GLFW_MOUSE_CURSOR);
			hasCursor = !hasCursor;						
			break;
		case GLFW_KEY_F3:
			resIdx = (++resIdx) % 5;
			winWidth = resolutions[resIdx][0];
			winHeight = resolutions[resIdx][1];
			glfwSetWindowSize(winWidth, winHeight);
			Log.setSingleLine(true);
			Log << "+ Set Resolution " << winWidth << "x" << winHeight;
			Log.newline();
			Log.setSingleLine(false);			
			break;
		case 'S':
			isCrouched = false;
			camera.updateNormalized(0.0f, -5.0f*strafeStep);
			break;
		}
	}
	else if(action == GLFW_PRESS)
	{
		blitz::geometry::Dyad p;
		
		switch(key)
		{	
		case 'W':
			camera.updateNormalized(0.0f, -strafeStep);
			break;
		case 'A':
			camera.updateNormalized(-strafeStep, 0.0f);
			break;
		case 'S':
			if(!isCrouched)
			{
				isCrouched = true;
				camera.updateNormalized(0.0f, 5.0f*strafeStep);
			}
			break;
		case 'D':
			camera.updateNormalized(strafeStep, 0.0f);
			break;
		}
	}
	
}

void GLFWCALL processKeyChar(int character, int action)
{
	action == GLFW_PRESS? stage.keyCharPressed(character) : stage.keyCharReleased(character);
}

void GLFWCALL processMousePos(int x, int y)
{			
	//camera.updateNormalized(x, y);
	stage.mouseMoved(x, y);
}

void GLFWCALL processMouseButton(int button, int action)
{
	action == GLFW_PRESS? stage.mousePressed(button) : stage.mouseReleased(button);
}