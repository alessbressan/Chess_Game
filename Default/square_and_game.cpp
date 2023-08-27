#include <iostream>
#include <stdlib.h>

#include <Windows.h> // also needed for the 2D graphics library

#include "2D_graphics.h" // use the 2D graphics library

#include "timer.h" // use the time / clock reading function

#include "square_and_game.h"

using namespace std;

square::square()
{
	piece = none;
	color = na;
}

square::~square() {
}

game::game()
{
	turn = 1;
	//initialize
	initialize_slots();
	//creating square objects
	checkmate = false;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			board[i][j] = new square();

			if (board[i][j] == NULL)
			{
				cout << "dynamic memory allocation error in game constructor";
				return;
			}
		}
	}

	//initializing white pieces (type, color and initial position)

	for (int i = 1; i <= 8; i++)
	{
		board[i][1]->color = white;
	}

	board[1][1]->piece = rook;
	board[2][1]->piece = knight;
	board[3][1]->piece = bishop;
	board[4][1]->piece = queen;
	board[5][1]->piece = king;
	board[6][1]->piece = bishop;
	board[7][1]->piece = knight;
	board[8][1]->piece = rook;

	for (int i = 1; i <= 8; i++)
	{
		board[i][2]->piece = pawn;
		board[i][2]->color = white;
	}


	//initializing black pieces (type, color and initial position)

	for (int i = 1; i <= 8; i++)
	{
		board[i][8]->color = black;
	}

	board[1][8]->piece = rook;
	board[2][8]->piece = knight;
	board[3][8]->piece = bishop;
	board[4][8]->piece = queen;
	board[5][8]->piece = king;
	board[6][8]->piece = bishop;
	board[7][8]->piece = knight;
	board[8][8]->piece = rook;

	for (int i = 1; i <= 8; i++)
	{
		board[i][7]->piece = pawn;
		board[i][7]->color = black;
	}

}

game::~game() 
{

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (board[i][j] != NULL) {
				delete board[i][j];
				board[i][j] = NULL;
			}
			else cout << "\n board[" << i << "][" << j << "]\n";
		}
	}
}

void game::sprite_creation()
{
	char background[] = "img/board.png";
	char display_background[] = "img/move_display.png";

	char white_pawn[] = "img/white_pawn.png";
	char white_rook[] = "img/white_rook.png";
	char white_knight[] = "img/white_knight.png";
	char white_bishop[] = "img/white_bishop.png";
	char white_queen[] = "img/white_queen.png";
	char white_king[] = "img/white_king.png";

	char black_pawn[] = "img/black_pawn.png";
	char black_rook[] = "img/black_rook.png";
	char black_knight[] = "img/black_knight.png";
	char black_bishop[] = "img/black_bishop.png";
	char black_queen[] = "img/black_queen.png";
	char black_king[] = "img/black_king.png";

	char white_rectangle[] = "img/rectangle_animation.jpg";
	char alien_gun[] = "img/Alien_Gun.png";
	char light_bullet[] = "img/Lightning_Bullet.png";

	create_sprite(background, id_board);
	create_sprite(display_background, id_move_display);

	create_sprite(white_pawn, id_white_pawn);
	create_sprite(white_rook, id_white_rook);
	create_sprite(white_knight, id_white_knight);
	create_sprite(white_bishop, id_white_bishop);
	create_sprite(white_queen, id_white_queen);
	create_sprite(white_king, id_white_king);

	create_sprite(black_pawn, id_black_pawn);
	create_sprite(black_rook, id_black_rook);
	create_sprite(black_knight, id_black_knight);
	create_sprite(black_bishop, id_black_bishop);
	create_sprite(black_queen, id_black_queen);
	create_sprite(black_king, id_black_king);

	create_sprite(white_rectangle, id_white_rectangle);
	create_sprite(alien_gun, id_alien_gun);

	for (int i = 0; i < 3; i++)
	{
		create_sprite(light_bullet, id_light_bullet[i]);
	}
}

void game::convert(int row, int col, int& xout, int& yout) // converts position on board to pixels
{
	xout = 97 * (row - 1) + 82;
	yout = 97 * (col - 1) + 83;
}

