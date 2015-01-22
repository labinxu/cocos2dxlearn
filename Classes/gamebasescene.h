#ifndef GAMEBASESCENE_H
#define GAMEBASESCENE_H

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;


class GameBaseScene : public Layer
{
  public:
    GameBaseScene();
    ~GameBaseScene();
    static Scene* createScene();
    virtual bool init();
    virtual void addMap(){};
    void onExit();
    void initTiledGrid(){};
    vid addDice();
    CREATE_FUNC(GameBaseScene);

  private:
    static const int titleColsCount = 20;
    static const int titleRowsCount = 15;
    SpriteFrameCache *diceFrameCache;
    TMXTiledMap* map;
};






#endif /* GAMEBASESCENE_H */

