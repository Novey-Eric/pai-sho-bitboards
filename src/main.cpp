
#include <iostream>
#include <ostream>
#include <strings.h>
#include"Computer.h"
#include"types.h"
#include"Bitboard.h"
#include <chrono>
#include <vector>
using namespace std::chrono;
using std::cout;
using std::endl;
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
    cout<<"move count "<< a.size()<<endl;
    cout<<"first move in hex: " << std::hex << a[0] << endl;
    print_move(a[0]);
    cout << std::dec<<endl;
    print_move_list(a);
        
    cout<<"WEST "<<endl;
    pretty(w3b);
    pretty(w3b<<NORTH);

}

void test_wheel(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    b.whiteBoards[allflowers] = w3b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b;
    b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;

    b.ww3=2;
    b.ww4=1;
    b.ww5=3;

    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    pretty(b.otherBoards[AllPieces]);
    cout<<"making move"<<endl;
    make_move(b, WHITE, a[125]);
    pretty(b.otherBoards[AllPieces]);

}
void test_wheel2(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    b.whiteBoards[allflowers] = w3b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b;
    b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;

    b.ww3=2;
    b.ww4=1;
    b.ww5=3;

    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    pretty(b.otherBoards[AllPieces]);
    cout<<"making move"<<endl;
    make_move(b, WHITE, a[125]);
    pretty(b.otherBoards[AllPieces]);

}

void test_boat(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    b.whiteBoards[allflowers] = w3b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b;
    b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;

    b.ww3=2;
    b.ww4=1;
    b.ww5=3;

    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    pretty(b.otherBoards[AllPieces]);
    cout<<"making move"<<endl;
    make_move(b, WHITE, a[159]);
    pretty(b.otherBoards[AllPieces]);

}


void test_harm_clashes(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    b.whiteBoards[allflowers] = w3b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b;
    b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;

    b.ww3=2;
    b.ww4=1;
    b.ww5=3;

    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    //pretty(b.otherBoards[AllPieces]);
    cout<<"making move"<<endl;
    pretty(b.whiteBoards[harmw3]);
    make_move(b, WHITE, a[159]);
    //pretty(b.otherBoards[AllPieces]);
    cout<<"PRINTING ALL white FLOWERS"<<endl;
    pretty(b.whiteBoards[allflowers]);
    cout<<"printing all pieces"<<endl;
    pretty(b.otherBoards[AllPieces]);
    cout<<"printing harmw3"<<endl;
    pretty(b.whiteBoards[harmw3]);
    cout<<"printing clashr3"<<endl;
    //pretty(b.otherBoards[clashr3]);
    //cout<<evaluate(b)<<endl;

}


void test_total_harms(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;

    Paisho::Bitboards::update_harms_clash(b);
    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    //pretty(b.otherBoards[AllPieces]);

    cout<<"making move"<<endl;
    make_move(b, WHITE, a[2298]);
    Move tm = a[2298];
    cout<< ((tm & MOVE_PIECE_MASK)>>MOVE_PIECE_OFFSET) << endl;
    cout<< w3<< endl;
    cout<<"printing w3 "<< endl;
    pretty(b.whiteBoards[w3]);
    cout<<"printing harmw3 "<< endl;
    pretty(b.whiteBoards[harmw3]);
    cout<<"printing w4 "<< endl;
    pretty(b.whiteBoards[w4]);
    cout<<"printing harmw4 "<< endl;
    pretty(b.whiteBoards[harmw4]);
    //pretty(b.otherBoards[AllPieces]);
    cout<<"PRINTING ALL white FLOWERS"<<endl;
    pretty(b.whiteBoards[allflowers]);
    cout<<"all tiles"<<endl;
    pretty(b.otherBoards[AllPieces]);
    cout<<evaluate(b)<<endl;
    
}


void test_abprune(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    update_harms_clash(b);
    Moves a = get_moves(b, WHITE);
    make_move(b, WHITE, a[1353]);
    Move bestmove;
    print_board(b);
    int eval = prune_helper(b, 3, WHITE, bestmove);
    cout<< "eval: " << eval << " found move: ";
    print_move(bestmove);


}

