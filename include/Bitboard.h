
#ifndef BITBOARD_H_INCLUDED
#define BITBOARD_H_INCLUDED

#include <bitset>
#include "types.h"
#include <map>
//using Bitboard = std::bitset<224>;
#define NORTH (17)
#define SOUTH (-17)
#define EAST (1)
#define WEST (-1)

std::string GetBinaryStringFromHexString (std::string sHex);

const int NUM_SQUARES = 290;
const Bitboard FullFile = (Bitboard(GetBinaryStringFromHexString("100008000400020001000080004000200010000800040002000100008000400020001")));


const Bitboard Illegal = (Bitboard("11110000000001111") |\
    (Bitboard("11100000000000111") << NORTH) |\
    (Bitboard("11000000000000011") << 2*NORTH) |\
    (Bitboard("10000000000000001") << 3*NORTH) | \
    (Bitboard("11110000000001111") << 16*NORTH) |\
    (Bitboard("11100000000000111") << 15*NORTH) |\
    (Bitboard("11000000000000011") << 14*NORTH) |\
    (Bitboard("10000000000000001") << 13*NORTH));
const Bitboard Legal = ~Illegal;


const Bitboard FileABB = ((FullFile) & Legal);
const Bitboard FileBBB = ((FullFile << 1) & Legal);
const Bitboard FileCBB = ((FullFile << 2) & Legal);
const Bitboard FileDBB = ((FullFile << 3) & Legal);
const Bitboard FileEBB = ((FullFile << 4) & Legal);
const Bitboard FileFBB = ((FullFile << 5) & Legal);
const Bitboard FileGBB = ((FullFile << 6) & Legal);
const Bitboard FileHBB = ((FullFile << 7) & Legal);
const Bitboard FileIBB = ((FullFile << 8) & Legal);
const Bitboard FileJBB = ((FullFile << 9) & Legal);
const Bitboard FileKBB = ((FullFile << 10) & Legal);
const Bitboard FileLBB = ((FullFile << 11) & Legal);
const Bitboard FileMBB = ((FullFile << 12) & Legal);
const Bitboard FileNBB = ((FullFile << 13) & Legal);
const Bitboard FileOBB = ((FullFile << 14) & Legal);
const Bitboard FilePBB = ((FullFile << 15) & Legal);
const Bitboard FileQBB = ((FullFile << 16) & Legal);

const Bitboard FullRank = (Bitboard(GetBinaryStringFromHexString("ffff")+"1"));

const Bitboard Rank1BB = (FullRank & Legal);
const Bitboard Rank2BB = ((FullRank << (17 * 1)) & Legal);
const Bitboard Rank3BB = ((FullRank << (17 * 2)) & Legal);
const Bitboard Rank4BB = ((FullRank << (17 * 3)) & Legal);
const Bitboard Rank5BB = ((FullRank << (17 * 4)) & Legal);
const Bitboard Rank6BB = ((FullRank << (17 * 5)) & Legal);
const Bitboard Rank7BB = ((FullRank << (17 * 6)) & Legal);
const Bitboard Rank8BB = ((FullRank << (17 * 7)) & Legal);
const Bitboard Rank9BB = ((FullRank << (17 * 8)) & Legal);
const Bitboard Rank10BB = ((FullRank << (17 * 9)) & Legal);
const Bitboard Rank11BB = ((FullRank << (17 * 10)) & Legal);
const Bitboard Rank12BB = ((FullRank << (17 * 11)) & Legal);
const Bitboard Rank13BB = ((FullRank << (17 * 12)) & Legal);
const Bitboard Rank14BB = ((FullRank << (17 * 13)) & Legal);
const Bitboard Rank15BB = ((FullRank << (17 * 14)) & Legal);
const Bitboard Rank16BB = ((FullRank << (17 * 15)) & Legal);
const Bitboard Rank17BB = ((FullRank << (17 * 16)) & Legal);

const Bitboard Gates = ((Bitboard(1)<<Paisho::i1) | (Bitboard(1)<<Paisho::i17) | (Bitboard(1)<<Paisho::a9) | (Bitboard(1)<<Paisho::q9));

