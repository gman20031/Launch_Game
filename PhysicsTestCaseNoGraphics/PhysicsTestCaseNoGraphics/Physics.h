#pragma once

struct location2
{
	double xPosition;
	double yPosition;
};

class Vector2
{
public:
	double xComponent = 0;
	double yComponent = 0;
	double direction = 0;
	double magnitude = 0;

	void SetDirectionFromComponents();
	void SetMagnitudeFromComponents();
	void SetXFromMagDir();
	void SetYFromMagDir();
};

class PhysicsObject
{
	Vector2 m_velocity;
	char m_displayer = 'x';
	double m_mass = 1;

public:
	location2 m_location;
	PhysicsObject(double XStart, double Ystart, double mass);

	void PrintLocation();
	void updateLocationFromForce();
	void ChangeDisplayer(char newDisplayer);
	void SetVelocity(double XVal, double YVal);
	void AddForce_X(double force);
	void AddForce_Y(double force);
};