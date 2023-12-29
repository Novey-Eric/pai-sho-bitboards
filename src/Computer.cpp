#include"Computer.h"
#include <cstring>
#include <iostream>


namespace Paisho{

int ply;
    
    void order_moves(Moves *in, Moves *out){
        int good_move = 0;
        int bad_move = MOVELIST_LEN-1;
        for (int i = 0; i < in->move_count; i++){
            Move *t_move = &in->movelist[i];
            if (((*t_move & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET) ||\
                ((*t_move & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == orchid) ||\
                ((*t_move & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == lotus) ||\
                ((*t_move & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == orchid) ||\
                ((*t_move & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == lotus) ||\
                ((*t_move & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET == PLACE) \
                ){
                out->movelist[good_move++] = *t_move;
            } else{
                out->movelist[bad_move--] = *t_move;
            }
            out->move_count++;
        }
    }

    int ab_prune(Board *b, int depth, int alpha, int beta, int player, Move *best_move){
        int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth <= 0 || Bitboards::check_win(b) != -1){
            //std::cout<<"eval: "<<eval<<std::endl;
            return evaluate(b);
        }
        Board b_copy;
        int value;
        Moves curr_moves;
        Move out_move;
        Moves ordered_moves;

        if (player == WHITE){
            value = -999999;
            curr_moves = Bitboards::get_moves(b_copy, WHITE);
            //order_moves(&curr_moves, &ordered_moves);
            for(int i = 0; i < curr_moves.move_count; i++){
                memcpy(&b_copy, b, sizeof(Board));
                //std::cout<< "total moves: " << curr_moves.move_count << " at: " << i << " with depth " << depth << std::endl;
                ply++;
                Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
                //Bitboards::make_move(&b_copy, player, ordered_moves.movelist[i]);
                int t_val = ab_prune(&b_copy, depth-1, alpha, beta, BLACK, &out_move);
                ply--;
                if (t_val > value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
                if (value > beta)
                    break;
                alpha = std::max(alpha, value);
            }

        } else{
            value = 999999;
            curr_moves = Bitboards::get_moves(b_copy, BLACK);
            //order_moves(&curr_moves, &ordered_moves);
            for(int i = 0; i < curr_moves.move_count; i++){
                memcpy(&b_copy, b, sizeof(Board));
                //std::cout<< "total moves: " << curr_moves.move_count << " at: " << i << " with depth " << depth << std::endl;
                ply++;
                Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
                //Bitboards::make_move(&b_copy, player, ordered_moves.movelist[i]);
                int t_val = ab_prune(&b_copy, depth-1, alpha, beta, WHITE, &out_move);
                ply--;
                if (t_val < value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
                if (value < alpha)
                    break;
                beta = std::min(beta, value);
            }
        }
        return value;
    }

    int ab_prune_neg(Board *b, int depth, int alpha, int beta, int player, Move *best_move){
        int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth <= 0 || Bitboards::check_win(b) != -1){
            int eval = evaluate(b);
            //std::cout<<"eval: "<<eval<<std::endl;
            return p_mult*eval;
        }
        int next_player = player ? WHITE : BLACK;
        Board b_copy;
        memcpy(&b_copy, b, sizeof(Board));
        int value;
        Moves curr_moves;
        Move out_move;
        value = -999999;
        curr_moves = Bitboards::get_moves(b_copy, WHITE);
        for(int i = 0; i < curr_moves.move_count; i++){
            //std::cout<< "total moves: " << curr_moves.move_count << " at: " << i << " with depth " << depth << std::endl;
            ply++;
            Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
            int t_val = -ab_prune_neg(&b_copy, depth-1, -beta, -alpha, next_player, &out_move);
            ply--;
            if (t_val > value){
                value = t_val;
                *best_move = curr_moves.movelist[i];
            }
            memcpy(&b_copy, b, sizeof(Board));
            alpha = std::max(alpha, value);
            if (alpha >= beta){
                break;
            }
        }
        return value;
    }


    int negamax(Board *b, int depth, int player, Move *best_move){
        int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth == 0 || Bitboards::check_win(b) != -1){
            return p_mult*evaluate(b);
        }
        int next_player = player ? WHITE : BLACK;

        Board b_copy;
        memcpy(&b_copy, b, sizeof(Board));
        int value;
        Moves curr_moves;
        Move out_move;
        value = -999999;
        curr_moves = Bitboards::get_moves(b_copy, WHITE);
        for(int i = 0; i < curr_moves.move_count; i++){
            ply++;
            Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
            int t_val = -minimax(&b_copy, depth-1, next_player, &out_move);
            ply--;
            if (t_val > value){
                value = t_val;
                *best_move = curr_moves.movelist[i];
            }
            memcpy(&b_copy, b, sizeof(Board));
            
        }
        return value;
    }

    

    int minimax(Board *b, int depth, int player, Move *best_move){
        //int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth == 0 || Bitboards::check_win(b) != -1){
            return evaluate(b);
        }

        Board b_copy;
        memcpy(&b_copy, b, sizeof(Board));
        int value;
        Moves curr_moves;
        Move out_move;
        if (player == WHITE){
            value = -999999;
            curr_moves = Bitboards::get_moves(b_copy, WHITE);
            for(int i = 0; i < curr_moves.move_count; i++){
                ply++;
                Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
                int t_val = minimax(&b_copy, depth-1, BLACK, &out_move);
                ply--;
                if (t_val > value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
                memcpy(&b_copy, b, sizeof(Board));
                
            }
            return value;
        }else{
            value = 999999;
            curr_moves = Bitboards::get_moves(b_copy, BLACK);
            for(int i = 0; i < curr_moves.move_count; i++){
                ply++;
                Bitboards::make_move(&b_copy, player, curr_moves.movelist[i]);
                int t_val = minimax(&b_copy, depth-1, WHITE, &out_move);
                ply--;
                if (t_val < value){
                    value = t_val;
                    *best_move = curr_moves.movelist[i];
                }
                memcpy(&b_copy, b, sizeof(Board));
            }
            return value;
        }
    }

    
    std::map<int, int> piece_onboard_score{
                            {w3, 30},
                            {w4, 35},
                            {w5, 40},
                            {r3, 30},
                            {r4, 35},
                            {r5, 40},
                            {lotus, 150},
                            {orchid, 100},
                            };


    int evaluate(Board *b){
        //Do white first
        int white_score = 0;
        int black_score = 0;

        for(int i = 0; i <= 5; i++){
            white_score += b->whiteBoards[i].count()*piece_onboard_score[i];
            black_score += b->blackBoards[i].count()*piece_onboard_score[i];
        }
        white_score += b->whiteBoards[orchid].count()*piece_onboard_score[orchid];
        black_score += b->blackBoards[orchid].count()*piece_onboard_score[orchid];

        white_score += b->whiteBoards[lotus].count()*piece_onboard_score[lotus];
        black_score += b->blackBoards[lotus].count()*piece_onboard_score[lotus];
        
        white_score += (b->wwild)*400;
        black_score += (b->bwild)*400;

        int accent_hand_weight = 100;
        white_score += __builtin_popcount(b->whiteAccents)*accent_hand_weight;
        black_score += __builtin_popcount(b->blackAccents)*accent_hand_weight;

        //int center = i9;
        //check for harmonizing pieces on the board
        int harm_pieces_w = 30;
        for(int i = 0; i <= 5; i++){
            int harm_index = Bitboards::harm_map[i];

            int n_piece = b->whiteBoards[i].count();
            int n_harm_pieces = Bitboards::reverse_harm_lookup(b, harm_index, WHITE).count();
            n_harm_pieces = std::min(n_harm_pieces, n_piece);
            white_score += n_harm_pieces*harm_pieces_w;

            int bn_piece = b->blackBoards[i].count();
            int bn_harm_pieces = Bitboards::reverse_harm_lookup(b, harm_index, BLACK).count();
            bn_harm_pieces = std::min(bn_harm_pieces, bn_piece);
            black_score += bn_harm_pieces*harm_pieces_w;
        }

        //keep a map of all the corners registered so far. 
        //Start at one of the corners, remove the connection in the bitboard to another corner.
        //register that new corner
        //If there is no connection from that corner to somewhere else, continue, but remove the corner from the bitboard
        //the map should be (square, corners_shared) pairs
        std::map<int, int> corner_map;
        Bitboard wh_copy = b->otherBoards[WhiteHarms];
        int c1 = get_lsb(wh_copy);
        corner_map[c1] = 1;
        int move;
        int t_square = get_lsb(wh_copy);
        while(t_square != -1){
            if(wh_copy[c1 + EAST]){
                move = EAST:
            } else if (wh_copy[c1 - EAST]){
                move = -EAST:
            } else if (wh_copy[c1 + NORTH]){
                move = NORTH:
            } else if (wh_copy[c1 - NORTH]){
                move = -NORTH:
            } else {
                wh_copy.reset(c1);
                continue;
            }
            
            c1 += move;
            while(wh_copy[c1]){
                wh_copy.reset(c1);
                c1 += move;
            }

            c1 -= move;
            wh_copy.set(c1);

            if (corner_map.contains(c1)){
                corner_map[c1]++;
            } else{
                corner_map[c1] = 1;
            }
            
            t_square = get_lsb(wh_copy);
        }
        //Here we should have a corner_map with number of corners and shared corners having a value >1
        

        return white_score - black_score;
    }


}

