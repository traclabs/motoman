#ifndef FAKE_MOTOPLUS_CONSTANTS_H__
#define FAKE_MOTOPLUS_CONSTANTS_H__


// MotoPlus constants //////////////////////////////////////////////////////////

// from VxWorks
#define FALSE  0
#define TRUE   (!FALSE)

#define OK     0
#define ERROR -1


// misc others
#define MP_GRP_NUM      32 // TODO (from mpManualMOV doc)
#define MAX_PULSE_AXES   8 // TODO (from mpGetPulsePos doc)
#define MP_GRP_AXES_NUM  8 // TODO (from mpGetUserVars doc)

// TODO: made up value!
#define MP_INTERPOLATION_CLK 2

// TODO: guessed based on comment in mpUsrRoot(..)!
#define MP_MS_PER_TICK 1


#endif // FAKE_MOTOPLUS_CONSTANTS_H__
