
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
    std::string Bitboards::pretty(Bitboard b){


        std::cout << "        ";
        for (int i = 276; i <= 284; i++){
            std::cout << " " << b[i];
        }
        std::cout << "        " << std::endl;;

        std::cout << "      ";
        for (int i = 258; i <= 268; i++){
            std::cout << " " << b[i];
        }
        std::cout << "      " << std::endl;;


        std::cout << "    ";
        for (int i = 240; i <= 252; i++){
            std::cout << " " << b[i];
        }
        std::cout << "    " << std::endl;;


        std::cout << "  ";
        for (int i = 222; i <= 236; i++){
            std::cout << " " << b[i];
        }
        std::cout << "  " << std::endl;;


        for (int j = 8; j >=0; j--){
            for (int i = 68 + j*17; i < 85 + j*17; i++){
                std::cout << " " << b[i];
            }
            std::cout << std::endl;
        }


        std::cout << "  ";
        for (int i = 52; i <= 66; i++){
            std::cout << " " << b[i];
        }
        std::cout << "  " << std::endl;;

        std::cout << "    ";
        for (int i = 36; i <= 48; i++){
            std::cout << " " << b[i];
        }
        std::cout << "    " << std::endl;;


        std::cout << "      ";
        for (int i = 20; i <= 30; i++){
            std::cout << " " << b[i];
        }
        std::cout << "      " << std::endl;;


        std::cout << "        ";
        for (int i = 4; i <= 12; i++){
            std::cout << " " << b[i];
        }
        std::cout << "        " << std::endl << std::endl;


        return "hello";
    }

    namespace Bitboards{

        void init(){
            return;
        }

        Bitboard mask_2_move(enum Squares square){
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


        Bitboard mask_3_move(enum Squares square){
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
                    ) & ~Gates;
            return moves;
        } 



        Bitboard mask_4_move(enum Squares square){
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
                    nnww|nnee|ssee|ssww) & ~Gates;
            return moves;
        } 



        Bitboard mask_5_move(enum Squares square){
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
                    ) & ~Gates;
            return moves;
        } 

        Bitboard mask_6_move(enum Squares square){
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
                    ) & ~Gates;
            return moves;
        }

    }//namespace bitboards

}
