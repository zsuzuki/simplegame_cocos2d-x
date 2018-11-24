//
//  Main.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/25.
//

#include "Main.hpp"
#include "../SequenceList.hpp"
#include "../system/InputInterface.hpp"
#include "../system/Manager.hpp"

namespace Game
{
namespace
{
// コントローラのアクティベーション
bool
activate_controller(int dev_id)
{
  if (dev_id < 0)
    return false;
  printf("activate controller\n");
  return true;
}
} // namespace

SetupMode::SetupMode() {}
SetupMode::~SetupMode() {}
void
SetupMode::initialize()
{
  printf("setup start\n");
  auto input_manager = Manager::getInputManager();
  input_manager->setActivateFunction(activate_controller);
}
bool
SetupMode::completeInitialize()
{
  Manager::requestSequence(SequenceMode::Title, true);
  printf("setup finish\n");
  return true;
}
void
SetupMode::finalize()
{
}
bool
SetupMode::completeFinalize()
{
  return true;
}
void
SetupMode::update(float dt)
{
}

} // namespace Game
