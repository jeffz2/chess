#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{
	enum class ReturnCode {SUCCESS = 0, START_POS_NOT_ON_BOARD = 1, END_POS_NOT_ON_BOARD = 2, CAPTURE_OWN_PIECE = 3, EMPTY_START_POS = 4,
		MISMATCHED_TURN_COLOR = 5,ILLEGAL_MOVE_SHAPE = 6,ILLEGAL_CAPTURE_SHAPE = 7,PATH_NOT_CLEAR = 8};

	class Game {

	public:
		// This default constructor initializes a board with the standard piece positions, 
		// and sets the state to white's turn
		Game();

		//clears the object
		void clear();

		// Returns true if it is white's turn
		/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
		bool turn_white() const { return is_white_turn; }

		// Check whether a move is possible by considering shape and clear path (if necessary), but not "checked" position.
		// Return 0 if move is possible (considering only shape and clear path)
		ReturnCode check_shape_clear_move(const Position& start, const Position& end, bool checking_check =false) const;

    	/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
   		// Displays the game by printing it to stdout
		void display() const { board.display(); }

		//return false if it won't be in check after the move, true if in check
		bool is_in_check_after_move(const Position& start, const Position& end) const;

    	/////////////////////////////////////
		// DO NOT MODIFY THIS FUNCTION!!!! //
		/////////////////////////////////////
    	// Checks if the game is valid
		bool is_valid_game() const { return board.has_valid_kings(); }

		// Check if the designator is valid
		bool is_valid_designator(const char& c, bool white) const{ return board.is_valid_designator(c, white);}

		// Attempts to make a move given the specified start and end positions. 
		// If successful, the move is made and the turn is switched white <-> black. Otherwise, an exception is thrown
		void make_move(const Position& start, const Position& end);

		// Returns true if the designated player is in check
		bool in_check(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_mate(const bool& white) const;

		// Returns true if the designated player is in mate
		bool in_stalemate(const bool& white) const;

        // Return the total material point value of the designated player
        int point_value(const bool& white) const;

		// Returns true if the path along the move is clear
		bool is_clear_path(const Position& start, const Position& end) const;
		
	private:
		// The board
		Board board;

		// Whether it is white's turn or not
		bool is_white_turn;

        // Writes the board out to a stream
        friend std::ostream& operator<< (std::ostream& os, const Game& game);

        // Reads the board in from a stream
        friend std::istream& operator>> (std::istream& is, Game& game);
	};
}
#endif // GAME_H
