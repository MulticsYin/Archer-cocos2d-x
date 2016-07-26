#ifndef PLAYMAPFIVE
#define PLAYMAPFIVE
//#include "cocos2d.h"
#include "Hero.h"
#include "arrow.h"
#include "Board.h"
#include "Ground.h"
#include "deadstar.h"
#include "obstacle.h"
#include "monsterA.h"
#include "monsterD.h"
#include "Circle.h"
//#include "GameDirectory.h"
using namespace cocos2d;

USING_NS_CC;

#include "contact_data.h"

// 地图类，负责地图的循环滚动、背景精灵的管理等
class PlayMapFive: public Layer
{
public:
	//PlayMapOne(void);
	Size visibleSize;
	Ground* ground1;
	Ground* stage1;
	Ground* deadLine;
	DeadStar* dead;
	Board* bridge;
	MonsterA* MA1;
    short state;
	//bisover 游戏是否结束
    bool bisover;
	int print_x;
	int print_y;
    virtual ~PlayMapFive(void);
    virtual void onEnter();
    virtual void onExit();
    void bg1change();
    void bg2change();
	virtual void update(float time);
    void setGameOver();

	//碰撞监听器
	EventListenerPhysicsContact* contactListener;

	//碰撞刚发生时
	virtual bool onContactBegin(PhysicsContact& contact);
	virtual bool onContactPreSolve(PhysicsContact&  contact, PhysicsContactPreSolve&  solve);
	virtual void onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve);
	
	//碰撞物体分离时
	virtual void onContactSeparate(PhysicsContact& contact);

	//map00瓦片地图地图
	TMXTiledMap* tilemap;

	void makePhysicsObjAt(Point p, Size size, bool d, float r, float f, float dens, float rest,int gid,int tag);

	CREATE_FUNC(PlayMapFive);
    //
};


#endif
