#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"


#include <vector>
#include <algorithm>
#include <assert.h>
namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}
  Board::Board(const Board& b){
    for(std::map<Position, Piece*>::const_iterator it = b.occ.cbegin(); it != b.occ.cend(); ++it){
      add_piece(it->first,it->second->to_ascii());
    }
  }
  // Helper function for destructor
  void Board::clear(){
    for(std::map<Position, Piece*>::iterator it = occ.begin(); it != occ.end(); ++it) 
      if (it->second) 
        delete it->second;
  }
  Board::~Board(){
    clear();
  }
  Board& Board::operator=(const Board& rhs){//TODO: do we need this?
    clear();
    for(std::map<Position, Piece*>::const_iterator it = rhs.occ.cbegin(); it != rhs.occ.cend(); ++it){
      add_piece(it->first,it->second->to_ascii());
    }
    return *this;
  }
  const Piece* Board::operator()(const Position& position) const {
    std::map<Position, Piece*>::const_iterator it = occ.find(position);
    if (it != occ.end()){
      return it->second;
    }
    return nullptr;
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {
     //TODO: a better way to do this?
    if (!is_valid_designator(piece_designator, true) && !is_valid_designator(piece_designator,false)){//if the designator does not belong to both white and black designators
      throw Exception("invalid designator\n");
    }
    if (position.first < 'A' || position.first > 'H' || position.second < '1' || position.second > '8'){
      throw Exception("invalid position\n");
    }
    if ((*this)(position) != nullptr){
      throw Exception("position is occupied\n");
    }
    occ[position] = create_piece(piece_designator);
  }

  bool Board::remove_piece(const Position& position){
    if (occ.find(position) == occ.end())
      return false;
    delete occ[position];
    occ.erase(position);
    return true;
  }

  bool Board::is_valid_designator(const char& c, bool white) const{
    std::vector<char> designators;
		if (white){
			designators = {'K', 'Q', 'R', 'B', 'N', 'P',  'M'};
		}
		else{
			designators = {'k', 'q', 'r', 'b', 'n',  'p', 'm'};
		}
    if (std::find(designators.begin(), designators.end(), c) != designators.end()){
      return true;
    }
    return false;
  }

  void Board::display() const{
    Terminal::set_default();
    Terminal::color_all(false,Terminal::BLACK, Terminal::BLUE);
    std::cout<<"  ";
    for (char c = 'A'; c <= 'H'; c++){
      std::cout<<"   " << c << "  ";
    }
    std::cout<<"    ";
    Terminal::set_default();
    std::cout<< std::endl;
    for (char row = '8'; row >= '1'; row--){
      for (int i = -1; i <= 1; i++){
        Terminal::color_all(false,Terminal::BLACK, Terminal::BLUE);
        if (i == 0) std::cout<<' '<<row<<' ';
        else std::cout<<"   ";
        for (char col = 'A'; col <= 'H'; col++){
          
          if ((col-'A'+row-'0')%2==0){
            Terminal::color_all(false,Terminal::BLACK,Terminal::WHITE);
          }
          else{
            Terminal::color_all(false,Terminal::BLACK,Terminal::GREEN);
          }
          if (i == 0){
            const Piece * p = (*this)(Position(col, row));
            if (p) std::cout<<"  "<< (p->to_unicode()) << "   ";
            else std::cout<<"      ";
          }
          else std::cout<<"      ";
        }
        Terminal::color_all(false,Terminal::BLACK, Terminal::BLUE);
        if (i == 0) std::cout<<' '<<row<<' ';
        else std::cout<<"   ";
        Terminal::set_default();
        std::cout<<std::endl;
      }
    }
    Terminal::color_all(false,Terminal::BLACK, Terminal::BLUE);
    std::cout<<"   ";
    for (char c = 'A'; c <= 'H'; c++){
      std::cout<<"  " << c << "   ";
    }
    std::cout<<"   ";
    Terminal::set_default();
    std::cout<<std::endl;
  }

  // Return true if the board has valid kings
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin(); it != occ.end(); it++) {
      if (it->second) {
        switch (it->second->to_ascii()) {
          case 'K':
            white_king_count++;
            break;
          case 'k':
            black_king_count++;
            break;
        }
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }

  //TODO:modified    
  bool Board::move(const Position& start, const Position& end){
    assert(start!=end);
    if(occ.find(start) == occ.end())
      return false; // TODO:throw exception at upper level?
    occ[end] = occ[start];
    occ.erase(start);
    return true;
  }
}
