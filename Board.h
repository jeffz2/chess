#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"

namespace Chess
{	
  class Board {

		// Throughout, we will be accessing board positions using Position defined in Piece.h.
		// The assumption is that the first value is the column with values in
		// {'A','B','C','D','E','F','G','H'} (all caps)
		// and the second is the row, with values in {'1','2','3','4','5','6','7','8'}

	public:
		// Default constructor
		Board();
		// Copy constructor
		Board(const Board& b);
		// Assignment constructor
		Board& operator=(const Board& rhs);
		// Returns a const pointer to the piece at a prescribed location if it exists, or nullptr if there is nothing there.
		const Piece* operator() (const Position& position) const;

		// Attempts to add a new piece with the specified designator, at the given position.
		// Throw exception for the following cases:
		// -- the designator is invalid, throw exception with error message "invalid designator"
		// -- the specified position is not on the board, throw exception with error message "invalid position"
		// -- if the specified position is occupied, throw exception with error message "position is occupied"
		void add_piece(const Position& position, const char& piece_designator);

		//Removes a key at the given position, do nothing if already removed
		//TODO: should I throw exception?
		bool remove_piece(const Position& position);
		// Displays the board by printing it to stdout
		void display() const;
		// Whether or not it's a valid designator
		bool is_valid_designator(const char& c, bool white) const;
		// Returns true if the board has the right number of kings on it
		bool has_valid_kings() const;

		// Iterator class which encapsulates the board iteration logic
		class const_iterator{
		private:
			Position pos;
			
		public:
			const_iterator(Position initial): pos(initial){ }	

			const_iterator& operator++(){
				if (pos.first < 'H'){
					pos.first += 1;
				}
				else{
					pos.first = 'A';
					pos.second -= 1;
				}
				return *this;
			}

			bool operator!=(const const_iterator& rhs) const{
				return !(pos.first == rhs.pos.first && pos.second == rhs.pos.second);
			}
			const Position& operator*() const{
				return pos;
			}
		};

		const_iterator cbegin() const{
			return const_iterator(Position('A','8'));
		}

		const_iterator cend() const{
			return const_iterator(Position('A', '0'));
  		} 

		// Clear the occ map
		void clear();
		// Move a piece from start pos to end pos
		bool move(const Position & start, const Position & end);
		// Destructor
		~Board();
		
	private:
		// The sparse map storing the pieces, keyed off locations
		std::map<Position, Piece*> occ;
        // Write the board state to an output stream
        friend std::ostream& operator<< (std::ostream& os, const Board& board);
	};
}
#endif // BOARD_H
