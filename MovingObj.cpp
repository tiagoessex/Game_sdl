
#include "MovingObj.h"

MovingObj::MovingObj(double speed, double direction)
{
	this->speed = speed;
	this->direction = direction;
}

void MovingObj::setSpeed(double speed)
{
	this->speed = speed;
}

void MovingObj::setDirection(double direction)
{
	this->direction = direction;
}


double MovingObj::getSpeed()
{
	return speed;
}

double MovingObj::getDirection()
{
	return direction;
}
