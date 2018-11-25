//
//  InputImplement.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/23.
//

#include "InputImplement.hpp"

GameInput::GameInput() : valid(false) { touch_list.resize(10); }
GameInput::~GameInput() {}

bool
GameInput::setSwitchMap(std::vector<int> map_list)
{
  return true;
}

void
GameInput::clear()
{
  for (auto& t : touch_list)
    t = InTouch{};
  auto& sl = switch_list;
  auto& al = analog_list;
  std::fill(sl.begin(), sl.end(), false);
  std::fill(al.begin(), al.end(), 0.0f);
  prev_switch_list = sl;
}

void
GameInput::preUpdate(float dt)
{
  auto sw_sz = switch_list.size();
  auto an_sz = analog_list.size();
  for (size_t i = 0; i < touch_list.size(); i++)
  {
    auto& t = touch_list[i];
    if (t.on == false)
    {
      if (t.target_switch >= 0)
      {
        switch_list[t.target_switch] = false;
        printf("off switch: %d\n", t.target_switch);
      }
      if (t.target_analog0 >= 0)
        analog_list[t.target_analog0] = 0.0f;
      if (t.target_analog1 >= 0)
        analog_list[t.target_analog1] = 0.0f;
      continue;
    }
    if (t.still)
    {
      auto tnow = std::chrono::steady_clock::now();
      auto dur  = std::chrono::duration_cast<std::chrono::milliseconds>(tnow - t.start);
      if (dur.count() > 500 && i < sw_sz)
      {
        t.target_switch = i;
        switch_list[i]  = true;
        printf("on switch: %d\n", i);
      }
    }
    else if (i < sw_sz && switch_list[i] == false)
    {
      if (an_sz > 0)
      {
        // TODO: get screen size
        float x          = (t.x - t.bx) / 200.0f;
        analog_list[0]   = std::max(std::min(x, 1.0f), -1.0f);
        t.target_analog0 = 0;
        if (an_sz > 1)
        {
          float y          = (t.y - t.by) / 200.0f;
          analog_list[1]   = std::max(std::min(y, 1.0f), -1.0f);
          t.target_analog1 = 1;
        }
      }
    }
  }
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
  auto i = t.getID();
  if (i >= touch_list.size())
    return;
  auto& touch = touch_list[i];
  touch.on    = true;
  auto v      = t.getLocation();
  touch.x     = v.x;
  touch.y     = v.y;
  touch.bx    = v.x;
  touch.by    = v.y;
  touch.mx    = 0.0f;
  touch.my    = 0.0f;
  touch.delta = 0.0f;
  touch.start = std::chrono::steady_clock::now();
  touch.last  = touch.start;
  touch.still = true;

  touch.target_switch  = -1;
  touch.target_analog0 = -1;
  touch.target_analog1 = -1;

  //   auto mf = t.getMaxForce();
  //   auto cf = t.getCurrentForce();
  //   printf("begin[%2d]: %0.1f, %0.1f f=%0.1f(%0.1f)\n", i, v.x, v.y, cf, mf);
}
void
GameInput::moveTouch(cocos2d::Touch& t)
{
  auto i = t.getID();
  if (i >= touch_list.size())
    return;
  auto& touch = touch_list[i];
  auto  v     = t.getLocation();
  touch.x     = v.x;
  touch.y     = v.y;
  auto d      = t.getDelta();
  touch.mx    = d.x;
  touch.my    = d.y;
  touch.last  = std::chrono::steady_clock::now();
  if (sqrtf(d.x * d.x + d.y * d.y) > 1.0f)
    touch.still = false;

  //   auto mf  = t.getMaxForce();
  //   auto cf  = t.getCurrentForce();
  //   auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(touch.last - touch.start);
  //   printf("move[%2d]: %lld %0.1f, %0.1f f=%0.1f(%0.1f)\n", i, dur.count(), d.x, d.y, cf, mf);
}
void
GameInput::endTouch(cocos2d::Touch& t)
{
  auto i = t.getID();
  if (i >= touch_list.size())
    return;
  auto& touch = touch_list[i];
  touch.on    = false;
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
      i.setValid(active_func(0, i));
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
GameInput*
GameInputManager::getInput(int ch)
{
  if (ch >= input.size())
    return nullptr;
  auto& i = input[ch];
  return i.isValid() ? &i : nullptr;
}

void
GameInputManager::changeScene()
{
  for (auto& i : input)
  {
    if (i.isValid())
      i.clear();
  }
}