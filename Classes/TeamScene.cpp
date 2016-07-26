#include "TeamScene.h"

USING_NS_CC;

Scene* TeamLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TeamLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TeamLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//加入设置背景图片；
	auto shezhiSprite = Sprite::create("background/set.png");
	shezhiSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(shezhiSprite, 0);

	//团队界面左上角精灵；
	auto top = Sprite::create("menu/we.png");
	top->setPosition(Vec2(top->getContentSize().width/2 + 100 , visibleSize.height - top->getContentSize().height /2 - 50));
	addChild(top,0);

	//设置“开发”文字.
	auto txtKaifa = Label::createWithTTF(MyUtility::getUTF8Char("kaifa"), "fonts/hanyi.ttf", 32);
	txtKaifa->setColor(Color3B(14,83,204));
	txtKaifa->setPosition(visibleSize.width/2, visibleSize.height / 5 * 3);
	txtKaifa->setAnchorPoint(Vec2(0,0));
	addChild(txtKaifa, 1);

	//设置开发下文字 ChengHao YinXingDong
	auto Kaifa = Label::createWithTTF("ChengHao YinXingDong", "fonts/hanyi.ttf", 42);
	Kaifa->setAnchorPoint(Vec2(0,0));
	Vec2 p1 = txtKaifa->convertToWorldSpace(Vec2(0, -40));
	Kaifa->setColor(Color3B(198,12,0));
	Kaifa->setPosition(p1);
	addChild(Kaifa, 1);

	//设置“美工”文字.
	auto txtMeigong = Label::createWithTTF(MyUtility::getUTF8Char("meigong"), "fonts/hanyi.ttf", 32);
	txtMeigong->setColor(Color3B(14,83,204));
	Vec2 p2 = Kaifa->convertToWorldSpace(Vec2(0, -80));
	txtMeigong->setPosition(p2);
	txtMeigong->setAnchorPoint(Vec2(0,0));
	addChild(txtMeigong, 1);

	//设置 美工下文字 Mr.Guan
	auto Meigong = Label::createWithTTF("LiuYan", "fonts/hanyi.ttf", 42);
	Meigong->setAnchorPoint(Vec2(0,0));
	Vec2 p3 = txtMeigong->convertToWorldSpace(Vec2(0, -40));
	Meigong->setColor(Color3B(198,12,0));
	Meigong->setPosition(p3);
	addChild(Meigong, 1);

//Ok菜单.
	auto okNormal = Sprite::create("menu/return.png");
	auto okSelected = Sprite::create("menu/return_0.png");

	auto okMenuItem = MenuItemSprite::create(okNormal, okSelected, CC_CALLBACK_1(TeamLayer::menuBackCallback, this));
	auto mu = Menu::create(okMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - okMenuItem->getContentSize().width / 2 - 10, okMenuItem->getContentSize().height - 10));
	addChild(mu, 0);


	return true;
}


void TeamLayer::menuBackCallback(Ref* pSender)
{
	Scene* tsc3 = nullptr;
	tsc3 = TransitionFade::create(1.0f, HomeMenuLayer::createScene());
	//Director::getInstance()->popScene(tsc1);
	Director::getInstance()->replaceScene(tsc3);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void TeamLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}