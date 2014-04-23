#pragma once
class MovingObject
{
	//To be converted to a Vector2 class
	float pos[2];

public:
	enum PositionComponents {X,Y,NUM_COMPONENTS};
	MovingObject(void);
	~MovingObject(void);

	void Update(float dt);
	void Input();
	float GetPosX() {return pos[X];}
	float GetPosY() {return pos[Y];}


};

