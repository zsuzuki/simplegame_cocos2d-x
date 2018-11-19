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

//
// Game control class
//
class Manager
{
public:
  Manager();
  ~Manager();

  static void setup(SequenceMode sm);
  static void update(float dt);

  static void         requestSequence(SequenceMode ss,bool jump = false);
  static SequenceMode getReturnSequence();

  static Manager& getInstance();
};
} // namespace Game

#endif /* Manager_hpp */
