#include "popuplayer.h"


PopupLayer::PopupLayer():
        m_pMenu(NULL),
        m_s9BackGround(NULL),
        m_spBackGround(NULL),
        m_ltTitle(NULL),
        m_ltContentText(NULL)
{

}
PopupLayer::~PopupLayer()
{
    CC_SAFE_RELEASE(m_pMenu);
    CC_SAFE_RELEASE(m_spBackGround);
    CC_SAFE_RELEASE(m_s9BackGround);
    CC_SAFE_RELEASE(m_ltContentText);
    CC_SAFE_RELEASE(m_ltTitle);
}

PopupLayer* PopupLayer::create(const char *bgImg)
{
    PopupLayer *pl = PopupLayer::create();
    pl->setSpriteBackGround(Sprite::create(bgImg));
    pl->setSprite9BackGround(ui::Scale9Sprite::create(bgImg));
    return pl;
}

void PopupLayer::buttonCallback(Ref* pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
    if(m_callback && m_callbackListener)
    {
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();
}


void PopupLayer::onEnter()
{
    Layer::onEnter();
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPt = Point(winSize.width/2, winSize.height/2);
    Size contentSize;
    if (getContentSize().equals(Size::ZERO)){
        getSpriteBackGround()->setPosition(centerPt);
        addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    }
    else
    {
        ui::Scale9Sprite* backGround = getSprite9BackGround();
        backGround->setPosition(centerPt);
        contentSize = getContentSize();
        backGround->setContentSize(contentSize);
        addChild(backGround, 0, 0);
    }

    // add button
    addChild(getMenuButton());
    float btnWidth = contentSize.width /(getMenuButton()->getChildrenCount() + 1);
    Vector<Node*> vecArray = getMenuButton()->getChildren();
    int j = 0;
    for (auto it=vecArray.begin(); it !=vecArray.end(); ++it) {
        Node* node = dynamic_cast<Node*>(*it);
        node->setPosition(Point(winSize.width/2-contentSize.width/2+btnWidth*(j+1),
                                winSize.height/2-contentSize.height/3));
        ++j;
    }

    //show title
    if(getLabelTitle())
    {
        getLabelTitle()->setPosition(centerPt + Point(0, contentSize.height/2-20));
        getLabelTitle()->setColor(Color3B(0,0,0));
        addChild(getLabelTitle());
    }
    // show content of text box
    auto ltf = getLabelContentText();
    if (ltf){
        ltf->setPosition(centerPt);
        //ltf->setDimensions(contentSize.width-m_contentPadding*2,
		//		contentSize.height-m_contentPaddingTop);
        //ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
        ltf->setColor(Color3B(0,1,1));
        addChild(ltf);

    }

    // effection of pop
    Action *popupLayer = Sequence::create(ScaleTo::create(0,0),
                                          ScaleTo::create(0.15, 1.05),
                                          ScaleTo::create(0.08, 0.95),
                                          ScaleTo::create(0.08, 1.0),
                                          NULL);
    runAction(popupLayer);

}


void PopupLayer::onExit()
{
    log("PopupLayer onExit");
    Layer::onExit();
}

void PopupLayer::setCallbackFunc(Ref *target, SEL_CallFuncN callFun)
{
    m_callbackListener = target;
    m_callback = callFun;
}


void PopupLayer::setTitle(const char *title, int fontSize)
{
    TTFConfig ttfConf("fonts/Marker Felt.ttf", 20);
    Label *tlTTF = Label::createWithTTF(ttfConf,
                                        title,
                                        TextHAlignment::LEFT);
    setLabelTitle(tlTTF);
}


bool PopupLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    setContentSize(Size::ZERO);
    Menu *menu = Menu::create();
    menu->setPosition(Point::ZERO);

    setMenuButton(menu);
    // setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch*t, Event *e){
         log("Popuplayer touch");
         return true;
    };
    //getEventDispatcher()
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


bool PopupLayer::addButton(const char* normalImg,
                           const char* selectedImg,
                           const char* title, int tag)
{
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPt = Point(winSize.width/2, winSize.height/2);

    // create picture and menu buttons
    auto* menuImage = MenuItemImage::create(normalImg,
                                            selectedImg,
                                            this,
                                            menu_selector(PopupLayer::buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(centerPt);

    Size imenu = menuImage->getContentSize();
    TTFConfig ttfConf("fonts/Marker Felt.ttf", 20);
    Label* ttf = Label::createWithTTF(ttfConf,
                                      title,
                                      TextHAlignment::LEFT);
    ttf->setPosition(Point(imenu.width/2, imenu.height/2));
    menuImage->addChild(ttf);
    getMenuButton()->addChild(menuImage);

    return true;
}


void PopupLayer::setContentText(const char* text,
                                int fontSize,
                                int padding,
                                int paddingTop)
{
    TTFConfig ttfConf("fonts/Marker Felt.ttf", 20);
    Label* ltf = Label::createWithTTF(ttfConf,
                                      text,
                                      TextHAlignment::LEFT);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}
