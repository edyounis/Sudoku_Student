#ifndef BTSOLVER_HPP
#define BTSOLVER_HPP

#include "SudokuBoard.hpp"
#include "Domain.hpp"
#include "Variable.hpp"
#include "ConstraintNetwork.hpp"
#include "Trail.hpp"

#include <utility>
#include <iostream>
#include <vector>

class BTSolver
{
public:
	// Constructor
	BTSolver ( SudokuBoard board, Trail* trail, std::string val_sh, std::string var_sh, std::string cc );

	// Consistency Checks (Implement these)
	bool assignmentsCheck ( void );
	bool forwardChecking  ( void );
	bool norvigCheck      ( void );

	// Variable Selectors (Implement these)
	Variable* getfirstUnassignedVariable ( void );
	Variable* MinimumRemainingValue      ( void );
	Variable* Degree                     ( void );
	Variable* MRVwithTieBreaker          ( void );

	// Value Selectors (Implement these)
	std::vector<int> getValuesInOrder       ( Variable* v );
	std::vector<int> LeastConstrainingValue ( Variable* v );

	// Engine Functions
	void solve ( int level = 0 );

	bool checkConsistency ( void );
	Variable* selectNextVariable ( void );
	std::vector<int> getNextValues ( Variable* v );

	// Helper Functions
	bool haveSolution ( void );
	SudokuBoard getSolution ( void );
	ConstraintNetwork getNetwork ( void );

private:
	ConstraintNetwork network;
	SudokuBoard sudokuGrid;
	Trail* trail;

	bool hasSolution = false;

	std::string varHeuristics;
	std::string valHeuristics;
	std::string cChecks;
};


#endif