//
//  MainGame.cpp
//  HPRunning
//
//  Created by student on 14-5-6.
//
//

#include "MainGame.h"
#include "Role.h"
MainGame::MainGame()
{

}

MainGame::~MainGame()
{
    CC_SAFE_RELEASE_NULL(m_GameMap);
    arrayMap->release();
    mRole->release();
}

bool MainGame::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
     winSize=CCDirector::sharedDirector()->getWinSize();
    
    //初始化数组
    arrayMap=CCArray::create();
    arrayMap->retain();
    
    enemyArray1=CCArray::create();
    enemyArray1->retain();
    
    enemyArray2=CCArray::create();
    enemyArray2->retain();
    
    enemyArray3=CCArray::create();
    enemyArray3->retain();
    //添加跳动按钮
    CCMenuItemImage* item=CCMenuItemImage::create("jumpMenu.png", "jumpMenuLock.png");
    item->setPosition(ccp(250,-140));
    item->setTarget(this, menu_selector(MainGame::jumpButton));
    //添加攻击按钮
    CCMenuItemImage* item1=CCMenuItemImage::create("attMenu.png", "attMenuLock.png");
    item1->setPosition(ccp(-250,-140));
    item1->setTarget(this, menu_selector(MainGame::attackButton));
    
    CCMenu* menu=CCMenu::create(item,item1,NULL);
    this->addChild(menu,20);
    //初始化各种Lable
    addLabel();
    
    //添加地图
    initMap();
    
    //初始化角色
    initRole();
    
    //碰撞检测的时间调度
    schedule(schedule_selector(MainGame::role_update), 0.016);
    schedule(schedule_selector(MainGame::distanceCount), 0.05);
    
    return true;
}

CCScene* MainGame::scene()
{
    CCScene* scene=CCScene::create();
    MainGame* layer=MainGame::create();
    scene->addChild(layer);
    return scene;
}

void MainGame::initMap()
{
    for(int i=0;i<25;i++)
    {
        char name[10];
        sprintf(name, "%d.tmx",i+1);
        m_GameMap=CCTMXTiledMap::create(name);
        CC_SAFE_RETAIN(m_GameMap);
        m_GameMap->setAnchorPoint(ccp(0,0));
        m_GameMap->setPosition(ccp(0+i*800,0))
        ;
        this->addChild(m_GameMap,1);
        arrayMap->addObject(m_GameMap);
        CCMoveBy* by=CCMoveBy::create(0.016, ccp(-8,0));
        CCRepeatForever* forever=CCRepeatForever::create(by);
        m_GameMap->runAction(forever);
        //添加敌人
        CCTMXObjectGroup *objects=m_GameMap->objectGroupNamed("enemy");
        if(objects)
        {
            for(int i=0;i<int(objects->getObjects()->count());i++)
            {
                CCDictionary *enemy=(CCDictionary*)objects->getObjects()->objectAtIndex(i);
                if(enemy->valueForKey("enemytype")->intValue()==3)
                {
                    CCSprite *s=CCSprite::create("enemy3_hurt1.png");
                    float x=enemy->valueForKey("x")->floatValue();
                    float y=enemy->valueForKey("y")->floatValue();
                    s->setPosition(ccp(x,y));
                    s->setAnchorPoint(CCPoint(0,0));
                    m_GameMap->addChild(s,20);
                   // this->enemyAction3(s);
                }
                if(enemy->valueForKey("enemytype")->intValue()==2)
                {
                    CCSprite* s2=CCSprite::create("enemy2_hurt2.png");
                    float x=enemy->valueForKey("x")->floatValue();
                    float y=enemy->valueForKey("y")->floatValue();
                    s2->setPosition(ccp(x,y));
                    s2->setAnchorPoint(CCPoint(0,0));
                    m_GameMap->addChild(s2,20);
                    this->enemyAction2(s2);
                }
                if(enemy->valueForKey("enemytype")->intValue()==1)
                {
                    CCSprite* s3=CCSprite::create("enemy1_hurt1.png");
                    float x=enemy->valueForKey("x")->floatValue();
                    float y=enemy->valueForKey("y")->floatValue();
                    s3->setPosition(ccp(x,y));
                    s3->setAnchorPoint(ccp(0,0));
                    m_GameMap->addChild(s3,20);
                    this->enemyAction1(s3);
                }
            }
        }

    }
}

