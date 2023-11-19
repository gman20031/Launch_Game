#include "Physics.h"
#include <cmath>

void Vector2::SetDirectionFromComponents()
{
	direction = std::atan2(xComponent, yComponent);
}//get Dir x,y

void Vector2::SetMagnitudeFromComponents()
{
	magnitude = std::sqrt((pow(xComponent, 2) + pow(yComponent, 2)));
}//get mag

void Vector2::SetXFromMagDir() {
	xComponent = magnitude * std::sin(direction);
}//getx

void Vector2::SetYFromMagDir() {
	xComponent = magnitude * std::cos(direction);
}//gety