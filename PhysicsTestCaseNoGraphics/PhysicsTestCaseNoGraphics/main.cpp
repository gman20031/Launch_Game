#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

//idk what esle to do here, feels like there should be a better way to apply a system wide number, like in a class somewhere.
// but I dont feel like I should just pass around the current value of gravity all the time.
double kGravityForce = 10; // REPLACE

#define Print(str) std::cout << str << std::endl;
#define Gather(inVar) std::cin >> inVar 

struct Vector2
{
	double xComponent = 0;
	double yComponent = 0;
	double direction = 0;
	double magnitude = 0;

	void GetDirection();
	void GetMagnitude();
	void GetX();
	void GetY();

	void GetDirection()
	{
		direction = std::atan2(xComponent, yComponent);
	}//get Dir x,y

	void GetMagnitude()
	{
		magnitude = std::sqrt((pow(xComponent, 2) + pow(yComponent, 2)));
	}//get mag

	void GetX() {
		xComponent = magnitude * std::sin(direction);
	}//getx

	void GetY() {
		xComponent = magnitude * std::cos(direction);
	}//gety

};

struct RigidBody
{

	Vector2 velocity;
	int xPos = 0;
	int yPos = 0;
	char displayer = '@';
	double mass = 1;
	double weight = mass * kGravityForce;
	double accelleration = 0;

	void AddForce_X(double force);
	void AddForce_Y(double force);

	void AddForce_X(double force)
	{
		velocity.xComponent += force;
	}

	void AddForce_Y(double force)
	{
		velocity.yComponent += force;
	}

};

class TheWorld
{
	double ForceOfGravity = 10

	void doPhysics(RigidBody newRigidBody);
};

struct TestContraints
{
	double ForceX = 0;
	double ForceY = 0;
};

TestContraints GetParameters();

void DoPhysicsLol();

int main()
{
	TestContraints parameters = GetParameters();


	return 0;
}

TestContraints GetParameters()
{
	TestContraints params;
	Print("input xforce");
	Gather(params.ForceX);
	Print("input yforce");
	Gather(params.ForceY);
	return params;
}