/*
void test_minimax(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;

    update_harms_clash(b);
    Moves a = get_moves(b, WHITE);
    //print_move_list(a);
    cout<<"move count "<< a.size()<<endl;
    //pretty(b.otherBoards[AllPieces]);

    cout<<"making move"<<endl;
    make_move(b, WHITE, a[1353]);
    Move bestmove;
    auto start = high_resolution_clock::now();
    Move t = minimax(b, 2, WHITE, bestmove);
    auto after_mm = high_resolution_clock::now();
    auto duration_mm = duration_cast<microseconds>(after_mm-start);
    cout << "minimax duration: " << duration_mm.count() << endl;

    Move t2 = negamax(b, 2, WHITE, bestmove);
    auto after_nm = high_resolution_clock::now();
    auto duration_nm = duration_cast<microseconds>(after_nm-after_mm);
    cout << "negamax duration: " << duration_nm.count() << endl;
}

*/
void test_move_types(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.wo=true;

    update_harms_clash(b);
    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    pretty(b.otherBoards[AllPieces]);

    cout<<"harm w3 before"<<endl;
    pretty(b.whiteBoards[harmw3]);
    cout<<"making move K9-I10+B I10-H10"<<endl;
    make_move(b, WHITE, a[2902]);
    //2806: K9-I10+B I10-H10
    
    cout<<"all tiles"<<endl;
    pretty(b.otherBoards[AllPieces]);

    Moves c = get_moves(b, WHITE);
    //print_move_list(c);
    make_move(b, WHITE, c[10]);
    pretty(b.otherBoards[AllPieces]);
    
    
}

void comp_v_comp(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=3;
    b.bw4=3;
    b.bw5=3;
    b.bl=1;
    b.bo=1;

    std::vector<Move> moves;

    int player = BLACK;
    update_harms_clash(b);
    while(evaluate(b) < 999999){
        Move bestmove;
        //pretty(b.otherBoards[AllPieces]);
        print_board(b);
        std::cout<<"num moves: "<<get_moves(b, player).size() << std::endl;
        //int eval = ab_prune(b, 2, -9999999, 9999999, player, bestmove);
        int eval = prune_helper(b, 2, player, bestmove);
        cout<< "eval: " << eval << " found move: ";
        moves.push_back(bestmove);
        print_move(bestmove);
        make_move(b, player, bestmove);
        cout<< "moves list: ";
        for (Move move: moves){
            cout<<move<<", ";
        }
        cout << endl;
        cout<< "black harms: ";
        for (auto it : b.black_harm_pairs){
            cout<< "("<<SquareStrings[it.first] << ", "<<SquareStrings[it.second]<<"), ";
        }
        cout<<endl;
        //player = player==WHITE ? BLACK : WHITE;
    }
    print_board(b);
}




void test_fail1(){
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) ;//| (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i9;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;

    //update_harms_clash(b);
    Moves a = get_moves(b, WHITE);
    //print_move_list(a);
    print_move(a[57]);
    make_move(b, WHITE, a[57]);
    pretty(b.whiteBoards[allflowers]);
    
    Move bestmove;
    //Moves a = get_moves(b, WHITE);
    //print_move_list(a);

    auto start = high_resolution_clock::now();
    //int eval = ab_prune(b, 3, -99999, 99999, WHITE, bestmove);
    int eval = prune_helper(b, 3, WHITE, bestmove);
    auto after_mm = high_resolution_clock::now();
    auto duration_mm = duration_cast<microseconds>(after_mm-start);
    cout << "prune duration: " << duration_mm.count() << endl;

    cout<<"eval for white: "<< eval<<endl;
    print_move(bestmove);
    cout<<"before making move allpieces"<<endl;
    pretty(b.otherBoards[AllPieces]);
    //pretty(b.whiteBoards[w3]);
    //pretty(b.whiteBoards[w4]);
    make_move(b, WHITE, bestmove);
    bestmove = 0;
    pretty(b.otherBoards[AllPieces]);

}

