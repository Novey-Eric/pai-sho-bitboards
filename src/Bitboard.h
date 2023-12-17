
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

#define Gates ((Bitboard(1)<<Paisho::Bitboards::i1) | (Bitboard(1)<<Paisho::Bitboards::i17) | (Bitboard(1)<<Paisho::Bitboards::a9) | (Bitboard(1)<<Paisho::Bitboards::q9))

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

#define get_bit(bitboard, square) (bitboard & (Bitboard(1) << square))


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

        enum Squares: int{
            a1,b1,c1,d1,e1,f1,g1,h1,i1,j1,k1,l1,m1,n1,o1,p1,q1,
            a2,b2,c2,d2,e2,f2,g2,h2,i2,j2,k2,l2,m2,n2,o2,p2,q2,
            a3,b3,c3,d3,e3,f3,g3,h3,i3,j3,k3,l3,m3,n3,o3,p3,q3,
            a4,b4,c4,d4,e4,f4,g4,h4,i4,j4,k4,l4,m4,n4,o4,p4,q4,
            a5,b5,c5,d5,e5,f5,g5,h5,i5,j5,k5,l5,m5,n5,o5,p5,q5,
            a6,b6,c6,d6,e6,f6,g6,h6,i6,j6,k6,l6,m6,n6,o6,p6,q6,
            a7,b7,c7,d7,e7,f7,g7,h7,i7,j7,k7,l7,m7,n7,o7,p7,q7,
            a8,b8,c8,d8,e8,f8,g8,h8,i8,j8,k8,l8,m8,n8,o8,p8,q8,
            a9,b9,c9,d9,e9,f9,g9,h9,i9,j9,k9,l9,m9,n9,o9,p9,q9,
            a10,b10,c10,d10,e10,f10,g10,h10,i10,j10,k10,l10,m10,n10,o10,p10,q10,
            a11,b11,c11,d11,e11,f11,g11,h11,i11,j11,k11,l11,m11,n11,o11,p11,q11,
            a12,b12,c12,d12,e12,f12,g12,h12,i12,j12,k12,l12,m12,n12,o12,p12,q12,
            a13,b13,c13,d13,e13,f13,g13,h13,i13,j13,k13,l13,m13,n13,o13,p13,q13,
            a14,b14,c14,d14,e14,f14,g14,h14,i14,j14,k14,l14,m14,n14,o14,p14,q14,
            a15,b15,c15,d15,e15,f15,g15,h15,i15,j15,k15,l15,m15,n15,o15,p15,q15,
            a16,b16,c16,d16,e16,f16,g16,h16,i16,j16,k16,l16,m16,n16,o16,p16,q16,
            a17,b17,c17,d17,e17,f17,g17,h17,i17,j17,k17,l17,m17,n17,o17,p17,q17,
        };

        std::string pretty(Bitboard b);
        void init();


    } //namespace bitboards


} //namespace Paisho

#endif