void game::print_board()
{
	clear();

	double scale = 1.75;
	double theta = 0.0;

	int x_pixel, y_pixel; //x and y coordinates in pixels of a piece
	
	draw_sprite(id_move_display, 947, 422, theta, 1.116); 
	draw_sprite(id_board, 423, 422, theta, 3);
	

	print_display_move();	

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{

			if (board[i][j]->piece != none)
			{
				convert(i, j, x_pixel, y_pixel); // convert i and j to pixels

				if (board[i][j]->color == white)
				{
					switch (board[i][j]->piece)
					{
					case pawn:
						draw_sprite(id_white_pawn, x_pixel, y_pixel, theta, scale);
						break;
					case rook:
						draw_sprite(id_white_rook, x_pixel, y_pixel, theta, scale);
						break;
					case bishop:
						draw_sprite(id_white_bishop, x_pixel, y_pixel, theta, scale);
						break;
					case knight:
						draw_sprite(id_white_knight, x_pixel, y_pixel, theta, scale);
						break;
					case queen:
						draw_sprite(id_white_queen, x_pixel, y_pixel, theta, scale);
						break;
					case king:
						draw_sprite(id_white_king, x_pixel, y_pixel, theta, scale);
						break;
					default:
						cout << "error";
						break;
					}
				}

				if (board[i][j]->color == black)
				{
					switch (board[i][j]->piece)
					{
					case pawn:
						draw_sprite(id_black_pawn, x_pixel, y_pixel, theta, scale);
						break;
					case rook:
						draw_sprite(id_black_rook, x_pixel, y_pixel, theta, scale);
						break;
					case bishop:
						draw_sprite(id_black_bishop, x_pixel, y_pixel, theta, scale);
						break;
					case knight:
						draw_sprite(id_black_knight, x_pixel, y_pixel, theta, scale);
						break;
					case queen:
						draw_sprite(id_black_queen, x_pixel, y_pixel, theta, scale);
						break;
					case king:
						draw_sprite(id_black_king, x_pixel, y_pixel, theta, scale);
						break;
					default:
						cout << "error";
						break;
					}
				}
			}

		}

	}
	update();
}

void game::move(int current_x, int current_y, int future_x, int future_y)
{
	board[future_x][future_y]->piece = board[current_x][current_y]->piece;
	board[future_x][future_y]->color = board[current_x][current_y]->color;

	board[current_x][current_y]->piece = none;
	board[current_x][current_y]->color = na;
}

// check if the initial input position is ok 
void game::input_position(int& current_x, int& current_y, bool& result) {

	char column;
	char row;

	char input[2];

	if (turn % 2 != 0.0) cout << "\nWhite's Turn\n";
	else cout << "\nBlack's Turn\n";
	cout << "\nWhat piece would you want to move? ex: a2\n";
	cin >> input;
	cout << "\n";
	column = input[0];
	row = input[1];

	switch (column) {

	case 'a':
		current_x = 1;
		break;
	case 'b':
		current_x = 2;
		break;
	case 'c':
		current_x = 3;
		break;
	case 'd':
		current_x = 4;
		break;
	case 'e':
		current_x = 5;
		break;
	case 'f':
		current_x = 6;
		break;
	case 'g':
		current_x = 7;
		break;
	case 'h':
		current_x = 8;
		break;
	default:
		cout << "Invalid Column entry \n";
	}

	switch (row) {

	case '1':
		current_y = 1;
		break;
	case '2':
		current_y = 2;
		break;
	case '3':
		current_y = 3;
		break;
	case '4':
		current_y = 4;
		break;
	case '5':
		current_y = 5;
		break;
	case '6':
		current_y = 6;
		break;
	case '7':
		current_y = 7;
		break;
	case '8':
		current_y = 8;
		break;
	default:
		cout << "Invalid Row entry \n";
	}

	if (board[current_x][current_y]->piece == none) {// checking if the square has a piece in it
		result = false;
		cout << "\nInvalid input, sqaure is empty. Please input again\n";
		return;
	}


	if (turn % 2 != 0.0) //to check if white turn with a black input
	{
		if (board[current_x][current_y]->color != white)
		{
			cout << "\nNot Black's turn";
			result = false;
			return;
		}
		else {
			result = true;
		}
	}

	if (turn % 2 == 0.0) //to check if black turn with a white input
	{
		if (board[current_x][current_y]->color != black)
		{
			cout << "\nNot White's turn";
			result = false;
			return;
		}
		else {
			result = true;
		}
	}

}

