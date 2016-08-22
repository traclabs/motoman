#ifndef FAKE_MOTOPLUS_SYSTEM_CTRL_H__
#define FAKE_MOTOPLUS_SYSTEM_CTRL_H__


#include "mptypes.h"


// System Control API //////////////////////////////////////////////////////////

typedef struct
{
  SHORT sServoPower;
  CHAR reserved[2];
} MP_SERVO_POWER_SEND_DATA;

typedef struct
{
  SHORT sServoPower;
  CHAR reserved[2];
} MP_SERVO_POWER_RSP_DATA;

typedef struct
{
  ULONG ulAddr;
  ULONG ulValue;
} MP_IO_DATA;

#define MP_MAX_APP_NAME    32
#define MP_MAX_APP_VERSION 16
#define MP_MAX_APP_COMMENT 32

typedef struct
{
  CHAR AppName[MP_MAX_APP_NAME+4];
  CHAR Version[MP_MAX_APP_VERSION+4];
  CHAR Comment[MP_MAX_APP_COMMENT+4];
  CHAR reserved[36];
} MP_APPINFO_SEND_DATA;

#define MAX_JOB_NAME_LEN (33)
typedef struct
{
  SHORT sTaskNo;
  CHAR cJobName[MAX_JOB_NAME_LEN];
  CHAR reserved[5];
} MP_START_JOB_SEND_DATA;


LONG mpCancelError(MP_STD_RSP_DATA* rData);
int  mpSetAlarm(short alm_code, char *alm_msg, UCHAR sub_code);
LONG mpResetAlarm(MP_STD_RSP_DATA* rData);
LONG mpSetServoPower(MP_SERVO_POWER_SEND_DATA* sData, MP_STD_RSP_DATA* rData);
LONG mpStartJob(MP_START_JOB_SEND_DATA* sData, MP_STD_RSP_DATA* rData);
LONG mpWriteIO(MP_IO_DATA* sData, LONG num);
int  mpApplicationInfoNotify(MP_APPINFO_SEND_DATA* sData, MP_STD_RSP_DATA* rData);


#endif // FAKE_MOTOPLUS_SYSTEM_CTRL_H__
