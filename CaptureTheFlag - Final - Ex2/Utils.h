#pragma once

#define TOOLS_NUMBER  3
#define PLAYERS_NUMER  2
#define TOOL_BORDER 6 
enum Directions { LEFT, RIGHT, UP, DOWN,STOP, NUM_OF_DIRS };
enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };

// Colors
void setColor(int choosecolor);
void resetColor();

// Functions
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();
