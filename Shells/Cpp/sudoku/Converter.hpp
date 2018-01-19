#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include"../cspSolver/Constraint.hpp"
#include"../cspSolver/ConstraintNetwork.hpp"
#include"SudokuFile.hpp"
#include"../cspSolver/Variable.hpp"
#include<map>
#include<utility>
#include<iostream>


ConstraintNetwork SudokuFileToConstraintNetwork(SudokuFile sf);
SudokuFile ConstraintNetworkToSudokuFile(ConstraintNetwork cn, int n, int p, int q);

#endif
