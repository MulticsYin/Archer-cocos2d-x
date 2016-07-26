#include "PlaySceneNine.h"
#include "PlayMapNine.h"
#include "Hero.h"
#include "Circle.h"
#include "Board.h"
#include "Ground.h"
#include "SystemHeader.h"
#include "HomeScene.h"
#include "GameDirectory.h"

#define PLAY_SCENE_NUM 9
using namespace cocos2d;

/*还要实现：
死亡返回（主角是否掉下山，是否撞倒什么）
按键返回（CALL_BACK）
通关返回（有多的场景做下一关）
连跳避免（未完成，暂留）
碰撞机制*/

Scene* PlaySceneNine::createScene()
{
	auto scene = Scene::createWithPhysics();
//	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	//设置保留调试线
	scene->getPhysicsWorld()->setGravity(Vec2(0, -1000));
	auto layer = PlaySceneNine::create();
	scene->addChild(layer);
	log("NEWSCENEEXECUTINNNNNNNNG!!!!!!!!!!!!");
	return scene;
}

bool PlaySceneNine::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	log("NEWSCENEEXECUTINNN             INIT!!!!!!!!!!!!");
	//添加纹理图.
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture.plist", "texture.pvr.ccz");
	auto animation = createAnimation("player", 8, 0.06f);
	AnimationCache::getInstance()->addAnimation(animation, "player");
	return true;

}

