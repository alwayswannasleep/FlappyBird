#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

CBird::CBird(
    CBaseScene* _Layer
  ) :
  m_IsFalling(true)
{
  m_FlappyBird        = Sprite::create("Ball.png");
  auto FlappyBirdBody = PhysicsBody::createCircle(m_FlappyBird->getContentSize().width / 2);

  FlappyBirdBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
  FlappyBirdBody->setContactTestBitmask(true);

  m_FlappyBird->setPhysicsBody(FlappyBirdBody);

  m_FlappyBird->setPosition(
    Point(
        m_VisibleSize.width / 2 + m_Origin.x,
        m_VisibleSize.height / 2 + m_Origin.y
      ));

  _Layer->addChild(m_FlappyBird, 100);
}

void CBird::ProcessFly(
    float _DeltaTime
  )
{
  if (m_IsFalling)
    m_FlappyBird->setPositionY(m_FlappyBird->getPositionY() - BIRD_FLYING_SPEED * _DeltaTime);
  else
    m_FlappyBird->setPositionY(m_FlappyBird->getPositionY() + BIRD_FLYING_SPEED * _DeltaTime);
}