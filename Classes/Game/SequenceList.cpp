//
//  SequenceList.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "SequenceList.hpp"
#include "InGameMode.hpp"
#include "TitleMode.hpp"
#include <map>

namespace Game
{
namespace
{
// 各モードクラスのホルダ
std::map<SequenceMode, ModePtr> sequence_list = {
    {SequenceMode::Title, std::make_shared<TitleMode>()},
    {SequenceMode::InGame, std::make_shared<InGameMode>()},
};
} // namespace

//
ModePtr
getModePtr(SequenceMode ss)
{
  return sequence_list[ss];
}

} // namespace Game
