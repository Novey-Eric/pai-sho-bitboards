
#include <algorithm>
#include "Bitboard.h"
#include "types.h"
#include <iostream>
#include <ostream>
#include <cstring>
#include<string>
#include <chrono>

using namespace std;
using namespace std::chrono;

std::string GetBinaryStringFromHexString (std::string sHex)
		{
			std::string sReturn = "";
			for (int i = 0; i < sHex.length (); ++i)
			{
				switch (sHex [i])
				{
					case '0': sReturn.append ("0000"); break;
					case '1': sReturn.append ("0001"); break;
					case '2': sReturn.append ("0010"); break;
					case '3': sReturn.append ("0011"); break;
					case '4': sReturn.append ("0100"); break;
					case '5': sReturn.append ("0101"); break;
					case '6': sReturn.append ("0110"); break;
					case '7': sReturn.append ("0111"); break;
					case '8': sReturn.append ("1000"); break;
					case '9': sReturn.append ("1001"); break;
					case 'a': sReturn.append ("1010"); break;
					case 'b': sReturn.append ("1011"); break;
					case 'c': sReturn.append ("1100"); break;
					case 'd': sReturn.append ("1101"); break;
					case 'e': sReturn.append ("1110"); break;
					case 'f': sReturn.append ("1111"); break;
				}
			}
			return sReturn;
		}

