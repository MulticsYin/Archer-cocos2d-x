#ifndef MOSTER_D
#define MOSTER_D
#include <cocos2d.h>
USING_NS_CC;
#include "contact_data.h"
#include "SystemHeader.h"
/*
#define HERO_BIT_MASK		0b10000000
#define BRIDGE_BIT_MASK		0b01000000
#define GROUND_BIT_MASK		0b00100000
#define CIRCLE_BIT_MASK		0b00010000
#define DEAD_LINE			0b00001000
#define ARROW_BIT_MASK		0b00000100
#define MONSTER1_BIT_MASK	0b00000010
#define OBJECT_BIT_MASK		0b00000001
*/

class MonsterD:public cocos2d::Sprite
{
public:
	short count;
	Size visibleSize;
	PhysicsBody* body;
	int lift;
	virtual bool init();
	void MyUpdate(float time);
	virtual void onExit();

	EventListenerPhysicsContact* contactListener;
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactPreSolve(PhysicsContact&  contact, PhysicsContactPreSolve&  solve);
	virtual void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	virtual void onContactSeparate(PhysicsContact& contact);

	CREATE_FUNC(MonsterD);
};


#endif 
#pragma once
