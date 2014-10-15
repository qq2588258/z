//
//  GameSet.h
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#ifndef __HPRunning__GameSet__
#define __HPRunning__GameSet__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameSet : public CCLayer
{
public:
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(GameSet);
    
public:
    CCControlSwitch* switchCtl;
    CCControlSlider* slider;
    void musicOn();
    void Back();
    void addSwitch();
    void voicechange();
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};
#endif /* defined(__HPRunning__GameSet__) */
