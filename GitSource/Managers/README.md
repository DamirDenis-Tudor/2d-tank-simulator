# Overview

- I preferred to work with static variables and methods instead of the Singleton Design Pattern. It was just a matter of preference.
	- Example : 
	```cpp
	/*
	* without Sigleton, here aStart is a static method
	*/
	_moves = MapSpaceManager::aStar(Mediator::getPosition(_id), target , _isHealing);
	
	/*
	* with Sigletonm here aStar in a non-static method
	*/
	MapSpaceManager * _mapSpaceManager = MapSpaceManager::getInstance();
	_moves =  _mapSpaceManager->aStar(Mediator::getPosition(_id), target , _isHealing);
	```
- This project consists of several classes that implement the `Component` interface. Each class serves a specific purpose in the game engine, as described below:

## 1. AnimationHandler
- This class has a static method that allows it to take over an animation at any moment in the game.
- It can be stored in the **Engine** components.

```cpp
/*
* Engine.cpp
*/
_components.emplace_back(new AnimationHandler);
```

## 2. AssetsStorage
- This class is responsible for loading assets such as : 
	- tanks
	- map and minimap tiles
	- effects and abilities 
	- menu items
- These informations are loaded from XML files.

## 3. CameraManager
- This class implements two modes:
  - Spectator mode: allows the player to observe the gameplay.
  - Focus mode: allows the player to track any object on the map.

## 4. CollisionManager
- This class offers a series of collision checks, including:
  - `static void mapCollision(...)`
  - `static bool circleRectangleCollision(...)`
  - `static bool pointMapCollision(...)`
  - `static bool pointRectangleCollision(...)`

## 5. InfoManager
- This class has a static method that allows it to take over a text at any moment in the game.
- It can be stored in the **Engine** components.
```cpp
/*
* Engine.cpp
*/
_components.emplace_back(new InfoManager);
```

## 6. InputManager
- This class handles input.

## 7. MapSpaceManager
- This class manages spawn positions and implements an optimized pathfinding algorithm (A*).
- For tanks, it helps to avoid collision with another tank (which will be seen as a temporary obstacle) and generates the best shooting position (by simulating bullet trajectory).
- Before interacting with the class, it must be informed with the `MapSpaceManager::setUser(_id, _colorTeam)` method. Example usage:
  ```cpp
  /*
  * AiBehavior.cpp
  */
  MapSpaceManager::setUser(_id, _colorTeam);
  _moves = MapSpaceManager::aStar(Mediator::getPosition(_id), target, _isHealing);

## 8. Mediator

- The Mediator class is responsible for managing the interaction between objects. 
- It can group objects according to certain characteristics, store information related to objects and recognize objects by an id.

### Usage example

```cpp
/*
* Tank.cpp
*/
Mediator::notifyTeam(_id, _teamColor);
Mediator::registerTank(_position, _id, Health);

/*
* Behavior.cpp
*/
for (auto& i : Mediator::recieveTanksPositions(_id))
{
    CollisionManager::circleRectagleCollision(potentialPos, i, rectDim);
}
```
## 9. RendererManager

The class creates a window and provides a renderer (specific SDL variable).

## 10. SoundManager

- This is responsible loading and playing sounds.
- Loading usage example : 
```cpp
/*
* Engine.cpp
*/

SoundManager::addBackgroundMusic("assets/sounds/menu/music.mp3", "music");
SoundManager::addBackgroundMusic("assets/sounds/game/war.mp3", "war");

SoundManager::addSoundEffect("assets/sounds/menu/switch.wav", "switch");
SoundManager::addSoundEffect("assets/sounds/menu/click.wav", "click");
```
- Playing usage example :
```cpp
/*
* Menu.cpp
*/
SoundManager::playBackgroundMusic("music");
```

## 11. SpecialObjectsManager

- These are static methods that allow them to collect special objects (bullets, mines, abilities) at any moment in the game.
- It can be stored in the **Engine** components.

```cpp
/*
* Engine.cpp
*/
_components.emplace_back(new SpecialObjectsManager);
```

## 12. TimersManager

The class deals with the management of timers in the game. Timers are identified by a string id.

### Usage example
```cpp
/*
Tank.cpp
*/
TimeManager::createTimer(to_string(_id) + "respawn", rand() % 5 + 10);
TimeManager::createTimer(to_string(_id) + "bullet", _attributes->_shotingTime);
TimeManager::createTimer(to_string(_id) + "mine" , 0.2);
TimeManager::createTimer(to_string(_id) + "healing", 0.2);

/*
*Tank.cpp
*/
if (!TimeManager::getTimer(to_string(_id) + "mine")->isTimerWorking() &&_behavior->isLaunchingMine() && ...)
{
	TimeManager::getTimer(to_string(_id) + "mine")->resetTimer();
	SpecialObjectsManager::addMine(new Mine(_teamColor + "mine", _position + AssetsStorage::_tileDim, _id));
}
