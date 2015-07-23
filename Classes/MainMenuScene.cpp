#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CMainMenuScene::CreateScene()
{
  auto scene = Scene::create();

  auto layer = create();

  scene->addChild(layer);

  return scene;
}

bool CMainMenuScene::Init()
{
  if (!CBaseScene::Init())
  {
    return false;
  }

  AddChild(Sprite::create("Background.png"));

  auto Title = Sprite::create("Title.png");

  Title->setPosition(
    Point(
        m_VisibleSize.width / 2 + m_Origin.x,
        m_VisibleSize.height + m_Origin.y - Title->getContentSize().height / 2
      )
    );

  addChild(Title);

  auto PlayButton = MenuItemImage::create(
      "Play Button.png",
      "Play Button Clicked.png",
      CC_CALLBACK_1(CMainMenuScene::GoToGameScene, this)
    );

  auto MainMenu = Menu::create(PlayButton, NULL);

  AddChild(MainMenu);

  return true;
}

void CMainMenuScene::GoToGameScene(
    Ref* _Sender
  )
{
  auto scene = CGameScene::CreateScene();

  GET_DIRECTOR->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}