Animation* PlaySceneNine::createAnimation(std::string prefixName, int framesNum, float delay)
{
	Vector<SpriteFrame*> animFrames;

	for (int i = 1; i <= framesNum; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%i.png", i);
		std::string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	return Animation::createWithSpriteFrames(animFrames, delay);
}

void PlaySceneNine::onEnter()
{
	Layer::onEnter();

	visibleSize = Director::getInstance()->getVisibleSize();
	log("NEWSCENEEXECUTINNNNNNNNG!!!!!!!!!!!!2");

	//加入设置背景图片；
	auto gameSprite = Sprite::create("map/bj3.jpg");
	gameSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(gameSprite, 0);

	//定义三个长按触摸控制范围
	//左下脚区域，移动控制
	auto ControlrectMove = Rect(Vec2(0, 0), Size(visibleSize.width / 3, visibleSize.height /3));
	//上侧射箭区域
	auto ControlrectShot = Rect(Vec2(0, visibleSize.height / 3), Size(visibleSize.width, visibleSize.height * 2 / 3));
	//右下区域
	auto ControlrectJump = Rect(Vec2(visibleSize.width *2/ 3, 0), Size(visibleSize.width / 3, visibleSize.height / 3));
	Point origin = Director::getInstance()->getVisibleOrigin();
	log("NEWSCENEEXECUTINNNNNNNNG!!!!!!!!!!!!5");
	//为上面的两个区域提供指示的箭头
	auto movearrow = Sprite::create("controlrectmove.png");	//静态的
	movearrow->setAnchorPoint(Point(0, 0));
	movearrow->setPosition(0, 0);
	this->addChild(movearrow, 200);
	auto jumparrow = Sprite::create("controlrectjump.png");	//静态的
	jumparrow->setAnchorPoint(Point(1, 0));
	jumparrow->setPosition(visibleSize.width,0);
	this->addChild(jumparrow, 200);

	//创建一个触摸监听
	auto Singlelistener = EventListenerTouchOneByOne::create();
	Singlelistener->setSwallowTouches(false); // 设置是否向下传递触摸,是
											  //不要使用回调函数
	Singlelistener->onTouchBegan = [ControlrectMove, ControlrectShot, ControlrectJump, this](Touch* touches, Event* event) {
		log("touchBeganNNNNN执行了---------------------------------------------");
		ontouch = 1;
		Touch* touch = static_cast<Touch*>(touches);
		Point locationInNodelocal = touch->getLocation();
		if (ControlrectMove.containsPoint(locationInNodelocal)) {
			proposL = locationInNodelocal;
		}
		else if (ControlrectJump.containsPoint(locationInNodelocal)) {
			proposR = locationInNodelocal;
		}
		else if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotbegan");
			proposM = locationInNodelocal;////////////////////////
			hero->archAngle = locationInNodelocal;
			hero->rotateArrow(hero->archAngle); hero->setState(7);
		}
		return true;
	};

	Singlelistener->onTouchMoved = [ControlrectMove, ControlrectShot, ControlrectJump, this](Touch* touches, Event* event) {
		log("touchMMMMMMMMMOOVVEDDD执行了---------------------------------------------");
		// 获取当前触摸的目标
		Touch* touch = static_cast<Touch*>(touches);
		Point locationInNodelocal = touch->getLocation();

		//log("GameObjHero::onTouchBegan::rx=%0.2f, ry=%0.2f, rw=%0.2f, rh=%0.2f, lx=%0.2f, ly=%0.2f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, locationInNode.x, locationInNode.y);
		//左侧手势 
		if (ControlrectMove.containsPoint(locationInNodelocal))
		{
			float adsxL = locationInNodelocal.x - proposL.x;
			float adsyL = locationInNodelocal.y - proposL.y;
			hero->locationInNode = locationInNodelocal;
			if (adsxL <= -50 && hero->state != 1) {	//减少手抖的影响且主角不在空中
				proposL = locationInNodelocal;
				// 设置运动状态：左移
				hero->setState(3); log("MMMMMMMMMOOOOOOOOVVVVEEEEE1");
			}
			else if (adsxL >= 50 && hero->state != 1) {
				proposL = locationInNodelocal;
				// 设置运动状态：右移
				hero->setState(4); log("MMMMMMMMMOOOOOOOOVVVVEEEEE2");
			}
		}
		//右上手势
		else if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotmoved");
			proposM = locationInNodelocal;////////////////////////;
			hero->archAngle = locationInNodelocal;
			hero->rotateArrow(hero->archAngle); hero->setState(7);
		}
		return true;
	};

	Singlelistener->onTouchEnded = [ControlrectMove, ControlrectShot, ControlrectJump, this](Touch* touches, Event* event) {
		Touch* touch = static_cast<Touch*>(touches);
		Point locationInNodelocal = touch->getLocation();
		ontouch = 0;

		//左侧区域手势
		if (ControlrectMove.containsPoint(locationInNodelocal)) {
			if (hero->state != 1)//主角不在空中
			{
				hero->stopAllActions();
				hero->setState(0);
			}
			//hero->setState(5);
		}
		//右下区域手势
		if (ControlrectJump.containsPoint(locationInNodelocal)) {
			float adsxR = locationInNodelocal.x - proposR.x;
			float adsyR = locationInNodelocal.y - proposR.y;
			hero->locationInNode = locationInNodelocal;
			if (adsxR <= -50 && adsyR >= 50 && hero->state != 1)
			{	//左上划，减少手抖的影响
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state); log("jumpppppppplift");
				// 设置运动状态:跳跃
				//auto jumpby = JumpBy::create(2.5, Point(-600, 0), hero->getContentSize().height, 1);
				/*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpLeft();
				//hero->state = 0;
			}
			else if (adsxR >= 50 && adsyR >= 50 && hero->state != 1)
			{	//右上滑
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state);
				log("jumppppppppright");
				//hero->setState(hero->state); log("jumppppppppright");
				// 设置运动状态:跳跃
				//auto jumpby = JumpBy::create(2.5, Point(600, 0), hero->getContentSize().height, 1);
				/*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpRight();
				//hero->state = 0;
			}
			else if (adsxR <= 50&&adsyR >= 50 && hero->state != 1)//向上滑
			{
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state); log("jumppppppppup");
				// 设置运动状态:跳跃
				/*auto jumpby = JumpBy::create(2.5, Point(0, 0), hero->getContentSize().height, 1);*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpUp();
				//hero->state = 0;
			}
		}
		//右上区域手势
		if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotend");
			proposM = locationInNodelocal;////////////////////////
			hero->archAngle = locationInNodelocal;
			hero->createAndShootArrow(hero->archAngle, map);
		}
		return true;
	};
	// 将触摸监听注册到eventDispacher中去
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(Singlelistener, this);

	//添加碰撞监听器，注意，1还是2根据回调函数参数个数
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlaySceneNine::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(PlaySceneNine::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(PlaySceneNine::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlaySceneNine::onContactSeparate, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//初始化暂停按钮.
	//auto pauseSprite = Sprite::createWithSpriteFrameName("gameplay.button.pause.png");
	auto pauseSprite = Sprite::create("backA.png");
	auto pauseMenuItem = MenuItemSprite::create(pauseSprite, pauseSprite,
		CC_CALLBACK_1(PlaySceneNine::menuPauseCallback, this));
	auto pauseMenu = Menu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(Vec2(visibleSize.width/16, visibleSize.height*15/16));
	this->addChild(pauseMenu, 20, 999);

	//加入测试用的关卡号
	auto star = Sprite::create("scene9.png");	//静态的
	star->setAnchorPoint(Point(0, 0));
	star->setPosition(visibleSize.width *9/ 10, visibleSize.height *9/ 10);
	this->addChild(star, 200);
	
	// 添加移动的地图
	map = PlayMapNine::create();
	map->setAnchorPoint(Point(0, 0));
	map->setPosition(Point(0, 0));
	addChild(map);
	log("NEWSCENEEXECUTINNNNNNNNG!!!!!!!!!!!!3");

	// 添加主角
	hero = Hero::create();
	//hero->setScale(0.5);
	hero->setAnchorPoint(Point(0, 0));
	hero->setPosition(map->heroposx, map->heroposy);
	hero->getPhysicsBody()->setContactTestBitmask(HERO_BIT_MASK);
	//hero->arrow->getPhysicsBody()->setContactTestBitmask(ARROW_BIT_MASK);
	addChild(hero);
	log("NEWSCENEEXECUTINNNNNNNNG!!!!!!!!!!!!4");

	// 游戏结束的图片精灵
	gameover = CCSprite::create("gameover.png");
	gameover->setAnchorPoint(Point(0.5, 0.5));
	gameover->setPosition(Point(0, 0));
	gameover->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 + 70));
	gameover->setVisible(false);
	//gameover->setScale(0.5);
	addChild(gameover);

	//Update每帧执行一次（1/60秒）
	schedule(schedule_selector(PlaySceneNine::Update));
}

bool PlaySceneNine::onTouchBegan(Touch* touches, Event* event)
{
	log("touchBeganNNNNN执行了---------------------------------------------");
	/*if (((PlaySceneOne *)this->getParent())->isover)
		return false;*/
	ontouch = 1;
	Touch* touch = static_cast<Touch*>(touches);
	Point locationInNodelocal = touch->getLocation();
		if (ControlrectMove.containsPoint(locationInNodelocal)) {
			proposL = locationInNodelocal;
		}
		else if (ControlrectJump.containsPoint(locationInNodelocal)) {
			proposR = locationInNodelocal;
		}
		else if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotbegan");
			proposM = locationInNodelocal;////////////////////////
			hero->archAngle = locationInNodelocal;
			hero->rotateArrow(hero->archAngle); hero->setState(7);
		}
	return true;
}

