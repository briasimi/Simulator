#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"
# include "Lista.h"
# include "TcpProtocol.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 1900;
// The height of the screen
const GLuint SCREEN_HEIGHT = 1000;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);
int n = 40, m = 76,**matrix;
Lista *lista;
void generateMatrix()
{
	matrix = new int*[n];
	for (int i = 0;i < n;i++)
	{
		matrix[i] = new int[m];
		for (int j = 0;j < m;j++)
			matrix[i][j] = 2;
	}
}
void GetStreets()
{
	lista = new Lista();
	lista->push_back(0, 1, 26, 1,singleDotted);
	lista->push_back(0, 3, 26, 3, singleDotted);
	lista->push_back(26,1 ,30 ,1 , singleDotted);
	lista->push_back(30, 1,34 , 2, singleDotted);
	lista->push_back(34, 2, 38, 2, singleDotted);
	lista->push_back(26, 3, 30, 3, singleDotted);
	lista->push_back(30, 3, 34, 2, singleDotted);


	//lista->push_back(, , , , singleDotted);
	/*lista->push_back(0, 10, 10, 10, singleDotted);
	lista->push_back(10, 10, 20, 20, singleDotted);
	lista->push_back(20, 15, 38, 15, singleDotted);*/
	//lista->push_back(10, 15, 20, 11, singleDotted);
}
 
int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	Breakout.Init(glm::vec2(0,50), glm::vec2(500, 50));

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// Start Game within Menu State
	Breakout.State = GAME_ACTIVE;
	/*TcpProtocol prot;
	prot.SetServerConfiguration("192.168.0.124", "20000");
	int m, n, **x;
	Lista *list = prot.RetrivingPrimariData();
	list->print();
	prot.SetPositions("1", "2", " 3", "4");*/
	//char *map = prot.GetMap("map1");

	GetStreets();
	Breakout.GetLista(lista);
	SuperPipeLine *a = new SuperPipeLine();
	a->nextPosition = glm::vec2(500, 150);
	a->nextRotation = 90.0f;
	Breakout.mainPipe.push_back(a);
	
	a = new SuperPipeLine();
	a->nextPosition = glm::vec2(1000, 150);
	a->nextRotation = 0.0f;
	Breakout.mainPipe.push_back(a);
	Breakout.secondPipe[0].push_back(a);
	a = new SuperPipeLine();
	a->nextPosition = glm::vec2(1000,15*50);
	a->nextRotation = 90.0f;
	Breakout.mainPipe.push_back(a);
	Breakout.secondPipe[0].push_back(a);
	a = new SuperPipeLine();
	a->nextPosition = glm::vec2(1900, 15 * 50);
	a->nextRotation = 0.0f;
	Breakout.mainPipe.push_back(a);
	Breakout.secondPipe[0].push_back(a);

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();

		
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		Breakout.ProcessInput(deltaTime);

		// Update Game state
		Breakout.Update(deltaTime);

		// Render
		glClearColor(0.85f, 0.85f, 0.85f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}