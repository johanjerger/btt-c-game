#ifndef BTT_GAME_TEXTS_H
#define BTT_GAME_TEXTS_H

#include "types.h"

#define BTT_TITLE RED "\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" RESET \
        RED "\t\tXX" YELLOW "X                                      X" RED "XX\n" RESET \
        RED "\t\tXX" BLUE "    XXXXXXX    XXXXXXXX     XXXXXXXX    " RED "XX\n" RESET \
        RED "\t\tXX" BLUE "    XX   XXX      XX           XX       " RED "XX\n" RESET \
        RED "\t\tXX" BLUE "    XXXXXXX       XX           XX       " RED "XX\n" RESET \
        RED "\t\tXX" BLUE "    XX   XXX      XX           XX       " RED "XX\n" RESET \
        RED "\t\tXX" BLUE "    XXXXXXX       XX           XX       " RED "XX\n" RESET \
        RED "\t\tXX" YELLOW "X                                      X" RED "XX\n" RESET \
        RED "\t\tXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n\n\n" RESET

const char * option_names[] = {
        "Start Game",
        "Score Tab",
        "History",
        "Tutorial",
        "Exit"
};

const char * difficults_names[] = {
        "Easy",
        "Normal",
        "Hard",
        "Very Hard",
        "Hopeless"
};

const char * players[] = {
        "*",
        "~",
        "+"
};

const char * file_names[] = {
        "EasyScoreTab",
        "NormalScoreTab",
        "HardScoreTab",
        "VeryHardScoreTab",
        "HopelessScoreTab"
};

const char * pause_options[] = {
        "Resume Game",
        "Go to Menu"
};

#endif
