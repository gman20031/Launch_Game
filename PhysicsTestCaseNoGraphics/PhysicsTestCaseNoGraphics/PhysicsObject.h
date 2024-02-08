#pragma once

struct location2
{
	double xPosition;
	double yPosition;
};

class Vector2
{
	double m_xComponent = 0;
	double m_yComponent = 0;
	double m_direction = 0;
	double m_magnitude = 0;

	void SetDirectionFromComponents();
	void SetMagnitudeFromComponents();
	void SetXFromMagY();
	void SetYFromMagX();
	void SetXFromDirY();
	void SetYFromDirX();
	void SetXFromMagDir();
	void SetYFromMagDir();

public:
	double GetX();
	void SetX(double newX);

	double GetY();
	void SetY(double newY);

	double GetDirection();
	void SetDirection(double newDirection);

	double GetMagnitude();
	void SetMagnitude(double newMagnitude);
};

class PhysicsObject
{
	location2 m_location;
	location2 m_lastLocation;
	Vector2 m_velocity;

	double m_mass = 1; // currently % modifier to how fast object falls.
	double m_massInverse = 1 / m_mass;
	double m_bouncyness = 0.80;

public:
	PhysicsObject(double XStart, double Ystart, double mass);

	void DebugLocationPrint();
	void updateLocationFromForce(const int stepsPerSecond);

	void SetMass(double newMass);
	double GetMass();
	double GetMassInverse();
	double GetBouncyness();

	void SetLocation(double XVal, double YVal);
	double GetLocation_X();
	double GetLocation_Y();
	void SetLastLocation(double XVal, double YVal);
	double GetLastLocation_X();
	double GetLastLocation_Y();

	void SetVelocity(double XVal, double YVal);
	void AddForce_X(double force);
	void AddForce_Y(double force);
	Vector2* GetVelocityPointer();
};

