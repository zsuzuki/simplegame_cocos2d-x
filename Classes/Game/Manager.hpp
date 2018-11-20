//
//  Manager.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef Manager_hpp
#define Manager_hpp

#include <cstdint>

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

void         requestSequence(SequenceMode ss, bool jump = false);
SequenceMode getReturnSequence();
} // namespace Manager

} // namespace Game

#endif /* Manager_hpp */
