#include "Tema1.h"

//#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;


Tema1::Tema1()
{
}	

Tema1::~Tema1()
{
}



vector<Obstacle> obsDown;//vector obstacole de jos
vector<Obstacle> obsUp;//vector obstacole de sus


void Tema1::Init()
{
	
	glm::ivec2 resolution = window->GetResolution();
	resX = resolution.x;
	resY = resolution.y;
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	
	glm::vec3 corner = glm::vec3(0, 0, 0);
	
	Restart();
	
	//create mesh

	//dreptunghiul vertical din obstacol
	Mesh* rec1 = Object2D::CreateRectangle("rec1", corner, length, height, glm::vec3(0,0,0), true);
	AddMeshToList(rec1);

	//dreptunghiul orizontal din obstacol
	Mesh* rec2 = Object2D::CreateRectangle("rec2", corner, heightBird, lengthBird, glm::vec3(0,0,0), true);
	AddMeshToList(rec2);

	//ciocul
	Mesh* tri = Object2D::CreateTriangle("tri", corner, heightBird/4, lengthBird/4, glm::vec3(1.00,0.49,0.00), true);
	AddMeshToList(tri);

	//aripa
	Mesh* triWing = Object2D::CreateTriangle("triWing", corner, heightBird/2, lengthBird/2, glm::vec3(0.95,0.61,0.73), true);
	AddMeshToList(triWing);
	
	//capul
	Mesh* circle = Object2D::CreateCircle("circle", corner, heightBird/3, glm::vec3(0.69,0.00,0.16), true);
	AddMeshToList(circle);

	//ochiul
	Mesh* circleEye = Object2D::CreateCircle("circleEye", corner, heightBird/16, glm::vec3(0,0,0), true);
	AddMeshToList(circleEye);

	//corpul
	Mesh* circleBody = Object2D::CreateCircle("circleBody", corner, heightBird/2, glm::vec3(0.69,0.00,0.16), true);
	AddMeshToList(circleBody);

	

	ok = 0;
	punctaj = 0;
	
	
}