//check if the final position is ok
void game::output_position(int current_x, int current_y, int& future_x, int& future_y, bool& result)
{

	char column;
	char row;

	char input[2];

	cout << "\nTo which square would you like to move to?";
	cin >> input;
	cout << "\n";
	column = input[0];
	row = input[1];
	
	keyboard_input[0] = column;
	keyboard_input[1] = row;
	keyboard_input[2] = '\0';
	
	switch (column) {

	case 'a':
		future_x = 1;
		break;
	case 'b':
		future_x = 2;
		break;
	case 'c':
		future_x = 3;
		break;
	case 'd':
		future_x = 4;
		break;
	case 'e':
		future_x = 5;
		break;
	case 'f':
		future_x = 6;
		break;
	case 'g':
		future_x = 7;
		break;
	case 'h':
		future_x = 8;
		break;
	default:
		cout << "Invalid Column entry \n";
	}

	switch (row) {

	case '1':
		future_y = 1;
		break;
	case '2':
		future_y = 2;
		break;
	case '3':
		future_y = 3;
		break;
	case '4':
		future_y = 4;
		break;
	case '5':
		future_y = 5;
		break;
	case '6':
		future_y = 6;
		break;
	case '7':
		future_y = 7;
		break;
	case '8':
		future_y = 8;
		break;
	default:
		cout << "Invalid Row entry \n";
	}
	if (future_x == current_x && future_y == current_y) {
		cout << "\nInput is the same as output\n";
		result = false;
		return;
	}

	if (turn % 2 != 0.0) //to check if white turn with a black input
	{
		if (board[future_x][future_y]->color == white)
		{
			cout << "\nCannot move there, same color piece";
			result = false;
			return;
		}
		else {
			result = true;
		}
	}

	if (turn % 2 == 0.0) //to check if black turn with a white input
	{
		if (board[future_x][future_y]->color == black)
		{
			cout << "\nCannot move there, same color piece";
			result = false;
			return;
		}
		else {
			result = true;
		}
	}

	
}

//check which rules apply
void game::validate_move(int current_x, int current_y, int future_x, int future_y, bool& result)
{
	switch (board[current_x][current_y]->piece) {
		//case none: 
		//cout << "square has no pieces";
		//break; validate_move will not get to this point since other function check for the case == none
	case pawn:
		pawn_rule(current_x, current_y, future_x, future_y, result);
		break;
	case rook:
		rook_rule(current_x, current_y, future_x, future_y, result);
		break;
	case bishop:
		bishop_rule(current_x, current_y, future_x, future_y, result);
		break;
	case queen:
		queen_rule(current_x, current_y, future_x, future_y, result);
		break;
	case king:
		king_rule(current_x, current_y, future_x, future_y, result);
		break;
	case knight:
		knight_rule(current_x, current_y, future_x, future_y, result);
		break;
	default:
		cout << "No piece cases apply, error\n";
	}
}

//function to play game
void game::play()
{
	int xi = 0, yi = 0;
	int xf = 0, yf = 0;
	bool result;

	input_position(xi, yi, result);
	if (result == true)
	{//checking if the inputs are on peices or on the squares
		output_position(xi, yi, xf, yf, result);
		if (result == true)
		{ //checking if the outputs are not the same as the inputs
			validate_move(xi, yi, xf, yf, result);
			if (result == true)
			{ // chcking if the output moves are acceptable according to rules
				battle_pieces_selection(xi, yi, xf, yf);
				capture_animation(xi, yi, xf, yf);
				move(xi, yi, xf, yf);
				display_move();
				print_board();
				update_move();
				update();
				turn++;
				check_for_mate();
			}
		}
	}

}

