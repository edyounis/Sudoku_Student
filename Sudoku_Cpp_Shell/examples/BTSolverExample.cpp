#include"../cspSolver/BTSolver.cpp"
#include"../sudoku/SudokuBoardGenerator.hpp"
#include"../sudoku/SudokuFile.hpp"

#include<iostream>

int main(){
    SudokuFile sf = generateBoard(4,2,2,3);
    BTSolver solver = BTSolver(sf);
	std::cout<<"Below is a randomly-generated sudoku file."<<std::endl;
    std::cout<<solver.getSolution().toString()<<std::endl;

    solver.setConsistencyChecks("None");

    solver.setValueSelectionHeuristic("None");

    solver.setVariableSelectionHeuristic("None");

    
    solver.solve();
	std::cout<<"solve_complete"<<std::endl;

    if(solver.haveSolution()){
		std::cout<<"has solution"<<std::endl;
        solver.printSolverStats();
        std::cout<<solver.getSolution().toString()<<std::endl;
    }
    else
        std::cout<<"Failed to find a solution"<<std::endl;
    return 0;
}
