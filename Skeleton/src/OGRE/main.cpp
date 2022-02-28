#include "OgreRenderer.h"

int main()
{
	OgreRenderer main = OgreRenderer();
	main.exampleScene();

	while (main.update()) {};
 
	return true;
}