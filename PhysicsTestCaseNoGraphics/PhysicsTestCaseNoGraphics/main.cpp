#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <time.h>
#include "Physics.h"

//idk what esle to do here, feels like there should be a better way to apply a system wide number, like in a class somewhere.
// but I dont feel like I should just pass around the current value of gravity all the time.

#define Print(str) std::cout << str << std::endl;

class World {
	const double m_kWorldGravity = -10;
	const double m_kWorldLength = 1000;
	const double m_kWorldHeight = 1000;
	//static bool m_phyStarted;

public:
	std::vector<PhysicsObject> m_physicsObjects; // make private

	World() {
		//m_phyStarted = false;
	}
	~World() {}

	void CreatePhysicsObject(double XStart, double Ystart, double mass);
	void StartPhysics();
	void StepPhysics();
};

void World::StepPhysics()
{
	for (int i = 0; i < m_physicsObjects.size(); ++i)
	{
		PhysicsObject& currentObject = m_physicsObjects.at(i);
		currentObject.AddForce_Y(m_kWorldGravity);
		if (currentObject.m_location.yPosition < 0)
			currentObject.SetVelocity(0, 0);
		currentObject.updateLocationFromForce();
		currentObject.PrintLocation();
	}
}

//void World::StartPhysics()
//{
//	m_phyStarted = true;
//
//}

void World::CreatePhysicsObject(double XStart, double Ystart, double mass)
{
	PhysicsObject newObject(XStart, Ystart, mass);
	m_physicsObjects.push_back(newObject);
}

int main()
{
	double xForce;
	double yForce;

	World myWorld;

	//std::cout << "x force" << std::endl;
	//std::cin >> xForce;
	//std::cout << "y force" << std::endl;
	//std::cin >> yForce;

	myWorld.CreatePhysicsObject(10, 10, 1);

	system("pause");

	
	bool keepRunning = true;
	//myWorld.StartPhysics();
	myWorld.m_physicsObjects.at(0).AddForce_X(50);
	myWorld.m_physicsObjects.at(0).AddForce_Y(100);
	//unsigned int currentTime = time(0);
	int count = 0;
	while(keepRunning)
	{
		myWorld.StepPhysics();
		++count;
		if (count >= 30)
			keepRunning = false;
	}
	system("pause");


	return 0;
}
