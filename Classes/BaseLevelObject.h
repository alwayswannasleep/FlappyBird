#pragma once

#include "cocos2d.h"

class CBaseLevelObject
{
public: // Construction/Destruction

  CBaseLevelObject();

protected: // Members

  cocos2d::Size m_VisibleSize;
  cocos2d::Vec2 m_Origin;
};