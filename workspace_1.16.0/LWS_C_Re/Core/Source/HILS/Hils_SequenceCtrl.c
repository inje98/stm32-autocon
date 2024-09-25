/*
 * File: Hils_SequenceCtrl.c
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

#include "Hils_SequenceCtrl.h"

/* Include model header file for global data */
#include "Lws_HilsCtrl_240218_v_1_0.h"
#include "Lws_HilsCtrl_240218_v_1_0_private.h"

/* Named constants for Chart: ''Hils_SequenceCtrl' (':5237')' */
#define Lws_Hi_IN_WinchDrum_Power_OnSet ((uint8_T)5U)
#define Lws_Hil_IN_BkUnlock_TimeDelay01 ((uint8_T)8U)
#define Lws_Hil_IN_BkUnlock_TimeDelay02 ((uint8_T)9U)
#define Lws_Hil_IN_BkUnlock_TimeDelay03 ((uint8_T)10U)
#define Lws_Hil_IN_DropLift_Power_OnSet ((uint8_T)1U)
#define Lws_HilsC_IN_BkLock_TimeDelay01 ((uint8_T)5U)
#define Lws_HilsC_IN_BkLock_TimeDelay02 ((uint8_T)6U)
#define Lws_HilsC_IN_BkLock_TimeDelay03 ((uint8_T)7U)
#define Lws_HilsC_IN_PowerOff_TimeDelay ((uint8_T)14U)
#define Lws_HilsCt_IN_AlignBk_SwitchOff ((uint8_T)1U)
#define Lws_HilsCt_IN_OutputSet_Process ((uint8_T)3U)
#define Lws_HilsCt_IN_Total_Power_OnSet ((uint8_T)4U)
#define Lws_HilsCtr_IN_AlignBk_SwitchOn ((uint8_T)2U)
#define Lws_HilsCtr_IN_BankBk_SwitchOff ((uint8_T)3U)
#define Lws_HilsCtr_IN_HilsControl_Init ((uint8_T)11U)
#define Lws_HilsCtr_IN_HilsControl_Loop ((uint8_T)12U)
#define Lws_HilsCtrl_240218_IN_Return_m ((uint8_T)5U)
#define Lws_HilsCtrl_240218_IN_Sys_Init ((uint8_T)4U)
#define Lws_HilsCtrl_240218_v_IN_Return ((uint8_T)15U)
#define Lws_HilsCtrl_240_IN_Output_Init ((uint8_T)4U)
#define Lws_HilsCtrl_24_IN_Hils_Control ((uint8_T)1U)
#define Lws_HilsCtrl_24_IN_OP_Mode_Stop ((uint8_T)3U)
#define Lws_HilsCtrl_24_IN_Time_Delay01 ((uint8_T)3U)
#define Lws_HilsCtrl_2_IN_OP_Mode_Check ((uint8_T)1U)
#define Lws_HilsCtrl_2_IN_PowerOff_Proc ((uint8_T)13U)
#define Lws_HilsCtrl_2_IN_WdBk_SwitchOn ((uint8_T)17U)
#define Lws_HilsCtrl_IN_BankBk_SwitchOn ((uint8_T)4U)
#define Lws_HilsCtrl_IN_HilsOutput_Init ((uint8_T)2U)
#define Lws_HilsCtrl_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define Lws_HilsCtrl_IN_OP_Mode_Running ((uint8_T)2U)
#define Lws_HilsCtrl_IN_PowerOn_Standby ((uint8_T)3U)
#define Lws_HilsCtrl__IN_OutputSet_Loop ((uint8_T)2U)
#define Lws_HilsCtrl__IN_WdBk_SwitchOff ((uint8_T)16U)
#define Lws_Hils_IN_Mode_Operation_Init ((uint8_T)2U)
#define Lws__IN_OutputSetCmd_ClearDelay ((uint8_T)1U)

/* Forward declaration for local functions */
static void Lws__exit_internal_Hils_Control(void);
static void enter_internal_PowerOn_Standby(void);
static void Lws_HilsCtrl__Main_Hils_Control(void);

/* Function for Chart: ''Hils_SequenceCtrl' (':5237')' */
static void Lws__exit_internal_Hils_Control(void)
{
  /* Exit Internal 'Hils_Control': (':5237:133') */
  /* Exit Internal 'Hils_Ctrl_Process': (':5237:493') */
  Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
}

