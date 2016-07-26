#ifndef PLAYMAPONEGROUND
#define PLAYMAPONEGROUND
#include <cocos2d.h>
USING_NS_CC;

class Playmaponeground : public Sprite
{
public:
	Size groundSize;
	PhysicsBody* groundPhysicsBody;
	virtual bool init();
	bool init(Size &groundSize);
	CREATE_FUNC(Playmaponeground);
};
#endif
#pragma once
