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

namespace Game {
    class Context;
}

void SwitchMode(Game::SequenceMode mode);
void ReturnMode();
void GameUpdate(float dt);
Game::Context& GetGameContext();

#endif /* GameSupport_hpp */
