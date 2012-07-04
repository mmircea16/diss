#ifndef __MODEL_LIF_H__
#define __MODEL_LIF_H__



#define LOG_P1                  (8)
#define LOG_P2                  (16)
#define P1                      (1 << LOG_P1)
#define P2                      (1 << LOG_P2)



typedef struct
{
    // Membrane potential constants and variables
    int v;              // * P2
    int v_rest;         // * P2
    int v_reset;        // * P2
    int v_thresh;       // * P2
    int v_decay;        // 1 / membrane_tau * P2
    int v_resistance;   // * P2
    int refrac_tau;     // * 1
    int refrac_clock;   // * 1
    // Injection current
    int bias_current;   // * P2
    // Synaptic time constants
    int exci_decay;     // 1 / exci_tau * P2
    int inhi_decay;     // 1 / inhi_tau * P2
} neuron_t;

// Input current control through SDP
void set_bias_value(uint population, int value);
void set_bias_values(uint population_id, uint length, uint * payload);

// spike count
#define OUTPUT_STATISTIC_TIMER 0x3F     // Time interval to collect spike counts
int * spike_count;              // used by recorders


#endif
