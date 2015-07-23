#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CGameScene::CreateScene()
{
  auto Scene        = Scene::createWithPhysics();
  auto PhysicsWorld = Scene->getPhysicsWorld();
  PhysicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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

  auto EdgeNode = Node::create();
  EdgeNode->setPhysicsBody(EdgeBody);

  AddChild(EdgeNode);

  schedule(schedule_selector(CGameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY);

  return true;
}

void CGameScene::SpawnPipe(
    float _DeltaTime
  )
{
  m_Pipe.SpawnPipe(this);
}