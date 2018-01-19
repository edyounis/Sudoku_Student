#include<iostream>

#include"../sudoku/SudokuBoardGenerator.hpp"
#include"../sudoku/SudokuFile.hpp"
#include"../cspSolver/LocalSolver.hpp"

int main(){
    SudokuFile sf = generateBoard(9,3,3,5);
    std::cout<<"Here is a randomly generated board:"<<std::endl;
	std::cout<<sf.toString()<<std::endl;
	LocalSolver solver = LocalSolver(sf);
    solver.solve();
    if(solver.hasSolution()){
        solver.printSolverStats();
    	std::cout<<solver.getSolution().toString()<<std::endl;
	} else {
        std::cout<<"Failed to find a solution"<<std::endl;
    }
    return 0;
}