void MainGame::initRole()
{
    mRole=new Role();
    mRole->setAnchorPoint(CCPointZero);
    mRole->setPosition(ccp(200,320));
    mRole->initWithFile("22.png");
    mRole->setCurrentRoleState(ROLE_JUMP_DOWN);
    this->addChild(mRole,10);
}

void MainGame::jumpButton()
{
    if(mRole->MaxJumpCount>mRole->currentJumpCount)
    {
        mRole->statejump=0;
        mRole->stopAllActions();
        mRole->currentJumpCount++;
        this->jumpUpLogic();
    }
}

void MainGame::attackButton()
{
    if(mRole->getCurrentRoleState()==ROLE_RUN)
    {
        mRole->stopAllActions();
        CCCallFunc* func=CCCallFunc::create(mRole, callfunc_selector(Role::runSate));
        CCCallFunc* changefun=CCCallFunc::create(this,callfunc_selector(MainGame::changAttackState));
        CCCallFunc* func1=CCCallFunc::create(mRole, callfunc_selector(Role::attackState));
        CCSequence* seq=CCSequence::create(func,changefun,func1,NULL);
        mRole->runAction(seq);
    }
}

void MainGame::role_update()
{
    for(int i=0;i<arrayMap->count();i++)
    {
        CCTMXTiledMap* _map=(CCTMXTiledMap*)arrayMap->objectAtIndex(i);
        float _mapX=_map->getPositionX();
        float RoleX=mRole->getCurrentRolePoint().x;
        if(_mapX<=RoleX && _mapX+800>RoleX)
        {
            mRole->setGameMap(_map);
            root =mRole->getGameMap()->layerNamed("root");
            jewel=mRole->getGameMap()->layerNamed("jewel");
            break;
        }
    }
    this->role_logic();
    if(timer->getPercentage()==100)
    {
        CCDirector::sharedDirector()->pause();
        addPasBoard();
    }
}

