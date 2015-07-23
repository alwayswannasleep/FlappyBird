#include "BaseScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CBaseScene::CreateScene()
{
  auto scene = Scene::create();

  auto layer = create();

  scene->addChild(layer);

  return scene;
}

bool CBaseScene::Init()
{
  if (!Layer::init())
    return false;

  m_VisibleSize = GET_SCREEN_SIZE;
  m_Origin      = GET_SCREEN_ORIGIN;

  return true;
}

bool CBaseScene::init()
{
  return Init();
}