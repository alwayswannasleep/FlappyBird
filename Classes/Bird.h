#pragma once

#include "BaseLevelObject.h"
#include "BaseScene.h"

class CBird :
  public CBaseLevelObject
{
public: // Construction/Destruction

  explicit CBird(
      CBaseScene* _Layer
    );

  void ProcessFly(
      float _DeltaTime
    );

  void StartFlying()
  {
    m_IsFalling = false;
  }

  void StopFlying()
  {
    m_IsFalling = true;
  }
  
protected:

  cocos2d::Sprite* m_FlappyBird;

  bool             m_IsFalling;
};