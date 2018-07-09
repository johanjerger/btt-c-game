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

const char * histories[] = {
      "\t\t\tIn the year 2057, an UFO descended\n\t\t\ton planet earth, infecting the entire\n\t\t\tplanet with " RED "cannibal orphans" RESET " with cold\n\t\t\tand mean feelings as a dead elephant.\n\n\t\t\tYou are the " BLUE "choosen one"RESET " to defend\n\t\t\tthe planet from evil " RED "cannibal orphans" RESET ".\n\n\t\t\tGrab your weaponds and go for them!\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\tTwo months have passed since the\n\t\t\tUFO descended. You and your squad have\n\t\t\tfound small hints indicating that the \n\t\t\t" RED "enemy base" RESET " is nearby.\n\n\t\t\tThe " RED "Cannibal orphans" RESET " have stolen all\n\t\t\tthe mothers of " BLUE "planet earth" RESET ",\n\t\t\tso that at last someone treats\n\t\t\tthem as people, unfortunately, the\n\t\t\tPhaders didn't have the same fate...\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\tYou finally found the enemy base, looking\n\t\t\tat it from a hill you see how the " RED "cannibal" RESET "\n\t\t\t" RED "orphans" RESET " violently rape the motehrs in\n\t\t\torder to reproduce and dominate \n\t\t\t" BLUE "planet earth" RESET ".\n\n\t\t\tNot only the mothers, You see as there\n\t\t\tare also helpless girls. " BLUE "You an your" RESET "\n\t\t\t" BLUE "squad" RESET " are subjected to hear those\n\t\t\tcries of pain and see that tears.\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n",
      "\t\t\t\tComing soon,...\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tPress " GREEN "ENTER" RESET "\n"
};

const char * option_names[] = {
        "Start Game",
        "Score Tab",
        "History",
        "Tutorial",
        "Exit"
};

const char * difficulties[] = {
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

const char * score_table_options[] = {
        "Go to Menu",
        "Clean Table"
};

#endif
