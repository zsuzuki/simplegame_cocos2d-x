//
//  StartUpScene.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/25.
//

#include "StartUpScene.hpp"
#include "Game/context.hpp"
#include "GameSupport.hpp"
#include "InputImplement.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene*
StartUpScene::createScene()
{
  return StartUpScene::create();
}

bool
StartUpScene::init()
{
  if (!Scene::init())
  {
    return false;
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  auto s = Sprite::create("maker.png");
  s->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
  this->addChild(s, 0);

  return true;
}

//
void
StartUpScene::update(float dt)
{
  GameUpdate(dt);
}

void
StartUpScene::onEnter()
{
  Scene::onEnter();
}
void
StartUpScene::onExit()
{
  Scene::onExit();
  unscheduleUpdate();
}

void
StartUpScene::onEnterTransitionDidFinish()
{
  scheduleUpdate();
}

void
StartUpScene::onExitTransitionDidStart()
{
}
