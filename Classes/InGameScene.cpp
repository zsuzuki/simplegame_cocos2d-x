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
  this->addChild(l, 2);

  auto listener = EventListenerTouchAllAtOnce::create();

  auto  ii = GetGameInput();
  auto* i1 = ii->getInput(0);

  listener->onTouchesBegan = [=](const std::vector<Touch*>& touch, Event* event) {
    for (auto t : touch)
      i1->beginTouch(*t);
    return true;
  };
  listener->onTouchesMoved = [=](const std::vector<Touch*>& touch, Event* event) {
    for (auto t : touch)
      i1->moveTouch(*t);
      printf("nb touch: %zu\n",touch.size());
    return true;
  };
  listener->onTouchesEnded = [=](const std::vector<Touch*>& touch, Event* event) {
    for (auto t : touch)
      i1->endTouch(*t);
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

  auto& ctx     = GetGameContext();
  auto  status  = ctx.get<Game::Status>("status");
  auto  player  = ctx.get<Game::Player>("player");
  auto  player2 = ctx.get<Game::Player>("player2");

  Vec2 f_sz{status->getFieldWidth(), status->getFieldHeight()};

  auto set_pos = [&](auto& pl, auto* sp) {
    Vec2 p_pos{pl->getX(), pl->getY()};
    Vec2 spos = calc_center(p_pos, f_sz, vs, orgs);
    sp->setPosition(spos);
  };
  set_pos(player, sprite);
  set_pos(player2, sprite2);
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
  this->addChild(sprite, 1);
  sprite2 = Sprite::create("rect_o.png");
  this->addChild(sprite2, 0);

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
