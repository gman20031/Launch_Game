#include "PhysicsObject.h"
#include <iostream>

//Constructor contrutor for the object
PhysicsObject::PhysicsObject(double XStart, double Ystart, double mass) {
	m_location.xPosition = XStart;
	m_location.yPosition = Ystart;
	m_lastLocation = m_location;
	m_mass = mass;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//Location functions
///////////////////////////////////////////////////////////////////////////////////////////////////

// location printing as standard ( x , y )
void PhysicsObject::DebugLocationPrint()
{
	std::cout << "(" << m_location.xPosition << "," << m_location.yPosition << ")\n";
}

// updates the position of the object based on the current velocity vector - divided by number of steps per second.
void PhysicsObject::updateLocationFromForce(const int stepsPerSecond)
{
	m_location.xPosition += (m_velocity.GetX() / stepsPerSecond);
	m_location.yPosition += (m_velocity.GetY() / stepsPerSecond);
}

// set the location of the object to specifed location
void PhysicsObject::SetLocation(double XVal, double YVal)
{
	m_location.xPosition = XVal;
	m_location.yPosition = YVal;
}

// returns X location of object
double PhysicsObject::GetLocation_X()
{
	return m_location.xPosition;
}

// returns Y location of object
double PhysicsObject::GetLocation_Y()
{
	return m_location.yPosition;
}

// set the location of the object at the last step to specified location
void PhysicsObject::SetLastLocation(double XVal, double YVal)
{
	m_lastLocation.xPosition = XVal;
	m_lastLocation.yPosition = YVal;
}

// returns last step X location of object
double PhysicsObject::GetLastLocation_X()
{
	return m_lastLocation.xPosition;
}

// returns last step Y location of object
double PhysicsObject::GetLastLocation_Y()
{
	return m_lastLocation.yPosition;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//Velocity Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

// Adds the value given to the X component of velocity vector
void PhysicsObject::AddForce_X(double force)
{
	m_velocity.SetX(m_velocity.GetX() + force);
}
// Adds the value given to the Y component of the velocity Vector
void PhysicsObject::AddForce_Y(double force)
{
	m_velocity.SetY(m_velocity.GetY() + force);
}
// sets the velocity of object to specified x,y values
void PhysicsObject::SetVelocity(double XVal, double YVal)
{
	m_velocity.SetX(XVal);
	m_velocity.SetY(YVal);
}

Vector2* PhysicsObject::GetVelocityPointer()
{
	return &m_velocity;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Mass Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void PhysicsObject::SetMass(double newMass)
{
	m_mass = newMass;
	m_massInverse = 1 / newMass;
}

double PhysicsObject::GetMass()
{
	return m_mass;
}

double PhysicsObject::GetMassInverse()
{
	return m_massInverse;
}

double PhysicsObject::GetBouncyness()
{
	return m_bouncyness;
}

