//
//  StartGame.cpp
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#include "StartGame.h"
#include "GameSet.h"
#include "SimpleAudioEngine.h"
#include "MainGame.h"
bool StartGame::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSprite* sprite=CCSprite::create("mainBackground.jpg");
    sprite->setPosition(ccp(400,240));
    this->addChild(sprite);
    this->moveMan();//让角色移动
    this->addButton();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("keepRunning.mp3", true);
    if(!game)
    {
        game=new GameSet;
    }

    return true;
}

CCScene* StartGame::scene()
{
    CCScene* scene=CCScene::create();
    StartGame* layer=StartGame::create();
    scene->addChild(layer);
    return scene;
}

void StartGame::moveMan()
{
    CCSprite* sprite1=CCSprite::create("miner1.png");
    sprite1->setPosition(ccp(220,380));
    sprite1->setScale(0.6);
    this->addChild(sprite1);
    CCSprite* sprite2=CCSprite::create("miner2.png");
    sprite2->setPosition(ccp(100,380));
    sprite2->setScale(0.5);
    this->addChild(sprite2);
    CCSprite* sprite3=CCSprite::create("miner3.png");
    sprite3->setPosition(ccp(340,380));
    sprite3->setScale(0.5);
    this->addChild(sprite3);
    
    CCMoveTo* move1=CCMoveTo::create(1.0, ccp(210,355));
    CCMoveTo* move2=CCMoveTo::create(1.0, ccp(220,380));
    CCSequence* seq=CCSequence::create(move1,move2,NULL);
    CCRepeatForever* forever=CCRepeatForever::create(seq);
    sprite1->runAction(forever);
    
    CCMoveTo* move3=CCMoveTo::create(1.2, ccp(100,355));
    CCMoveTo* move4=CCMoveTo::create(1.2, ccp(100,380));
    CCSequence* seq1=CCSequence::create(move3,move4,NULL);
    CCRepeatForever* forever1=CCRepeatForever::create(seq1);
    sprite2->runAction(forever1);
    
    CCMoveTo* move5=CCMoveTo::create(1.1, ccp(345,355));
    CCMoveTo* move6=CCMoveTo::create(1.1, ccp(340,380));
    CCSequence* seq2=CCSequence::create(move5,move6,NULL);
    CCRepeatForever* forever2=CCRepeatForever::create(seq2);
    sprite3->runAction(forever2);
}

void StartGame::addButton()
{
    CCMenuItemImage* item1=CCMenuItemImage::create("button4.png", "button5.png");
    item1->setPosition(ccp(-160,-20));
    item1->setScale(0.7);
    item1->setTarget(this, menu_selector(StartGame::beginGame));
    CCMenuItemImage* item2=CCMenuItemImage::create("button5.png", "button3.png");
    item2->setPosition(ccp(-160,-80));
    item2->setScale(0.7);
    item2->setTarget(this, menu_selector(StartGame::setGame));
    
    CCMenuItemImage* item3=CCMenuItemImage::create("button3.png", "button4.png");
    item3->setPosition(ccp(-160,-140));
    item3->setScale(0.7);
    item3->setTarget(this, menu_selector(StartGame::quitGame));
    CCMenu* menu=CCMenu::create(item1,item2,item3,NULL);
    this->addChild(menu);
    
    //添加字体
    CCLabelTTF* label1=CCLabelTTF::create("开始游戏", "Zapinfo", 25);
    label1->setPosition(ccp(200,220));
    label1->setColor(ccc3(0, 0, 255));
    this->addChild(label1);
    CCLabelTTF* label2=CCLabelTTF::create("游戏设置", "Zapinfo", 25);
    label2->setPosition(ccp(200,160));
    label2->setColor(ccc3(0, 0, 255));
    this->addChild(label2);
    CCLabelTTF* label3=CCLabelTTF::create("退出游戏", "Zapinfo", 25);
    label3->setPosition(ccp(200,100));
    label3->setColor(ccc3(0, 0, 255));
    this->addChild(label3);

}

void StartGame::beginGame()
{
    CCTransitionScene* scene=CCTransitionFadeUp::create(1.0, MainGame::scene());
    CCDirector::sharedDirector()->replaceScene(scene);
}

void StartGame::quitGame()
{

}

void StartGame::setGame()
{
    GameSet* layer=GameSet::create();
    this->addChild(layer);
}

StartGame::~StartGame()
{
    game->release();
}