void MainGame::isCollWithCollArea()
{
//怪物与英雄的碰撞

    enemyObjects=mRole->getGameMap()->objectGroupNamed("enemy");
    if(enemyObjects)
    {
        float mRoleX=mRole->getCurrentRolePoint().x-mRole->getGameMap()->getPositionX();
        float mRoleY=mRole->getCurrentRolePoint().y-mRole->getGameMap()->getTileSize().height;
        CCRect mRoleRect;
        mRoleRect.setRect(mRoleX, mRoleY, 32, 32);
        for(int i=0;i<int(enemyObjects->getObjects()->count());i++)
        {
            CCDictionary *enemy=(CCDictionary*)enemyObjects->getObjects()->objectAtIndex(i);
            if(enemy->valueForKey("enemytype")->intValue()==3)
            {
                float x=enemy->valueForKey("x")->floatValue();
                float y=enemy->valueForKey("y")->floatValue();
                CCRect enemyRect;
                enemyRect.setRect(x, y, 32, 32);
                if(iscollision(mRoleRect, enemyRect))
                {
                    if(mRole->IsAttack)
                    {
                        CCLog("把怪打死了");
                    }
                    else
                    {
                        CCLog("碰到第三种怪了");
                      //  CCDirector::sharedDirector()->pause();
                       // addOverBoard();
                    }
                }
            }
            if(enemy->valueForKey("enemytype")->intValue()==2)
            {
                float x=enemy->valueForKey("x")->floatValue();
                float y=enemy->valueForKey("y")->floatValue();
                CCRect enemyRect;
                enemyRect.setRect(x, y, 32, 32);
                if(iscollision(mRoleRect, enemyRect))
                {
                    if(mRole->IsAttack)
                    {
                        CCLog("把怪打死了");
                    }
                    else
                    {
                        CCLog("碰到第二种怪了");
                       // CCDirector::sharedDirector()->pause();
                       // addOverBoard();
                    }
                }
            }
            if(enemy->valueForKey("enemytype")->intValue()==1)
            {
                float x=enemy->valueForKey("x")->floatValue();
                float y=enemy->valueForKey("y")->floatValue();
                CCRect enemyRect;
                enemyRect.setRect(x, y, 32, 32);
                if(iscollision(mRoleRect, enemyRect))
                {
                    if(mRole->IsAttack)
                    {
                        CCLog("把怪打死了");
                    }
                    else
                    {
                        CCLog("碰到第一种怪了");
                        //CCDirector::sharedDirector()->pause();
                       // addOverBoard();
                    }
                }
            }
        }
    }
    
    //对金币的检测碰撞
    CCPoint currentPoint=mRole->getCurrentRolePoint();
    int x1=(currentPoint.x-mRole->getGameMap()->getPositionX())/(mRole->getGameMap()->getTileSize().width);
    int y1=((mRole->getGameMap()->getMapSize().height * mRole->getGameMap()->getTileSize().height) - currentPoint.y)/mRole->getGameMap()->getTileSize().height;
    CCPoint tileCoin =ccp(x1,y1);
    int tiledgidCoin=jewel->tileGIDAt(tileCoin);
    CCLog("tiledCoin=%d",tiledgidCoin);
    if(tiledgidCoin)
    {
        CCDictionary* propertiess=mRole->getGameMap()->propertiesForGID(tiledgidCoin);
        if(propertiess)
        {
            CCString *collCoin= (CCString *)propertiess->objectForKey("jewelType");
            if(collCoin && collCoin->compare("1") == 0 )//第一种金币)
            {
                CCSprite* coin=jewel->tileAt(tileCoin);
                coin->removeFromParent();
                score+=20;
                char scoreGet[20];
                sprintf(scoreGet, "%d",score);
                getCoin->setString(scoreGet);
                addscore2();
                CCLog("吃到第一种金币");
            }
            if(collCoin && collCoin->compare("2") == 0 )
            {
                CCSprite* coin=jewel->tileAt(tileCoin);
                coin->removeFromParent();
                score+=10;
                char scoreGet[20];
                sprintf(scoreGet, "%d",score);
                getCoin->setString(scoreGet);
                addscore1();
                CCLog("吃到第二种金币");

            }
            if(collCoin && collCoin->compare("3") == 0 )
            {
                CCSprite* coin=jewel->tileAt(tileCoin);
                coin->removeFromParent();
                score+=50;
                char scoreGet[20];
                sprintf(scoreGet, "%d",score);
                getCoin->setString(scoreGet);
                addscore3();
                CCLog("吃到第三种金币");

            }
        }
    }
    //对地面的检测碰撞
    if(mRole->getCurrentRoleState()!=ROLE_JUMP_UP)
    {
        int x=(nextPoint.x-mRole->getGameMap()->getPositionX())/(mRole->getGameMap()->getTileSize().width);
        int y=((mRole->getGameMap()->getMapSize().height * mRole->getGameMap()->getTileSize().height) - nextPoint.y)/mRole->getGameMap()->getTileSize().height;
        CCPoint tileCoord=ccp(x,y);
        int tilegid=root->tileGIDAt(tileCoord);//返回指定位置的砖块的对象的ID
        CCLog("=%d",tilegid);
        if(tilegid)
        {
            CCDictionary * properties=mRole->getGameMap()->propertiesForGID(tilegid);
            if(properties)
            {
                CCString *collisionx= (CCString *)properties->objectForKey("rootX");
                CCString *collisiony = (CCString *)properties->objectForKey("rootY");
                if(collisionx && collisionx->compare("-1") == 0 && collisiony && collisiony->compare("0") == 0)//阻碍了
                {
                    CCLog("到底了");
                    mRole->setCurrentRoleState(ROLE_RUN);
                    mRole->currentJumpCount=0;
                }
                if(collisionx && collisionx->compare("0") == 0 && collisiony && collisiony->compare("-1") == 0)//阻碍了)
                {
                    CCLog("碰到别处GameOver");
                    CCDirector::sharedDirector()->pause();
                    addOverBoard();
                }
            }
        }
    else
    {
        if(mRole->getCurrentRoleState()==ROLE_JUMP_UP)
        {
            CCLog("正在跳动状态不可下降");
        }
        else
        {
            mRole->setCurrentRoleState(ROLE_JUMP_DOWN);
        }
        if(mRole->getCurrentRoleState()==ROLE_JUMP_DOWN)
        {
            mRole->setCurrentRolePoint(nextPoint);
        }
    }
    }
}


