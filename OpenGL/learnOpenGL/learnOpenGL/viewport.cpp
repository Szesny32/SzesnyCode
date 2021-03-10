#include "include.h"
#include "viewport.h"
void resizeViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
