#include "HomeScene.h"

USING_NS_CC;

Scene* HomeMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HomeMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HomeMenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	// 加入了右上角游戏结束菜单；
	auto closeItem = MenuItemImage::create(
		"menu/quit.png",
		"menu/quit_0.png",
		CC_CALLBACK_1(HomeMenuLayer::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 50 ,origin.y + visibleSize.height - closeItem->getContentSize().height / 2 - 50));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//加入主界面背景；
	auto sprite = Sprite::create("background/home.png");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sprite, 0);

	// 开始菜单
	auto startSpriteNormal = Sprite::create("menu/home1.png");
	auto startSpriteSelected = Sprite::create("menu/home1_0.png");
	auto startMenuItem = MenuItemSprite::create(
		startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	log("beging.........");
	startMenuItem->setTag(ActionType::MenuItemStart);

	// 设置菜单
	auto settingSpriteNormal = Sprite::create("menu/home2.png");
	auto settingSpriteSelected = Sprite::create("menu/home2_0.png");
	auto settingMenuItem = MenuItemSprite::create(
		settingSpriteNormal,
		settingSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	log("set.......");
	settingMenuItem->setTag(ActionType::MenuItemSetting);

	// 帮助菜单
	auto helppriteNormal = Sprite::create("menu/home3.png");
	auto helpSpriteSelected = Sprite::create("menu/home3_0.png");
	auto helpMenuItem = MenuItemSprite::create(
		helppriteNormal,
		helpSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	log("help.....");
	helpMenuItem->setTag(ActionType::MenuItemHelp);


	//设置主界面按钮位置（三个一起设置的方法，为更具有灵活性，采用下面分开设置的方法）；
//	auto mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);	
//	mu->setPosition(visibleSize.width/2, visibleSize.height/2);
//	mu->alignItemsVerticallyWithPadding(12);
//	addChild(mu);

	//设置主界面按钮位置（分开设置）；
	//开始菜单位置；
	auto startMenu = Menu::create(startMenuItem, NULL);
	startMenu->setPosition(origin.x + startMenuItem->getContentSize().width / 2, origin.y + startMenuItem->getContentSize().height/2 + 30);
	startMenu->alignItemsVerticallyWithPadding(12);
	addChild(startMenu);

	//设置菜单位置；
	auto settingMenu = Menu::create(settingMenuItem, NULL);
	settingMenu->setPosition(origin.x + visibleSize.width / 2,origin.y + settingMenuItem->getContentSize().height/2 + 30);
	settingMenu->alignItemsVerticallyWithPadding(12);
	addChild(settingMenu);

	//帮助菜单位置；
	auto helpMenu = Menu::create(helpMenuItem, NULL);
	helpMenu->setPosition(origin.x + visibleSize.width - helpMenuItem->getContentSize().width/2, origin.y + helpMenuItem->getContentSize().height / 2 + 30);
	helpMenu->alignItemsVerticallyWithPadding(12);
	addChild(helpMenu);

	return true;
}

//设置右上角结束游戏按钮的回调函数，使程序终止；
void HomeMenuLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


void HomeMenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HomeMenuLayer onEnterTransitionDidFinish");	
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}


void HomeMenuLayer::menuItemCallback(cocos2d::Ref *sender)
{

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Scene* tsc = nullptr;

	MenuItem* menuItem = (MenuItem*)sender;
	log("MenuItem Tag = %d", menuItem->getTag());
	switch(menuItem->getTag())
	{
	case ActionType::MenuItemStart:
		tsc = TransitionFade::create(1.0f, DirectoryMenuLayer::createScene());
		log("StartCallback");
		break;
	case ActionType::MenuItemHelp:
		tsc = TransitionFade::create(1.0f, TeamLayer::createScene());
		log("HelpCallback");
		break;
	case ActionType::MenuItemSetting:
		tsc = TransitionFade::create(1.0f, SettingLayer::createScene());
		log("SettingCallback");
		break;
	}
	if (tsc)
		Director::getInstance()->replaceScene(tsc);

}