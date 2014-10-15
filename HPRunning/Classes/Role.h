//
//  Role.h
//  HPRunning
//
//  Created by student on 14-5-6.
//
//

#ifndef __HPRunning__Role__
#define __HPRunning__Role__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
enum ROLE_STATE{
    ROLE_INVAILD_STATE = 0,
    ROLE_RUN,
    ROLE_JUMP_UP,
    ROLE_JUMP_DOWN,
    ROLE_STAND_BY
};
class Role : public CCSprite
{
public:
    bool IsAttack;
    Role();
    ~Role();
    virtual bool init();
    
    CC_SYNTHESIZE(CCTMXTiledMap*, gameMap, GameMap);
    
    CC_PROPERTY(CCPoint, currentRolePoint, CurrentRolePoint);
    
    CC_SYNTHESIZE(ROLE_STATE, currentRoleState, CurrentRoleState);
    
public:
    //碰撞检测
    void runSate();//跑动帧动画
    void jumpState();//跳动帧动画
    void attackState();//攻击帧动画
    
public:
    int MaxJumpCount;
    int currentJumpCount;
    float time;
    float stateCtl;//跑动控制
    float statejump;//跳动控制
    
};
#endif /* defined(__HPRunning__Role__) */
