
#include"Bitboard.h"
#include <iostream>
#include <ostream>
#include <strings.h>

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
    pretty(mask_6_move(q8));
}


void test_lsb(){
    int square = p8;
    Bitboard test = mask_2_move(p10);
    pretty(test);
    cout << get_lsb(test) << " "<< square << endl;

    Bitboard t2(0);
    cout << get_lsb(t2) << endl;

}

void test_gen_moves(){
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    pretty(w3b);
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    pretty(w3h);
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    b.whiteBoards[allflowers] = w3b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w3h;

    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    
    Moves a = get_moves(b, WHITE);
    cout<<"move count "<< a.move_count<<endl;
    cout<<"first move in hex: " << std::hex << a.movelist[0] << endl;
    print_move(a.movelist[0]);
    cout << endl;
    print_move_list(a);

}

void test_make_move(){
    


}



int main(){
    //test_print_macros();
    //test_board_ops();
    //test_lsb();
    test_gen_moves();
    return 1;
}
