/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Game/context.hpp"
#include "Game/status/Status.hpp"
#include "GameSupport.hpp"
#include "InputImplement.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene*
HelloWorld::createScene()
{
  return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void
problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool
HelloWorld::init()
{
  if (!Scene::init())
  {
    return false;
  }

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin      = Director::getInstance()->getVisibleOrigin();

  auto closeItem =
      MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

  if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
  {
    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
  }
  else
  {
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));
  }

  auto menu = Menu::create(closeItem, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);

  auto label = Label::createWithTTF("Touch to START", "fonts/Marker Felt.ttf", 24);
  if (label == nullptr)
  {
    problemLoading("'fonts/Marker Felt.ttf'");
  }
  else
  {
    // position the label on the center of the screen
    label->setPosition(
        Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3 - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
  }

  // add "HelloWorld" splash screen"
  auto sprite = Sprite::create("launch.png");
  if (sprite == nullptr)
  {
    problemLoading("'HelloWorld.png'");
  }
  else
  {
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
  }

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
    SwitchMode(Game::SequenceMode::InGame);
    return true;
  };

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

  return true;
}

//
void
HelloWorld::update(float dt)
{
  GameUpdate(dt);
}

void
HelloWorld::onEnter()
{
  auto  visibleSize = Director::getInstance()->getVisibleSize();
  Vec2  origin      = Director::getInstance()->getVisibleOrigin();
  auto& ctx         = GetGameContext();
  auto  stat        = ctx.get<Game::Status>("status");
  if (stat)
  {
    char buff[128];
    snprintf(buff, sizeof(buff), "Score: %d", stat->getScore());
    auto l = Label::createWithTTF(buff, "fonts/Marker Felt.ttf", 24);
    auto h = visibleSize.height;
    l->setPosition({origin.x + visibleSize.width / 2, origin.y + (h - h / 3)});
    this->addChild(l);
  }

  Scene::onEnter();
}
void
HelloWorld::onExit()
{
  Scene::onExit();
  unscheduleUpdate();
}

void
HelloWorld::onEnterTransitionDidFinish()
{
  scheduleUpdate();
}

void
HelloWorld::onExitTransitionDidStart()
{
}

//
void
HelloWorld::menuCloseCallback(Ref* pSender)
{
  // Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  exit(0);
#endif

  /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
   * Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm
   * as below*/

  // EventCustom customEndEvent("game_scene_close_event");
  //_eventDispatcher->dispatchEvent(&customEndEvent);
}
