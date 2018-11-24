//
//  InputInterface.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/23.
//

#ifndef InputInterface_hpp
#define InputInterface_hpp

#include <cstdint>
#include <functional>
#include <utility>

namespace Game
{

//
class InputInterface
{
public:
  struct Touch
  {
    float x, y;
    float mx, my;
    float dt;
  };

  InputInterface()          = default;
  virtual ~InputInterface() = default;
  // 更新
  virtual void preUpdate(float dt) = 0;
  virtual void postUpdate()        = 0;
  virtual bool isValid() const     = 0;
  // 必要なスイッチ数を提示して、実際に確保できるスイッチ数を返す
  virtual std::pair<int, int> requestNeedChannel(int nb_sw, int nb_ana) = 0;
  // 取得
  virtual bool         getSwitch(int id) const   = 0;
  virtual bool         getSwitchOn(int id) const = 0;
  virtual float        getAnalog(int id) const   = 0;
  virtual const Touch& getTouch(int id) const    = 0;
  virtual size_t       getNbTouch() const        = 0;
};

//
class InputManager
{
public:
  // デバイス接続時のコールバック
  // arg<int>: デバイスID(アプリケーションで決める=ハードウェアの何らかのIDを直接表す物ではない)
  // return: true=そのデバイスは有効化される
  using ActivateFunction = std::function<bool(int)>;

  InputManager()          = default;
  virtual ~InputManager() = default;

  virtual void setActivateFunction(ActivateFunction af) = 0;

  virtual void preUpdate(float dt) = 0;
  virtual void postUpdate()        = 0;

  virtual size_t          getNbInput()     = 0;
  virtual InputInterface& getInput(int ch) = 0;
};
} // namespace Game

#endif /* InputInterface_hpp */
