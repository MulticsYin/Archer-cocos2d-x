#include "WayScene.h"

USING_NS_CC;

Scene* WayLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WayLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool WayLayer::init()
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
	auto shezhiSprite = Sprite::create("background/way.png");
	shezhiSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(shezhiSprite, 0);

	//返回菜单.
	auto okNormal = Sprite::create("menu/return.png");
	auto okSelected = Sprite::create("menu/return_0.png");

	auto okMenuItem = MenuItemSprite::create(okNormal, okSelected, CC_CALLBACK_1(WayLayer::menuBackCallback, this));
	auto mu = Menu::create(okMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - okMenuItem->getContentSize().width / 2 - 10, okMenuItem->getContentSize().height - 10));
	addChild(mu, 0);


	return true;
}


void WayLayer::menuBackCallback(Ref* pSender)
{
	Scene* tsc3 = nullptr;
	tsc3 = TransitionFade::create(1.0f, DirectoryMenuLayer::createScene());
	//Director::getInstance()->popScene(tsc1);
	Director::getInstance()->replaceScene(tsc3);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void WayLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}