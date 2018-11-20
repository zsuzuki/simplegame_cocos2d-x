//
//  Manager.cpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#include "Manager.hpp"
#include "SequenceList.hpp"
#include "context.hpp"
#include "mode.h"
#include <memory>
#include <sol.hpp>
#include <vector>

namespace Game
{
namespace
{
//
struct Implement
{
  using SequenceStack = std::vector<SequenceMode>;
  sol::state    lua;
  Context       context;
  SequenceStack sequence;
  SequenceMode  request = SequenceMode::None;
  ModePtr       mode;
  bool          jump_sequence = false;
  bool          enable_update = false;

  Implement() { sequence.reserve(20); }

  // 現在のシーケンスを取得
  SequenceMode getSequence() const
  {
    auto sz = sequence.size();
    return sz == 0 ? SequenceMode::None : sequence[sz - 1];
  }
  // 次のシーケンスを設定
  void setSequence(SequenceMode s, bool replace)
  {
    auto sz = sequence.size();
    if (replace && sz > 0)
      sequence[sz - 1] = s;
    else
      sequence.push_back(s);
  }

  //
  void updateMode(float dt)
  {
    auto seq = getSequence();
    if (request != seq)
    {
      bool need_initialize = false;
      // モード変更リクエスト
      if (enable_update)
      {
        // 終了
        if (mode)
          mode->finalize();
        else
          need_initialize = true;
        enable_update = false; // 一旦更新禁止
      }
      else
        need_initialize = !mode || mode->completeFinalize();

      if (need_initialize)
      {
        // 終了チェック -> 次のモードの初期化
        mode = getModePtr(request);
        if (mode)
          mode->initialize();
        setSequence(request, jump_sequence);
        jump_sequence = false;
      }
    }
    else if (enable_update == false && mode)
    {
      // 初期化待ち -> 実行可能
      enable_update = mode->completeInitialize();
    }

    if (enable_update && mode)
      mode->update(dt);
  }
};

std::unique_ptr<Implement> impl;
} // namespace

//
// interface
//

//
Context&
Manager::getContext()
{
  return impl->context;
}

// 初期化
void
Manager::setup(SequenceMode sm)
{
  impl = std::move(std::make_unique<Implement>());
  impl->lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::coroutine, sol::lib::string, sol::lib::math,
                           sol::lib::table, sol::lib::debug, sol::lib::bit32);
  impl->request = sm;
}

// 次のモードをリクエスト
void
Manager::requestSequence(SequenceMode ss, bool jump)
{
  impl->request       = ss;
  impl->jump_sequence = jump;
}

// 一つ前のモードに戻る
SequenceMode
Manager::getReturnSequence()
{
  impl->sequence.resize(impl->sequence.size() - 1);
  return impl->getSequence();
}

//
void
Manager::update(float dt)
{
  impl->updateMode(dt);
}
} // namespace Game
