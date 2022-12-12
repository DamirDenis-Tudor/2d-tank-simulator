#pragma once

#include"Builder.h"
#include"Tank.h"
#include"Vector2i.h"
#include"Mediator.h"
#include"CameraManager.h"


/*
	Descriere:
		-> adauga caracteristici noi specifice unui tank
*/
class TankBuilder : public Builder
{
	friend class Director;

protected:
	bool playerIdentifier = false;
	Vector2T<float> _velocity;
	float _shotingTime = 0;
	const char* _shotingAnim = nullptr;
	const char* _impactAnim = nullptr;
	Behavior* _behavior = nullptr;

	void setTankParameters();
	void build() override;

public:
	virtual void setBehavior() = 0;
};

/*
*/
class AiTank : public TankBuilder
{
public:
	AiTank()
	{
	}

	void setBehavior() override 
	{

		_behavior = nullptr;
		_behavior = new AiBehavior;
	}

};

class PlayerTank : public TankBuilder
{
public:
	PlayerTank()
	{
		playerIdentifier = true;
	}
	void setBehavior() override
	{
		_behavior = nullptr;
		_behavior = new InputBehavior;
	}
};
