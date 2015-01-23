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
    void addDice();
    CREATE_FUNC(GameBaseScene);
  private:
    CC_SYNTHESIZE(Animate*, dice_animate, Dice_animate);
    CC_SYNTHESIZE(Sprite*, diceSprite, DiceSprite)
  private:
    static const int tileColsCount = 20;
    static const int tileRowsCount = 15;
    static const int tileWidth = 32;
    static const int tileHeight = 32;
    static const int tableStartPosition_x = 650;
    static const int tableStartPosition_y = 450;
    static const int tableWidth = 50;
    static const int tableHeight = 40;
    static const int FONT_SIZE = 20;
    SpriteFrameCache *diceFrameCache;
    TMXTiledMap* map;

};






#endif /* GAMEBASESCENE_H */

