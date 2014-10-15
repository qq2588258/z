//
//  Loading.h
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#ifndef __HPRunning__Loading__
#define __HPRunning__Loading__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class Loading : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(Loading);
    
public:
    int i;
    CCSprite* spriterMiner;
    CCProgressTimer* timer;
    
    void jumpScene();
    void loading();
    void loadPic();
};
#endif /* defined(__HPRunning__Loading__) */
