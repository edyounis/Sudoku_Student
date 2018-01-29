#include"BTSolver.hpp"

using namespace std;

BTSolver::BTSolver ( SudokuBoard input, std::string val_sh, std::string var_sh, std::string cc )
: sudokuGrid( input.get_p(), input.get_q(), input.get_board() ), network( input )
{
	valHeuristics = val_sh;
	varHeuristics = var_sh;
	cChecks =  cc;
}

bool BTSolver::assignmentsCheck ( void )
{
	int i = 0;
	for ( Variable* v : network.getVariables() )
	{
		if ( v->isAssigned() )
		{
			++i;
			for ( Variable* pVOther : network.getNeighborsOfVariable(v) )
			{
				if ( v->getAssignment() == pVOther->getAssignment() )
				{
					return false;
				}
			}
		}
	}
	return true;
}

// Implement This
bool BTSolver::forwardChecking ( void )
{
	return false;
}

// Implement This
bool BTSolver::arcConsistency ( void )
{
	return false;
}

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

// Implement This
Variable* BTSolver::MinimumRemainingValue ( void )
{
	return nullptr;
}

// Implement This
Variable* BTSolver::Degree ( void )
{
	return nullptr;
}

// Implement This
Variable* BTSolver::MRVwithTieBreaker ( void )
{
	return nullptr;
}

std::vector<int> BTSolver::getValuesInOrder ( Variable* v )
{
	return v->getDomain().getValues();
}

// Implement This
std::vector<int> BTSolver::LeastConstrainingValue ( Variable* v )
{
	return std::vector<int>();
}

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
				std::cout << "Error" << std::endl;
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
		trail.push(std::pair<Variable*, Domain>(v,v->getDomain()));
		v->assignValue( i );

		if ( checkConsistency() )
			solve ( level+1 );

		if ( hasSolution )
			return;

		// Backtrack
		std::pair<Variable*, Domain> vPair = trail.top();
		trail.pop();
		vPair.first->setDomain(vPair.second);
	}
}

bool BTSolver::checkConsistency ( void )
{
	if ( cChecks == "forwardChecking" )
		return forwardChecking();

	if ( cChecks == "arcConsistency" )
		return arcConsistency();

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

std::vector<int> BTSolver::getNextValues ( Variable* v )
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
