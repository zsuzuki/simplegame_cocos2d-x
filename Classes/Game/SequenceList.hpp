//
//  SequenceList.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef SequenceList_hpp
#define SequenceList_hpp

#include <cstdint>
#include <memory>

namespace Game
{
enum class SequenceMode : uint8_t
{
  None,
  Setup,
  Title,
  InGame,
};

class Mode;
using ModePtr = std::shared_ptr<Mode>;
ModePtr getModePtr(SequenceMode ss);

} // namespace Game

#endif /* SequenceList_hpp */
