#include "SettingScene.h"

USING_NS_CC;

Scene* SettingLayer::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = SettingLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//加入设置背景图片；
	auto shezhiSprite = Sprite::create("background/set.png");
	shezhiSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(shezhiSprite, 0);

	//设置界面左上角设置图标；
	auto top = Sprite::create("menu/set.png");
	top->setPosition(Vec2(top->getContentSize().width/2 + 100, visibleSize.height - top->getContentSize().height /2 - 50));
	addChild(top);

	
	//音效选中按钮；
	auto soundOnSprite  = Sprite::create("menu/on1.png");
	auto soundOffSprite  = Sprite::create("menu/off1.png");
	
	auto soundOnMenuItem = MenuItemSprite::create(soundOnSprite, NULL);
	auto soundOffMenuItem = MenuItemSprite::create(soundOffSprite, NULL);
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuSoundToggleCallback, this), soundOnMenuItem,soundOffMenuItem, NULL);

	//音乐选中按钮；
	auto musicOnSprite  = Sprite::create("menu/on2.png");
	auto musicOffSprite  = Sprite::create("menu/off2.png");
	
	auto musicOnMenuItem = MenuItemSprite::create(musicOnSprite, NULL);
	auto musicOffMenuItem = MenuItemSprite::create(musicOffSprite, NULL);
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuMusicToggleCallback, this), musicOnMenuItem,musicOffMenuItem, NULL);

/*	//设置按钮以及标签位置（两个一起设置）；
	auto  menu = Menu::create(soundToggleMenuItem, musicToggleMenuItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2 - 70) + Vec2(100, 50));
	menu->alignItemsVerticallyWithPadding(30.0f);
	addChild(menu, 1);

	auto lblSound = Label::createWithTTF(MyUtility::getUTF8Char("lblSound"), "fonts/hanyi.ttf", 72);
	lblSound->setColor(Color3B(14,83,204));	
	lblSound->setPosition(menu->getPosition() - Vec2(250, -100));
	addChild(lblSound, 1);

	auto lblMusic = Label::createWithTTF(MyUtility::getUTF8Char("lblMusic"), "fonts/hanyi.ttf", 72);
	lblMusic->setColor(Color3B(14,83,204));	
	lblMusic->setPosition(lblSound->getPosition() - Vec2(20, 200));
	addChild(lblMusic, 1);
*/

	auto  menu = Menu::create(soundToggleMenuItem, musicToggleMenuItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 7 * 5, visibleSize.height / 2));
	menu->alignItemsVerticallyWithPadding(40.0f);
	addChild(menu, 1);

	auto lblSound = Label::createWithTTF(MyUtility::getUTF8Char("lblSound"), "fonts/hanyi.ttf", 60);
	lblSound->setColor(Color3B(14, 83, 204));
	lblSound->setPosition(Vec2(visibleSize.width / 7 * 4, visibleSize.height / 16 * 9.5));
	addChild(lblSound, 1);

	auto lblMusic = Label::createWithTTF(MyUtility::getUTF8Char("lblMusic"), "fonts/hanyi.ttf", 60);
	lblMusic->setColor(Color3B(14, 83, 204));
	lblMusic->setPosition(Vec2(visibleSize.width / 7 * 4, visibleSize.height / 16 * 7));
	addChild(lblMusic, 1);

	//设置音效和音乐选中状态
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		musicToggleMenuItem->setSelectedIndex(0);
	} else {
		musicToggleMenuItem->setSelectedIndex(1);		
	}
	if (defaults->getBoolForKey(SOUND_KEY)) {
		soundToggleMenuItem->setSelectedIndex(0);
	} else {
		soundToggleMenuItem->setSelectedIndex(1);
	}


	//Ok菜单.
	auto okNormal = Sprite::create("menu/return.png");
	auto okSelected = Sprite::create("menu/return_0.png");

	auto okMenuItem = MenuItemSprite::create(okNormal, okSelected, CC_CALLBACK_1(SettingLayer::menuBackCallback, this));
	auto mu = Menu::create(okMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - okMenuItem->getContentSize().width / 2 - 10, okMenuItem->getContentSize().height - 10));
	addChild(mu, 0);

	return true;
}

void SettingLayer::menuSoundToggleCallback(Ref* pSender)
{
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY)) {
		defaults->setBoolForKey(SOUND_KEY, false);
	} else {
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}


void SettingLayer::menuMusicToggleCallback(Ref* pSender)
{
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	} else {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2, true);
	}
}


void SettingLayer::menuBackCallback(Ref* pSender)
{
	Scene* tsc2 = nullptr;
	tsc2 = TransitionFade::create(1.0f, HomeMenuLayer::createScene());
	Director::getInstance()->replaceScene(tsc2);
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void SettingLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}
