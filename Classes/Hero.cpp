//
//  GameObjHero.cpp
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
//960*640
#include "Hero.h"


bool Hero::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

    log("GameObjHero::onEnter::x=%0.2f, y=%0.2f, w=%0.2f, h=%0.2f", this->getPosition().x, this->getPosition().y, this->getContentSize().width, this->getContentSize().height);

    state = 0;  // 置为静止状态

	//身体
	playerbody = Sprite::create();
	playerbody->initWithSpriteFrameName("player1.png");
	archpos = Size(playerbody->getContentSize().width / 2, playerbody->getContentSize().height / 3 * 2);
	playerbody->setAnchorPoint(Vec2(0.7f, 0.4f));
	this->setAnchorPoint(Vec2(0.7f, 0.4f));

	// 以主精灵图片的大小作为当前精灵的大小
	auto tmp = playerbody->getContentSize();
	physicsSize = Size(tmp.width,tmp.height*7/10);
	//设置物理
	physicshero = PhysicsBody::createBox(physicsSize);
	log("width %f,height %f", getContentSize().width, this->getContentSize().height);
	physicshero->setRotationEnable(false);
	//调试时设置主角重力；
	physicshero->setGravityEnable(true);
//	physicshero->setGravityEnable(false);
	physicshero->setLinearDamping(0.1f);
	physicshero->getShape(0)->setRestitution(0.6f);
	physicshero->getShape(0)->setFriction(0.5f);
	physicshero->getShape(0)->setDensity(1.0f);
	this->addChild(playerbody);
	this->setPhysicsBody(physicshero);

	//射箭相关
	winSize = Director::getInstance()->getWinSize();
	playerarrow = NULL;
	drawNode = NULL;
	bezier.controlPoint = Vec2(0, 0);
	bezier.endPosition = Vec2(0, 0);

	//手臂和弓箭
	playerarrow = Sprite::create();
	playerarrow->Sprite::initWithSpriteFrameName("playerarrow.png");
	playerarrow->setPosition(Vec2(0, 0));
	playerarrow->setAnchorPoint(Vec2(0.2f, 0.5f));
	this->addChild(playerarrow);
	schedule(schedule_selector(Hero::MyUpdate),0.1f);	//每0.1秒执行一次

	return true;
}

// 设置精灵当前状态
void Hero::setState(short var){
    if(state == var)
        return;     // 状态相同不需要处理

    // 重置状态
    state = var;

    switch(state){
		case 0:     // 在地上，静止状态
		{
			// 先停止所有正在进行的动画
			this->stopAllActions(); Hero::moveStop();
			playerbody->stopAllActions();
			break;
		}
        case 1: // 跳跃，在空中
        {
            // 先停止所有正在进行的动画
            this->stopAllActions();
			playerbody->stopAllActions();
	      // 设置主角贴图为跳跃的贴图



            break;
        }
        case 2: // 受伤
        {
            // 先停止所有正在进行的动画
            this->stopAllActions();
			playerbody->stopAllActions();
            // 设置主角贴图为哭的贴图

            break;
        }
		case 3://左移
		{
			//this->stopAllActions();
			Hero::moveLeft();
			// 运行奔跑的动画
			break;
		}
		case 4://右移
		{
			//this->stopAllActions();
			Hero::moveRight();

			break;
		}
		case 6:
		{
			//在进行弓的摇动
			Hero::rotateArrow(Hero::archAngle);
			break;
		}
    }
}

//射箭相关

void Hero::rotateArrow(Point touchPoint) //随触摸点旋转的弓
{
	// 1
	auto playerPos = this->getPosition();
	auto pos = playerPos + playerarrow->getPosition();
	// 2
	Point vector = touchPoint - pos;
	auto rotateRadians = vector.getAngle();
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
	// 3
	if (rotateDegrees >= -180 && rotateDegrees <= -90) {
		rotateDegrees = -90;
	}
	else if (rotateDegrees >= 90 && rotateDegrees <= 180) {
		rotateDegrees = 90;
	}
	// 4
	auto speed = 0.5 / M_PI;
	auto rotateDuration = fabs(rotateRadians * speed);
	// 5
	playerarrow->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL));

	// 检测路径贝赛尔的控制点和终点
	auto MAX_DISTANCE = winSize.width / 2;
	auto x = MAX(MAX_DISTANCE / 10, MIN(vector.x, MAX_DISTANCE));
	auto y = vector.y;

	Point endPoint = Vec2(4 * x, -this->convertToWorldSpace(Vec2(4 * x, y > 0 ? 0 : std::abs(y * 10))).y);

	Point q = Point(2 * x, y * 2);
	bezier.controlPoint = q;

	//改写落点在这里
	bezier.endPosition = Vec2(endPoint.x,endPoint.y+visibleSize.height/4);
	log("bezier.controlPoint=%f,%f;bezier.endPosition=%f,%f",q.x,q.y,endPoint.x,endPoint.y);
	startDraw = true;
}

