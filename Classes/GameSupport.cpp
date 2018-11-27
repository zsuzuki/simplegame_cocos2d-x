//
//  GameSupport.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "GameSupport.hpp"
#include "Game/context.hpp"
#include "Game/system/Manager.hpp"
#include "HelloWorldScene.h"
#include "InGameScene.hpp"
#include "InputImplement.hpp"
#include "cocos2d.h"
#include <map>

USING_NS_CC;

namespace
{
// 現在が違うシーンであれば、新しいシーンを生成
template <class T, class S>
cocos2d::Scene*
make_scene(S* current)
{
  if (dynamic_cast<T*>(current) == nullptr)
    return T::createScene();
  return nullptr;
};
// モードに対応するシーンの切り替え
void
switch_scene(Game::SequenceMode m)
{
  cocos2d::Scene* scene   = nullptr;
  auto*           current = Director::getInstance()->getRunningScene();
  switch (m)
  {
  case Game::SequenceMode::Title:
    scene = make_scene<HelloWorld>(current);
    break;
  case Game::SequenceMode::InGame:
    scene = make_scene<InGameScene>(current);
    break;
  default:
    break;
  }
  if (scene)
  {
    auto input_manager = std::dynamic_pointer_cast<GameInputManager>(Game::Manager::getInputManager());
    input_manager->changeScene();
    auto* fade = TransitionFade::create(0.5f, scene, {0, 0, 0});
    Director::getInstance()->replaceScene(fade);
  }
}
// コントローラマネージャ
GameInputManagerPtr input;
} // namespace

// 指定モードに移行して、対応するUIに切り替える
void
SwitchMode(Game::SequenceMode mode)
{
  Game::Manager::requestSequence(mode, false);
}

// 指定モードに移行して、対応するUIに切り替える(かつモード履歴もリセット)
void
ResetMode(Game::SequenceMode mode)
{
  Game::Manager::resetSequence(mode);
}

// 前のモードに戻る
void
ReturnMode()
{
  auto mode = Game::Manager::popSequence();
  Game::Manager::requestSequence(mode, true);
}

//
void
GameSetup()
{
  Game::Manager::setup(Game::SequenceMode::Setup);
  input = std::make_shared<GameInputManager>();
  Game::Manager::setInputManager(input);
  Game::Manager::setChangeModeFunction(switch_scene);
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

//
GameInputManagerPtr
GetGameInput()
{
  return input;
}