void MainGame::role_logic()
{
    switch (mRole->getCurrentRoleState()) {
        case ROLE_INVAILD_STATE:
            
            break;
            
        case ROLE_RUN://跑动状态
            runLogic();
            CCLog("正在跑动");
            break;
            
        case ROLE_JUMP_DOWN://下降状态
            this->jumpDownLogic();
            CCLog("正在下落");
            break;
            
        case ROLE_JUMP_UP://跳动状态
            this->jumpUpLogic();
            CCLog("正在跳动");
            break;
            
        case ROLE_STAND_BY://战力状态
            break;
            
        default:
            break;
    }
}

void MainGame::runLogic()//跑动的方法
{
    mRole->statejump=0;
    mRole->stateCtl++;
    if(mRole->stateCtl<=1)
    {
        mRole->runSate();
    }
    this->isCollWithCollArea();
}

void MainGame::jumpUpLogic()//起跳的方法
{
    mRole->statejump++;
    mRole->stateCtl=0;
    if(mRole->statejump<=1)
    {
        mRole->jumpState();
    }
    mRole->setCurrentRoleState(ROLE_JUMP_UP);
    CCPoint preRolePoint=mRole->getCurrentRolePoint();
    CCPoint targetPoint = ccp(preRolePoint.x,preRolePoint.y+mRole->getGameMap()->getTileSize().height/2);
    CCLog("mRole->getTile=%f",mRole->getGameMap()->getTileSize().height);
    mRole->time++;
    mRole->setCurrentRolePoint(targetPoint);
    if(mRole->time==9)
    {
        mRole->setCurrentRoleState(ROLE_JUMP_DOWN);
        nextPoint=targetPoint;
        mRole->time=0;
    }
    
    this->isCollWithCollArea();
}

void MainGame::jumpDownLogic()//下落的方法
{
    CCPoint preRolePoint = mRole->getCurrentRolePoint();
    CCPoint targetRolePoint = ccp(preRolePoint.x,preRolePoint.y-mRole->getGameMap()->getTileSize().height/4);
    nextPoint=targetRolePoint;
    this->isCollWithCollArea();
    if(nextPoint.y<=80)
    {
        CCDirector::sharedDirector()->pause();
        addOverBoard();
    }
}


