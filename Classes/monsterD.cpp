#include "monsterD.h"
USING_NS_CC;


bool MonsterD::init() {
	count = 0; lift = 1;
	visibleSize = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("monster/purple.png");
	body = PhysicsBody::createCircle(this->getContentSize().width/2);
	body->setGravityEnable(1);
//设置怪物的速度；
//	auto tmpx = sqrt(visibleSize.width / 5);
//	auto tmpx = visibleSize.width / 100000;
	Vect impulse = Vect(0.0, 0.0f);
	body->setVelocity(impulse);
	body->setRotationEnable(false);//设置怪物能不能滚动；
	setPhysicsBody(body);
	schedule(schedule_selector(MonsterD::MyUpdate), 0.2f);	//每0.2秒执行一次

	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MonsterD::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(MonsterD::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(MonsterD::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MonsterD::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void MonsterD::MyUpdate(float time) {
	if (count < 2) {
		Sprite::initWithFile("monster/purple.png");
		auto tmpx = sqrt(visibleSize.width * 200);
		Vect impulse = Vect( 0.0f, tmpx);
		body->setVelocity(impulse);
		++count;
	}
	else if (2<= count&&count < 20) {
		/*
		Sprite::initWithFile("monster/purple.png");
		auto tmpx = sqrt(visibleSize.width * 6);
		Vect impulse = Vect(tmpx, 0.0f);
		body->setVelocity(impulse);
		*/
		++count;
	}
	else if (count == 20)count = 0;
}

bool MonsterD::onContactBegin(PhysicsContact &contact) {
	switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
		contact.getShapeB()->getBody()->getContactTestBitmask())
	{
	case ARROW_BIT_MASK | MONSTER1_BIT_MASK://箭射中怪物
	{
		//this->removeFromParentAndCleanup(true);
		auto a = contact.getShapeA()->getBody()->getNode();
		auto b = contact.getShapeB()->getBody()->getNode();
		log("dispear！！！！！！！！！！！！！！！");
		if (a != NULL) {
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(sound_4);
			}
			a->removeFromParentAndCleanup(true);

		}
		if (b != NULL) {
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(sound_4);
			}
			b->removeFromParentAndCleanup(true);
			//long bt = b->getTag();// tilemap->removeChildByTag();
			//b->removeFromParentAndCleanup(true);
			//log("bt %d", bt);
			//if (-1 < bt < 10001)tilemap->getLayer("pengzhuang")->removeChildByTag(bt);
		}
	}
	break;
	default:
		break;
	}
	return true;
}

bool MonsterD::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	return true;
}

void MonsterD::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {

}

void MonsterD::onContactSeparate(PhysicsContact& contact) {

}

void MonsterD::onExit() {
	Sprite::onExit();

}

