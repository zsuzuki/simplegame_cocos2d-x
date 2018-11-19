//
//  InGameScene.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "InGameScene.hpp"
#include "GameSupport.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene*
InGameScene::createScene()
{
  return InGameScene::create();
}

bool
InGameScene::init()
{
  if (!Scene::init())
  {
    return false;
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  auto l = Label::createWithTTF("In Game", "fonts/Marker Felt.ttf", 24);
  l->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - l->getContentSize().height));
  this->addChild(l, 1);

  auto listener = EventListenerTouchOneByOne::create();
  listener->setSwallowTouches(true);

  listener->onTouchBegan = [](Touch* touch, Event* event) { return true; };
  listener->onTouchMoved = [](Touch* touch, Event* event) {};
  listener->onTouchEnded = [](Touch* touch, Event* event) { ReturnMode(); };

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

//
void
InGameScene::update(float dt)
{
  GameUpdate(dt);
}

void
InGameScene::onEnter()
{
  Scene::onEnter();
  scheduleUpdate();
}
void
InGameScene::onExit()
{
  Scene::onExit();
  unscheduleUpdate();
}
