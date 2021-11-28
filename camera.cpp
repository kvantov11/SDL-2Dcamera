#include "camera.h"
#include <SDL.h>
#include <cstdint>

#define SWITCH
camera::camera(int x = 0, int y = 0, int w = 0, int h = 0)
{
	cameraRect = { x,y,w,h };
	objectRect = { 0,0,0,0 };
	textureRect = { 0,0,0,0 };
	targetRect = { 0,0,0,0 };

#ifndef SWITCH
	A = false;
	B = false;
	C1 = false;
	D1 = false;
#endif // !SWITCH

#ifdef SWITCH
	flag = 0;
#endif // SWITCH
}

camera::~camera()
{
	cameraRect = { 0,0,0,0 };
	objectRect = { 0,0,0,0 };
	textureRect = { 0,0,0,0 };
	targetRect = { 0,0,0,0 };

#ifndef SWITCH
	A = false;
	B = false;
	C1 = false;
	D1 = false;
#endif // !SWITCH

#ifdef SWITCH
	flag = 0;
#endif // SWITCH
}

// main function return false if intersection of camera and object was not found
bool camera::inputObjectRect(const SDL_Rect& objRect) 
{ 
	objectRect = objRect;
#ifndef SWITCH
	if (!canRender()) return false;
	else
	{
		createBools();
		xwFunction();
		return true;
	}
#endif // !SWITCH	

#ifdef SWITCH
	return foo();
#endif // SWITCH	
}

#ifndef SWITCH
bool camera::canRender()
{
	//!C
	if (!(cameraRect.x + cameraRect.w >= objectRect.x)) return false;
	//A1
	if (cameraRect.x >= objectRect.x + objectRect.w) return false;
	//!D
	if (!(cameraRect.y + cameraRect.h >= objectRect.y)) return false;
	//B1
	if (cameraRect.y >= objectRect.y + objectRect.h) return false;
	return true;
}

void camera::createBools()
{
	//A
	if (cameraRect.x >= objectRect.x) A = true;
	else A = false;
	//C1
	if (cameraRect.x + cameraRect.w >= objectRect.x + objectRect.w)	C1 = true;
	else C1 = false;
	//B
	if (cameraRect.y >= objectRect.y) B = true;
	else B = false;
	//D1
	if (cameraRect.y + cameraRect.h >= objectRect.y + objectRect.h) D1 = true;
	else D1 = false;
}

void camera::xwFunction()
{
	if (A)
	{
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		if (!C1)
		{
			textureRect.w = cameraRect.w;
			targetRect.w = cameraRect.w;
			yhFunction();
		}
		else
		{
			textureRect.w = objectRect.x + objectRect.w - cameraRect.x;
			targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
			yhFunction();
		}
	}
	else
	{
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		if (!C1)
		{
			textureRect.w = cameraRect.x + cameraRect.w - objectRect.x;
			targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
			yhFunction();
		}
		else
		{
			textureRect.w = objectRect.w;
			targetRect.w = objectRect.w;
			yhFunction();
		}
	}
}

void camera::yhFunction()
{
	if (B)
	{
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		if (!D1)
		{
			textureRect.h = cameraRect.h;
			targetRect.h = cameraRect.h;
		}
		else
		{
			textureRect.h = objectRect.y + objectRect.h - cameraRect.y;
			targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		}
	}
	else
	{
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		if (!D1)
		{
			textureRect.h = cameraRect.y + cameraRect.h - objectRect.y;
			targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		}
		else
		{
			textureRect.h = objectRect.h;
			targetRect.h = objectRect.h;
		}
	}
}
#endif // !SWITCH

const SDL_Rect& camera::outputTextureRect() { return textureRect; }
const SDL_Rect& camera::outputTargetRect() { return targetRect; }
const SDL_Rect& camera::outputCameraRect() { return cameraRect; }

void camera::cameraMovement(int x = 0, int y = 0)
{
	cameraRect.x += x;
	cameraRect.y += y;
}

