
#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <bitset>
//using Bitboard = std::bitset<224>;

typedef std::bitset<290> Bitboard;
std::string GetBinaryStringFromHexString (std::string sHex);


#define FileABB Bitboard(GetBinaryStringFromHexString("100008000400020001000080004000200010000800040002000100008000400020001"))
#define FileBBB FileABB << 1
#define FileCBB FileABB << 2
#define FileDBB FileABB << 3
#define FileEBB FileABB << 4
#define FileFBB FileABB << 5
#define FileGBB FileABB << 6
#define FileHBB FileABB << 7
#define FileIBB FileABB << 8
#define FileJBB FileABB << 9
#define FileKBB FileABB << 10
#define FileLBB FileABB << 11
#define FileMBB FileABB << 12
#define FileNBB FileABB << 13
#define FileOBB FileABB << 14
#define FilePBB FileABB << 15
#define FileQBB FileABB << 16

#define Rank1BB Bitboard(GetBinaryStringFromHexString("ffff")+"1")
#define Rank2BB Rank1BB << (17 * 1)
#define Rank3BB Rank1BB << (17 * 2)
#define Rank4BB Rank1BB << (17 * 3)
#define Rank5BB Rank1BB << (17 * 4)
#define Rank6BB Rank1BB << (17 * 5)
#define Rank7BB Rank1BB << (17 * 6)
#define Rank8BB Rank1BB << (17 * 7)
#define Rank9BB Rank1BB << (17 * 8)
#define Rank10BB Rank1BB << (17 * 9)
#define Rank11BB Rank1BB << (17 * 10)
#define Rank12BB Rank1BB << (17 * 11)
#define Rank13BB Rank1BB << (17 * 12)
#define Rank14BB Rank1BB << (17 * 13)
#define Rank15BB Rank1BB << (17 * 14)
#define Rank16BB Rank1BB << (17 * 15)
#define Rank17BB Rank1BB << (17 * 16)



namespace Paisho{
    struct Board {
        Bitboard AllWhitePieces;
        Bitboard AllBlackPieces;
        Bitboard AllPieces;

        Bitboard BlackW3;
        Bitboard BlackW4;
        Bitboard BlackW5;
        Bitboard BlackR3;
        Bitboard BlackR4;
        Bitboard BlackR5;
        Bitboard BlackAccent;
        Bitboard BlackOrchid;
        Bitboard BlackLotus;

        Bitboard WhiteW3;
        Bitboard WhiteW4;
        Bitboard WhiteW5;
        Bitboard WhiteR3;
        Bitboard WhiteR4;
        Bitboard WhiteR5;
        Bitboard WhiteAccent;
        Bitboard WhiteOrchid;
        Bitboard WhiteLotus;

    };

    enum Direction: int{
        NORTH = 16,
        EAST = 1,
        SOUTH = -NORTH,
        WEST = -EAST,

        NORTH_EAST = NORTH + EAST,
        NORTH_WEST = NORTH + WEST,
        SOUTH_EAST = SOUTH + EAST,
        SOUTH_WEST = SOUTH + WEST,
    };

    namespace Bitboards{
/*
        constexpr Bitboard FileABB("0001000100010001000100010001000100010001000100010001000100010001");
        Bitboard FileBBB = FileABB << 1;
        Bitboard FileCBB = FileABB << 2;
        Bitboard FileDBB = FileABB << 3;
        Bitboard FileEBB = FileABB << 4;
        Bitboard FileFBB = FileABB << 5;
        Bitboard FileGBB = FileABB << 6;
        Bitboard FileHBB = FileABB << 7;
        Bitboard FileIBB = FileABB << 8;
        Bitboard FileJBB = FileABB << 9;
        Bitboard FileKBB = FileABB << 10;
        Bitboard FileLBB = FileABB << 11;
        Bitboard FileMBB = FileABB << 12;
        Bitboard FileNBB = FileABB << 13;
        Bitboard FileOBB = FileABB << 14;
        Bitboard FilePBB = FileABB << 15;
        Bitboard FileQBB = FileABB << 16;

        Bitboard Rank1BB(0xFFFF);
        Bitboard Rank2BB = Rank1BB << (8 * 1);
        Bitboard Rank3BB = Rank1BB << (8 * 2);
        Bitboard Rank4BB = Rank1BB << (8 * 3);
        Bitboard Rank5BB = Rank1BB << (8 * 4);
        Bitboard Rank6BB = Rank1BB << (8 * 5);
        Bitboard Rank7BB = Rank1BB << (8 * 6);
        Bitboard Rank8BB = Rank1BB << (8 * 7);
        Bitboard Rank9BB = Rank1BB << (8 * 8);
        Bitboard Rank10BB = Rank1BB << (8 * 9);
        Bitboard Rank11BB = Rank1BB << (8 * 10);
        Bitboard Rank12BB = Rank1BB << (8 * 11);
        Bitboard Rank13BB = Rank1BB << (8 * 12);
        Bitboard Rank14BB = Rank1BB << (8 * 13);
        Bitboard Rank15BB = Rank1BB << (8 * 14);
        Bitboard Rank16BB = Rank1BB << (8 * 15);
*/
        std::string pretty(Bitboard b);
        void init();


    } //namespace bitboards


} //namespace Paisho

#endif
