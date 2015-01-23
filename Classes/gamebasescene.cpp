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
        diceVector.pushBack(diceFrameCache->getSpriteFrameByName(name));

    }

    if(!AnimationCache::getInstance()->getAnimation("dice_animation"))
    {
        auto animation = Animation::createWithSpriteFrames(diceVector, 0.1);
        AnimationCache::getInstance()->addAnimation(animation, "dice_animation");
    }

    auto animation = AnimationCache::getInstance()->getAnimation("dice_animation");
    dice_animate = Animate::create(animation);
    dice_animate->retain();

    auto spriteFrame = diceFrameCache->getSpriteFrameByName("dice_01.png");
    diceSprite = Sprite::createWithSpriteFrame(spriteFrame);

    Point position(tableStartPosition_x + 2 * tableWidth, tableStartPosition_y - tableHeight * 4.5);
    diceSprite->setPosition(position);
    addChild(diceSprite);

    diceSprite->runAction(RepeatForever::create(dice_animate));

}

void GameBaseScene::onExit()
{

}
