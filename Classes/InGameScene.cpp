//
//  InGameScene.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "InGameScene.hpp"
#include "Game/status/Player.hpp"
#include "Game/status/Status.hpp"
#include "Game/context.hpp"
#include "GameSupport.hpp"
#include "InputImplement.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene*
InGameScene::createScene()
{
  return InGameScene::create();
}

namespace
{
//
Vec2
calc_center(Vec2 p, Vec2 f, Size vs, Vec2 o)
{
  auto vh = vs / 2.0f;
  return {p.x / f.x + o.x + vh.width, p.y / f.y + o.y + vh.height};
}

} // namespace

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

  auto  ii = GetGameInput();
  auto& i1 = ii->getInput(0);

  listener->onTouchBegan = [&](Touch* touch, Event* event) {
    i1.beginTouch(*touch);
    return true;
  };
  listener->onTouchMoved = [&](Touch* touch, Event* event) {
    i1.moveTouch(*touch);
    return true;
  };
  listener->onTouchEnded = [&](Touch* touch, Event* event) {
    i1.endTouch(*touch);
    ReturnMode();
    return true;
  };

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

  auto vs   = Director::getInstance()->getVisibleSize();
  Vec2 orgs = Director::getInstance()->getVisibleOrigin();

  auto& ctx    = GetGameContext();
  auto  status = ctx.get<Game::Status>("status");
  auto  player = ctx.get<Game::Player>("player");

  Vec2 p_pos{player->getX(), player->getY()};
  Vec2 f_sz{status->getFieldWidth(), status->getFieldHeight()};
  Vec2 spos = calc_center(p_pos, f_sz, vs, orgs);

  auto sprite = Sprite::create("circle.png");
  sprite->setPosition(spos);
  this->addChild(sprite, 0);
}
void
InGameScene::onExit()
{
  Scene::onExit();
  unscheduleUpdate();
}

void
InGameScene::onEnterTransitionDidFinish()
{
  scheduleUpdate();
}

void
InGameScene::onExitTransitionDidStart()
{
}
