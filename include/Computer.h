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

    enum hash_flags{
        hf_alpha,
        hf_beta,
        hf_exact,
        hf_nohash=-1,
    };


    typedef struct HashEntry{
        int depth;
        int flag;
        int val;
    } HashEntry;
    typedef std::unordered_map<size_t, HashEntry> HashTable;

    int read_hash_entry(int alpha, int beta, int depth);
    void write_hash_entry(int score, int depth, int flag);

    int minimax(const Board& b, int depth, int player, Move& eval);
    int negamax(const Board& b, int depth, int player, Move& eval);
    int ab_prune_neg(const Board& b, int depth, int alpha, int beta, int player, Move& eval);
    void ab_prune(const Board& b, int depth, int alpha, int beta, int player, Move* eval, HashTable * shared_hash, int& eval_score);
    //void order_moves(const Moves& in, Moves& out);
    int prune_helper(const Board& b, int depth, int player, Move& best_move);
    void order_moves(Moves& in);
    int evaluate(const Board& b);

}


#endif
