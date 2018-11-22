//
//  Manager.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef Manager_hpp
#define Manager_hpp

#include <cstdint>
#include <functional>

namespace Game
{
enum class SequenceMode : uint8_t;
class Context;

//
// Game control class
//
namespace Manager
{
void setup(SequenceMode sm);
void update(float dt);

Context& getContext();

using ModeChangeFunc = std::function<void(SequenceMode)>;
void         requestSequence(SequenceMode ss, bool jump, ModeChangeFunc f);
SequenceMode popSequence();
} // namespace Manager

} // namespace Game

#endif /* Manager_hpp */
