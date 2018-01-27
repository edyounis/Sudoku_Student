#include"LocalSolver.hpp"

LocalSolver::LocalSolver(SudokuFile sf){
    network = SudokuFileToConstraintNetwork(sf);
    n = sf.getN();
    sudokuGrid = sf;
	numTotalAttempts = 0;
	numAttempts = 0;
}

//Accessors
bool LocalSolver::hasSolution(){
    return isSolution();
}

/**
 * @return solution if a solution has been found, otherwise returns the unsolved puzzle.
 */
SudokuFile LocalSolver::getSolution(){
    return sudokuGrid;
}

void LocalSolver::printSolverStats(){
    long time = endTime - startTime;
    std::cout<<"Time taken:"<<time<<" ms"<<std::endl;
    std::cout<<"Steps until convergence:"<<numTotalAttempts<<" steps"<<std::endl;
}

//Helper Methods
bool LocalSolver::isSolution(){
    for(Constraint& c : network.getConstraints()){
        if(!c.isConsistent()){
            return false;
        }
    }
    return true;
}

/**
 * Restarts the local search after a predefined number of attempts.
 */
void LocalSolver::restartCounter(){
	numTotalAttempts ++;
	numAttempts ++;
    if(numAttempts > limitAttempts){
        std::cout<<"restart"<<std::endl;
        numAttempts = 0;
        generateStartState();
    }
}

void LocalSolver::generateStartState(){
    for(Variable* v : network.getVariables()){
        if(v->isChangeable()){
			v->assignValue(rand() % n + 1 );
        }
    }
    sudokuGrid = ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());
    network = SudokuFileToConstraintNetwork(sudokuGrid);
}

int LocalSolver::generateSuccessor(){
	std::vector<Assignment*> assignments = getAllPossibleAssignments();
    std::cout<<assignments.size()<<std::endl;
    if(assignments.size() == 0){
	//	success();
		std::cout<<"No possible assignments. Failed"<<std::endl;
		return 0;
	}
	Assignment* nextAssignment = assignments[rand() % (assignments.size())];
	network.pushAssignment(*nextAssignment);
	for(int i = 0; i < assignments.size(); ++i)
		delete assignments[i];
	return 1;
}

std::vector<Assignment*> LocalSolver::getAllPossibleAssignments(){
	std::vector<Assignment*> assignments;
    for(Variable* v : network.getVariables()){
        if(v->isChangeable()){
            for(int val = 1; val <= n; val++){
                Assignment* a = new Assignment(v,val);
                assignments.push_back(a);
            }
        }
    }
    return assignments;
}

void LocalSolver::success(){
    endTime = currentTimeMillis();
    std::cout<<"Solution found!"<<std::endl;
    std::cout<<sudokuGrid.getN()<<" "<<sudokuGrid.getP()<<" "<<sudokuGrid.getQ()<<std::endl;
    sudokuGrid = ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());
    std::cout<<sudokuGrid.toString()<<std::endl;
}

int LocalSolver::getNetworkScore(){
    int networkScore = 0;
    for(Constraint& c : network.getConstraints()){
        networkScore += c.getConflicts();
    }
    return networkScore;
}

void LocalSolver::solve(){
	srand(time(NULL));
    startTime = currentTimeMillis();
    generateStartState();
    while(!isSolution()){
		std::cout<<"attempt:"<<numAttempts<<std::endl;
		sudokuGrid = ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());
  //  network = SudokuFileToConstraintNetwork(sudokuGrid);
		std::cout<<getSolution().toString()<<std::endl;
        restartCounter();
    //    std::cout<<"counter success"<<std::endl;
		if(generateSuccessor() == 0)
			break;
    } 
    success();
}
