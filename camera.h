// "camera.h" evaulates intersection of object and camera and calculate position and dimension of rendered part of object on screen
// camera and object are instance in world with coordinates x and y and dimension w and h
// input parameters are SDL rectangle of object and camera position + dimension
// "camera." returns SDL rectangles targerRect - destination and textureRect - source which can be used in SDL_RenderCopy()
// #define SWITCH swaps 4 nested if-else for 1 switch
#ifndef CAMERA_H
#define CAMERA_H
#include <SDL.h>
#include <cstdint>
#define SWITCH
class camera
{
private:
	SDL_Rect cameraRect; //camera position and dimension in world
	SDL_Rect objectRect; //object position and dimension in world
	SDL_Rect textureRect; //part of object
	SDL_Rect targetRect; //part of window

#ifndef SWITCH
	bool A; //left edge
	bool B; //top edge
	bool C1; //right edge
	bool D1; //bottom edge
#endif // !SWITCH

#ifdef SWITCH
	int flag;
	const std::uint8_t maskA{ 0b1000 }; //left edge
	const std::uint8_t maskC1{ 0b0100 }; //right edge
	const std::uint8_t maskB{ 0b0010 }; //top edge
	const std::uint8_t maskD1{ 0b0001 }; //bottom edge
#endif //SWITCH

#ifdef SWITCH
//reworked canRender(), createBools(), xwFunction() and yhFunction() to function with switch()
//return false if obhect is outside of camera
	bool foo();
#endif // SWITCH

public:
	//camera position and dimension in world
	camera(int x, int y, int w, int h); 
	~camera();

	//input paramater is rectangle of object
	//return false if object is outside of the camera
	//function update output rectangles in the class
	bool inputObjectRect(const SDL_Rect& objRect);

#ifndef SWITCH
	//return false if object is outside of the camera
	bool canRender();
	//intialize bools A B C1 D1
	void createBools();
	//calculate x and w of output rectangles
	void xwFunction();
	//calculate y and h of output rectangles
	void yhFunction();
#endif // !SWITCH

	//return rectangle for object - source
	const SDL_Rect& outputTextureRect();
	//return rectangle for camera - destination
	const SDL_Rect& outputTargetRect();
	//return rectangle of camera position and dimension in world
	const SDL_Rect& outputCameraRect();
	//change position of camera in world
	void cameraMovement(int x,int y);
};
#endif

