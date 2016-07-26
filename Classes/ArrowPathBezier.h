//
//  ArrowPathBezier.h
//  arrowGame
//
//  Created by renshan on 15/6/23.
//
//

#ifndef __arrowGame__ArrowPathBezier__
#define __arrowGame__ArrowPathBezier__

#include <iostream>

#include "cocos2d.h"
USING_NS_CC;


typedef struct _ccQuadBezierConfig {
    Point endPosition;
    Point controlPoint;
} ccQuadBezierConfig;

class ArrowPathBezier: public BezierBy
{
public:
    ArrowPathBezier();
    static ArrowPathBezier* create(float t, const ccQuadBezierConfig& c);
    bool initWithDuration(float t, const ccQuadBezierConfig& c);
    virtual void update(float time);
	virtual float bezierat(float a, float b, float c, float d, float t);
	float bezierattwice(float a, float b, float d, float t);
private:
    ccQuadBezierConfig _config;
};
#endif /* defined(__arrowGame__ArrowPathBezier__) */
