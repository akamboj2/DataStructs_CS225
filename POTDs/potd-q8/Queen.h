#ifndef _QUEEN_H
#define _QUEEN_H
#include <string>
using std::string;
#include "Piece.h"
class Queen : public Piece {
  public:
    string getType(){ return "Queen";}
};

#endif
