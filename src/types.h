
#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED


#define copy_board()                                                      \
    U64 bitboards_copy[33] \
    int side_copy, enpassant_copy, castle_copy;                           \
    memcpy(bitboards_copy, bitboards, sizeof(bitboards));                                \
    side_copy = side, enpassant_copy = enpassant, castle_copy = castle;   \

// restore board state
#define take_back()                                                       \
    memcpy(bitboards, bitboards_copy, 96);                                \
    side = side_copy, enpassant = enpassant_copy, castle = castle_copy;   \

namespace Paisho{


    enum MoveType: int{
        MOVE,
        PLACE,
        HARMPLACE,
        HARMACCENT
    };

    enum BitBoardIndex{
        WhiteW3,WhiteW4,WhiteW5,WhiteR3,WhiteR4,WhiteR5,WhiteLotus,WhiteOrchid,WhiteAccent,
        BlackW3,BlackW4,BlackW5,BlackR3,BlackR4,BlackR5,BlackLotus,BlackOrchid,BlackAccent,
        BlackHarmR3,BlackHarmR4,BlackHarmR5,BlackHarmW3,BlackHarmW4,BlackHarmW5,
        WhiteHarmR3,WhiteHarmR4,WhiteHarmR5,WhiteHarmW3,WhiteHarmW4,WhiteHarmW5,
        AllWhiteFlowers,AllBlackFlowers,BlackAccents,WhiteAccents,AllPieces,
        ClashR3,ClashR4,ClashR5,ClashW3,ClashW4,ClashW5

        
    };

    enum Accent: char{
        Rock1=0b10000000,
        Rock20=0b01000000,
        Knotweed1=0b00100000,
        Knotweed2=0b00010000,
        Wheel1=0b00001000,
        Wheel2=0b00000100,
        Boat1=0b00000010,
        Boat2=0b00000001
    };


    enum Color{
        WHITE,
        BLACK,
        NB
    };

    enum Value: int{
        VAL_DRAW = 0,
        VAL_INF=10000,
        p3Val,
        p4Val,
        p5Val,
        lotusVal,
        orchidVal,
        wildOrchVal,
        harmVal,
        harmThroughMidVal
    };

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

    struct Move{
        enum MoveType move_type;
        enum Squares s1; //This is the square used in a place move, or the source square of a Move
        enum Squares s2; //destination square in move
        enum Piece place_piece; //Used in harmplace move
        enum Accent aux_piece; //accent tile in harm move
        enum Squares s3; //If boat is placed on a flower tile, this will be the destination tile of the moved piece.
    };


    struct Moves{
        Move[1000];
        int move_count;
    }

}//Paisho


#endif
