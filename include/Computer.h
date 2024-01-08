#ifndef COMPUTER_H_DEF
#define COMPUTER_H_deF

#include"Bitboard.h"

namespace Paisho{


    constexpr int piece_onboard_score(int piece){
        switch(piece){
            case w3: return 30;
            case w4: return 35;
            case w5: return 40;
            case r3: return 30;
            case r4: return 35;
            case r5: return 40;
            case lotus: return 250;
            case orchid: return 200;
            default: return 0;
        }
    }


    int minimax(const Board& b, int depth, int player, Move& eval);
    int negamax(const Board& b, int depth, int player, Move& eval);
    int ab_prune_neg(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    int ab_prune(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    //void order_moves(const Moves& in, Moves& out);
    void order_moves(Moves& in);
    int evaluate(const Board& b);

}


#endif
