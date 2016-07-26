#ifndef _BRIDGE
#define _BRIDGE
#include <cocos2d.h>
#include <iostream>
USING_NS_CC;

class Board :public Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Board);
	//void updateStart(float delta); √ª”√
	//virtual void update(float delta) override;
};

#endif
#pragma once
