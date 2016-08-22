
#include <mprtl/system_mon.h>

#include <stdio.h>

#include "robot_config.h"


// System Monitor API //////////////////////////////////////////////////////////

int mpCtrlGrpId2GrpNo(MP_GRP_ID_TYPE grp_id)
{
  printf("%s:%u:%s: NOT IMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);

  switch (grp_id)
  {
    default:
      return 0;
  }

  return ERROR;
}


LONG mpReadIO(MP_IO_INFO* sData, USHORT* rData, LONG num)
{
  // TODO: maybe come up with a better emulation of this?

  // TODO: this is also used for reading controller status IO signals. Switch
  //       on ulAddr and return suitable values for them

  int i;

  if (num > 1)
  {
    for (i = 0; i < num; ++i)
      rData[i] = 0;

    //printf("mpReadIO: %d->%d: all 0\n", sData->ulAddr, sData->ulAddr + num);
    return OK;
  }

  switch (sData->ulAddr)
  {
    default:
      *rData = 0;
  }

  //printf("mpReadIO: %d: %d\n", sData->ulAddr, *rData);

  return 0;
}


LONG mpGetAlarmCode(MP_ALARM_CODE_RSP_DATA* rData)
{
  // never any errors
  rData->usErrorNo = 0;
  rData->usErrorData = 0;
  rData->usAlarmNum = 0;

  return 0;
}


// retrieves the commanded position
LONG mpGetPulsePos(MP_CTRL_GRP_SEND_DATA* sData, MP_PULSE_POS_RSP_DATA* rData)
{
  int i;

  // TODO: this makes the commanded position ALWAYS 0 --> all groups
  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    rData->lPos[i] = 0;

  return 0;
}


// retrieves the actual current position
LONG mpGetFBPulsePos(MP_CTRL_GRP_SEND_DATA* sData, MP_FB_PULSE_POS_RSP_DATA* rData)
{
  int i;

  // robot is ALWAYS at 0 pos ---> all groups
  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    rData->lPos[i] = 0;

  return 0;
}
