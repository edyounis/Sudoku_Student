#!/usr/bin/env python3

import sys
import os
import math
import SudokuBoard
import Constraint
import ConstraintNetwork
import BTSolver
import time

def main ( ):
    args = sys.argv

    # Important Variables
    file   = "";
    var_sh = "";
    val_sh = "";
    cc     = "";

    for arg in [args[i] for i in range(1, len(args))]:
        if arg == "MRV":
            var_sh = "MinimumRemainingValue"

        elif arg == "DEG":
            var_sh = "Degree"

        elif arg == "MAD":
            var_sh = "MRVwithTieBreaker"

        elif arg == "LCV":
            val_sh = "LeastConstrainingValue"

        elif arg == "FC":
            cc = "forwardChecking"

        elif arg == "NOR":
            cc = "norvigCheck"

        else:
            file = arg;

    if file == "":
        sudokudata = SudokuBoard.SudokuBoard( 3, 3, 7 )
        print(sudokudata)

        solver = BTSolver.BTSolver( sudokudata, val_sh, var_sh, cc )
        solver.solve()

        if solver.hassolution:
            print( solver.getSolution() )

        else:
            print( "Failed to find a solution" )

        return

    if os.path.isdir(file):
        listOfBoards = None

        try:
            listOfBoards = os.listdir ( file )
        except:
            print ( "[ERROR] Failed to open directory." )
            return

        for f in listOfBoards:
                print ( "Running board: " + str(f) )
                sudokudata = SudokuBoard.SudokuBoard( filepath=f )

                solver = BTSolver.BTSolver( sudokudata, val_sh, var_sh, cc )
                solver.solve()

                if solver.hassolution:
                    print( solver.getSolution() )

                else:
                    print( "Failed to find a solution" )

        return

    sudokudata =  SudokuBoard.SudokuBoard( filepath=file )
    print(sudokudata)

    solver = BTSolver.BTSolver( sudokudata, val_sh, var_sh, cc )
    solver.solve()

    if solver.hassolution:
        print( solver.getSolution() )

    else:
        print( "Failed to find a solution" )

main()