#ifdef SWITCH
bool camera::foo()
{
	//!C
	if (!(cameraRect.x + cameraRect.w >= objectRect.x)) return false;
	//A1
	if (cameraRect.x >= objectRect.x + objectRect.w) return false;
	//!D
	if (!(cameraRect.y + cameraRect.h >= objectRect.y)) return false;
	//B1
	if (cameraRect.y >= objectRect.y + objectRect.h) return false;

	flag = 0;
	//A
	if (cameraRect.x >= objectRect.x) flag |= maskA;
	//B
	if (cameraRect.y >= objectRect.y) flag |= maskB;
	//C1
	if (cameraRect.x + cameraRect.w >= objectRect.x + objectRect.w)	flag |= maskC1;
	//D1
	if (cameraRect.y + cameraRect.h >= objectRect.y + objectRect.h) flag |= maskD1;

	switch (flag)
	{
		
	case 0b1111://(A) (C1) (B) (D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = objectRect.x + objectRect.w - cameraRect.x;
		targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = objectRect.y + objectRect.h - cameraRect.y;
		targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		break;
	case 0b1110://(A) (C1) (B) (!D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = objectRect.x + objectRect.w - cameraRect.x;
		targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = cameraRect.h;
		targetRect.h = cameraRect.h;
		break;
	case 0b1101://(A) (C1) (!B) (D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = objectRect.x + objectRect.w - cameraRect.x;
		targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = objectRect.h;
		targetRect.h = objectRect.h;
		break;
	case 0b1100://(A) (C1) (!B) (!D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = objectRect.x + objectRect.w - cameraRect.x;
		targetRect.w = objectRect.x + objectRect.w - cameraRect.x;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		break;
	case 0b1011://(A) (!C1) (B) (D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = cameraRect.w;
		targetRect.w = cameraRect.w;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = objectRect.y + objectRect.h - cameraRect.y;
		targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		break;
	case 0b1010://(A) (!C1) (B) (!D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = cameraRect.w;
		targetRect.w = cameraRect.w;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = cameraRect.h;
		targetRect.h = cameraRect.h;
		break;
	case 0b1001://(A) (!C1) (!B) (D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = cameraRect.w;
		targetRect.w = cameraRect.w;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = objectRect.h;
		targetRect.h = objectRect.h;
		break;
	case 0b1000://(A) (!C1) (!B) (!D1)
		textureRect.x = cameraRect.x - objectRect.x;
		targetRect.x = 0;
		textureRect.w = cameraRect.w;
		targetRect.w = cameraRect.w;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		break;
	case 0b0111://(!A) (C1) (B) (D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = objectRect.w;
		targetRect.w = objectRect.w;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = objectRect.y + objectRect.h - cameraRect.y;
		targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		break;
	case 0b0110://(!A) (C1) (B) (!D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = objectRect.w;
		targetRect.w = objectRect.w;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = cameraRect.h;
		targetRect.h = cameraRect.h;
		break;
	case 0b0101://(!A) (C1) (!B) (D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = objectRect.w;
		targetRect.w = objectRect.w;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = objectRect.h;
		targetRect.h = objectRect.h;
		break;
	case 0b0100://(!A) (C1) (!B) (!D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = objectRect.w;
		targetRect.w = objectRect.w;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		break;
	case 0b0011://(!A) (!C1) (B) (D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = objectRect.y + objectRect.h - cameraRect.y;
		targetRect.h = objectRect.y + objectRect.h - cameraRect.y;
		break;
	case 0b0010://(!A) (!C1) (B) (!D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		textureRect.y = cameraRect.y - objectRect.y;
		targetRect.y = 0;
		textureRect.h = cameraRect.h;
		targetRect.h = cameraRect.h;
		break;
	case 0b0001://(!A) (!C1) (!B) (D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = objectRect.h;
		targetRect.h = objectRect.h;
		break;
	case 0b0000://(!A) (!C1) (!B) (!D1)
		textureRect.x = 0;
		targetRect.x = objectRect.x - cameraRect.x;
		textureRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		targetRect.w = cameraRect.x + cameraRect.w - objectRect.x;
		textureRect.y = 0;
		targetRect.y = objectRect.y - cameraRect.y;
		textureRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		targetRect.h = cameraRect.y + cameraRect.h - objectRect.y;
		break;
	}
	return true;
}
#endif // SWITCH