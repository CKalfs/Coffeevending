#ifndef STATES_H
#define STATES_H

typedef enum {
    S_NO,                         ///< Used for initialisation if state is not yet known
    S_START_PROGRAM,                      ///< Initial state
    S_RESTART_PROGRAM,
    S_INITIALISESUBSYSTEMS,       ///< Initialised subsystems
    S_CONFIGURE,                  ///< Ask user for action
    S_PROCESS_ESPRESSO,
    S_PROCESS_CAPPUCINO,
    S_PROCESS_HOTCHOCOLATE,
    S_INSERTED_MONEY,
    S_CHOOSE_COFFEE,
    S_STOP, ///< Ends program
    S_TAKE_OUT,
    S_PROCESS_25C,                ///< Handle the 20c insert
    S_PROCESS_50C,                ///< Handle the 50c insert
    S_PROCESS_100C,
    //end
} state_t;

#endif
