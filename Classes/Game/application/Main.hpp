//
//  Main.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/25.
//

#ifndef Main_hpp
#define Main_hpp

#include "../mode.h"
#include <cstdint>

namespace Game
{
// アプリケーションのセットアップモード
class SetupMode : public Mode
{
public:
  SetupMode();
  ~SetupMode() override;
  void initialize() override;
  bool completeInitialize() override;
  void finalize() override;
  bool completeFinalize() override;
  void update(float dt) override;
};
} // namespace Game

#endif /* Main_hpp */
