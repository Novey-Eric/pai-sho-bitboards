#ifndef COMPUTER_H_DEF
#define COMPUTER_H_deF

#include"Bitboard.h"

namespace Paisho{
    int minimax(Board *b, int depth, int player, Move *eval);
    int negamax(Board *b, int depth, int player, Move *eval);
    int ab_prune_neg(Board *b, int depth, int alpha, int beta, int player, Move *eval);
    int ab_prune(Board *b, int depth, int alpha, int beta, int player, Move *eval);
    void order_moves(Moves *in, Moves *out);
    int evaluate(Board *b);

}


#endif
