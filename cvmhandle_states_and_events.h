#ifndef CVMHANDLE_STATES_AND_EVENTS_H
#define CVMHANDLE_STATES_AND_EVENTS_H

/*!
 * Functions to handle the states, events and transitions
*/

/*!
 * \brief S_InitialiseSubsystems_onEntry
 *
 * Initialise the subsystems of the CVM
 * Initialises the User interface, coladispenser and the coinaccptor
 */
#include <stdint.h>
void S_InitialiseSubsystems_onEntry(void);
/*!
 * \brief S_InitialiseSubsystems_onExit
 */
void S_InitialiseSubsystems_onExit(void);
/*!
 * \brief S_Configure_onEntry
 */
void S_Choose_Coffee_onEntry(void);
/*!
 * \brief S_Configure_onExit
 */
void S_Choose_Coffee_onExit(void);
/*!
 * \brief S_WaitForCoins_onEntry
 */
void S_Process_Espresso_onEntry(void);
/*!
 * \brief S_WaitForCoins_onExit
 */
void S_Process_Espresso_onExit(void);
/*!
 * \brief S_Process_20C_onEntry
 */
void S_Process_Cappucino_onEntry(void);
/*!
 * \brief S_Process_20C_onExit
 */
void S_Process_Cappucino_onExit(void);
/*!
 * \brief S_Process_50C_onEntry
 */
void S_Process_HotChocolate_onEntry(void);
/*!
 * \brief S_Process_50C_onExit
 */
void S_Process_HotChocolate_onExit(void);
/*!
 * \brief S_Process_100C_onEntry
 */
void S_Process_INSERTED_MONEY_onEntry(void);
/*!
 * \brief S_Process_100C_onExit
 */
void S_Process_INSERTED_MONEY_onExit(void);
/*!
 * \brief S_ShutdownSystem
 * \param exitCode
 * \abstract Handles: Exception or graceful shutdown
 */
void S_Start_program_onEntry(void);
void S_Start_program_onExit(void);
void S_RestartProgram_onEntry(void);
void S_RestartProgram_onExit(void);
void S_ShutdownSystem(int exitCode);

///helper functions
/*!
 * \brief delay_ms
 * \param d
 * \abstract helper function to create a program delay in miliseconds
 */
void delay_ms(uint32_t d);


#endif
