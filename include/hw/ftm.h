/*
 * ftm.h
 *
 *  Created on: 15 sep. 2017
 *      Author: SERAGUD
 */

#ifndef INCLUDE_HW_FTM_H_
#define INCLUDE_HW_FTM_H_

#include "hw/common.h"
#include "types.h"

/// FTM - Register Layout Typedef
typedef struct {
	__IO uint32_t SC; /**< Status And Control, offset: 0x0 */
	__IO uint32_t CNT; /**< Counter, offset: 0x4 */
	__IO uint32_t MOD; /**< Modulo, offset: 0x8 */
	struct { /* offset: 0xC, array step: 0x8 */
		__IO uint32_t CnSC; /**< Channel (n) Status And Control, array offset: 0xC, array step: 0x8 */
		__IO uint32_t CnV; /**< Channel (n) Value, array offset: 0x10, array step: 0x8 */
	} CONTROLS[8];__IO uint32_t CNTIN; /**< Counter Initial Value, offset: 0x4C */
	__IO uint32_t STATUS; /**< Capture And Compare Status, offset: 0x50 */
	__IO uint32_t MODE; /**< Features Mode Selection, offset: 0x54 */
	__IO uint32_t SYNC; /**< Synchronization, offset: 0x58 */
	__IO uint32_t OUTINIT; /**< Initial State For Channels Output, offset: 0x5C */
	__IO uint32_t OUTMASK; /**< Output Mask, offset: 0x60 */
	__IO uint32_t COMBINE; /**< Function For Linked Channels, offset: 0x64 */
	__IO uint32_t DEADTIME; /**< Deadtime Insertion Control, offset: 0x68 */
	__IO uint32_t EXTTRIG; /**< FTM External Trigger, offset: 0x6C */
	__IO uint32_t POL; /**< Channels Polarity, offset: 0x70 */
	__IO uint32_t FMS; /**< Fault Mode Status, offset: 0x74 */
	__IO uint32_t FILTER; /**< Input Capture Filter Control, offset: 0x78 */
	__IO uint32_t FLTCTRL; /**< Fault Control, offset: 0x7C */
	__IO uint32_t QDCTRL; /**< Quadrature Decoder Control And Status, offset: 0x80 */
	__IO uint32_t CONF; /**< Configuration, offset: 0x84 */
	__IO uint32_t FLTPOL; /**< FTM Fault Input Polarity, offset: 0x88 */
	__IO uint32_t SYNCONF; /**< Synchronization Configuration, offset: 0x8C */
	__IO uint32_t INVCTRL; /**< FTM Inverting Control, offset: 0x90 */
	__IO uint32_t SWOCTRL; /**< FTM Software Output Control, offset: 0x94 */
	__IO uint32_t PWMLOAD; /**< FTM PWM Load, offset: 0x98 */
}__attribute__((__packed__)) ftm_t;

enum {
	HWFTM_SC_CPWMS_Shift = 5,
	HWFTM_SC_CPWMS_Mask = 1 << HWFTM_SC_CPWMS_Shift,

	HWFTM_SC_TOIE_Shift = 6,
	HWFTM_SC_TOIE_Mask = 1 << HWFTM_SC_TOIE_Shift,

	HWFTM_SC_CLKS_Shift = 3,
	HWFTM_SC_CLKS_Mask = 0x3 << HWFTM_SC_CLKS_Shift,

	HWFTM_SC_CLKS_NONE = 0 << HWFTM_SC_CLKS_Shift,
	HWFTM_SC_CLKS_SYS = 1 << HWFTM_SC_CLKS_Shift,
	HWFTM_SC_CLKS_FIXED = 2 << HWFTM_SC_CLKS_Shift,
	HWFTM_SC_CLKS_EXTERNAL = 3 << HWFTM_SC_CLKS_Shift,

	HWFTM_SC_PS_Mask = 0x7,
	HWFTM_SC_PS_Div1 = 0,
	HWFTM_SC_PS_Div2 = 1,
	HWFTM_SC_PS_Div4 = 2,
	HWFTM_SC_PS_Div8 = 3,
	HWFTM_SC_PS_Div16 = 4,
	HWFTM_SC_PS_Div32 = 5,
	HWFTM_SC_PS_Div64 = 6,
	HWFTM_SC_PS_Div128 = 7,
} hw_ftm_sc_fields_t;

enum {
	HWFTM_CONTROL_DMA_Mask = 1,

	HWFTM_CONTROL_ICRST_Shift = 1,
	HWFTM_CONTROL_ICRST_Mask = 1 << HWFTM_CONTROL_ICRST_Shift,

	HWFTM_CONTROL_ELS_Shift = 2,
	HWFTM_CONTROL_ELS_Mask = 3 << HWFTM_CONTROL_ELS_Shift,

	HWFTM_CONTROL_MS_Shift = 4,
	HWFTM_CONTROL_MS_Mask = 3 << HWFTM_CONTROL_MS_Shift,

	HWFTM_CONTROL_CHIE_Shift = 6,
	HWFTM_CONTROL_CHIE_Mask = 1 << HWFTM_CONTROL_CHIE_Shift,

	HWFTM_CONTROL_CHF_Shift = 7,
	HWFTM_CONTROL_CHF_Mask = 1 << HWFTM_CONTROL_CHF_Shift,

	HWFTM_CONTROL_MS_CAPTURE = 0 << HWFTM_CONTROL_MS_Shift,
	HWFTM_CONTROL_MS_COMPARE = 1 << HWFTM_CONTROL_MS_Shift,

	HWFTM_CONTROL_ELS_CaptureRising = 1 << HWFTM_CONTROL_ELS_Shift,
	HWFTM_CONTROL_ELS_CaptureFalling = 2 << HWFTM_CONTROL_ELS_Shift,
	HWFTM_CONTROL_ELS_CaptureBoth = 3 << HWFTM_CONTROL_ELS_Shift,

	HWFTM_CONTROL_ELS_CompareToggle = 1 << HWFTM_CONTROL_ELS_Shift,
	HWFTM_CONTROL_ELS_CompareClear = 2 << HWFTM_CONTROL_ELS_Shift,
	HWFTM_CONTROL_ELS_CompareSet = 3 << HWFTM_CONTROL_ELS_Shift,


	HWFTM_MODE_WPDIS_Shift = 2,
	HWFTM_MODE_WPDIS_Mask = 1 << HWFTM_MODE_WPDIS_Shift,

	HWFTM_MODE_FTMEN_Mask = 1,
} hw_ftm_contol_fields_t;

volatile ftm_t * const volatile hw_ftm0 = (ftm_t *) Memmap_FTM0_Addr;

volatile ftm_t * const volatile hw_ftm1 = (ftm_t *) Memmap_FTM1_Addr;

volatile ftm_t * const volatile hw_ftm2 = (ftm_t *) Memmap_FTM2_Addr;

volatile ftm_t * const volatile hw_ftm3 = (ftm_t *) Memmap_FTM3_Addr;

#endif /* INCLUDE_HW_FTM_H_ */
