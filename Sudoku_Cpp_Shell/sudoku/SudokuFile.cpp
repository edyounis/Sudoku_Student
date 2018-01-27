#include"SudokuFile.hpp"

SudokuFile::SudokuFile(){
//	setP(1);
//	setQ(1);
//	setN(1);
//	board = new int*[1];
//	board[0] = new int[1];
}

SudokuFile::SudokuFile(int nN, int np, int nq, std::vector<std::vector<int> > b){
	if(nN != np * nq || nN < 1){
		std::cout<<"Board parameters invalid. Creating a 9x9 sudoku file instead."<<std::endl;
		setP(3);
		setQ(3);
		setN(9);
		std::cout<<"here"<<std::endl;
//        int** b = new int*[9];
//       for(int i = 0; i < 9; ++i){
//            b[i] = new int[9];
//        }
        setBoard(b);
    } else {
        setP(np);
        setQ(nq);
        setN(nN);
 //       if(board != nullptr){
        setBoard(b);
//        }
//        else{
//            int** newBoard = new int*[N];
//            for(int i = 0; i < N; ++i)
//                newBoard[i] = new int[N];
//            setBoard(newBoard);
 //       }
    }
}

SudokuFile::SudokuFile(int nN, int np, int nq){
	setN(nN);
	setP(np);
	setQ(nq);
	board = std::vector<std::vector<int> >();
	for(int i = 0; i < getN(); ++i){
		std::vector<int> line = std::vector<int>();
		for(int j = 0; j < getN(); ++j)
			line.push_back(0);
		board.push_back(line);
	}
}

//SudokuFile::~SudokuFile(){
    //deleteBoard();
//}

SudokuFile& SudokuFile::operator=(const SudokuFile& other){
    setP(other.getP());
    setQ(other.getQ());
    setN(other.getN());
    //deleteBoard();
    //int** newBoard = new int*[getN()];
    //for(int i = 0; i < getN(); ++i)
    //    newBoard[i] = new int[getN()];
    //for(int i = 0; i < getN(); ++i){
    //    for(int j = 0; j < getN(); ++j){
    //        newBoard[i][j] = other.getBoard()[i][j];
    //    }
    //}
    setBoard(other.board);
    return *this;
}

int SudokuFile::getP() const{
    return p;
}

void SudokuFile::setP(int np) {
    p = np;
}

int SudokuFile::getQ() const{
    return q;
}

void SudokuFile::setQ(int nq) {
    q = nq;
}

int SudokuFile::getN() const{
    return N;
}

void SudokuFile::setN(int nn) {
    N = nn;
}

std::vector<std::vector<int> > SudokuFile::getBoard() const{
    return board;
}

void SudokuFile::setBoard(std::vector<std::vector<int> > newBoard) {
//    deleteBoard();
    board = newBoard;
//	for(int i = 0; i <getN(); ++i){
//		for(int j = 0; j < getN(); ++j){
//			board[i][j] = newBoard[i][j];
//		}
//	}
}

void SudokuFile::deleteBoard(){
/*	if(board != nullptr){
    	for (int i = 0; i < N; ++i){
			if(board[i] != nullptr)
				delete[] board[i];
		}
		delete[] board;
	}*/
}


std::string SudokuFile::toString(){
	std::stringstream ss;
	ss<<"N:  "<<N;
	ss<<"\tP:  "<<p;
	ss<<"\tQ:  "<<q;
	ss<<"\n";
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
//			std::cout<<i<<" "<<j<<" "<<board[i][j]<<std::endl;
			ss<<intToOdometer(board[i][j])<<" ";
//			std::cout<<"xx"<<std::endl;
			if((j+1)%q == 0 && j != 0 && j != N-1){
				ss<<"| ";
			}
		}
		ss<<"\n";
		if((i+1)%p == 0 && i != 0 && i != N-1){
			for(int k = 0; k < N+p-1;k++){
				ss<<"- ";
			}
			ss<<"\n";
		}
	}
	return ss.str();
}
