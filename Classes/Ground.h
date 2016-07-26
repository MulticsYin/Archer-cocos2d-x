#ifndef _GROUND
#define _GROUND
#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

class Ground : public Sprite
{
public:
	//地面的尺寸
	Size groundSize;
	PhysicsBody* groundPhysicsBody;
	//默认的初始化
	virtual bool init();
	//自定义尺寸的初始化
	bool init(Size &groundSize);
	CREATE_FUNC(Ground);
};

#endif
#pragma once
