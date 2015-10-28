
#include "CastleEngine.h"
#include "Triangle.h"
#include "Camera.h"
#include "Robot.h"
#include "Floor.h"
#include "Tree.h"
#include "Light.h"
#include "Castle.h"
#include "Sun.h"
#include "StreetLight.h"
#include "Skybox.h"

#include <cmath>
CastleEngine::CastleEngine( int argc, char **argv, const char *title, const int windowWidth, const int windowHeight ) : Engine(argc, argv, title, windowWidth, windowHeight)
{

}

CastleEngine::~CastleEngine()
{

}

void CastleEngine::Init()
{
	// add camera
	Camera *c = new Camera();
	AddCameraToScene(c);

	Skybox* sb = new Skybox(c);
    AddObjectToScene(sb);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	Floor *floor = new Floor( 10.0, 10.0, 0.0, 0.0, 0.0, 4.0, "./grass.bmp");

	AddObjectToScene(floor);

	//add light
	for (int i = 0; i < 6; i+=2) {
		StreetLight *l1 = new StreetLight(c,-4,0,i*(-10) - 5 ,i,0);
		StreetLight *l2 = new StreetLight(c,4,0,i*(-10) - 5,i + 1,1);
		AddObjectToScene(l1);
		AddObjectToScene(l2);

	}

	//add castle
	Castle *castle = new Castle(0, 0, -90, "./wall1.bmp");
	AddObjectToScene(castle);

	//add trees
	for (int j = 0; j < 5; j++) {

		for(int i = 0; i < 5; i++){ 
			Tree *tree1 = new Tree(-3 - j%2 + i*(-2),0, -60 + j *3);
			AddObjectToScene(tree1);

			Tree *tree2 = new Tree( 3 +j%2  + i*(2),0,-60+ j *3);
			AddObjectToScene(tree2);

		}
	}

	//add robot
	for (int i = 0; i < 8; i+=1) {
		Robot *r1 = new Robot(rand() % 70 - 50,0,10 - rand()%70,rand() % 4);
		AddObjectToScene(r1);
	}
}
