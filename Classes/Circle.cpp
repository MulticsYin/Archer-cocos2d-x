#include <iostream>
#include <cocos2d.h>
#include "Circle.h"

bool Circular:: init() {

		Sprite::initWithFile("CloseNormal.png");
		auto body = PhysicsBody::createCircle(this->getContentSize().width / 2);
		body->setGravityEnable(1);
		setPhysicsBody(body);
		getPhysicsBody()->setRotationEnable(true);
		return true;
}
	
