/*
 * File: Lws_HilsCtrl_240218_v_1_0_types.h
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

#ifndef RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_types_h_
#define RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_types_h_
#include "rtwtypes.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_Di_i_
#define DEFINED_TYPEDEF_FOR_Di_i_

typedef struct
{
  uint16_T NoLoadValve_Winch;
  uint16_T NoLoadValve_DropLift;
  uint16_T CutValve_Winch;
  uint16_T DirValve_AlignBk;
  uint16_T DirValve_MainBk;
  uint16_T DirValve_SubBk;
  uint16_T Spare01;
  uint16_T Spare02;
}
Di_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Do_i_
#define DEFINED_TYPEDEF_FOR_Do_i_

typedef struct
{
  uint16_T PreSwitch_Boost;
  uint16_T PreSwitch_DropLift;
  uint16_T PreSwitch_PreOver;
  uint16_T PreSwitch_Wind;
  uint16_T PreSwitch_Unwind;
  uint16_T PreSwitch_AlignDrv;
  uint16_T FilterSwitch_Return;
  uint16_T FilterSwitch_BoostPump;
  uint16_T FilterSwitch_WinchDrv;
  uint16_T FilterSwitch_DropLift;
  uint16_T AlighLimit_RightA;
  uint16_T AlighLimit_RightB;
  uint16_T AlighLimit_LeftA;
  uint16_T AlighLimit_LeftB;
  uint16_T FiveTurn_Switch;
  uint16_T PreSwitch_AlignBk;
  uint16_T PreSwitch_MainBk;
  uint16_T PreSwitch_SubBk;
  uint16_T PValveError_WinchPw;
}
Do_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_DataMon_i_
#define DEFINED_TYPEDEF_FOR_Hils_DataMon_i_

typedef struct
{
  real32_T WinchDrun_Angle;
  real32_T WinchDrum_Vel;
  real32_T Align_Angle;
  real32_T Align_Vel;
  real32_T MainCy01_Pos;
  real32_T MainCy01_Vel;
  real32_T MainCy02_Pos;
  real32_T MainCy02_Vel;
  real32_T SubCy01_Pos;
  real32_T SubCy01_Vel;
  real32_T SubCy02_Pos;
  real32_T SubCy02_Vel;
  real32_T Spare01;
  real32_T Spare02;
  real32_T Spare03;
}
Hils_DataMon_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ai_i_
#define DEFINED_TYPEDEF_FOR_Ai_i_

typedef struct
{
  real32_T PValve_EmgDrv;
  real32_T PValve_DrumDrv;
  real32_T PValve_AlignDrv;
  real32_T PValve_MainCy01Drv;
  real32_T PValve_MainCy02Drv;
  real32_T PValve_SubCy01Drv;
  real32_T PValve_SubCy02Drv;
  real32_T Spare;
}
Ai_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ao_i_
#define DEFINED_TYPEDEF_FOR_Ao_i_

typedef struct
{
  real32_T Pressure_WinchPw;
  real32_T Pressure_DropLiftPw;
  real32_T OilFlow_DropLift;
  real32_T PValveError_EmgDrv;
  real32_T WinchDrum_Angle;
  real32_T Align_Angle;
  real32_T PValveError_AlignDrv;
  real32_T DrumMotorA_Velocity;
  real32_T DrumMotorB_Velocity;
  real32_T AlignMotor_Velocity;
  real32_T TensionSensor;
  real32_T MainSy01_ExpPressure;
  real32_T MainSy01_ConPressure;
  real32_T MainSy01_LVDT;
  real32_T MainSy01_PValveError;
  real32_T MainSy02_ExpPressure;
  real32_T MainSy02_ConPressure;
  real32_T MainSy02_LVDT;
  real32_T MainSy02_PValveError;
  real32_T SubSy01_ExpPressure;
  real32_T SubSy01_ConPressure;
  real32_T SubSy01_LVDT;
  real32_T SubSy01_PValveError;
  real32_T SubSy02_ExpPressure;
  real32_T SubSy02_ConPressure;
  real32_T SubSy02_LVDT;
  real32_T SubSy02_PValveError;
}
Ao_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_Alarm_i_
#define DEFINED_TYPEDEF_FOR_Hils_Alarm_i_

typedef struct
{
  uint16_T a;
  uint16_T a1;
  uint16_T a2;
  uint16_T a3;
  uint16_T a4;
  uint16_T a5;
  uint16_T a6;
  uint16_T a7;
  uint16_T a8;
  uint16_T a9;
  uint16_T a10;
  uint16_T a11;
  uint16_T a12;
  uint16_T a13;
  uint16_T a14;
  uint16_T a15;
}
Hils_Alarm_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ui_Cmd_i_
#define DEFINED_TYPEDEF_FOR_Ui_Cmd_i_

typedef struct
{
  uint16_T HilsMode_Start;
  uint16_T HilsMode_Stop;
  uint16_T HilsOutSet_Change;
  uint16_T Spare;
}
Ui_Cmd_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Ui_OutSet_i_
#define DEFINED_TYPEDEF_FOR_Ui_OutSet_i_

typedef struct
{
  uint16_T Filter_Return;
  uint16_T Filter_BoostPump;
  uint16_T Filter_WinchDrv;
  uint16_T Filter_DropLift;
  uint16_T AlignLimit_RightA;
  uint16_T AlignLimit_RightB;
  uint16_T AlignLimit_LeftA;
  uint16_T AlignLimit_LeftB;
  uint16_T FiveTurnSwitch;
  uint16_T PValveErr_WinchDrv;
  uint16_T PValveErr_AlignDrv;
  uint16_T PValveErr_EmgDrv;
  uint16_T PValveErr_MainCy01Drv;
  uint16_T PValveErr_MainCy02Drv;
  uint16_T PValveErr_SubCy01Drv;
  uint16_T PValveErr_SubCy02Drv;
  uint16_T OverPressure;
  uint16_T Spare;
}
Ui_OutSet_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_Error_i_
#define DEFINED_TYPEDEF_FOR_Hils_Error_i_

typedef struct
{
  uint16_T a;
  uint16_T a1;
  uint16_T a2;
  uint16_T a3;
  uint16_T a4;
  uint16_T a5;
  uint16_T a6;
  uint16_T a7;
  uint16_T a8;
  uint16_T a9;
  uint16_T a10;
  uint16_T a11;
  uint16_T a12;
  uint16_T a13;
  uint16_T a14;
  uint16_T a15;
}
Hils_Error_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_Status_i_
#define DEFINED_TYPEDEF_FOR_Hils_Status_i_

typedef struct
{
  uint16_T HilsRunning;
  uint16_T Power_On;
  uint16_T WinchPower_On;
  uint16_T BoostPower_On;
  uint16_T DlPower_On;
  uint16_T AlignBk_Unlock;
  uint16_T BandBk_Unlock;
  uint16_T WdBk_Unlock;
  uint16_T PValveErr_Algin;
  uint16_T PValveErr_Emg;
  uint16_T PValveErr_MC01;
  uint16_T PValveErr_MC02;
  uint16_T PValveErr_SC01;
  uint16_T PValveErr_SC02;
  uint16_T a14;
  uint16_T a15;
}
Hils_Status_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_Para_i_
#define DEFINED_TYPEDEF_FOR_Hils_Para_i_

typedef struct
{
  real32_T Winch_InitAngle;
  real32_T Align_InitAngle;
  real32_T MainCy01_InitPos;
  real32_T MainCy02_InitPos;
  real32_T SubCy01_InitPos;
  real32_T SubCy02_InitPos;
  real32_T WinchPw_RefPressure;
  real32_T DropLiftPw_RefPressure;
  real32_T OilFlowS_RefFlow;
  real32_T TensionS_RefTension;
  real32_T MainSy_ExpRefPressure;
  real32_T MainSy_ConRefPressure;
  real32_T SubSy_ExpRefPressure;
  real32_T SubSy_ConRefPressure;
  real32_T Spare01;
  real32_T Spare02;
  real32_T Spare03;
  real32_T Spare04;
  real32_T Spare05;
  real32_T Spare06;
}
Hils_Para_i;

#endif

#ifndef DEFINED_TYPEDEF_FOR_Hils_Mode_i_
#define DEFINED_TYPEDEF_FOR_Hils_Mode_i_

typedef struct
{
  uint16_T Op_Mode;
}
Hils_Mode_i;

#endif
#endif                       /* RTW_HEADER_Lws_HilsCtrl_240218_v_1_0_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
