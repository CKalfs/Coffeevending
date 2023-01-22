#ifndef CVMFSM_FUNCTIONS_H
#define CVMFSM_FUNCTIONS_H
#include "fsm_functions/fsm.h"

/// FSM Initialisation and start function

/*!
 * Function to configure and modeling the CVM FSM
 * \brief cvmInitialiseFSM
 */

void cvmInitialiseFSM();

/*!
 * \brief cvmStartFSM
 * \param start_state
 * \param start_event
 */
void cvmStartFSM(state_t start_state, event_t start_event);

#endif