void Tema1::Restart() {

	
	
	dist = resX/4; //dist intre obstacole
	length = 128;//latime obstacol
	height = 260;//inaltime obstacol
	
	lengthBird = 40;//inaltime pasare
	heightBird = 70;//lungime pasare
	
	srand (static_cast <unsigned> (time(0)));
	
	//stergere elemente vector de obstacole pentru resetare
	if(!obsDown.empty()) {
		
		obsDown.erase(obsDown.begin(),obsDown.end());
	}
	if(!obsUp.empty()) {
		
		obsUp.erase(obsUp.begin(),obsUp.end());
	}
	
	for(int i = 0; i < 4; i++) {
	
		float x = (resY - 80 - 7*lengthBird)/(height + lengthBird);
		float y = 40/(height + lengthBird);
		float r = y + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(x - y)));
		Obstacle o = Obstacle();
		o.Initializeaza(resX/2, dist, height, r, i);
		o.newHeight = height*r;	
		obsDown.push_back(o);
		

		x = (resY - obsDown[i].newHeight - 7*lengthBird)/(height + lengthBird);	
		y = 40/(height + lengthBird);
		o.Initializeaza(resX/2, dist, height, x, i);
		o.newHeight = height*x;	
		obsUp.push_back(o);
		
	}
	
	maxPoint = 2*heightBird/3 + heightBird + heightBird/4;//lungime pasare
	
	angularStep = 0;//unghiul cu care se roteste pasarea
	}
   	void Tema1::print() {
		if(punctaj >= 10)
			printf("Good job! Your score is: %d \n", punctaj);
		else
			printf("LOSER! Your score is: %d \n", punctaj);
	}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1.00,0.88,0.30, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	
	//pasare
	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(resX/128 + heightBird, resY/2 + heightBird);//pozitia la care apare pasarea pe ecran
	
	modelMatrix *= Transform2D::Translate(0, translateBirdY);
	modelMatrix *= Transform2D::Rotate(angularStep);
	//aripa
	modelMatrix *= Transform2D::Translate(-heightBird/4, -heightBird/4);
	RenderMesh2D(meshes["triWing"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= Transform2D::Translate(heightBird/4, heightBird/4);
	//corp
	RenderMesh2D(meshes["circleBody"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= Transform2D::Translate(heightBird/2 + heightBird/4, 0);
	//ochi
    RenderMesh2D(meshes["circleEye"], shaders["VertexColor"], modelMatrix);
	//cap
	RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= Transform2D::Translate(-heightBird - heightBird/3, -lengthBird/2);
	//cioc
	modelMatrix *= Transform2D::Translate(heightBird + heightBird/4 + heightBird/3, lengthBird/2-length/20);
	RenderMesh2D(meshes["tri"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= Transform2D::Translate(- heightBird - heightBird/4 - heightBird/3, -lengthBird/2 + length/20);

	modelMatrix *= Transform2D::Translate(-heightBird/2, translateBirdY - lengthBird/2);//translatare inversa in pozitia initiala
	
	
	//obstacole
	float radius = maxPoint/2;
	float xBird = resX/128 + radius; //coordonata x centru de greutate pasare
	float yBird = resY/2 + radius + translateBirdY; //coordonata Y centru de greutate pasare
	
	//punerea in ecran a celor 4 obstacole
	for(int i = 0; i < 4; i++) {
			obsDown[i].modelMatrix = glm::mat3(1);
			if(ok == 0){
				obsDown[i].translateX += -200*deltaTimeSeconds;
			}
			obsDown[i].modelMatrix *= Transform2D::Translate(obsDown[i].translateX, 0);
			obsDown[i].Scalare();
			RenderMesh2D(meshes["rec1"], shaders["VertexColor"], obsDown[i].scaleMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate (obsDown[i].translateX - 6, obsDown[i].newHeight);
			//modelMatrix *= Transform2D::Translate ((2* heightBird)/2, 0);
			modelMatrix *= Transform2D::Scale(2,1);
			RenderMesh2D(meshes["rec2"], shaders["VertexColor"], modelMatrix);


			
		
			obsUp[i].modelMatrix = glm::mat3(1);
			if(ok == 0) {//daca nu s-a produs o coliziune
				obsUp[i].translateX += -200*deltaTimeSeconds;	
			}
			obsUp[i].modelMatrix *= Transform2D::Translate(obsUp[i].translateX, resY);
			obsUp[i].modelMatrix *= Transform2D::Rotate(3.14);
			obsUp[i].modelMatrix *= Transform2D::Translate(-length, 0);
			obsUp[i].Scalare();	
			RenderMesh2D(meshes["rec1"], shaders["VertexColor"], obsUp[i].scaleMatrix);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate (obsUp[i].translateX - 6, resY - obsUp[i].newHeight - lengthBird);
			//modelMatrix *= Transform2D::Translate ((2* heightBird)/2, 0);
			modelMatrix *= Transform2D::Scale(2,1);
			RenderMesh2D(meshes["rec2"], shaders["VertexColor"], modelMatrix);
			
	}
	
	//reintrarea in scena pe rand a cate un obstacol
	for(int i = 0; i < 4; i++) {
		if(obsDown[i].translateX <= 0) {
			punctaj++;
			obsDown[i].modelMatrix = glm::mat3(1);
			obsDown[i].translateX  = resX;
			obsDown[i].modelMatrix *= Transform2D::Translate (obsDown[i].translateX, 0);
			RenderMesh2D(meshes["rec1"], shaders["VertexColor"], obsDown[i].modelMatrix);
		}
		if(obsUp[i].translateX <= 0) {
			obsUp[i].modelMatrix = glm::mat3(1);
			obsUp[i].translateX = resX;	
			obsUp[i].modelMatrix *= Transform2D::Rotate(3.14);
			obsUp[i].modelMatrix *= Transform2D::Translate(obsUp[i].translateX, resY);
			obsUp[i].modelMatrix *= Transform2D::Translate(-length, 0);
			RenderMesh2D(meshes["rec1"], shaders["VertexColor"], obsUp[i].modelMatrix);

		}

	}
	
	//coliziuni
	for(int i = 0; i < 4; i++) {
		if(xBird + radius >= obsDown[i].translateX && xBird + radius <= obsDown[i].translateX + length) {
			if(yBird - heightBird/2 <= obsDown[i].newHeight + lengthBird || yBird + heightBird/2 >= (resY - obsUp[i].newHeight - lengthBird)) {
				ok = 1; //variabila folosita pentru a semnaliza producerea unei coliziuni
				Restart();
				print();
				break;
			}
		}
		else if(xBird + radius >= obsDown[i].translateX) {
	 		if((yBird + heightBird/2 >= 0 && yBird + heightBird/2 <= obsDown[i].newHeight + lengthBird) || (yBird + heightBird/2 >= 
			 (resY - obsUp[i].newHeight- lengthBird) && yBird + heightBird/2 <= resY)) {
				ok = 1; 
				Restart();
				print();
				break;
			}

		}
	}
	


}		

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{	
	int speed = 200;
	if(window->KeyHold(GLFW_KEY_SPACE)) {
		if(angularStep <= 0.2) {
			angularStep += 2*deltaTime;	
		}
		translateBirdY += 2*speed*deltaTime;

	}
		
	else if(!window->KeyHold(GLFW_KEY_SPACE)) {
		if(angularStep >= -0.2) {
			angularStep -= 1*deltaTime;	
		}	
		if(translateBirdY >= -resY/2 ){
			translateBirdY -= speed*deltaTime;
		}
	}

	
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
	

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
	
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
