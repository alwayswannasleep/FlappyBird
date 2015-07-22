#pragma once

#include "cocos2d.h"

#define DIRECTOR m_Director

class CBaseScene :
  public cocos2d::Layer
{
public: // Interface

  static cocos2d::Scene * CreateScene();

  virtual bool Init();

  CREATE_FUNC(CBaseScene);

public: // Override

  virtual bool init() override;

protected: // Service

  template <
      typename T,
      typename = typename std::enable_if<std::is_base_of<Node, T>::value>::type>
  void AddChild(
      T* _Child
    )
  {
    AddChild(
        _Child,
        cocos2d::Point(
            m_VisibleSize.width / 2 - m_Origin.x,
            m_VisibleSize.height / 2 - m_Origin.y
          )
      );
  }

  template <
    typename T,
    typename = typename std::enable_if<std::is_base_of<Node, T>::value>::type>
  void AddChild(
      T*              _Child,
      cocos2d::Point _Point
    )
  {
    _Child->setPosition(_Point);

    addChild(_Child);
  }

protected: // Members

  cocos2d::Director * m_Director;

  cocos2d::Size       m_VisibleSize;
  cocos2d::Vec2       m_Origin;
};