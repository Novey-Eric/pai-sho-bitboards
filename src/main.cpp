
#include"Bitboard.h"
#include <iostream>
#include <ostream>

using namespace std;
using namespace Paisho::Bitboards;
using namespace Paisho;

void test_print_macros(){

    pretty(FileABB);
    pretty(FileBBB);
    pretty(FileCBB);
    pretty(FileDBB);
    pretty(FileEBB);
    pretty(FileFBB);
    pretty(FileGBB);
    pretty(FileHBB);
    pretty(FileIBB);
    pretty(FileJBB);
    pretty(FileKBB);
    pretty(FileLBB);
    pretty(FileMBB);
    pretty(FileNBB);
    pretty(FileOBB);
    pretty(FilePBB);
    pretty(FileQBB);

    pretty(Rank1BB);
    pretty(Rank2BB);
    pretty(Rank3BB);
    pretty(Rank4BB);
    pretty(Rank5BB);
    pretty(Rank6BB);
    pretty(Rank7BB);
    pretty(Rank8BB);
    pretty(Rank9BB);
    pretty(Rank10BB);
    pretty(Rank11BB);
    pretty(Rank12BB);
    pretty(Rank13BB);
    pretty(Rank14BB);
    pretty(Rank15BB);
    pretty(Rank16BB);
    pretty(Rank17BB);
    
    pretty(Gates);
    pretty(Illegal);
    pretty(Legal);
    pretty(Red);
    pretty(White);
    pretty(Neutral);
}

void test_board_ops(){
    pretty(Rank10BB & FileFBB);
    pretty(Rank10BB);
    cout << Rank10BB[f10] << endl;
    //pretty(get_bit(Rank10BB, f10));

    pretty(mask_2_move(q10));
    pretty(mask_3_move(q10));
    pretty(mask_3_move(g16));
    pretty(mask_4_move(i8));
    pretty(mask_4_move(g16));

    pretty(mask_5_move(a8));
    pretty(mask_5_move(b8));
    pretty(mask_5_move(c8));
    pretty(mask_5_move(d8));
    pretty(mask_5_move(e8));

    pretty(mask_5_move(q8));
    pretty(mask_5_move(p8));
    pretty(mask_5_move(o8));
    pretty(mask_5_move(m8));
    pretty(mask_5_move(n8));

    pretty(mask_5_move(i8));
    pretty(mask_6_move(i8));
}


int main(){
    //test_print_macros();
    test_board_ops();
    return 1;
}
