#include"Computer.h"
#include <cstring>
#include <chrono>
#include <iostream>
#include <cmath>
#include <mutex>
#include <thread>
#include <functional>

namespace Paisho{

using namespace std;
using namespace std::chrono;
using namespace Bitboards;

    
    bool compare_moves(const Move& first, const Move& second){
        bool spec1 = (((first & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET) ||\
            ((first & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == orchid) ||\
            ((first & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == lotus) ||\
            ((first & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == orchid) ||\
            ((first & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == lotus) ||\
            ((first & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET == PLACE) \
            );
/*
        bool spec2 = (((*t_move & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET) ||\
            ((*t_move & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == orchid) ||\
            ((*t_move & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET == lotus) ||\
            ((*t_move & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == orchid) ||\
            ((*t_move & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET == lotus) ||\
            ((*t_move & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET == PLACE) \
            );
*/
        return (spec1);
    }

    int read_hash_entry(const HashTable& ht, size_t key, int alpha, int beta, int depth){
        if(!ht.count(key))
            return hf_nohash;

        const HashEntry* he = &ht.at(key);
        if (he->depth >= depth){
            if(he->flag == hf_exact)
                return he->val;
            if(he->flag == hf_alpha && he->val <= alpha)
                return alpha;
            if(he->flag == hf_beta && he->val >= beta)
                return beta;
        }
        return hf_nohash;
    }

    void write_hash_entry(HashTable& ht, size_t key, int score, int depth, int flag){
        HashEntry he = {depth, flag, score};
        ht[key] = he;
    }


int ply;
std::mutex hash_mtx;
std::mutex move_mtx;



    //shared hash is used for checking duplicate positions.
    void ab_prune(const Board& b, int depth, int alpha, int beta, int player, Move* best_move, HashTable * shared_hash, int& eval_ret){
        //int p_mult = player ? -1 : 1; //WHITEs enum value is 0
    //int read_hash_entry(const HashTable& ht, size_t key, int alpha, int beta, int depth){
        int score;
        size_t curr_hash = get_hash(b);
        hash_mtx.lock();
        score = read_hash_entry(*shared_hash, curr_hash, alpha, beta, depth);
        hash_mtx.unlock();
        if (score != hf_nohash){
            //return score;
            eval_ret = score;
            return;
        }

        int eval = evaluate(b);
        if (depth <= 0 || std::abs(eval) >= 999999){
            eval += depth;
            eval_ret = eval;
            return;
        }
        Board b_copy;
        int value;
        Moves curr_moves;
        Move out_move;
        //Moves ordered_moves;

        if (player == WHITE){
            value = -9999999;

            curr_moves = Bitboards::get_moves(b, WHITE);
            std::random_shuffle(curr_moves.begin(), curr_moves.end());
            if(!curr_moves.size())
                value = 0;
            //cout << "get_moves dur: " << dur_get_moves.count() << " movecnt: " << curr_moves.move_count<< endl;

            //curr_moves.sort();
            //order_moves(&curr_moves, &ordered_moves);
            for(auto t_move : curr_moves){
            //for(int i = 0; i < curr_moves.size(); i++){
                b_copy = b;
                //std::cout<< "total moves: " << curr_moves.move_count << " at: " << i << " with depth " << depth << std::endl;
                ply++;
                //Bitboards::make_move(&b_copy, player, ordered_moves.movelist[i]);
                Bitboards::make_move(b_copy, player, t_move);

                int t_val;
                ab_prune(b_copy, depth-1, alpha, beta, BLACK, &out_move, shared_hash, t_val);
                ply--;
                if (t_val > value){
                    value = t_val;
                    move_mtx.lock();
                    *best_move = t_move;
                    move_mtx.unlock();
                }
                if (value > beta){
                    hash_mtx.lock();
                    write_hash_entry(*shared_hash, curr_hash, value, depth, hf_beta);
                    hash_mtx.unlock();
                    eval_ret = beta;
                    return;
                }
                alpha = std::max(alpha, value);
            }

        } else{
            value = 9999999;
            curr_moves = Bitboards::get_moves(b, BLACK);
            std::random_shuffle(curr_moves.begin(), curr_moves.end());
            if(!curr_moves.size())
                value = 0;
            //curr_moves.sort();
            //order_moves(&curr_moves, &ordered_moves);

            for(auto t_move : curr_moves){
                b_copy = b;
                ply++;
                Bitboards::make_move(b_copy, player, t_move);
                int t_val;
                ab_prune(b_copy, depth-1, alpha, beta, WHITE, &out_move, shared_hash, t_val);
                ply--;
                if (t_val < value){
                    value = t_val;
                    move_mtx.lock();
                    *best_move = t_move;
                    move_mtx.unlock();
                }
                if (value < alpha){
                    hash_mtx.lock();
                    write_hash_entry(*shared_hash, curr_hash, value, depth, hf_alpha);
                    hash_mtx.unlock();
                    eval_ret = alpha;
                    return;
                }
                beta = std::min(beta, value);
            }
        }
        eval_ret = value;
        return;
        //return value;
    }


    int prune_helper(const Board& b, int depth, int player, Move& best_move){
        HashTable shared_hash;
        int num_threads = 8;
        std::thread t_arr[num_threads];
        int eval_arr[num_threads];
        Move move_arr[num_threads];
        for(int i = 0; i < num_threads; i++){
            t_arr[i] = std::thread(std::cref(ab_prune), b, depth, -99999, 99999, player, &move_arr[i], &shared_hash, std::ref(eval_arr[i]));
        }
        for (int i = 0; i < num_threads; i++){
            t_arr[i].join();
        }
        int t_score = -99999;
        for(int i = 0; i < num_threads; i++){
            if(eval_arr[i] > t_score){
                t_score = eval_arr[i];
                best_move = move_arr[i];
            }
        }
        return t_score;
    }
    
/*
    int minimax(Board *b, int depth, int player, Move *best_move){
        //int p_mult = player ? -1 : 1; //WHITEs enum value is 0

        if (depth == 0 || Bitboards::check_win(b) != -1){
            return evaluate(b);
        }

        Board b_copy;
        //memcpy(&b_copy, b, sizeof(Board));
        b_copy = *b;
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
                //memcpy(&b_copy, b, sizeof(Board));
                b_copy = *b;
                
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
                //memcpy(&b_copy, b, sizeof(Board));
                b_copy = *b;
            }
            return value;
        }
    }
*/
    



    int get_quadrant(int square){
        int row = (square/17)+1;
        int col = (square%17)+1;
        if (row < 9 && col < 9){
            return 4;
        } else if (row > 9 && col < 9){
            return 1;
        } else if (row < 9 && col > 9){
            return 3;
        } else if (row > 9 && col > 9){
            return 2;
        } else{
            return -1;
        }

    }

    float get_radius(int square){
        int row = (square/17) - 8;
        int col = (square%17) - 8;
        float rad = std::sqrt(row*row + col*col);
        return rad;

    }

    
    int eval_helper_harms(const Board& b, int team){
        //keep a map of all the corners registered so far. 
        //Start at one of the corners, remove the connection in the bitboard to another corner.
        //register that new corner
        //If there is no connection from that corner to somewhere else, continue, but remove the corner from the bitboard
        //the map should be (square, corners_shared) pairs
  
        std::map<int, int> square_cnt;
        int harm_cnt = 0;
        const std::deque<std::pair<int, int>> *team_pairs;
        if (team == WHITE){
            team_pairs = &b.white_harm_pairs;
        } else{
            team_pairs = &b.black_harm_pairs;
        }

        int doub_cnt = 0;
        for (auto i : *team_pairs){
            int q1 = get_quadrant(i.first);
            int q2 = get_quadrant(i.second);
            if (q1 != q2 && q1 != -1 && q2 != -1){
                harm_cnt++;
                if(square_cnt.count(i.first)){
                    square_cnt[i.first]++;
                } else{ 
                    square_cnt[i.first] = 1;
                }
                if(square_cnt.count(i.second)){
                    square_cnt[i.second]++;
                } else{ 
                    square_cnt[i.second] = 1;
                }
            }
        }
        for(auto i : square_cnt){
            if (i.second > 1){
                doub_cnt++;
            }
        }


        int win_bonus = 0;
        if(doub_cnt >= 4){
            for (auto i = square_cnt.begin(); i != square_cnt.end(); i++){//if using ordered map this will be guaranteed bottom right
                if(i->second <= 1)
                    continue;
                int r1, c1;
                r1 = i->first/17;
                c1 = i->first%17;
                for(auto j = std::next(i, 1); j != square_cnt.end(); j++){//bottom left
                    if(j->second <= 1)
                        continue;
                    int r2, c2;
                    r2 = j->first/17;
                    c2 = j->first%17;
                    for(auto k = std::next(j, 1); k != square_cnt.end(); k++){//top right
                        if(k->second <= 1)
                            continue;
                        int r3, c3;
                        r3 = k->first/17;
                        c3 = k->first%17;
                        for(auto m = std::next(k, 1); m != square_cnt.end(); m++){//top left
                            if(m->second <= 1)
                                continue;
                            int r4, c4;
                            r4 = m->first/17;
                            c4 = m->first%17;
                            if(r1 == r2 && r3 == r4 && c4 == c2 && c1 == c3){
                                win_bonus = 999999;
                            }
                        }
                    }
                }
            }
        }
        

        return 200*harm_cnt + 300*doub_cnt + win_bonus;
    }


    int evaluate(const Board& b){
        //Do white first
        int white_score = 0;
        int black_score = 0;

        for(int i = 0; i <= 7; i++){
            white_score += b.whiteBoards[i].count()*piece_onboard_score(i);
            white_score += (b.whiteBoards[i] & ~Gates).count()*40; //has it moved out of the gate
            black_score += b.blackBoards[i].count()*piece_onboard_score(i);
            black_score += (b.blackBoards[i] & ~Gates).count()*40;
        }

        //black_score += b.blackBoards[lotus].count()*piece_onboard_score(lotus);
        
        white_score += (b.wwild)*400;
        black_score += (b.bwild)*400;

        int accent_hand_weight = 100;
        white_score += __builtin_popcount(b.whiteAccents)*accent_hand_weight;
        black_score += __builtin_popcount(b.blackAccents)*accent_hand_weight;

        //int center = i9;
        //check for harmonizing pieces on the board
        int harm_pieces_w = 30;
        for(int i = 0; i <= 5; i++){
            int harm_index = Bitboards::harm_map(i);

            int n_piece = b.whiteBoards[i].count();
            int n_harm_pieces = Bitboards::reverse_harm_lookup(b, harm_index, WHITE).count();
            n_harm_pieces = std::min(n_harm_pieces, n_piece);
            white_score += n_harm_pieces*harm_pieces_w;

            int bn_piece = b.blackBoards[i].count();
            int bn_harm_pieces = Bitboards::reverse_harm_lookup(b, harm_index, BLACK).count();
            bn_harm_pieces = std::min(bn_harm_pieces, bn_piece);
            black_score += bn_harm_pieces*harm_pieces_w;
        }

        for (int i = 0; i < NUM_SQUARES; i++){
            if(b.whiteBoards[allflowers][i]){
                float r = get_radius(i);
                if(r <= 3){
                    white_score += 50;
                } else if (r <= 5){
                    white_score += 20;
                }
            }
            if(b.blackBoards[allflowers][i]){
                float r = get_radius(i);
                if(r <= 3){
                    black_score += 50;
                } else if (r <= 5){
                    black_score += 20;
                }
            }
    
        }
        

        white_score += eval_helper_harms(b, WHITE);
        black_score += eval_helper_harms(b, BLACK);

        return white_score - black_score;
    }


}

