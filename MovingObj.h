#ifndef MovingObj_h
#define MovingObj_h


class MovingObj
{
public:
	MovingObj(double speed, double direction);

	void setSpeed(double speed);
	void setDirection(double direction);

	double getSpeed();
	double getDirection();

private:
	double speed;
	double direction;

};



#endif