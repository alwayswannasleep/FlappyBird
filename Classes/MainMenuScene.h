#pragma once

#include "BaseScene.h"

class CMainMenuScene : 
  public CBaseScene
{
public: // Interface

  static cocos2d::Scene* CreateScene();

  bool Init() override;

  CREATE_FUNC(CMainMenuScene);

private:

  void GoToGameScene(
      cocos2d::Ref* _Sender
    );
};