#include"Computer.h"


namespace Paisho{

int ply;

    Move minimax(Board b, int depth, int player, Move *best_move){
        //int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth == 0 || Bitboards::check_win(&b) != -1){
            return evaluate(&b);
        }

        int value;
        Moves curr_moves;
        Move out_move;
        if (player == WHITE){
            value = -999999;
            curr_moves = Bitboards::get_moves(b, WHITE);
            for(int i = 0; i < curr_moves.move_count; i++){
                ply++;
                Bitboards::make_move(&b, player, curr_moves.movelist[i]);
                int t_val = minimax(b, depth-1, BLACK, &out_move);
                ply--;
                if (t_val > value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
            }
            return value;
        }else{
            value = 999999;
            curr_moves = Bitboards::get_moves(b, BLACK);
            for(int i = 0; i < curr_moves.move_count; i++){
                ply++;
                Bitboards::make_move(&b, player, curr_moves.movelist[i]);
                int t_val = minimax(b, depth-1, WHITE, &out_move);
                ply--;
                if (t_val < value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
            }
            return value;
        }
    }


    int evaluate(Board *b){
        return 5;
    }


}

