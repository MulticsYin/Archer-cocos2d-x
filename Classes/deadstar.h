#ifndef DEAD_STAR
#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

class DeadStar :public Sprite {
public:
	short count;
	PhysicsBody* body;
	virtual bool init();
	void MyUpdate(float time);
	CREATE_FUNC(DeadStar);
};
#endif
#pragma once
