#include "HelpScene.h"

USING_NS_CC;

Scene* HelpLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelpLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelpLayer::init()
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
	auto shezhiSprite = Sprite::create("picture/base.jpg");
	shezhiSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(shezhiSprite, 0);

	auto top = Sprite::create("picture/help-top.png");
	top->setPosition(Vec2(top->getContentSize().width/2 + 50 , visibleSize.height - top->getContentSize().height /2));
	addChild(top,0);

	//设置“开发”文字.
	auto txtKaifa = Label::createWithTTF(MyUtility::getUTF8Char("kaifa"), "fonts/hanyi.ttf", 32);
	txtKaifa->setColor(Color3B(14,83,204));
	txtKaifa->setPosition(visibleSize.width/2 - 120, visibleSize.height/2);
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

/*	//设置 音乐下文字 YunLong
	auto music2 = Label::createWithTTF("YunLong", "fonts/hanyi.ttf", 18);
	music2->setAnchorPoint(Vec2(0,0));
	Vec2 p4 = Meigong->convertToWorldSpace(Vec2(0, -20));
	music2->setColor(Color3B(198,12,0));	
	music2->setPosition(p4);
	addChild(music2, 1);

	//设置“音效”文字.
	auto txtSound = Label::createWithTTF(MyUtility::getUTF8Char("sound"), "fonts/hanyi.ttf", 18);
	txtSound->setColor(Color3B(14,83,204));	
	Vec2 p5 = music2->convertToWorldSpace(Vec2(0, -40));
	txtSound->setPosition(p5);
	txtSound->setAnchorPoint(Vec2(0,0));
	addChild(txtSound, 1);

	//设置 音效下文字 Mr.Zhao
	auto sound1 = Label::createWithTTF("Mr.Zhao", "fonts/hanyi.ttf", 18);
	sound1->setAnchorPoint(Vec2(0,0));
	Vec2 p6 = txtSound->convertToWorldSpace(Vec2(0, -20));
	sound1->setColor(Color3B(198,12,0));	
	sound1->setPosition(p6);
	addChild(sound1, 1);

	//设置 音效下文字 YunLong
	auto sound2 = Label::createWithTTF("YunLong", "fonts/hanyi.ttf", 18);
	sound2->setAnchorPoint(Vec2(0,0));
	Vec2 p7 = sound1->convertToWorldSpace(Vec2(0, -20));
	sound2->setColor(Color3B(198,12,0));	
	sound2->setPosition(p7);
	addChild(sound2, 1);

		//设置“信息与服务”文字.
	auto txtInfoService = Label::createWithTTF(MyUtility::getUTF8Char("info_service"), "fonts/hanyi.ttf", 18);
	txtInfoService->setColor(Color3B(14,83,204));	
	Vec2 p8 = sound2->convertToWorldSpace(Vec2(0, -40));
	txtInfoService->setPosition(p8);
	txtInfoService->setAnchorPoint(Vec2(0,0));
	addChild(txtInfoService, 1);

	//设置 信息与服务 下文字 
	auto infoService = Label::createWithTTF("www.51work6.com", "fonts/hanyi.ttf", 18);
	infoService->setAnchorPoint(Vec2(0,0));
	Vec2 p9 = txtInfoService->convertToWorldSpace(Vec2(0, -20));
	infoService->setColor(Color3B(198,12,0));	
	infoService->setPosition(p9);
	addChild(infoService, 1);
*/

//Ok菜单.
	auto okNormal = Sprite::create("picture/setting.button.ok.png");
	auto okSelected = Sprite::create("picture/setting.button.ok-on.png");

	auto okMenuItem = MenuItemSprite::create(okNormal, okSelected, CC_CALLBACK_1(HelpLayer::menuBackCallback, this));
	auto mu = Menu::create(okMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - okMenuItem->getContentSize().width / 2 - 10, okMenuItem->getContentSize().height - 10));
	addChild(mu, 0);


	return true;
}


void HelpLayer::menuBackCallback(Ref* pSender)
{
	Scene* tsc3 = nullptr;
	tsc3 = TransitionFade::create(1.0f, HomeMenuLayer::createScene());
	//Director::getInstance()->popScene(tsc1);
	Director::getInstance()->replaceScene(tsc3);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void HelpLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}