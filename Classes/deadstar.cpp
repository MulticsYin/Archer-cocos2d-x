#include "deadstar.h"

bool DeadStar::init() {
	count = 0;
	Sprite::initWithFile("car.png");
	body = PhysicsBody::createBox(this->getContentSize());
	body->setGravityEnable(1);
	Vect impulse = Vect(200.0f, 0.0f);
	body->setVelocity(impulse); 
	body->setRotationEnable(true);
	setPhysicsBody(body);
	schedule(schedule_selector(DeadStar::MyUpdate), 0.2f);	//每0.2秒执行一次
	
	return true;
}

void DeadStar::MyUpdate(float time) {
	if (count < 60) {
		Sprite::initWithFile("car.png");
		Vect impulse = Vect(200.0f,0.0f );
		body->setVelocity(impulse); 
		++count;
	}
	else if (60 <= count&&count < 120) {
		Sprite::initWithFile("car.png");
		Vect impulse = Vect(-200.0f,0.0f);
		body->setVelocity(impulse); 
		++count;
	}else if (count == 120)count = 0;
}

