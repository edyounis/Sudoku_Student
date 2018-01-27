#include<iostream>

#include"../sudoku/SudokuBoardGenerator.hpp"
#include"../sudoku/SudokuBoardReader.hpp"
#include"../sudoku/SudokuFile.hpp"

int main(){
    int N = 16;
    int p = 4;
    int q = 4;
    int m = 25;
    
    SudokuFile generatedSudokuFile = generateBoard(N, p, q, m);
    
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<"below is a randomly generated SudokuFile:"<<std::endl;
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<generatedSudokuFile.toString();
    
    return 0;
}
