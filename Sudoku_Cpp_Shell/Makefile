make: SudokuFileExample ConverterExample LocalSolverExample BTSolverExample

SudokuFileExample: SudokuFileExample.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o
#	g++ -std=c++11 -c examples/SudokuFileExample.cpp
	g++ -std=c++11 -o SudokuFileExample SudokuBoardGenerator.o SudokuFile.o Odometer.o SudokuFileExample.o CurrentTime.o SudokuBoardReader.o

ConverterExample: ConverterExample.o SudokuBoardGenerator.o SudokuFile.o SudokuBoardReader.o Odometer.o CurrentTime.o Converter.o Constraint.o ConstraintNetwork.o Variable.o Assignment.o
#	g++ -std=c++11 -c examples/ConverterExample.cpp
	g++ -std=c++11 -o ConverterExample ConverterExample.o Converter.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o Assignment.o Constraint.o ConstraintNetwork.o Variable.o

BTSolverExample: BTSolverExample.o Assignment.o BTSolver.o Constraint.o ConstraintNetwork.o Variable.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o Converter.o
#	g++ -std=c++11 -c examples/BTSolverExample.cpp
	g++ -std=c++11 -o BTSolverExample BTSolverExample.o Assignment.o BTSolver.o Constraint.o ConstraintNetwork.o Variable.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o Converter.o

LocalSolverExample: LocalSolverExample.o Assignment.o LocalSolver.o Constraint.o ConstraintNetwork.o Variable.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o Converter.o
#	g++ -std=c++11 -c examples/LocalSolverExample.cpp
	g++ -std=c++11 -o LocalSolverExample LocalSolverExample.o Assignment.o LocalSolver.o Constraint.o ConstraintNetwork.o Variable.o SudokuBoardGenerator.o SudokuFile.o Odometer.o CurrentTime.o SudokuBoardReader.o Converter.o

SudokuBoardGenerator.o: sudoku/SudokuBoardGenerator.cpp sudoku/SudokuBoardGenerator.hpp
	g++ -std=c++11 -c sudoku/SudokuBoardGenerator.cpp
SudokuFile.o: sudoku/SudokuFile.cpp sudoku/SudokuFile.hpp
	g++ -std=c++11 -c sudoku/SudokuFile.cpp
Odometer.o: sudoku/Odometer.cpp sudoku/Odometer.hpp
	g++ -std=c++11 -c sudoku/Odometer.cpp
SudokuFileExample.o: examples/SudokuFileExample.cpp
	g++ -std=c++11 -c examples/SudokuFileExample.cpp
CurrentTime.o: sudoku/CurrentTime.cpp sudoku/CurrentTime.hpp
	g++ -std=c++11 -c sudoku/CurrentTime.cpp
SudokuBoardReader.o: sudoku/SudokuBoardReader.cpp sudoku/SudokuBoardReader.hpp
	g++ -std=c++11 -c sudoku/SudokuBoardReader.cpp
Converter.o: sudoku/Converter.cpp sudoku/Converter.hpp
	g++ -std=c++11 -c sudoku/Converter.cpp
BTSolverExample.o: examples/BTSolverExample.cpp
	g++ -std=c++11 -c examples/BTSolverExample.cpp
Assignment.o: cspSolver/Assignment.cpp cspSolver/Assignment.hpp
	g++ -std=c++11 -c cspSolver/Assignment.cpp
BTSolver.o: cspSolver/BTSolver.cpp cspSolver/BTSolver.hpp
	g++ -std=c++11 -c cspSolver/BTSolver.cpp
Constraint.o: cspSolver/Constraint.cpp cspSolver/Constraint.hpp
	g++ -std=c++11 -c cspSolver/Constraint.cpp
ConstraintNetwork.o: cspSolver/ConstraintNetwork.cpp cspSolver/ConstraintNetwork.hpp
	g++ -std=c++11 -c cspSolver/ConstraintNetwork.cpp
Variable.o: cspSolver/Variable.cpp cspSolver/Variable.hpp
	g++ -std=c++11 -c cspSolver/Variable.cpp
LocalSolverExample.o: examples/LocalSolverExample.cpp
	g++ -std=c++11 -c examples/LocalSolverExample.cpp
LocalSolver.o: cspSolver/LocalSolver.cpp cspSolver/LocalSolver.hpp
	g++ -std=c++11 -c cspSolver/LocalSolver.cpp
ConverterExample.o: examples/ConverterExample.cpp
	g++ -std=c++11 -c examples/ConverterExample.cpp

clean:
	rm *.o
	rm *Example