const Bitboard Red = ((Bitboard("11111") << (7*NORTH + 3*EAST)) |\
    (Bitboard("11111") << (9*NORTH + 9*EAST)) |\
    (Bitboard("1111") << (6*NORTH + 4*EAST)) |\
    (Bitboard("1111") << (10*NORTH + 9*EAST)) |\
    (Bitboard("111") << (5*NORTH + 5*EAST)) |\
    (Bitboard("111") << (11*NORTH + 9*EAST)) |\
    (Bitboard("11") << (4*NORTH + 6*EAST)) |\
    (Bitboard("11") << (12*NORTH + 9*EAST)) |\
    (Bitboard("1") << (3*NORTH + 7*EAST)) |\
    (Bitboard("1") << (13*NORTH + 9*EAST)));

const Bitboard White = ((Bitboard("11111") << (7*NORTH + 9*EAST)) |\
    (Bitboard("11111") << (9*NORTH + 3*EAST)) |\
    (Bitboard("1111") << (6*NORTH + 9*EAST)) |\
    (Bitboard("1111") << (10*NORTH + 4*EAST)) |\
    (Bitboard("111") << (5*NORTH + 9*EAST)) |\
    (Bitboard("111") << (11*NORTH + 5*EAST)) |\
    (Bitboard("11") << (4*NORTH + 9*EAST)) |\
    (Bitboard("11") << (12*NORTH + 6*EAST)) |\
    (Bitboard("1") << (3*NORTH + 9*EAST)) |\
    (Bitboard("1") << (13*NORTH + 7*EAST)));

const Bitboard Neutral = (Legal^Red^White^Gates);

namespace Paisho{
    //Used to initialize all the bitboards
    Board init_board();
    void print_move(Move m);
    void print_move_list(Moves ml);
    //use one char (8 bits) to pick from {rock1, r2, knot1, knot2, w1, w2, b1, b2}
    typedef Bitboard (*mask_ptr)(int);


    namespace Bitboards{
        
        constexpr Bitboard correct_color(int piece){
            switch(piece){
                case w3: return White | Neutral;
                case w4: return White | Neutral;
                case w5: return White | Neutral;
                case r3: return Red | Neutral;
                case r4: return Red | Neutral;
                case r5: return Red | Neutral;
                case orchid: return Legal;
                case lotus: return Legal;
            }
        }

        Bitboard mask_2_move(int square);
        Bitboard mask_3_move(int square);
        Bitboard mask_4_move(int square);
        Bitboard mask_5_move(int square);
        Bitboard mask_6_move(int square);

        constexpr mask_ptr mask_move_map(int piece){
            switch(piece){
                case w3: return &mask_3_move;
                case w4: return &mask_4_move;
                case w5: return &mask_5_move;
                case r3: return &mask_3_move;
                case r4: return &mask_4_move;
                case r5: return &mask_5_move;
                case orchid: return &mask_6_move;
                case lotus: return &mask_2_move;
            }
        }


        const Bitboard col_map[] = {
                            FileABB,
                            FileBBB,
                            FileCBB,
                            FileDBB,
                            FileEBB,
                            FileFBB,
                            FileGBB,
                            FileHBB,
                            FileIBB,
                            FileJBB,
                            FileKBB,
                            FileLBB,
                            FileMBB,
                            FileNBB,
                            FileOBB,
                            FilePBB,
                            FileQBB
                            };

        const Bitboard row_map[] = {
                            Rank1BB,
                            Rank2BB,
                            Rank3BB,
                            Rank4BB,
                            Rank5BB,
                            Rank6BB,
                            Rank7BB,
                            Rank8BB,
                            Rank9BB,
                            Rank10BB,
                            Rank11BB,
                            Rank12BB,
                            Rank13BB,
                            Rank14BB,
                            Rank15BB,
                            Rank16BB,
                            Rank17BB
                            };

/*
        constexpr int clash_map(int piece){
            switch(piece){
                case w4: return clashw3;
                case w4: return clashw4;
                case w5: return clashw5;
                case r3: return clashr3;
                case r4: return clashr4;
                case r5: return clashr5;
                default: return -1;
            }
        }
*/
        constexpr int harm_map(int piece){
            switch(piece){
                case w3: return harmw3;
                case w4: return harmw4;
                case w5: return harmw5;
                case r3: return harmr3;
                case r4: return harmr4;
                case r5: return harmr5;
                default: return -1;
            }
        }



        void make_move(Board *b, int team, Move m);
        void update_harms_clash(Board *b);
        void update_team_harms(Board *b);
        int check_win(Board *b); //returns WHITE, BLACK or -1
        Bitboard reverse_harm_lookup(Board *b, int harm_index, int team);

        std::string pretty(Bitboard b);
        int get_lsb(Bitboard b);
        Moves get_moves(Board *b, int color);

    } //namespace bitboards
} //namespace Paisho

#endif
