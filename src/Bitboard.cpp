
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

        switch(m.fields.move_type){
            case MOVE:
                std::cout << SquareStrings.at(m.fields.s1) << "-" << SquareStrings.at(m.fields.s2);
                break;
            case PLACE:
                std::cout << WhitePieceStrings[m.fields.piece] << " " << SquareStrings.at(m.fields.s1);
                break;
            case HARMPLACE:
                std::cout << SquareStrings.at(m.fields.s1) << "-" << SquareStrings.at(m.fields.s2);
                std::cout << "+" << WhitePieceStrings[m.fields.auxpiece] << " " << SquareStrings.at(m.fields.s3);
                break;
            case HARMACCENT:
                if (m.fields.boatmove){
                    std::cout << SquareStrings.at(m.fields.s1) << "-" << SquareStrings.at(m.fields.s2);
                    std::cout << "+" << AccentStrings[m.fields.auxpiece] << " " << SquareStrings.at(m.fields.s3) << "-" << SquareStrings.at(m.fields.s4);
                    //std::cout << std::dec << " " << m.fields.s4 << " " << SquareStrings.at(m.fields.s4);
                } else{
                    std::cout << SquareStrings.at(m.fields.s1) << "-" << SquareStrings.at(m.fields.s2);
                    std::cout << "+" << AccentStrings[m.fields.auxpiece] << " " << SquareStrings.at(m.fields.s3);
                }
                break;
            default:
                std::cout << "move type not detected " << std::hex << m.fields.move_type;
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
                if(b.whiteBoard.boards.at(i)[sq]){
                    sq_strs[sq] = WhitePieceStrings.at(i) + " ";
                }else if (b.blackBoard.boards.at(i)[sq]){
                    sq_strs[sq] = BlackPieceStrings.at(i) + " ";
                }
            }
        }

        for(int i = 0; i < NUM_SQUARES; i++){
           if(b.otherBoards.at(Accents).test(i)){
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
        Bitboard get_harm_pieces(const TeamBoard& b, int flower){
            Bitboard harm_board;
            const Bitboard *t_board = &b.boards.at(0);
            const Bitboard *opps_board = &(*(b.oppsBoards)).at(0);

            switch(flower){
                case w3:
                    harm_board = t_board[w4] | t_board[r5] | t_board[lotus] | opps_board[lotus];
                    break;
                case w4:
                    harm_board = t_board[w3] | t_board[w5] | t_board[lotus] | opps_board[lotus];
                    break;
                case w5:
                    harm_board = t_board[w4] | t_board[r3] | t_board[lotus] | opps_board[lotus];
                    break;
                case r3:
                    harm_board = t_board[r4] | t_board[w5] | t_board[lotus] | opps_board[lotus];
                    break;
                case r4:
                    harm_board = t_board[r5] | t_board[r3] | t_board[lotus] | opps_board[lotus];
                    break;
                case r5:
                    harm_board = t_board[r4] | t_board[w5] | t_board[lotus] | opps_board[lotus];
                    break;
                //Lotus only harmonizes with own team.fields.
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


        Bitboard get_harm_board(const TeamBoard& b, int flower){
            Bitboard harm_board;
            const Bitboard *opps_board = &(*(b.oppsBoards)).at(0);
            
            switch(flower){
                case w3:
                    harm_board = b.boards.at(harmw4) | b.boards.at(harmr5) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                case w4:
                    harm_board = b.boards.at(harmw3) | b.boards.at(harmw5) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                case w5:
                    harm_board = b.boards.at(harmw4) | b.boards.at(harmr3) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                case r3:
                    harm_board = b.boards.at(harmr4) | b.boards.at(harmw5) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                case r4:
                    harm_board = b.boards.at(harmr5) | b.boards.at(harmr3) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                case r5:
                    harm_board = b.boards.at(harmr4) | b.boards.at(harmw5) | b.boards.at(harmlotus) | opps_board[harmlotus];
                    break;
                //Lotus only harmonizes with own team.fields.
                case orchid:
                    harm_board = Illegal & Legal;
                    break;
                case lotus:
                    harm_board = b.boards.at(harmw3) | b.boards.at(harmw4) | b.boards.at(harmw5) | b.boards.at(harmr3) | b.boards.at(harmr4) | b.boards.at(harmr5);
                    break;
              default:
                    std::cout << "bad piece in get harm board" << std::endl;
            }
            
            return harm_board;
        }

        Bitboard get_cap_board(const TeamBoard& b, int bbpiece){
            Bitboard cap_board;
            const Bitboard *t_board;
            const Bitboard *opps_board;
            bool wild;

            t_board = &b.boards.at(0);
            opps_board = &(*(b.oppsBoards)).at(0);
            wild = b.wild;

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


        Bitboard get_clash_board(const TeamBoard& b, int piece){
            const Bitboard *opps_board = &(*(b.oppsBoards)).at(0);
            switch(piece){
                case w3: return b.boards.at(harmr3) | opps_board[harmr3];
                case w4: return b.boards.at(harmr4) | opps_board[harmr4];
                case w5: return b.boards.at(harmr5) | opps_board[harmr5];
                case r3: return b.boards.at(harmw3) | opps_board[harmw3];
                case r4: return b.boards.at(harmw4) | opps_board[harmw4];
                case r5: return b.boards.at(harmw5) | opps_board[harmw5];
                default: return Bitboard(0);
            }
        }

        void get_flower_moves(const TeamBoard& b, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            team_board = &b.boards.at(0);


            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard cap_board = get_cap_board(b, bbflowerpiece);
            Bitboard clash_board = get_clash_board(b, bbflowerpiece);
            Bitboard w3_copy = team_board[bbflowerpiece];

            //Go through each piece and generate moves for it
            Bitboard t_dests;
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if (w3_copy[t_src]){
                    t_dests = mask_move_ptr(t_src) & \
                              (~(*(b.otherBoards)).at(AllPieces) ^ cap_board) & 
                              (~clash_board) & correct_color(bbflowerpiece);
                    
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                        //while (t_dest != -1){
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            Move t_move = { .bits = 0};
                            t_move.fields.move_type=MOVE;
                            t_move.fields.capture=cap_bit;
                            t_move.fields.piece=bbflowerpiece;
                            t_move.fields.s1=t_src;
                            t_move.fields.s2=t_dest;
                            
                            move_list.push_back(t_move);
                        }
                    }
                }
            }
        }



        //This function does NOT include boat moves that move a flower piece from tile to tile.
        void get_harmony_accent_moves(const TeamBoard& b, int bbflowerpiece, Moves& move_list){

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, bbflowerpiece); //harm1 & harm2
            
            Bitboard cap_board = get_cap_board(b, bbflowerpiece);

            //Note have to add lotus to harm board cases
            int pieces_in_hand[4];
            int num_pieces = 0;
        
            if (b.accents.rocks)
                pieces_in_hand[num_pieces++] = Rock;
            if (b.accents.knotweeds)
                pieces_in_hand[num_pieces++] = Knotweed;
            if (b.accents.wheels)
                pieces_in_hand[num_pieces++] = Wheel;
            if (b.accents.boats)
                pieces_in_hand[num_pieces++] = Boat;

            Bitboard w3_copy = b.boards.at(bbflowerpiece);
            //Go through each piece and generate moves for it
            Bitboard t_dests;
            Bitboard harm_pieces = get_harm_pieces(b, bbflowerpiece);
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if(w3_copy[t_src]){
            //while (t_src != -1){ //square piece is being moved from
                    Bitboard updated_harm = remove_duplicate_harm(harm_pieces, harm_board, t_src);

                    t_dests = mask_move_ptr(t_src) & \
                              ~(*b.otherBoards).at(Accents) & \
                              updated_harm & \
                              correct_color(bbflowerpiece) & \
                              (~(b.boards.at(allflowers)) | cap_board);

                    //int t_dest = get_lsb(t_dests);
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                        //while (t_dest != -1){//square piece is being moved to
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            
                            for(int i = 0; i < num_pieces; i++){//For each aux piece in the player's hand
                                int auxpiece = pieces_in_hand[i];
                                if (auxpiece == Rock || auxpiece == Knotweed){
                                    Bitboard post_move_bb = (*b.otherBoards).at(AllPieces);
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
                                            Move t_move = {.bits = 0};
                                            t_move.fields.move_type = HARMACCENT;
                                            t_move.fields.capture = cap_bit;
                                            t_move.fields.piece = bbflowerpiece;
                                            t_move.fields.s1 = t_src;
                                            t_move.fields.s2 = t_dest;
                                            t_move.fields.auxpiece = auxpiece;
                                            t_move.fields.s3 = auxpiece_square;
                                            move_list.push_back(t_move);
                                            //move_list[move_list.move_count++] = t_move;
                                        }
                                    }
                                }else if (auxpiece == Wheel){
                                    Bitboard post_move_bb = (*b.otherBoards).at(AllPieces);
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
                                                Move t_move = {.bits = 0};
                                                t_move.fields.move_type = HARMACCENT;
                                                t_move.fields.capture = cap_bit;
                                                t_move.fields.piece = bbflowerpiece;
                                                t_move.fields.s1 = t_src;
                                                t_move.fields.s2 = t_dest;
                                                t_move.fields.auxpiece = auxpiece;
                                                t_move.fields.s3 = auxpiece_square;
                                                move_list.push_back(t_move);
                                            }
                                        }
                                    }

                                }else if (auxpiece == Boat){
                                    Bitboard all_accents = (*b.otherBoards).at(Accents);
                                    //int t_accent = get_lsb(all_accents);
                                    //while (t_accent != -1){
                                    for(int t_accent = 0; t_accent < NUM_SQUARES; t_accent++){
                                        if(all_accents[t_accent]){
                                            Move t_move = { .bits = 0};
                                            t_move.fields.move_type = HARMACCENT;
                                            t_move.fields.capture = cap_bit;
                                            t_move.fields.piece = bbflowerpiece;
                                            t_move.fields.s1 = t_src;
                                            t_move.fields.s2 = t_dest;
                                            t_move.fields.auxpiece = auxpiece;
                                            t_move.fields.s3 = t_accent;
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

        void get_harmony_place_moves(const TeamBoard& b, int bbflowerpiece, Moves& move_list){
            const Bitboard *teamboard = &b.boards.at(0);

            bool only_lotus_orc = false;

            if ((teamboard[allflowers] & Gates).any()){
                only_lotus_orc = true;
                //Trying to harmony place with a growing tile in gate
            }

            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, bbflowerpiece); //harm1 & harm2
            Bitboard cap_board = get_cap_board(b, bbflowerpiece);

            //pretty(harm_board);
            //Note have to add lotus to harm board cases
            int pieces_in_hand[8];
            int num_pieces = 0;
                        
            if(!only_lotus_orc){
                if (b.w3)
                    pieces_in_hand[num_pieces++] = w3;
                if (b.w4)
                    pieces_in_hand[num_pieces++] = w4;
                if (b.w5)
                    pieces_in_hand[num_pieces++] = w5;
                if (b.r3)
                    pieces_in_hand[num_pieces++] = r3;
                if (b.r4)
                    pieces_in_hand[num_pieces++] = r4;
                if (b.r5)
                    pieces_in_hand[num_pieces++] = r5;
            }
            if (b.o)
                pieces_in_hand[num_pieces++] = orchid;
            if (b.l)
                pieces_in_hand[num_pieces++] = lotus;


            Bitboard w3_copy = teamboard[bbflowerpiece];
            //Go through each piece and generate moves for it
            Bitboard t_dests;
            Bitboard t_open_gates;
            Bitboard harm_pieces = get_harm_pieces(b, bbflowerpiece);
            for(int t_src = 0; t_src < NUM_SQUARES; t_src++){
                if (w3_copy[t_src]){
                //while (t_src != -1){ //First look at quiet moves only
                    Bitboard updated_harm = remove_duplicate_harm(harm_pieces, harm_board, t_src);
                    t_dests = mask_move_ptr(t_src) & \
                              updated_harm & \
                              correct_color(bbflowerpiece) & \
                              ~(*b.otherBoards).at(Accents) & \
                              (~teamboard[allflowers] | cap_board);

                    //int t_dest = get_lsb(t_dests);
                    for(int t_dest = 0; t_dest < NUM_SQUARES; t_dest++){
                        if(t_dests[t_dest]){
                            int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                            t_open_gates = Gates & ~(*b.otherBoards).at(AllPieces);

                            
                            //int t_open_gate = get_lsb(t_open_gates);
                            for(int t_open_gate = 0; t_open_gate < NUM_SQUARES; t_open_gate++){
                                if(t_open_gates[t_open_gate]){
                                    for (int i = 0; i < num_pieces; i++){
                                        int piece_bits = pieces_in_hand[i];
                                        Move t_move = { .bits = 0};
                                        t_move.fields.move_type = HARMPLACE;
                                        t_move.fields.capture = cap_bit;
                                        t_move.fields.s1 = t_src;
                                        t_move.fields.s2 = t_dest;
                                        t_move.fields.piece = bbflowerpiece;
                                        t_move.fields.auxpiece = piece_bits;
                                        t_move.fields.s3 = t_open_gate;
                                        move_list.push_back(t_move);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        void get_place_moves(const TeamBoard& b, Moves& move_list){
            //Note have to add lotus to harm board cases
            int pieces_in_hand[8];
            int num_pieces = 0;
            
            if (b.w3)
                pieces_in_hand[num_pieces++] = w3;
            if (b.w4)
                pieces_in_hand[num_pieces++] = w4;
            if (b.w5)
                pieces_in_hand[num_pieces++] = w5;
            if (b.r3)
                pieces_in_hand[num_pieces++] = r3;
            if (b.r4)
                pieces_in_hand[num_pieces++] = r4;
            if (b.r5)
                pieces_in_hand[num_pieces++] = r5;


            Bitboard t_open_gates = Gates & ~(*b.otherBoards).at(AllPieces);
            int t_open_gate = get_lsb(t_open_gates);
            while (t_open_gate != -1){
                for (int i = 0; i < num_pieces; i++){
                    int piece_bits = pieces_in_hand[i];
                    Move t_move = { .bits = 0};
                    t_move.fields.move_type=PLACE;
                    t_move.fields.s1 = t_open_gate;
                    t_move.fields.piece = piece_bits;
                    move_list.push_back(t_move);
                }
                t_open_gates.reset(t_open_gate);
                t_open_gate = get_lsb(t_open_gates);
            }
        }
        

        void get_boat_flower_moves(const TeamBoard& b, int bbflowerpiece, Moves& move_list){
            const Bitboard *team_board;
            const Bitboard *opps_board = &(*(b.oppsBoards)).at(0);
            if(!b.accents.boats){
                return;
            }
            team_board = &b.boards.at(0);


            mask_ptr mask_move_ptr = mask_move_map(bbflowerpiece);
            Bitboard harm_board = get_harm_board(b, bbflowerpiece); //harm1 & harm2
            Bitboard cap_board = get_cap_board(b, bbflowerpiece);

            //Note have to add lotus to harm board cases
            
            Bitboard w3_copy = team_board[bbflowerpiece];
            //Go through each piece and generate moves for it
            int t_src = get_lsb(w3_copy);
            Bitboard t_dests;
            while (t_src != -1){ //square piece is being moved from
                t_dests = mask_move_ptr(t_src) & \
                          harm_board & \
                          correct_color(bbflowerpiece) & \
                          ~(*b.otherBoards).at(Accents) & \
                          (~team_board[allflowers] | cap_board);

                int t_dest = get_lsb(t_dests);
                while (t_dest != -1){//square piece is being moved to
                    int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                    Bitboard post_move_bb = team_board[allflowers] & opps_board[allflowers];
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
                            Move t_move = { .bits = 0};
                            t_move.fields.move_type=HARMACCENT;
                            t_move.fields.capture=cap_bit;
                            t_move.fields.s1=t_src;
                            t_move.fields.s2=t_dest;
                            t_move.fields.auxpiece=Boat;
                            t_move.fields.piece=bbflowerpiece;
                            t_move.fields.s3=boat_square;
                            t_move.fields.s4=s4_square;
                            t_move.fields.boatmove=1;
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

        Moves get_moves(const TeamBoard& b){
            Moves move_list;
            int piece_list[] = {w3,w4,w5,r3,r4,r5,lotus,orchid};

            for (int i = 0; i < 8; i++){
                get_flower_moves(b, piece_list[i], move_list);
                //get_harmony_place_moves(b, piece_list[i], move_list);
                //get_harmony_accent_moves(b, piece_list[i], move_list);
                //get_boat_flower_moves(b, piece_list[i], move_list);
                //get harmony boat moves
            }
            get_place_moves(b, move_list);
            return move_list;
        }


        int get_lsb(const Bitboard b){
            for (int i = 0; i < NUM_SQUARES-3; i++){//-3 since some are out of bounds we dont care about
                if (b[i])
                    return i;
            }
            return -1; //There is no 1
        }

        void make_place_move(TeamBoard& b, int piece, int square){
            switch(piece){
                case w3:
                    b.w3--;
                    break;
                case w4:
                    b.w4--;
                    break;
                case w5:
                    b.w5--;
                    break;
                case r3:
                    b.r3--;
                    break;
                case r4:
                    b.r4--;
                    break;
                case r5:
                    b.r5--;
                    break;
                case lotus:
                    b.l = false;
                    break;
                case orchid:
                    b.o = false;
                    break;
            }

            
            //Set all pieces board, set team board
            (*b.otherBoards).at(AllPieces).set(square);
            b.boards[allflowers].set(square);
            b.boards[piece].set(square);            
        }

        void make_move_move(TeamBoard& b, int piece, int src, int dst, bool cap){
            //Bitboard *team_board;
            //Bitboard *opps_board;

            //team_board = &b.boards.at(0);
            //opps_board = &(*(b.oppsBoards)).at(0);
            if (piece == lotus)
                b.wild = true;

            
            if (cap){
                //Find which tile is being captured, and remove from opponents boards
                //Maybe reset all boards?
                for (int i = 0; i < NUM_BOARDS; i++)
                    (*b.oppsBoards).at(i).reset(dst);
            } else{
                (*b.otherBoards).at(AllPieces).set(dst); //if capturing piece, allpieces already set. only set if not capping.
            }
            
            (*b.otherBoards).at(AllPieces).reset(src);
            b.boards.at(piece).reset(src);
            b.boards.at(allflowers).reset(src);
            b.boards.at(piece).set(dst);
            b.boards.at(allflowers).set(dst);

        }

        void make_harm_place_move(TeamBoard& b, int piece, int src, int dst, int auxflower, int placesq, bool cap){
            make_move_move(b, piece, src, dst, cap);
            make_place_move(b, auxflower, placesq);
        }

        
        void make_harm_accent_move(TeamBoard& b, int piece, int src, int dst, int auxpiece, int auxsq, bool cap){
            make_move_move(b, piece, src, dst, cap);
            switch (auxpiece){
                case Rock:
                    b.accents.rocks--;
                    break;
                case Knotweed:
                    b.accents.knotweeds--;
                    break;
                case Wheel:
                    b.accents.wheels--;
                    break;
                case Boat:
                    b.accents.boats--;
                    break;
            }
        

            (*b.otherBoards).at(Accents).set(auxsq);
            (*b.otherBoards).at(AllPieces).set(auxsq);

            if (auxpiece == Rock){
                (*b.otherBoards).at(Rocks).set(auxsq);
            } else if (auxpiece == Wheel){
                TeamBoard copy = b;
                //int hmoves[8] = {EAST, EAST+NORTH, NORTH, NORTH+WEST, WEST, SOUTH+WEST, SOUTH, SOUTH+EAST};
                int hmoves[8] = {SOUTH+EAST, SOUTH, SOUTH+WEST, WEST, NORTH+WEST, NORTH, EAST+NORTH, EAST};
                
                for(int t_board = 0; t_board < NUM_BOARDS; t_board++){ //TODO: this can be optimized since half the boards are harmonies.
                    b.boards.at(t_board)[auxsq + hmoves[0]] = copy.boards.at(t_board)[auxsq + hmoves[7]];
                    for (int t_move=1; t_move<8; t_move++){
                        b.boards.at(t_board)[auxsq + hmoves[t_move]] = copy.boards.at(t_board)[auxsq + hmoves[t_move-1]];
                    }

                    (*b.oppsBoards).at(t_board)[auxsq + hmoves[0]] = (*copy.oppsBoards).at(t_board)[auxsq + hmoves[7]];
                    for (int t_move=1; t_move<8; t_move++){
                        (*b.oppsBoards).at(t_board)[auxsq + hmoves[t_move]] = (*copy.oppsBoards).at(t_board)[auxsq + hmoves[t_move-1]];
                    }
                }

                for(int t_board = 0; t_board < NUM_OTHER_BOARDS; t_board++){
                    (*b.otherBoards).at(t_board)[auxsq + hmoves[0]] = (*copy.otherBoards).at(t_board)[auxsq + hmoves[7]];
                    for (int t_move=1; t_move<8; t_move++){
                        (*b.otherBoards).at(t_board)[auxsq + hmoves[t_move]] = (*copy.otherBoards).at(t_board)[auxsq + hmoves[t_move-1]];
                    }

                }
                
            } else if (auxpiece == Boat){
                (*b.otherBoards).at(Rocks).reset(auxsq);
                (*b.otherBoards).at(Knotweeds).reset(auxsq);
            }if (auxpiece == Knotweed){
                (*b.otherBoards).at(Knotweeds).set(auxsq);
            }

        }

        void make_harm_accent_boatmove(TeamBoard& b, int piece, int src, int dst, int boatsq, int boat_move_sq, bool cap){
            make_move_move(b, piece, src, dst, cap);
            b.accents.boats--;

            (*b.otherBoards).at(Accents).set(boatsq);
            (*b.otherBoards).at(AllPieces).set(boat_move_sq);
            //Need all pieces move too
            for(int t_board = 0; t_board < NUM_BOARDS; t_board++){

                if (b.boards.at(t_board)[boatsq]){
                    b.boards.at(t_board).set(boat_move_sq);
                    b.boards.at(t_board).reset(boatsq);
                }

                if ((*b.oppsBoards).at(t_board)[boatsq]){
                    (*b.oppsBoards).at(t_board).set(boat_move_sq);
                    (*b.oppsBoards).at(t_board).reset(boatsq);
                }
                //this is SUPER cursed, going through all arrays in 
                //whiteboards and blackboards by doubling the length of the first
            }
        }

        void make_move(Board& b, int team, Move m){
            TeamBoard *teamboard;
            if (team == WHITE)
                teamboard = &b.whiteBoard;
            else
                teamboard = &b.blackBoard;

            if (m.fields.move_type == MOVE){
                //std::cout<<"in move"<< std::endl;
                make_move_move(*teamboard, m.fields.piece, m.fields.s1, m.fields.s2, m.fields.capture);
            }else if(m.fields.move_type == PLACE){
                //std::cout<<"place"<< std::endl;
                make_place_move(*teamboard, m.fields.piece, m.fields.s1);
            }else if(m.fields.move_type == HARMPLACE){
                //std::cout<<"harmplace"<< std::endl;
                make_harm_place_move(*teamboard, m.fields.piece, m.fields.s1, m.fields.s2, m.fields.auxpiece, m.fields.s3, m.fields.capture);
            }else if(m.fields.move_type == HARMACCENT && !m.fields.boatmove){
                //std::cout<<"harmacc"<< std::endl;
                make_harm_accent_move(*teamboard, m.fields.piece, m.fields.s1, m.fields.s2, m.fields.auxpiece, m.fields.s3, m.fields.capture);
            }else if(m.fields.move_type == HARMACCENT && m.fields.boatmove){
                //std::cout<<"harmacc boatmove"<< std::endl;
                make_harm_accent_boatmove(*teamboard, m.fields.piece, m.fields.s1, m.fields.s2, m.fields.s3, m.fields.s4, m.fields.capture);
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


        void find_harms(TeamBoard& b){
            //HARM CASE
            //int t_piece = w3;
            Bitboard *teamboard;
            //std::deque<std::pair<int, int>> *team_harms;
            teamboard = &(b.boards).at(0);
            //team_harms = &b.harm_pairs;

            b.harm_pairs.clear();
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
                Bitboard harm_board = reverse_harm_lookup(b, harm_map(t_piece)) & ~Gates;
                int harm_ind = harm_map(t_piece);
                //std::cout<<"tpiece " << t_piece << " " << "harm ind " << harm_ind<<std::endl;
                tmp_square = w3_piece + EAST;
                current_row = w3_piece / 17;

                while(tmp_square/17 == current_row && tmp_square < NUM_SQUARES-1 && (*b.otherBoards).at(AllPieces)[tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square += EAST;
                }
                if (tmp_square/17 == current_row && tmp_square < NUM_SQUARES-1){
                    teamboard[harm_ind].set(tmp_square);

                    //if the final square you check is actually a piece you can harmonize with. Add it to the pairs.
                    if(harm_board[tmp_square]){
                        bool found = false;
                        for(int i = 0; i < b.harm_pairs.size(); i++){
                            if(std::pair<int, int>{tmp_square, w3_piece} == b.harm_pairs.at(i)){
                                found = true;
                                break;
                            } 
                        }
                        if (!found){
                            b.harm_pairs.push_back(std::pair<int, int>{w3_piece, tmp_square});
                        }
                    }
                        
                    //if [tmp_square], then add {w3_piece, tmp_square} to harmpairs
                }

                tmp_square = w3_piece - EAST;
                while(tmp_square/17 == current_row && tmp_square >= 0 && (*b.otherBoards).at(AllPieces)[tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square -= EAST;
                }
                if (tmp_square/17 == current_row && tmp_square >= 0){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square]){
                        bool found = false;
                        for(int i = 0; i < b.harm_pairs.size(); i++){
                            if(std::pair<int, int>{tmp_square, w3_piece} == b.harm_pairs.at(i)){
                                found = true;
                                break;
                            } 
                        }
                        if (!found){
                            b.harm_pairs.push_back(std::pair<int, int>{w3_piece, tmp_square});
                        }
                    }
                }

                tmp_square = w3_piece + NORTH;
                while(tmp_square < NUM_SQUARES && (*b.otherBoards).at(AllPieces)[tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square += NORTH;
                }
                if (tmp_square < NUM_SQUARES){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square]){
                        bool found = false;
                        for(int i = 0; i < b.harm_pairs.size(); i++){
                            if(std::pair<int, int>{tmp_square, w3_piece} == b.harm_pairs.at(i)){
                                found = true;
                                break;
                            } 
                        }
                        if (!found){
                            b.harm_pairs.push_back(std::pair<int, int>{w3_piece, tmp_square});

                        }
                    }
                }


                tmp_square = w3_piece - NORTH;
                while(tmp_square >= 0 && (*b.otherBoards).at(AllPieces)[tmp_square] == 0){ //left first
                    teamboard[harm_ind].set(tmp_square);
                    tmp_square -= NORTH;
                }
                if (tmp_square >= 0){
                    teamboard[harm_ind].set(tmp_square);

                    if(harm_board[tmp_square]){
                        bool found = false;
                        for(int i = 0; i < b.harm_pairs.size(); i++){
                            if(std::pair<int, int>{tmp_square, w3_piece} == b.harm_pairs.at(i)){
                                found = true;
                                break;
                            } 
                        }
                        if (!found){
                            b.harm_pairs.push_back(std::pair<int, int>{w3_piece, tmp_square});

                        }
                    }
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
            find_harms(b.whiteBoard);
            find_harms(b.blackBoard);
        }


        //take harmboard index as input, return bitbord of which pieces can harmonize with that piece
        Bitboard reverse_harm_lookup(const TeamBoard& b, int harm_index){
            Bitboard ret;
            const Bitboard *teamboard = &b.boards.at(0);

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
                    ret = teamboard[allflowers];
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