/* Function for Chart: ''Hils_SequenceCtrl' (':5237')' */
static void enter_internal_PowerOn_Standby(void)
{
  /* Entry Internal 'PowerOn_Standby': (':5237:469') */
  /* Transition: (':5237:470') */
  Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
    Lws_HilsCtrl_IN_HilsOutput_Init;

  /* Entry 'HilsOutput_Init': (':5237:478') */
  /* (':5237:478:3') HilsStatus.Power_On = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On = 0U;

  /* (':5237:478:4') HilsStatus.WinchPower_On = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WinchPower_On = 0U;

  /* (':5237:478:5') HilsStatus.BoostPower_On = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BoostPower_On = 0U;

  /* (':5237:478:6') HilsStatus.DlPower_On = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.DlPower_On = 0U;

  /*  Pressure Switch Set */
  /* (':5237:478:8') HilsDO.PreSwitch_Boost = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Boost = 0U;

  /* (':5237:478:9') HilsDO.PreSwitch_AlignDrv = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignDrv = 0U;

  /* (':5237:478:10') HilsDO.PreSwitch_DropLift = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_DropLift = 0U;

  /*  Analog output set */
  /* (':5237:478:12') Pressure_WinchPwBase = 0; */
  Lws_HilsCtrl_240218_v_1_0_B.Pressure_WinchPwBase = 0.0F;

  /* (':5237:478:13') Pressure_DropLiftPw = 0; */
  Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw = 0.0F;

  /* (':5237:478:14') OilFlow_DropLift = 0; */
  Lws_HilsCtrl_240218_v_1_0_B.OilFlow_DropLift = 0.0F;

  /*  Brake Lock status */
  /* (':5237:478:16') HilsDO.PreSwitch_AlignBk = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk = 0U;

  /* (':5237:478:17') HilsDO.PreSwitch_MainBk = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk = 0U;

  /* (':5237:478:18') HilsDO.PreSwitch_SubBk = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk = 0U;

  /* (':5237:478:19') HilsStatus. AlignBk_Unlock = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock = 0U;

  /* (':5237:478:20') HilsStatus. WdBk_Unlock = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock = 0U;

  /* (':5237:478:21') HilsStatus. BandBk_Unlock = 0; */
  Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock = 0U;
}

