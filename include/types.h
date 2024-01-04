
#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <unordered_map>
#include <array>
#include <vector>
#include <deque>
#include <list>

#define NUM_OTHER_BOARDS (15)
#define NUM_BOARDS (16)
typedef std::bitset<290> Bitboard;
using std::array;
namespace Paisho{

    typedef struct {
        //save how many are in each hand
        int bw3;
        int bw4;
        int bw5;
        int br3;
        int br4;
        int br5;
        bool bo;
        bool bl;
        bool bwild;
        char blackAccents;

        int ww3;
        int ww4;
        int ww5;
        int wr3;
        int wr4;
        int wr5;
        bool wo;
        bool wl;
        bool wwild;
        char whiteAccents;
    
        std::unordered_map<int,int> white_harm_pairs;
        std::unordered_map<int,int> black_harm_pairs;

        array<Bitboard, NUM_BOARDS> whiteBoards;
        array<Bitboard, NUM_BOARDS> blackBoards;
        //Bitboard whiteBoards[NUM_BOARDS];
        //Bitboard blackBoards[NUM_BOARDS];
        //Bitboard bitboards[41];

        array<Bitboard, NUM_OTHER_BOARDS> otherBoards;
        //Bitboard otherBoards[NUM_OTHER_BOARDS];
        //Bitboard HarmLotus;

    } Board;

    enum OtherBoards: int{
        Accents,Rocks,Knotweeds,
        AllPieces,Nothing
    };

    enum MoveType: int{
        MOVE,
        PLACE,
        HARMPLACE,
        HARMACCENT
    };

    // Note: Clash<piece> means that if <piece> moves onto this spot, it will clash with something else on the row/column
    // BUT: Harm<piece> means there is a <piece> on this row/column and you have to check to see if the landing piece harmonizes with it

    enum Boards{
        w3,w4,w5,r3,r4,r5,lotus,orchid,harmr3,harmr4,harmr5,harmw3,harmw4,harmw5,harmlotus,
        allflowers
    };
    //Set these like 1<<Rock or something
    enum Accent: int{
        Rock,
        Rock2,
        Knotweed,
        Knotweed2,
        Wheel,
        Wheel2,
        Boat,
        Boat2,
    };

    const std::string AccentStrings[] = {"R", "R", "K", "K", "W", "W", "B", "B"};

    enum Team{
        WHITE,
        BLACK,
        NB
    };
    
    enum Color{
        WHITEFLOWER,
        REDFLOWER
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

    const std::string SquareStrings[] = {
        "A1","B1","C1","D1","E1","F1","G1","H1","I1","J1","K1","L1","M1","N1","O1","P1","Q1",
        "A2","B2","C2","D2","E2","F2","G2","H2","I2","J2","K2","L2","M2","N2","O2","P2","Q2",
        "A3","B3","C3","D3","E3","F3","G3","H3","I3","J3","K3","L3","M3","N3","O3","P3","Q3",
        "A4","B4","C4","D4","E4","F4","G4","H4","I4","J4","K4","L4","M4","N4","O4","P4","Q4",
        "A5","B5","C5","D5","E5","F5","G5","H5","I5","J5","K5","L5","M5","N5","O5","P5","Q5",
        "A6","B6","C6","D6","E6","F6","G6","H6","I6","J6","K6","L6","M6","N6","O6","P6","Q6",
        "A7","B7","C7","D7","E7","F7","G7","H7","I7","J7","K7","L7","M7","N7","O7","P7","Q7",
        "A8","B8","C8","D8","E8","F8","G8","H8","I8","J8","K8","L8","M8","N8","O8","P8","Q8",
        "A9","B9","C9","D9","E9","F9","G9","H9","I9","J9","K9","L9","M9","N9","O9","P9","Q9",
        "A10","B10","C10","D10","E10","F10","G10","H10","I10","J10","K10","L10","M10","N10","O10","P10","Q10",
        "A11","B11","C11","D11","E11","F11","G11","H11","I11","J11","K11","L11","M11","N11","O11","P11","Q11",
        "A12","B12","C12","D12","E12","F12","G12","H12","I12","J12","K12","L12","M12","N12","O12","P12","Q12",
        "A13","B13","C13","D13","E13","F13","G13","H13","I13","J13","K13","L13","M13","N13","O13","P13","Q13",
        "A14","B14","C14","D14","E14","F14","G14","H14","I14","J14","K14","L14","M14","N14","O14","P14","Q14",
        "A15","B15","C15","D15","E15","F15","G15","H15","I15","J15","K15","L15","M15","N15","O15","P15","Q15",
        "A16","B16","C16","D16","E16","F16","G16","H16","I16","J16","K16","L16","M16","N16","O16","P16","Q16",
        "A17","B17","C17","D17","E17","F17","G17","H17","I17","J17","K17","L17","M17","N17","O17","P17","Q17"
    };    

    const std::string PieceStrings[] = {"w3", "w4", "w5", "r3", "r4", "r5", "l", "o"};

    // {move_type: 3 bits}, {capture: 1 bit}, {s1: 9 bits}, {s2: 9 bits},
    // {Piece: 3 bits}, {aux_piece: 3 bits}, {s3: 9 bits}, {s4: 9 bits}, {boatmove: 1 bit}
    // Total 47 bits
    #define MOVE_TYPE_OFFSET (0)
    #define MOVE_CAPTURE_OFFSET (3)
    #define MOVE_S1_OFFSET (4)
    #define MOVE_S2_OFFSET (13)
    #define MOVE_PIECE_OFFSET (22)
    #define MOVE_AUXPIECE_OFFSET (25)
    //Here you need to start using uint64_t
    #define MOVE_S3_OFFSET (28)
    #define MOVE_S4_OFFSET (37)
    #define MOVE_BOATMOVE_OFFSET (46)

    constexpr uint64_t MOVE_TYPE_MASK = (((uint64_t) 0b111));
    constexpr uint64_t MOVE_CAPTURE_MASK = (((uint64_t) 0b1) << MOVE_CAPTURE_OFFSET);
    constexpr uint64_t MOVE_S1_MASK = (((uint64_t) 0b111111111) << MOVE_S1_OFFSET);
    constexpr uint64_t MOVE_S2_MASK = (((uint64_t) 0b111111111) << MOVE_S2_OFFSET);
    constexpr uint64_t MOVE_PIECE_MASK = (((uint64_t) 0b111) << MOVE_PIECE_OFFSET);
    constexpr uint64_t MOVE_AUXPIECE_MASK = (((uint64_t) 0b111) << MOVE_AUXPIECE_OFFSET);
    constexpr uint64_t MOVE_S3_MASK = (((uint64_t) 0b111111111) << MOVE_S3_OFFSET);
    constexpr uint64_t MOVE_S4_MASK = (((uint64_t) 0b111111111) << MOVE_S4_OFFSET);
    constexpr uint64_t MOVE_BOATMOVE_MASK = (((uint64_t) 0b1) << MOVE_BOATMOVE_OFFSET);
    typedef uint64_t Move;

    typedef std::deque<Move> Moves;
  //  #define MOVELIST_LEN (8000)
/*
    typedef struct {
        Move movelist[MOVELIST_LEN];
        int move_count;
    } Moves;
*/
}//Paisho


#endif
