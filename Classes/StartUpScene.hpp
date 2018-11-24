//
//  StartUpScene.hpp
//  simplegame
//
//  Created by 鈴木良則 on 2018/11/25.
//

#ifndef StartUpScene_hpp
#define StartUpScene_hpp

#include "cocos2d.h"

class StartUpScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();

  bool init() override;
  void update(float dt) override;
  void onEnter() override;
  void onExit() override;
  void onEnterTransitionDidFinish() override;
  void onExitTransitionDidStart() override;

  CREATE_FUNC(StartUpScene);
};

#endif /* StartUpScene_hpp */
