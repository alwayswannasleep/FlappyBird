#pragma once

#include "BaseScene.h"

class CSplashScene :
  public CBaseScene
{
public:

  static cocos2d::Scene* CreateScene();

  bool Init() override;

  CREATE_FUNC(CSplashScene);

private:

  void GoToMainMenuScene(
      float _DeltaTime
    );
};