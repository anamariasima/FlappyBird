#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Transform2D.h"

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;
		void Restart();
		void print();

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		float translateBirdY;
		float radius;
		float angularStep;
		float length, height, lengthBird, heightBird;
		int punctaj;
		int dist;
		int ok;
		float maxPoint;
		float resX, resY;
	
};

class Obstacle 
{
	
	public:
		float translateX;
		
		float scaleY;
		float newHeight;//inaltime dupa scalare
		glm::mat3 modelMatrix;
		glm::mat3 scaleMatrix;
		
		void Scalare() {
			
			scaleMatrix = modelMatrix * Transform2D::Scale(1, scaleY);
		}
		Obstacle(){

		}
		void Initializeaza(float maxX, int dist, int height, float r, int i)
		{	
			translateX = maxX + i*dist;
			newHeight = height;
			scaleY = r;
		}
};
