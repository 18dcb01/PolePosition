#pragma once
#include "Car.h"
class Player :
	public Object
{
public:
	Player();
	~Player();

	void tick();
	void drawDashboard();

private:
	vector<Sound>;
};