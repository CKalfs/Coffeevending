char * stateEnumToText[] =
{
    "S_NO",                         ///< Used for initialisation if state is not yet known
    "S_START_PROGRAM",                      ///< Initial state
    "S_RESTART_PROGRAM",            ///< Cancel program
    "S_INITIALISESUBSYSTEMS",       ///< Initialised subsystems
    "S_CONFIGURE",                  ///< Ask user for action
    "S_PROCESS_Espresso",                ///< Handle the 20c insert
    "S_PROCESS_Cappuccino",                ///< Handle the 50c insert
    "S_PROCESS_HotChocolate",                ///< Handle the 100c insert
    "S_Inserted_Money",               ///< Wait for the user to insert coins
    "S_SHUTDOWN_SYSTEM",            ///< Exception or system exit shutdown requested
    "S_Choose_Coffee",
    "S_Take_Out",
    "S_PROCESS_25C",                ///< Handle the 20c insert
    "S_PROCESS_50C",                ///< Handle the 50c insert
    "S_PROCESS_100C",                ///< Handle the 100c insert
};

