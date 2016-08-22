
#include <mprtl/motion_ctrl.h>

#include <stdio.h>

#include "robot_config.h"


// Robot Motion Control API ////////////////////////////////////////////////////

int mpExRcsIncrementMove(MP_EXPOS_DATA * src_p)
{
  printf("%s:%u:%s: NOT IMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);
  // TODO: update internal fake robot state

  return ERROR;
}
