TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        console_functions/devConsole.c \
        console_functions/display.c \
        console_functions/keyboard.c \
        console_functions/systemErrors.c \
        cvmfsm_functions.c \
        cvmhandle_states_and_events.c \
        events.c \
        fsm_functions/fsm.c \
        main.c \
        states.c

HEADERS += \
   appInfo.h \
   console_functions/devConsole.h \
   console_functions/display.h \
   console_functions/keyboard.h \
   console_functions/systemErrors.h \
   cvmfsm_functions.h \
   cvmhandle_states_and_events.h \
   events.h \
   fsm.h \
   fsm_functions/fsm.h \
   initialise_FSM.h \
   states.h

DISTFILES +=
