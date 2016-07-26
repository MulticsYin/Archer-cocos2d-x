#include "PlayMapNine.h"

//根据tmx决定
#define BODY_GID 9
#define GROUND_GID 3
#define DEAD_LINE_GID 2
#define CAN_DISPEAR_GID 10
#define TMX_WIDTH 200
#define TMX_HEIGHT 23

static int count=0;


PlayMapNine::~PlayMapNine() {

}

void PlayMapNine::onEnter() {
	Layer::onEnter();

	bisover = false;
	//visibleSize，屏幕尺寸
	visibleSize = Director::getInstance()->getVisibleSize();

	//添加碰撞监听器
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayMapNine::onContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_2(PlayMapNine::onContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_2(PlayMapNine::onContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlayMapNine::onContactSeparate, this);
	//事件分发器
	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//网格地图
	auto winSize = Director::getInstance()->getWinSize();
	//map00瓦片地图地图
	tilemap = TMXTiledMap::create("map/map9.tmx");
	tilemap->setAnchorPoint(Vec2(0,0));
	tilemap->setPosition(Vec2(0,0));
	this->addChild(tilemap, -1);

	auto group = tilemap->getObjectGroup("objectsLayer");
	ValueMap heropos = group->getObject("hero");
	heroposx = heropos["x"].asFloat();
	heroposy = heropos["y"].asFloat();

	TMXLayer* layer = tilemap->getLayer("collideLayer");//从map中取出“bricks”图层
														//这个循环嵌套是为了给每个砖块精灵设置一个刚体
	int count = 0;

	for (int y = 0; y<TMX_HEIGHT; y++)
	{
		log("xxxxxxxxxxxxxxxxxxxx:%d", y); int groundcounter = 0; int deadlinecounter = 0; int dispearcounter = 0; int bodycounter = 0;
		Point groundpoint, deadlinepoint, dispearpoint, bodypoint; Size groundsize, deadlinesize, dispearsize, bodysize;
		for (int x = 0; x<TMX_WIDTH; x++)
		{

			int gid = layer->getTileGIDAt(Vec2(x, y));
			Sprite* sprite = layer->getTileAt(Vec2(x, y));//从tile的坐标取出对应的精灵

			if (gid == GROUND_GID) {

				log("sssssssssss  %f,ppppppppppppp %f", sprite->getPosition().x, sprite->getPosition().y);
				if (groundcounter == 0) {
					groundpoint = Point(sprite->getPosition().x, sprite->getPosition().y);
					groundsize = sprite->getContentSize();
					log("groundcounter==0");
				}
				groundcounter++; log("groundcounter=%d", groundcounter);

			}
			else {
				if (groundcounter != 0) {
					log("make execute!");
					groundsize = Size(groundsize.width*groundcounter, groundsize.height);
					log("point=%f  %f,size=%f  %f", groundpoint.x, groundpoint.y, groundsize.width, groundsize.height);
					this->makePhysicsObjAt(groundpoint, groundsize, false, 0, 0.0f, 0.0f, 0, GROUND_GID, -1);
				}
				groundcounter = 0;
			}/////////////////
			if (gid == DEAD_LINE_GID) {

				log("sssssssssss  %f,ppppppppppppp %f", sprite->getPosition().x, sprite->getPosition().y);
				if (deadlinecounter == 0) {
					deadlinepoint = Point(sprite->getPosition().x, sprite->getPosition().y);
					deadlinesize = sprite->getContentSize();
					log("groundcounter==0");
				}
				deadlinecounter++; log("groundcounter=%d", deadlinecounter);

			}
			else {
				if (deadlinecounter != 0) {
					log("make execute!");
					deadlinesize = Size(deadlinesize.width*deadlinecounter, deadlinesize.height);
					log("point=%f  %f,size=%f  %f", deadlinepoint.x, deadlinepoint.y, deadlinesize.width, deadlinesize.height);
					this->makePhysicsObjAt(deadlinepoint, deadlinesize, false, 0, 0.0f, 0.0f, 0, DEAD_LINE_GID, -1);
				}
				deadlinecounter = 0;
			}
			if (gid == CAN_DISPEAR_GID) {
				sprite->setTag(count);
				log("sprite->setTag(%d);",count);
				log("sssssssssss  %f,ppppppppppppp %f", sprite->getPosition().x, sprite->getPosition().y);
				if (dispearcounter == 0) {
					dispearpoint = Point(sprite->getPosition().x, sprite->getPosition().y);
					dispearsize = sprite->getContentSize();
					log("groundcounter==0");
				}
				dispearcounter++; log("groundcounter=%d", dispearcounter);

			}
			else {
				if (dispearcounter != 0) {
					log("make execute!");
					dispearsize = Size(dispearsize.width*dispearcounter, dispearsize.height);
					log("point=%f  %f,size=%f  %f", dispearpoint.x, dispearpoint.y, dispearsize.width, dispearsize.height);
					this->makePhysicsObjAt(dispearpoint, dispearsize, false, 0, 0.0f, 0.0f, 0, CAN_DISPEAR_GID, count);
					count++;
				}
				dispearcounter = 0;
			}
			if (gid == BODY_GID) {

				log("sssssssssss  %f,ppppppppppppp %f", sprite->getPosition().x, sprite->getPosition().y);
				if (bodycounter == 0) {
					bodypoint = Point(sprite->getPosition().x, sprite->getPosition().y);
					bodysize = sprite->getContentSize();
					log("groundcounter==0");
				}
				bodycounter++; log("groundcounter=%d", bodycounter);

			}
			else {
				if (bodycounter != 0) {
					log("make execute!");
					bodysize = Size(bodysize.width*bodycounter, bodysize.height);
					log("point=%f  %f,size=%f  %f", bodypoint.x, bodypoint.y, bodysize.width, bodysize.height);
					this->makePhysicsObjAt(bodypoint, bodysize, false, 0, 0.0f, 0.0f, 0, BODY_GID, -1);
				}
				bodycounter = 0;
			}
			if (count == 10000)count = 0;
		}
	}
	
	//带物理的会动的，这个是小车
	dead = DeadStar::create();
	dead->initWithFile("dead.png");			
	dead->setAnchorPoint(Point(0, 0));
	ValueMap carpos = group->getObject("car");
	float carposx = carpos["x"].asFloat();
	float carposy = carpos["y"].asFloat();
	dead->setPosition(carposx, carposy);
	dead->getPhysicsBody()->setContactTestBitmask(OBJECT_BIT_MASK);
	this->addChild(dead);
	

	//加入障碍物
	auto obstacle1 = Obstacle::create();
	obstacle1->setAnchorPoint(Point(0, 0));//
	ValueMap obs1pos = group->getObject("obstacle");
	auto obs1posx = obs1pos["x"].asFloat();
	auto obs1posy = obs1pos["y"].asFloat();
	obstacle1->setPosition(obs1posx, obs1posy);
	obstacle1->getPhysicsBody()->setContactTestBitmask(OBJECT_BIT_MASK);
	this->addChild(obstacle1);

	//加入圆形
	/*
	auto circular = Circular::create();
	circular->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 3+50);
	circular->getPhysicsBody()->setContactTestBitmask(OBJECT_BIT_MASK);
	addChild(circular);

	auto circular2 = Circular::create();
	circular2->setPosition(visibleSize.width / 2 + 100, visibleSize.height / 3 + 100);
	circular2->getPhysicsBody()->setContactTestBitmask(OBJECT_BIT_MASK);
	addChild(circular2);*/

	//加入小怪兽
	MA1 = MonsterA::create();
	MA1->initWithFile("redcircle.png");
	MA1->setAnchorPoint(Point(0, 1));////////////////
	ValueMap MA1pos = group->getObject("monsterone");
	float MA1posx = MA1pos["x"].asFloat();
	float MA1posy = MA1pos["y"].asFloat();
	MA1->setPosition(MA1posx, MA1posy);
	MA1->getPhysicsBody()->setContactTestBitmask(MONSTER1_BIT_MASK);
	log("MA1 - getTag();%d", MA1 - getTag());
	this->addChild(MA1);

	//加入门
	auto door = Ground::create();
	door->groundSize = Size(visibleSize.width / 6, visibleSize.height/4);
	door->init(door->groundSize);
	door->getPhysicsBody()->setContactTestBitmask(DOOR_BIT_MASK);
	//stage1->setAnchorPoint(Point(0, 1));visibleSize.width / 2, visibleSize.height / 3
	auto doorpicture = Sprite::create("road_5.png");	//静态的,为不动的刚体添加图片使用这种方式
	//doorpicture->setAnchorPoint(Point(0, 0));
	//doorpicture->setPosition(visibleSize.width * 17 / 6, visibleSize.height / 3);
	door->addChild(doorpicture);//
	ValueMap doorpos = group->getObject("door");
	float doorposx = doorpos["x"].asFloat();
	float doorposy = doorpos["y"].asFloat();
	door->setPosition(doorposx, doorposy);
	addChild(door);
	//加入桥
	/*
	bridge = Board::create();
	bridge->setPosition(100, 100);
	bridge->setPosition(visibleSize.width / 2 + 20, visibleSize.height / 3 + 200);
	addChild(bridge);*/

	state = 0;
	scheduleUpdate();
}


void PlayMapNine::update(float time) {

}

void PlayMapNine::onExit() {
	Layer::onExit();
	auto nodes = this->getChildren();
	for (const auto& node : nodes) {
		auto subnodes = node->getChildren();
		for (const auto& subnode : subnodes) {
			node->removeChild(subnode);
		}
		this->removeChild(node);
	}
}


bool PlayMapNine::onContactBegin(PhysicsContact &contact) {
	switch (contact.getShapeA()->getBody()->getContactTestBitmask() |
		contact.getShapeB()->getBody()->getContactTestBitmask())
	{
	//注意整个解决方法中各类中碰撞处理函数中的 case的值不要相同，同一个的碰撞只能有一个地方在处理
	/*case ARROW_BIT_MASK | MONSTER1_BIT_MASK://箭射中怪物
	{
		//dead->removeFromParentAndCleanup(true);
		MA1->removeFromParentAndCleanup(true);
	}
	break;*/
	case ARROW_BIT_MASK|CAN_DISPEAR_BIT_MASK:
	{
		auto a = contact.getShapeA()->getBody()->getNode();
		auto b = contact.getShapeB()->getBody()->getNode();
		log("dispear！！！！！！！！！！！！！！！");
		if (a != NULL) {
			long at = a->getTag();// tilemap->removeChildByTag();
			a->removeFromParentAndCleanup(true); 
			log("at  %d", at); long bt = b->getTag(); log("bt %d", bt);
			if (-1 < at < 10001) {
				do{
					tilemap->getLayer("collideLayer")->removeChildByTag(at);
					}
					while (tilemap->getLayer("collideLayer")->getChildByTag(at));
							
			}
			
				//
		}
		if (b!= NULL) {
			//long bt = b->getTag();// tilemap->removeChildByTag();
			//b->removeFromParentAndCleanup(true);
			//log("bt %d", bt);
			//if (-1 < bt < 10001)tilemap->getLayer("pengzhuang")->removeChildByTag(bt);
		}
	}break;
	default:
		break;
	}
	return true;
}

bool PlayMapNine::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve) {
	return true;
}

