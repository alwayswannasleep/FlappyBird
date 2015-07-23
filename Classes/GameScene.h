#pragma once

#include "BaseScene.h"
#include "Pipe.h"

class CGameScene :
  public CBaseScene
{
public: // Constants

  const float EDGE_BOX_BORDER_SIZE = 3;

public: // Interface

  static cocos2d::Scene* CreateScene();

    bool Init() override;

    CREATE_FUNC(CGameScene);

protected: // Service

  void SetPhysicsWorld(
      cocos2d::PhysicsWorld* _World
    )
  {
    m_SceneWorld = _World;
  }

  void SpawnPipe(
      float _DeltaTime
    );

protected: // Members

  cocos2d::PhysicsWorld* m_SceneWorld;

  CPipe                  m_Pipe;
};