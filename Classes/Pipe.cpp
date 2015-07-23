#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

CPipe::CPipe()
{
  m_VisibleSize = GET_SCREEN_SIZE;
  m_Origin      = GET_SCREEN_ORIGIN;
}

void CPipe::SpawnPipe(
    CBaseScene* _Layer
  )
{
  auto TopPipe        = Sprite::create("Pipe.png");
  auto BottomPipe     = Sprite::create("Pipe.png");
  auto FreeSpace      = Node::create();

  auto TopPipeBody    = PhysicsBody::createBox(TopPipe->getContentSize());
  auto BottomPipeBody = PhysicsBody::createBox(BottomPipe->getContentSize());
  auto FreeSpaceBody  = PhysicsBody::createEdgeSegment(Point::ZERO, Point(0.0, Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP));

  TopPipeBody   ->setDynamic(false);
  BottomPipeBody->setDynamic(false);
  FreeSpaceBody ->setDynamic(false);

  TopPipeBody   ->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
  TopPipeBody   ->setContactTestBitmask(true);
  BottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
  BottomPipeBody->setContactTestBitmask(true);
  FreeSpaceBody ->setCollisionBitmask(POINT_COLLISION_BITMASK);
  FreeSpaceBody ->setContactTestBitmask(true);

  TopPipe       ->setPhysicsBody(TopPipeBody);
  BottomPipe    ->setPhysicsBody(BottomPipeBody);
  FreeSpace     ->setPhysicsBody(FreeSpaceBody);

  auto Random = CCRANDOM_0_1();

  if (Random < LOWER_SCREEN_PIPE_THRESHOLD)
    Random = LOWER_SCREEN_PIPE_THRESHOLD;
  else
  if (Random > UPPER_SCREEN_PIPE_THRESHOLD)
    Random = UPPER_SCREEN_PIPE_THRESHOLD;

  auto TopPipeYPos = Random * m_VisibleSize.height + TopPipe->getContentSize().height / 2;

  _Layer->AddChild(
      TopPipe,
      Point(
          m_VisibleSize.width + TopPipe->getContentSize().width + m_Origin.x,
          TopPipeYPos
        )
    );

  _Layer->AddChild(
        BottomPipe,
        Point(
            TopPipe->getPositionX(),
            TopPipeYPos - Sprite::create("Ball.png")->getContentSize().height * PIPE_GAP - TopPipe->getContentSize().height
          )
    );

  _Layer->AddChild(
      FreeSpace,
      Point(
          TopPipe->getPositionX(),
          BottomPipe->getPositionY() + TopPipe->getContentSize().height / 2
        )
    );

  auto Duration         = PIPE_MOVEMENT_SPEED * m_VisibleSize.width;
  auto DeltaPosition    = Point(-m_VisibleSize.width * DELTA_POSITION_FACTOR, 0);
  auto TopPipeAction    = MoveBy::create(Duration, DeltaPosition);
  auto BottomPipeAction = MoveBy::create(Duration, DeltaPosition);
  auto FreeSpaceAction  = MoveBy::create(Duration, DeltaPosition);

  TopPipe   ->runAction(TopPipeAction);
  BottomPipe->runAction(BottomPipeAction);
  FreeSpace ->runAction(FreeSpaceAction);
}