#include "monsterA.h"
USING_NS_CC;


bool MonsterA::init() {
	count = 0;
	visibleSize = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("redcirclesmall.png");
	body = PhysicsBody::createCircle(this->getContentSize().width/2);
	body->setGravityEnable(1);
//设置怪物的速度；
//	auto tmpx = sqrt(visibleSize.width / 5);
	auto tmpx = visibleSize.width / 1000;
	Vect impulse = Vect(tmpx, 0.0f);
	body->setVelocity(impulse);
	body->setRotationEnable(true);//设置怪物能不能滚动；
	setPhysicsBody(body);
	schedule(schedule_selector(MonsterA::MyUpdate), 0.2f);	//每0.2秒执行一次

	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MonsterA::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(MonsterA::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(MonsterA::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(MonsterA::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}

void MonsterA::MyUpdate(float time) {
	if (count < 10) {
		Sprite::initWithFile("redcirclesmall.png");
		auto tmpx = sqrt(visibleSize.width * 600);
		Vect impulse = Vect(-tmpx, 0.0f);
		body->setVelocity(impulse);
		++count;
	}
	else if (10<= count&&count < 20) {
		Sprite::initWithFile("redcirclesmall.png");
		auto tmpx = sqrt(visibleSize.width * 600);
		Vect impulse = Vect(tmpx, 0.0f);
		body->setVelocity(impulse);
		++count;
	}
	else if (count == 20)count = 0;
}

bool MonsterA::onContactBegin(PhysicsContact &contact) {
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
				SimpleAudioEngine::getInstance()->playEffect(sound_3);
			}
			a->removeFromParentAndCleanup(true);
		
		}
		if (b != NULL) {
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(sound_3);
			}
			if (lift == 1) { lift--; }
			else if (lift == 0) {
				b->removeFromParentAndCleanup(true);
			}
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

bool MonsterA::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	return true;
}

void MonsterA::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {

}

void MonsterA::onContactSeparate(PhysicsContact& contact) {

}

void MonsterA::onExit() {
	Sprite::onExit();

}

