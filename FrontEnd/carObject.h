#pragma once
# include <GL\glew.h>
# include <glm.hpp>
# include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "NewTypes.h"
# include <vector>
class carObject
{
public:
	double maxSpeed = 2, minSpeed = 0.5f;
	double currSpeed = 0.5f;
	bool objInFace = false;
	GLfloat rotation = 0.0f;
	GLfloat speed = 1.0f;
	std::vector <SuperPipeLine *>*pipe = nullptr;
	glm::vec2 finalPosition;
	glm::vec2 position;
	carObject **carsList = nullptr;
	int carListLim = 1;
	int exceptedCar = -1;
	carObject *carinFace = nullptr;
	carObject();
	carObject(char *texture,glm::vec2 position, glm::vec2 finalposition,SpriteRenderer *renderer);
	void Move();
	void Draw();
	~carObject();


	bool shouldStop = false;
private:
	float a, b;
	
	
	char *texture = nullptr;
	SpriteRenderer *Renderer;
	

	void CalculateEcuation();
	float DistanceRemain();
	_position calculate_p(double unit, _position initial, _position final);
	void CalculateSpeed();
	void GetObstacle();

};

