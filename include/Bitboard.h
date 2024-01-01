
#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <bitset>
#include "types.h"
#include <map>
//using Bitboard = std::bitset<224>;

std::string GetBinaryStringFromHexString (std::string sHex);

#define NUM_SQUARES 290
#define FullFile (Bitboard(GetBinaryStringFromHexString("100008000400020001000080004000200010000800040002000100008000400020001")))
#define FileABB ((FullFile) & Legal)
#define FileBBB ((FullFile << 1) & Legal)
#define FileCBB ((FullFile << 2) & Legal)
#define FileDBB ((FullFile << 3) & Legal)
#define FileEBB ((FullFile << 4) & Legal)
#define FileFBB ((FullFile << 5) & Legal)
#define FileGBB ((FullFile << 6) & Legal)
#define FileHBB ((FullFile << 7) & Legal)
#define FileIBB ((FullFile << 8) & Legal)
#define FileJBB ((FullFile << 9) & Legal)
#define FileKBB ((FullFile << 10) & Legal)
#define FileLBB ((FullFile << 11) & Legal)
#define FileMBB ((FullFile << 12) & Legal)
#define FileNBB ((FullFile << 13) & Legal)
#define FileOBB ((FullFile << 14) & Legal)
#define FilePBB ((FullFile << 15) & Legal)
#define FileQBB ((FullFile << 16) & Legal)

#define FullRank (Bitboard(GetBinaryStringFromHexString("ffff")+"1"))

#define Rank1BB (FullRank & Legal)
#define Rank2BB ((FullRank << (17 * 1)) & Legal)
#define Rank3BB ((FullRank << (17 * 2)) & Legal)
#define Rank4BB ((FullRank << (17 * 3)) & Legal)
#define Rank5BB ((FullRank << (17 * 4)) & Legal)
#define Rank6BB ((FullRank << (17 * 5)) & Legal)
#define Rank7BB ((FullRank << (17 * 6)) & Legal)
#define Rank8BB ((FullRank << (17 * 7)) & Legal)
#define Rank9BB ((FullRank << (17 * 8)) & Legal)
#define Rank10BB ((FullRank << (17 * 9)) & Legal)
#define Rank11BB ((FullRank << (17 * 10)) & Legal)
#define Rank12BB ((FullRank << (17 * 11)) & Legal)
#define Rank13BB ((FullRank << (17 * 12)) & Legal)
#define Rank14BB ((FullRank << (17 * 13)) & Legal)
#define Rank15BB ((FullRank << (17 * 14)) & Legal)
#define Rank16BB ((FullRank << (17 * 15)) & Legal)
#define Rank17BB ((FullRank << (17 * 16)) & Legal)

#define Gates ((Bitboard(1)<<Paisho::i1) | (Bitboard(1)<<Paisho::i17) | (Bitboard(1)<<Paisho::a9) | (Bitboard(1)<<Paisho::q9))

#define Illegal (Bitboard("11110000000001111") |\
    (Bitboard("11100000000000111") << Paisho::NORTH) |\
    (Bitboard("11000000000000011") << 2*Paisho::NORTH) |\
    (Bitboard("10000000000000001") << 3*Paisho::NORTH) | \
    (Bitboard("11110000000001111") << 16*Paisho::NORTH) |\
    (Bitboard("11100000000000111") << 15*Paisho::NORTH) |\
    (Bitboard("11000000000000011") << 14*Paisho::NORTH) |\
    (Bitboard("10000000000000001") << 13*Paisho::NORTH))



