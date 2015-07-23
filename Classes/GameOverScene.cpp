#include "GameOverScene.h"

USING_NS_CC;

Scene* CGameOverScene::CreateScene()
{
  auto scene = Scene::create();

  auto layer = create();

  scene->addChild(layer);

  return scene;
}

bool CGameOverScene::Init()
{
  if (!CBaseScene::Init())
  {
    return false;
  }

  return true;
}
