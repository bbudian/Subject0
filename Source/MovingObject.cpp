#include "stdafx.h"
#include "Headers\MovingObject.h"


MovingObject::MovingObject(void)
{
	pos[X] = pos[Y] = 0.0f;
}


MovingObject::~MovingObject(void)
{
}

void MovingObject::Update(float dt){

}

void MovingObject::Input(){
	if(GetAsyncKeyState('A'))
		pos[X] -= 0.05f;
	if(GetAsyncKeyState('D'))
		pos[X] += 0.05f;
	if(GetAsyncKeyState('W'))
		pos[Y] += 0.05f;
	if(GetAsyncKeyState('S'))
		pos[Y] -= 0.05f;
}
