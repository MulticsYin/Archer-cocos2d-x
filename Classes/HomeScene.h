#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include "SettingScene.h"
#include "TeamScene.h"
#include "SystemHeader.h"
#include "GameDirectory.h"

class HomeMenuLayer : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnterTransitionDidFinish();

	void menuItemCallback(cocos2d::Ref *sender);

	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HomeMenuLayer);
};

#endif // __HOME_SCENE_H__
