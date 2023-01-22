/*#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#include "console_functions/devConsole.h"
#include "console_functions/display.h"
#include "console_functions/keyboard.h"
#include "console_functions/systemErrors.h"
#include "fsm_functions/fsm.h"
#include "cvmfsm_functions.h"
#include "coffeedispenser.h"


 * These functions handle the states entries and exits
 */
/*
/// Some global variables \todo try to avoid these global variables
char selectedCoffee[15] = "none";
int coffeeLeft = 10;
int change = 100;
int priceEspresso = 120;                   /// Configure the price
int priceHotChocolate = 130;
int priceCappuccino = 125;
int insertedMoney;
int exitCode;             //signal graceful shutdown

extern char * eventEnumToText[];
extern char * stateEnumToText[];

extern state_t state;
extern event_t event;

event_t setCoffeeselection(void);
event_t insertedmoney(void);

void S_InitialiseSubsystems_onEntry(void)
{

    // Initalize the debug console
    DSPinitialise();                                /// Initialise User interface
    DSPshowDisplay();                               /// And debug console
    DCSinitialise();
    KYBinitialise();

    // Inform the CVM user
    insertedMoney = 0;                              /// 0 coins inserted
    change = 100;
    DSPshow(1, "Starting Coffee machine");
    DSPshow(2, "Program started");                  /// Update user interface
    DSPshow(3, "insertMoney = %d", insertedMoney);  ///
    DSPshow(4, "change = %d", change);
    DSPshow(5, "Coffee left = %", coffeeLeft);
    DSPshow(6, "Press <ENTER> to continue");

    FSM_AddEvent(E_CONTINUE);           /// Initialisation done, go to next state
}

void S_InitialiseSubsystems_onExit(void)
{
    /// nothing to do onExit
}

void S_Choose_Coffee_onEntry(void)
{
    DSPshow(1, "Coffee");

    DSPshow(3, "Enter a program.");
    DSPshow(4, "<1> Espresso");
    DSPshow(5, "<2> Cappucino");
    DSPshow(6, "<3> Hot Chocolate");

    DSPshow(8, "Press <ENTER> to continue");
    event_t coffeeselection = setCoffeeselection();          /// Get program information from the program subsystem
    FSM_AddEvent(coffeeselection);     /// Configuration complete Internal generated event
}

void S_Choose_Coffee_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);   /// Debug info
}

void S_Process_Espresso_onEntry(void)
{
    insertedmoney();                    /// Displays the time selecion menu
    event_t money = insertedmoney();          /// Call setTime function
    FSM_AddEvent(money);                /// Gets trigger from setTime function
}

void S_Espresso_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_Process_Cappucino_onEntry(void)
{
    insertedmoney();                    /// Displays the time selecion menu
    event_t money = insertedmoney();          /// Call setTime function
    FSM_AddEvent(money);                /// Gets trigger from setTime function
}

void S_Process_Cappucino_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_Process_HotChocolate_onEntry(void)
{
    insertedmoney();                    /// Displays the time selecion menu
    event_t money = insertedmoney();          /// Call setTime function
    FSM_AddEvent(money);                /// Gets trigger from setTime function
}

void S_Process_HotChocolate_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_Process_INSERTED_MONEY_onEntry(void)
{
    FSM_AddEvent(E_START);
}

void S_Process_inserted_money_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_Start_program_onEntry(void)
{
    DSPshow(1, "Selected coffee: %s", selectedCoffee);
    DSPshow(2, "Making coffee :)");

}
void S_Start_program_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_RestartProgram_onEntry(void)
{
    DSPshow(1, "Restarting");
    strcpy(selectedCoffee, "none");
    change = 0;
    FSM_AddEvent(E_Return);
}

void S_RestartProgram_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);   /// Debug info
}
void S_ShutdownSystem(int status)
{
    if (status !=0)
    {
        DCSshowSystemError("System shutting down error code %d, state = %", status, stateEnumToText[state]);
    }
    else
    {
        DCSsimulationSystemInfo("System shutting down", status);
    }
    exit(status);
}
event_t setCoffeeselection(void)
{
    char kb;
    event_t coffeeselection = E_Return;
kb = DCSsimulationSystemInputChar("Which coffee do you want?:", "123");
    switch(kb)
    {
       case '1':
            coffeeselection = E_Espresso;
            strcpy(selectedCoffee, "Espresso");
            break;
       case '2':
            coffeeselection = E_Cappuccino;
            strcpy(selectedCoffee, "Cappucino");
            break;
       case '3':
            coffeeselection = E_HotChocolate;
            strcpy(selectedCoffee, "Hot Chocolate");
            break;
       default:
            DSPshow(1, "Wrong character");
            strcpy(selectedCoffee, "none");
            }
           return coffeeselection;

}

event_t insertedmoney(void)            /// coinacceptor
{
    char kb;
    event_t money = E_EXIT_SYSTEM;
    kb = DCSsimulationSystemInputChar("Please insert a coin enter 1 for 25c enter 2 for 50c or enter 3 for 100c", "123");
    switch (kb)
    {
    case '1':
        money = E_25C;
        break;
    case '2':
        money = E_50C;
        break;
    case '3':
        money = E_100C ;
        break;
    default:
        money = E_EXIT_SYSTEM;
    }
    return money;
}


/// Helper functions

/// simulate delay in miliseconds
void delay_ms(uint32_t d)
{
    DCSdebugSystemInfo("Delay waiting for %d micro-seconds", d);
    sleep(d/1000);
}*/
