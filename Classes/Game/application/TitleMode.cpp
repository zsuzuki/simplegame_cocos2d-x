//
//  TitleMode.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "TitleMode.hpp"
#include "../status/Status.hpp"
#include <cstdio>

namespace Game
{
TitleMode::TitleMode() {}
TitleMode::~TitleMode() {}
void
TitleMode::initialize()
{
  printf("in title mode\n");
}
bool
TitleMode::completeInitialize()
{
  return true;
}
void
TitleMode::finalize()
{
  printf("out title mode\n");
}
bool
TitleMode::completeFinalize()
{
  return true;
}
void
TitleMode::update(float dt)
{
}
} // namespace Game
