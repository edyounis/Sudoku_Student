#ifndef SUDOKUBOARDGENERATOR_HPP
#define SUDOKUBOARDGENERATOR_HPP

#include<iostream>
#include<cstdlib>
#include<stdexcept>
#include<ctime>
#include<vector>
#include"CurrentTime.hpp"
#include"SudokuFile.hpp"


SudokuFile generateBoard(int N, int p, int q, int numAssignments);
SudokuFile generateBoard(int N, int p, int q, int numAssignments, long timeout);

bool checkConstraints(int row, int col, int value, SudokuFile sf, std::vector<std::vector<int> > board);
bool checkRow(int row, int value, int N, std::vector<std::vector<int> > board);
bool checkColumn(int column, int value, int N, std::vector<std::vector<int> > board);
bool checkBox(int row, int column, int value, int p, int q, std::vector<std::vector<int> > board);

#endif
