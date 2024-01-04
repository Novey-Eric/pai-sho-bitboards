#ifndef COMPUTER_H_DEF
#define COMPUTER_H_deF

#include"Bitboard.h"

namespace Paisho{
    int minimax(const Board& b, int depth, int player, Move& eval);
    int negamax(const Board& b, int depth, int player, Move& eval);
    int ab_prune_neg(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    int ab_prune(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    void order_moves(const Moves& in, Moves& out);
    int evaluate(const Board& b);

}


#endif
