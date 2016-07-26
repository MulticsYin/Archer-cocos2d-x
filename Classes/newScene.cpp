#include "newScene.h"

USING_NS_CC;

Scene* newScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = newScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool newScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//加入游戏攻略图片；
	auto HelpMenuSprite = Sprite::create("background/help.png");
	HelpMenuSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(HelpMenuSprite, 0);

	//继续菜单.
	auto HelpMenuNormal = Sprite::create("menu/game1.png");
	auto HelpMenuSelected = Sprite::create("menu/game1_0.png");

	auto HelpMenuItem = MenuItemSprite::create(HelpMenuNormal, HelpMenuSelected, CC_CALLBACK_1(newScene::menuBackCallback, this));
	auto helpmu = Menu::create(HelpMenuItem, NULL);
	helpmu->setPosition(HelpMenuItem->getContentSize().width / 2 + 10, visibleSize.height/7*2);
	addChild(helpmu, 0);


	return true;
}


void newScene::menuBackCallback(Ref* pSender)
{
	Scene* tsc4 = nullptr;
	tsc4 = TransitionFade::create(1.0f, PlaySceneOne::createScene());
	//Director::getInstance()->popScene(tsc1);
	Director::getInstance()->replaceScene(tsc4);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void newScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}