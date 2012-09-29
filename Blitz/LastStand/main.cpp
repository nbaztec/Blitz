/*
 * main.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <GL/glfw.h>


//#include "../Engine/View/Stage.hpp"
#include "View/GameStage.hpp"
#include "../Engine/Core/Camera.hpp"
#include "../Engine/Core/Coordinate.hpp"
#include "../Engine/Core/Point.hpp"
#include "../Engine/Util/TextureManager.hpp"
#include "../Engine/Util/Randomizer.hpp"
#include "../Engine/Util/cal3d/model.h"

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
			pModel->onUpdate(delta);
			next_game_tick += SKIP_TICKS;
			loops++;

		}
		renderScene();
		glfwSwapBuffers();
	}
}

void quit(void)
{
	pModel->onShutdown();
	glfwTerminate();
	exit(0);
}


void init(int argc, char **argv)
{
	if (glfwInit() != GL_TRUE)
		quit();

	if (glfwOpenWindow(winWidth, winHeight, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
		quit();

	glfwSetWindowTitle("Last Stand - Powered by Blitz");
	glfwSetWindowPos(0, 0);
	
	// Screen Settings
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	//glEnable(GL_TEXTURE_2D);
	
	/*
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	*/
	glAlphaFunc(GL_GREATER, 0.0f);	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glShadeModel(GL_SMOOTH);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glfwDisable(GLFW_MOUSE_CURSOR);
	
	
	// Callbacks
	glfwSetWindowSizeCallback(windowResize);
	glfwSetKeyCallback(processKeys);
	glfwSetCharCallback(processKeyChar);
	glfwSetMousePosCallback(processMousePos);
	glfwSetMouseButtonCallback(processMouseButton);

	glfwEnable(GLFW_KEY_REPEAT);

	// Load Textures/Models
	texMgr.load("background", "./res/space.png");
	texMgr.load("player_fire", "./res/star.png");
	texMgr.load("crosshair", "./res/crosshair.png");
	texMgr.load("enemy", "./res/enemy.png");

	// Init Stage
	stage.setTextureManager(&texMgr);	
	camera = blitz::Camera(blitz::geometry::Triad(), blitz::geometry::Dyad(float(winWidth), float(winHeight)), blitz::geometry::Quad(-5.0f, 0.5f, 5.0f, -2.0f), false);
	for(int i=0; i<50; i++)
		starMap.push_back(blitz::geometry::Dyad(fRand.randFloat(2.0f, 6.0f), fRand.randFloat(-1.0f, 1.0f)));		

	// Cal3D
	pModel = new Model();	
	pModel->setPath( "./res/skeleton/" );
	if(!pModel->onInit("./res/skeleton/skeleton.cfg"))
	{
		delete pModel;
		std::cerr << "Model initialization failed! (skeleton)" << std::endl;		
	}
	std::cout << "Model loaded! (skeleton)" << std::endl;		
}

// Handler for window resizes
void GLFWCALL windowResize(int w, int h)
{
	winWidth = w;
	winHeight = h;	
	if(h == 0)							// Check for zero division
		h = 1;
	camera.setScreen(w, h);
	float ratio =  float(w)/h;			// Set aspect ratio	
	glMatrixMode(GL_PROJECTION);		// Use the Projection Matrix	
	glLoadIdentity();					// Reset Matrix	
	glViewport(0, 0, w, h);				// Set the viewport to be the entire window	
	gluPerspective(45,ratio,1,100);		// Set the correct perspective.
	glMatrixMode(GL_MODELVIEW);			// Get Back to the Modelview
}

void drawStar()
{
	glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();	
}