void test_fail2(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;

    update_harms_clash(b);
    pretty(b.otherBoards[AllPieces]);
    make_move(b, WHITE, 5369873843);
    pretty(b.otherBoards[AllPieces]);
    make_move(b, WHITE, 2152458530);
    pretty(b.otherBoards[AllPieces]);
    make_move(b, WHITE, 36511465602);
    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    print_board(b);
    
}

void test_fail3(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;
    b.bo=1;
    b.wo=1;
    b.wl=1;

    update_harms_clash(b);
    make_move(b, WHITE, 5369873843);
    make_move(b, WHITE, 2152458530);
    make_move(b, WHITE, 36511465602);
    Moves a = get_moves(b, WHITE);
    make_move(b, WHITE, 4661344);
    make_move(b, WHITE, 1583328);
    make_move(b, WHITE, 493008);
    make_move(b, WHITE, 5383664);
    make_move(b, WHITE, 5794064);
    make_move(b, WHITE, 6220848);
    make_move(b, WHITE, 2001936);
    print_board(b);
    make_move(b, WHITE, 75368211346);

    a = get_moves(b, WHITE);
    //print_move_list(a);
    print_move(75368211346);
    //cout<<a[1044]<<endl;
    print_board(b);
    cout<<evaluate(b)<<endl;
    for (auto it : b.white_harm_pairs){
        cout<< "("<<SquareStrings[it.first] << ", "<<SquareStrings[it.second]<<"), ";
    }
    cout<<"\n";
    
    
}


void test_fail4(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;
    b.bo=1;
    b.wo=1;
    b.wl=1;

    update_harms_clash(b);
    std::array<Move,12> moves = {8388737, 8390785, 9545856, 8390785, 4196737, 4198785, 5409152, 41008892226, 26265984, 41043399042, 30558600, 30124328};
    for(Move m : moves){
        print_move(m);
        make_move(b, BLACK, m);
        print_board(b);
    }
    
}



void test_print_board(){
    
    Bitboard w3b(1);
    w3b <<= i6;
    w3b |= Bitboard(1)<<i8;
    w3b |= Bitboard(1)<<g6;
    Board b={0};
    b.whiteAccents = (1<<Rock) | (1<<Knotweed) | (1<<Wheel) | (1<<Boat);

    Bitboard w3h(1);
    w3h <<= i10;
    b.whiteBoards[harmw4] = w3h;

    b.whiteBoards[w3]=w3b;
    Bitboard w4b = Bitboard(1)<<k9;
    b.whiteBoards[w4]=w4b;
    b.whiteBoards[allflowers] = w3b | w4b;

    Bitboard waccent(1);
    waccent <<= e3;
    b.otherBoards[Accents]=waccent;

    b.otherBoards[AllPieces]= waccent | w3b | w4b;
    //b.otherBoards[AllPieces] |= (Bitboard(1)<<h5)<<EAST;
    
    b.ww3=2;
    b.ww4=1;
    b.ww5=3;
    b.bw3=2;
    b.bw4=1;
    b.bw5=3;

    update_harms_clash(b);
    pretty(b.otherBoards[AllPieces]);
    print_board(b);
    print_move(5369873843);
    make_move(b, WHITE, 5369873843);
    print_board(b);
    print_move(2152458530);
    make_move(b, WHITE, 2152458530);
    print_board(b);
    print_move(36511465602);
    make_move(b, WHITE, 36511465602);
    print_board(b);
/*
    Moves a = get_moves(b, WHITE);
    print_move_list(a);
    pretty(b.otherBoards[AllPieces]);
    pretty(b.whiteBoards[allflowers]);
    pretty(b.blackBoards[allflowers]);
  */  
}

int main(){
    //test_print_macros();
    //test_board_ops();
    //test_lsb();
    //test_gen_moves();
    //test_wheel2();
    //test_boat();
    //test_harm_clashes();
    //test_total_harms();
    //test_minimax();
    test_abprune();
    //test_move_types();
    //comp_v_comp();
    //test_fail2();
    //test_fail3();
    //test_fail4();
    //test_fail1();
    //test_print_board();
    return 1;
}
