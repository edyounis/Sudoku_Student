#ifndef SUDOKUBOARDREADER_HPP
#define SUDOKUBOARDREADER_HPP

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<stdexcept>
#include<fstream>
//#include<cstdlib>
#include"SudokuFile.hpp"
#include"Odometer.hpp"

SudokuFile readFile(std::string filePath);
SudokuFile setSudokuFileParameters(std::vector<std::string> params);
void parseLineOfSudokuBoard(SudokuFile& sf, std::vector<std::string> params, int rowNumber);


#endif
