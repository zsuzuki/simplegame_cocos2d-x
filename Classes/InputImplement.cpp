//
//  InputImplement.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/23.
//

#include "InputImplement.hpp"

GameInput::GameInput() : valid(false) {}
GameInput::~GameInput() {}

bool
GameInput::setSwitchMap(std::vector<int> map_list)
{
  return true;
}

void
GameInput::preUpdate(float dt)
{
}
void
GameInput::postUpdate()
{
  prev_switch_list = switch_list;
}

bool
GameInput::isValid() const
{
  return valid;
}

std::pair<int, int>
GameInput::requestNeedChannel(int nb_sw, int nb_ana)
{
  auto& sl = switch_list;
  auto& al = analog_list;
  sl.resize(nb_sw);
  al.resize(nb_ana);
  std::fill(sl.begin(), sl.end(), false);
  std::fill(al.begin(), al.end(), 0.0f);
  prev_switch_list = sl;
  return std::make_pair(nb_sw, nb_ana);
}

bool
GameInput::getSwitch(int id) const
{
  return switch_list[id];
}
bool
GameInput::getSwitchOn(int id) const
{
  return switch_list[id] && prev_switch_list[id] == false;
}

float
GameInput::getAnalog(int id) const
{
  return analog_list[id];
}

const Game::InputInterface::Touch&
GameInput::getTouch(int id) const
{
  return touch_list[id];
}

size_t
GameInput::getNbTouch() const
{
  return touch_list.size();
}

//
//
//

void
GameInput::beginTouch(cocos2d::Touch& t)
{
  auto v = t.getLocation();
  auto i = t.getID();
  // auto d = t.getDelta();
  printf("begin[%2d]: %0.1f, %0.1f\n", i, v.x, v.y);
}
void
GameInput::moveTouch(cocos2d::Touch& t)
{
  auto v = t.getLocation();
  auto i = t.getID();
  auto d = t.getDelta();
  printf("move[%2d]: %0.1f, %0.1f(%0.1f, %0.1f)\n", i, v.x, v.y, d.x, d.y);
}
void
GameInput::endTouch(cocos2d::Touch& t)
{
  auto v = t.getLocation();
  auto i = t.getID();
  auto d = t.getDelta();
  printf("end[%2d]: %0.1f, %0.1f(%0.1f, %0.1f)\n", i, v.x, v.y, d.x, d.y);
}

//
// Input manager
//

void
GameInputManager::preUpdate(float dt)
{
  if (input.size() == 0)
  {
    input.resize(1);
  }

  for (auto& i : input)
  {
    if (i.isValid())
    {
      i.preUpdate(dt);
    }
    else if (active_func)
    {
      i.setValid(active_func(0));
    }
  }
}

void
GameInputManager::postUpdate()
{
  for (auto& i : input)
    i.postUpdate();
}

size_t
GameInputManager::getNbInput()
{
  return input.size();
}
GameInput&
GameInputManager::getInput(int ch)
{
  return input[ch];
}
