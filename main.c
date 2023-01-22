#include "console_functions/keyboard.h"
#include "fsm_functions/fsm.h"
#include "console_functions/devConsole.h"
#include "console_functions/display.h"
/*#include "cvmhandle_states_and_events.h"*/
#include "states.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
extern char * eventEnumToText[];
extern char * stateEnumToText[];
extern state_t state;
extern event_t event;
state_t state;
event_t event;
state_t previousState;
event_t previousEvent;


char selectedCoffee[15] = "none";  /// char array for selected coffee name
int coffeeLeft = 10;                /// How much coffee is left in de machine
int change = 100;                   ///How much coins is left in machine
int priceEspresso = 120;            ///Price 1 espresso
int priceHotChocolate = 130;        ///Price 1 hot chocolate
int priceCappuccino = 125;          ///Price 1 cappuccino
int insertedMoney;
int exitCode;             ///signal graceful shutdown


void S_InitialiseSubsystems_onEntry(void);
void S_InitialiseSubsystems_onExit(void);
void S_Choose_Coffee_onEntry(void);
void S_Choose_Coffee_onExit(void);

void S_Process_Espresso_onEntry(void);
void S_Process_Espresso_onExit(void);
void S_Process_Cappuccino_onEntry(void);
void S_Process_Cappuccino_onExit(void);
void S_Process_HotChocolate_onEntry(void);
void S_Process_HotChocolate_onExit(void);

void S_Inserted_Money_onEntry(void);
void S_Inserted_Money_onExit(void);

void S_StartProgram_onEntry(void);
void S_StartProgram_onExit(void);
void S_RestartProgram_onEntry(void);
void S_RestartProgram_onExit(void);

void S_ShutdownSystem(int status);

void delay_ms(uint32_t d);

event_t setCoffeeselection(void);
event_t insertedmoney(void);

/*!
 * FSM Init Functions
 * \brief cvmInitialiseFSM
 * \param start_state
 * \param start_event
 */
int main(void)
{
    //           State                                     onEntry()                       onExit()
    FSM_AddState(S_INITIALISESUBSYSTEMS, &(state_funcs_t){ S_InitialiseSubsystems_onEntry, S_InitialiseSubsystems_onExit });
    FSM_AddState(S_CHOOSE_COFFEE,        &(state_funcs_t){ S_Choose_Coffee_onEntry,        S_Choose_Coffee_onExit });
    FSM_AddState(S_PROCESS_ESPRESSO,     &(state_funcs_t){ S_Process_Espresso_onEntry,     S_Process_Espresso_onExit });
    FSM_AddState(S_PROCESS_CAPPUCINO,    &(state_funcs_t){ S_Process_Cappuccino_onEntry,   S_Process_Cappuccino_onExit });
    FSM_AddState(S_PROCESS_HOTCHOCOLATE, &(state_funcs_t){ S_Process_HotChocolate_onEntry, S_Process_HotChocolate_onExit});
    FSM_AddState(S_INSERTED_MONEY,       &(state_funcs_t){ S_Inserted_Money_onEntry,       S_Inserted_Money_onExit });
    FSM_AddState(S_START_PROGRAM,        &(state_funcs_t){ S_StartProgram_onEntry,         S_StartProgram_onExit });
    FSM_AddState(S_RESTART_PROGRAM,      &(state_funcs_t){ S_RestartProgram_onEntry,       S_RestartProgram_onExit });

    //                                 From                     Event                To
    FSM_AddTransition(&(transition_t){ S_NO,                    E_START,        S_INITIALISESUBSYSTEMS    });
    FSM_AddTransition(&(transition_t){ S_INITIALISESUBSYSTEMS,  E_CONTINUE,     S_CONFIGURE });
    FSM_AddTransition(&(transition_t){ S_CONFIGURE,             E_CONFIG_READY, S_STOP});

    FSM_AddTransition(&(transition_t){ S_CHOOSE_COFFEE,         E_Espresso,     S_PROCESS_ESPRESSO});
    FSM_AddTransition(&(transition_t){ S_CHOOSE_COFFEE,         E_Cappuccino,   S_PROCESS_CAPPUCINO});
    FSM_AddTransition(&(transition_t){ S_CHOOSE_COFFEE,         E_HotChocolate, S_PROCESS_HOTCHOCOLATE});

    FSM_AddTransition(&(transition_t){ S_PROCESS_ESPRESSO,      E_100C,         S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_ESPRESSO,      E_50C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_ESPRESSO,      E_25C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_ESPRESSO,      E_NOT_ENOUGH,   S_PROCESS_ESPRESSO});

    FSM_AddTransition(&(transition_t){ S_PROCESS_CAPPUCINO,     E_100C,         S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_CAPPUCINO,     E_50C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_CAPPUCINO,     E_25C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_CAPPUCINO,     E_NOT_ENOUGH,   S_PROCESS_CAPPUCINO});

    FSM_AddTransition(&(transition_t){ S_PROCESS_HOTCHOCOLATE,  E_100C,         S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_HOTCHOCOLATE,  E_50C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_HOTCHOCOLATE,  E_25C,          S_INSERTED_MONEY});
    FSM_AddTransition(&(transition_t){ S_PROCESS_HOTCHOCOLATE,  E_NOT_ENOUGH,   S_PROCESS_HOTCHOCOLATE});

    FSM_AddTransition(&(transition_t){ S_INSERTED_MONEY,  E_ENOUGH,   S_START_PROGRAM});
    FSM_AddTransition(&(transition_t){ S_START_PROGRAM,  E_Done,   S_TAKE_OUT});

    FSM_AddTransition(&(transition_t){ S_TAKE_OUT,  E_Return,   S_CHOOSE_COFFEE});
    FSM_AddTransition(&(transition_t){ S_TAKE_OUT,  E_EMPTY,   S_STOP});

    /// Should unexpected events in a state be flushed or not?
    FSM_FlushEnexpectedEvents(true);

    /// Set the finite state machine in the S_NO state
    /// and add a E_START event into the event buffer
    state = S_NO;                    /// Begin state
    FSM_AddEvent(E_START);           /// Machine is switched on

    while(event != E_CONTINUE_ERROR) /// While E_CONTINUE_ERROR is NOT triggert display debug


   {
        if(!FSM_NoEvents())
        {
            // Get the event and handle it
            previousEvent = event;
            previousState = state;
            event = FSM_GetEvent();
            state = FSM_EventHandler(state, event);
        }
    }
}

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
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);   ///Show debug info
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

void S_Process_Cappuccino_onExit(void)
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

void S_inserted_money_onExit(void)
{
    DSPshowDelete(1, "");
    DCSdebugSystemInfo("Curent state: %s, Current event: %s", stateEnumToText[state], eventEnumToText[event]);
}

void S_Startprogram_onEntry(void)
{
    DSPshow(1, "Selected coffee: %s", selectedCoffee);
    DSPshow(2, "Making coffee :)");

}
void S_StartProgram_onExit(void)
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
        insertedMoney = insertedMoney + 25;
        break;
    case '2':
        money = E_50C;
        insertedMoney = insertedMoney + 50;
        break;
    case '3':
        money = E_100C ;
        insertedMoney = insertedMoney +100;
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
}
