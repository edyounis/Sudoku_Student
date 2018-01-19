#include "SudokuBoardGenerator.hpp"

SudokuFile generateBoard(int N, int p, int q, int numAssignments){
    return generateBoard(N, p, q, numAssignments, 5000);
}

SudokuFile generateBoard(int N, int p, int q, int numAssignments, long timeout){
    //given a SudokuFile with N, P, Q, creates a board with the given params
    //and assigns it to the board of the SudokuFile.
    //timeout represents the time in ms allowed to created the SudokuFile
	SudokuFile sf = SudokuFile(N, p, q);
	std::vector<std::vector<int> > tempBoard;
	for(int i = 0; i < sf.getN(); ++i){
		std::vector<int> line = std::vector<int>();
		for(int j = 0; j < sf.getN(); ++j)
			line.push_back(0);
		tempBoard.push_back(line);
	}
	if(numAssignments > sf.getN()*sf.getN()){
		std::cout<<"Number of assignments exceeds available spaces in board. Returning SudokuFile with an empty board"<<std::endl;
        return sf;
    }
    long startTime = currentTimeMillis();
    long currentTime;
	srand(time(NULL));
    for(int i = 0; i < numAssignments; i++){
        int randomRow = rand() % sf.getN(); //0 to N-1
		int randomColumn = rand() % sf.getN(); //0 to N-1
        int randomAssignment = rand() % sf.getN() +1; //1 to N
        //std::cout<<i<<" "<<randomRow<<" "<<randomColumn<<" "<<randomAssignment<<std::endl;
//    	std::cout<<i<<std::endl;
        if(tempBoard [randomRow][randomColumn] == 0 && checkConstraints(randomRow, randomColumn, randomAssignment, sf, tempBoard) ){
            tempBoard[randomRow][randomColumn] = randomAssignment;
        }
        else{
            i--;
            currentTime = currentTimeMillis();
            if(currentTime - startTime > timeout){
                std::cout<<"Timeout at "<<i<<" elements"<<std::endl;
				tempBoard.clear();
                //int** tempBoard = new int* [sf.getN()];
                for(int i = 0; i < sf.getN(); ++i){
                    std::vector<int> tempLine = std::vector<int>();
		    for(int j = 0; j < sf.getN(); ++j)
			tempLine.push_back(0);
		    tempBoard.push_back(tempLine);
		}
                break;
            }
        }
    }
    sf.setBoard(tempBoard);
    return sf;
}


bool checkConstraints(int row, int col, int value, SudokuFile sf, std::vector<std::vector<int> > board){
    if(checkRow(row, value, sf.getN(), board)
       && checkColumn(col, value, sf.getN(), board)
       && checkBox(row, col, value, sf.getP(), sf.getQ(), board)){
        return true;
    }
    return false;
}

bool checkRow(int row, int value, int N, std::vector<std::vector<int> > board){
    for(int i = 0; i < N; i++)
        if(board[row][i] == value)
            return false;
    return true;
}

bool checkColumn(int column, int value, int N, std::vector<std::vector<int> > board){
    for (int i = 0; i < N; i++)
        if(board[i][column] == value)
            return false;
    return true;
}

bool checkBox(int row, int column, int value, int p, int q, std::vector<std::vector<int> > board){
    int rDiv = row/p;
    int cDiv = column/q;
    for(int i = rDiv * p; i < (rDiv + 1) * p; i++){
        for(int j = cDiv * q; j < (cDiv + 1) * q; j++){
            try{
                if(board[i][j] == value)
                    return false;
            }catch(const std::out_of_range& oor){
                std::cout<<p<<" "<<q<<std::endl;
            }
        }
    }
    return true;
}
