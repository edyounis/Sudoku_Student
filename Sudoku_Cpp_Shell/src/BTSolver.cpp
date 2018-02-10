#include"BTSolver.hpp"

using namespace std;

// Constructor
BTSolver::BTSolver ( SudokuBoard input, Trail* _trail,  string val_sh, string var_sh, string cc )
: sudokuGrid( input.get_p(), input.get_q(), input.get_board() ), network( input )
{
	valHeuristics = val_sh;
	varHeuristics = var_sh;
	cChecks =  cc;

	trail = _trail;
}

// =====================================================================
// Consistency Checks
// =====================================================================

// Basic consistency check, no propagation done
bool BTSolver::assignmentsCheck ( void )
{
	for ( Constraint c : network.getConstraints() )
	{
		if ( ! c.isConsistent() )
		{
			return false;
		}
	}
	return true;
}

/**
 * Part 1 TODO: Implement the Forward Checking Heuristic
 *
 * Note: remember to trail.push variables before you assign them
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::forwardChecking ( void )
{
	return false;
}

/**
 * Part 2 TODO: Implement both of Norvig's Heuristics
 *
 * Note: remember to trail.push variables before you assign them
 * Return: true is assignment is consistent, false otherwise
 */
bool BTSolver::norvigCheck ( void )
{
	return false;
}

// =====================================================================
// Variable Selectors
// =====================================================================

// Basic variable selector, returns first unassigned variable
Variable* BTSolver::getfirstUnassignedVariable ( void )
{
	for ( Variable* v : network.getVariables() )
	{
		if ( !(v->isAssigned()) )
		{
			return v;
		}
	}

	// Everything is assigned
	return nullptr;
}

/**
 * Part 1 TODO: Implement the Minimum Remaining Value Heuristic
 *
 * Return: The unassigned variable with the smallest domain
 */
Variable* BTSolver::MinimumRemainingValue ( void )
{
	return nullptr;
}

/**
 * Part 2 TODO: Implement the Degree Heuristic
 *
 * Return: The unassigned variable involved in the most constraints
 */
Variable* BTSolver::Degree ( void )
{
	return nullptr;
}

/**
 * Part 2 TODO: Implement the Minimum Remaining Value Heuristic
 *                with Degree Heuristic as a Tie Breaker
 *
 * Return: The unassigned variable with the smallest domain and involved
 *             in the most constraints
 */
Variable* BTSolver::MRVwithTieBreaker ( void )
{
	return nullptr;
}

// =====================================================================
// Variable Selectors
// =====================================================================

// Default Value Ordering
vector<int> BTSolver::getValuesInOrder ( Variable* v )
{
	return v->getDomain().getValues();
}

/**
 * Part 1 TODO: Implement the Least Constraining Value Heuristic
 *
 * Return: A list of v's domain sorted by the LCV heuristic
 */
vector<int> BTSolver::LeastConstrainingValue ( Variable* v )
{
	return vector<int>();
}

// =====================================================================
// Engine functions
// =====================================================================

void BTSolver::solve ( int level )
{
	if ( hasSolution )
		return;

	// Variable Selection
	Variable* v = selectNextVariable();

	if ( v == nullptr )
	{
		for ( Variable* var : network.getVariables() )
		{
			// If all variables haven't been assigned
			if ( !var->isAssigned() )
			{
				cout << "Error" << endl;
				return;
			}
		}

		// Success
		hasSolution = true;
		return;
	}

	// Attempt to assign a value
	for ( int i : getNextValues( v ) )
	{
		// Store place in trail and push variable's state on trail
		trail->placeTrailMarker();
		trail->push( v );

		// Assign the value
		v->assignValue( i );

		// Propagate constraints, check consistency, recurse
		if ( checkConsistency() )
			solve ( level+1 );

		if ( hasSolution )
			return;

		// Backtrack
		trail->undo();
	}
}

bool BTSolver::checkConsistency ( void )
{
	if ( cChecks == "forwardChecking" )
		return forwardChecking();

	if ( cChecks == "norvigCheck" )
		return norvigCheck();

	return assignmentsCheck();
}

Variable* BTSolver::selectNextVariable ( void )
{
	if ( varHeuristics == "MinimumRemainingValue" )
		return MinimumRemainingValue();

	if ( varHeuristics == "Degree" )
		return Degree();

	if ( varHeuristics == "MRVwithTieBreaker" )
		return MRVwithTieBreaker();

	return getfirstUnassignedVariable();
}

vector<int> BTSolver::getNextValues ( Variable* v )
{
	if ( valHeuristics == "LeastConstrainingValue" )
		return LeastConstrainingValue(v);

	return getValuesInOrder(v);
}

bool BTSolver::haveSolution ( void )
{
	return hasSolution;
}

SudokuBoard BTSolver::getSolution ( void )
{
	return network.toSudokuBoard ( sudokuGrid.get_p(), sudokuGrid.get_q() );
}

ConstraintNetwork BTSolver::getNetwork ( void )
{
	return network;
}
