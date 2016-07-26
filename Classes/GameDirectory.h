#ifndef __GAME_DIRECTORY_H__
#define __GAME_DIRECTORY_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "HomeScene.h"
#include "PlaySceneOne.h"
#include "PlaySceneTwo.h"
#include "PlaySceneThree.h"
#include "PlaySceneFour.h"
#include "PlaySceneFive.h"
#include "PlaySceneSix.h"
#include "PlaySceneSeven.h"
#include "PlaySceneEight.h"
#include "PlaySceneNine.h"
#include "WayScene.h"
#include "newScene.h"


typedef  enum {
	MenuOne,
	MenuTwo,
	MenuThree,
	MenuFour,
	MenuFive,
	MenuSix,
	MenuSeven,
	MenuEight,
	MenuNine,
	MenuItemStart,
	MenuItemSetting,
	MenuItemHelp,
	MenuWay,
	MenuHome
} ActionType;

class DirectoryMenuLayer : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	void menuItemCallback(cocos2d::Ref *sender);

	// implement the "static create()" method manually
	CREATE_FUNC(DirectoryMenuLayer);
};

#endif // __GAME_DIRECTORY_H_
