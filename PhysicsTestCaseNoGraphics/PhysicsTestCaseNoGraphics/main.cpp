#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "PhysicsObject.h"

#define Print(str) std::cout << str << std::endl;

class World {
	const double m_kWorldGravity = -10;
	const double m_kWorldLength = 1000;
	const double m_kWorldHeight = 1000;
	const int m_kStepsPerSecond = 60;

public:
	std::vector<PhysicsObject> m_physicsObjects; // make private

	void CreatePhysicsObject(double XStart, double Ystart, double mass);
	void AllStepPhysics();
};

// For every Object in world, steps through and executes physics on it.
void World::AllStepPhysics()
{
	for (int i = 0; i < m_physicsObjects.size(); ++i)
	{
		PhysicsObject& currentObject = m_physicsObjects.at(i);
		currentObject.AddForce_Y((currentObject.GetMass() * m_kWorldGravity)/ m_kStepsPerSecond);
		currentObject.updateLocationFromForce(m_kStepsPerSecond);
		if (currentObject.GetLocation_Y() < 0)
		{
			currentObject.SetLocation(currentObject.GetLastLocation_X(), 0);
			currentObject.SetVelocity(0, 0);
		}
		currentObject.SetLastLocation(currentObject.GetLocation_X(), currentObject.GetLocation_Y());
	}

}

void World::CreatePhysicsObject(double XStart, double Ystart, double mass)
{
	PhysicsObject newObject(XStart, Ystart, mass);
	m_physicsObjects.push_back(newObject);
}

int main()
{
	World myWorld;
	
	//create test object at 10,10 with mass 1. then fill in forces applied with simple text
	myWorld.CreatePhysicsObject(10, 10, 1);
	double xForce;
	double yForce;
	int steps;
	std::cout << "x force" << std::endl;
	std::cin >> xForce;
	std::cout << "y force" << std::endl;
	std::cin >> yForce;
	std::cout << "steps" << std::endl;
	std::cin >> steps;

	system("pause");

	std::ofstream coordinateFile("coordinates.txt");
	if (coordinateFile.is_open())
	{
		// give the object its initial kick
		myWorld.m_physicsObjects.at(0).AddForce_X(xForce);
		myWorld.m_physicsObjects.at(0).AddForce_Y(yForce);

		
		double tempX;
		double tempY;
		
		for (int i = 0; i < steps; ++i)
		{
			myWorld.AllStepPhysics();
			tempX = myWorld.m_physicsObjects.at(0).GetLocation_X();
			tempY = myWorld.m_physicsObjects.at(0).GetLocation_Y();
			coordinateFile << '(' << tempX << ',' << tempY << ')' << std::endl;
		}

		
	}//write coordinates files

	system("pause");

	return 0;
}
