#include <cassert>
#include "Game.h"
#include <vector>
#include <algorithm>

namespace Chess
{
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Game::Game() : is_white_turn(true) {
		// Add the pawns
		for (int i = 0; i < 8; i++) {
			board.add_piece(Position('A' + i, '1' + 1), 'P');
			board.add_piece(Position('A' + i, '1' + 6), 'p');
		}

		// Add the rooks
		board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
		board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
		board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );

		// Add the knights
		board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
		board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
		board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );

		// Add the bishops
		board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
		board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
		board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );

		// Add the kings and queens
		board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
		board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
		board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
		board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
	}

	bool Game::is_clear_path(const Position& start, const Position& end) const{
		assert(start!=end); //must move the piece for a valid path
		bool diagonal_path = (start.first != end.first && start.second != end.second); //check if the path is diagonal
		Position curr_pos = start;
		int horizontal_offset = (int)(end.first - start.first);
		int vertical_offset = (int)(end.second - start.second);
		// Calculate how many steps we need to carry out to reach the position just before the end. 
		// For diagonal, we need two steps less (one horizontal, one vertical) to reach just before the end
		int i = 0, sum_steps = diagonal_path ? abs(horizontal_offset)+abs(vertical_offset) - 2 : abs(horizontal_offset)+abs(vertical_offset) - 1; 
		while (i < sum_steps){ //iteratively detect if the position up to the block just before the end is empty 
			if (horizontal_offset > 0){
				curr_pos.first += 1; i++;
			}
			else if (horizontal_offset < 0){
				curr_pos.first -= 1; i++;
			}
			if (vertical_offset > 0){
				curr_pos.second += 1; i++;
			}
			else if (vertical_offset < 0){
				curr_pos.second -= 1; i++;
			}
			if (board(curr_pos) != nullptr){
				return false;
			}
		}
		return true;
	}

	// If we are checking for in_check, we need to assume that it's the opponent's turn, and see if it can capture the king. 
	// checking_check is false by default, in header file
	ReturnCode Game::check_shape_clear_move(const Position& start, const Position& end, bool checking_check) const{ 
		if (start.first < 'A' || start.first > 'H' || start.second < '1' || start.second > '8'){
		  return ReturnCode::START_POS_NOT_ON_BOARD; //1
	 	}
		if (end.first < 'A' || end.first > 'H' || end.second < '1' || end.second > '8'){
			return ReturnCode::END_POS_NOT_ON_BOARD; //2
		}
		bool white_turn = turn_white();
		bool capture = false;
		const Piece * curr_piece = board(start);
		const Piece * end_piece = board(end);
		if (!curr_piece){
			return ReturnCode::EMPTY_START_POS;//4
		}
		if ( !checking_check && ((white_turn && curr_piece->to_ascii() > 'Z') || (!white_turn && curr_piece->to_ascii() <= 'Z') )){
			//if the designator of curr_piece is uppercase, it should be white; if lowercase, black
			return ReturnCode::MISMATCHED_TURN_COLOR;//5
		}
		if (end_piece) capture = true;
		if (!capture && curr_piece->legal_move_shape(start, end) == false){
			return ReturnCode::ILLEGAL_MOVE_SHAPE; //6
		}
		if (capture && curr_piece->legal_capture_shape(start, end) == false){
			return ReturnCode::ILLEGAL_CAPTURE_SHAPE;//7
		}
		if (capture && (start == end || curr_piece->is_white() == end_piece->is_white())){
			return ReturnCode::CAPTURE_OWN_PIECE;//3
		}

		switch(curr_piece->to_ascii()){
			//if not initial move, then 
			//fall through
			case 'P':
				
			//if not initial move, then 
			//fall through
			case 'p':
				
			//fall through 
			case 'Q':
			case 'q':
			case 'B':
			case 'b':
			case 'R':
			case 'r': 
				if (!is_clear_path(start,end)){
					return ReturnCode::PATH_NOT_CLEAR;
				}
				break;
			case 'M':
			case 'm':
				if (start.first - end.first == 0 || start.second - end.second == 0 || (abs(start.first-end.first) == abs(start.second-end.second)) ){//if along a straight line
					if (!is_clear_path(start,end)) return ReturnCode::PATH_NOT_CLEAR;
				}
				break;
		}
		return ReturnCode::SUCCESS;
	}

	//return false if won't be in check after the move, true if in check after the move
	bool Game::is_in_check_after_move(const Position& start, const Position& end) const{
		Game new_game(*this);
		new_game.board.move(start, end);
		if (new_game.in_check(is_white_turn)){
			return true;
		}
		return false;
	}

	void Game::make_move(const Position& start, const Position& end) {
		ReturnCode return_code = check_shape_clear_move(start,end);
		switch(return_code){
			case ReturnCode::SUCCESS: break;
			case ReturnCode::START_POS_NOT_ON_BOARD: 	throw Exception("start position is not on board"); break;
			case ReturnCode::END_POS_NOT_ON_BOARD: 		throw Exception("end position is not on board"); break;
			case ReturnCode::CAPTURE_OWN_PIECE: 		throw Exception("cannot capture own piece"); break;
			case ReturnCode::EMPTY_START_POS: 			throw Exception("no piece at start position"); break;
			case ReturnCode::MISMATCHED_TURN_COLOR: 	throw Exception("piece color and turn do not match"); break;
			case ReturnCode::ILLEGAL_MOVE_SHAPE: 		throw Exception("illegal move shape"); break;
			case ReturnCode::ILLEGAL_CAPTURE_SHAPE: 	throw Exception("illegal capture shape"); break;
			case ReturnCode::PATH_NOT_CLEAR: 			throw Exception("path is not clear"); break;
		}
		if (is_in_check_after_move(start,end) == true){
			throw Exception("move exposes check");
		}
		///////////////////////
		//move               //
		board.move(start, end);
		///////////////////////
		if ((board(end)->to_ascii() == 'P'&& end.second == '8') || (board(end)->to_ascii() == 'p' && end.second == '1')){
			char queen = is_white_turn ? 'Q' : 'q';
			board.remove_piece(end);
			board.add_piece(end,queen);
		}

		//alternate the turn
		is_white_turn = !is_white_turn;
	}

	bool Game::in_check(const bool& white) const {
		Position king_pos(0,0);
		const char king_char = white ? 'K' : 'k';
		
		for (Board::const_iterator cit = board.cbegin(); cit != board.cend();++cit){
			
			if (board(*cit) != nullptr && board(*cit)->to_ascii() == king_char){
				king_pos = *cit;
			}
		}
		assert(king_pos.first != 0 && king_pos.second != 0); //make sure a corresponding position for king is found

		for (Board::const_iterator cit = board.cbegin(); cit != board.cend();++cit){
			if (board(*cit) != nullptr){
				if (check_shape_clear_move(*cit, king_pos, true) == ReturnCode::SUCCESS){
					return true; //in check
				}
			}
		}
		return false; //not in check
	}

	bool Game::in_mate(const bool& white) const {
		if (!in_check(white)) return false;
		for (Board::const_iterator cit = board.cbegin(); cit != board.cend();++cit){//iterate over all pieces
			if (board(*cit) != nullptr && is_valid_designator(board(*cit)->to_ascii(), white) ){
				for (Board::const_iterator ccit = board.cbegin(); ccit != board.cend();++ccit){//iterate over all positions for the piece
					if(check_shape_clear_move(*cit, *ccit) == ReturnCode::SUCCESS && is_in_check_after_move(*cit, *ccit) == false){ // if not in check after move
						return false;
					}
				}
			}
		}
		return true;
	}

	bool Game::in_stalemate(const bool& white) const {
		if (in_check(white)) return false;
		for (Board::const_iterator cit = board.cbegin(); cit != board.cend();++cit){//iterate over all pieces
			if (board(*cit) != nullptr && is_valid_designator( board(*cit)->to_ascii(), white)){
				for (Board::const_iterator ccit = board.cbegin(); ccit != board.cend();++ccit){//iterate over all positions for the piece
					if(check_shape_clear_move(*cit, *ccit) == ReturnCode::SUCCESS && is_in_check_after_move(*cit, *ccit) == false){ // if not in check after move
						return false;
					}
				}
			}
		}
		return true;
	}

    // Return the total material point value of the designated player
    int Game::point_value(const bool& white) const {
		int sum = 0;
		for (Board::const_iterator cit = board.cbegin(); cit != board.cend();++cit){//iterate over all pieces
			if (board(*cit) != nullptr && is_valid_designator( board(*cit)->to_ascii(), white)){
				sum += board(*cit)->point_value();
			}
		}
        return sum;
    }

      std::istream& operator>> (std::istream& is, Game& game) {
		  //TODO: why is "is" an ifstream in main when calling this function, but "istream" inside the function？？
		char curr_char = 0;

		for (Board::const_iterator cit = game.board.cbegin(); cit != game.board.cend() ; ++cit){ //loop will stop if iterator reached the end but there is still char to read (the last char, w or b)
			if (!(is >> curr_char)){
				throw Exception("Eof reached unexpectedly");
			}
			const Piece * p = game.board(*cit);
			if (p == nullptr && curr_char == '-'){
				continue;
			}
			if (p != nullptr && curr_char == '-'){
				game.board.remove_piece(*cit);
				continue;
			}
			if (p == nullptr && curr_char != '-'){
				game.board.add_piece(*cit, curr_char);
				continue;
			}
			if (p->to_ascii() == curr_char){
				continue;
			}
			if (p->to_ascii() != curr_char && curr_char != '-'){
				game.board.remove_piece(*cit);
				// std::cout<<curr_char<<std::endl;
				game.board.add_piece(*cit, curr_char);
			}
		}
		char turn = 0;
		if(!(is >> turn)) throw Exception("Eof reached unexpectedly");
		if (turn != 'w' && turn != 'b') throw Exception("Turn designator should only be w or b");
		game.is_white_turn = (turn == 'w');
		char end = 0;
		if (is >> end) throw Exception("Should reach Eof, but didn't");
		return is;
	}

    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
	std::ostream& operator<< (std::ostream& os, const Game& game) {
		// Write the board out and then either the character 'w' or the character 'b', depending on whose turn it is
		return os << game.board << (game.turn_white() ? 'w' : 'b');
	}
}
