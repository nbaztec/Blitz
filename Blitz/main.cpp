/*
 * main.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <GL/glfw.h>


#include "Core\Stage.hpp"
#include "Core\Camera.hpp"
#include "Core\Coordinate.hpp"
#include "Core\Point.hpp"
#include "Util\TextureManager.hpp"
#include "Util\Randomizer.hpp"


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
int winWidth = 1280;
int winHeight = 720;
blitz::Stage stage;
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

void gameLoop()
{
	DWORD next_game_tick = GetTickCount();
	int loops;
	unsigned long now = 0;
	double old_time = GetTickCount();
	float t = 0;
	float delta = 0.0f;

	while(glfwGetWindowParam(GLFW_OPENED))
	{		
		loops = 0;		
		while((now = GetTickCount()) > next_game_tick && loops < MAX_FRAMESKIP)
		{
			delta = float(now - old_time)/1000.0f;
			if(delta)
				old_time = now;			
			stage.tick(delta);
			next_game_tick += SKIP_TICKS;
			loops++;

		}
		renderScene();
		glfwSwapBuffers();
	}
}

void quit(void)
{
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glAlphaFunc(GL_GREATER, 0.0f);
	glEnable(GL_ALPHA_TEST);
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
	camera = blitz::Camera(blitz::geometry::Triad(), blitz::geometry::Dyad(float(winWidth), float(winHeight)), blitz::geometry::Quad(-5.0f, -0.5f, 5.0f, 2.0f), false);
	for(int i=0; i<50; i++)
		starMap.push_back(blitz::geometry::Dyad(fRand.randFloat(2.0f, 6.0f), fRand.randFloat(-1.0f, 1.0f)));		
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
/*
#define mathsInnerProduct(v,q)\
	( ((v)[0] * (q)[0]) +\
	  ((v)[1] * (q)[1]) +\
	  ((v)[2] * (q)[2])  )	



#define mathsCrossProduct(a,b,c)\
	(a)[0] = ((b)[1] * (c)[2]) - ((c)[1] * (b)[2]);\
	(a)[1] = ((b)[2] * (c)[0]) - ((c)[2] * (b)[0]);\
	(a)[2] = ((b)[0] * (c)[1]) - ((c)[0] * (b)[1]);


#include <cmath>
inline void mathsNormalize(float* v){  
    int d = std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);  
    v[0] /= d;  
	v[1] /= d;
    v[2] /= d;
}  

void billboardCylindricalBegin(
			float camX, float camY, float camZ,
			float lookAtX, float lookAtY, float lookAtZ,
			float objPosX, float objPosY, float objPosZ) {

	float lookAt[3],objToCamProj[3],upAux[3];
	float modelview[16],angleCosine;
	
	glPushMatrix();

// objToCamProj is the vector in world coordinates from the 
// local origin to the camera projected in the XZ plane
	objToCamProj[0] = camX - objPosX ;
	objToCamProj[1] = 0;
	objToCamProj[2] = camZ - objPosZ ;

// This is the original lookAt vector for the object 
// in world coordinates
	lookAt[0] = lookAtX;
	lookAt[1] = lookAtY;
	lookAt[2] = lookAtZ;


// normalize both vectors to get the cosine directly afterwards
	mathsNormalize(objToCamProj);

// easy fix to determine wether the angle is negative or positive
// for positive angles upAux will be a vector pointing in the 
// positive y direction, otherwise upAux will point downwards
// effectively reversing the rotation.

	mathsCrossProduct(upAux,lookAt,objToCamProj);

// compute the angle
	angleCosine = mathsInnerProduct(lookAt,objToCamProj);

// perform the rotation. The if statement is used for stability reasons
// if the lookAt and objToCamProj vectors are too close together then 
// |angleCosine| could be bigger than 1 due to lack of precision
   if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
      glRotatef(acos(angleCosine)*180/3.14,upAux[0], upAux[1], upAux[2]);	
}
*/
void renderScene(void)
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		
	// Set the camera
	blitz::geometry::Triad lookAt = camera.getCurrent();
	glTranslatef(0.0f, 0.0f, -10.0f);
	//glPushMatrix();	
	gluLookAt(	lookAt.x * 10.0f, -lookAt.y * 5.0f, 10.0f,							
				lookAt.x * 10.0f, -lookAt.y * 5.0f,  0.0f,		
				0.0f, 1.0f,  0.0f);	
	
	//glPopMatrix();
	//glMatrixMode (GL_MODELVIEW);
	glDisable(GL_DEPTH_TEST);
	glPushMatrix ();
		glLoadIdentity();		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();		
			glLoadIdentity();				
			glEnable( GL_TEXTURE_2D );	
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
	//glMatrixMode(GL_MODELVIEW);
	
	
	glEnable(GL_DEPTH_TEST);
		
	// Draw here
	//glDisable(GL_DEPTH_TEST);		
	
	//glBindTexture(GL_TEXTURE_2D, texMgr["enemy"].first());
	/*
	glPushMatrix();		
		glTranslatef(-150.0f, 0.0f, -10.0f);		
		for(std::vector<blitz::geometry::Dyad>::iterator it = starMap.begin(); it != starMap.end(); it++)
		{			
			glTranslatef(it->x, -it->y, 0.0f);
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
			drawStar();
		}
	glPopMatrix();
	*/
	//glBindTexture(GL_TEXTURE_2D, texMgr["star"].first());
	stage.draw();

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
	/*
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
	*/
}

bool isCrouched = false;
void GLFWCALL processKeys(int key, int action)
{
	if(action == GLFW_RELEASE)
	{
		switch(key)
		{
		case GLFW_KEY_ESC:
			quit();
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
				stage.playerFire(blitz::geometry::Triad(lookAt.x * 10.0f, lookAt.y * 5.0f, -20.0f));
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				stage.spawnEnemy(blitz::geometry::Triad(fRand.randFloat(-50.0f, 50.0f), fRand.randFloat(-4.0f, 4.0f), 80.0f));				
				break;
		}
	}
}