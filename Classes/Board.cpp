#include "Board.h"
USING_NS_CC;
//static const int DRAG_BODYS_TAG = 0x80;
bool Board::init() {
	Sprite::init();
	//Size s = Size(600,15);
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//auto body = PhysicsBody::createBox(s);
	//body->setGravityEnable(1);
	//setPhysicsBody(body);
	//getPhysicsBody()->setRotationEnable(true);
	//setContentSize(visibleSize);
	//以下解决刚体穿透问题
	Size s = Size(600, 15);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createBox(s);
	body->setGravityEnable(1);
	//body->setTag(DRAG_BODYS_TAG);
	body->setRotationEnable(true);
	setPhysicsBody(body);
	setContentSize(visibleSize);
	return true;
}