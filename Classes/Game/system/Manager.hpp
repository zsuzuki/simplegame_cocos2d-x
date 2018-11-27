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
#include <memory>

namespace Game
{
enum class SequenceMode : uint8_t;
class Context;
class InputManager;

//
// Game control class
//
namespace Manager
{

void setup(SequenceMode sm);
void update(float dt);

using InputManagerPtr = std::shared_ptr<InputManager>;
void            setInputManager(InputManagerPtr im);
InputManagerPtr getInputManager();

Context& getContext();

using ModeChangeFunc = std::function<void(SequenceMode)>;
void         requestSequence(SequenceMode ss, bool jump);
void         resetSequence(SequenceMode ss);
void         setChangeModeFunction(ModeChangeFunc f);
SequenceMode popSequence();
} // namespace Manager

} // namespace Game

#endif /* Manager_hpp */
