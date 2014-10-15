//
//  MainGame.h
//  HPRunning
//
//  Created by student on 14-5-6.
//
//

#ifndef __HPRunning__MainGame__
#define __HPRunning__MainGame__

#include <iostream>
#include "StartGame.h"
#include "cocos2d.h"
USING_NS_CC;
class Role;
class MainGame : public CCLayer
{
public:
    MainGame();
    ~MainGame();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(MainGame);
    
public:
    void isCollWithCollArea();
    void role_update();
    void initMap();
    void initRole();
    void jumpButton();
    void attackButton();
    void role_logic();
    void runLogic();//跑动的方法
    void jumpUpLogic();//跳动的方法
    void jumpDownLogic();//下落的方法

    CCArray* arrayMap;//地图数组

    Role* mRole;
    CCTMXLayer* root;
    CCTMXLayer* jewel;
    CCTMXObjectGroup *enemyObjects;//敌人对象层
    CCPoint nextPoint;//检测碰撞点
public:
    void addLabel();
    CCLabelTTF* getCoin;
    CCLabelTTF* Distance;
    CCLabelTTF* getCoinLayer;
    CCLabelTTF* DistanceLayer;
    int score;
    int distance;
    void distanceCount();
    void changAttackState();//切换攻击状态
    CCSize winSize;
    
//吃金币弹出动画
    void remove(CCNode * node);
    void addscore1();
    void addscore2();
    void addscore3();
    
//游戏结束弹出对话框
    void addOverBoard();
    void reStart();
    void BackMainMenu();
    
//过关的时候弹出对话框
    void addPasBoard();
    
//敌人帧动画
    void enemyAction1(CCSprite* sprite);
    void enemyAction2(CCSprite* sprite);
    void enemyAction3(CCSprite* sprite);
    
//敌人数组
    CCArray* enemyArray1;
    CCArray* enemyArray2;
    CCArray* enemyArray3;
    
//判断敌人与人物是否碰撞
    bool iscollision(CCRect myRect,CCRect testRect);
    
private:
    CCTMXTiledMap* m_GameMap;
    CCProgressTimer* timer;

};
#endif /* defined(__HPRunning__MainGame__) */
