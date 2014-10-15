//
//  StartGame.h
//  HPRunning
//
//  Created by student on 14-5-12.
//
//

#ifndef __HPRunning__StartGame__
#define __HPRunning__StartGame__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class GameSet;
class StartGame : public CCLayer
{
public:
    ~StartGame();
    virtual bool init();
    static CCScene* scene();
    CREATE_FUNC(StartGame);
    
public:
    GameSet* game;
    void moveMan();
    void addButton();
    void beginGame();
    void quitGame();
    void setGame();
};
#endif /* defined(__HPRunning__StartGame__) */
