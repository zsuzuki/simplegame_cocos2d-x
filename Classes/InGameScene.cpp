//
//  InGameScene.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "InGameScene.hpp"
#include "Game/context.hpp"
#include "Game/status/Player.hpp"
#include "Game/status/Status.hpp"
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
  return {p.x / f.x * vs.width + o.x, p.y / f.y * vs.height + o.y};
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
  auto* i1 = ii->getInput(0);

  listener->onTouchBegan = [=](Touch* touch, Event* event) {
    i1->beginTouch(*touch);
    return true;
  };
  listener->onTouchMoved = [=](Touch* touch, Event* event) {
    i1->moveTouch(*touch);
    return true;
  };
  listener->onTouchEnded = [=](Touch* touch, Event* event) {
    i1->endTouch(*touch);
    return true;
  };

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

//
void
InGameScene::updateDisp()
{
  auto vs   = Director::getInstance()->getVisibleSize();
  Vec2 orgs = Director::getInstance()->getVisibleOrigin();

  auto& ctx    = GetGameContext();
  auto  status = ctx.get<Game::Status>("status");
  auto  player = ctx.get<Game::Player>("player");

  Vec2 p_pos{player->getX(), player->getY()};
  Vec2 f_sz{status->getFieldWidth(), status->getFieldHeight()};
  Vec2 spos = calc_center(p_pos, f_sz, vs, orgs);

  sprite->setPosition(spos);
}

//
void
InGameScene::update(float dt)
{
  GameUpdate(dt);
  updateDisp();
}

void
InGameScene::onEnter()
{
  Scene::onEnter();

  sprite = Sprite::create("circle.png");
  this->addChild(sprite, 0);

  updateDisp();
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
