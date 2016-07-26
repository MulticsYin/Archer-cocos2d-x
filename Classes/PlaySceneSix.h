#ifndef PLAYSCENESIX
#define PLAYSCENESIX
#include "cocos2d.h"
#include "Hero.h"
#include "PLayMapSix.h"
#include "GameOverScene.h"
#include "GameDirectory.h"
#include "arrow.h"
using namespace cocos2d;
USING_NS_CC;
#include "contact_data.h"

class PlaySceneSix : public Layer {
public:
	//第几个关
	int playSceneNum;
	Animation* createAnimation(std::string prefixName, int framesNum, float delay);
	Hero* hero;
	Size visibleSize;
	Point proposL, proposM,proposR;
	virtual bool init();
	bool isover;//ccQuadBezierConfig

	//碰撞相关
	EventListenerPhysicsContact* contactListener;
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactPreSolve(PhysicsContact&  contact,PhysicsContactPreSolve&  solve);
	virtual void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	virtual void onContactSeparate(PhysicsContact& contact);

	Rect ControlrectMove;
	Rect ControlrectShot;
	Rect ControlrectJump;
	EventListenerTouchOneByOne* Singlelistener;
	virtual bool onTouchBegan(Touch* touches, Event* event);
	virtual void onTouchMoved(Touch* touches, Event* event);
	virtual void onTouchEnded(Touch* touches, Event* event);
	//Singlelistener->onTouchMoved = CC_CALLBACK_2(NewScene::onTouchMoved, this);
	//Singlelistener->onTouchEnded = CC_CALLBACK_2(NewScene::onTouchEnded, this);
	bool ontouch;
	static cocos2d::Scene* createScene();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	//virtual void onEnterTransitionDidFinish();
	PlayMapSix * map;
	Sprite * gameover;
	double distance;    //两个触摸点之间的距离  为多点触摸准备
	double deltax;    //目标x轴的改变值  
	double deltay;    //目标y轴的改变值  
	double mscale;   //初始地图缩放比例
	CREATE_FUNC(PlaySceneSix);

	Scene* gameOverScene;
	Menu* menu;
	void menuPauseCallback(Ref* pSender);
	void menuBackCallback(Ref* pSender);
	void menuResumeCallback(Ref* pSender);
	// 计时器更新函数，每帧一次
	void Update(float time);
	void isGameOver();
};
#endif