//rule for pawn
void game::pawn_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	while (1) {
		if (board[current_x][current_y]->color == white) {
			if ((board[future_x][future_y]->color == black) && (abs(future_x - current_x) == 1) && (future_y - current_y == 1)) { // rule for pawn to capture in diagonal
				result = true;
				break;
			}
			else if (future_x - current_x != 0) { // rule for pawn not moving left and right if not capturing
				cout << "\nInvalid moving square pawn cannot move to another column \n";
				result = false;
				break;
			}
			else if ((current_y == 2) && (future_y == 4) && (board[future_x][3]->piece == none)) { //rule for pawn to move 2 steps if on the 2nd row at the start of the game. However, rule has to check if there are other peices in front of the pawn. if not valid move
				result = true;
				break;
			}
			else if ((current_y == 2) && (future_y == 4) && (board[future_x][3]->piece != none)) { //rule for pawn to move 2 steps if on the 2nd row at the start of the game. However, rule has to check if there are other peices in front of the pawn. if yes not valid move
				cout << "\nInvalid moving square, pawn cannot move 2 steps initally due to piece in front\n";
				result = false;
				break;
			}
			else if (board[future_x][future_y]->piece != none) { // rule for not moving when there is another piece blocking in front
				cout << "\nInvalid moving square, pawn cannot move with piece in front\n";
				result = false;
				break;
			}
			else if ((future_y - current_y) != 1) { // rule for not moving more than 1
				cout << "\nInvalid moving square, pawn cannot move more than 1 step forward or backwards \n";
				result = false;
				break;
			}
			else {
				result = true;
				break;
			}
		}

		if (board[current_x][current_y]->color == black) {
			if ((board[future_x][future_y]->color == white) && (abs(future_x - current_x) == 1) && (future_y - current_y == -1)) { // rule for pawn to capture in diagonal
				result = true;
				break;
			}
			else if (future_x - current_x != 0) { // rule for pawn not moving left and right if not capturing
				cout << "\nInvalid moving square pawn cannot move to another column \n";
				result = false;
				break;
			}
			else if ((current_y == 7) && (future_y == 5) && (board[future_x][6]->piece == none)) { //rule for pawn to move 2 steps if on the 2nd row at the start of the game. However, rule has to check if there are other peices in front of the pawn. if not valid move
				result = true;
				break;
			}
			else if ((current_y == 7) && (future_y == 5) && (board[future_x][6]->piece != none)) { //rule for pawn to move 2 steps if on the 2nd row at the start of the game. However, rule has to check if there are other peices in front of the pawn. if yes not valid move
				cout << "\nInvalid moving square, pawn cannot move 2 steps initally due to piece in front\n";
				result = false;
				break;
			}
			else if (board[future_x][future_y]->piece != none) { // rule for not moving when there is another piece blocking in front
				cout << "\nInvalid moving square, pawn cannot move with piece in front\n";
				result = false;
				break;
			}
			else if ((future_y - current_y) != -1) { // rule for not moving more than 1
				cout << "\nInvalid moving square, pawn cannot move more than 1 step forward or backwards\n";
				result = false;
				break;
			}
			else {
				result = true;
				break;
			}
		}
	}
}

//rule for rook
void game::rook_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	int i;
	int count;
	while (1) {
		count = 0;
		if ((future_x - current_x == 0) && (abs(future_y - current_y) > 1)) { // check if we are moving vertically only and if we move least by 2 steps to check if there is any piece in between the steps
			if (future_y > current_y) { // moving up
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x][i]->piece != none) {
						count++;
						break;
					}
				}
			}
			else { // moving down
				for (i = future_y + 1; i < current_y; i++) {
					if (board[current_x][i]->piece != none) {
						count++;
						break;
					}
				}
			}
		}
		if (future_y - current_y == 0 && (abs(future_x - current_x) > 1)) { // check if we are moving horizontally only and if we move least by 2 steps to check if there is any piece in between the steps
			if (future_x > current_x) { // moving right
				for (i = current_x + 1; i < future_x; i++) {
					if (board[i][current_y]->piece != none) {
						count++;
						break;
					}
				}
			}
			else { // moving left
				for (i = future_x + 1; i < current_x; i++) {
					if (board[i][current_y]->piece != none) {
						count++;
						break;
					}
				}
			}
		}
		if (count != 0) { // if the count has been modified by the if statements, there is at least 1 piece in between the final and current position. Thus cannot move.
			cout << "\nRook is blocked from another piece\n";
			result = false;
			break;
		}
		if ((future_x - current_x == 0) || (future_y - current_y == 0)) { // if there are no peice and the rook only moves left, right, up and down, it is correct
			result = true;
			break;
		}
		else {
			cout << "\nInvalid move, rook cannot be moved\n";
			result = false;
			break;
		}
	}
}

