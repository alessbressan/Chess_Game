#include <iostream>
#include <stdlib.h>

#include <Windows.h> // also needed for the 2D graphics library

#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function

#include "square_and_game.h"

using namespace std;

void instructions();

int main()
{
	instructions();
	game A;
	
	initialize_graphics();
	clear();
	A.sprite_creation();

	A.print_board();
	

	while (A.checkmate != true)
	{
		A.play();
	}

	return 0;
}

void instructions() {
	cout << "\t\t\t CHESS GAME FOR MECH 415\n" << endl;
	cout << "\tPresented by Alessio Bressan, William Gallant, Inderjeet Saini, Rami Noueir\n" << endl;

	cout << "Here are the instructions to play our game of chess:\n";
	cout << "\nRule 1. To win a player must capture the king with an opposing colour piece\n";
	cout << "\nRule 2: The capturing moves for each piece are the same as in classical chess\n";
	cout << "\nRule 3: This game will not involve pins or checks thus the players must be aware of their kings position\n";
	cout << "\nRule 4: To move a piece the user must input the piece's coordinate they would like to move\n";
	cout << "\tThen input the coordinate of the location they would like to move to\n";
	cout << "\nRule 5: The coordiante system is composed of numbers for columns and letters for rows\n";
	cout << "\nRule 6: The input for letters is case sensitive, they must be lowercase\n";
}
