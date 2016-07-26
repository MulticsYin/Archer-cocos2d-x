#ifndef _ARROW
#define _ARROW
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}
#include "cocos2d.h"
#include "Hero.h"
#include "PlayMapOne.h"
#include "contact_data.h"
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
using namespace cocos2d;
USING_NS_CC;

class Arrow : public Sprite{
public :

	//Åö×²Ïà¹Ø
	EventListenerPhysicsContact* contactListener;
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactPreSolve(PhysicsContact&  contact, PhysicsContactPreSolve&  solve);
	virtual void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	virtual void onContactSeparate(PhysicsContact& contact);

	virtual bool init();
	void shotend(Layer* map);
	PhysicsBody* body;
	virtual void onExit();
	CREATE_FUNC(Arrow);
};

#endif
#pragma once
