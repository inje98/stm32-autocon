/*
 * File: Lws_HilsCtrl_240218_v_1_0.h
 *
 * Code generated for Simulink model 'Lws_HilsCtrl_240218_v_1_0'.
 *
 * Model version                  : 1.0.9
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Jun 17 14:47:57 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_h_
#define RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_h_
#include <string.h>
#ifndef Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_
#define Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                          /* Lws_HilsCtrl_240218_v_1_0_COMMON_INCLUDES_ */

#include "Lws_HilsCtrl_240218_v_1_0_types.h"

/* Child system includes */
#include "Lws_HilsCtrl.h"

/* Macros for accessing real-time model data structure */

/* Block signals (default storage) */
typedef struct
{
  real32_T Pressure_WinchPwBase;       /* 'Hils_SequenceCtrl' (':5237') */
  real32_T OilFlow_DropLift;           /* 'Hils_SequenceCtrl' (':5237') */
  real32_T Pressure_DropLiftPw;        /* 'Hils_SequenceCtrl' (':5237') */
  real32_T DataStoreRead2_o1;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o2;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o3;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o4;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o5;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o6;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o7;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o8;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o9;          /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o10;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o11;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o12;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o13;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o14;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o15;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o16;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o17;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o18;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o19;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o20;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o21;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o22;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o23;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o24;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o25;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o26;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead2_o27;         /* 'Data Store Read2' (':5036') */
  real32_T DataStoreRead8_o1;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o2;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o3;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o4;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o5;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o6;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o7;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o8;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o9;          /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o10;         /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o11;         /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o12;         /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o13;         /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o14;         /* 'Data Store Read8' (':5042') */
  real32_T DataStoreRead8_o15;         /* 'Data Store Read8' (':5042') */
  uint16_T DataStoreRead1_o1;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o2;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o3;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o4;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o5;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o6;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o7;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o8;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o9;          /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o10;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o11;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o12;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o13;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o14;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o15;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o16;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o17;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o18;         /* 'Data Store Read1' (':5032') */
  uint16_T DataStoreRead1_o19;         /* 'Data Store Read1' (':5032') */
}
B_Lws_HilsCtrl_240218_v_1_0_T;