/* Function for Chart: ''Hils_SequenceCtrl' (':5237')' */
static void Lws_HilsCtrl__Main_Hils_Control(void)
{
  /* During 'Main_Hils_Control': (':5237:334') */
  switch (Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control)
  {
   case Lws_HilsCtrl_24_IN_Hils_Control:
    /* During 'Hils_Control': (':5237:133') */
    /* (':5237:137:1') sf_internal_predicateOutput = HilsStatus.Power_On==0; */
    if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On) == 0)
    {
      /* Transition: (':5237:137') */
      Lws__exit_internal_Hils_Control();
      Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
        Lws_HilsCtrl_IN_PowerOn_Standby;
      enter_internal_PowerOn_Standby();
    }
    else
    {
      /* During 'Hils_Ctrl_Process': (':5237:493') */
      switch (Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process)
      {
       case Lws_HilsCt_IN_AlignBk_SwitchOff:
        /* During 'AlignBk_SwitchOff': (':5237:538') */
        /* Transition: (':5237:544') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;

       case Lws_HilsCtr_IN_AlignBk_SwitchOn:
        /* During 'AlignBk_SwitchOn': (':5237:521') */
        /* Transition: (':5237:524') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;

       case Lws_HilsCtr_IN_BankBk_SwitchOff:
        /* During 'BankBk_SwitchOff': (':5237:548') */
        /* Transition: (':5237:545') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;

       case Lws_HilsCtrl_IN_BankBk_SwitchOn:
        /* During 'BankBk_SwitchOn': (':5237:535') */
        /* Transition: (':5237:532') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;

       case Lws_HilsC_IN_BkLock_TimeDelay01:
        /* During 'BkLock_TimeDelay01': (':5237:550') */
        /* (':5237:551:1') sf_internal_predicateOutput = after(0.5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 200U)
        {
          /* Transition: (':5237:551') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCt_IN_AlignBk_SwitchOff;

          /* Entry 'AlignBk_SwitchOff': (':5237:538') */
          /* (':5237:538:3') HilsDO.PreSwitch_AlignBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk = 0U;

          /* (':5237:538:4') HilsStatus. AlignBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock = 0U;
        }
        break;

       case Lws_HilsC_IN_BkLock_TimeDelay02:
        /* During 'BkLock_TimeDelay02': (':5237:541') */
        /* (':5237:543:1') sf_internal_predicateOutput = after(0.5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 200U)
        {
          /* Transition: (':5237:543') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtrl__IN_WdBk_SwitchOff;

          /* Entry 'WdBk_SwitchOff': (':5237:542') */
          /* (':5237:542:3') HilsDO.PreSwitch_SubBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk = 0U;

          /* (':5237:542:4') HilsStatus. WdBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock = 0U;
        }
        break;

       case Lws_HilsC_IN_BkLock_TimeDelay03:
        /* During 'BkLock_TimeDelay03': (':5237:549') */
        /* (':5237:546:1') sf_internal_predicateOutput = after(1.0,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 400U)
        {
          /* Transition: (':5237:546') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtr_IN_BankBk_SwitchOff;

          /* Entry 'BankBk_SwitchOff': (':5237:548') */
          /* (':5237:548:3') HilsDO.PreSwitch_MainBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk = 0U;

          /* (':5237:548:4') HilsStatus. BandBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock = 0U;
        }
        break;

       case Lws_Hil_IN_BkUnlock_TimeDelay01:
        /* During 'BkUnlock_TimeDelay01': (':5237:520') */
        /* (':5237:522:1') sf_internal_predicateOutput = after(0.5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 200U)
        {
          /* Transition: (':5237:522') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtr_IN_AlignBk_SwitchOn;

          /* Entry 'AlignBk_SwitchOn': (':5237:521') */
          /* (':5237:521:3') HilsDO.PreSwitch_AlignBk = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk = 1U;

          /* (':5237:521:4') HilsStatus. AlignBk_Unlock = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock = 1U;
        }
        break;

       case Lws_Hil_IN_BkUnlock_TimeDelay02:
        /* During 'BkUnlock_TimeDelay02': (':5237:529') */
        /* (':5237:530:1') sf_internal_predicateOutput = after(0.5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 200U)
        {
          /* Transition: (':5237:530') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtrl_2_IN_WdBk_SwitchOn;

          /* Entry 'WdBk_SwitchOn': (':5237:527') */
          /* (':5237:527:3') HilsDO.PreSwitch_SubBk = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk = 1U;

          /* (':5237:527:4') HilsStatus. WdBk_Unlock = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock = 1U;
        }
        break;

       case Lws_Hil_IN_BkUnlock_TimeDelay03:
        /* During 'BkUnlock_TimeDelay03': (':5237:534') */
        /* (':5237:536:1') sf_internal_predicateOutput = after(1.0,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 400U)
        {
          /* Transition: (':5237:536') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtrl_IN_BankBk_SwitchOn;

          /* Entry 'BankBk_SwitchOn': (':5237:535') */
          /* (':5237:535:3') HilsDO.PreSwitch_MainBk = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk = 1U;

          /* (':5237:535:4') HilsStatus. BandBk_Unlock = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock = 1U;
        }
        break;

       case Lws_HilsCtr_IN_HilsControl_Init:
        /* During 'HilsControl_Init': (':5237:127') */
        /* Transition: (':5237:142') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtr_IN_HilsControl_Loop;

        /* Entry 'HilsControl_Loop': (':5237:141') */
        break;

       case Lws_HilsCtr_IN_HilsControl_Loop:
        /* During 'HilsControl_Loop': (':5237:141') */
        /* (':5237:156:1') sf_internal_predicateOutput = (AlignBk == 1) &&(HilsStatus. AlignBk_Unlock == 0); */
        if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.AlignBk) == 1) && (((int32_T)
              Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock) == 0))
        {
          /* Transition: (':5237:156') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_Hil_IN_BkUnlock_TimeDelay01;
          Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

          /* Entry 'BkUnlock_TimeDelay01': (':5237:520') */
        }
        else
        {
          /* (':5237:526:1') sf_internal_predicateOutput = (WdBk == 1) &&(HilsStatus. WdBk_Unlock == 0); */
          if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.WdBk) == 1) && (((int32_T)
                Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock) == 0))
          {
            /* Transition: (':5237:526') */
            Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
              Lws_Hil_IN_BkUnlock_TimeDelay02;
            Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

            /* Entry 'BkUnlock_TimeDelay02': (':5237:529') */
          }
          else
          {
            /* (':5237:533:1') sf_internal_predicateOutput = (BandBk == 1)&&(HilsStatus. BandBk_Unlock == 0); */
            if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.BandBk) == 1) &&
                (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock)
                 == 0))
            {
              /* Transition: (':5237:533') */
              Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
                Lws_Hil_IN_BkUnlock_TimeDelay03;
              Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

              /* Entry 'BkUnlock_TimeDelay03': (':5237:534') */
            }
            else
            {
              /* (':5237:537:1') sf_internal_predicateOutput = (AlignBk == 0) &&(HilsStatus. AlignBk_Unlock == 1); */
              if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.AlignBk) == 0) &&
                  (((int32_T)
                    Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock) == 1))
              {
                /* Transition: (':5237:537') */
                Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
                  Lws_HilsC_IN_BkLock_TimeDelay01;
                Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

                /* Entry 'BkLock_TimeDelay01': (':5237:550') */
              }
              else
              {
                /* (':5237:540:1') sf_internal_predicateOutput = (WdBk == 0) &&(HilsStatus. WdBk_Unlock == 1); */
                if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.WdBk) == 0) &&
                    (((int32_T)
                      Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock) == 1))
                {
                  /* Transition: (':5237:540') */
                  Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
                    Lws_HilsC_IN_BkLock_TimeDelay02;
                  Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

                  /* Entry 'BkLock_TimeDelay02': (':5237:541') */
                }
                else
                {
                  /* (':5237:547:1') sf_internal_predicateOutput = (BandBk == 0)&&(HilsStatus. BandBk_Unlock == 1); */
                  if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.BandBk) == 0) &&
                      (((int32_T)
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock) ==
                       1))
                  {
                    /* Transition: (':5237:547') */
                    Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
                      Lws_HilsC_IN_BkLock_TimeDelay03;
                    Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

                    /* Entry 'BkLock_TimeDelay03': (':5237:549') */
                  }
                  else
                  {
                    /* (':5237:562:1') sf_internal_predicateOutput = (HilsDI.NoLoadValve_Winch==1)&&(HilsDI.NoLoadValve_DropLift==1); */
                    if ((((int32_T)
                          Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_Winch)
                         == 1) && (((int32_T)
                                    Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_DropLift)
                                   == 1))
                    {
                      /* Transition: (':5237:562') */
                      Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
                        Lws_HilsC_IN_PowerOff_TimeDelay;
                      Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

                      /* Entry 'PowerOff_TimeDelay': (':5237:552') */
                    }
                    else
                    {
                      /* (':5237:141:3') AlignBk = HilsDI.DirValve_AlignBk; */
                      Lws_HilsCtrl_240218_v_1_0_DW.AlignBk =
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_AlignBk;

                      /* (':5237:141:4') BandBk = HilsDI.DirValve_MainBk; */
                      Lws_HilsCtrl_240218_v_1_0_DW.BandBk =
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_MainBk;

                      /* (':5237:141:5') WdBk = HilsDI.DirValve_SubBk; */
                      Lws_HilsCtrl_240218_v_1_0_DW.WdBk =
                        Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.DirValve_SubBk;
                    }
                  }
                }
              }
            }
          }
        }
        break;

       case Lws_HilsCtrl_2_IN_PowerOff_Proc:
        /* During 'PowerOff_Proc': (':5237:563') */
        break;

       case Lws_HilsC_IN_PowerOff_TimeDelay:
        /* During 'PowerOff_TimeDelay': (':5237:552') */
        /* (':5237:564:1') sf_internal_predicateOutput = after(5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 2000U)
        {
          /* Transition: (':5237:564') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
            Lws_HilsCtrl_2_IN_PowerOff_Proc;

          /* Entry 'PowerOff_Proc': (':5237:563') */
          /*  Hils Control Process Out */
          /* (':5237:563:4') HilsStatus.Power_On = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On = 0U;
        }
        break;

       case Lws_HilsCtrl_240218_v_IN_Return:
        /* During 'Return': (':5237:148') */
        /* Transition: (':5237:525') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtr_IN_HilsControl_Loop;

        /* Entry 'HilsControl_Loop': (':5237:141') */
        break;

       case Lws_HilsCtrl__IN_WdBk_SwitchOff:
        /* During 'WdBk_SwitchOff': (':5237:542') */
        /* Transition: (':5237:539') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;

       default:
        /* During 'WdBk_SwitchOn': (':5237:527') */
        /* Transition: (':5237:531') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
          Lws_HilsCtrl_240218_v_IN_Return;

        /* Entry 'Return': (':5237:148') */
        break;
      }

      /* During 'Another_Process': (':5237:494') */
    }
    break;

   case Lws_Hils_IN_Mode_Operation_Init:
    /* During 'Mode_Operation_Init': (':5237:124') */
    /* Transition: (':5237:126') */
    Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
      Lws_HilsCtrl_IN_PowerOn_Standby;
    enter_internal_PowerOn_Standby();
    break;

   default:
    /* During 'PowerOn_Standby': (':5237:469') */
    /* (':5237:136:1') sf_internal_predicateOutput = HilsStatus.Power_On==1; */
    if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On) == 1)
    {
      /* Transition: (':5237:136') */
      /* Exit Internal 'PowerOn_Standby': (':5237:469') */
      Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
        Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
      Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
        Lws_HilsCtrl_24_IN_Hils_Control;

      /* Entry Internal 'Hils_Control': (':5237:133') */
      /* Entry Internal 'Hils_Ctrl_Process': (':5237:493') */
      /* Transition: (':5237:131') */
      Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
        Lws_HilsCtr_IN_HilsControl_Init;

      /* Entry 'HilsControl_Init': (':5237:127') */
      /* (':5237:127:3') HilsDO.PreSwitch_AlignBk = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk = 0U;

      /*  Brake Lock status */
      /* (':5237:127:4') HilsDO.PreSwitch_MainBk = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk = 0U;

      /* (':5237:127:5') HilsDO.PreSwitch_SubBk = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk = 0U;

      /* (':5237:127:6') HilsStatus. AlignBk_Unlock = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock = 0U;

      /* (':5237:127:7') HilsStatus. WdBk_Unlock = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock = 0U;

      /* (':5237:127:8') HilsStatus. BandBk_Unlock = 0; */
      Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock = 0U;
    }
    else
    {
      switch (Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby)
      {
       case Lws_Hil_IN_DropLift_Power_OnSet:
        /* During 'DropLift_Power_OnSet': (':5237:486') */
        /* (':5237:490:1') sf_internal_predicateOutput = (HilsDI.NoLoadValve_Winch==0)&&(HilsDI.NoLoadValve_DropLift==0); */
        if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_Winch) ==
             0) && (((int32_T)
                     Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_DropLift) ==
                    0))
        {
          /* Transition: (':5237:490') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
            Lws_HilsCt_IN_Total_Power_OnSet;

          /* Entry 'Total_Power_OnSet': (':5237:491') */
          /* (':5237:491:3') HilsStatus.Power_On = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On = 1U;

          /*  Total Power On */
        }
        break;

       case Lws_HilsCtrl_IN_HilsOutput_Init:
        /* During 'HilsOutput_Init': (':5237:478') */
        /* (':5237:472:1') sf_internal_predicateOutput = (HilsDI.NoLoadValve_Winch==1)&&(HilsDI.NoLoadValve_DropLift==1); */
        if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_Winch) ==
             1) && (((int32_T)
                     Lws_HilsCtrl_240218_v_1_0_DW.HilsDI.NoLoadValve_DropLift) ==
                    1))
        {
          /* Transition: (':5237:472') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
            Lws_HilsCtrl_24_IN_Time_Delay01;
          Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

          /* Entry 'Time_Delay01': (':5237:480') */
        }
        break;

       case Lws_HilsCtrl_24_IN_Time_Delay01:
        /* During 'Time_Delay01': (':5237:480') */
        /* (':5237:474:1') sf_internal_predicateOutput = after(7.5,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 3000U)
        {
          /* Transition: (':5237:474') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
            Lws_Hi_IN_WinchDrum_Power_OnSet;
          Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

          /* Entry 'WinchDrum_Power_OnSet': (':5237:481') */
          /* (':5237:481:3') HilsStatus.WinchPower_On = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WinchPower_On = 1U;

          /*  WinchDrum MotorPower On */
          /* (':5237:481:4') HilsStatus.BoostPower_On = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BoostPower_On = 1U;

          /*  Align MotorPower On */
          /*  Pressure Switch Set */
          /* (':5237:481:6') HilsDO.PreSwitch_Boost = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Boost = 1U;

          /* (':5237:481:7') HilsDO.PreSwitch_AlignDrv = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignDrv = 1U;

          /*  Analog output set */
          /* (':5237:481:9') Pressure_WinchPwBase = HilsPara.WinchPw_RefPressure; */
          Lws_HilsCtrl_240218_v_1_0_B.Pressure_WinchPwBase =
            Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.WinchPw_RefPressure;
        }
        break;

       case Lws_HilsCt_IN_Total_Power_OnSet:
        /* During 'Total_Power_OnSet': (':5237:491') */
        break;

       default:
        /* During 'WinchDrum_Power_OnSet': (':5237:481') */
        /* (':5237:487:1') sf_internal_predicateOutput = after(5.0,sec); */
        if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 2000U)
        {
          /* Transition: (':5237:487') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
            Lws_Hil_IN_DropLift_Power_OnSet;

          /* Entry 'DropLift_Power_OnSet': (':5237:486') */
          /* (':5237:486:3') HilsStatus.DlPower_On = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.DlPower_On = 1U;

          /*  DropLift MotorPower On */
          /*  Pressure Switch Set */
          /* (':5237:486:5') HilsDO.PreSwitch_DropLift = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_DropLift = 1U;

          /*  Analog output set */
          /* (':5237:486:7') Pressure_DropLiftPw = HilsPara.DropLiftPw_RefPressure; */
          Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw =
            Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.DropLiftPw_RefPressure;

          /* (':5237:486:8') OilFlow_DropLift = HilsPara.OilFlowS_RefFlow; */
          Lws_HilsCtrl_240218_v_1_0_B.OilFlow_DropLift =
            Lws_HilsCtrl_240218_v_1_0_DW.HilsPara.OilFlowS_RefFlow;
        }
        break;
      }
    }
    break;
  }
}