void PlaySceneNine::onTouchMoved(Touch* touches, Event* event)
{
	log("touchMMMMMMMMMOOVVEDDD执行了---------------------------------------------");
	// 获取当前触摸的目标
	Touch* touch = static_cast<Touch*>(touches);
	Point locationInNodelocal = touch->getLocation();

	//log("GameObjHero::onTouchBegan::rx=%0.2f, ry=%0.2f, rw=%0.2f, rh=%0.2f, lx=%0.2f, ly=%0.2f", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, locationInNode.x, locationInNode.y);
		//左侧手势 
		if (ControlrectMove.containsPoint(locationInNodelocal))
		{
			float adsxL = locationInNodelocal.x - proposL.x;
			float adsyL = locationInNodelocal.y - proposL.y;
			hero->locationInNode = locationInNodelocal;
			if (adsxL <= -50 && hero->state != 1) {	//减少手抖的影响且主角不在空中
				proposL = locationInNodelocal;
				// 设置运动状态：左移
				hero->setState(3); log("MMMMMMMMMOOOOOOOOVVVVEEEEE1");
			}
			else if (adsxL >= 50 && hero->state != 1) {
				proposL = locationInNodelocal;
				// 设置运动状态：右移
				hero->setState(4); log("MMMMMMMMMOOOOOOOOVVVVEEEEE2");
			}
		}
		//右上手势
		else if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotmoved");
			proposM = locationInNodelocal;////////////////////////;
			hero->archAngle = locationInNodelocal;
			hero->rotateArrow(hero->archAngle); hero->setState(7);
		}
}

