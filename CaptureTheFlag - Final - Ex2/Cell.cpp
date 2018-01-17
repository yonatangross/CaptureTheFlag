#include "Cell.h"
#include "Utils.h"
#include <iostream>

using namespace std;

// Printing
void Cell::draw(char ch) const
{
	gotoxy(x, y);
	cout << ch;
	// make sure it gets to screen on time
	cout.flush();
}
void Cell::draw() const
{
	gotoxy(x, y);
	cout << ch;
	// make sure it gets to screen on time
	cout.flush();
}

