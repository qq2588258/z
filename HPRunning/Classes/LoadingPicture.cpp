//
//  LoadingPicture.cpp
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#include "LoadingPicture.h"
#include "StartGame.h"
bool LoadingPicture::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    this->addpicture1();
    this->addpicture3();
    this->addpicture2();
    this->addpicture4();
    scheduleOnce(schedule_selector(LoadingPicture::replaceScene), 14);
    
    return true;
}

CCScene* LoadingPicture::scene()
{
    CCScene* scene=CCScene::create();
    LoadingPicture* layer=LoadingPicture::create();
    scene->addChild(layer);
    return scene;
}

void LoadingPicture::addpicture1()
{
    CCSprite* sprite1=CCSprite::create("Screenshot1.png");
    sprite1->setPosition(ccp(1000,1000));
    sprite1->setScale(0.5);
    this->addChild(sprite1);
    CCMoveTo* move1=CCMoveTo::create(4.0, ccp(400,240));
    CCMoveTo* move2=CCMoveTo::create(1.0, ccp(130,240));
    CCScaleTo* scale=CCScaleTo::create(1.0, 0.4);
    CCSpawn* spawn=CCSpawn::create(move2,scale,NULL);
    CCDelayTime* delay=CCDelayTime::create(0.5);
    CCSequence* seq=CCSequence::create(move1,delay,spawn,NULL);
    sprite1->runAction(seq);

}

void LoadingPicture::addpicture2()
{
    CCSprite* sprite2=CCSprite::create("Screenshot2.png");
    sprite2->setPosition(ccp(1500,160));
    sprite2->setScale(0.5);
    this->addChild(sprite2);
    CCMoveTo* move1=CCMoveTo::create(4.0, ccp(400,240));
    CCMoveTo* move2=CCMoveTo::create(1.0, ccp(360,240));
    CCScaleTo* scale=CCScaleTo::create(1.0, 0.4);
    CCSpawn* spawn=CCSpawn::create(move2,scale,NULL);
    CCDelayTime* delay=CCDelayTime::create(0.5);
    CCDelayTime* delay1=CCDelayTime::create(4.5);
    CCSequence* seq=CCSequence::create(delay1,move1,delay,spawn,NULL);
    sprite2->runAction(seq);

}

void LoadingPicture::addpicture3()
{
    CCSprite* sprite3=CCSprite::create("Screenshot3.png");
    sprite3->setPosition(ccp(-1000,-1000));
    sprite3->setScale(0.5);
    this->addChild(sprite3);
    CCMoveTo* move1=CCMoveTo::create(5.0, ccp(400,240));
    CCMoveTo* move2=CCMoveTo::create(1.0, ccp(130,80));
    CCScaleTo* scale=CCScaleTo::create(1.0, 0.4);
    CCSpawn* spawn=CCSpawn::create(move2,scale,NULL);
    CCDelayTime* delay=CCDelayTime::create(0.5);
    CCDelayTime* delay1=CCDelayTime::create(1);
    CCSequence* seq=CCSequence::create(delay1,move1,delay,spawn,NULL);
    sprite3->runAction(seq);
}

void LoadingPicture::addpicture4()
{
    CCSprite* sprite7=CCSprite::create("Screenshot4.png");
    sprite7->setPosition(ccp(-1500,500));
    sprite7->setScale(0.5);
    this->addChild(sprite7);
    CCMoveTo* move1=CCMoveTo::create(4.0, ccp(400,240));
    CCMoveTo* move2=CCMoveTo::create(1.0, ccp(360,80));
    CCScaleTo* scale=CCScaleTo::create(1.0, 0.4);
    CCSpawn* spawn=CCSpawn::create(move2,scale,NULL);
    CCDelayTime* delay=CCDelayTime::create(0.5);
    CCDelayTime* delay1=CCDelayTime::create(7);
    CCSequence* seq=CCSequence::create(delay1,move1,delay,spawn,NULL);
    sprite7->runAction(seq);
}

void LoadingPicture::replaceScene()
{
    CCTransitionScene* scene=CCTransitionRotoZoom::create(1.0, StartGame::scene());
    CCDirector::sharedDirector()->replaceScene(scene);

}