void MainGame::addLabel()
{
    distance=0;
    score=0;
    //计分板
    CCSprite* messageBoard=CCSprite::create("message_board.png");
    messageBoard->setPosition(ccp(100,400));
    this->addChild(messageBoard,20);
    //距离和金币
    getCoin=CCLabelTTF::create("0", "Zapinfo", 25);
    getCoin->setPosition(ccp(120,380));
    getCoin->setColor(ccc3(255, 255, 0));
    this->addChild(getCoin,20);
    Distance=CCLabelTTF::create("0", "Zapinfo", 25);
    Distance->setPosition(ccp(120,410));
    Distance->setColor(ccc3(255, 255, 0));
    this->addChild(Distance,20);
    
    //添加进度条
    CCSprite * sprite=CCSprite::create("taskBoardInGame.png");
    sprite->setPosition(ccp(600,400));
    this->addChild(sprite,20);
    timer=CCProgressTimer::create(CCSprite::create("load.png"));
    timer->setPercentage(0.0f);
    timer->setBarChangeRate(ccp(1,0));
    timer->setType(kCCProgressTimerTypeBar);
    timer->setMidpoint(ccp(0,0));
    timer->setPosition(ccp(590,377));
    timer->setScale(0.41);
    this->addChild(timer,20);
   

}

void MainGame::remove(CCNode * node)
{
    this->removeChild(node);
}

void MainGame::addscore1()
{
    CCLabelTTF* label=CCLabelTTF::create("金币 1*10", "Zapinfo", 25);
    label->setPosition(ccp(200,320));
    label->setColor(ccc3(255, 0, 0));
    this->addChild(label);
    CCCallFuncN* x=CCCallFuncN::create(this, callfuncN_selector(MainGame::remove));
    label->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(0,20)),x,NULL));
}

void MainGame::addscore2()
{
    CCLabelTTF* label=CCLabelTTF::create("金币 1*20", "Zapinfo", 25);
    label->setPosition(ccp(200,320));
    label->setColor(ccc3(0, 0, 255));
    this->addChild(label);
    CCCallFuncN* x=CCCallFuncN::create(this, callfuncN_selector(MainGame::remove));
    label->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(0,20)),x,NULL));

}

void MainGame::addscore3()
{
    CCLabelTTF* label=CCLabelTTF::create("金币 1*50", "Zapinfo", 25);
    label->setPosition(ccp(200,320));
    label->setColor(ccc3(0, 255, 0));
    this->addChild(label);
    CCCallFuncN* x=CCCallFuncN::create(this, callfuncN_selector(MainGame::remove));
    label->runAction(CCSequence::create(CCMoveBy::create(0.5, ccp(0,20)),x,NULL));

}

void MainGame::distanceCount()
{
    distance=distance+1;
    char distacnes[20];
    sprintf(distacnes, "%d",distance);
    Distance->setString(distacnes);
    timer->setPercentage(distance/10);
}

void MainGame::addOverBoard()
{
    unscheduleAllSelectors();
    CCSprite* sprite=CCSprite::create("passBoard.png");
    sprite->setPosition(ccp(winSize.width/2,winSize.height/3));
    this->addChild(sprite,20);
    
    CCSprite* asprite=CCSprite::create("lose.png");
    asprite->setPosition(ccp(200,300));
    sprite->addChild(asprite);
    
    CCMenuItemImage* item1=CCMenuItemImage::create("overRestarMenu.png", "overRestartMenuLock.png");
    item1->setTarget(this, menu_selector(MainGame::reStart));
    item1->setPosition(ccp(-250,-180));
    
    CCMenuItemImage* item2=CCMenuItemImage::create("overReturnMain.png", "overReturnMainLock.png");
    item2->setTarget(this, menu_selector(MainGame::BackMainMenu));
    item2->setPosition(ccp(-100,-180));
    CCMenu* menu=CCMenu::create(item1,item2,NULL);
    sprite->addChild(menu);
    //金币数
    getCoinLayer=CCLabelTTF::create("0", "Zapinfo", 25);
    getCoinLayer->setPosition(ccp(185,160));
    getCoinLayer->setColor(ccc3(0, 0, 255));
    
    sprite->addChild(getCoinLayer);
    
    //距离
    DistanceLayer=CCLabelTTF::create("0", "Zapinfo", 25);
    DistanceLayer->setPosition(ccp(185,120));
    DistanceLayer->setColor(ccc3(0, 0, 255));
    sprite->addChild(DistanceLayer);

    char SCORE[20];
    sprintf( SCORE,"%d",score);
    getCoinLayer->setString(SCORE);
    
    char DISTANCE[20];
    sprintf(DISTANCE, "%d",distance);
    DistanceLayer->setString(DISTANCE);
}

