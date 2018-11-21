//
//  GameSupport.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "GameSupport.hpp"
#include "Game/Manager.hpp"
#include "HelloWorldScene.h"
#include "InGameScene.hpp"
#include "cocos2d.h"
#include <map>

USING_NS_CC;

namespace
{
// モードに対応するシーンの切り替え
void
switch_scene(Game::SequenceMode mode, bool jump)
{
  Game::Manager::requestSequence(mode, jump, [mode]() {
    cocos2d::Scene* scene = nullptr;
    switch (mode)
    {
    case Game::SequenceMode::Title:
      scene = HelloWorld::createScene();
      break;
    case Game::SequenceMode::InGame:
      scene = InGameScene::createScene();
      break;
    default:
      break;
    }
    if (scene)
    {
      auto* fade = TransitionFade::create(0.5f, scene, {255, 255, 255});
      Director::getInstance()->replaceScene(fade);
    }
  });
}
} // namespace

// 指定モードに移行して、対応するUIに切り替える
void
SwitchMode(Game::SequenceMode mode)
{
  switch_scene(mode, false);
}

// 前のモードに戻る
void
ReturnMode()
{
  auto mode = Game::Manager::popSequence();
  switch_scene(mode, true);
}

//
void
GameUpdate(float dt)
{
  Game::Manager::update(dt);
}

//
Game::Context&
GetGameContext()
{
  return Game::Manager::getContext();
}
