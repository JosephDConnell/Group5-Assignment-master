/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : TU2.c
**     Project     : Assignment 2
**     Processor   : MK20DX128VLH5
**     Component   : TimerUnit_LDD
**     Version     : Component 01.164, Driver 01.11, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-10-17, 15:12, # CodeGen: 1
**     Abstract    :
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
**     Settings    :
**          Component name                                 : TU2
**          Module name                                    : FTM1
**          Counter                                        : FTM1_CNT
**          Counter direction                              : Up
**          Counter width                                  : 16 bits
**          Value type                                     : uint16_t
**          Input clock source                             : Internal
**            Counter frequency                            : Auto select
**          Counter restart                                : On-match
**            Period device                                : FTM1_MOD
**            Period                                       : 12.5 ms
**            Interrupt                                    : Disabled
**          Channel list                                   : 1
**            Channel 0                                    : 
**              Mode                                       : Compare
**                Compare                                  : FTM1_C1V
**                Offset                                   : 0 �s
**                Output on compare                        : Set
**                  Output on overrun                      : Clear
**                  Initial state                          : Low
**                  Output pin                             : PTA13/LLWU_P4/FTM1_CH1/I2S0_TX_FS/FTM1_QD_PHB
**                  Output pin signal                      : 
**                Interrupt                                : Disabled
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Auto initialization                          : no
**            Event mask                                   : 
**              OnCounterRestart                           : Disabled
**              OnChannel0                                 : Disabled
**              OnChannel1                                 : Disabled
**              OnChannel2                                 : Disabled
**              OnChannel3                                 : Disabled
**              OnChannel4                                 : Disabled
**              OnChannel5                                 : Disabled
**              OnChannel6                                 : Disabled
**              OnChannel7                                 : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init               - LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr);
**         GetPeriodTicks     - LDD_TError TU2_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType...
**         GetCounterValue    - TU2_TValueType TU2_GetCounterValue(LDD_TDeviceData *DeviceDataPtr);
**         SetOffsetTicks     - LDD_TError TU2_SetOffsetTicks(LDD_TDeviceData *DeviceDataPtr, uint8_t...
**         GetOffsetTicks     - LDD_TError TU2_GetOffsetTicks(LDD_TDeviceData *DeviceDataPtr, uint8_t...
**         SelectOutputAction - LDD_TError TU2_SelectOutputAction(LDD_TDeviceData *DeviceDataPtr, uint8_t...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TU2.c
** @version 01.11
** @brief
**          This TimerUnit component provides a low level API for unified hardware access across
**          various timer devices using the Prescaler-Counter-Compare-Capture timer structure.
*/         
/*!
**  @addtogroup TU2_module TU2 module documentation
**  @{
*/         

/* MODULE TU2. */

#include "TU2.h"
/* {Default RTOS Adapter} No RTOS includes */
#include "IO_Map.h"

#ifdef __cplusplus
extern "C" {
#endif 

/* List of channels used by component */
static const uint8_t ChannelDevice[TU2_NUMBER_OF_CHANNELS] = {0x01U};

/* Table of channels mode / 0 - compare mode, 1 - capture mode */
static const uint8_t ChannelMode[TU2_NUMBER_OF_CHANNELS] = {0x00U};


typedef struct {
  uint8_t InitCntr;                    /* Number of initialization */
  LDD_TUserData *UserDataPtr;          /* RTOS device data structure */
} TU2_TDeviceData;

typedef TU2_TDeviceData *TU2_TDeviceDataPtr; /* Pointer to the device data structure. */

/* {Default RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static TU2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;

#define AVAILABLE_PIN_MASK (LDD_TPinMask)(TU2_CHANNEL_0_PIN)
#define LAST_CHANNEL 0x00U

/* Internal method prototypes */
/*
** ===================================================================
**     Method      :  TU2_Init (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc. If the
**         property ["Enable in init. code"] is set to "yes" value then
**         the device is also enabled (see the description of the
**         [Enable] method). In this case the [Enable] method is not
**         necessary and needn't to be generated. This method can be
**         called only once. Before the second call of Init the [Deinit]
**         must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Pointer to the dynamically allocated private
**                           structure or NULL if there was an error.
*/
/* ===================================================================*/
LDD_TDeviceData* TU2_Init(LDD_TUserData *UserDataPtr)
{
  TU2_TDeviceData *DeviceDataPrv;

  if (PE_LDD_DeviceDataList[PE_LDD_COMPONENT_TU2_ID] == NULL) {
    /* Allocate device structure */
    /* {Default RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
    DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
    DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
    DeviceDataPrv->InitCntr = 1U;      /* First initialization */
  }
  else {
    /* Memory is already allocated */
    DeviceDataPrv = (TU2_TDeviceDataPtr) PE_LDD_DeviceDataList[PE_LDD_COMPONENT_TU2_ID];
    DeviceDataPrv->UserDataPtr = UserDataPtr; /* Store the RTOS device structure */
    DeviceDataPrv->InitCntr++;         /* Increment counter of initialization */
    return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
  }
  /* SIM_SCGC6: FTM1=1 */
  SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;
  /* FTM1_MODE: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,FAULTIE=0,FAULTM=0,CAPTEST=0,PWMSYNC=0,WPDIS=1,INIT=0,FTMEN=0 */
  FTM1_MODE = (FTM_MODE_FAULTM(0x00) | FTM_MODE_WPDIS_MASK); /* Set up mode register */
  /* FTM1_SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TOF=0,TOIE=0,CPWMS=0,CLKS=0,PS=0 */
  FTM1_SC = (FTM_SC_CLKS(0x00) | FTM_SC_PS(0x00)); /* Clear status and control register */
  /* FTM1_CNTIN: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,INIT=0 */
  FTM1_CNTIN = FTM_CNTIN_INIT(0x00);   /* Clear counter initial register */
  /* FTM1_CNT: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,COUNT=0 */
  FTM1_CNT = FTM_CNT_COUNT(0x00);      /* Reset counter register */
  /* FTM1_C0SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM1_C0SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM1_C1SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=0,MSA=0,ELSB=0,ELSA=0,??=0,DMA=0 */
  FTM1_C1SC = 0x00U;                   /* Clear channel status and control register */
  /* FTM1_MOD: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,MOD=0xFFFF */
  FTM1_MOD = FTM_MOD_MOD(0xFFFF);      /* Set up modulo register */
  /* FTM1_C1SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,CHF=0,CHIE=0,MSB=1,MSA=0,ELSB=1,ELSA=1,??=0,DMA=0 */
  FTM1_C1SC = (FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK); /* Set up channel status and control register */
  /* FTM1_C1V: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,VAL=0 */
  FTM1_C1V = FTM_CnV_VAL(0x00);        /* Set up channel value register */
  /* PORTA_PCR13: ISF=0,MUX=3 */
  PORTA_PCR13 = (uint32_t)((PORTA_PCR13 & (uint32_t)~(uint32_t)(
                 PORT_PCR_ISF_MASK |
                 PORT_PCR_MUX(0x04)
                )) | (uint32_t)(
                 PORT_PCR_MUX(0x03)
                ));
  /* FTM1_SC: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,TOF=0,TOIE=0,CPWMS=0,CLKS=1,PS=2 */
  FTM1_SC = (FTM_SC_CLKS(0x01) | FTM_SC_PS(0x02)); /* Set up status and control register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_TU2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the device data structure */
}

/*
** ===================================================================
**     Method      :  TU2_GetPeriodTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the number of counter ticks before re-initialization.
**         See also method [SetPeriodTicks]. This method is available
**         only if the property ["Counter restart"] is switched to
**         'on-match' value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         TicksPtr        - Pointer to return value of the
**                           number of counter ticks before
**                           re-initialization
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_GetPeriodTicks(LDD_TDeviceData *DeviceDataPtr, TU2_TValueType *TicksPtr)
{
  uint16_t tmp;

  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  tmp = (uint16_t)(FTM_PDD_ReadModuloReg(FTM1_BASE_PTR));
  *TicksPtr = (TU2_TValueType)++tmp;
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TU2_GetCounterValue (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the content of counter register. This method can be
**         used both if counter is enabled and if counter is disabled.
**         The method is not available if HW doesn't allow reading of
**         the counter.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Counter value (number of counted ticks).
*/
/* ===================================================================*/
TU2_TValueType TU2_GetCounterValue(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  return (TU2_TValueType)FTM_PDD_ReadCounterReg(FTM1_BASE_PTR);
}

/*
** ===================================================================
**     Method      :  TU2_SetOffsetTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Sets the new offset value to channel specified by the
**         parameter ChannelIdx. It is user responsibility to use value
**         below selected period. This method is available when at
**         least one channel is configured.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ChannelIdx      - Index of the component
**                           channel.
**     @param
**         Ticks           - Number of counter ticks to compare
**                           match.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_PARAM_INDEX - ChannelIdx parameter is
**                           out of possible range.
**                           ERR_NOTAVAIL -  The compare mode is not
**                           selected for selected channel
**                           ERR_PARAM_TICKS - Ticks parameter is out of
**                           possible range.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_SetOffsetTicks(LDD_TDeviceData *DeviceDataPtr, uint8_t ChannelIdx, TU2_TValueType Ticks)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Parameter test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (ChannelIdx > LAST_CHANNEL) {     /* Is the channel index out of range? */
    return ERR_PARAM_INDEX;            /* If yes then error */
  }
  if ((ChannelMode[ChannelIdx]) != 0U) { /* Is the channel in compare mode? */
    return ERR_NOTAVAIL;               /* If not then error */
  }
  FTM_PDD_WriteChannelValueReg(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], (uint16_t)Ticks);
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TU2_GetOffsetTicks (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Returns the number of counter ticks to compare match channel
**         specified by the parameter ChannelIdx. See also method
**         [SetOffsetTicks]. This method is available when at least one
**         channel is configured.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ChannelIdx      - Index of the component
**                           channel.
**     @param
**         TicksPtr        - Pointer to return value of the
**                           number of counter ticks to compare match.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK 
**                           ERR_PARAM_INDEX - ChannelIdx parameter is
**                           out of possible range.
**                           ERR_NOTAVAIL -  The compare mode is not
**                           selected for selected channel.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_GetOffsetTicks(LDD_TDeviceData *DeviceDataPtr, uint8_t ChannelIdx, TU2_TValueType *TicksPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Parameter test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (ChannelIdx > LAST_CHANNEL) {     /* Is the channel index out of range? */
    return ERR_PARAM_INDEX;            /* If yes then error */
  }
  if ((ChannelMode[ChannelIdx]) != 0U) { /* Is the channel in compare mode? */
    return ERR_NOTAVAIL;               /* If not then error */
  }
  *TicksPtr = (TU2_TValueType)(FTM_PDD_ReadChannelValueReg(FTM1_BASE_PTR, ChannelDevice[ChannelIdx]));
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TU2_SelectOutputAction (component TimerUnit_LDD)
*/
/*!
**     @brief
**         Sets the type of compare match and counter overflow action
**         on channel output. This method is available when at least
**         one channel is configured.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ChannelIdx      - Index of the component
**                           channel.
**     @param
**         CompareAction   - Select output action
**                           on compare match
**     @param
**         CounterAction   - Select output action
**                           on counter overflow
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_PARAM_INDEX - ChannelIdx parameter is
**                           out of possible range
**                           ERR_NOTAVAIL -  Action is not possible on
**                           selected channel or counter. Supported
**                           combinations are HW specific.
**                           ERR_SPEED - The component does not work in
**                           the active clock configuration
*/
/* ===================================================================*/
LDD_TError TU2_SelectOutputAction(LDD_TDeviceData *DeviceDataPtr, uint8_t ChannelIdx, LDD_TimerUnit_TOutAction CompareAction, LDD_TimerUnit_TOutAction CounterAction)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* Parameter test - this test can be disabled by setting the "Ignore range checking"
     property to the "yes" value in the "Configuration inspector" */
  if (ChannelIdx > LAST_CHANNEL) {     /* Is the channel index out of range? */
    return ERR_PARAM_INDEX;            /* If yes then error */
  }
  if ((ChannelMode[ChannelIdx]) != 0U) { /* Is the channel in compare mode? */
    return ERR_NOTAVAIL;               /* If not then error */
  }
  switch (CounterAction) {
    case OUTPUT_NONE:
      FTM_PDD_SelectChannelMode(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_OUTPUT_TOGGLE);
      switch (CompareAction) {
        case OUTPUT_NONE:
          FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_NONE);
          break;
        case OUTPUT_TOGGLE:
          FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_RISING);
          break;
        case OUTPUT_CLEAR:
          FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_FALLING);
          break;
        case OUTPUT_SET:
          FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_BOTH);
          break;
        default:
          return ERR_NOTAVAIL;
      }
      break;
    case OUTPUT_CLEAR:
      if (CompareAction != OUTPUT_SET) {
        return ERR_NOTAVAIL;
      }
      FTM_PDD_SelectChannelMode(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_OUTPUT_CLEAR);
      FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_BOTH);
      break;
    case OUTPUT_SET:
      if (CompareAction != OUTPUT_CLEAR) {
        return ERR_NOTAVAIL;
      }
      FTM_PDD_SelectChannelMode(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_OUTPUT_SET);
      FTM_PDD_SelectChannelEdgeLevel(FTM1_BASE_PTR, ChannelDevice[ChannelIdx], FTM_PDD_EDGE_FALLING);
      break;
    default:
      return ERR_NOTAVAIL;
  }
  return ERR_OK;                       /* OK */
}

/* END TU2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
