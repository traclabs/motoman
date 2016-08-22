#ifndef FAKE_MOTOPLUS_SYSTEM_MON_H__
#define FAKE_MOTOPLUS_SYSTEM_MON_H__


#include "mptypes.h"


// System Monitor API //////////////////////////////////////////////////////////

typedef struct
{
  CTRLG_T sCtrlGrp;
} MP_CTRL_GRP_SEND_DATA;

typedef struct
{
  LONG lPos[MAX_PULSE_AXES];
} MP_PULSE_POS_RSP_DATA;

typedef struct
{
  LONG lPos[MAX_PULSE_AXES];
} MP_FB_PULSE_POS_RSP_DATA;

typedef int MP_GRP_ID_TYPE;

#define MAX_ALARM_COUNT (4)
typedef struct
{
  USHORT usAlarmNo[MAX_ALARM_COUNT];
  USHORT usAlarmData[MAX_ALARM_COUNT];
} MP_ALARM_DATA;

typedef struct
{
  USHORT usErrorNo;
  USHORT usErrorData;
  USHORT usAlarmNum;
  CHAR reserved[2];
  MP_ALARM_DATA AlarmData;
} MP_ALARM_CODE_RSP_DATA;


typedef struct
{
  ULONG ulAddr;
} MP_IO_INFO;


// TODO: these values are guesses
#define MP_R1_GID  0
#define MP_R2_GID  1
#define MP_R4_GID  3

#define MP_B1_GID  8
#define MP_B2_GID  9

#define MP_S1_GID 16
#define MP_S2_GID 17

#define MP_S3_GID 19


int  mpCtrlGrpId2GrpNo(MP_GRP_ID_TYPE grp_id);
LONG mpGetAlarmCode(MP_ALARM_CODE_RSP_DATA* rData);
LONG mpGetPulsePos(MP_CTRL_GRP_SEND_DATA* sData, MP_PULSE_POS_RSP_DATA* rData);
LONG mpGetFBPulsePos(MP_CTRL_GRP_SEND_DATA* sData, MP_FB_PULSE_POS_RSP_DATA* rData);
LONG mpReadIO(MP_IO_INFO* sData, USHORT* rData, LONG num);


#endif // FAKE_MOTOPLUS_SYSTEM_MON_H__