void _renderScene(void)
{	
	glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
		// Reset transformations
		float renderScale;
		renderScale = pModel->getRenderScale()*1;
  
		// set the projection transformation
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
  	
		gluPerspective(45.0f, (GLdouble)winWidth/ (GLdouble)winHeight, renderScale * 50.0, renderScale * 5000.0);
  
		// set the model transformation
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glTranslatef(0.0f, -50.0f, -200.0f);

		const GLfloat lightPosition[] = { 1.0f, -1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		const GLfloat lightColorAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightColorAmbient);
		const GLfloat lightColorDiffuse[] = { 0.52f, 0.5f, 0.5f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
		const GLfloat lightColorSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightColorSpecular);


		glTranslatef(0.0f, 0.0f, -270.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(0.0f, 0.0f, 0.0f, 1.0f);  
		//if(pModel)
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		pModel->onRender();
	glPopMatrix();

}
void renderScene(void)
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	// Set the camera
	blitz::geometry::Triad lookAt = camera.getCurrent();	

	//glPushMatrix();	
	gluLookAt(	lookAt.x * 10.0f, lookAt.y * 5.0f, 0.0f,
				lookAt.x * 10.0f, lookAt.y * 5.0f, -50.0f,
				0.0f, 1.0f,  0.0f);
	
	//glTranslatef(0.0f, 0.0f, 150.0f);
	//glPopMatrix();
	//glMatrixMode (GL_MODELVIEW);
	//glDisable(GL_DEPTH_TEST);
	
	glPushMatrix ();
		glLoadIdentity();		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();		
			glLoadIdentity();			
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texMgr["background"].first());
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();			
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix ();
	/*
	glPushMatrix();		
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		const GLfloat lightPosition[] = { 1.0f, -1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		const GLfloat lightColorAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightColorAmbient);
		const GLfloat lightColorDiffuse[] = { 0.52f, 0.5f, 0.5f, 1.0f };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
		const GLfloat lightColorSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightColorSpecular);
		
		//glTranslatef(0.0f, 0.0f, -270.0f);
		glTranslatef(0.0f, 0.0f, -80.0f);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(0.0f, 0.0f, 0.0f, 1.0f);  		
		//if(pModel)
		glScalef(0.025f, 0.025f, 0.025f);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
		pModel->onRender();
	glPopMatrix();
	*/
	
	stage.draw();

	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);

	glBindTexture(GL_TEXTURE_2D, texMgr["crosshair"].first());
    glPushMatrix();				// Crosshair
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -2.0f);
		glColor4f(1.0f, 0.2f, 0.2f, 0.5f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f,-0.1f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.1f,-0.1f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f, 0.1f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.1f, 0.0f);
		glEnd();  
	glPopMatrix();
	glDisable( GL_TEXTURE_2D );
	
	// HUD
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
		glLoadIdentity();		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();		
			glLoadIdentity();				
			glEnable( GL_TEXTURE_2D );	
			glBindTexture(GL_TEXTURE_2D, 0);
			//glTranslatef(0.0f, -1.0f, 0.0f);
			float xl = -1.0f;
			float xh =  1.0f;
			float yh = -0.75f;
			float yl = -1.0f;
			float pX = 0.02f;
			float pY = 0.02f;
			glColor4f(0.1f, 0.1f, 0.1f, 0.75f);
			glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, yh, 0.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, yh, 0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, yl, 0.0f);
					glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, yl, 0.0f);
			glEnd();

			glPushMatrix();
				glLoadIdentity();
				glTranslatef(xh-pX, yl+pY, 0.0f);
				
				float bw = 0.04f;
				float bh = 0.02f;
				float bp = 0.005f;
				// Health
				glColor4f(0.1f, 1.0f, 0.1f, 0.65f);
				glPushMatrix();				
					for(int i=0; i<10; i++)
					{
						glBegin(GL_QUADS);												
								glTexCoord2f(0.0f, 0.0f); glVertex3f(-bw,  -bh, 0.0f);						
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -bh, 0.0f);						
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);						
								glTexCoord2f(0.0f, 1.0f); glVertex3f(-bw,  0.0f, 0.0f);						
						glEnd();
						glTranslatef(0.0f, bh+bp, 0.0f);
					}
				glPopMatrix();
				glTranslatef(-(bw+2*bp), 0.0f, 0.0f);
				// Energy
				glColor4f(0.1f, 1.0f, 1.0f, 0.65f);
				glPushMatrix();				
					for(int i=0; i<10; i++)
					{
						glBegin(GL_QUADS);												
								glTexCoord2f(0.0f, 0.0f); glVertex3f(-bw,  -bh, 0.0f);						
								glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -bh, 0.0f);						
								glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);						
								glTexCoord2f(0.0f, 1.0f); glVertex3f(-bw,  0.0f, 0.0f);						
						glEnd();
						glTranslatef(0.0f, bh+bp, 0.0f);
					}
				glPopMatrix();
			glPopMatrix();			
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	// BAM!
	if(screenHit && stage.persistHitDraw(delta))
	{
		glPushMatrix();
			glLoadIdentity();		
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();		
				glLoadIdentity();				
				glEnable( GL_TEXTURE_2D );	
				glBindTexture(GL_TEXTURE_2D, 0);
				glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
				glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
				glEnd();			
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		glPopMatrix();			
	}
	else
		if(screenHit = (stage.getPlayerHits() > 0))
			stage.decPlayerHits();
}

bool isCrouched = false;
bool hasCursor = false;
void GLFWCALL processKeys(int key, int action)
{
	if(action == GLFW_RELEASE)
	{
		switch(key)
		{
		case GLFW_KEY_ESC:
			quit();
			break;
		case GLFW_KEY_F2:			
			hasCursor ? glfwDisable(GLFW_MOUSE_CURSOR): glfwEnable(GLFW_MOUSE_CURSOR);			
			hasCursor = !hasCursor;
			break;
		case GLFW_KEY_F3:
			resIdx = (++resIdx) % 5;
			winWidth = resolutions[resIdx][0];
			winHeight = resolutions[resIdx][1];
			glfwSetWindowSize(winWidth, winHeight);
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
	if(action == GLFW_PRESS)
	{
		/*switch(character)
		{		
		}*/
	}
}

void GLFWCALL processMousePos(int x, int y)
{			
	camera.updateNormalized(x, y);
}

void GLFWCALL processMouseButton(int button, int action)
{
	if(action == GLFW_RELEASE)
	{
		blitz::geometry::Triad lookAt = camera.getCurrent();
		switch(button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:				
				//blitz::geometry::Triad lookAt = blitz::geometry::Triad();
				stage.playerFire(blitz::geometry::Triad(lookAt.x * 10.0f, lookAt.y * 5.0f, 0.0f));
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				stage.spawnEnemy(blitz::geometry::Triad(fRand.randFloat(-50.0f, 50.0f), fRand.randFloat(-4.0f, 4.0f), -100.0f), pModel);				
				break;
		}
	}
}