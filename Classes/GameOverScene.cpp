#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOverScene::CreateScene()
{
  auto scene = Scene::create();

  auto layer = create();

  scene->addChild(layer);

  return scene;
}

bool GameOverScene::Init()
{
  if (!CBaseScene::init())
  {
    return false;
  }

  return true;
}