/* System initialize for atomic system: 'Hils_SequenceCtrl' (':5237') */
void Hils_SequenceCtrl_Init(void)
{
  Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
  Lws_HilsCtrl_240218_v_1_0_DW.is_Hils_Ctrl_Process =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
  Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
  Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
  Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2 = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.is_active_c10_Lws_HilsCtrl_2402 = 0U;
  Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
    Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
}

/* Output and update for atomic system: 'Hils_SequenceCtrl' (':5237') */
void Hils_SequenceCtrl(void)
{
  if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) < 4095U)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = (uint16_T)(((uint32_T)
      Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) + 1U);
  }

  if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2) < 255U)
  {
    Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2 = (uint8_T)(((uint32_T)
      Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2) + 1U);
  }

  /* Chart: 'Hils_SequenceCtrl' (':5237') */
  /* Gateway: Lws_HilsCtrl/Hils_SequenceCtrl */
  /* During: Lws_HilsCtrl/Hils_SequenceCtrl */
  if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.is_active_c10_Lws_HilsCtrl_2402) ==
      0U)
  {
    /* Entry: Lws_HilsCtrl/Hils_SequenceCtrl */
    Lws_HilsCtrl_240218_v_1_0_DW.is_active_c10_Lws_HilsCtrl_2402 = 1U;

    /* Entry Internal: Lws_HilsCtrl/Hils_SequenceCtrl */
    /* Transition: (':5237:11') */
    Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
      Lws_HilsCtrl_240218_IN_Sys_Init;
    Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1 = 0U;

    /* Entry 'Sys_Init': (':5237:10') */
  }
  else
  {
    switch (Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_)
    {
     case Lws_HilsCtrl_2_IN_OP_Mode_Check:
      /* During 'OP_Mode_Check': (':5237:103') */
      /* (':5237:120:1') sf_internal_predicateOutput = HilsMode.Op_Mode == 0; */
      if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode) == 0)
      {
        /* Transition: (':5237:120') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
          Lws_HilsCtrl_24_IN_OP_Mode_Stop;

        /* Entry Internal 'OP_Mode_Stop': (':5237:90') */
        /* Transition: (':5237:94') */
        /* Entry 'OP_Mode_Convert': (':5237:49') */
      }
      break;

     case Lws_HilsCtrl_IN_OP_Mode_Running:
      /* During 'OP_Mode_Running': (':5237:95') */
      /* (':5237:119:1') sf_internal_predicateOutput = HilsMode.Op_Mode == 0; */
      if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode) == 0)
      {
        /* Transition: (':5237:119') */
        /* Exit Internal 'OP_Mode_Running': (':5237:95') */
        /* Exit Internal 'OutSet_Control': (':5237:415') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
          Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;

        /* Exit Internal 'HilsMode_EndChk': (':5237:605') */
        /* Exit Internal 'Main_Hils_Control': (':5237:334') */
        Lws__exit_internal_Hils_Control();

        /* Exit Internal 'PowerOn_Standby': (':5237:469') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_PowerOn_Standby =
          Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
        Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
          Lws_HilsCtrl_IN_NO_ACTIVE_CHILD;
        Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
          Lws_HilsCtrl_24_IN_OP_Mode_Stop;

        /* Entry Internal 'OP_Mode_Stop': (':5237:90') */
        /* Transition: (':5237:94') */
        /* Entry 'OP_Mode_Convert': (':5237:49') */
      }
      else
      {
        Lws_HilsCtrl__Main_Hils_Control();

        /* During 'HilsMode_EndChk': (':5237:605') */
        /* During 'OP_Mode_End': (':5237:618') */
        /* (':5237:618:3') if((HilsCmd.HilsMode_Start == 0) && (HilsCmd.HilsMode_Stop == 1)) */
        if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Start) == 0)
            && (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Stop) ==
                1))
        {
          /*  Hils Mode End */
          /* (':5237:618:5') HilsMode.Op_Mode = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode = 0U;

          /* (':5237:618:6') HilsStatus.HilsRunning = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning = 0U;
        }

        /* During 'OutSet_Control': (':5237:415') */
        switch (Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control)
        {
         case Lws__IN_OutputSetCmd_ClearDelay:
          /* During 'OutputSetCmd_ClearDelay': (':5237:598') */
          /* (':5237:602:1') sf_internal_predicateOutput = after(0.6,sec); */
          if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2) >=
              240U)
          {
            /* Transition: (':5237:602') */
            Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
              Lws_HilsCt_IN_OutputSet_Process;

            /* Entry 'OutputSet_Process': (':5237:586') */
            /*  Output Set */
            /* (':5237:586:4') HilsDO.FilterSwitch_Return = HilsOutSet.Filter_Return; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_Return =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_Return;

            /* (':5237:586:5') HilsDO.FilterSwitch_BoostPump = HilsOutSet.Filter_BoostPump; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_BoostPump =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_BoostPump;

            /* (':5237:586:6') HilsDO.FilterSwitch_WinchDrv = HilsOutSet.Filter_WinchDrv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_WinchDrv =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_WinchDrv;

            /* (':5237:586:7') HilsDO.FilterSwitch_DropLift = HilsOutSet.Filter_DropLift; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_DropLift =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.Filter_DropLift;

            /* (':5237:586:8') HilsDO.AlighLimit_RightA = HilsOutSet.AlignLimit_RightA; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightA =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_RightA;

            /* (':5237:586:9') HilsDO.AlighLimit_RightB = HilsOutSet.AlignLimit_RightB; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightB =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_RightB;

            /* (':5237:586:10') HilsDO.AlighLimit_LeftA = HilsOutSet.AlignLimit_LeftA; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftA =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_LeftA;

            /* (':5237:586:11') HilsDO.AlighLimit_LeftB = HilsOutSet.AlignLimit_LeftB; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftB =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.AlignLimit_LeftB;

            /* (':5237:586:12') HilsDO.FiveTurn_Switch = HilsOutSet.FiveTurnSwitch; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FiveTurn_Switch =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.FiveTurnSwitch;

            /* (':5237:586:13') HilsDO.PValveError_WinchPw = HilsOutSet.PValveErr_WinchDrv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PValveError_WinchPw =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_WinchDrv;

            /* (':5237:586:14') HilsStatus.PValveErr_Algin = HilsOutSet.PValveErr_AlignDrv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Algin =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_AlignDrv;

            /* (':5237:586:15') HilsStatus.PValveErr_Emg = HilsOutSet.PValveErr_EmgDrv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Emg =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_EmgDrv;

            /* (':5237:586:16') HilsStatus.PValveErr_MC01 = HilsOutSet.PValveErr_MainCy01Drv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC01 =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_MainCy01Drv;

            /* (':5237:586:17') HilsStatus.PValveErr_MC02 = HilsOutSet.PValveErr_MainCy02Drv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC02 =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_MainCy02Drv;

            /* (':5237:586:18') HilsStatus.PValveErr_SC01 = HilsOutSet.PValveErr_SubCy01Drv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC01 =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_SubCy01Drv;

            /* (':5237:586:19') HilsStatus.PValveErr_SC02 = HilsOutSet.PValveErr_SubCy02Drv; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC02 =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.PValveErr_SubCy02Drv;

            /* (':5237:586:20') HilsDO.PreSwitch_PreOver = HilsOutSet.OverPressure; */
            Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_PreOver =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsOutSet.OverPressure;
          }
          break;

         case Lws_HilsCtrl__IN_OutputSet_Loop:
          /* During 'OutputSet_Loop': (':5237:565') */
          /* (':5237:567:1') sf_internal_predicateOutput = OutputSetCmd==1; */
          if (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.OutputSetCmd) == 1)
          {
            /* Transition: (':5237:567') */
            Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
              Lws__IN_OutputSetCmd_ClearDelay;
            Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i2 = 0U;

            /* Entry 'OutputSetCmd_ClearDelay': (':5237:598') */
          }
          else
          {
            /* (':5237:565:3') OutputSetCmd = HilsCmd.HilsOutSet_Change; */
            Lws_HilsCtrl_240218_v_1_0_DW.OutputSetCmd =
              Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsOutSet_Change;
          }
          break;

         case Lws_HilsCt_IN_OutputSet_Process:
          /* During 'OutputSet_Process': (':5237:586') */
          /* Transition: (':5237:592') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
            Lws_HilsCtrl_240218_IN_Return_m;

          /* Entry 'Return': (':5237:604') */
          break;

         case Lws_HilsCtrl_240_IN_Output_Init:
          /* During 'Output_Init': (':5237:568') */
          /* Transition: (':5237:566') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
            Lws_HilsCtrl__IN_OutputSet_Loop;

          /* Entry 'OutputSet_Loop': (':5237:565') */
          /* (':5237:565:3') OutputSetCmd = HilsCmd.HilsOutSet_Change; */
          Lws_HilsCtrl_240218_v_1_0_DW.OutputSetCmd =
            Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsOutSet_Change;
          break;

         default:
          /* During 'Return': (':5237:604') */
          /* Transition: (':5237:600') */
          Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
            Lws_HilsCtrl__IN_OutputSet_Loop;

          /* Entry 'OutputSet_Loop': (':5237:565') */
          /* (':5237:565:3') OutputSetCmd = HilsCmd.HilsOutSet_Change; */
          Lws_HilsCtrl_240218_v_1_0_DW.OutputSetCmd =
            Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsOutSet_Change;
          break;
        }
      }
      break;

     case Lws_HilsCtrl_24_IN_OP_Mode_Stop:
      /* During 'OP_Mode_Stop': (':5237:90') */
      /* (':5237:117:1') sf_internal_predicateOutput = HilsMode.Op_Mode == 1; */
      switch (Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode)
      {
       case 1:
        /* Transition: (':5237:117') */
        /* Exit Internal 'OP_Mode_Stop': (':5237:90') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
          Lws_HilsCtrl_IN_OP_Mode_Running;

        /* Entry Internal 'OP_Mode_Running': (':5237:95') */
        /* Entry Internal 'Main_Hils_Control': (':5237:334') */
        /* Transition: (':5237:125') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_Main_Hils_Control =
          Lws_Hils_IN_Mode_Operation_Init;

        /* Entry 'Mode_Operation_Init': (':5237:124') */
        /*  Hils Running */
        /* (':5237:124:4') HilsStatus.HilsRunning = 1; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning = 1U;

        /* Entry Internal 'HilsMode_EndChk': (':5237:605') */
        /* Transition: (':5237:619') */
        /* Entry 'OP_Mode_End': (':5237:618') */
        /* Entry Internal 'OutSet_Control': (':5237:415') */
        /* Transition: (':5237:603') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_OutSet_Control =
          Lws_HilsCtrl_240_IN_Output_Init;

        /* Entry 'Output_Init': (':5237:568') */
        /*  Output Init */
        /* (':5237:568:4') HilsDO.FilterSwitch_Return = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_Return = 0U;

        /* (':5237:568:5') HilsDO.FilterSwitch_BoostPump = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_BoostPump = 0U;

        /* (':5237:568:6') HilsDO.FilterSwitch_WinchDrv = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_WinchDrv = 0U;

        /* (':5237:568:7') HilsDO.FilterSwitch_DropLift = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_DropLift = 0U;

        /* (':5237:568:8') HilsDO.AlighLimit_RightA = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightA = 0U;

        /* (':5237:568:9') HilsDO.AlighLimit_RightB = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightB = 0U;

        /* (':5237:568:10') HilsDO.AlighLimit_LeftA = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftA = 0U;

        /* (':5237:568:11') HilsDO.AlighLimit_LeftB = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftB = 0U;

        /* (':5237:568:12') HilsDO.FiveTurn_Switch = 1; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FiveTurn_Switch = 1U;

        /* (':5237:568:13') HilsDO.PValveError_WinchPw = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PValveError_WinchPw = 0U;

        /* (':5237:568:14') HilsStatus.PValveErr_Algin = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Algin = 0U;

        /* (':5237:568:15') HilsStatus.PValveErr_Emg = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Emg = 0U;

        /* (':5237:568:16') HilsStatus.PValveErr_MC01 = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC01 = 0U;

        /* (':5237:568:17') HilsStatus.PValveErr_MC02 = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC02 = 0U;

        /* (':5237:568:18') HilsStatus.PValveErr_SC01 = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC01 = 0U;

        /* (':5237:568:19') HilsStatus.PValveErr_SC02 = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC02 = 0U;

        /* (':5237:568:20') HilsDO.PreSwitch_PreOver = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_PreOver = 0U;
        break;

       case 2:
        /* (':5237:118:1') sf_internal_predicateOutput = HilsMode.Op_Mode == 2; */
        /* Transition: (':5237:118') */
        /* Exit Internal 'OP_Mode_Stop': (':5237:90') */
        Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
          Lws_HilsCtrl_2_IN_OP_Mode_Check;
        break;

       default:
        /* During 'OP_Mode_Convert': (':5237:49') */
        /* (':5237:49:3') if((HilsCmd.HilsMode_Start == 1) && (HilsCmd.HilsMode_Stop == 0)) */
        if ((((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Start) == 1)
            && (((int32_T)Lws_HilsCtrl_240218_v_1_0_DW.HilsCmd.HilsMode_Stop) ==
                0))
        {
          /*  Hils Mode Run */
          /* (':5237:49:5') HilsMode.Op_Mode = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode = 1U;

          /* (':5237:49:6') HilsDO.FiveTurn_Switch = 1; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FiveTurn_Switch = 1U;
        }
        else
        {
          /* (':5237:49:7') else */
          /*  출력변수들 초기화 상태에서 HILS 전환 명령 인가시 모드 천이한다. */
          /* (':5237:49:9') HilsStatus.Power_On = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.Power_On = 0U;

          /* (':5237:49:10') HilsStatus.WinchPower_On = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WinchPower_On = 0U;

          /* (':5237:49:11') HilsStatus.BoostPower_On = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BoostPower_On = 0U;

          /* (':5237:49:12') HilsStatus.DlPower_On = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.DlPower_On = 0U;

          /*  Pressure Switch Set */
          /* (':5237:49:14') HilsDO.PreSwitch_Boost = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_Boost = 0U;

          /* (':5237:49:15') HilsDO.PreSwitch_AlignDrv = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignDrv = 0U;

          /* (':5237:49:16') HilsDO.PreSwitch_DropLift = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_DropLift = 0U;

          /*  Analog output set */
          /* (':5237:49:18') Pressure_WinchPwBase = 0; */
          Lws_HilsCtrl_240218_v_1_0_B.Pressure_WinchPwBase = 0.0F;

          /* (':5237:49:19') Pressure_DropLiftPw = 0; */
          Lws_HilsCtrl_240218_v_1_0_B.Pressure_DropLiftPw = 0.0F;

          /* (':5237:49:20') OilFlow_DropLift = 0; */
          Lws_HilsCtrl_240218_v_1_0_B.OilFlow_DropLift = 0.0F;

          /*  Brake Lock status */
          /* (':5237:49:22') HilsDO.PreSwitch_AlignBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_AlignBk = 0U;

          /* (':5237:49:23') HilsDO.PreSwitch_MainBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_MainBk = 0U;

          /* (':5237:49:24') HilsDO.PreSwitch_SubBk = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_SubBk = 0U;

          /* (':5237:49:25') HilsStatus.AlignBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.AlignBk_Unlock = 0U;

          /* (':5237:49:26') HilsStatus.WdBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.WdBk_Unlock = 0U;

          /* (':5237:49:27') HilsStatus.BandBk_Unlock = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.BandBk_Unlock = 0U;

          /*  Output Set Init */
          /* (':5237:49:30') HilsDO.FilterSwitch_Return = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_Return = 0U;

          /* (':5237:49:31') HilsDO.FilterSwitch_BoostPump = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_BoostPump = 0U;

          /* (':5237:49:32') HilsDO.FilterSwitch_WinchDrv = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_WinchDrv = 0U;

          /* (':5237:49:33') HilsDO.FilterSwitch_DropLift = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FilterSwitch_DropLift = 0U;

          /* (':5237:49:34') HilsDO.AlighLimit_RightA = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightA = 0U;

          /* (':5237:49:35') HilsDO.AlighLimit_RightB = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_RightB = 0U;

          /* (':5237:49:36') HilsDO.AlighLimit_LeftA = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftA = 0U;

          /* (':5237:49:37') HilsDO.AlighLimit_LeftB = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.AlighLimit_LeftB = 0U;

          /* (':5237:49:38') HilsDO.FiveTurn_Switch = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.FiveTurn_Switch = 0U;

          /* (':5237:49:39') HilsDO.PValveError_WinchPw = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PValveError_WinchPw = 0U;

          /* (':5237:49:40') HilsStatus.PValveErr_Algin = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Algin = 0U;

          /* (':5237:49:41') HilsStatus.PValveErr_Emg = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_Emg = 0U;

          /* (':5237:49:42') HilsStatus.PValveErr_MC01 = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC01 = 0U;

          /* (':5237:49:43') HilsStatus.PValveErr_MC02 = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_MC02 = 0U;

          /* (':5237:49:44') HilsStatus.PValveErr_SC01 = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC01 = 0U;

          /* (':5237:49:45') HilsStatus.PValveErr_SC02 = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.PValveErr_SC02 = 0U;

          /* (':5237:49:46') HilsDO.PreSwitch_PreOver = 0; */
          Lws_HilsCtrl_240218_v_1_0_DW.HilsDO.PreSwitch_PreOver = 0U;
        }
        break;
      }
      break;

     default:
      /* During 'Sys_Init': (':5237:10') */
      /* (':5237:93:1') sf_internal_predicateOutput = after(0.5,sec); */
      if (((uint32_T)Lws_HilsCtrl_240218_v_1_0_DW.temporalCounter_i1) >= 200U)
      {
        /* Transition: (':5237:93') */
        /* Exit 'Sys_Init': (':5237:10') */
        /* (':5237:10:3') HilsMode.Op_Mode = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode = 0U;

        /*  Hils Mode */
        /* (':5237:10:4') HilsStatus.HilsRunning = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning = 0U;

        /*  Hils Status */
        Lws_HilsCtrl_240218_v_1_0_DW.is_c10_Lws_HilsCtrl_240218_v_1_ =
          Lws_HilsCtrl_24_IN_OP_Mode_Stop;

        /* Entry Internal 'OP_Mode_Stop': (':5237:90') */
        /* Transition: (':5237:94') */
        /* Entry 'OP_Mode_Convert': (':5237:49') */
      }
      else
      {
        /* (':5237:10:3') HilsMode.Op_Mode = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsMode.Op_Mode = 0U;

        /*  Hils Mode */
        /* (':5237:10:4') HilsStatus.HilsRunning = 0; */
        Lws_HilsCtrl_240218_v_1_0_DW.HilsStatus.HilsRunning = 0U;

        /*  Hils Status */
      }
      break;
    }
  }

  /* End of Chart: 'Hils_SequenceCtrl' (':5237') */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