void PlayMapNine::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve) {

}

void PlayMapNine::onContactSeparate(PhysicsContact& contact) {

}

void PlayMapNine::makePhysicsObjAt(Point p, Size size, bool d, float r, float f, float dens, float rest,int gid,int tag)
{

	auto sprite = Ground::create();
	sprite->groundSize = size;
	sprite->setTag(tag);
	sprite->init(sprite->groundSize);
	//stage1->setAnchorPoint(Point(0, 1));visibleSize.width / 2, visibleSize.height / 3
	sprite->setPosition(sprite->groundSize.width / 2 + p.x, sprite->groundSize.height / 2 + p.y);
	switch(gid)
	{
	case GROUND_GID:
	{
		sprite->getPhysicsBody()->setContactTestBitmask(GROUND_BIT_MASK);
	}break;
	case DEAD_LINE_GID:
	{
		sprite->getPhysicsBody()->setContactTestBitmask(DEAD_LINE_BIT_MASK);
	}break;
	case CAN_DISPEAR_GID:
	{
		sprite->getPhysicsBody()->setContactTestBitmask(CAN_DISPEAR_BIT_MASK);
	}break;
	case BODY_GID:
	{
		sprite->getPhysicsBody()->setContactTestBitmask(GROUND_BIT_MASK);
	}break;
	default:
		break;
	}
	addChild(sprite);
}

