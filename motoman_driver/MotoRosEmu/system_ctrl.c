
#include <mprtl/system_ctrl.h>

#include <stdio.h>


// System Control API //////////////////////////////////////////////////////////

int mpSetAlarm(short alm_code, char *alm_msg, UCHAR sub_code)
{
  // according to docs
  if ((alm_code > 8999) || (alm_code < 8000))
    return ERROR;

  printf("mpSetAlarm: '%s' (%d:%d)\n", alm_msg, alm_code, sub_code);

  // TODO: update internal fake robot state

  return OK;
}


LONG mpResetAlarm(MP_STD_RSP_DATA* rData)
{
  // TODO: update internal fake robot state

  rData->err_no = 0x0000; // 'normal end' according to docs

  return OK;
}


LONG mpWriteIO(MP_IO_DATA* sData, LONG num)
{
  printf("mpWriteIO: %d: %d\n", sData->ulAddr, sData->ulValue);
  // TODO: update internal fake robot state

  // TODO: this is also used for writing controller status IO signals. Switch
  //       on ulAddr and store incoming values for them

  return OK;
}


LONG mpCancelError(MP_STD_RSP_DATA* rData)
{
  printf("%s:%u:%s: NOT IMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);
  // TODO: update internal fake robot state
  return ERROR;
}


LONG mpSetServoPower(MP_SERVO_POWER_SEND_DATA* sData, MP_STD_RSP_DATA* rData)
{
  // TODO: update internal fake robot state
  printf("mpSetServoPower: %d\n", sData->sServoPower);

  //0x0000 Normal end
  //0x2060 In error/alarm status
  //0x3450 Failed (Unable to turn servo on)

  rData->err_no = 0x0000;

  return OK;
}


LONG mpStartJob(MP_START_JOB_SEND_DATA* sData, MP_STD_RSP_DATA* rData)
{
  printf("mpStartJob: taskno: %d, jobname: '%s'\n", sData->sTaskNo, sData->cJobName);

  // TODO: check for NULL in 'sData->cJobName': should 'resume' current job

  // 0x0000 Normal end
  rData->err_no = 0x0000;

  return OK;
}


int mpApplicationInfoNotify(MP_APPINFO_SEND_DATA* sData, MP_STD_RSP_DATA* rData)
{
  printf("%s: '%s', '%s', '%s'\n", __FUNCTION__, sData->AppName, sData->Version, sData->Comment);
  rData->err_no = 0x0000; // Normal end
  return OK;
}
