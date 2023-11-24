#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <math.h>
#include <ratio>
#include <thread>
#include "PhysicsObject.h"

#define Print(str) std::cout << str << std::endl;

class World {
	const int kMircosecondsPerSecond = 100000;
	const double m_kWorldGravity = -10;
	const double m_kWorldLength = 1000;
	const double m_kWorldHeight = 1000;
	const int m_kStepsPerSecond = 60;
	const int m_kMicrosecondsPerStep = kMircosecondsPerSecond / m_kStepsPerSecond;

	bool m_physicsStarted = false;

	void AllStepPhysics();
	void HandleBelowWorld(PhysicsObject& currentObject);

public:
	std::vector<PhysicsObject> m_physicsObjects; // make private

	void CreatePhysicsObject(double XStart, double Ystart, double mass);
	void RunPhysics(int durationSeconds);

	int getMicrosecondsPerStep()
	{
		return m_kMicrosecondsPerStep;
	}
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
			HandleBelowWorld(currentObject);

		currentObject.SetLastLocation(currentObject.GetLocation_X(), currentObject.GetLocation_Y());
	}

}

void World::HandleBelowWorld(PhysicsObject& currentObject)
{
	// 0 = (Y Velocity / X Velocity)(x) + Starting Y
	// => -Starting Y / ( (Y Velocity / X Velocity) ) = x

	Vector2* velocityPointer = currentObject.GetVelocityPointer();
	double  newXPosition = (-currentObject.GetLastLocation_Y()) / (velocityPointer->GetY() / velocityPointer->GetX());
	newXPosition += currentObject.GetLastLocation_X(); // shift over to the correct area

	currentObject.SetLocation(newXPosition, 0);
	currentObject.SetVelocity(0, 0);
}

void World::CreatePhysicsObject(double XStart, double Ystart, double mass)
{
	PhysicsObject newObject(XStart, Ystart, mass);
	m_physicsObjects.push_back(newObject);
}

void World::RunPhysics(int durationSeconds)
{
	if (m_physicsStarted)
	{
		Print("Error with RunPhysics: Physics Already Running");
		// I should throw here, not just run an error message
		return;
	}
	m_physicsStarted = true;
	if (durationSeconds == 0)
		durationSeconds = 1;

	// this is the point where I start threading
	std::ofstream coordinateFile("coordinates.txt");
	if (coordinateFile.is_open())
	{
		double tempX;
		double tempY;
		long totalMircoseconds = durationSeconds * kMircosecondsPerSecond;
		int linecount = 0;

		std::chrono::duration<double, std::micro> deltaMicroseconds;
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		Print(" Going into infinite loop")
		while (true)
		{
			
			deltaMicroseconds = std::chrono::steady_clock::now() - startTime;
			long long MicroSecondCount = deltaMicroseconds.count();

			if (deltaMicroseconds.count() < 0)
			{
				//this should never happen, so throw here too
				m_physicsStarted = false;
				return;
			}

			if (MicroSecondCount % getMicrosecondsPerStep() == 0)
			{
				++linecount;
				//std::cout << MicroSecondCount << std::endl;
				AllStepPhysics();
				tempX = m_physicsObjects.at(0).GetLocation_X();
				tempY = m_physicsObjects.at(0).GetLocation_Y();
				coordinateFile << '(' << tempX << ',' << tempY << ')' << std::endl;
			}

			if (deltaMicroseconds.count() >= totalMircoseconds)
			{
				Print(linecount << "Lines");
				break;
			}

		}
	}//write coordinates files
	else
	{
		Print("File not opened");
	}
	m_physicsStarted = false;
}

int main()
{
	World myWorld;

	//create test object at 10,10 with mass 1. then fill in forces applied with simple text
	myWorld.CreatePhysicsObject(10, 10, 1);
	double xForce;
	double yForce;
	int seconds;
	std::cout << "x force" << std::endl;
	std::cin >> xForce;
	std::cout << "y force" << std::endl;
	std::cin >> yForce;
	std::cout << "seconds" << std::endl;
	std::cin >> seconds;

	// give the object its initial kick
	myWorld.m_physicsObjects.at(0).AddForce_X(xForce);
	myWorld.m_physicsObjects.at(0).AddForce_Y(yForce);
	
	
	//deltaMicroseconds = std::chrono::steady_clock::now() - startTime;

	system("pause");

	//try the following, dont natty run.
	myWorld.RunPhysics(seconds);

	system("pause");

	return 0;
}