void PlaySceneNine::onTouchEnded(Touch* touches, Event* event)
{
	Touch* touch = static_cast<Touch*>(touches);
	Point locationInNodelocal = touch->getLocation();
	ontouch = 0;
	
		//左侧手势
		if (ControlrectMove.containsPoint(locationInNodelocal)) {
			if (hero->state != 1)//主角不在空中
			{
				hero->stopAllActions();
				hero->setState(5);
			}
			//hero->setState(5);
		}
		//右下手势
		if (ControlrectJump.containsPoint(locationInNodelocal)) {
			float adsxR = locationInNodelocal.x - proposR.x;
			float adsyR = locationInNodelocal.y - proposR.y;
			hero->locationInNode = locationInNodelocal;
			if (adsxR <= -50&&adsyR >= 50&&hero->state!= 1)
			{	//左上划，减少手抖的影响
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state); log("jumpppppppplift");
				// 设置运动状态:跳跃
				//auto jumpby = JumpBy::create(2.5, Point(-600, 0), hero->getContentSize().height, 1);
				/*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpLeft();
				//hero->state = 0;
			}
			else if (adsxR>= 50&&adsyR>= 50&&hero->state != 1)
			{	//右上滑
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state); log("jumppppppppright");
				// 设置运动状态:跳跃
				//auto jumpby = JumpBy::create(2.5, Point(600, 0), hero->getContentSize().height, 1);
				/*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpRight();
				//hero->state = 0;
			}
			else if (adsyR>=50&&hero->state!= 1)//向上滑
			{
				proposL = locationInNodelocal;
				// 显示跳跃的动画
				hero->state = 1;
				hero->setState(hero->state); log("jumppppppppup");
				// 设置运动状态:跳跃
				/*auto jumpby = JumpBy::create(2.5, Point(0, 0), hero->getContentSize().height, 1);*hero->runAction(Sequence::create(jumpby,
				CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend, hero)), NULL));*/
				hero->jumpUp();
				//hero->state = 0;
			}
		}
		//右上手势
		if (ControlrectShot.containsPoint(locationInNodelocal)) {
			log("shotend");
			proposM = locationInNodelocal;////////////////////////
			hero->archAngle= locationInNodelocal; 
			hero->createAndShootArrow(hero->archAngle,map); 
			
		}
	
}

bool PlaySceneNine::onContactBegin(PhysicsContact &contact) {
	switch (contact.getShapeA()->getBody()->getContactTestBitmask()|
		contact.getShapeB()->getBody()->getContactTestBitmask())
	{
	case HERO_BIT_MASK|BRIDGE_BIT_MASK:	
	{
		log("hero contact bridge");
		hero->state = 0;//主角不在空中，在桥上
	}
		break;
	case HERO_BIT_MASK|GROUND_BIT_MASK:
	{
		log("on the ground");//主角在地上
		hero->state = 0;
	}
	break;
	case HERO_BIT_MASK|DEAD_LINE_BIT_MASK://主角掉到屏幕底部
	{
		log("GameOver");
		/*
		auto gameOverLayer = GameOverLayer::createScene();
		auto gameOverScene = Scene::create();
		gameOverScene->addChild(gameOverLayer);
		auto tsc = TransitionFade::create(1.0f, gameOverScene);
		Director::getInstance()->pushScene(tsc);
		*/
		this->isGameOver();
	}
	break;
	case HERO_BIT_MASK|MONSTER1_BIT_MASK://主角碰到怪物1
	{
		log("GameOver");	
	    this->isGameOver();
	}
	break;
	case DOOR_BIT_MASK | HERO_BIT_MASK://英雄进门
	{
		log("GameOVERisTouched");
		//Director::getInstance()->popScene();//不可使用
		auto tsc = TransitionFade::create(1.0f, DirectoryMenuLayer::createScene());
		Director::getInstance()->replaceScene(tsc);		//已经重写原来是pushScene

	}
	break;
	default:
		break;
	}
	if ((contact.getShapeA()->getBody()->getContactTestBitmask() |
		contact.getShapeB()->getBody()->getContactTestBitmask())&HERO_BIT_MASK) {
		hero->state = 0;//主角不在空中，它撞上了什么
	}
	return true;
}