/* Block states (default storage) for system 'Lws_HilsCtrl_240218_v_1_0' */
typedef struct
{
  Ao_i HilsAO;                         /* 'Data Store Memory15' (':2228') */
  Hils_Para_i HilsPara;                /* 'Data Store Memory8' (':257') */
  Hils_DataMon_i HilsMon;              /* 'Data Store Memory12' (':2902') */
  Do_i HilsDO;                         /* 'Data Store Memory1' (':218') */
  Ui_OutSet_i HilsOutSet;              /* 'Data Store Memory4' (':231') */
  Ai_i HilsAI;                         /* 'Data Store Memory14' (':2227') */
  Hils_Alarm_i HilsAlarm;              /* 'Data Store Memory2' (':2893') */
  Hils_Error_i HilsError;              /* 'Data Store Memory5' (':232') */
  Hils_Status_i HilsStatus;            /* 'Data Store Memory6' (':233') */
  Di_i HilsDI;                         /* 'Data Store Memory' (':173') */
  real_T DiscreteTransferFcn_states;   /* 'Discrete Transfer Fcn' (':6389:2') */
  real_T DiscreteTimeIntegrator2_DSTATE;
                                     /* 'Discrete-Time Integrator2' (':6364') */
  real_T DiscreteTransferFcn_states_g; /* 'Discrete Transfer Fcn' (':6457:2') */
  real_T DiscreteTimeIntegrator1_DSTATE;
                                     /* 'Discrete-Time Integrator1' (':6434') */
  real_T DiscreteTransferFcn_states_o; /* 'Discrete Transfer Fcn' (':6388:2') */
  real_T DiscreteTransferFcn_states_a; /* 'Discrete Transfer Fcn' (':6387:2') */
  real_T DiscreteTransferFcn_states_i; /* 'Discrete Transfer Fcn' (':6456:2') */
  real_T DiscreteTransferFcn_states_g1;/* 'Discrete Transfer Fcn' (':6411:2') */
  real_T DiscreteTransferFcn_states_id;/* 'Discrete Transfer Fcn' (':5851:2') */
  real_T DiscreteTransferFcn_states_e; /* 'Discrete Transfer Fcn' (':6809:2') */
  real_T DiscreteTimeIntegrator_DSTATE;
                                      /* 'Discrete-Time Integrator' (':6780') */
  real_T DiscreteTransferFcn_states_d; /* 'Discrete Transfer Fcn' (':5909:2') */
  real_T DiscreteTransferFcn_states_k; /* 'Discrete Transfer Fcn' (':6810:2') */
  real_T DiscreteTimeIntegrator1_DSTAT_e;
                                     /* 'Discrete-Time Integrator1' (':6781') */
  real_T DiscreteTransferFcn_states_n; /* 'Discrete Transfer Fcn' (':5875:2') */
  real_T DiscreteTransferFcn_states_ip;/* 'Discrete Transfer Fcn' (':6719:2') */
  real_T DiscreteTimeIntegrator_DSTATE_c;
                                      /* 'Discrete-Time Integrator' (':6690') */
  real_T DiscreteTransferFcn_states_m; /* 'Discrete Transfer Fcn' (':5933:2') */
  real_T DiscreteTransferFcn_states_h; /* 'Discrete Transfer Fcn' (':6720:2') */
  real_T DiscreteTimeIntegrator1_DSTAT_c;
                                     /* 'Discrete-Time Integrator1' (':6691') */
  real_T DiscreteTimeIntegrator_DSTATE_n;
                                      /* 'Discrete-Time Integrator' (':6433') */
  real_T DiscreteTransferFcn_states_hp;/* 'Discrete Transfer Fcn' (':6412:2') */
  real_T DiscreteTransferFcn_states_oh;/* 'Discrete Transfer Fcn' (':5934:2') */
  real_T DiscreteTransferFcn_states_m4;/* 'Discrete Transfer Fcn' (':5876:2') */
  real_T DiscreteTransferFcn_states_g1m;/* 'Discrete Transfer Fcn' (':5908:2') */
  real_T DiscreteTransferFcn_states_hf;/* 'Discrete Transfer Fcn' (':5850:2') */
  real_T DiscreteTimeIntegrator1_DSTAT_j;
                                     /* 'Discrete-Time Integrator1' (':6363') */
  real_T DiscreteTimeIntegrator_DSTATE_f;
                                      /* 'Discrete-Time Integrator' (':6362') */
  Ui_Cmd_i HilsCmd;                    /* 'Data Store Memory3' (':3575') */
  Hils_Mode_i HilsMode;                /* 'Data Store Memory9' (':950') */
  real32_T DigitalFilter_FILT_STATES[2];/* 'Digital Filter' (':5362:26') */
  real32_T DigitalFilter_FILT_STATES_o[2];/* 'Digital Filter' (':5421:26') */
  real32_T DigitalFilter_FILT_STATES_g[2];/* 'Digital Filter' (':5426:26') */
  real32_T DigitalFilter_FILT_STATES_a[2];/* 'Digital Filter' (':5431:26') */
  real32_T DigitalFilter_FILT_STATES_c[2];/* 'Digital Filter' (':5436:26') */
  real32_T DigitalFilter_FILT_STATES_h[2];/* 'Digital Filter' (':5441:26') */
  real32_T DigitalFilter_FILT_STATES_m[2];/* 'Digital Filter' (':5446:26') */
  uint16_T AlignBk;                    /* 'Hils_SequenceCtrl' (':5237') */
  uint16_T BandBk;                     /* 'Hils_SequenceCtrl' (':5237') */
  uint16_T WdBk;                       /* 'Hils_SequenceCtrl' (':5237') */
  uint16_T OutputSetCmd;               /* 'Hils_SequenceCtrl' (':5237') */
  uint16_T temporalCounter_i1;         /* 'Hils_SequenceCtrl' (':5237') */
  int8_T DiscreteTimeIntegrator2_PrevRes;
                                     /* 'Discrete-Time Integrator2' (':6364') */
  int8_T DiscreteTimeIntegrator1_PrevRes;
                                     /* 'Discrete-Time Integrator1' (':6434') */
  int8_T DiscreteTimeIntegrator_PrevRese;
                                      /* 'Discrete-Time Integrator' (':6780') */
  int8_T DiscreteTimeIntegrator1_PrevR_d;
                                     /* 'Discrete-Time Integrator1' (':6781') */
  int8_T DiscreteTimeIntegrator_PrevRe_b;
                                      /* 'Discrete-Time Integrator' (':6690') */
  int8_T DiscreteTimeIntegrator1_PrevR_g;
                                     /* 'Discrete-Time Integrator1' (':6691') */
  int8_T DiscreteTimeIntegrator_PrevRe_n;
                                      /* 'Discrete-Time Integrator' (':6433') */
  int8_T DiscreteTimeIntegrator1_PrevR_k;
                                     /* 'Discrete-Time Integrator1' (':6363') */
  int8_T DiscreteTimeIntegrator_PrevRe_p;
                                      /* 'Discrete-Time Integrator' (':6362') */
  uint8_T is_active_c10_Lws_HilsCtrl_2402;/* 'Hils_SequenceCtrl' (':5237') */
  uint8_T is_c10_Lws_HilsCtrl_240218_v_1_;/* 'Hils_SequenceCtrl' (':5237') */
  uint8_T is_Main_Hils_Control;        /* 'Hils_SequenceCtrl' (':5237') */
  uint8_T is_PowerOn_Standby;          /* 'Hils_SequenceCtrl' (':5237') */
  uint8_T is_Hils_Ctrl_Process;        /* 'Hils_SequenceCtrl' (':5237') */
  uint8_T is_OutSet_Control;           /* 'Hils_SequenceCtrl' (':5237') */
  uint8_T temporalCounter_i2;          /* 'Hils_SequenceCtrl' (':5237') */
  uint8_T DiscreteTimeIntegrator2_IC_LOAD;
                                     /* 'Discrete-Time Integrator2' (':6364') */
  uint8_T DiscreteTimeIntegrator1_IC_LOAD;
                                     /* 'Discrete-Time Integrator1' (':6434') */
  uint8_T DiscreteTimeIntegrator_IC_LOADI;
                                      /* 'Discrete-Time Integrator' (':6780') */
  uint8_T DiscreteTimeIntegrator1_IC_LO_c;
                                     /* 'Discrete-Time Integrator1' (':6781') */
  uint8_T DiscreteTimeIntegrator_IC_LOA_a;
                                      /* 'Discrete-Time Integrator' (':6690') */
  uint8_T DiscreteTimeIntegrator1_IC_LO_p;
                                     /* 'Discrete-Time Integrator1' (':6691') */
  uint8_T DiscreteTimeIntegrator_IC_LOA_e;
                                      /* 'Discrete-Time Integrator' (':6433') */
  uint8_T DiscreteTimeIntegrator1_IC_LO_n;
                                     /* 'Discrete-Time Integrator1' (':6363') */
  uint8_T DiscreteTimeIntegrator_IC_LOA_n;
                                      /* 'Discrete-Time Integrator' (':6362') */
}
DW_Lws_HilsCtrl_240218_v_1_0_T;