//rule for bishopa
void game::bishop_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	int i, j;
	int count;
	while (1) {//need to add rule for collision with other peices but rule works for both black and white
		count = 0;
		j = 1;
		if ((abs(future_x - current_x)) == (abs(future_y - current_y)) && (abs(future_x - current_x) > 1) && (future_y > current_y)) { // moving up
			if (future_x > current_x) { // moving to the right
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x + j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
			else { // moving to the left
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x - j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
		}
		if ((abs(future_x - current_x)) == (abs(future_y - current_y)) && (abs(future_x - current_x) > 1) && (future_y < current_y)) { // moving down
			if (future_x > current_x) { // moving to the right
				for (i = future_y + 1; i < current_y; i++) {
					if (board[future_x - j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
			else { // moving to the left
				for (i = future_y + 1; i < current_y; i++) {
					if (board[future_x + j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
		}

		if (count != 0) { // if the count has been modified by the if statements, there is at least 1 piece in between the final and current position. Thus cannot move.
			cout << "\nBishop is blocked from another piece\n";
			result = false;
			break;
		}
		if (abs(future_x - current_x) == abs(future_y - current_y)) {
			result = true;
			break;
		}
		else {
			cout << "\nInvalid move, bishop cannot be moved\n";
			result = false;
			break;
		}
	}
}

//rule for queen
void game::queen_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	int i, j;
	int count;
	while (1) {
		count = 0;
		if ((future_x - current_x == 0) && (abs(future_y - current_y) > 1)) { // check if we are moving vertically only and if we move least by 2 steps to check if there is any piece in between the steps
			if (future_y > current_y) { // moving up
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x][i]->piece != none) {
						count++;
						break;
					}
				}
			}
			else { // moving down
				for (i = future_y + 1; i < current_y; i++) {
					if (board[current_x][i]->piece != none) {
						count++;
						break;
					}
				}
			}
		}
		if (future_y - current_y == 0 && (abs(future_x - current_x) > 1)) { // check if we are moving horizontally only and if we move least by 2 steps to check if there is any piece in between the steps
			if (future_x > current_x) { // moving right
				for (i = current_x + 1; i < future_x; i++) {
					if (board[i][current_y]->piece != none) {
						count++;
						break;
					}
				}
			}
			else { // moving left
				for (i = future_x + 1; i < current_x; i++) {
					if (board[i][current_y]->piece != none) {
						count++;
						break;
					}
				}
			}
		}
		j = 1;
		if ((abs(future_x - current_x)) == (abs(future_y - current_y)) && (abs(future_x - current_x) > 1) && (future_y > current_y)) { // moving up
			if (future_x > current_x) { // moving to the right
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x + j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
			else { // moving to the left
				for (i = current_y + 1; i < future_y; i++) {
					if (board[current_x - j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
		}
		if ((abs(future_x - current_x)) == (abs(future_y - current_y)) && (abs(future_x - current_x) > 1) && (future_y < current_y)) { // moving down
			if (future_x > current_x) { // moving to the right
				for (i = future_y + 1; i < current_y; i++) {
					if (board[future_x - j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
			else { // moving to the left
				for (i = future_y + 1; i < current_y; i++) {
					if (board[future_x + j][i]->piece != none) {
						count++;
						break;
					}
					j++;
				}
			}
		}
		if (count != 0) { // if the count has been modified by the if statements, there is at least 1 piece in between the final and current position. Thus cannot move.
			cout << "\nQueen is blocked from another piece\n";
			result = false;
			break;
		}
		if (abs(future_x - current_x) == abs(future_y - current_y)) {
			result = true;
			break;
		}
		else if (future_x - current_x == 0 || future_y - current_y == 0) {
			result = true;
			break;
		}
		else {
			cout << "\nInvalid move, queen cannot be moved\n";
			result = false;
			break;
		}
	}
}

//rule for king
void game::king_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	while (1) {
		if (abs(future_x - current_x) == 1 && abs(future_y - current_y) == 0) {
			result = true;
			break;
		}
		else if (abs(future_x - current_x) == 0 && abs(future_y - current_y) == 1) {
			result = true;
			break;
		}
		else if (abs(future_x - current_x) == 1 && abs(future_y - current_y) == 1) {
			result = true;
			break;
		}
		else {
			cout << "\nInvalid move, king cannot be moved\n";
			result = false;
			break;
		}
	}
}

//rule for knight
void game::knight_rule(int current_x, int current_y, int future_x, int future_y, bool& result) {
	while (1) {
		if (abs(future_x - current_x) == 1 && abs(future_y - current_y) == 2) {
			result = true;
			break;
		}
		else if (abs(future_x - current_x) == 2 && abs(future_y - current_y) == 1) {
			result = true;
			break;
		}
		else {
			cout << "\nInvalid move, knight cannot be moved\n";
			result = false;
			break;
		}
	}
}

void game::update_move() {

	if (turn % 2 != 0) {
		for (int i = 0; i < 2; i++) {
			white_slot10[i] = white_slot9[i];
			white_slot9[i] =  white_slot8[i];
			white_slot8[i] =  white_slot7[i];
			white_slot7[i] =  white_slot6[i];
			white_slot6[i] =  white_slot5[i];
			white_slot5[i] =  white_slot4[i];
			white_slot4[i] =  white_slot3[i];
			white_slot3[i] =  white_slot2[i];
			white_slot2[i] =  white_slot1[i];
			white_slot1[i] = NULL; 
		}
	}
	if (turn % 2 == 0) {
		for (int i = 0; i < 2; i++) {
			black_slot10[i] = black_slot9[i];
			black_slot9[i] = black_slot8[i];
			black_slot8[i] = black_slot7[i];
			black_slot7[i] = black_slot6[i];
			black_slot6[i] = black_slot5[i];
			black_slot5[i] = black_slot4[i];
			black_slot4[i] = black_slot3[i];
			black_slot3[i] = black_slot2[i];
			black_slot2[i] = black_slot1[i];
			black_slot1[i] = NULL;
		}
	}

}

void game::display_move() {

	if (turn % 2 != 0) {
	
		white_slot1[0] = keyboard_input[0];
		white_slot1[1] = keyboard_input[1];
		white_slot1[2] = '\0';
	}

	else if (turn % 2 == 0) {
		
		black_slot1[0] = keyboard_input[0];
		black_slot1[1] = keyboard_input[1];
		black_slot1[2] = '\0';
	}

	else {
		cout << "invalid entry" << endl;
	}

}

void game::print_display_move() {
	double scale = 1.0;
	double yarray[10] = { 80, 182, 282, 382, 482, 582, 682, 782};
	double xarray[2] = { 860, 960 };


	if (turn % 2 != 0 || turn % 2 == 0) {
		
		text(white_slot1, xarray[0], yarray[0], scale);
		text(white_slot2, xarray[0], yarray[1], scale);
		text(white_slot3, xarray[0], yarray[2], scale);
		text(white_slot4, xarray[0], yarray[3], scale);
		text(white_slot5, xarray[0], yarray[4], scale);
		text(white_slot6, xarray[0], yarray[5], scale);
		text(white_slot7, xarray[0], yarray[6], scale);
		text(white_slot8, xarray[0], yarray[7], scale);
		

		text(black_slot1, xarray[1], yarray[0], scale);
		text(black_slot2, xarray[1], yarray[1], scale);
		text(black_slot3, xarray[1], yarray[2], scale);
		text(black_slot4, xarray[1], yarray[3], scale);
		text(black_slot5, xarray[1], yarray[4], scale);
		text(black_slot6, xarray[1], yarray[5], scale);
		text(black_slot7, xarray[1], yarray[6], scale);
		text(black_slot8, xarray[1], yarray[7], scale);

	}

	else {
		cout << "nothing is printing" << endl;
	}

}

void game::initialize_slots() {

	for (int i = 0; i < 2; i++) {

		white_slot10[i] = ' ';
		white_slot9[i] =  ' ';
		white_slot8[i] =  ' ';
		white_slot7[i] =  ' ';
		white_slot6[i] =  ' ';
		white_slot5[i] =  ' ';
		white_slot4[i] =  ' ';
		white_slot3[i] =  ' ';
		white_slot2[i] =  ' ';
		white_slot1[i] =  ' ';
						 
		black_slot10[i] = ' ';
		black_slot9[i] =  ' ';
		black_slot8[i] =  ' ';
		black_slot7[i] =  ' ';
		black_slot6[i] =  ' ';
		black_slot5[i] =  ' ';
		black_slot4[i] =  ' ';
		black_slot3[i] =  ' ';
		black_slot2[i] =  ' ';
		black_slot1[i] =  ' ';
	
		keyboard_input[i] = ' ';
	}

	white_slot10[2] = '\0';
	white_slot9[2] = '\0';
	white_slot8[2] = '\0';
	white_slot7[2] = '\0';
	white_slot6[2] = '\0';
	white_slot5[2] = '\0';
	white_slot4[2] = '\0';
	white_slot3[2] = '\0';
	white_slot2[2] = '\0';
	white_slot1[2] = '\0';

	black_slot10[2] = '\0';
	black_slot9[2] = '\0';
	black_slot8[2] = '\0';
	black_slot7[2] = '\0';
	black_slot6[2] = '\0';
	black_slot5[2] = '\0';
	black_slot4[2] = '\0';
	black_slot3[2] = '\0';
	black_slot2[2] = '\0';
	black_slot1[2] = '\0';

	keyboard_input[2] = '\0';
}

void game::battle_pieces_selection(int attacking_x, int attacking_y, int defending_x, int defending_y)
{
	if (board[defending_x][defending_y]->piece == none)
	{
		start_animation = false;
	}
	else start_animation = true;

	if (start_animation == true)
	{
		if (board[attacking_x][attacking_y]->color == white)
		{
			switch (board[attacking_x][attacking_y]->piece)
			{
			case pawn:
				id_attacking_piece = id_white_pawn;
				break;
			case rook:
				id_attacking_piece = id_white_rook;
				break;
			case bishop:
				id_attacking_piece = id_white_bishop;
				break;
			case knight:
				id_attacking_piece = id_white_knight;
				break;
			case queen:
				id_attacking_piece = id_white_queen;
				break;
			case king:
				id_attacking_piece = id_white_king;
				break;
			default:
				cout << "error";
				break;
			}
			switch (board[defending_x][defending_y]->piece)
			{
			case pawn:
				id_defending_piece = id_black_pawn;
				break;
			case rook:
				id_defending_piece = id_black_rook;
				break;
			case bishop:
				id_defending_piece = id_black_bishop;
				break;
			case knight:
				id_defending_piece = id_black_knight;
				break;
			case queen:
				id_defending_piece = id_black_queen;
				break;
			case king:
				id_defending_piece = id_black_king;
				break;
			default:
				cout << "error";
				break;
			}
		}

		if (board[attacking_x][attacking_y]->color == black)
		{
			switch (board[attacking_x][attacking_y]->piece)
			{
			case pawn:
				id_attacking_piece = id_black_pawn;
				break;
			case rook:
				id_attacking_piece = id_black_rook;
				break;
			case bishop:
				id_attacking_piece = id_black_bishop;
				break;
			case knight:
				id_attacking_piece = id_black_knight;
				break;
			case queen:
				id_attacking_piece = id_black_queen;
				break;
			case king:
				id_attacking_piece = id_black_king;
				break;
			default:
				cout << "error";
				break;
			}
			switch (board[defending_x][defending_y]->piece)
			{
			case pawn:
				id_defending_piece = id_white_pawn;
				break;
			case rook:
				id_defending_piece = id_white_rook;
				break;
			case bishop:
				id_defending_piece = id_white_bishop;
				break;
			case knight:
				id_defending_piece = id_white_knight;
				break;
			case queen:
				id_defending_piece = id_white_queen;
				break;
			case king:
				id_defending_piece = id_white_king;
				break;
			default:
				cout << "error";
				break;
			}
		}
	}
}

void game::capture_animation(int current_x, int current_y, int future_x, int future_y)
{

	double distance[3];
	int health = 3;
	double t;

	double battle_scaling_rectangle = 0.25;
	double battle_scaling_alien_gun = 0.0;
	double battle_scaling_piece = 0.0;
	double alien_gun_x = 526;
	double attacking_piece_x = 526;
	double defending_piece_x = 526;
	double bullet_x[3];
	double gun_recoil = 0.0;
	double piece_flip = 0.0;


	if (start_animation == true)
	{
		while (battle_scaling_rectangle <= 1.25) //goes 20 loops ; size increases
		{
			clear();
			//print_board();

			battle_scaling_rectangle += 0.05;
			battle_scaling_alien_gun += 0.0075;
			battle_scaling_piece += 0.125;
			alien_gun_x -= 5;
			attacking_piece_x -= 10;
			defending_piece_x += 10;

			draw_sprite(id_white_rectangle, 526, 526, 0, battle_scaling_rectangle);
			draw_sprite(id_alien_gun, alien_gun_x, 526, 0, battle_scaling_alien_gun);
			draw_sprite(id_attacking_piece, attacking_piece_x, 526, 0, battle_scaling_piece);
			draw_sprite(id_defending_piece, defending_piece_x, 526, 0, battle_scaling_piece);

			update();
		}

		for (int i = 0; i < 3; i++)
		{
			bullet_x[i] = alien_gun_x + 50.0;
		}

		while (health != 0) //we want 3 gun shots, where PI/2 is the period health of defending piece !=0
		{
			t = high_resolution_time();
			gun_recoil = abs(sin(2 * t));
			//print_board();
			draw_sprite(id_white_rectangle, 526, 526, 0, battle_scaling_rectangle);
			draw_sprite(id_alien_gun, alien_gun_x, 526, gun_recoil, battle_scaling_alien_gun);
			draw_sprite(id_attacking_piece, attacking_piece_x, 526, 0, battle_scaling_piece);
			draw_sprite(id_defending_piece, defending_piece_x, 526, piece_flip, battle_scaling_piece);

			if (health == 3)
			{
				bullet_x[0] += 3;
				draw_sprite(id_light_bullet[0], bullet_x[0], 526, 90, 0.1);
				distance[0] = defending_piece_x - bullet_x[0];
				if (distance[0] <= 15)
				{
					health--;
				}
			}

			if (t > 0.5 * PI && health != 1)
			{
				bullet_x[1] += 3;
				draw_sprite(id_light_bullet[1], bullet_x[1], 526, 90, 0.1);
				distance[1] = defending_piece_x - bullet_x[1];
				if (distance[1] <= 15)
				{
					health--;
				}
			}

			if (t > PI)
			{
				bullet_x[2] += 3;
				draw_sprite(id_light_bullet[2], bullet_x[2], 526, 90, 0.1);
				distance[2] = defending_piece_x - bullet_x[2];
				if (distance[2] <= 15)
				{
					health--;
					gun_recoil = 0.0;
					piece_flip = PI;
				}
			}
			
			update(); //updates the window

			if (health == 0)
			{
				clear();
				//print_board();
				draw_sprite(id_white_rectangle, 526, 526, 0, battle_scaling_rectangle);
				draw_sprite(id_alien_gun, alien_gun_x, 526, gun_recoil, battle_scaling_alien_gun);
				draw_sprite(id_attacking_piece, attacking_piece_x, 526, 0, battle_scaling_piece);
				draw_sprite(id_defending_piece, defending_piece_x, 526, piece_flip, battle_scaling_piece);
				update();
				//Sleep(10); //sleeps a bit the screen
			}
		}
		

		while (battle_scaling_rectangle >= 0) //goes 20 loops ; shrinks down
		{
			clear();
			//print_board();
			draw_sprite(id_white_rectangle, 526, 526, 0, battle_scaling_rectangle);
			draw_sprite(id_alien_gun, alien_gun_x, 526, gun_recoil, battle_scaling_alien_gun);
			draw_sprite(id_attacking_piece, attacking_piece_x, 526, 0, battle_scaling_piece);
			draw_sprite(id_defending_piece, defending_piece_x, 526, piece_flip, battle_scaling_piece);
			battle_scaling_rectangle -= 0.05; //-0.05
			battle_scaling_alien_gun -= 0.005; //-0.0075
			battle_scaling_piece -= 0.1; //-0.125
			alien_gun_x += 4; //5
			attacking_piece_x += 8; //10
			defending_piece_x -= 8; //10
			//Sleep(50);
			update();
		}
	}
}

void game::check_for_mate()
{
	{
		int countkings = 0;

		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				if (board[i][j]->piece == king)
				{
					countkings++;
				}
			}
		}

		if (countkings < 2)
		{
			checkmate = true;

			if (turn % 2 == 0) {
				cout << "\nGameOver White Wins\n";
			}

			if (turn % 2 != 0) {
				cout << "\nGameOver Black Wins\n";
			}
		}
	}
}

