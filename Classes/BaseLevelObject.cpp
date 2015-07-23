#include "BaseLevelObject.h"
#include "Definitions.h"

CBaseLevelObject::CBaseLevelObject()
{
  m_VisibleSize = GET_SCREEN_SIZE;
  m_Origin      = GET_SCREEN_ORIGIN;
}