//定义了碰撞监听的标识位的值
#include <cocos2d.h>
using namespace cocos2d;

USING_NS_CC;

#define HERO_BIT_MASK		0b1000000000
#define BRIDGE_BIT_MASK		0b0100000000
#define GROUND_BIT_MASK		0b0010000000
#define CIRCLE_BIT_MASK		0b0001000000
#define DEAD_LINE_BIT_MASK			0b0000100000
#define ARROW_BIT_MASK		0b0000010000
#define MONSTER1_BIT_MASK	0b0000001000
#define OBJECT_BIT_MASK		0b0000000100
#define DOOR_BIT_MASK		0b0000000010
#define CAN_DISPEAR_BIT_MASK 0b0000000001

/*
#include "PlaySceneOne.h"
#include "PlaySceneTwo.h"
#include "PlaySceneThree.h"
#include "PlaySceneFour.h"
#include "PlaySceneFive.h"
#include "PlaySceneSix.h"
#include "PlaySceneSeven.h"
#include "PlaySceneEight.h"
#include "PlaySceneNine.h"
#include "PlayMapOne.h"
#include "PlayMapTwo.h"
#include "PlayMapThree.h"
#include "PlayMapFour.h"
#include "PlayMapFive.h"
#include "PlayMapSix.h"
#include "PlayMapSeven.h"
#include "PlayMapEight.h"
#include "PlayMapNine.h"
*/
#pragma once
