//
//  GameObjHero.h
//  example12-1
//
//  Created by shuoquan man on 12-10-14.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef example15_1_GameObjHero_h
#define example15_1_GameObjHero_h

#include "cocos2d.h"
#include "ArrowPathBezier.h"
#include "arrow.h"
#include "PlayMapOne.h"
#include "PlayMapTwo.h"
#include "PlayMapThree.h"
#include "PlayMapFour.h"
#include "PlayMapFive.h"
#include "PlayMapSix.h"
#include "PlayMapSeven.h"
#include "PlayMapEight.h"
#include "PlayMapNine.h"
#include "SystemHeader.h"
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

class Hero : public cocos2d::Sprite
{
public:
	Size visibleSize;

	Texture2D *mainsprite;
	Size physicsSize;
	PhysicsBody* physicshero;
	Texture2D *hurt;
	Texture2D *jump;
	Point locationInNode;
	Point offset;
	short state;    // 0:正常 1：跳跃 2：受伤 3:
	bool iscontrol;

	void setState(short var);
	virtual bool init();
	virtual void onExit();

	// 处理动画结束后的操作
	void jumpend();
	void hurtend();

	void moveRight();
	void moveLeft();
	void moveStop();
	void jumpUp();
	void jumpLeft();
	void jumpRight();
	void MyUpdate(float time);

	// 3x中，使用事件管理器对事件进行管理了
	//    bool containsTouchLocation(Touch* touch);
	//    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	//    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	//    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	//    virtual void touchDelegateRetain();
	//    virtual void touchDelegateRelease();
	//射箭相关
	Sprite* arrow;
	Point archAngle;
	bool isShooting;
	void rotateArrow(Point touchPoint);
	void createAndShootArrow(Point touchPoint, Layer* map);
	void shootArrow(Layer* map);
	void finishRunAction();
	bool startDraw=0;
	bool isRunAction = 0;
	//CC_SYNTHESIZE(bool, startDraw, StartDraw);
	//CC_SYNTHESIZE(bool, isRunAction, IsRunAction);
	Sprite* playerbody;        // 角色身体
	Sprite* playerarrow;       // 角色的弓箭，也就是会随触摸点旋转的弓和箭部分
	//CC_SYNTHESIZE(bool, startDraw, StartDraw);     // 是否开始画红色的路径线
	//CC_SYNTHESIZE(bool, isRunAction, IsRunAction); // 玩家是否正在执行射箭动画
	CREATE_FUNC(Hero);
	Vec2 playerPos;            // 角色在 tmx 地图上的位置
	Size archpos;           // 角色尺寸
	Size winSize;              // 屏幕窗口尺寸
	//Sprite* hPBgSprite;      // 角色血条背景精灵
	//ProgressTimer* hpBar;    // 角色血条
	ccQuadBezierConfig bezier; // 路径贝赛尔
	DrawNode* drawNode;        // 这里表示我们的线条对象

};
#endif
