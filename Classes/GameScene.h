#pragma once

#include "BaseScene.h"
#include "Pipe.h"
#include "Bird.h"

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

  void update(
      float _DeltaTime
    ) override;

  void SetPhysicsWorld(
      cocos2d::PhysicsWorld* _World
    )
  {
    m_SceneWorld = _World;
  }

  void SpawnPipe(
      float _DeltaTime
    );

  bool OnContactBegin(
      cocos2d::PhysicsContact& _Content
    );

  bool onTouchBegan(
      cocos2d::Touch* _Touch,
      cocos2d::Event* _Event
    ) override;

  void StopFlying(
      float _DeltaTime
    );

  void OnPointsIncrease();

protected: // Members

  cocos2d::PhysicsWorld* m_SceneWorld;

  const char *           m_CounterText;
  int                    m_Points;

  cocos2d::Label*        m_ScoresLabel;

  CBird*                 m_Bird;
  CPipe                  m_Pipe;
};