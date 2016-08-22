
#include <ParameterExtraction.h>

#include <mprtl/mptypes.h>


#include "robot_config.h"




int GP_getNumberOfGroups()
{
  return FAKE_ROBOT_NUM_GROUPS;
}


/******************************************************************************/
/* << 3 >>                                                              	  */
/* Function name : int  GP_getNumberOfAxes()								  */
/* Functionality : Retrieves the Number of Axes								  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/* Return value	 : Success = Number of Axes									  */
/*				 : Failure = -1												  */
/******************************************************************************/
int GP_getNumberOfAxes(int ctrlGrp)
{
  // TODO: return error if not the correct control group
  return FAKE_ROBOT_NUM_AXES_GRP_1;
}


/******************************************************************************/
/* << 4 >>                                                              	  */
/* Function name : STATUS GP_getPulseToRad()								  */
/* Functionality : Gets the Pulse to radians conversion factors				  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/*				   GB_PULSE_TO_RAD *PulseToRad -array of conversion data [OUT]*/
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS  GP_getPulseToRad(int ctrlGrp, PULSE_TO_RAD *PulseToRad)
{
  int i;

  // TODO: return error if not the correct control group

  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    PulseToRad->PtoR[i] = FAKE_ROBOT_PULSE_TO_RAD;

  return 0;
}


/******************************************************************************/
/* << 11 >>                                                             	  */
/* Function name : STATUS GetFBPulseCorrection()							  */
/* Functionality : Get all the pulse correction data for required axes		  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data [IN]			  */
/*				   FB_PULSE_CORRECTION_DATA * correctionData[OUT]			  */
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getFBPulseCorrection(int ctrlGrp, FB_PULSE_CORRECTION_DATA *correctionData)
{
  int i;

  // TODO: return error if not the correct control group

  // we fake a robot that has no axes linked, so none of the correctionData
  // members are valid
  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
  {
    correctionData->correction[i].bValid = FALSE;
    correctionData->correction[i].fCorrectionRatio = 0;
    correctionData->correction[i].ulCorrectionAxis = 0;
    correctionData->correction[i].ulSourceAxis = 0;
  }

  return 0;
}


/******************************************************************************/
/* << 12 >>                                                             	  */
/* Function name : STATUS GP_getQtyOfAllowedTasks()							  */
/* Functionality : No.of MotoPlus tasks that can be started concurrently  	  */
/* Parameter	 : TASK_QTY_INFO *taskInfo [OUT]				  			  */
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getQtyOfAllowedTasks(TASK_QTY_INFO *taskInfo)
{
  taskInfo->qtyOfHighPriorityTasks = FAKE_ROBOT_MAX_NUM_TASKS_PRIO_HIGH;
  taskInfo->qtyOfNormalPriorityTasks = FAKE_ROBOT_MAX_NUM_TASKS_PRIO_NORMAL;

  // TODO: made up value (is this even used in this application?)
  taskInfo->qtyOfOutFiles = 0;

  return 0;
}


/******************************************************************************/
/* << 13 >>                                                             	  */
/* Function name : STATUS GP_getInterpolationPeriod()						  */
/* Functionality : No.of millisecs b/w each tick of the interpolation-clock	  */
/* Parameter	 : UINT16 *periodInMilliseconds [OUT]						  */
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getInterpolationPeriod(UINT16* periodInMilliseconds)
{
  *periodInMilliseconds = FAKE_ROBOT_INTERPOLATION_PERIOD;
  return 0;
}


/******************************************************************************/
/* << 14 >>                                                             	  */
/* Function name : STATUS GP_getMaxIncPerIpCycle()							  */
/* Functionality : Max increment the arm is capable of(limited by governor)	  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data [IN]			  */
/*				   int interpolationPeriodInMilliseconds - obtained from GP_getInterpolationPeriod [IN] */
/*				   MAX_INCREMENT_INFO *mip [OUT]	   		 				  */
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getMaxIncPerIpCycle(int ctrlGrp, int interpolationPeriodInMilliseconds, MAX_INCREMENT_INFO *mip)
{
  int i;

  // TODO: return error if not the correct control group

  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    mip->maxIncrement[i] = FAKE_ROBOT_MAX_INC_PER_CYCLE;

  return 0;
}


/******************************************************************************/
/* << 15 >>                                                             	  */
/* Function name : GP_getGovForIncMotion()									  */
/* Functionality : Percentage Limit of the max-increment					  */
/* Parameter	 : int ctrlGrp 				[IN]			  				  */
/* Return value	 : Success = percentage limit Of MaxSpeed					  */
/*				 : Failure = -1												  */
/******************************************************************************/
float GP_getGovForIncMotion(int ctrlGrp)
{
  // TODO: return error if not the correct control group
  return FAKE_ROBOT_GOV_FOR_INC_MOTION;
}


/******************************************************************************/
/* << 16 >>                                                              	  */
/* Function name : STATUS GP_getJointPulseLimits()							  */
/* Functionality : Gets the Pulse to radians conversion factors				  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/*				   GB_PULSE_TO_RAD *PulseToRad -array of conversion data [OUT]*/
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getJointPulseLimits(int ctrlGrp, JOINT_PULSE_LIMITS* jointPulseLimits)
{
  printf("%s:%u:%s: NOT IMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);
  return -1;
}


/******************************************************************************/
/* << 17 >>                                                              	  */
/* Function name : STATUS GP_getJointVelocityLimits()						  */
/* Functionality : Gets the velocity limit for each joint					  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/*				   JOINT_ANGULAR_VELOCITY_LIMITS *GP_getJointAngularVelocityLimits (deg/sec) [OUT]*/
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getJointAngularVelocityLimits(int ctrlGrp, JOINT_ANGULAR_VELOCITY_LIMITS* jointVelocityLimits)
{
  printf("%s:%u:%s: NOT IMPLEMENTED!\n", __FILE__, __LINE__, __FUNCTION__);
  return -1;
}


/******************************************************************************/
/* << 18 >>                                                              	  */
/* Function name : STATUS GP_getAxisMotionType()							  */
/* Functionality : Gets the motion type of each axis in the group			  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/*				   AXIS_MOTION_TYPE *axisType -array of data [OUT]			  */
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getAxisMotionType(int ctrlGrp, AXIS_MOTION_TYPE* axisType)
{
  int i;

  // TODO: return error if not the correct control group

  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    axisType->type[i] = ROTATION_AXIS;

  return 0;
}


/******************************************************************************/
/* << 19 >>                                                              	  */
/* Function name : STATUS GP_getPulseToMeter()								  */
/* Functionality : Gets the Pulse to meter conversion factors				  */
/* Parameter	 : int ctrlGrp - Robot control to fetch data	[IN]		  */
/*				   PULSE_TO_METER *PulseToMeter -array of conversion data [OUT]*/
/* Return value	 : Success = OK 											  */
/*				 : Failure = NG												  */
/******************************************************************************/
STATUS GP_getPulseToMeter(int ctrlGrp, PULSE_TO_METER* PulseToMeter)
{
  int i;

  // TODO: return error if not the correct control group

  for (i = 0; i < FAKE_ROBOT_NUM_AXES_GRP_1; ++i)
    PulseToMeter->PtoM[i] = FAKE_ROBOT_PULSE_TO_METER;

  return 0;
}
