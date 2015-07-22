#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

#define IS_LANDSCAPE false

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
  //set OpenGL context attributions,now can only set six attributions:
  //red,green,blue,alpha,depth,stencil
  GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

  GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  auto director = Director::getInstance();
  auto glview = director->getOpenGLView();
  if(!glview) {
      glview = GLViewImpl::create("FlappyBird");
      director->setOpenGLView(glview);
  }

  // turn on display FPS
  director->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  director->setAnimationInterval(1.0 / 60);

  auto fileUtils  = FileUtils::getInstance();
  auto screenSize = glview->getFrameSize();
  std::vector<std::string> resDirOrders;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
  // check which assets the devices requires
  if (2048 == screenSize.width ||
      2048 == screenSize.height) // retina iPad
  {
    resDirOrders.push_back("ipadhd");
    resDirOrders.push_back("ipad");
    resDirOrders.push_back("iphonehd5");
    resDirOrders.push_back("iphonehd");
    resDirOrders.push_back("iphone");

    if (true == IS_LANDSCAPE)
    {
      glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
    }
    else
    {
      glview->setDesignResolutionSize(1536, 2048, ResolutionPolicy::NO_BORDER);
    }
  }
  else
  if (1024 == screenSize.width ||
      1024 == screenSize.height) // non retina iPad
  {
    resDirOrders.push_back("ipad");
    resDirOrders.push_back("iphonehd5");
    resDirOrders.push_back("iphonehd");
    resDirOrders.push_back("iphone");

    if (true == IS_LANDSCAPE)
    {
      glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
    }
    else
    {
      glview->setDesignResolutionSize(768, 1024, ResolutionPolicy::NO_BORDER);
    }
  }
  else
  if (1136 == screenSize.width ||
      1136 == screenSize.height) // retina iPhone (5 and 5S)
  {
    resDirOrders.push_back("iphonehd5");
    resDirOrders.push_back("iphonehd");
    resDirOrders.push_back("iphone");

    if (true == IS_LANDSCAPE)
    {
      glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
    }
    else
    {
      glview->setDesignResolutionSize(640, 1136, ResolutionPolicy::NO_BORDER);
    }
  }
  else 
  if (960 == screenSize.width ||
      960 == screenSize.height) // retina iPhone (4 and 4S)
  {
    resDirOrders.push_back("iphonehd");
    resDirOrders.push_back("iphone");

    if (true == IS_LANDSCAPE)
    {
      glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
    }
    else
    {
      glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
    }
  }
  else // non retina iPhone and Android devices
  {
    if (1080 <= screenSize.width &&
        1080 <= screenSize.height) // FULL HD android Dvices
    {
      resDirOrders.push_back("ipadhd");
      resDirOrders.push_back("ipad");
      resDirOrders.push_back("iphonehd5");
      resDirOrders.push_back("iphonehd");
      resDirOrders.push_back("iphone");

      if (true == IS_LANDSCAPE)
      {
        glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::NO_BORDER);
      }
      else
      {
        glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::NO_BORDER);
      }
    }
    else
    if (640 < screenSize.width &&
        640 < screenSize.height) // android devices that have a high resolution
    {
      resDirOrders.push_back("iphonehd");
      resDirOrders.push_back("iphone");

      if (true == IS_LANDSCAPE)
      {
        glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
      }
      else
      {
        glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
      }
    }
    else // non retina iPhone and Android devices with lower resolutions
    {
      resDirOrders.push_back("iphone");

      if (true == IS_LANDSCAPE)
      {
        glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
      }
      else
      {
        glview->setDesignResolutionSize(320, 480, ResolutionPolicy::NO_BORDER);
      }
    }
  }
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
  resDirOrders.push_back("iphonehd");
  resDirOrders.push_back("iphone");

  if (true == IS_LANDSCAPE)
  {
    glview->setFrameSize(1280, 720);
    glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::NO_BORDER);
  }
  else
  {
    glview->setFrameSize(640, 960);
    glview->setDesignResolutionSize(640, 960, ResolutionPolicy::NO_BORDER);
  }
#endif

  fileUtils->setSearchPaths(resDirOrders);

  auto scene = CSplashScene::CreateScene();

  // run
  director->runWithScene(scene);

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  Director::getInstance()->stopAnimation();

  // if you use SimpleAudioEngine, it must be pause
  // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
  Director::getInstance()->startAnimation();

  // if you use SimpleAudioEngine, it must resume here
  // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}