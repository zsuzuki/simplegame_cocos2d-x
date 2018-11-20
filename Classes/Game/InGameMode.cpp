//
//  InGameMode.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "InGameMode.hpp"
#include "Manager.hpp"
#include "Status.hpp"
#include "context.hpp"

namespace Game
{
namespace
{
double score = 0.0;
}

InGameMode::InGameMode() {}
InGameMode::~InGameMode() {}
void
InGameMode::initialize()
{
  score = 0.0;
}
bool
InGameMode::completeInitialize()
{
  return true;
}
void
InGameMode::finalize()
{
  auto& ctx  = Manager::getContext();
  auto  stat = ctx.get<Status>("stat");
  if (!stat)
  {
    stat = ctx.create<Status>("stat");
  }
  stat->setScore(score);
}

bool
InGameMode::completeFinalize()
{
  return true;
}
void
InGameMode::update(float dt)
{
  score += dt * 10.0f;
}
} // namespace Game
