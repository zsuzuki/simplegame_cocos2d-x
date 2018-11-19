//
//  TitleMode.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef TitleMode_hpp
#define TitleMode_hpp

#include "mode.h"
#include <cstdint>

namespace Game
{
class TitleMode : public Mode
{
public:
  TitleMode();
  ~TitleMode() override;
  void initialize() override;
  bool completeInitialize() override;
  void finalize() override;
  bool completeFinalize() override;
  void update(float dt) override;
};
} // namespace Game

#endif /* TitleMode_hpp */
