/*
 * Utils.c
 *
 *  Created on: May 16, 2022
 *      Author: fame
 */

#include <Library/Utils.h>

int32_t Unwrap(uint16_t pulse, uint16_t prev_pulse) {
	int32_t dPulse = pulse - prev_pulse;
	if (dPulse >= 8192){
		dPulse -= 16384;
	}
	else if (dPulse <= -8192){
		dPulse += 16384;
	}

//	if (pulse - prev_pulse > 8192) {
//		dPulse = (16384 + (prev_pulse - pulse));
//	} else if ( pulse -  prev_pulse < -8192) {
//		dPulse = 16384 - (prev_pulse - pulse);
//	} else {
//		dPulse =  pulse -  prev_pulse;
//	}

	return dPulse;
}
