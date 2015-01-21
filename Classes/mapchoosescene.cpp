#include "mapchoosescene.h"

MapChooseScene::MapChooseScene()
{
}
MapChooseScene::~MapChooseScene()
{
}

Scene* MapChooseScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MapChooseScene::create();
    scene->addChild(layer);
    return scene;
}

bool MapChooseScene::init()
{
    if(!Layer::init()){
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    currentPage = 1;
    addBackGroundSprite();
    addScrollView();
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MapChooseScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MapChooseScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MapChooseScene::onTouchEnded, this);

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

void MapChooseScene::addScrollView()
{
    Point centerPt = Point(visibleSize.width/2, visibleSize.height/2);
    spriteContainer = Layer::create();

    Sprite* beachSprite = Sprite::create("map/beach_item.png");
    Sprite* seaSprite = Sprite::create("map/sea_item.png");
    Sprite* moonSprite = Sprite::create("map/moon_item.png");

    spriteContainer->addChild(beachSprite);
    beachSprite->setPosition(centerPt);

    spriteContainer->addChild(seaSprite);
    seaSprite->setPosition(centerPt + Point(visibleSize.width, 0));

    spriteContainer->addChild(moonSprite);
    moonSprite->setPosition(centerPt + Point(visibleSize.width*2, 0));

    spriteContainer->setPosition(Point::ZERO);
    spriteContainer->setContentSize(Size(visibleSize.width * MAP_COUNT, visibleSize.height));

    scrollView = ScrollView::create();
    scrollView->setContainer(spriteContainer);
    scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    scrollView->setTouchEnabled(true);
    scrollView->setPosition(Point::ZERO);

    scrollView->setViewSize(visibleSize);
    scrollView->setContentOffset(Point::ZERO, true);
    scrollView->setContentSize(Size(visibleSize.width * MAP_COUNT, visibleSize.height));
    scrollView->setDelegate(this);
    scrollView->setTouchEnabled(false);
    addChild(scrollView);

}

bool MapChooseScene::onTouchBegan(Touch *touch, Event *unusedEvent)
{
    beginTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
    log("touch began");
    return true;
}


void MapChooseScene::onTouchEnded(Touch *touch, Event *unusedEvent)
{
    Point endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
    float distance = endPoint.x - beginTouchPoint.x;
    if(fabs(distance) > TOUCH_DISTANCE)
    {
        adjustScrollView(distance);
    }
    else
    {
        if(currentPage == 2)
        {
            //auto scene = TransitionFadeBL::create(2, seaScene::create());
            //Director::getInstance()->pushScene(scene);
        }
    }
}

void MapChooseScene::adjustScrollView(float offset)
{
    log("adjustScrollView");
    if (offset>0)
    {
        currentPage--;
    }
    else
    {
        currentPage++;
    }

    if(currentPage < 1)
    {
        currentPage = 1;
    }

    if(currentPage > MAP_COUNT)
    {
        currentPage = MAP_COUNT;
    }

    Point adjustPos = Point(-visibleSize.width*(currentPage-1), 0);
    scrollView->setContentOffset(adjustPos, true);
}


void MapChooseScene::scrollViewDidScroll(ScrollView *view)
{
    //log("MapChoosScene::scrollViewDidScroll");
}


void MapChooseScene::onTouchMoved(Touch* touch, Event *unusedEvent)
{
    //log("ontouchMoved");
}


void MapChooseScene::scrollViewDidZoom(ScrollView *view)
{
    log("MapChooseScene::scrollViewDidZoom");
}

void MapChooseScene::scrollViewMoveOver(ScrollView *view)
{
    log("MapChooseScene::scrollViewMoveOver");
}

void MapChooseScene::addBackGroundSprite()
{
    Sprite* stageSprite = Sprite::create("map/stage_background2.png");
    stageSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
    stageSprite->setAnchorPoint(Point(0.5, 0.5));
    addChild(stageSprite);
}
