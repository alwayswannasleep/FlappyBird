#pragma once

#include "BaseScene.h"

class GameOverScene :
  public CBaseScene
{
public:

  static cocos2d::Scene* CreateScene();

  bool Init() override;

  // implement the "static create()" method manually
  CREATE_FUNC(GameOverScene);
};