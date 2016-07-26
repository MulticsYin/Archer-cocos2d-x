#include "Ground.h"
#include <iostream>

#include <cocos2d.h>

USING_NS_CC;

bool Ground::init() {
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	groundSize = Size(visibleSize.width*3,10);
	auto physicsBody = PhysicsBody::createEdgeBox(groundSize);
	//physicsBody->setGravityEnable(0);////
	physicsBody->getShape(0)->setRestitution(0.0f);
	physicsBody->getShape(0)->setFriction(1.0f);
	physicsBody->getShape(0)->setDensity(0.0f);
	//this->setAnchorPoint(Vec2(0, 1));
	setPhysicsBody(physicsBody);
	setTextureRect(Rect(0,0, groundSize.width, groundSize.height));
	setContentSize(visibleSize);
	return true;
}

bool Ground::init(Size &groundSize) {
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//groundSize = Size(visibleSize.width * 3, 10);
	auto physicsBody = PhysicsBody::createEdgeBox(groundSize);
	physicsBody->getShape(0)->setRestitution(0.0f);
	physicsBody->getShape(0)->setFriction(1.0f);
	physicsBody->getShape(0)->setDensity(0.0f);
	setPhysicsBody(physicsBody);
	setContentSize(visibleSize);
	//this->setAnchorPoint(Vec2(0, 0));
	return true;
}