void Hero::createAndShootArrow(Point touchPoint, Layer* map) {
	if (isRunAction==false) {
		isRunAction = true;

		auto animation = AnimationCache::getInstance()->getAnimation("player");
		auto animate = Animate::create(animation);
		auto delayTime = DelayTime::create(0.2f);
		auto funcall1 = CallFunc::create(CC_CALLBACK_0(Hero::shootArrow, this, map));
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_2);
	}
		auto funcall2 = CallFunc::create(CC_CALLBACK_0(Hero::finishRunAction, this));
		playerbody->runAction(Sequence::create(animate, funcall1, delayTime, funcall2, NULL));
		//startDraw = false;
		log("it's shoting5");
	}
}

void Hero::shootArrow(Layer* map) {
	auto arrow = Arrow::create();
	arrow->initWithSpriteFrameName("arrow1.png");
	arrow->getPhysicsBody()->setContactTestBitmask(ARROW_BIT_MASK);
	arrow->setRotation(playerarrow->getRotation());
	arrow->setPosition(Vec2(playerarrow->getPosition().x / 2, playerarrow->getPosition().y));
	this->addChild(arrow);

	auto action = ArrowPathBezier::create(2, bezier);
	//arrow->runAction(action);
	arrow->runAction(Sequence::create(action, CallFunc::create(CC_CALLBACK_0(Arrow::shotend, arrow,map)), NULL)); //arrow->removeFromParent();
}

void Hero::finishRunAction() {
	isRunAction = false;
	startDraw = false;
	log("it's shoting4");
}

void Hero::jumpend(){
    // 恢复为奔跑状态
    setState(0);
	this->state = 0;
}

void Hero::hurtend(){
    // 恢复为奔跑状态
    //setState(0);  // 游戏结束了，就不应该再奔跑了吧？
}

void Hero::onExit()
{
    CCNode::onExit();
}
//bool GameObjHero::containsTouchLocation(Touch* touch)
//{
//	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
//}

void Hero::jumpUp() {
	startDraw = false;
	auto tmp = sqrt(visibleSize.height*500);
	Vect impulse = Vect(0, tmp);
	physicshero->setVelocity(impulse); //setState(1);
}

void Hero::jumpLeft() {
	startDraw = false;
	auto tmpy = sqrt(visibleSize.height * 500);
	auto tmpx = sqrt(visibleSize.width*23);
	Vect impulse = Vect(-tmpx, tmpy);
	//Vect impulse = Vect(-visibleSize.width  / 6, visibleSize.height * 4 / 5);
	physicshero->setVelocity(impulse); //setState(1);
}

void Hero::jumpRight() {
	startDraw = false;
	auto tmpy = sqrt(visibleSize.height * 500);
	auto tmpx = sqrt(visibleSize.width * 23);
	Vect impulse = Vect(tmpx, tmpy);
	//Vect impulse = Vect(visibleSize.width / 6, visibleSize.height * 4 / 5);
	physicshero->setVelocity(impulse); //setState(1);
}

void Hero::moveRight() {
	startDraw = false;
	log("RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
	auto tmpx = sqrt(visibleSize.width * 120);
	Vect impulse = Vect(tmpx,0.0f);
	physicshero->setVelocity(impulse);
}

void Hero::moveLeft()
{
	startDraw = false;
	auto tmpx = sqrt(visibleSize.width * 120);
	Vect impulse = Vect(-tmpx, 0.0f);
	physicshero->setVelocity(impulse);
}

void Hero::moveStop()
{
	startDraw = false;
	Vect impulse = Vect(0.0f, 0.0f);
	physicshero->setVelocity(impulse);
}

void Hero::MyUpdate(float time) {
	switch (Hero::state)	//调用函数，使用setState可能会出错
	{
	case 3:
		Hero::moveLeft();
		break;
	case 4:
		log("UUUUUUUUUUUURRRRRRRRRRRRRRRRR");
		Hero::moveRight();
		break;
	case 5:
		Hero::moveStop();
		break;
	default:
		break;
	}
	if (state == 6) {	//
		Hero::rotateArrow(Hero::archAngle);
	}
	if (drawNode) {
		//drawNode->drawPoint(Vec2(0, 0), 0.0f, Color4F(1.0, 0.0, 0.0, 1.0));
		drawNode->removeFromParentAndCleanup(true); drawNode = NULL;
	}
	if (!startDraw) {
		return;
	}
	if (drawNode) {
		drawNode->removeFromParentAndCleanup(true); drawNode = NULL;
	}
	drawNode = DrawNode::create();
	//hero->getPosition().x + hero->archpos.width * 1 / 3, hero->getPosition().y - hero->archpos.height * 2 / 9
	drawNode->drawQuadBezier(Vec2(playerarrow->getPosition().x / 2, playerarrow->getPosition().y), bezier.controlPoint, bezier.endPosition, 100, Color4F(1.0, 0.0, 0.0, 1.0));
	//drawNode->drawQuadBezier(Vec2(playerarrow->getPosition().x / 2, playerarrow->getPosition().y), bezier.controlPoint, bezier.endPosition, 100, Color4F(1.0, 0.0, 0.0, 1.0));
	this->addChild(drawNode, -2);


}





