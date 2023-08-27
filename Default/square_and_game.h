
const double PI = 3.14159;

enum Piece { pawn, rook, knight, bishop, queen, king, none };
enum Color { white, black, na };

class square {
public:
	Color color;
	Piece piece;

	square();
	~square();
};

class game {
public:
	square* board[9][9];

	int turn;
	char keyboard_input[3];

	char white_slot1[3], black_slot1[3];
	char white_slot2[3], black_slot2[3];
	char white_slot3[3], black_slot3[3];
	char white_slot4[3], black_slot4[3];
	char white_slot5[3], black_slot5[3];
	char white_slot6[3], black_slot6[3];
	char white_slot7[3], black_slot7[3];
	char white_slot8[3], black_slot8[3];
	char white_slot9[3], black_slot9[3];
	char white_slot10[3], black_slot10[3];

	game();
	~game();

	void print_board();
	void convert(int row, int col, int& xout, int& yout);
	void sprite_creation();
	void move(int current_x, int current_y, int future_x, int future_y);
	void input_position(int& current_x, int& current_y, bool& result);
	void output_position(int current_x, int current_y, int& future_x, int& future_y, bool& result);
	void validate_move(int current_x, int current_y, int future_x, int future_y, bool& result);
	void play();

	void pawn_rule(int current_x, int current_y, int future_x, int future_y, bool& result);
	void rook_rule(int current_x, int current_y, int future_x, int future_y, bool& result);
	void bishop_rule(int current_x, int current_y, int future_x, int future_y, bool& result);
	void queen_rule(int current_x, int current_y, int future_x, int future_y, bool& result);
	void king_rule(int current_x, int current_y, int future_x, int future_y, bool& result);
	void knight_rule(int current_x, int current_y, int future_x, int future_y, bool& result);

	void initialize_slots();
	void update_move();
	void display_move();
	void print_display_move();

	void check_for_mate();

	void battle_pieces_selection(int attacking_x, int attacking_y, int defending_x, int defending_y);
	void capture_animation(int attacking_x, int attacking_y, int defending_x, int defending_y);

	int id_board, id_move_display;
	int id_white_pawn, id_white_rook, id_white_knight, id_white_bishop, id_white_queen, id_white_king;
	int id_black_pawn, id_black_rook, id_black_knight, id_black_bishop, id_black_queen, id_black_king;

	bool checkmate;

	int id_white_rectangle, id_alien_gun, id_light_bullet[3];
	int id_attacking_piece, id_defending_piece;
	bool start_animation;
	
};