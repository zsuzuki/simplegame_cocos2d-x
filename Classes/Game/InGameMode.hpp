//
//  InGameMode.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef InGameMode_hpp
#define InGameMode_hpp

#include "mode.h"
#include <cstdint>

namespace Game
{
class InGameMode : public Mode
{
public:
  InGameMode();
  ~InGameMode() override;
  void initialize() override;
  bool completeInitialize() override;
  void finalize() override;
  bool completeFinalize() override;
  void update(float dt) override;
};
} // namespace Game

#endif /* InGameMode_hpp */
