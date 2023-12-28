#ifndef COMPUTER_H_DEF
#define COMPUTER_H_deF

#include"Bitboard.h"

namespace Paisho{
    Move minimax(Board *b, int depth, int player, Move *out);
    Move negamax(Board *b, int depth, int player, Move *out);
    int evaluate(Board *b);

}


#endif
