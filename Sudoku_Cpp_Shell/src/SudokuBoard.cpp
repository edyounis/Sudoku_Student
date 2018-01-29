#include "SudokuBoard.hpp"

using namespace std;

SudokuBoard::SudokuBoard ( int _p, int _q, int _m )
{
	p = _p;
	q = _q;
	int N = p*q;

	for ( int i = 0; i < N; ++i )
	{
		Row row;

		for ( int j = 0; j < N; ++j )
			row.push_back( 0 );

		board.push_back(row);
	}

	if ( _m > N*N )
		_m = N*N;

	srand( time( NULL ) );

	for ( int i = 0; i <= _m; )
	{
		int randomRow = rand() % N;
		int randomCol = rand() % N;
		int randomAssignment = (rand() % N) + 1;

		if ( board[randomRow][randomCol] == 0 )
		{
			if ( check ( randomRow, randomCol, randomAssignment ) )
			{
				board[randomRow][randomCol] = randomAssignment;
				++i;
			}
		}
	}
}

SudokuBoard::SudokuBoard ( int _p, int _q, Board _board )
{
	p = _p;
	q = _q;
	board = _board;
}

SudokuBoard::SudokuBoard ( std::string filename )
{
	ifstream file( filename );

	file >> p;
	file >> q;
	int N = p*q;

	for ( int i = 0; i < N; ++i )
	{
		for ( int j = 0; j < N; ++j )
		{
			file >> board[i][j];
		}
	}
}

int SudokuBoard::get_p ( void ) const
{
	return p;
}

int SudokuBoard::get_q ( void ) const
{
	return q;
}

int SudokuBoard::get_n ( void ) const
{
	return p*q;
}

SudokuBoard::Board SudokuBoard::get_board ( void ) const
{
	return board;
}


string SudokuBoard::toString ( void ) const
{
	stringstream ss;
	int N = p*q;
	ss << "P:  " << p << "\t" << "Q:  " << q << "\n";

	for ( int i = 0; i < N; ++i )
	{
		for ( int j = 0; j < N; ++j )
		{
			ss << intToOdometer( board[i][j] ) << " ";

			if ( (j+1) % q == 0 && j != 0 && j != N-1 )
			{
				ss << "| ";
			}
		}

		ss << "\n";

		if ( (i+1) % p == 0 && i != 0 && i != N-1 )
		{
			for ( int k = 0; k < N+p-1; ++k )
			{
				ss << "- ";
			}
			ss << "\n";
		}
	}
	return ss.str();
}

bool SudokuBoard::check ( int row, int col, int value ) const
{
	return checkRow( row, value ) && checkCol( col, value ) && checkBox( row, col, value );
}

bool SudokuBoard::checkRow ( int row, int value ) const
{
	for ( int i = 0; i < p*q; ++i )
		if ( board[row][i] == value )
			return false;
	return true;
}

bool SudokuBoard::checkCol ( int col, int value ) const
{
	for ( int i = 0; i < p*q; ++i )
		if ( board[i][col] == value )
			return false;
	return true;
}

bool SudokuBoard::checkBox ( int row, int col, int value ) const
{
	int rDiv = row / p;
	int cDiv = col / q;

	for ( int i = rDiv * p; i < (rDiv + 1) * p; ++i )
	{
		for ( int j = cDiv * q; j < (cDiv + 1) * q; ++j )
		{
			if(board[i][j] == value)
				return false;
		}
	}

	return true;
}

string SudokuBoard::intToOdometer ( int n ) const
{
	string ret = "";

	for ( int i = n; n > 0; n /= 36 )
	{
		int r  = n % 36;
		char x = r < 10 ? '0' + r : 'A' + r;
		ret += x;
	}

	return ret == "" ? "0" : ret;
}
