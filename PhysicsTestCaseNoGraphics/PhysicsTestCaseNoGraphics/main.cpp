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
	const int m_kStepsPerSecond = 60;
	const int m_kMicrosecondsPerStep = kMircosecondsPerSecond / m_kStepsPerSecond;
	static constexpr double m_kPi = 3.14159265359;
	const double m_kNeintyDegree = m_kPi / 2;

	const double m_kWorldGravity		= -.10;
	const double m_kWorldFriciton		= .9;
	const double m_kWorldCutOffThreshold= .05;
	const double m_kWorldLength			= 1000;
	const double m_kWorldHeight			= 1000;

	bool m_physicsStarted = false;

	void AllStepPhysics();
	void CheckIfOutOfWorld(PhysicsObject& currentObject);
	void HandleOutOfWorld(PhysicsObject& currentObject);
	void HandleBelowWorld(PhysicsObject& currentObject);
	void RollObject(PhysicsObject& currentObject);
	double GetNearestGoodX(PhysicsObject& currentObject);
	double GetNearestGoodY(PhysicsObject& currentObject);

public:
	World() {};

	std::vector<PhysicsObject> m_physicsObjects; // make private?

	void CreatePhysicsObject(double XStart, double Ystart, double mass);
	void RunPhysics();

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
		currentObject.SetLastLocation(currentObject.GetLocation_X(), currentObject.GetLocation_Y());
		currentObject.AddForce_Y(currentObject.GetMass() * m_kWorldGravity);
		currentObject.updateLocationFromForce(m_kStepsPerSecond);
		CheckIfOutOfWorld(currentObject);
	}

}

void World::CheckIfOutOfWorld(PhysicsObject& currentObject)
{
	if (currentObject.GetLocation_X() < 0 or currentObject.GetLocation_X() > m_kWorldLength
	or currentObject.GetLocation_Y() < 0 or currentObject.GetLocation_Y() > m_kWorldHeight)
	{
		if (currentObject.GetVelocityPointer()->GetY() == m_kWorldGravity)
			RollObject(currentObject);
		else
			HandleBelowWorld(currentObject);
	}
	
}

void World::HandleOutOfWorld(PhysicsObject& currentObject)
{
	//set to correct location
	double good_X = currentObject.GetLocation_X();
	double good_Y = currentObject.GetLocation_Y();
	if (currentObject.GetLocation_X() < 0 or currentObject.GetLocation_X() > m_kWorldLength)
		good_X = GetNearestGoodX(currentObject);

	if (currentObject.GetLocation_Y() < 0 or currentObject.GetLocation_Y() > m_kWorldHeight)
		good_Y = GetNearestGoodY(currentObject);

	// if collding with bottom
	// Theta = pi -( pi - curVectorAngle) - neintyDegrees
	// new direction = neintyDegree - theta

	// if collding with Top
	// Theta = pi -( pi - curVectorAngle ) - neintyDegrees
	// new direction = neintyDegree + theta

	// if collding with Right
	// Theta = neintyDegrees - (pi -( pi - curVectorAngle ) - neintyDegrees)
	// newDIrection = 2pi - theta

	// if colliding with left
	// Theta = neintyDegrees - (pi -( pi - curVectorAngle ) - neintyDegrees)
	// new DIrection = theta


	//uzkad
	/*
	I don't know how your backend works but the crossproduct of two vectors is always normal to the surface
	That's the usual math way of doing it
	From there I believe you can use the dot product to make angle calculations easier
	*/


	//set to correct vector followup

	currentObject.SetLocation(good_X, good_Y);
}

double World::GetNearestGoodX(PhysicsObject& currentObject)
{
	// y = mx+b
	// => 0 = (Y Velocity / X Velocity)(x) + Starting Y
	// => x = -Starting Y / ( (Y Velocity / X Velocity) )
	Vector2* pVelocity = currentObject.GetVelocityPointer();
	double  newXPosition = (-currentObject.GetLastLocation_Y()) / (pVelocity->GetY() / pVelocity->GetX());
	newXPosition += currentObject.GetLastLocation_X(); // shift over to the correct area since i didnt calculate for B in y=mx+b
	return newXPosition;
}

double World::GetNearestGoodY(PhysicsObject& currentObject)
{
	// y = mx+b
	// => starting Y = (Y Velocity / X Velocity)(starting X) + b
	// => b = -(Y Velocity / X Velocity)(starting X) + starting Y
	Vector2* pVelocity = currentObject.GetVelocityPointer();
	double newYPosition = (-(pVelocity->GetY() / pVelocity->GetX()) * currentObject.GetLastLocation_X()) + currentObject.GetLastLocation_Y();
	newYPosition += currentObject.GetLastLocation_Y();

	return newYPosition;
}

void World::HandleBelowWorld(PhysicsObject& currentObject)
{
	Vector2* pVelocity = currentObject.GetVelocityPointer();
	double newXPosition = GetNearestGoodX(currentObject);

	currentObject.SetLocation(newXPosition, 0);

	double newVelocity_X = (currentObject.GetBouncyness() * pVelocity->GetX());
	double newVelocity_Y = (currentObject.GetBouncyness() * -pVelocity->GetY());
	if (newVelocity_Y < 3)
		newVelocity_Y = 0;
	if (newVelocity_X < .5)
		newVelocity_X = 0;
	currentObject.SetVelocity(newVelocity_X, newVelocity_Y);

	
}

void World::RollObject(PhysicsObject& currentObject)
{
	Vector2* pVelocity = currentObject.GetVelocityPointer();
	currentObject.SetLocation(currentObject.GetLocation_X(), 0);
	double newVelocity_X = (m_kWorldFriciton * pVelocity->GetX());
	if (newVelocity_X < .5)
		newVelocity_X = 0;
	currentObject.SetVelocity(newVelocity_X, 0);
}

void World::CreatePhysicsObject(double XStart, double Ystart, double mass)
{
	PhysicsObject newObject(XStart, Ystart, mass);
	m_physicsObjects.push_back(newObject);
}

void World::RunPhysics()
{
	if (m_physicsStarted)
	{
		Print("Error with RunPhysics: Physics Already Running");
		// I should throw here, not just run an error message
		return;
	}

	// this is the point where I start threading
	std::ofstream coordinateFile("coordinates.txt");
	if (coordinateFile.is_open())
	{
		double tempX;
		double tempY;
		int linecount = 0;

		std::chrono::duration<double, std::micro> deltaMicroseconds;
		std::chrono::time_point<std::chrono::steady_clock> startTime = std::chrono::steady_clock::now();
		Print(" Going into infinite loop")
		for(;;)
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


				if (m_physicsObjects.at(0).GetVelocityPointer()->GetMagnitude() == 0)
				{
					break;
				}

				coordinateFile << '(' << tempX << ',' << tempY << ')' << std::endl;
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

	// give the object its initial kick
	myWorld.m_physicsObjects.at(0).AddForce_X(xForce);
	myWorld.m_physicsObjects.at(0).AddForce_Y(yForce);
	
	
	//deltaMicroseconds = std::chrono::steady_clock::now() - startTime;

	system("pause");

	//try the following, dont natty run.
	myWorld.RunPhysics();

	system("pause");

	return 0;
}
