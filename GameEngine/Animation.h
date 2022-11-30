#pragma once

#include"SpriteComponent.h"
#include"AssetsStorage.h"
#include"TimeManager.h"

class Animation : public Component
{
private:
	int _frameID = 0;
	int _frames = 0;
	vector<SpriteComponent*> _anim;
	float animationSpeed = 0.05;
	Vector2T<int> _position;

public:
	Animation(string _type , Vector2T<int> position , float angle):_position(position)
	{
		TimeManager::createTimer(_id, animationSpeed);
		_frames = size(AssetsStorage::_effects[_type]);
		for (int i = 0; i < _frames ; i++)
		{
			_anim.push_back(new SpriteComponent(AssetsStorage::_effects[_type][i]));
			_anim[i]->setPosition(position);
			_anim[i]->setAngle(angle);
		}
	}

	~Animation()
	{
		TimeManager::removeTimer(_id);
		_anim.clear();
	}

	void draw() override
	{
		_anim[_frameID]->setPosition(_position - CameraManager::offset - _anim[_frameID]->_dest->w/2);
		_anim[_frameID]->draw();
	}

	void update() override
	{
		if (!TimeManager::_timers[_id]->isTimerWorking())
		{
			_frameID++;
			if (_frameID == _frames)
			{
				disable();
			}
			TimeManager::_timers[_id]->resetTimer();
		}
	}
};