#include "GameDirectory.h"
USING_NS_CC;

Scene* DirectoryMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = DirectoryMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool DirectoryMenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加游戏主目录背景；
	auto sprite = Sprite::create("background/dir0.jpg");
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(sprite, 0);

	//目录选择菜单1；
	auto One = Sprite::create("GameDirectory/1.png");
	auto One0 = Sprite::create("GameDirectory/11.png");
	auto OneMenuItem = MenuItemSprite::create(
		One,
		One0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));
	//设置游戏选关菜单1的位置（下同）；
	OneMenuItem->setTag(ActionType::MenuOne);
	auto OneMenu = Menu::create(OneMenuItem, NULL);
	OneMenu->setPosition(origin.x + visibleSize.width / 5, origin.y + visibleSize.height/5 * 4);
	OneMenu->alignItemsVerticallyWithPadding(12);
	addChild(OneMenu);

	//目录选择菜单2；
	auto Two = Sprite::create("GameDirectory/2.png");
	auto Two0 = Sprite::create("GameDirectory/22.png");
	auto TwoMenuItem = MenuItemSprite::create(
		Two,
		Two0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	TwoMenuItem->setTag(ActionType::MenuTwo);
	auto TwoMenu = Menu::create(TwoMenuItem, NULL);
	TwoMenu->setPosition(origin.x + visibleSize.width / 5 * 2, origin.y + visibleSize.height / 5 * 4);
	TwoMenu->alignItemsVerticallyWithPadding(12);
	addChild(TwoMenu);

	//目录选择菜单3；
	auto Three = Sprite::create("GameDirectory/3.png");
	auto Three0 = Sprite::create("GameDirectory/33.png");
	auto ThreeMenuItem = MenuItemSprite::create(
		Three,
		Three0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	ThreeMenuItem->setTag(ActionType::MenuThree);
	auto ThreeMenu = Menu::create(ThreeMenuItem, NULL);
	ThreeMenu->setPosition(origin.x + visibleSize.width / 5 * 3, origin.y + visibleSize.height / 5 * 4);
	ThreeMenu->alignItemsVerticallyWithPadding(12);
	addChild(ThreeMenu);

	//目录选择菜单4；
	auto Four = Sprite::create("GameDirectory/4.png");
	auto Four0 = Sprite::create("GameDirectory/44.png");
	auto FourMenuItem = MenuItemSprite::create(
		Four,
		Four0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	FourMenuItem->setTag(ActionType::MenuFour);
	auto FourMenu = Menu::create(FourMenuItem, NULL);
	FourMenu->setPosition(origin.x + visibleSize.width / 5 * 4, origin.y + visibleSize.height / 5 * 4);
	FourMenu->alignItemsVerticallyWithPadding(12);
	addChild(FourMenu);

	//目录选择菜单5；
	auto Five = Sprite::create("GameDirectory/5.png");
	auto Five0 = Sprite::create("GameDirectory/55.png");
	auto FiveMenuItem = MenuItemSprite::create(
		Five,
		Five0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	FiveMenuItem->setTag(ActionType::MenuFive);
	auto FiveMenu = Menu::create(FiveMenuItem, NULL);
	FiveMenu->setPosition(origin.x + visibleSize.width / 4, origin.y + visibleSize.height / 5 * 3);
	FiveMenu->alignItemsVerticallyWithPadding(12);
	addChild(FiveMenu);

	//目录选择菜单6；
	auto Six = Sprite::create("GameDirectory/6.png");
	auto Six0 = Sprite::create("GameDirectory/66.png");
	auto SixMenuItem = MenuItemSprite::create(
		Six,
		Six0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	SixMenuItem->setTag(ActionType::MenuSix);
	auto SixMenu = Menu::create(SixMenuItem, NULL);
	SixMenu->setPosition(origin.x + visibleSize.width / 4 * 2, origin.y + visibleSize.height / 5 * 3);
	SixMenu->alignItemsVerticallyWithPadding(12);
	addChild(SixMenu);
	/*
	//目录选择菜单7；
	auto Seven = Sprite::create("GameDirectory/7.png");
	auto Seven0 = Sprite::create("GameDirectory/77.png");
	auto SevenMenuItem = MenuItemSprite::create(
		Seven,
		Seven0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	SevenMenuItem->setTag(ActionType::MenuSeven);
	auto SevenMenu = Menu::create(SevenMenuItem, NULL);
	SevenMenu->setPosition(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 5 * 2);
	SevenMenu->alignItemsVerticallyWithPadding(12);
	addChild(SevenMenu);
	*/
	//目录选择菜单8；改为7
	auto Eight = Sprite::create("GameDirectory/7.png");//原来是8
	auto Eight0 = Sprite::create("GameDirectory/77.png");
	auto EightMenuItem = MenuItemSprite::create(
		Eight,
		Eight0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	EightMenuItem->setTag(ActionType::MenuEight);
	auto EightMenu = Menu::create(EightMenuItem, NULL);
	EightMenu->setPosition(origin.x + visibleSize.width / 4  * 3 , origin.y + visibleSize.height / 5 * 3);
	EightMenu->alignItemsVerticallyWithPadding(12);
	addChild(EightMenu);
	/*
	//目录选择菜单9；
	auto Nine = Sprite::create("GameDirectory/9.png");
	auto Nine0 = Sprite::create("GameDirectory/99.png");
	auto NineMenuItem = MenuItemSprite::create(
		Nine,
		Nine0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	NineMenuItem->setTag(ActionType::MenuNine);
	auto NineMenu = Menu::create(NineMenuItem, NULL);
	NineMenu->setPosition(origin.x + visibleSize.width / 5 * 3, origin.y + visibleSize.height / 5 * 2);
	NineMenu->alignItemsVerticallyWithPadding(12);
	addChild(NineMenu);
	*/
	//返回主菜单；
	auto Home = Sprite::create("menu/return.png");
	auto Home0 = Sprite::create("menu/return_0.png");
	auto HomeMenuItem = MenuItemSprite::create(
		Home,
		Home0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	HomeMenuItem->setTag(ActionType::MenuHome);
	auto HomeMenu = Menu::create(HomeMenuItem, NULL);
	HomeMenu->setPosition(origin.x + visibleSize.width / 5 * 4, origin.y + visibleSize.height / 7);
	HomeMenu->alignItemsVerticallyWithPadding(12);
	addChild(HomeMenu);

	//游戏攻略按钮；
	auto Way = Sprite::create("menu/way.png");
	auto Way0 = Sprite::create("menu/way_0.png");
	auto WayMenuItem = MenuItemSprite::create(
		Way,
		Way0,
		CC_CALLBACK_1(DirectoryMenuLayer::menuItemCallback, this));

	WayMenuItem->setTag(ActionType::MenuWay);
	auto WayMenu = Menu::create(WayMenuItem, NULL);
	WayMenu->setPosition(origin.x + visibleSize.width / 5 * 1, origin.y + visibleSize.height / 7);
	WayMenu->alignItemsVerticallyWithPadding(12);
	addChild(WayMenu);

	return true;
}

void DirectoryMenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HomeMenuLayer onEnterTransitionDidFinish");
	UserDefault *defaults  = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1, true);
	}
}

//添加游戏目录的回调函数，有新的关卡后需修改以下回调函数；
//在目录选择界面采用pushScene的方法切换场景，故在游戏关卡中需采用popScene
void DirectoryMenuLayer::menuItemCallback(cocos2d::Ref *sender)
{

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
	Scene* tsc = nullptr;

	MenuItem* menuItem = (MenuItem*)sender;
	log("MenuItem Tag = %d", menuItem->getTag());
	switch(menuItem->getTag())
	{
	case ActionType::MenuOne:
		tsc = TransitionFade::create(1.0f, newScene::createScene());
		log("DirectoryOne....");
		break;
	case ActionType::MenuTwo:
		tsc = TransitionFade::create(1.0f, PlaySceneTwo::createScene());
		log("DirectoryTwo....");
		break;
	case ActionType::MenuThree:
		tsc = TransitionFade::create(1.0f, PlaySceneThree::createScene());
		log("DirectoryTwo....");
		break;
	case ActionType::MenuFour:
		tsc = TransitionFade::create(1.0f, PlaySceneFour::createScene());
		log("DirectoryFour....");
		break;
	case ActionType::MenuFive:
		tsc = TransitionFade::create(1.0f, PlaySceneFive::createScene());
		log("DirectoryFive....");
		break;
	case ActionType::MenuSix:
		tsc = TransitionFade::create(1.0f, PlaySceneSix::createScene());
		log("DirectorySix....");
		break;
	case ActionType::MenuSeven:
		tsc = TransitionFade::create(1.0f, PlaySceneSeven::createScene());
		log("DirectorySeven....");
		break;
	case ActionType::MenuEight:
		tsc = TransitionFade::create(1.0f, PlaySceneEight::createScene());
		log("DirectoryEight....");
		break;
	case ActionType::MenuNine:
		tsc = TransitionFade::create(1.0f, PlaySceneNine::createScene());
		log("DirectoryNine....");
		break;
	case ActionType::MenuHome:
		tsc = TransitionFade::create(1.0f, HomeMenuLayer::createScene());
		log("DirectoryNine....");
		break;
	case ActionType::MenuWay:
		tsc = TransitionFade::create(1.0f, WayLayer::createScene());
		log("DirectoryNine....");
		break;

	}
	if (tsc)
		//Director::getInstance()->pushScene(tsc);
		Director::getInstance()->replaceScene(tsc);

}
