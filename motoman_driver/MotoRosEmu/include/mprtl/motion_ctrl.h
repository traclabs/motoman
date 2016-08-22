#ifndef FAKE_MOTOPLUS_MOTION_CTRL_H__
#define FAKE_MOTOPLUS_MOTION_CTRL_H__


#include "mptypes.h"


// Robot Motion Control API ////////////////////////////////////////////////////

#define MP_INC_PULSE_DTYPE 0x80

typedef struct
{
  UCHAR data[8];
  CTRLG_T ei_ctrl_grp;
} MP_POS_TAG;

typedef struct
{
  MP_POS_TAG pos_tag;
  long pos[MP_GRP_AXES_NUM];
} MP_GRP_POS_INFO;

typedef struct
{
  CTRLG_T ctrl_grp;
  CTRLG_T m_ctrl_grp;
  CTRLG_T s_ctrl_grp;
  MP_GRP_POS_INFO grp_pos_info[MP_GRP_NUM];
} MP_EXPOS_DATA;


int mpExRcsIncrementMove(MP_EXPOS_DATA* src_p);


#endif // FAKE_MOTOPLUS_MOTION_CTRL_H__
