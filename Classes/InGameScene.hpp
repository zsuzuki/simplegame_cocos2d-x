//
//  InGameScene.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/19.
//

#ifndef InGameScene_hpp
#define InGameScene_hpp

#include "cocos2d.h"

class InGameScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();

  bool init() override;
  void update(float dt) override;
  void onEnter() override;
  void onExit() override;

  CREATE_FUNC(InGameScene);
};

#endif /* InGameScene_hpp */