#define Legal (~Illegal)
#define Red ((Bitboard("11111") << (7*Paisho::NORTH + 3*Paisho::EAST)) |\
    (Bitboard("11111") << (9*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("1111") << (6*Paisho::NORTH + 4*Paisho::EAST)) |\
    (Bitboard("1111") << (10*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("111") << (5*Paisho::NORTH + 5*Paisho::EAST)) |\
    (Bitboard("111") << (11*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("11") << (4*Paisho::NORTH + 6*Paisho::EAST)) |\
    (Bitboard("11") << (12*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("1") << (3*Paisho::NORTH + 7*Paisho::EAST)) |\
    (Bitboard("1") << (13*Paisho::NORTH + 9*Paisho::EAST)))

#define White ((Bitboard("11111") << (7*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("11111") << (9*Paisho::NORTH + 3*Paisho::EAST)) |\
    (Bitboard("1111") << (6*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("1111") << (10*Paisho::NORTH + 4*Paisho::EAST)) |\
    (Bitboard("111") << (5*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("111") << (11*Paisho::NORTH + 5*Paisho::EAST)) |\
    (Bitboard("11") << (4*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("11") << (12*Paisho::NORTH + 6*Paisho::EAST)) |\
    (Bitboard("1") << (3*Paisho::NORTH + 9*Paisho::EAST)) |\
    (Bitboard("1") << (13*Paisho::NORTH + 7*Paisho::EAST)))

#define Neutral (Legal^Red^White^Gates)

//#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (Bitboard(1) << square) : 0)

namespace Paisho{
    //Used to initialize all the bitboards
    Board init_board();
    void print_move(Move m);
    void print_move_list(Moves ml);
    //use one char (8 bits) to pick from {rock1, r2, knot1, knot2, w1, w2, b1, b2}
    typedef Bitboard (*mask_ptr)(int);


    
    enum Direction: int{
        NORTH = 17,
        EAST = 1,
        SOUTH = -NORTH,
        WEST = -EAST,

        NORTH_EAST = NORTH + EAST,
        NORTH_WEST = NORTH + WEST,
        SOUTH_EAST = SOUTH + EAST,
        SOUTH_WEST = SOUTH + WEST,
    };

    namespace Bitboards{


        static std::map<int, Bitboard> col_map{
                                {0, FileABB},
                                {1, FileBBB},
                                {2, FileCBB},
                                {3, FileDBB},
                                {4, FileEBB},
                                {5, FileFBB},
                                {6, FileGBB},
                                {7, FileHBB},
                                {8, FileIBB},
                                {9, FileJBB},
                                {10, FileKBB},
                                {11, FileLBB},
                                {12, FileMBB},
                                {13, FileNBB},
                                {14, FileOBB},
                                {15, FilePBB},
                                {16, FileQBB}
                                };


        static std::map<int, Bitboard> row_map{
                                {0, Rank1BB},
                                {1, Rank2BB},
                                {2, Rank3BB},
                                {3, Rank4BB},
                                {4, Rank5BB},
                                {5, Rank6BB},
                                {6, Rank7BB},
                                {7, Rank8BB},
                                {8, Rank9BB},
                                {9, Rank10BB},
                                {10, Rank11BB},
                                {11, Rank12BB},
                                {12, Rank13BB},
                                {13, Rank14BB},
                                {14, Rank15BB},
                                {15, Rank16BB},
                                {16, Rank17BB}
                                };


        static std::map<int, int> clash_map{
                                {w3, clashw3},
                                {w4, clashw4},
                                {w5, clashw5},
                                {r3, clashr3},
                                {r4, clashr4},
                                {r5, clashr5},
                                {orchid, Nothing},
                                {lotus, Nothing},
                                };
        static std::map<int, int> harm_map{
                                    {w3, harmw3},
                                    {w4, harmw4},
                                    {w5, harmw5},
                                    {r3, harmr3},
                                    {r4, harmr4},
                                    {r5, harmr5},
                                    {lotus, harmlotus},
                                    };



        Bitboard mask_2_move(int square);
        Bitboard mask_3_move(int square);
        Bitboard mask_4_move(int square);
        Bitboard mask_5_move(int square);
        Bitboard mask_6_move(int square);

        void make_move(Board *b, int team, Move m);
        void update_harms_clash(Board *b);
        void update_team_harms(Board *b);
        int check_win(Board *b); //returns WHITE, BLACK or -1
        Bitboard reverse_harm_lookup(Board *b, int harm_index, int team);

        std::string pretty(Bitboard b);
        void init();
        int get_lsb(Bitboard b);
        Moves get_moves(Board *b, int color);

    } //namespace bitboards


} //namespace Paisho

#endif
