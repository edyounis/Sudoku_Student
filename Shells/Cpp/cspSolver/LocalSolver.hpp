#ifndef LOCALSOLVER_HPP
#define LOCALSOLVER_HPP

#include"ConstraintNetwork.hpp"
#include"../sudoku/CurrentTime.hpp"
#include"../sudoku/SudokuFile.hpp"
#include"../sudoku/Converter.hpp"
#include"../cspSolver/Assignment.hpp"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<ctime>

class LocalSolver{
private:
    //Properties
    ConstraintNetwork network;
    int n;
    
    int numTotalAttempts;
    int numAttempts = 0;
    int limitAttempts = 1000;
    long startTime;
    long endTime;
    
    SudokuFile sudokuGrid;
    
public:
    //Constructor
    LocalSolver(SudokuFile sf);
    //Accessors
    bool hasSolution();
    /**
     * @return solution if a solution has been found, otherwise returns the unsolved puzzle.
     */
    SudokuFile getSolution();
    void printSolverStats();
    //Helper Methods
    bool isSolution();
    /**
     * Restarts the local search after a predefined number of attempts.
     */
    void restartCounter();
    
    void generateStartState();
    int generateSuccessor();
    std::vector<Assignment*> getAllPossibleAssignments();
    
    void success();
    
    int getNetworkScore();
    void solve();
};

#endif
