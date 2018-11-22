/// \file delay.c
///
/// Fast peripheral clock is used as source.
///
/// For 1us tick, TODO
/// TODO
///

#include "driv/delay/delay.h"
#include "driv/cpu/cpu.h"
#include "hw/hw.h"

void delay_init(void) {
	// Enable clock gating
	hw_sim->SCGC6 |= SIM_SCGC6_FTM0_Mask;

	// Disable FTM
	hw_ftm0->SC &= ~HWFTM_SC_CLKS_Mask;

	/// TPM compatibility
	hw_ftm0->MODE |= HWFTM_MODE_WPDIS_Mask;
	hw_ftm0->MODE &= ~HWFTM_MODE_FTMEN_Mask;
	hw_ftm0->MODE &= ~HWFTM_MODE_WPDIS_Mask;

	// Disable synchronization, dead time, dual edge capture mode, fault control
	hw_ftm0->COMBINE = 0;

	hw_ftm0->QDCTRL = 0;

	// Disable PWM load, software control of output pin and inversion
	hw_ftm0->PWMLOAD = 0;
	hw_ftm0->SWOCTRL = 0;
	hw_ftm0->INVCTRL = 0;

	// Set output init states to 0
	hw_ftm0->OUTINIT = 0;

	// Mask all outputs
	hw_ftm0->OUTMASK = 0xFF;

	// Initialize all channels
	for (uint_t channel = 0; channel < 8; channel++) {
		// Disable channel interrupt
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_CHIE_Mask;

		// Disable DMA transfer for this channel
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_DMA_Mask;

		// Disable counter reset on input capture event
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_ICRST_Mask;

		// Disable action on pin
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_ELS_Mask;
		hw_ftm0->CONTROLS[channel].CnSC |= HWFTM_CONTROL_ELS_CompareToggle;

		// Set mode to compare
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_MS_Mask;
		hw_ftm0->CONTROLS[channel].CnSC |= HWFTM_CONTROL_MS_COMPARE;

		// Clear channel flag
		hw_ftm0->CONTROLS[channel].CnSC &= ~HWFTM_CONTROL_CHF_Mask;

		// Reset channel trigger value
		hw_ftm0->CONTROLS[channel].CnV = 0;
	}

	// Set counter initial value
	hw_ftm0->CNTIN = 0;

	// Set counter overflow value
	hw_ftm0->MOD = 0xFFFF;

	// Disable timer overflow interrupt
	hw_ftm0->SC &= ~HWFTM_SC_TOIE_Mask;

	// Up counting mode
	hw_ftm0->SC &= ~HWFTM_SC_CPWMS_Mask;

	// Clock prescale factor
	hw_ftm0->SC &= ~HWFTM_SC_PS_Mask;
	hw_ftm0->SC |= HWFTM_SC_PS_Div128;	// TODO adjust this to get 1 us

	// Enable FTM by selecting source clock
	hw_ftm0->SC &= ~HWFTM_SC_CLKS_Mask;
	hw_ftm0->SC |= HWFTM_SC_CLKS_SYS;
}

uint32_t delay_get_current_time(void) {
	// Return current COUNT value
	return hw_ftm0->CNT & 0xFFFF;
}

enum {
	DELAY_CHANNEL_MONITOR = 0,
	DELAY_CHANNEL_WORKHORSE = 1,
	DELAY_CHANNEL_DIGSAFEQ = 2,
} delay_channel_t;

void delay_us_workhorse(uint16_t const us) {
	const uint8_t ch = DELAY_CHANNEL_WORKHORSE;

	// TODO disable interrupts

	// Disable channel
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;
	// Enable channel in compare mode
	hw_ftm0->CONTROLS[ch].CnSC |= HWFTM_CONTROL_MS_COMPARE;

	// Reset the channel event flag
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;

	// Set the compare register value
	uint16_t const newV =  hw_ftm0->CNT + us;
	hw_ftm0->CONTROLS[ch].CnV = newV;

	// TODO enable interrupts

	// Wait for timer to expire
	while ((hw_ftm0->CONTROLS[ch].CnSC & HWFTM_CONTROL_CHF_Mask) == 0) {
	};

	// Disable channel
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;

	// Reset the channel event flag
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;
}

void delay_ms_workhorse(uint32_t const ms) {
	for (uint64_t wait = 0; wait < ms; wait++) {
		delay_us_workhorse(1000);
	}
}

void delay_monitor_us(uint16_t const us) {
	const uint8_t ch = DELAY_CHANNEL_MONITOR;

	// TODO disable interrupts

	// Disable channel
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;
	// Enable channel in compare mode
	hw_ftm0->CONTROLS[ch].CnSC |= HWFTM_CONTROL_MS_COMPARE;

	// Reset the channel event flag
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;

	// Set the compare register value
	uint16_t const newV =  hw_ftm0->CNT + us;
	hw_ftm0->CONTROLS[ch].CnV = newV;

	// TODO enable interrupts

	// Wait for timer to expire
	while ((hw_ftm0->CONTROLS[ch].CnSC & HWFTM_CONTROL_CHF_Mask) == 0) {
	};

	// Disable channel
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;

	// Reset the channel event flag
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;
}

void delay_ms_monitor(uint16_t const ms) {
	for (uint32_t wait = 0; wait < ms; wait++) {
		delay_monitor_us(1000);
	}
}

void delay_us_nonblocking_monitor(uint16_t const us) {
	const uint8_t ch = DELAY_CHANNEL_MONITOR;

	// Disable channel
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_ELS_Mask;
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;
	// Enable channel in compare mode
	hw_ftm0->CONTROLS[ch].CnSC |= HWFTM_CONTROL_MS_COMPARE;

	// Reset the channel event flag
	hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;

	// Set the compare register value
	uint16_t const newV =  hw_ftm0->CNT + us;
	hw_ftm0->CONTROLS[ch].CnV = newV;
}

bool_t delay_hasExpired_us_nonblocking_monitor(void) {
	const uint8_t ch = DELAY_CHANNEL_MONITOR;

	// If channel event flag is set, delay has expired
	if ((hw_ftm0->CONTROLS[ch].CnSC & HWFTM_CONTROL_CHF_Mask) != 0) {
		// Disable channel
		hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_MS_Mask;

		// Reset the channel event flag
		hw_ftm0->CONTROLS[ch].CnSC &= ~HWFTM_CONTROL_CHF_Mask;
		return TRUE;
	}

	// If channel is not enabled, return that delay expired
	if((hw_ftm0->CONTROLS[ch].CnSC & HWFTM_CONTROL_MS_Mask) != HWFTM_CONTROL_MS_COMPARE) {
		return TRUE;
	}

	return FALSE;
}