/* External inputs (root inport signals with default storage) */
typedef struct
{
  uint16_T LwsWtuA_HilsDI[8];          /* 'LwsWtuA_HilsDI' (':4') */
  real32_T LwsWtuA_HilsAI[8];          /* 'LwsWtuA_HilsAI' (':3999') */
  uint16_T LwsWtuA_HilsCmd[4];         /* 'LwsWtuA_HilsCmd' (':20') */
  uint16_T LwsWtuA_HilsOutSet[18];     /* 'LwsWtuA_HilsOutSet' (':21') */
  real32_T LwsWutA_HilsPara[20];       /* 'LwsWutA_HilsPara' (':11') */
}
ExtU_Lws_HilsCtrl_240218_v_1__T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct
{
  uint16_T LwsWtuA_HilsDO[19];         /* 'LwsWtuA_HilsDO' (':1441') */
  real32_T LwsWtuA_HilsAO[27];         /* 'LwsWtuA_HilsAO' (':2900') */
  real32_T LwsWtuA_HilsMon[15];        /* 'LwsWtuA_HilsMon' (':2923') */
  uint16_T LwsWtuA_HilsMode;           /* 'LwsWtuA_HilsMode' (':1445') */
  uint16_T LwsWtuA_HilsStatus;         /* 'LwsWtuA_HilsStatus' (':1446') */
  uint16_T LwsWtuA_HilsError;          /* 'LwsWtuA_HilsError' (':1448') */
  uint16_T LwsWtuA_HilsAlarm;          /* 'LwsWtuA_HilsAlarm' (':2921') */
}
ExtY_Lws_HilsCtrl_240218_v_1__T;

/* Block signals (default storage) */
extern B_Lws_HilsCtrl_240218_v_1_0_T Lws_HilsCtrl_240218_v_1_0_B;

/* Block states (default storage) */
extern DW_Lws_HilsCtrl_240218_v_1_0_T Lws_HilsCtrl_240218_v_1_0_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Lws_HilsCtrl_240218_v_1__T Lws_HilsCtrl_240218_v_1_0_Y;

/* Model entry point functions */
extern void Lws_HilsCtrl_240218_v_1_0_initialize(void);
extern void Lws_HilsCtrl_240218_v_1_0_step(void);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'Gain2' (':6549') : Unused code path elimination
 * Block 'Gain2' (':6439') : Unused code path elimination
 * Block synthesized block : Eliminate redundant data type conversion
 * Block 'Gain36' (':6616') : Eliminated nontunable gain of 1
 * Block 'Manual Switch4' (':5741') : Eliminated due to constant selection input
 * Block 'Manual Switch2' (':6380') : Eliminated due to constant selection input
 * Block 'Cmd_Xv_Limit (0:close,  1:Positive Full Open,  -1:Negitive Full Open)' (':6470') : Unused code path elimination
 * Block 'Gain1' (':6474') : Unused code path elimination
 * Block 'Gain3' (':6475') : Unused code path elimination
 * Block 'Gain4' (':6476') : Unused code path elimination
 * Block 'Gain5' (':6477') : Unused code path elimination
 * Block 'Prssure_Limit' (':6479') : Unused code path elimination
 * Block synthesized block : Unused code path elimination
 * Block 'Discrete Transfer Fcn' (':6483:2') : Unused code path elimination
 * Block 'Discrete Transfer Fcn' (':6484:2') : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is 'block_name' ('SID'), where block_name is the name of the block
 * and SID is the Simulink identifier of the block without the model name.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system(':3')    - opens block with Simulink identifier 'model:3'
 */

/*-
 * Requirements for model: Lws_HilsCtrl_240218_v_1_0
 */
#endif                             /* RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
