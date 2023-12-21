
#include "Bitboard.h"
#include "types.h"
#include <iostream>
#include <ostream>

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

    
    void print_move(Move m){
        uint64_t move_type = (m & MOVE_TYPE_MASK) >> MOVE_TYPE_OFFSET;
        uint64_t move_capture = (m & MOVE_CAPTURE_MASK) >> MOVE_CAPTURE_OFFSET;
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
                std::cout << PieceStrings[move_piece] << " " << SquareStrings[move_s1];
                break;
            case HARMPLACE:
                std::cout << SquareStrings[move_s1] << "-" << SquareStrings[move_s2];
                std::cout << "+" << PieceStrings[move_piece] << " " << SquareStrings[move_s3];
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
    
    void print_move_list(Moves mlist){
        for (int i = 0; i < mlist.move_count; i++){
            //std::cout << "About to print " << std::hex << mlist.movelist[i] << std::endl;
            
            print_move(mlist.movelist[i]);
        }
    }


    std::string Bitboards::pretty(Bitboard b){
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

        return "hello";
    }

    namespace Bitboards{

        void get_flower_moves(Board b, int team, int bbflowerpiece, Moves *move_list){
            Bitboard (*mask_move_ptr)(int);
            Bitboard cap_board;
            Bitboard clash_board;
            //Bitboard mask_3_move(int square){
            switch(bbflowerpiece){
                case WhiteW3:
                    mask_move_ptr = &mask_3_move;
                    clash_board = b.bitboards[ClashW3];
                    cap_board = b.bitboards[BlackR3];
                    break;
                case WhiteW4:
                    mask_move_ptr = &mask_4_move;
                    clash_board = b.bitboards[ClashW4];
                    cap_board = b.bitboards[BlackR4];
                    break;
                case WhiteW5:
                    mask_move_ptr = &mask_5_move;
                    clash_board = b.bitboards[ClashW5];
                    cap_board = b.bitboards[BlackR5];
                    break;
                case WhiteR3:
                    mask_move_ptr = &mask_3_move;
                    clash_board = b.bitboards[ClashR3];
                    cap_board = b.bitboards[BlackW3];
                    break;
                case WhiteR4:
                    mask_move_ptr = &mask_4_move;
                    clash_board = b.bitboards[ClashR4];
                    cap_board = b.bitboards[BlackW4];
                    break;
                case WhiteR5:
                    mask_move_ptr = &mask_5_move;
                    clash_board = b.bitboards[ClashR5];
                    cap_board = b.bitboards[BlackW4];
                    break;
                case BlackW3:
                    mask_move_ptr = &mask_3_move;
                    clash_board = b.bitboards[ClashW3];
                    cap_board = b.bitboards[WhiteR3];
                    break;
                case BlackW4:
                    mask_move_ptr = &mask_4_move;
                    clash_board = b.bitboards[ClashW4];
                    cap_board = b.bitboards[WhiteR4];
                    break;
                case BlackW5:
                    mask_move_ptr = &mask_5_move;
                    clash_board = b.bitboards[ClashW5];
                    cap_board = b.bitboards[WhiteR5];
                    break;
                case BlackR3:
                    mask_move_ptr = &mask_3_move;
                    clash_board = b.bitboards[ClashR3];
                    cap_board = b.bitboards[WhiteW3];
                    break;
                case BlackR4:
                    mask_move_ptr = &mask_4_move;
                    clash_board = b.bitboards[ClashR4];
                    cap_board = b.bitboards[WhiteW4];
                    break;
                case BlackR5:
                    mask_move_ptr = &mask_5_move;
                    clash_board = b.bitboards[ClashR5];
                    cap_board = b.bitboards[WhiteW5];
                    break;
                case BlackTameOrchid:
                    mask_move_ptr = &mask_6_move;
                    clash_board = Illegal;
                    cap_board = Illegal;
                    break;
                case WhiteTameOrchid:
                    mask_move_ptr = &mask_6_move;
                    clash_board = Illegal;
                    cap_board = Illegal;
                    break;
                case BlackWildOrchid:
                    mask_move_ptr = &mask_6_move;
                    clash_board = Illegal;
                    cap_board = b.bitboards[AllWhiteFlowers] & b.bitboards[WhiteLotus];
                    break;
                case WhiteWildOrchid:
                    mask_move_ptr = &mask_6_move;
                    clash_board = Illegal;
                    cap_board = b.bitboards[AllBlackFlowers] & b.bitboards[BlackLotus];
                    break;
                case WhiteLotus:
                    mask_move_ptr = &mask_2_move;
                    clash_board = Illegal;
                    cap_board = Illegal;
                    break;
                case BlackLotus:
                    mask_move_ptr = &mask_2_move;
                    clash_board = Illegal;
                    cap_board = Illegal;
                    break;
              default:
                    std::cout << "bad piece in get quiet moves" << std::endl;
            }
            
            Bitboard w3_copy = b.bitboards[bbflowerpiece];

            //Go through each piece and generate moves for it
            int t_src = get_lsb(w3_copy);
            Bitboard t_dests;
            while (t_src != -1){ //First look at quiet moves only
                t_dests = mask_move_ptr(t_src) & \
                          ~b.bitboards[AllPieces] & \
                          ~clash_board;

                int t_dest = get_lsb(t_dests);
                while (t_dest != -1){
                    int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                    //std::cout << std::hex << MOVE  << " " << t_src << " " << t_dest << std::endl;
                    Move t_move = (MOVE << MOVE_TYPE_OFFSET) |\
                                    (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                    (t_src << MOVE_S1_OFFSET) |\
                                    (t_dest << MOVE_S2_OFFSET);
                    move_list->movelist[move_list->move_count++] = t_move;
                    t_dests.reset(t_dest);
                    t_dest = get_lsb(t_dests);
                }
            //~(b.bitboards[AllBlackFlowers] ^ b.bitboards[BlackR3]); //Case for capturing 
                w3_copy.reset(t_src);
                t_src = get_lsb(w3_copy);
            }
        }

        void get_harmony_place_moves(Board b, int team, int bbflowerpiece, Moves *move_list){
            if ((team == WHITE) && (b.bitboards[AllWhiteFlowers] & b.bitboards[WhiteTameOrchid] & b.bitboards[WhiteWildOrchid] & b.bitboards[WhiteLotus] & Gates).any()){
                //Trying to harmony place with a growing tile in gate
                return;
            }

            Bitboard (*mask_move_ptr)(int);
            Bitboard harm_board; //harm1 & harm2
            Bitboard cap_board;

            switch(bbflowerpiece){
                case WhiteW3:
                    mask_move_ptr = &mask_3_move;
                    harm_board = b.bitboards[WhiteHarmW4] | b.bitboards[WhiteHarmR5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackR3];
                    break;
                case WhiteW4:
                    mask_move_ptr = &mask_4_move;
                    harm_board = b.bitboards[WhiteHarmW3] | b.bitboards[WhiteHarmW5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackR4];
                    break;
                case WhiteW5:
                    mask_move_ptr = &mask_5_move;
                    harm_board = b.bitboards[WhiteHarmW4] | b.bitboards[WhiteHarmR3] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackR5];
                    break;
                case WhiteR3:
                    mask_move_ptr = &mask_3_move;
                    harm_board = b.bitboards[WhiteHarmR4] | b.bitboards[WhiteHarmW5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackW3];
                    break;
                case WhiteR4:
                    mask_move_ptr = &mask_4_move;
                    harm_board = b.bitboards[WhiteHarmR5] | b.bitboards[WhiteHarmR3] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackW4];
                    break;
                case WhiteR5:
                    mask_move_ptr = &mask_5_move;
                    harm_board = b.bitboards[WhiteHarmR4] | b.bitboards[WhiteHarmW5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[BlackW4];
                    break;
                case BlackW3:
                    mask_move_ptr = &mask_3_move;
                    harm_board = b.bitboards[BlackHarmW4] | b.bitboards[BlackHarmW5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteR3];
                    break;
                case BlackW4:
                    mask_move_ptr = &mask_4_move;
                    harm_board = b.bitboards[BlackHarmW5] | b.bitboards[BlackHarmW3] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteR4];
                    break;
                case BlackW5:
                    mask_move_ptr = &mask_5_move;
                    harm_board = b.bitboards[BlackHarmW4] | b.bitboards[BlackHarmR3] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteR5];
                    break;
                case BlackR3:
                    mask_move_ptr = &mask_3_move;
                    harm_board = b.bitboards[BlackHarmW5] | b.bitboards[BlackHarmR4] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteW3];
                    break;
                case BlackR4:
                    mask_move_ptr = &mask_4_move;
                    harm_board = b.bitboards[BlackHarmR3] | b.bitboards[BlackHarmR5] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteW4];
                    break;
                case BlackR5:
                    mask_move_ptr = &mask_5_move;
                    harm_board = b.bitboards[BlackHarmR4] | b.bitboards[BlackHarmW3] | b.bitboards[WhiteLotus] | b.bitboards[BlackLotus];
                    cap_board = b.bitboards[WhiteW5];
                    break;
                case BlackTameOrchid:
                    mask_move_ptr = &mask_6_move;
                    harm_board = Illegal;
                    break;
                case WhiteTameOrchid:
                    mask_move_ptr = &mask_6_move;
                    harm_board = Illegal;
                    break;
                case BlackWildOrchid:
                    mask_move_ptr = &mask_6_move;
                    harm_board = Illegal;
                    break;
                case WhiteWildOrchid:
                    mask_move_ptr = &mask_6_move;
                    harm_board = Illegal;
                    break;
                case WhiteLotus:
                    mask_move_ptr = &mask_2_move;
                    harm_board = Illegal;
                    break;
                case BlackLotus:
                    mask_move_ptr = &mask_2_move;
                    harm_board = Illegal;
                    break;
              default:
                    std::cout << "bad piece in get harm place moves" << std::endl;
            }
            //Note have to add lotus to harm board cases
            int w3Pieces, w4Pieces, w5Pieces, r3Pieces, r4Pieces, r5Pieces;
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

            Bitboard w3_copy = b.bitboards[bbflowerpiece];
            //Go through each piece and generate moves for it
            int t_src = get_lsb(w3_copy);
            Bitboard t_dests;
            Bitboard t_open_gates;
            while (t_src != -1){ //First look at quiet moves only
                t_dests = mask_move_ptr(t_src) & \
                          harm_board;

                int t_dest = get_lsb(t_dests);
                while (t_dest != -1){
                    int cap_bit = cap_board[t_dest]; //If you are landing on a capturable piece, set bit to 1
                    t_open_gates = Gates & ~b.bitboards[AllPieces];
                    int t_open_gate = get_lsb(t_open_gates);
                    while (t_open_gate != -1){
                        for (int i = 0; i < num_pieces; i++){
                            int piece_bits = pieces_in_hand[i];
                            Move t_move = (HARMPLACE << MOVE_TYPE_OFFSET) |\
                                            (cap_bit << MOVE_CAPTURE_OFFSET) |\
                                            (t_src << MOVE_S1_OFFSET) |\
                                            (t_dest << MOVE_S2_OFFSET) |\
                                            (piece_bits << MOVE_PIECE_OFFSET) |\
                                            ((uint64_t) t_open_gate << MOVE_S3_OFFSET);
                            move_list->movelist[move_list->move_count++] = t_move;
                        }
                        t_open_gates.reset(t_open_gate);
                        t_open_gate = get_lsb(t_open_gates);
                    }
                    t_dests.reset(t_dest);
                    t_dest = get_lsb(t_dests);
                }
                w3_copy.reset(t_src);
                t_src = get_lsb(w3_copy);
            }
        }


        //get_flower_moves(Board b, int team, int bbflowerpiece, Moves *move_list){
        Moves get_moves(Board b, int team){
            Moves move_list;
            move_list.move_count = 0;
            int piece_list[9];
            if (team == WHITE){
                piece_list[0] = WhiteW3;
                piece_list[1] = WhiteW4;
                piece_list[2] = WhiteW5;
                piece_list[3] = WhiteR3;
                piece_list[4] = WhiteR4;
                piece_list[5] = WhiteR5;
                piece_list[6] = WhiteLotus;
                piece_list[7] = WhiteTameOrchid;
                piece_list[8] = WhiteWildOrchid;
            } else{
                piece_list[0] = BlackW3;
                piece_list[1] = BlackW4;
                piece_list[2] = BlackW5;
                piece_list[3] = BlackR3;
                piece_list[4] = BlackR4;
                piece_list[5] = BlackR5;
                piece_list[6] = BlackLotus;
                piece_list[7] = BlackTameOrchid;
                piece_list[8] = BlackWildOrchid;
            }
            for (int i = 0; i < 9; i++){
                get_flower_moves(b, team, piece_list[i], &move_list);
                get_harmony_place_moves(b, team, piece_list[i], &move_list);
            }
            return move_list;
        }

        int get_lsb(Bitboard b){
            Bitboard mask(1);
            for (int i = 0; i < NUM_SQUARES; i++){
                if ((mask & b).any()){
                    return i;
                }else{
                    mask <<= 1;
                }
            }
            return -1; //There is no 1
        }

        void init(){
            return;
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

}
