#ifndef COMPUTER_H_DEF
#define COMPUTER_H_DEF

#include"Bitboard.h"

namespace Paisho{

    constexpr int tier1_w = 50;
    constexpr int tier2_w = 30;
    constexpr int tier3_w = 20;
    constexpr int tier4_w = 10;
    constexpr int wild_w = 400;
    constexpr int accent_hand_w = 60;
    constexpr int harm_pieces_w = 30;

    constexpr int piece_onboard_score(int piece){
        switch(piece){
            case w3: return 20;
            case w4: return 25;
            case w5: return 30;
            case r3: return 20;
            case r4: return 25;
            case r5: return 30;
            case lotus: return 150;
            case orchid: return 100;
            default: return 0;
        }
    }

    const Bitboard square ((Bitboard(1) << j10) | (Bitboard(1) << j11) | (Bitboard(1) << k10) | (Bitboard(1) << k11));
    const Bitboard tier1 = square | (square >> EAST*3) | (square >> NORTH*3) | ((square >> EAST*3) >> NORTH*3);
    const Bitboard open_square = Bitboard(1) << j9 | 
                                Bitboard(1) << k9 | 
                                Bitboard(1) << l10 | 
                                Bitboard(1) << l11 | 
                                Bitboard(1) << k12 |
                                Bitboard(1) << j12 |
                                Bitboard(1) << i10 | 
                                Bitboard(1) << i11;
    const Bitboard tier2 = open_square | 
                           open_square >> EAST*3 | 
                           open_square >> NORTH*3 | 
                           open_square >> NORTH*3 >> EAST*3 | 
                           Bitboard(1) << k13 |
                           Bitboard(1) << l12 |
                           Bitboard(1) << m11 | 
                           Bitboard(1) << g13 |
                           Bitboard(1) << f12 | 
                           Bitboard(1) << e11 |
                           Bitboard(1) << g5 | 
                           Bitboard(1) << f6 | 
                           Bitboard(1) << e7 |
                           Bitboard(1) << k5 | 
                           Bitboard(1) << l6 | 
                           Bitboard(1) << m7;
        const Bitboard tier3p1 = square << NORTH*5 |
                                square << NORTH*4 |
                                square << NORTH*5 << EAST |
                                square << NORTH*3 >> EAST |
                                square << NORTH*3 >> EAST*2 |
                                square << NORTH*5 >> EAST*4 |
                                square << NORTH*5 >> EAST*3 |
                                Bitboard(1) << i12 |
                                Bitboard(1) << m16 |
                                Bitboard(1) << e16;
        const Bitboard tier3p2 = square << EAST*5 << NORTH |
                                square << EAST*5 |
                                square << EAST*4 |
                                square << EAST*3 >> NORTH |
                                square << EAST*3 >> NORTH*2 |
                                square << EAST*5 >> NORTH*4 |
                                square << EAST*5 >> NORTH*3 |
                                square << EAST*4 >> NORTH*3 |
                                Bitboard(1) << l9 |
                                Bitboard(1) << p13 |
                                Bitboard(1) << p5;
        const Bitboard tier3p3 = square >> EAST*8 << NORTH |
                                 square >> EAST*8 |
                                 square >> EAST*7 |
                                 square >> EAST*8 >> NORTH*4 |
                                 square >> EAST*8 >> NORTH*3 |
                                 square >> EAST*7 >> NORTH*3 |
                                 square >> EAST*6 >> NORTH |
                                 square >> EAST*6 >> NORTH*2 |
                                 Bitboard(1) << b13 |
                                 Bitboard(1) << b5 |
                                 Bitboard(1) << f9;
        const Bitboard tier3p4 = square >> NORTH*8 << EAST |
                                square >> NORTH*8 | 
                                square >> NORTH*7 |
                                square >> NORTH*6 >> EAST |
                                square >> NORTH*6 >> EAST*2 |
                                square >> NORTH*8 >> EAST*4 |
                                square >> NORTH*8 >> EAST*3 |
                                square >> NORTH*7 >> EAST*3 |
                                Bitboard(1) << i6 |
                                Bitboard(1) << e2 |
                                Bitboard(1) << m2;
        const Bitboard tier3 = tier3p1 | tier3p2 | tier3p3 | tier3p4;
        const Bitboard tier4 = ~(tier1 | tier2 | tier3) ^ Gates;
    
    //const Bitboard tier2 = 

    int minimax(const Board& b, int depth, int player, Move& eval);
    int negamax(const Board& b, int depth, int player, Move& eval);
    int ab_prune_neg(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    int ab_prune(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    //void order_moves(const Moves& in, Moves& out);
    void order_moves(Moves& in);
    int evaluate(const Board& b);

}

#endif
