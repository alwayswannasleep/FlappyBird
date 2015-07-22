#include "BaseScene.h"

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

  DIRECTOR      = Director::getInstance();
  m_VisibleSize = DIRECTOR->getVisibleSize();
  m_Origin      = DIRECTOR->getVisibleOrigin();

  return true;
}

bool CBaseScene::init()
{
  return Init();
}