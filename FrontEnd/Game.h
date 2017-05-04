#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
# include "ResourceManager.h"
# include "SpriteRenderer.h"
# include "Lista.h"
# include "carObject.h"


#define PI 3.14159265

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
	//utilitis functions
public:
	void GetMatrix(int n, int m, int **mat);

public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;
	std::vector<SuperPipeLine*> mainPipe;
	std::vector<SuperPipeLine*> *secondPipe;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init(glm::vec2 mainCarPoz, glm::vec2 mainCarDestPoz);
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
//Drawing functions
private:
	void DrawStreets();
	void DrawCars();
	//private workers
private:
	GLfloat CalculateDegrees(Nod *nod);
	void MoveCars();
	Nod *CreateNod(glm::vec2 start, glm::vec2 final);
	//public workers
public:
	void GetLista(Lista *list);
	//graphic variables
private:
	SpriteRenderer *Renderer = nullptr;

	//backend variables
private:
	int n, m, **matrix;
	Lista *lista = nullptr;
	carObject *maincar;
	carObject **cars;
};
