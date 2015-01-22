#include "gamebasescene.h"

GameBaseScene::GameBaseScene()
{}
GameBaseScene::~GameBaseScene()
{

}


Scene *GameBaseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameBaseScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameBaseScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    addMap();
    initTiledGrid();
    return true;
}
void GameBaseScene::addDice()
{
    diceFrameCache = SpriteFrameCache::getInstance();
    diceFrameCache->addSpriteFramesWithFile("map/dice.plist", "map/dice.png");
    Vector<SpriteFrame*> diceVector;
    char name[20];
    memset(name, 0, 20);
    
    for (int i = 1; i <= 6; ++i ) {
        sprintf(name, "dice_%02d.png", i);
        diceVector.pushBack(diceFrameChache->getSpriteFrameByName(name));
    }
    if(!AnimationCache::getInstance()->getAnimation("dice_animation"))
    {
        
    }
}

void GameBaseScene::onExit()
{
    
}
