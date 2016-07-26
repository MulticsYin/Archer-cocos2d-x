#ifndef OBSTACLE
#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

class Obstacle :public Sprite {
public:
	short count;
	PhysicsBody* body;
	virtual bool init();
	void MyUpdate(float time);
	CREATE_FUNC(Obstacle);
};
#endif
#pragma once