void MainGame::reStart()
{
    CCDirector::sharedDirector()->resume();
    CCScene * aScene=MainGame::scene();
    CCDirector::sharedDirector()->replaceScene(aScene);
}

void MainGame::BackMainMenu()
{
    CCDirector::sharedDirector()->resume();
    CCScene * aScene=StartGame::scene();
    CCDirector::sharedDirector()->replaceScene(aScene);
}

void MainGame::addPasBoard()
{ unscheduleAllSelectors();
    CCSprite* sprite=CCSprite::create("passBoard.png");
    sprite->setPosition(ccp(winSize.width/2,winSize.height/3));
    this->addChild(sprite,20);
    
    CCSprite* asprite=CCSprite::create("win.png");
    asprite->setPosition(ccp(200,300));
    sprite->addChild(asprite);
    
    CCMenuItemImage* item2=CCMenuItemImage::create("overReturnMain.png", "overReturnMainLock.png");
    item2->setTarget(this, menu_selector(MainGame::BackMainMenu));
    item2->setPosition(ccp(-180,-180));
    CCMenu* menu=CCMenu::create(item2,NULL);
    sprite->addChild(menu);
    //金币数
    getCoinLayer=CCLabelTTF::create("0", "Zapinfo", 25);
    getCoinLayer->setPosition(ccp(185,160));
    getCoinLayer->setColor(ccc3(0, 0, 255));
    
    sprite->addChild(getCoinLayer);
    
    //距离
    DistanceLayer=CCLabelTTF::create("0", "Zapinfo", 25);
    DistanceLayer->setPosition(ccp(185,120));
    DistanceLayer->setColor(ccc3(0, 0, 255));
    sprite->addChild(DistanceLayer);
    
    char SCORE[20];
    sprintf( SCORE,"%d",score);
    getCoinLayer->setString(SCORE);
    
    char DISTANCE[20];
    sprintf(DISTANCE, "%d",distance);
    DistanceLayer->setString(DISTANCE);
}

void MainGame::enemyAction1(CCSprite* sprite)
{
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<7;i++)
    {
        char fram[30];
        sprintf(fram, "enemy_att%d.png",i+1);
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.2);
    CCAnimate* animate=CCAnimate::create(animation);
    CCRepeatForever* forever=CCRepeatForever::create(animate);
    sprite->runAction(forever);
    array->release();
}

void MainGame::enemyAction2(CCSprite* sprite)
{
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<7;i++)
    {
        char fram[30];
        sprintf(fram, "enemy2_att%d.png",i+1);
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.2);
    CCAnimate* animate=CCAnimate::create(animation);
    CCRepeatForever* forever=CCRepeatForever::create(animate);
    sprite->runAction(forever);
    array->release();
}

void MainGame::enemyAction3(CCSprite* sprite)
{
    CCArray* array=CCArray::createWithCapacity(40);
    array->retain();
    for(int i=0;i<8;i++)
    {
        char fram[30];
        sprintf(fram, "enemy3_att%d.png",i+1);
        CCSpriteFrame* framName=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fram);
        array->addObject(framName);
    }
    CCAnimation* animation=CCAnimation::createWithSpriteFrames(array,0.2);
    CCAnimate* animate=CCAnimate::create(animation);
    CCRepeatForever* forever=CCRepeatForever::create(animate);
    sprite->runAction(forever);
    array->release();
}

bool MainGame::iscollision(CCRect myRect,CCRect testRect)
{
    return  myRect.intersectsRect(testRect);
}

void MainGame::changAttackState()
{
    mRole->IsAttack=false;
}