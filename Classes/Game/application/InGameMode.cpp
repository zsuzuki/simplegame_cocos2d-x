//
//  InGameMode.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "InGameMode.hpp"
#include "../context.hpp"
#include "../status/Player.hpp"
#include "../status/Status.hpp"
#include "../system/InputInterface.hpp"
#include "../system/Manager.hpp"

namespace Game
{
namespace
{
double                  score = 0.0;
std::shared_ptr<Player> player;
} // namespace

InGameMode::InGameMode() {}
InGameMode::~InGameMode() {}

void
InGameMode::initialize()
{
  auto& ctx = Manager::getContext();

  auto stat = ctx.get<Status>("status");
  if (!stat)
  {
    stat = ctx.create<Status>("status");
  }

  auto player = ctx.get<Player>("player");
  if (!player)
  {
    player = ctx.create<Player>("player");
    player->setX(stat->getFieldWidth() * 0.5f);
    player->setY(stat->getFieldHeight() * 0.5f);
  }
  auto player2 = ctx.get<Player>("player2");
  if (!player2)
  {
    player2 = ctx.create<Player>("player2");
    player2->setX(stat->getFieldWidth() * 0.5f);
    player2->setY(stat->getFieldHeight() * 0.5f);
  }

  score = 0.0;

  printf("in game\n");
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
  auto  stat = ctx.get<Status>("status");
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
  auto& ctx     = Manager::getContext();
  auto  stat    = ctx.get<Status>("status");
  auto  player  = ctx.get<Player>("player");
  auto  player2 = ctx.get<Player>("player2");
  auto  input   = Manager::getInputManager();
  auto* input0  = input->getInput(0);
  auto  fx      = stat->getFieldWidth();
  auto  fy      = stat->getFieldHeight();
  player->setX((input0->getAnalog(0) * fx + fx) * 0.5f);
  player->setY((input0->getAnalog(1) * fy + fy) * 0.5f);
  player2->setX((input0->getAnalog(2) * fx + fx) * 0.5f);
  player2->setY((input0->getAnalog(3) * fy + fy) * 0.5f);

  if (score > 2.0 && input0->getSwitch(0))
  {
    auto mode = Game::Manager::popSequence();
    Game::Manager::requestSequence(mode, true);
    printf("exit game mode\n");
  }
}
} // namespace Game
