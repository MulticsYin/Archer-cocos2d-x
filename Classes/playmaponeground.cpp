#include "playmaponeground.h"
#include <cocos2d.h>
USING_NS_CC;

bool Playmaponeground::init() {
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	groundSize = Size(visibleSize.width * 5, 10);
	auto physicsBody = PhysicsBody::createEdgeBox(groundSize);
	//physicsBody->setGravityEnable(0);////
	physicsBody->getShape(0)->setRestitution(0.6f);
	physicsBody->getShape(0)->setFriction(1.0f);
	physicsBody->getShape(0)->setDensity(1.0f);
	setPhysicsBody(physicsBody);
	setTextureRect(Rect(0, 0, groundSize.width, groundSize.height));
	setContentSize(visibleSize);
	return true;
}

bool Playmaponeground::init(Size &groundSize) {
	Sprite::init();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//groundSize = Size(visibleSize.width * 3, 10);
	auto physicsBody = PhysicsBody::createEdgeBox(groundSize);
	setPhysicsBody(physicsBody);
	setContentSize(visibleSize);
	return true;
}
