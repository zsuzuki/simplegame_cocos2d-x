//
//  SequenceList.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "SequenceList.hpp"
#include "application/InGameMode.hpp"
#include "application/Main.hpp"
#include "application/TitleMode.hpp"
#include <map>

namespace Game
{
namespace
{
// 各モードクラスのホルダ
std::map<SequenceMode, ModePtr> sequence_list = {
    {SequenceMode::Setup, std::make_shared<SetupMode>()},
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
