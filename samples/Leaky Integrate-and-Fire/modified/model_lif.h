#ifndef __MODEL_LIF_H__
#define __MODEL_LIF_H__

#include "FixedPoint.h"

#define LOG_P1                  (8)
#define LOG_P2                  (16)
#define P1                      (1 << LOG_P1)
#define P2                      (1 << LOG_P2)



typedef struct
{
    // Membrane potential constants and variables
	//MODIFIED: transformed int into int16_16
    int16_16 v;              // * P2
    int16_16 v_rest;         // * P2
    int16_16 v_reset;        // * P2
    int16_16 v_thresh;       // * P2
    int16_16 v_decay;        // 1 / membrane_tau * P2
    int16_16 v_resistance;   // * P2
    int refrac_tau;     // * 1
    int refrac_clock;   // * 1
    // Injection current
    int16_16 bias_current;   // * P2
    // Synaptic time constants
    int16_16 exci_decay;     // 1 / exci_tau * P2
    int16_16 inhi_decay;     // 1 / inhi_tau * P2
} neuron_t;

// Input current control through SDP
void set_bias_value(uint population, int value);
void set_bias_values(uint population_id, uint length, uint * payload);

// spike count
#define OUTPUT_STATISTIC_TIMER 0x3F     // Time interval to collect spike counts
int * spike_count;              // used by recorders


#endif
