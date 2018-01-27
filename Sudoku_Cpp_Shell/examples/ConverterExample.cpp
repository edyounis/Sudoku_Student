#include<iostream>
#include"../sudoku/Converter.hpp"
#include"../sudoku/SudokuBoardGenerator.hpp"
#include"../sudoku/SudokuFile.hpp"
#include"../cspSolver/ConstraintNetwork.hpp"

int main(){
	SudokuFile sf = generateBoard(9,3,3,25);
	ConstraintNetwork cn = SudokuFileToConstraintNetwork(sf);
    
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<"below is a randomly generated SudokuFile:"<<std::endl;
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<sf.toString()<<std::endl;
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<"below is the constraint network representation of the above SudokuFile:"<<std::endl;
    std::cout<<"*****************************************"<<std::endl;
    std::cout<<cn.toString()<<std::endl;
    return 0;
}
