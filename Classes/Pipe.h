#pragma once

#include "BaseScene.h"

class CPipe
{
public: // Construction/Destruction
  
  CPipe();

public: // Interface

  void SpawnPipe(
      CBaseScene* _Layer
    );

protected:

  cocos2d::Size m_VisibleSize;
  cocos2d::Vec2 m_Origin;
};