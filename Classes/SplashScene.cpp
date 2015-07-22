#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CSplashScene::CreateScene()
{
  auto scene = Scene::create();

  auto layer = create();

  scene->addChild(layer);

  return scene;
}

bool CSplashScene::Init()
{
  if (!CBaseScene::Init())
  {
    return false;
  }

  scheduleOnce(schedule_selector(CSplashScene::GoToMainMenuScene), SPLASH_SCENE_DISPLAY_TIME);

  AddChild(Sprite::create("Splash Screen.png"));

  return true;
}

void CSplashScene::GoToMainMenuScene(
    float _DeltaTime
  )
{
  auto scene = CMainMenuScene::CreateScene();

  DIRECTOR->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}