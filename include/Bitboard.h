
#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <bitset>
#include "types.h"
//using Bitboard = std::bitset<224>;

typedef std::bitset<290> Bitboard;
std::string GetBinaryStringFromHexString (std::string sHex);

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

#define Illegal ((Bitboard("11110000000001111") |\
    (Bitboard("11100000000000111") << Paisho::NORTH) |\
    (Bitboard("11000000000000011") << 2*Paisho::NORTH) |\
    (Bitboard("10000000000000001") << 3*Paisho::NORTH) | \
    (Bitboard("11110000000001111") << 16*Paisho::NORTH) |\
    (Bitboard("11100000000000111") << 15*Paisho::NORTH) |\
    (Bitboard("11000000000000011") << 14*Paisho::NORTH) |\
    (Bitboard("10000000000000001") << 13*Paisho::NORTH)))



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

#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (Bitboard(1) << square) : 0)

namespace Paisho{
    struct Board {

        //save how many are in each hand
        int bw3;
        int bw4;
        int bw5;
        int br3;
        int br4;
        int br5;
        char blackAccents;

        int ww3;
        int ww4;
        int ww5;
        int wr3;
        int wr4;
        int wr5;
        char whiteAccents;

        Bitboard bitboards[41];

        Bitboard HarmLotus;

        Bitboard WhiteHarms;
        Bitboard BlackHarms;

    };

    //Used to initialize all the bitboards
    Board init_board();
    //use one char (8 bits) to pick from {rock1, r2, knot1, knot2, w1, w2, b1, b2}
    
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

        std::string pretty(Bitboard b);
        void init();
        Moves get_moves(Bitboard b);

        Bitboard mask_2_move(enum Squares square);
        Bitboard mask_3_move(enum Squares square);
        Bitboard mask_4_move(enum Squares square);
        Bitboard mask_5_move(enum Squares square);
        Bitboard mask_6_move(enum Squares square);

    } //namespace bitboards


} //namespace Paisho

#endif
