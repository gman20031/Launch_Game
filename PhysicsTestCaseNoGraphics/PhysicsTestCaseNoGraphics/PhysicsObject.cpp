#include "Physics.h"
#include <iostream>

PhysicsObject::PhysicsObject(double XStart, double Ystart, double mass) {
	m_location.xPosition = XStart;
	m_location.yPosition = Ystart;
	m_mass = mass;
}

void PhysicsObject::PrintLocation()
{
	std::cout << "( " << m_location.xPosition << " , " << m_location.yPosition << " )\n";
}

void PhysicsObject::AddForce_X(double force)
{
	m_velocity.xComponent += force;
}

void PhysicsObject::AddForce_Y(double force)
{
	m_velocity.yComponent += force;
}

void PhysicsObject::ChangeDisplayer(char newDisplayer)
{
	m_displayer = newDisplayer;
}

void PhysicsObject::updateLocationFromForce()
{
	m_location.xPosition += m_velocity.xComponent;
	m_location.yPosition += m_velocity.yComponent;
}

void PhysicsObject::SetVelocity(double XVal, double YVal)
{
	m_velocity.xComponent = XVal;
	m_velocity.yComponent = YVal;
}