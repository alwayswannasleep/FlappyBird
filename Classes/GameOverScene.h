#pragma once

#include "BaseScene.h"

class CGameOverScene :
  public CBaseScene
{
public:

  static cocos2d::Scene* CreateScene();

  bool Init() override;

  CREATE_FUNC(CGameOverScene);
};