namespace Paisho{

    
    void print_move(const Move m){
        uint64_t move_type = (m & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET;
        //uint64_t move_capture = (m & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET;
        uint64_t move_s1 = (m & MOVE_S1_MASK) >> MOVE_S1_OFFSET;
        uint64_t move_s2 = (m & MOVE_S2_MASK) >> MOVE_S2_OFFSET;
        uint64_t move_piece = (m & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET;
        uint64_t move_auxpiece = (m & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET;
        uint64_t move_s3 = (m & MOVE_S3_MASK) >> MOVE_S3_OFFSET;
        uint64_t move_s4 = (m & MOVE_S4_MASK) >> MOVE_S4_OFFSET;
        uint64_t move_boatmove = (m & MOVE_BOATMOVE_MASK) >> MOVE_BOATMOVE_OFFSET;

        switch(move_type){
            case MOVE:
                std::cout << SquareStrings[move_s1] << "-" << SquareStrings[move_s2];
                break;
            case PLACE:
                std::cout << WhitePieceStrings[move_piece] << " " << SquareStrings[move_s1];
                break;
            case HARMPLACE:
                std::cout << SquareStrings[move_s1] << "-" << SquareStrings[move_s2];
                std::cout << "+" << WhitePieceStrings[move_piece] << " " << SquareStrings[move_s3];
                break;
            case HARMACCENT:
                if (move_boatmove){
                    std::cout << SquareStrings[move_s1] << "-" << SquareStrings[move_s2];
                    std::cout << "+" << AccentStrings[move_auxpiece] << " " << SquareStrings[move_s3] << "-" << SquareStrings[move_s4];
                } else{
                    std::cout << SquareStrings[move_s1] << "-" << SquareStrings[move_s2];
                    std::cout << "+" << AccentStrings[move_auxpiece] << " " << SquareStrings[move_s3];
                }
                break;
            default:
                std::cout << "move type not detected " << std::hex << move_type;
        }
        std::cout << std::endl;

    }
    
    void print_move_list(const Moves& mlist){
        int i = 0;
        for(auto move : mlist){
        //for (int i = 0; i < mlist.size(); i++){
            std::cout<<i++<<": ";
            print_move(move);
        }
    }


    void Bitboards::print_board(const Board& b){

        std::array<std::string, NUM_SQUARES> sq_strs;
        for (int i = 0; i < NUM_SQUARES; i++){

            if (Legal[i]){
                if (Red[i])
                    sq_strs[i] = " r ";
                else if (White[i])
                    sq_strs[i] = " w ";
                else
                    sq_strs[i] = " . ";

            }else{
                sq_strs[i] = "   ";
                }
            }

        //do w3 first
        for (int i = 0; i < 8; i++){
            for(int sq = 0; sq < NUM_SQUARES; sq++){
                if(b.whiteBoards[i][sq]){
                    sq_strs[sq] = WhitePieceStrings[i] + " ";
                }else if (b.blackBoards[i][sq]){
                    sq_strs[sq] = BlackPieceStrings[i] + " ";
                }
            }
        }

        for(int i = 0; i < NUM_SQUARES; i++){
           if(b.otherBoards[Accents][i]){
                sq_strs[i] = " A ";
            }
        }

        for (int row = 16; row >= 0; row--){
            std::cout << std::to_string(row+1) + "\t";
            for(int col = 0; col < 17; col++){
                std::cout<<sq_strs[row*17 + col];
                if(col == 16)
                    std::cout<<"\n";
            }
        }
        std::cout << "\t A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q\n";

    }



    void Bitboards::pretty(const Bitboard b){
        std::cout << "17 " << "        ";
        for (int i = 276; i <= 284; i++){
            std::cout << " " << b[i];
        }
        std::cout << "        " << std::endl;;

        std::cout << "16 " << "      ";
        for (int i = 258; i <= 268; i++){
            std::cout << " " << b[i];
        }
        std::cout << "      " << std::endl;;


        std::cout << "15 " << "    ";
        for (int i = 240; i <= 252; i++){
            std::cout << " " << b[i];
        }
        std::cout << "    " << std::endl;;


        std::cout << "14 " << "  ";
        for (int i = 222; i <= 236; i++){
            std::cout << " " << b[i];
        }
        std::cout << "  " << std::endl;;


        for (int j = 8; j >4; j--){
            std::cout << j+5 << " ";
            for (int i = 68 + j*17; i < 85 + j*17; i++){
                std::cout << " " << b[i];
            }
            std::cout << std::endl;
        }

        for (int j = 4; j >=0; j--){
            std::cout << j+5 << "  ";
            for (int i = 68 + j*17; i < 85 + j*17; i++){
                std::cout << " " << b[i];
            }
            std::cout << std::endl;
        }

        std::cout << "4  " << "  ";
        for (int i = 52; i <= 66; i++){
            std::cout << " " << b[i];
        }
        std::cout << "  " << std::endl;;

        std::cout << "3  " << "    ";
        for (int i = 36; i <= 48; i++){
            std::cout << " " << b[i];
        }
        std::cout << "    " << std::endl;;


        std::cout << "2  " << "      ";
        for (int i = 20; i <= 30; i++){
            std::cout << " " << b[i];
        }
        std::cout << "      " << std::endl;;


        std::cout << "1  " << "        ";
        for (int i = 4; i <= 12; i++){
            std::cout << " " << b[i];
        }
        std::cout << "        " << std::endl;
        std::cout << "    A B C D E F G H I J K L M N O P Q" << std::endl;

    }

    namespace Bitboards{

        //takes flower as input and returns bitboard of every space it can harmonize with.
        Bitboard get_harm_pieces(const Board& b, int team, int flower){
            Bitboard harm_board;
            const Bitboard *t_board;
            if (team == WHITE)
                t_board = &b.whiteBoards[0];
            else
                t_board = &b.blackBoards[0];
            
            switch(flower){
                case w3:
                    harm_board = t_board[w4] | t_board[r5] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                case w4:
                    harm_board = t_board[w3] | t_board[w5] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                case w5:
                    harm_board = t_board[w4] | t_board[r3] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                case r3:
                    harm_board = t_board[r4] | t_board[w5] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                case r4:
                    harm_board = t_board[r5] | t_board[r3] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                case r5:
                    harm_board = t_board[r4] | t_board[w5] | b.whiteBoards[lotus] | b.blackBoards[lotus];
                    break;
                //Lotus only harmonizes with own team.
                case orchid:
                    harm_board = Illegal & Legal;
                    break;
                case lotus:
                    harm_board = t_board[harmw3] | t_board[harmw4] | t_board[harmw5] | t_board[harmr3] | t_board[harmr4] | t_board[harmr5];
                    break;
              default:
                    std::cout << "bad piece in get harm board" << std::endl;
            }
            
            return harm_board;

        }


        Bitboard get_harm_board(const Board& b, int team, int flower){
            Bitboard harm_board;
            const Bitboard *t_board;
            if (team == WHITE)
                t_board = &b.whiteBoards[0];
            else
                t_board = &b.blackBoards[0];
            
            switch(flower){
                case w3:
                    harm_board = t_board[harmw4] | t_board[harmr5] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                case w4:
                    harm_board = t_board[harmw3] | t_board[harmw5] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                case w5:
                    harm_board = t_board[harmw4] | t_board[harmr3] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                case r3:
                    harm_board = t_board[harmr4] | t_board[harmw5] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                case r4:
                    harm_board = t_board[harmr5] | t_board[harmr3] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                case r5:
                    harm_board = t_board[harmr4] | t_board[harmw5] | b.whiteBoards[harmlotus] | b.blackBoards[harmlotus];
                    break;
                //Lotus only harmonizes with own team.
                case orchid:
                    harm_board = Illegal & Legal;
                    break;
                case lotus:
                    harm_board = t_board[harmw3] | t_board[harmw4] | t_board[harmw5] | t_board[harmr3] | t_board[harmr4] | t_board[harmr5];
                    break;
              default:
                    std::cout << "bad piece in get harm board" << std::endl;
            }
            
            return harm_board;
        }

        Bitboard get_cap_board(const Board& b, int team, int bbpiece){
            Bitboard cap_board;
            const Bitboard *t_board;
            const Bitboard *opps_board;
            bool wild;
            if (team == WHITE){
                t_board = &b.whiteBoards[0];
                opps_board = &b.blackBoards[0];
                wild = b.wwild;
            } else {
                t_board = &b.blackBoards[0];
                opps_board = &b.whiteBoards[0];
                wild = b.bwild;
            }
            
            switch(bbpiece){
                case w3:
                    cap_board = t_board[r3];
                    break;
                case w4:
                    cap_board = t_board[r4];
                    break;
                case w5:
                    cap_board = t_board[r5];
                    break;
                case r3:
                    cap_board = t_board[w3];
                    break;
                case r4:
                    cap_board = t_board[w4];
                    break;
                case r5:
                    cap_board = t_board[w4];
                    break;
                case orchid:
                    cap_board = wild ? opps_board[allflowers] : Illegal & Legal;
                    break;
                case lotus:
                    cap_board = Illegal & Legal;
                    break;
              default:
                    std::cout << "bad piece in get cap board" << std::endl;
            }
            return cap_board;
        }



        //Harm pieces is a bitboard of only the actual pieces that the square in question harmonizes with.
        //harm_board is harm_pieces with tendrils extending from the piece.
        Bitboard remove_duplicate_harm(Bitboard harm_pieces, Bitboard harm_board, int square){ //Takes board and square, it will remove harmonizing squares that it is currently connected to.
            int row = square/17;
            int col = square%17;
            Bitboard sq_board(1);
            sq_board <<= square;
            if ((sq_board & harm_board).any()){ //if it is already harmonizing with a piece, do the calculation. Else just return harm_board
                int t_harm_p = get_lsb(harm_pieces);
                while(t_harm_p != -1){
                    int t_row = t_harm_p / 17;
                    int t_col = t_harm_p % 17;
                    if (t_row == row || t_col == col){ //if piece is already lined up with the harmonizing piece. Remove that from the board
                        harm_board &= ~col_map[t_col] & ~row_map[t_row];
                    }
                harm_pieces.reset(t_harm_p);
                t_harm_p = get_lsb(harm_pieces);
                }
            } 
            return harm_board;
        }


        Bitboard get_clash_board(const Board& b, int piece){
            switch(piece){
                case w3: return b.whiteBoards[harmr3] | b.blackBoards[harmr3];
                case w4: return b.whiteBoards[harmr4] | b.blackBoards[harmr4];
                case w5: return b.whiteBoards[harmr5] | b.blackBoards[harmr5];
                case r3: return b.whiteBoards[harmw3] | b.blackBoards[harmw3];
                case r4: return b.whiteBoards[harmw4] | b.blackBoards[harmw4];
                case r5: return b.whiteBoards[harmw5] | b.blackBoards[harmw5];
                default: return Bitboard(0);
            }
        }

        void get_flower_moves(const Board& b, int team, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            if(team == WHITE){
                team_board = &b.whiteBoards[0];
            }else{
                team_board = &b.blackBoards[0];
            }

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard cap_board = get_cap_board(b, team, bbflowerpiece);
            Bitboard clash_board = get_clash_board(b, bbflowerpiece);
            Bitboard w3_copy = team_board[bbflowerpiece];

            //Go through each piece and generate moves for it
            Bitboard t_dests;
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if (w3_copy[t_src]){
                    t_dests = mask_move_ptr(t_src) & \
                              (~b.otherBoards[AllPieces] ^ cap_board) & 
                              (~clash_board) & correct_color(bbflowerpiece);
                    
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                        //while (t_dest != -1){
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            Move t_move = (MOVE << MOVE_TYPE_OFFSET) |\
                                            (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                            (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                            (t_src << MOVE_S1_OFFSET) |\
                                            (t_dest << MOVE_S2_OFFSET);
                            move_list.push_back(t_move);
                        }
                    }
                }
            }
        }



        //This function does NOT include boat moves that move a flower piece from tile to tile.
        void get_harmony_accent_moves(const Board& b, int team, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            if(team == WHITE){
                team_board = &b.whiteBoards[0];
            }else{
                team_board = &b.blackBoards[0];
            }

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, team, bbflowerpiece); //harm1 & harm2
            
            Bitboard cap_board = get_cap_board(b, team, bbflowerpiece);

            //Note have to add lotus to harm board cases
            int pieces_in_hand[8];
            int num_pieces = 0;
            const Bitboard *teamboard;
            
            if (team == WHITE){
                teamboard = &b.whiteBoards[0];
                if (b.whiteAccents & (1<<Rock | 1<<Rock2))
                    pieces_in_hand[num_pieces++] = Rock;
                if (b.whiteAccents & (1<<Knotweed | 1<<Knotweed2))
                    pieces_in_hand[num_pieces++] = Knotweed;
                if (b.whiteAccents & (1<<Wheel | 1<<Wheel2))
                    pieces_in_hand[num_pieces++] = Wheel;
                if (b.whiteAccents & (1<<Boat | 1<<Boat2))
                    pieces_in_hand[num_pieces++] = Boat;
            } else{
                teamboard = &b.blackBoards[0];
                if (b.blackAccents & (1<<Rock | 1<<Rock2))
                    pieces_in_hand[num_pieces++] = Rock;
                if (b.blackAccents & (1<<Knotweed | 1<<Knotweed2))
                    pieces_in_hand[num_pieces++] = Knotweed;
                if (b.blackAccents & (1<<Wheel | 1<<Wheel2))
                    pieces_in_hand[num_pieces++] = Wheel;
                if (b.blackAccents & (1<<Boat | 1<<Boat2))
                    pieces_in_hand[num_pieces++] = Boat;
            }

            Bitboard w3_copy = team_board[bbflowerpiece];
            //Go through each piece and generate moves for it
            Bitboard t_dests;
            Bitboard harm_pieces = get_harm_pieces(b, team, bbflowerpiece);
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if(w3_copy[t_src]){
            //while (t_src != -1){ //square piece is being moved from
                    Bitboard updated_harm = remove_duplicate_harm(harm_pieces, harm_board, t_src);

                    t_dests = mask_move_ptr(t_src) & \
                              ~b.otherBoards[Accents] & \
                              updated_harm & \
                              correct_color(bbflowerpiece) & \
                              (~teamboard[allflowers] | cap_board);

                    //int t_dest = get_lsb(t_dests);
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                        //while (t_dest != -1){//square piece is being moved to
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            
                            for(int i = 0; i < num_pieces; i++){//For each aux piece in the player's hand
                                int auxpiece = pieces_in_hand[i];
                                if (auxpiece == Rock || auxpiece == Knotweed){
                                    Bitboard post_move_bb = b.otherBoards[AllPieces];
                                    post_move_bb.reset(t_src);
                                    post_move_bb.set(t_dest);
                                    Bitboard rock_squares = ((post_move_bb >> EAST) |\
                                                            (post_move_bb << EAST) |\
                                                            (post_move_bb << NORTH) |\
                                                            (post_move_bb >> NORTH) |\
                                                            (post_move_bb >> (NORTH + EAST)) |\
                                                            (post_move_bb >> (NORTH - EAST)) |\
                                                            (post_move_bb << (NORTH + EAST)) |\
                                                            (post_move_bb << (NORTH - EAST))) &\
                                                            Legal & ~post_move_bb & ~Gates;
                                    //int auxpiece_square = get_lsb(rock_squares);
                                    for(int auxpiece_square = 0; auxpiece_square<NUM_SQUARES; auxpiece_square++){
                                        if(rock_squares[auxpiece_square]){
                                            Move t_move = (HARMACCENT << MOVE_TYPE_OFFSET) |\
                                                            (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                                            (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                                            (t_src << MOVE_S1_OFFSET) |\
                                                            (t_dest << MOVE_S2_OFFSET) |\
                                                            (auxpiece << MOVE_AUXPIECE_OFFSET) |\
                                                            ((uint64_t) auxpiece_square << MOVE_S3_OFFSET);
                                            move_list.push_back(t_move);
                                            //move_list[move_list.move_count++] = t_move;
                                        }
                                    }
                                }else if (auxpiece == Wheel){
                                    Bitboard post_move_bb = b.otherBoards[AllPieces];
                                    post_move_bb.reset(t_src);
                                    post_move_bb.set(t_dest);
                                    Bitboard wheel_squares = ((post_move_bb >> EAST) |\
                                                            (post_move_bb << EAST) |\
                                                            (post_move_bb << NORTH) |\
                                                            (post_move_bb >> NORTH) |\
                                                            (post_move_bb >> (NORTH + EAST)) |\
                                                            (post_move_bb >> (NORTH - EAST)) |\
                                                            (post_move_bb << (NORTH + EAST)) |\
                                                            (post_move_bb << (NORTH - EAST))) &\
                                                            Legal & ~post_move_bb & ~Gates;
                                    //int auxpiece_square = get_lsb(wheel_squares);
                                    //while(auxpiece_square != -1){
                                    for(int auxpiece_square=0; auxpiece_square < NUM_SQUARES; auxpiece_square++){
                                        if(wheel_squares[auxpiece_square]){
                                            Bitboard legal_bb(1);
                                            legal_bb <<= auxpiece_square; //This is a bitboard of all the squares around the wheel square. Check to make sure there are exactly 9 bits
                                            legal_bb = (((legal_bb & ~FileABB) >> EAST) |\
                                                        ((legal_bb & ~FileQBB) << EAST) |\
                                                        (legal_bb << NORTH) |\
                                                        (legal_bb >> NORTH) |\
                                                        ((legal_bb & ~FileABB) >> (NORTH + EAST)) |\
                                                        ((legal_bb & ~FileQBB) >> (NORTH - EAST)) |\
                                                        ((legal_bb & ~FileQBB) << (NORTH + EAST)) |\
                                                        ((legal_bb & ~FileABB) << (NORTH - EAST))) &\
                                                        Legal & ~Gates;
                                            if (legal_bb.count() == 8){
                                                Move t_move = (HARMACCENT << MOVE_TYPE_OFFSET) |\
                                                                (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                                                (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                                                (t_src << MOVE_S1_OFFSET) |\
                                                                (t_dest << MOVE_S2_OFFSET) |\
                                                                (auxpiece << MOVE_AUXPIECE_OFFSET) |\
                                                                ((uint64_t) auxpiece_square << MOVE_S3_OFFSET);
                                                //std::cout << move_list.move_count << " ";
                                                //print_move(t_move);
                                                move_list.push_back(t_move);
                                            }
                                        }
                                    }

                                }else if (auxpiece == Boat){
                                    Bitboard all_accents = b.otherBoards[Accents];
                                    //int t_accent = get_lsb(all_accents);
                                    //while (t_accent != -1){
                                    for(int t_accent = 0; t_accent < NUM_SQUARES; t_accent++){
                                        if(all_accents[t_accent]){
                                            Move t_move = (HARMACCENT << MOVE_TYPE_OFFSET) |\
                                                            (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                                            (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                                            (t_src << MOVE_S1_OFFSET) |\
                                                            (t_dest << MOVE_S2_OFFSET) |\
                                                            (auxpiece << MOVE_AUXPIECE_OFFSET) |\
                                                            ((uint64_t) t_accent << MOVE_S3_OFFSET);
                                                move_list.push_back(t_move);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        void get_harmony_place_moves(const Board& b, int team, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            if(team == WHITE){
                team_board = &b.whiteBoards[0];
            }else{
                team_board = &b.blackBoards[0];
            }

            if ((team_board[allflowers] & team_board[orchid] & team_board[lotus] & Gates).any()){
                //Trying to harmony place with a growing tile in gate
                return;
            }

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, team, bbflowerpiece); //harm1 & harm2
            Bitboard cap_board = get_cap_board(b, team, bbflowerpiece);

            //pretty(harm_board);
            //Note have to add lotus to harm board cases
            int pieces_in_hand[8];
            int num_pieces = 0;
            const Bitboard *teamboard;
            
            if (team == WHITE){
                teamboard = &b.whiteBoards[0];
                if (b.ww3)
                    pieces_in_hand[num_pieces++] = w3;
                if (b.ww4)
                    pieces_in_hand[num_pieces++] = w4;
                if (b.ww5)
                    pieces_in_hand[num_pieces++] = w5;
                if (b.wr3)
                    pieces_in_hand[num_pieces++] = r3;
                if (b.wr4)
                    pieces_in_hand[num_pieces++] = r4;
                if (b.wr5)
                    pieces_in_hand[num_pieces++] = r5;
                if (b.wo)
                    pieces_in_hand[num_pieces++] = orchid;
                if (b.wl)
                    pieces_in_hand[num_pieces++] = lotus;
                
            } else{
                teamboard = &b.blackBoards[0];
                if (b.bw3)
                    pieces_in_hand[num_pieces++] = w3;
                if (b.bw4)
                    pieces_in_hand[num_pieces++] = w4;
                if (b.bw5)
                    pieces_in_hand[num_pieces++] = w5;
                if (b.br3)
                    pieces_in_hand[num_pieces++] = r3;
                if (b.br4)
                    pieces_in_hand[num_pieces++] = r4;
                if (b.br5)
                    pieces_in_hand[num_pieces++] = r5;
                if (b.bo)
                    pieces_in_hand[num_pieces++] = orchid;
                if (b.bl)
                    pieces_in_hand[num_pieces++] = lotus;
            }

            Bitboard w3_copy = team_board[bbflowerpiece];
            //Go through each piece and generate moves for it
            Bitboard t_dests;
            Bitboard t_open_gates;
            Bitboard harm_pieces = get_harm_pieces(b, team, bbflowerpiece);
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if (w3_copy[t_src]){
                //while (t_src != -1){ //First look at quiet moves only
                    Bitboard updated_harm = remove_duplicate_harm(harm_pieces, harm_board, t_src);
                    t_dests = mask_move_ptr(t_src) & \
                              updated_harm & \
                              correct_color(bbflowerpiece) & \
                              ~b.otherBoards[Accents] & \
                              (~teamboard[allflowers] | cap_board);

                    //int t_dest = get_lsb(t_dests);
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            t_open_gates = Gates & ~b.otherBoards[AllPieces];

                            
                            //int t_open_gate = get_lsb(t_open_gates);
                            for(int t_open_gate = 0; t_open_gate < NUM_SQUARES; t_open_gate++){
                                if(t_open_gates[t_open_gate]){
                                    for (int i = 0; i < num_pieces; i++){
                                        int piece_bits = pieces_in_hand[i];
                                        Move t_move = (HARMPLACE << MOVE_TYPE_OFFSET) |\
                                                        (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                                        (t_src << MOVE_S1_OFFSET) |\
                                                        (t_dest << MOVE_S2_OFFSET) |\
                                                        (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                                        (piece_bits << MOVE_AUXPIECE_OFFSET) |\
                                                        ((uint64_t) t_open_gate << MOVE_S3_OFFSET);
                                        move_list.push_back(t_move);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        void get_place_moves(const Board& b, int team, Moves& move_list){
            //Note have to add lotus to harm board cases
            int pieces_in_hand[8];
            int num_pieces = 0;
            
            if (team == WHITE){
                if (b.ww3)
                    pieces_in_hand[num_pieces++] = w3;
                if (b.ww4)
                    pieces_in_hand[num_pieces++] = w4;
                if (b.ww5)
                    pieces_in_hand[num_pieces++] = w5;
                if (b.wr3)
                    pieces_in_hand[num_pieces++] = r3;
                if (b.wr4)
                    pieces_in_hand[num_pieces++] = r4;
                if (b.wr5)
                    pieces_in_hand[num_pieces++] = r5;
                
            } else{
                if (b.bw3)
                    pieces_in_hand[num_pieces++] = w3;
                if (b.bw4)
                    pieces_in_hand[num_pieces++] = w4;
                if (b.bw5)
                    pieces_in_hand[num_pieces++] = w5;
                if (b.br3)
                    pieces_in_hand[num_pieces++] = r3;
                if (b.br4)
                    pieces_in_hand[num_pieces++] = r4;
                if (b.br5)
                    pieces_in_hand[num_pieces++] = r5;
            }

            Bitboard t_open_gates = Gates & ~b.otherBoards[AllPieces];
            int t_open_gate = get_lsb(t_open_gates);
            while (t_open_gate != -1){
                for (int i = 0; i < num_pieces; i++){
                    int piece_bits = pieces_in_hand[i];
                    Move t_move = (PLACE << MOVE_TYPE_OFFSET) |\
                                    (t_open_gate << MOVE_S1_OFFSET) |\
                                    (piece_bits << MOVE_PIECE_OFFSET);
                    move_list.push_back(t_move);
                }
                t_open_gates.reset(t_open_gate);
                t_open_gate = get_lsb(t_open_gates);
            }
        }
        

        void get_boat_flower_moves(const Board& b, int team, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            if(team == WHITE){
                if(!(b.whiteAccents & (1<<Boat | 1<<Boat2))){
                    return;
                }
                team_board = &b.whiteBoards[0];
            }else{
                if(!(b.blackAccents & (1<<Boat | 1<<Boat2))){
                    return;
                }
                team_board = &b.blackBoards[0];
            }

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, team, bbflowerpiece); //harm1 & harm2
            Bitboard cap_board = get_cap_board(b, team, bbflowerpiece);

            //Note have to add lotus to harm board cases
            
            Bitboard w3_copy = team_board[bbflowerpiece];
            //Go through each piece and generate moves for it
            int t_src = get_lsb(w3_copy);
            Bitboard t_dests;
            while (t_src != -1){ //square piece is being moved from
                t_dests = mask_move_ptr(t_src) & \
                          harm_board & \
                          correct_color(bbflowerpiece) & \
                          ~b.otherBoards[Accents] & \
                          (~team_board[allflowers] | cap_board);

                int t_dest = get_lsb(t_dests);
                while (t_dest != -1){//square piece is being moved to
                    int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                    Bitboard post_move_bb = b.whiteBoards[allflowers] & b.blackBoards[allflowers];
                    post_move_bb.reset(t_src);
                    post_move_bb.set(t_dest);
                    int boat_square = get_lsb(post_move_bb);
                    while (boat_square != -1){
                        Bitboard s4_squares = (((post_move_bb & ~FileABB) >> EAST) |\
                                                ((post_move_bb & ~FileQBB) << EAST) |\
                                                (post_move_bb << NORTH) |\
                                                (post_move_bb >> NORTH) |\
                                                ((post_move_bb & ~FileABB) >> (NORTH + EAST)) |\
                                                ((post_move_bb & ~FileQBB) >> (NORTH - EAST)) |\
                                                ((post_move_bb & ~FileQBB) << (NORTH + EAST)) |\
                                                ((post_move_bb & ~FileABB) << (NORTH - EAST))) &\
                                                Legal & ~post_move_bb & ~Gates;
                        int s4_square = get_lsb(s4_squares);
                        while(s4_square != -1){
                            Move t_move = (HARMACCENT << MOVE_TYPE_OFFSET) |\
                                            (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                            (t_src << MOVE_S1_OFFSET) |\
                                            (t_dest << MOVE_S2_OFFSET) |\
                                            (Boat << MOVE_AUXPIECE_OFFSET) |\
                                            (bbflowerpiece << MOVE_PIECE_OFFSET) |\
                                            ((uint64_t) boat_square << MOVE_S3_OFFSET) |\
                                            ((uint64_t) s4_square << MOVE_S4_OFFSET) |\
                                            ((uint64_t) 1 << MOVE_BOATMOVE_OFFSET);
                            move_list.push_back(t_move);
                            
                            s4_squares.reset(s4_square);
                            s4_square = get_lsb(s4_squares);
                        }
                        post_move_bb.reset(boat_square);
                        boat_square = get_lsb(post_move_bb);
                    }
                    t_dests.reset(t_dest);
                    t_dest = get_lsb(t_dests);
                }
                w3_copy.reset(t_src);
                t_src = get_lsb(w3_copy);
            }
        }




        //get_flower_moves(Board b, int team, int bbflowerpiece, Moves *move_list){
        Moves get_moves(const Board& b, int team){
            Moves move_list;
            int piece_list[] = {w3,w4,w5,r3,r4,r5,lotus,orchid};

            for (int i = 0; i < 8; i++){
                get_flower_moves(b, team, piece_list[i], move_list);
                get_harmony_place_moves(b, team, piece_list[i], move_list);
                get_harmony_accent_moves(b, team, piece_list[i], move_list);
                get_boat_flower_moves(b, team, piece_list[i], move_list);
                //get harmony boat moves
            }
            get_place_moves(b, team, move_list);
            return move_list;
        }


        int get_lsb(const Bitboard b){
            for (int i = 0; i < NUM_SQUARES-3; i++){//-3 since some are out of bounds we dont care about
                if (b[i])
                    return i;
            }
            return -1; //There is no 1
        }

        void make_place_move(Board& b, int team, int piece, int square){
            Bitboard *team_board;
            if(team == WHITE){
                team_board = &b.whiteBoards[0];
                switch(piece){
                    case w3:
                        b.ww3--;
                        break;
                    case w4:
                        b.ww4--;
                        break;
                    case w5:
                        b.ww5--;
                        break;
                    case r3:
                        b.wr3--;
                        break;
                    case r4:
                        b.wr4--;
                        break;
                    case r5:
                        b.wr5--;
                        break;
                    case lotus:
                        b.wl = false;
                        break;
                    case orchid:
                        b.wo = false;
                        break;
                }
            }else{
                team_board = &b.blackBoards[0];
                switch(piece){
                    case w3:
                        b.bw3--;
                        break;
                    case w4:
                        b.bw4--;
                        break;
                    case w5:
                        b.bw5--;
                        break;
                    case r3:
                        b.br3--;
                        break;
                    case r4:
                        b.br4--;
                        break;
                    case r5:
                        b.br5--;
                        break;
                    case lotus:
                        b.bl = false;
                        break;
                    case orchid:
                        b.bo = false;
                        break;
                }
            }
            
            //Set all pieces board, set team board
            b.otherBoards[AllPieces].set(square);
            team_board[allflowers].set(square);
            team_board[piece].set(square);
            
        }

        void make_move_move(Board& b, int team, int piece, int src, int dst, bool cap){
            Bitboard *team_board;
            Bitboard *opps_board;

            if(team == WHITE){
                team_board = &b.whiteBoards[0];
                opps_board = &b.blackBoards[0];
                if (piece == lotus)
                    b.wwild = true;
            }else{
                team_board = &b.blackBoards[0];
                opps_board = &b.whiteBoards[0];
                if (piece == lotus)
                    b.bwild = true;
            }
            
            if (cap){
                //Find which tile is being captured, and remove from opponents boards
                //Maybe reset all boards?
                for (int i = 0; i < NUM_BOARDS; i++)
                    opps_board[i].reset(dst);
            } else{
                b.otherBoards[AllPieces].set(dst); //if capturing piece, allpieces already set. only set if not capping.
            }
            
            b.otherBoards[AllPieces].reset(src);
            team_board[piece].reset(src);
            team_board[allflowers].reset(src);
            team_board[piece].set(dst);
            team_board[allflowers].set(dst);

        }

        void make_harm_place_move(Board& b, int team, int piece, int src, int dst, int auxflower, int placesq, bool cap){
            make_move_move(b, team, piece, src, dst, cap);
            make_place_move(b, team, auxflower, placesq);
        }

        
        void make_harm_accent_move(Board& b, int team, int piece, int src, int dst, int auxpiece, int auxsq, bool cap){
            make_move_move(b, team, piece, src, dst, cap);
            if (team == WHITE){
                if (auxpiece & b.whiteAccents)
                    b.whiteAccents ^= 1<<auxpiece;
                else
                    b.whiteAccents ^= 1<<(auxpiece+1);
                
            }else{
                if (auxpiece & b.blackAccents)
                    b.blackAccents ^= 1<<auxpiece;
                else
                    b.blackAccents ^= 1<<(auxpiece+1);
            }

            b.otherBoards[Accents].set(auxsq);
            b.otherBoards[AllPieces].set(auxsq);

            if (auxpiece == Rock){
                b.otherBoards[Rocks].set(auxsq);
            } else if (auxpiece == Wheel){
                Board copy = b;
                //int hmoves[8] = {EAST, EAST+NORTH, NORTH, NORTH+WEST, WEST, SOUTH+WEST, SOUTH, SOUTH+EAST};
                int hmoves[8] = {SOUTH+EAST, SOUTH, SOUTH+WEST, WEST, NORTH+WEST, NORTH, EAST+NORTH, EAST};
                for(int t_board = 0; t_board < (2*NUM_BOARDS)+NUM_OTHER_BOARDS; t_board++){ //TODO: this can be optimized since half the boards are harmonies.
                    b.whiteBoards[t_board][auxsq + hmoves[0]] = copy.whiteBoards[t_board][auxsq + hmoves[7]];
                    for (int t_move=1; t_move<8; t_move++){
                        b.whiteBoards[t_board][auxsq + hmoves[t_move]] = copy.whiteBoards[t_board][auxsq + hmoves[t_move-1]];
                        //this is SUPER cursed, going through all arrays in 
                        //whiteboards and blackboards by doubling the length of the first
                    }
                }
                
            } else if (auxpiece == Boat){
                b.otherBoards[Rocks].reset(auxsq);
                b.otherBoards[Knotweeds].reset(auxsq);
            }if (auxpiece == Knotweed){
                b.otherBoards[Knotweeds].set(auxsq);
            }

        }

        void make_harm_accent_boatmove(Board& b, int team, int piece, int src, int dst, int boatsq, int boat_move_sq, bool cap){
            make_move_move(b, team, piece, src, dst, cap);
            if (team == WHITE){
                if (Boat & b.whiteAccents)
                    b.whiteAccents ^= 1<<Boat;
                else
                    b.whiteAccents ^= 1<<(Boat+1);
                
            }else{
                if (Boat & b.blackAccents)
                    b.blackAccents ^= 1<<Boat;
                else
                    b.blackAccents ^= 1<<(Boat+1);
            }

            b.otherBoards[Accents].set(boatsq);
            b.otherBoards[AllPieces].set(boat_move_sq);
            //Need all pieces move too
            for(int t_board = 0; t_board < (2*NUM_BOARDS); t_board++){
                if (b.whiteBoards[t_board][boatsq]){
                    b.whiteBoards[t_board].set(boat_move_sq);
                    b.whiteBoards[t_board].reset(boatsq);
                }
                //this is SUPER cursed, going through all arrays in 
                //whiteboards and blackboards by doubling the length of the first
            }
        }

        void make_move(Board& b, int team, Move m){
            uint64_t type = (m & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET;
            uint64_t cap = (m & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET;
            uint64_t s1 = (m & MOVE_S1_MASK) >> MOVE_S1_OFFSET;
            uint64_t s2 = (m & MOVE_S2_MASK) >> MOVE_S2_OFFSET;
            uint64_t piece = (m & MOVE_PIECE_MASK) >> MOVE_PIECE_OFFSET;
            uint64_t auxpiece = (m & MOVE_AUXPIECE_MASK) >> MOVE_AUXPIECE_OFFSET;
            uint64_t s3 = (m & MOVE_S3_MASK) >> MOVE_S3_OFFSET;
            uint64_t s4 = (m & MOVE_S4_MASK) >> MOVE_S4_OFFSET;
            uint64_t boatmove = (m & MOVE_BOATMOVE_MASK) >> MOVE_BOATMOVE_OFFSET;
            
            

            if (type == MOVE){
                //std::cout<<"in move"<< std::endl;
                make_move_move(b, team, piece, s1, s2, cap);
            }else if(type == PLACE){
                //std::cout<<"place"<< std::endl;
                make_place_move(b, team, piece, s1);
            }else if(type == HARMPLACE){
                //std::cout<<"harmplace"<< std::endl;
                make_harm_place_move(b, team, piece, s1, s2, piece, s3, cap);
            }else if(type == HARMACCENT && !boatmove){
                //std::cout<<"harmacc"<< std::endl;
                make_harm_accent_move(b, team, piece, s1, s2, auxpiece, s3, cap);
            }else if(type == HARMACCENT && boatmove){
                //std::cout<<"harmacc boatmove"<< std::endl;
                make_harm_accent_boatmove(b, team, piece, s1, s2, s3, s4, cap);
            }
            update_harms_clash(b);
        }

        //returns a bitboard with vertical and horizontal lines extending from square.
        //not inclusive of square
        Bitboard get_tendrils(int square){
            int row = square/17;
            int col = square%17;
            Bitboard ret = col_map[col] ^ row_map[row];
            return ret;
        }


        void find_harms(Board& b, int team){
            //HARM CASE
            //int t_piece = w3;
            Bitboard *teamboard;
            std::deque<std::pair<int, int>> *team_harms;
            if (team == WHITE){
                teamboard = &(b.whiteBoards)[0];
                team_harms = &b.white_harm_pairs;
            }else{
                teamboard = &(b.blackBoards)[0];
                team_harms = &b.black_harm_pairs;
            }
            team_harms->clear();
            //teamboard[harm_map(t_piece)] = Bitboard(0);

            teamboard[harmw3] = Bitboard(0);
            teamboard[harmw4] = Bitboard(0);
            teamboard[harmw5] = Bitboard(0);
            teamboard[harmr3] = Bitboard(0);
            teamboard[harmr4] = Bitboard(0);
            teamboard[harmr5] = Bitboard(0);
            int piece_ind[18];
            int piece_count = 0;
            Bitboard flowers_copy = teamboard[allflowers] & ~Gates & ~teamboard[orchid];
            //pretty(flowers_copy);
            //int t_teampiece = get_lsb(flowers_copy);
            for(int t_teampiece = 0; t_teampiece < NUM_SQUARES; t_teampiece++){
                if (flowers_copy[t_teampiece]){
                    piece_ind[piece_count++]=t_teampiece;
                    //std::cout << "piece count " << piece_count << std::endl;
                }
            }

            //go through all pieces once. Find all white or black pieces. Then just check those squares instead of getlsb every time


            int tmp_square;
            int current_row;
            //int w3_piece = get_lsb(w3_pieces);
            int w3_piece;
            for(int i = 0; i < piece_count; i++){
            //while(w3_piece != -1){ //for each r3 piece on the board:
                w3_piece = piece_ind[i];
                Bitboard w3_pieces;
                int t_piece = 0;
                for(t_piece = 0; t_piece <= 6; t_piece++){
                    if (teamboard[t_piece][w3_piece]){
                        w3_pieces = teamboard[t_piece];
                        break;
                    }
                }
                    
                //Bitboard get_harm_pieces(Board *b, int team, int flower){
                //Bitboard reverse_harm_lookup(Board *b, int harm_index, int team){
                //returns bitboard of pieces that can harmonize with t_piece
                Bitboard harm_board = reverse_harm_lookup(b, harm_map(t_piece), team) & ~Gates;
                int harm_ind = harm_map(t_piece);
                //std::cout<<"tpiece " << t_piece << " " << "harm ind " << harm_ind<<std::endl;
                tmp_square = w3_piece + EAST;
                current_row = w3_piece / 17;

                while(tmp_square/17 == current_row && tmp_square < NUM_SQUARES-1 && b.otherBoards[AllPieces][tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square += EAST;
                }
                if (tmp_square/17 == current_row && tmp_square < NUM_SQUARES-1){
                    teamboard[harm_ind].set(tmp_square);

                    //if the final square you check is actually a piece you can harmonize with. Add it to the pairs.
                    if(harm_board[tmp_square])
                        (*team_harms).push_back(std::pair{w3_piece, tmp_square});
                    //if [tmp_square], then add {w3_piece, tmp_square} to harmpairs
                }

                tmp_square = w3_piece - EAST;
                while(tmp_square/17 == current_row && tmp_square >= 0 && b.otherBoards[AllPieces][tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square -= EAST;
                }
                if (tmp_square/17 == current_row && tmp_square >= 0){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square])
                        (*team_harms).push_back(std::pair{w3_piece, tmp_square});
                }

                tmp_square = w3_piece + NORTH;
                while(tmp_square < NUM_SQUARES && b.otherBoards[AllPieces][tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square += NORTH;
                }
                if (tmp_square < NUM_SQUARES){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square])
                        (*team_harms).push_back(std::pair{w3_piece, tmp_square});
                }


                tmp_square = w3_piece - NORTH;
                while(tmp_square >= 0 && b.otherBoards[AllPieces][tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square -= NORTH;
                }
                if (tmp_square >= 0){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square])
                        (*team_harms).push_back(std::pair{w3_piece, tmp_square});
                }
                //std::cout<<"w3 pieces after loop" <<std::endl;
                //pretty(teamboard[allflowers]);
                
                //go up and down, left and right from the piece.
                //until hitting another piece. All those squares should be set to 1
                //for clashes, it should be un-inclusive of the flowers
                
                //For harmonies, it should be inclusive of the tile on the board.
            }
        }



        void update_harms_clash(Board& b){
            find_harms(b, WHITE);
            find_harms(b, BLACK);
        }


        //take harmboard index as input, return bitbord of which pieces can harmonize with that piece
        Bitboard reverse_harm_lookup(const Board& b, int harm_index, int team){
            Bitboard ret;
            const Bitboard *teamboard;
            if (team == WHITE){
                teamboard = &b.whiteBoards[0];
            }else{
                teamboard = &b.blackBoards[0];
            }
            switch(harm_index){
                case harmr3:
                    ret = teamboard[r4] | teamboard[w5];
                    break;
                case harmr4:
                    ret = teamboard[r5] | teamboard[r3];
                    break;
                case harmr5:
                    ret = teamboard[w3] | teamboard[r4];
                    break;
                case harmw3:
                    ret = teamboard[w4] | teamboard[r5];
                    break;
                case harmw4:
                    ret = teamboard[w5] | teamboard[w3];
                    break;
                case harmw5:
                    ret = teamboard[w5] | teamboard[r3];
                    break;
                case harmlotus:
                    ret = teamboard[w5] | teamboard[r3];
                    break;
            }
            return ret;
        }

        int check_win(const Board& b){
            return -1;
        }


        Bitboard mask_2_move(int square){
            Bitboard bb(0);
            Bitboard moves(0);
            bb.set(square);
            //East, East2, West, West2, S, S2, NE, NW, SE, SW
            //Never be able to move into a gate, or wrong color, or same square
            //Check for wrapping
            Bitboard s2 = (bb >> 2*NORTH);
            Bitboard s = (bb >> NORTH);
            Bitboard n2 = (bb << 2*NORTH);
            Bitboard n = (bb << NORTH);
            Bitboard w2 = (bb & ~FileABB & ~FileBBB) >> 2*EAST;
            Bitboard w = (bb & ~FileABB) >> EAST;
            Bitboard e2 = (bb & ~FileQBB & ~FilePBB) << 2*EAST;
            Bitboard e = (bb & ~FileQBB) << EAST;
            Bitboard ne = ((bb & ~FileQBB) << EAST) << NORTH;
            Bitboard se = ((bb & ~FileQBB) << EAST) >> NORTH;
            Bitboard nw = ((bb & ~FileABB) >> EAST) << NORTH;
            Bitboard sw = ((bb & ~FileABB) >> EAST) >> NORTH;
            
            moves = (s2 | s | n2 | n | w | w2 | e | e2 | ne | se | nw | sw) & ~Gates;
            return moves;
        } 

        Bitboard mask_3_move(int square){
            Bitboard bb(0);
            Bitboard moves(0);
            bb.set(square);
            Bitboard m2_moves = mask_2_move(square);
            //East, East2, West, West2, S, S2, NE, NW, SE, SW
            //Never be able to move into a gate, or wrong color, or same square
            //Check for wrapping
            Bitboard s3 = (bb >> 3*NORTH);
            Bitboard n3 = (bb << 3*NORTH);
            Bitboard w3 = (bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST;
            Bitboard e3 = (bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST;

            Bitboard nne = ((bb & ~FileQBB) << EAST) << 2*NORTH;
            Bitboard nnw = ((bb & ~FileABB) >> EAST) << 2*NORTH;
            Bitboard sse = ((bb & ~FileQBB) << EAST) >> 2*NORTH;
            Bitboard ssw = ((bb & ~FileABB) >> EAST) >> 2*NORTH;

            Bitboard nww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) << NORTH;
            Bitboard nee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) << NORTH;
            Bitboard see = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) >> NORTH;
            Bitboard sww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) >> NORTH;
            
            moves = (m2_moves|\
                    n3|s3|e3|w3|\
                    nne|nnw|sse|ssw|\
                    nww|nee|see|sww\
                    ) & ~Gates & Legal;
            return moves;
        } 


        Bitboard mask_4_move(int square){
            Bitboard bb(0);
            Bitboard moves(0);
            bb.set(square);

            Bitboard m3_mask = mask_3_move(square);
            //East, East2, West, West2, S, S2, NE, NW, SE, SW
            //Never be able to move into a gate, or wrong color, or same square
            //Check for wrapping
            Bitboard s4 = (bb >> 4*NORTH);
            Bitboard n4 = (bb << 4*NORTH);
            Bitboard w4 = (bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB) >> 4*EAST;
            Bitboard e4 = (bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB) << 4*EAST;

            Bitboard nnne = ((bb & ~FileQBB) << EAST) << 3*NORTH;
            Bitboard nnnw = ((bb & ~FileABB) >> EAST) << 3*NORTH;
            Bitboard ssse = ((bb & ~FileQBB) << EAST) >> 3*NORTH;
            Bitboard sssw = ((bb & ~FileABB) >> EAST) >> 3*NORTH;

            Bitboard nwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) << NORTH;
            Bitboard neee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) << NORTH;
            Bitboard seee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) >> NORTH;
            Bitboard swww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) >> NORTH;

            Bitboard nnww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) << 2*NORTH;
            Bitboard nnee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) << 2*NORTH;
            Bitboard ssee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) >> 2*NORTH;
            Bitboard ssww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) >> 2*NORTH;

            
            moves = (m3_mask|\
                    n4|w4|e4|s4|\
                    nnne|nnnw|ssse|sssw|\
                    nwww|neee|swww|seee|\
                    nnww|nnee|ssee|ssww) & ~Gates & Legal;
            return moves;
        } 



        Bitboard mask_5_move(int square){
            Bitboard bb(0);
            Bitboard moves(0);
            bb.set(square);
            Bitboard m4_mask = mask_4_move(square);
            //East, East2, West, West2, S, S2, NE, NW, SE, SW
            //Never be able to move into a gate, or wrong color, or same square
            //Check for wrapping
            Bitboard s5 = (bb >> 5*NORTH);
            Bitboard n5 = (bb << 5*NORTH);
            Bitboard w5 = (bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB & ~FileEBB) >> 5*EAST;
            Bitboard e5 = (bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB & ~FileMBB) << 5*EAST;

            Bitboard nnnne = ((bb & ~FileQBB) << EAST) << 4*NORTH;
            Bitboard nnnnw = ((bb & ~FileABB) >> EAST) << 4*NORTH;
            Bitboard sssse = ((bb & ~FileQBB) << EAST) >> 4*NORTH;
            Bitboard ssssw = ((bb & ~FileABB) >> EAST) >> 4*NORTH;

            Bitboard nwwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB) >> 4*EAST) << NORTH;
            Bitboard neeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB) << 4*EAST) << NORTH;
            Bitboard seeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB) << 4*EAST) >> NORTH;
            Bitboard swwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB) >> 4*EAST) >> NORTH;

            Bitboard nnnww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) << 3*NORTH;
            Bitboard nnnee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) << 3*NORTH;
            Bitboard sssee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) >> 3*NORTH;
            Bitboard sssww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) >> 3*NORTH;


            Bitboard nnwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) << 2*NORTH;
            Bitboard nneee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) << 2*NORTH;
            Bitboard sseee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) >> 2*NORTH;
            Bitboard sswww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) >> 2*NORTH;

            moves = (m4_mask|\
                    s5|w5|e5|n5|\
                    nnnne|nnnnw|sssse|ssssw|\
                    neeee|nwwww|seeee|swwww|\
                    nnnww|nnnee|sssee|sssww|\
                    nnwww|nneee|sseee|sswww\
                    ) & ~Gates & Legal;
            return moves;
        } 

        Bitboard mask_6_move(int square){
            Bitboard bb(0);
            Bitboard moves(0);
            bb.set(square);
            Bitboard m5_mask = mask_5_move(square);
            
            Bitboard s6 = (bb >> 6*NORTH);
            Bitboard n6 = (bb << 6*NORTH);
            Bitboard w6 = (bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB & ~FileEBB & ~FileFBB) >> 6*EAST;
            Bitboard e6 = (bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB & ~FileMBB & ~FileLBB) << 6*EAST;

            Bitboard nnnnne = ((bb & ~FileQBB) << EAST) << 5*NORTH;
            Bitboard nnnnnw = ((bb & ~FileABB) >> EAST) << 5*NORTH;
            Bitboard ssssse = ((bb & ~FileQBB) << EAST) >> 5*NORTH;
            Bitboard sssssw = ((bb & ~FileABB) >> EAST) >> 5*NORTH;

            Bitboard nwwwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB & ~FileEBB) >> 5*EAST) << NORTH;
            Bitboard neeeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB & ~FileLBB) << 5*EAST) << NORTH;
            Bitboard seeeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB & ~FileLBB) << 5*EAST) >> NORTH;
            Bitboard swwwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB & ~FileEBB) >> 5*EAST) >> NORTH;

            Bitboard nnnnww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) << 4*NORTH;
            Bitboard nnnnee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) << 4*NORTH;
            Bitboard ssssee = ((bb & ~FileQBB & ~FilePBB) << 2*EAST) >> 4*NORTH;
            Bitboard ssssww = ((bb & ~FileABB & ~FileBBB) >> 2*EAST) >> 4*NORTH;

            Bitboard nnnwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) << 3*NORTH;
            Bitboard nnneee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) << 3*NORTH;
            Bitboard ssseee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB) << 3*EAST) >> 3*NORTH;
            Bitboard ssswww = ((bb & ~FileABB & ~FileBBB & ~FileCBB) >> 3*EAST) >> 3*NORTH;

            Bitboard nnwwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB) >> 4*EAST) << 2*NORTH;
            Bitboard nneeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB) << 4*EAST) << 2*NORTH;
            Bitboard sseeee = ((bb & ~FileQBB & ~FilePBB & ~FileOBB & ~FileNBB) << 4*EAST) >> 2*NORTH;
            Bitboard sswwww = ((bb & ~FileABB & ~FileBBB & ~FileCBB & ~FileDBB) >> 4*EAST) >> 2*NORTH;

            moves = (m5_mask|\
                    s6|n6|w6|e6|\
                    nnnnne|nnnnnw|ssssse|sssssw|\
                    nwwwww|neeeee|seeeee|swwwww|\
                    nnnnww|nnnnee|ssssee|ssssww|\
                    nnnwww|nnneee|ssseee|ssswww|\
                    nnwwww|nneeee|sseeee|sswwww\
                    ) & ~Gates & Legal;
            return moves;
        }

    }//namespace bitboards

}//namespace paisho
