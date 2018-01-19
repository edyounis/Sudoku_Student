#ifndef SUDOKUFILE_HPP
#define SUDOKUFILE_HPP

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include"Odometer.hpp"

class SudokuFile{
	private:
		int p;
		int q;
		int N;
		std::vector<std::vector<int> > board;
		
	public:
        SudokuFile();
		SudokuFile(int N, int p, int q, std::vector<std::vector<int> > board);
		SudokuFile(int N, int p, int q);
    
//        ~SudokuFile();
    
        SudokuFile& operator=(const SudokuFile& other);

		int getP() const;
		void setP(int p);
		int getQ() const;
		void setQ(int q);
		int getN() const;
		void setN(int n);
		std::vector<std::vector<int> > getBoard() const;
		void setBoard(std::vector<std::vector<int> > b);
        void deleteBoard();
		std::string toString();
};

#endif
