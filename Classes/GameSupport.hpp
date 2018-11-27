//
//  GameSupport.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef GameSupport_hpp
#define GameSupport_hpp

#include "Game/SequenceList.hpp"
#include <cstdint>
#include <memory>

namespace Game
{
class Context;
}
class GameInputManager;
using GameInputManagerPtr = std::shared_ptr<GameInputManager>;

void GameSetup();

void SwitchMode(Game::SequenceMode mode);
void ResetMode(Game::SequenceMode mode);
void ReturnMode();
void GameUpdate(float dt);

GameInputManagerPtr GetGameInput();
Game::Context&      GetGameContext();

#endif /* GameSupport_hpp */
