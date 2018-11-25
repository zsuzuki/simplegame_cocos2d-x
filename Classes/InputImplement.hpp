//
//  InputImplement.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/23.
//

#ifndef InputImplement_hpp
#define InputImplement_hpp

#include "Game/system/InputInterface.hpp"
#include "cocos2d.h"
#include <chrono>
#include <vector>

class GameInput : public Game::InputInterface
{
  struct InTouch : public Game::InputInterface::Touch
  {
    using time = std::chrono::steady_clock::time_point;
    time start{};
    time last{};
    bool still          = false;
    int  target_switch  = -1;
    int  target_analog0 = -1;
    int  target_analog1 = -1;
  };

  std::vector<bool>    prev_switch_list;
  std::vector<bool>    switch_list;
  std::vector<float>   analog_list;
  std::vector<InTouch> touch_list;
  bool                 valid;

public:
  GameInput();
  ~GameInput() override;
  // 更新
  void preUpdate(float dt) override;
  void postUpdate() override;
  bool isValid() const override;
  // 必要なスイッチ数を提示して、実際に確保できるスイッチ数を返す
  std::pair<int, int> requestNeedChannel(int nb_sw, int nb_ana) override;
  // 取得
  bool         getSwitch(int id) const override;
  bool         getSwitchOn(int id) const override;
  float        getAnalog(int id) const override;
  const Touch& getTouch(int id) const override;
  size_t       getNbTouch() const override;

  // 有効化
  void setValid(bool v) { valid = v; }
  // 各スイッチのマッピングリストを渡す
  bool setSwitchMap(std::vector<int> map_list);

  // タッチ入力
  void beginTouch(cocos2d::Touch& t);
  void moveTouch(cocos2d::Touch& t);
  void endTouch(cocos2d::Touch& t);

  void clear();
};

//
class GameInputManager : public Game::InputManager
{
  std::vector<GameInput> input;
  ActivateFunction       active_func;

public:
  GameInputManager() { input.reserve(4); }
  ~GameInputManager() = default;

  void setActivateFunction(ActivateFunction af) override { active_func = af; }

  void preUpdate(float dt) override;
  void postUpdate() override;

  size_t     getNbInput() override;
  GameInput* getInput(int ch) override;

  void changeScene();
};

#endif /* InputImplement_hpp */
