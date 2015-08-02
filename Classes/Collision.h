#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "cocos2d.h"
#include <cstring>

USING_NS_CC;
using namespace std;

class Collision :public cocos2d::Layer {
	int w;
	int all;
public:
	Collision();
	~Collision();

	unsigned int *plex_t;
	void setThePlex(string src);
	unsigned int getThePlexByPoint(int psx, int psy);
};
#endif