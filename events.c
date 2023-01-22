// global variables
char * eventEnumToText[] =
{
   "E_NO",                ///< Used for initialisation of an event variable
   "E_START",             ///< First event after example is switched on
   "E_CONTINUE",          ///< Initialising subsystems is ready
   "E_CONTINUE_ERROR",    ///< Initialisation error
   "E_Espresso",      ///< User action is open gate
   "E_Cappuccino",               ///< Coin acceptor detects 20c coin
   "E_HotChocolate",               ///< Coin acceptor detects 50c coin
   "E_100C",              ///< Coin acceptor detects 100c coin
   "E_50C",
   "E_25C",
   "E_NOT_ENOUGH",        ///< Total inserted money is not enough
   "E_ENOUGH",            ///< Total inserted money is enough
   "E_EXIT_SYSTEM",       ///< System exception or shutdown
"E_Empty",
    "E_return",

};