bool PlaySceneNine::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	return true;
}

void PlaySceneNine::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {

}

void PlaySceneNine::onContactSeparate(PhysicsContact& contact) {

}

// 计时器更新函数，每帧一次
void PlaySceneNine::Update(float time) {
	log("UPDATE             !!!!!!!!!!!!");

	if (hero->getPosition().x<visibleSize.width / 3)	//主角若出了地图,左,使用setPosition,不是runAction
	{
		auto offset = visibleSize.width/3 - hero->getPosition().x;
		//auto draftby = MoveBy::create(2.5, Point(10, 0));
		map->setPosition(Vec2(offset + map->getPosition().x, map->getPosition().y));
		hero->setPosition(Vec2(visibleSize.width / 3+1, hero->getPosition().y));

	}
	else if (hero->getPosition().x>visibleSize.width *2/ 3)
	{
		auto offset = hero->getPosition().x-visibleSize.width * 2 / 3;
		//hero->stopAllActions();
		map->setPosition(Vec2(map->getPosition().x - offset, map->getPosition().y));
		hero->setPosition(Vec2(visibleSize.width*2/3-1, hero->getPosition().y));
	}
	//判定死亡
	//this->isGameOver();
}

void PlaySceneNine::onExit() {
	Layer::onExit();
	//停止调用 shootBullet函数.
	this->unschedule(schedule_selector(PlaySceneNine::Update));
	//注销事件监听器.
	Director::getInstance()->getEventDispatcher()->removeEventListener(Singlelistener);

	auto nodes = this->getChildren();
	for (const auto& node : nodes) {
		//如果是背景不进行remove
		auto subnodes = node->getChildren();
		for (const auto& subnode : subnodes) {
			node->removeChild(subnode,true);
			}
			this->removeChild(node,true);
		}
}

void PlaySceneNine::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GamePlayLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}

/*void NewScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GamePlayLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}*/

void PlaySceneNine::isGameOver()
{
	//无法返回游戏界面
		//选择重来
		log("GameOver");

		auto gameOverLayer = GameOverLayer::createScene(PLAY_SCENE_NUM);
		gameOverScene = Scene::create();
		gameOverScene->addChild(gameOverLayer);
		auto tsc = TransitionFade::create(1.0f, gameOverScene);
		Director::getInstance()->pushScene(tsc);
	

}

void PlaySceneNine::menuPauseCallback(Ref* pSender) {	//暂停按钮
	log("menuPauseCallback");
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	
	//
	//暂停当前层中的node，效果不佳
	this->pause();

	for (const auto& node : this->getChildren())
	{
		//for (const auto& subnode:node) {
		
		//}
		node->pause();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//返回主菜单
	auto backNormal = Sprite::create("menu/game2.png");
	auto backSelected = Sprite::create("menu/game2_0.png");

	auto backMenuItem = MenuItemSprite::create(backNormal, backSelected,
		CC_CALLBACK_1(PlaySceneNine::menuBackCallback, this));

	//继续游戏菜单
	auto resumeNormal = Sprite::create("menu/game1.png");
	auto resumeSelected = Sprite::create("menu/game1_0.png");

	auto resumeMenuItem = MenuItemSprite::create(resumeNormal, resumeSelected,
		CC_CALLBACK_1(PlaySceneNine::menuResumeCallback, this));

	menu = Menu::create(backMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	menu->alignItemsVerticallyWithPadding(20.0f);

	addChild(menu, 20, 1000);
	//---------------------
}

void PlaySceneNine::menuBackCallback(Ref* pSender)	//回到主界面
{
	log("menuBackCallback");
	/*
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}*/
	log("GameOVERisTouched");
	//Director::getInstance()->popScene();//不可使用
	auto tsc = TransitionFade::create(1.0f, DirectoryMenuLayer::createScene());
	Director::getInstance()->pushScene(tsc);
}

void PlaySceneNine::menuResumeCallback(Ref* pSender)		//回到游戏
{
	log("menuResumeCallback");
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	this->resume();

	for (const auto& node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);
}



