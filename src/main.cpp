
#include"Bitboard.h"

void test_print_macros(){

    Paisho::Bitboards::pretty(FileABB);
    Paisho::Bitboards::pretty(FileBBB);
    Paisho::Bitboards::pretty(FileCBB);
    Paisho::Bitboards::pretty(FileDBB);
    Paisho::Bitboards::pretty(FileEBB);
    Paisho::Bitboards::pretty(FileFBB);
    Paisho::Bitboards::pretty(FileGBB);
    Paisho::Bitboards::pretty(FileHBB);
    Paisho::Bitboards::pretty(FileIBB);
    Paisho::Bitboards::pretty(FileJBB);
    Paisho::Bitboards::pretty(FileKBB);
    Paisho::Bitboards::pretty(FileLBB);
    Paisho::Bitboards::pretty(FileMBB);
    Paisho::Bitboards::pretty(FileNBB);
    Paisho::Bitboards::pretty(FileOBB);
    Paisho::Bitboards::pretty(FilePBB);
    Paisho::Bitboards::pretty(FileQBB);

    Paisho::Bitboards::pretty(Rank1BB);
    Paisho::Bitboards::pretty(Rank2BB);
    Paisho::Bitboards::pretty(Rank3BB);
    Paisho::Bitboards::pretty(Rank4BB);
    Paisho::Bitboards::pretty(Rank5BB);
    Paisho::Bitboards::pretty(Rank6BB);
    Paisho::Bitboards::pretty(Rank7BB);
    Paisho::Bitboards::pretty(Rank8BB);
    Paisho::Bitboards::pretty(Rank9BB);
    Paisho::Bitboards::pretty(Rank10BB);
    Paisho::Bitboards::pretty(Rank11BB);
    Paisho::Bitboards::pretty(Rank12BB);
    Paisho::Bitboards::pretty(Rank13BB);
    Paisho::Bitboards::pretty(Rank14BB);
    Paisho::Bitboards::pretty(Rank15BB);
    Paisho::Bitboards::pretty(Rank16BB);
    Paisho::Bitboards::pretty(Rank17BB);
    
    Paisho::Bitboards::pretty(Gates);
    Paisho::Bitboards::pretty(Illegal);
    Paisho::Bitboards::pretty(Legal);


}

void test_board_ops(){
    Paisho::Bitboards::pretty(Rank10BB & FileFBB);


}


int main(){
    test_print_macros();
    //test_board_ops();
    return 1;
}
