#include "PhysicsObject.h"
#include <cmath>

#define square(x) pow(x,2)

// Set magnitude using x and y
void Vector2::SetMagnitudeFromComponents()
{
	m_magnitude = std::sqrt(square(m_xComponent) + square(m_yComponent));
}
// Set direction using x and y
void Vector2::SetDirectionFromComponents()
{
	m_direction = std::atan2(m_xComponent, m_yComponent);
}
// Set x using magnitude and y
void Vector2::SetXFromMagY()
{
	m_xComponent = std::sqrt(square(m_magnitude) + square(m_yComponent));
}
// Set y using magnitude and x
void Vector2::SetYFromMagX()
{
	m_yComponent = std::sqrt(square(m_magnitude) + square(m_xComponent));
}
// Set x using Direction and Y
void Vector2::SetXFromDirY()
{
	m_xComponent = m_yComponent / (std::tan(m_direction));
}
// Set Y using direction and X
void Vector2::SetYFromDirX()
{
	m_yComponent = m_xComponent * (std::tan(m_direction));
}
// Set X using magnitude and direction
void Vector2::SetXFromMagDir() {
	m_xComponent = m_magnitude * std::sin(m_direction);
}
// Set Y using Magnitude and direction
void Vector2::SetYFromMagDir() {
	m_yComponent = m_magnitude * std::cos(m_direction);
}

////////////////////////////////////////////
// Set and Get functions
////////////////////////////////////////////

//Handling of xComponent
double Vector2::GetX()
{
	return m_xComponent;
}
void Vector2::SetX(double newX)
{
	m_xComponent = newX;
	SetDirectionFromComponents();
	SetMagnitudeFromComponents();
}

//Handling of yComponent
double Vector2::GetY()
{
	return  m_yComponent;
}
void Vector2::SetY(double newY)
{
	m_yComponent = newY;
	SetDirectionFromComponents();
	SetMagnitudeFromComponents();
}

//Handling of direction
double Vector2::GetDirection()
{
	return m_direction;
}
void Vector2::SetDirection(double newDirection)
{
	m_direction = newDirection;
	SetXFromMagDir();
	SetYFromMagDir();
}

//Handling of magnitude
double Vector2::GetMagnitude()
{
	return m_magnitude;
}
void Vector2::SetMagnitude(double newMagnitude)
{
	m_magnitude = newMagnitude;
	SetXFromMagDir();
	SetYFromMagDir();
}