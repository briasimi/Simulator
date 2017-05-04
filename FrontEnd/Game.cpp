#include "Game.h"



void Game::GetMatrix(int n, int m, int ** mat)
{
	this->n = n;
	this->m = m;
	this->matrix = mat;
}

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init(glm::vec2 mainCarPoz,glm::vec2 mainCarDestPoz)
{
	// Load shaders
	ResourceManager::LoadShader("vertex2d.in", "fragment2d.in", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("simpleroad.jpg", GL_TRUE, "singledotted");
	ResourceManager::LoadTexture("Doubleroad.jpg", GL_TRUE, "double");
	ResourceManager::LoadTexture("car.png", GL_TRUE, "car");
	ResourceManager::LoadTexture("gira.jpg", GL_TRUE, "giro");
	ResourceManager::LoadTexture("map.jpg", GL_TRUE, "map");
	//ResourceManager::LoadTexture("gira.png", GL_TRUE, "uni");
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	maincar = new carObject("car", mainCarPoz,mainCarDestPoz, Renderer);
	maincar->pipe = &mainPipe;
	secondPipe = new std::vector<SuperPipeLine*>[1];
	cars = new carObject*[1];
	cars[0] = new carObject("car", mainCarDestPoz, glm::vec2(500, 150), Renderer);
	cars[0]->rotation = CalculateDegrees(CreateNod(mainCarDestPoz, glm::vec2(500, 150)));
	cars[0]->pipe = &secondPipe[0];
	cars[0]->maxSpeed = 1.0f;
	cars[0]->carsList = cars;
	cars[0]->carListLim = 0;
	maincar->carListLim = 1;
	maincar->carsList = cars;
}

void Game::Update(GLfloat dt)
{
	MoveCars();
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
	DrawStreets();
	DrawCars();
}

void Game::DrawStreets()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("map"), glm::vec2(0, 0), glm::vec2(1900, 1000),0);
	//int len = lista->size();
	//float size = 0;
	//Nod *aux;
	//for (int i = 0;i < len;i++)
	//{
	//	aux = (*lista)[i];
	//	/*size = abs(aux->xFinal - aux->xStart) * 50;
	//	if (size==0)
	//		size = abs(aux->yFinal - aux->yStart) * 50;*/
	//	size = sqrt((aux->xStart - aux->xFinal)*(aux->xStart - aux->xFinal) + (aux->yFinal - aux->yStart)*(aux->yFinal - aux->yStart))*50;
	//	if (aux->type==0)
	//		Renderer->DrawSprite(ResourceManager::GetTexture("singledotted"), glm::vec2(aux->xStart*50, aux->yStart*50), glm::vec2(size, 50), CalculateDegrees(aux));
	//	else
	//		Renderer->DrawSprite(ResourceManager::GetTexture("double"), glm::vec2(aux->xStart * 50, aux->yStart * 50), glm::vec2(size, 100), CalculateDegrees(aux));
	//	//Renderer->DrawSprite(ResourceManager::GetTexture("giro"), glm::vec2(10* 50, 10 * 50), glm::vec2(50, 50), 0);
	//	
	//}
	
}

void Game::DrawCars()
{
	maincar->Draw();
	cars[0]->Draw();
}

GLfloat Game::CalculateDegrees(Nod *nod)
{
	double y = nod->yStart - nod->yFinal;
	double x= nod->xStart - nod->xFinal;
	float result = std::atan2(y, x)*180/PI;
	/*if (result < 0)
		result = 360.0f - result;
	else
		result = 360.0f + result;*/
	result -= 180.0f;
	//result = 360.0f - result;
	if (result == 360.0f)
		result = 0.0f;
	//std::cout << result << endl;
	GLfloat retval = result;
	return retval;
}

void Game::MoveCars()
{
	maincar->Move();
	cars[0]->Move();
}

Nod * Game::CreateNod(glm::vec2 start, glm::vec2 final)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	x1 = start.x;
	x2 = start.y;
	y1 = final.x;
	y2 = final.y;
	streetTypes t = singleContinuous;
	Nod *a = new Nod(x1, x2, y1, y2, t);
	return a;
}

void Game::GetLista(Lista * list)
{
	lista = list;
}
