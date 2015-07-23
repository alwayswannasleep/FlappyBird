#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* CGameScene::CreateScene()
{
  auto Scene        = Scene::createWithPhysics();
  auto PhysicsWorld = Scene->getPhysicsWorld();
  PhysicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
  PhysicsWorld->setGravity(Vec2::ZERO);

  auto Layer = create();
  Layer->SetPhysicsWorld(PhysicsWorld);

  Scene->addChild(Layer);

  return Scene;
}

bool CGameScene::Init()
{
  if (!CBaseScene::Init())
  {
    return false;
  }

  AddChild(Sprite::create("Background.png"));

  auto EdgeBody = PhysicsBody::createEdgeBox(
      m_VisibleSize, 
      PHYSICSBODY_MATERIAL_DEFAULT, 
      EDGE_BOX_BORDER_SIZE
    );

  EdgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
  EdgeBody->setContactTestBitmask(true);

  auto EdgeNode = Node::create();
  EdgeNode->setPhysicsBody(EdgeBody);

  AddChild(EdgeNode);

  m_Bird = new CBird(this);

  schedule(schedule_selector(CGameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY);
  scheduleUpdate();

  auto ContactListener            = EventListenerPhysicsContact::create();
  ContactListener->onContactBegin = CC_CALLBACK_1(CGameScene::OnContactBegin, this);

  auto EventListener          = EventListenerTouchOneByOne::create();
  EventListener->onTouchBegan = CC_CALLBACK_2(CGameScene::onTouchBegan, this);

  GET_DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(EventListener, this);
  GET_DIRECTOR->getEventDispatcher()->addEventListenerWithSceneGraphPriority(ContactListener, this);

  m_CounterText = "Scores: ";
  m_Points      = 0;

  m_ScoresLabel = Label::createWithSystemFont(
      String::createWithFormat("%s %i", m_CounterText, m_Points)->_string,
      "Marker Felt.ttf",
      m_VisibleSize.height * FONT_SIZE_SCALE
    );

  m_ScoresLabel->setPosition(
      m_VisibleSize.width + m_Origin.x - m_ScoresLabel->getContentSize().width,
      m_VisibleSize.height + m_Origin.y - m_ScoresLabel->getContentSize().height
    );

  m_ScoresLabel->enableOutline(Color4B::BLACK);
  m_ScoresLabel->enableShadow();

  addChild(m_ScoresLabel, 1000);

  return true;
}

void CGameScene::update(
    float _DeltaTime
  )
{
  m_Bird->ProcessFly(_DeltaTime);
}

void CGameScene::SpawnPipe(
    float _DeltaTime
  )
{
  m_Pipe.SpawnPipe(this);
}

bool CGameScene::OnContactBegin(
    PhysicsContact& _Content
  )
{
  auto A = _Content.getShapeA()->getBody();
  auto B = _Content.getShapeB()->getBody();

  if (A->getCollisionBitmask() == BIRD_COLLISION_BITMASK     &&
      B->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK ||
      A->getCollisionBitmask() == OBSTACLE_COLLISION_BITMASK &&
      B->getCollisionBitmask() == BIRD_COLLISION_BITMASK)
  {
    auto Scene = CGameOverScene::CreateScene();

    GET_DIRECTOR->replaceScene(TransitionFade::create(TRANSITION_TIME, Scene));

    return true;
  }
  else
  if (A->getCollisionBitmask() == BIRD_COLLISION_BITMASK  &&
      B->getCollisionBitmask() == POINT_COLLISION_BITMASK ||
      A->getCollisionBitmask() == POINT_COLLISION_BITMASK &&
      B->getCollisionBitmask() == BIRD_COLLISION_BITMASK)
  {
    OnPointsIncrease();

    return true;
  }

  return false;
}

bool CGameScene::onTouchBegan(
    Touch* _Touch,
    Event* _Event
  )
{
  unschedule(CC_SCHEDULE_SELECTOR(CGameScene::StopFlying));

  StopFlying(0.0);

  m_Bird->StartFlying();

  scheduleOnce(CC_SCHEDULE_SELECTOR(CGameScene::StopFlying), BIRD_FLYING_DURATION);

  return true;
}

void CGameScene::StopFlying(
    float _DeltaTime
  )
{
  m_Bird->StopFlying();
}

void CGameScene::OnPointsIncrease()
{
  m_Points++;

  m_ScoresLabel->setString(String::createWithFormat("%s %i", m_CounterText, m_Points)->getCString());
}