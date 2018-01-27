This program’s structure follows the Java shell.

Some structural Differences:
Variable.cpp and Variable.hpp contains both Variable class and Domain class
Trail class in the Java shell is written in the BTSolver.

CurrentTime.hpp contains code I wrote to imitate the functionality of CurrentTimeMillis in Java.

All other files have the same functionality as they appear in the original Java shell.


To Run the Example code:

(I tested the code on Ubuntu 14.04 using gcc 4.8.4. Some of my code using c++11 standard. 
It seems that the gcc on openlab is a bit out-of-dated and does not support c++11. 
If it has to be runnable on openlab, please let me know and I will try to make it compatible to older c++ versions.)

I have created a Makefile in the parent directory. Just run the Makefile and it will automatically compile and link all the needed files.

After running the Makefile, it will create three executable files in the parent dirctory:

SudokuFileExample:  This is a demo on how the program randomly generates a new sudoku problem. 
Modify examples/SudokuFileExample.cpp to change the behavior of this demo.

ConverterExample:  This is a demo on how the program convert a sudoku file into a constraint network. 
It prints out the variable numbers in the sudoku file and then prints out each group of varibles that are in the same constraint. 
Modify examples/ConverterExample.cpp to change the behavior of this demo.

BTSolverExample: This is a demo on how the program use a "dummy" backtracking solver to solver a problem. 
After each round, the program will print out its current process. It will print out a final solution if it succeeded. 
Modify examples/BTSolverExample.cpp to change the behavior of this demo(e.g. the size of the sudoku problem). 
Since the shell is very "dummy", I set the size of the sudoku problem in this sample to be "4*4". 
The probability of usin this shell to solve a "9*9" problem is very low.  
cspSolver/BTSolver.cpp is the file that students should modify to make the algorithm "smarter".


-Several issues:
*For Local Solver, I think you specified that students do not need to complete this part for the project. 
I did create the Local Solver based on the Java shell, but it seems to have some problem. I am have trouble locating this problem. 
I'm not sure if the problem comes from the Java shell or my own code.

*It seems that the Java shell somehow turns the sudoku board by 90 degrees. 
I tried but was unable to find the problem. My shell also has this issue.

*The Makefile may sometimes fail to update the executable files after updating the source code. 
If you encounter any weird problems after editing the source code, please do "make clean" and then re-"make" it.

Thank you very much. I sincerely apologize for the issues that I am unable to solve.
