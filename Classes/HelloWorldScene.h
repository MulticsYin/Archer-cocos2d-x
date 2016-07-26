#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HomeScene.h"
#include "SystemHeader.h"

class HelloWorld : public cocos2d::Layer
{
private:
	std::thread* _loadingAudioThread;
	void loadingAudio();
	void delayCall(float dt);
	void loadingTextureCallBack(cocos2d::Texture2D* texture);
	int m_nNumberOfLoaded;

public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	virtual void onExit();
    
	//官方原有函数 调试注释；
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);


    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
