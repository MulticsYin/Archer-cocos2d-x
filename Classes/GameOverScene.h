#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "MyUtility.h"

#include "SystemHeader.h"
#include "PlaySceneOne.h"
#include "PlaySceneTwo.h"
#include "PlaySceneThree.h"
#include "PlaySceneFour.h"
#include "PlaySceneFive.h"
#include "PlaySceneSix.h"
#include "PlaySceneSeven.h"
#include "PlaySceneEight.h"
#include "PlaySceneNine.h"

typedef  enum {
	Menu1,
	Menu2
} ActionType1;

class GameOverLayer : public cocos2d::Layer
{
public:
	//返回第几关的参数
	int playSceneNum;

	GameOverLayer(int playSceneNum);
	virtual bool init();
	virtual void onExit();
	void menuItemCallback(cocos2d::Ref *sender);
	static GameOverLayer* createScene(int playSceneNum);
	//CREATE_FUNC(GameOverLayer);
};

#endif // __GAMEOVER_SCENE_H__
