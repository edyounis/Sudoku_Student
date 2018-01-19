#include"BTSolver.hpp"
#include"../sudoku/SudokuFile.hpp"
#include"../sudoku/Converter.hpp"
#include"../sudoku/CurrentTime.hpp"
#include<stack>
#include<utility>
#include<iostream>
#include<vector>


//TODO: comment all the cout commands upon final submission

class BTSolver{
private:
    ConstraintNetwork network;
    std::stack<std::pair<Variable*, Domain> > trail;
    std::stack<int> breadcrumbs;
    bool hasSolution = false;
    SudokuFile sudokuGrid;
    
    int numAssignments;
    int numBacktracks;
    long startTime;
    long endTime;
    
    std::string varHeuristics;
    std::string valHeuristics;
    std::string cChecks;

public:
    BTSolver(SudokuFile sf){
		network = SudokuFileToConstraintNetwork(sf);
        sudokuGrid = sf;
		SudokuFile n = ConstraintNetworkToSudokuFile(network, sf.getN(), sf.getP(), sf.getQ());
        numAssignments = 0;
        numBacktracks = 0;
    }
    
    void setVariableSelectionHeuristic(std::string vsh){
        varHeuristics = vsh;
    }
    
    void setValueSelectionHeuristic(std::string vsh){
        valHeuristics = vsh;
    }
    
    void setConsistencyChecks(std::string cc){
        cChecks = cc;
    }
    
    bool haveSolution(){
        return hasSolution;
    }
    
    SudokuFile getSolution(){
        return sudokuGrid;
    }
    
    void printSolverStats(){
        long timeTaken = endTime - startTime;
        std::cout<<"Time taken:"<<timeTaken<<" ms"<<std::endl;
        std::cout<<"Number of assignments: "<<numAssignments<<std::endl;
        std::cout<<"Number of backtracks: "<<numBacktracks<<std::endl;
    }
    
    long getTimeTaken(){
        return endTime - startTime;
    }
    
    int getNumAssignments(){
        return numAssignments;
    }
    
    int getNumBacktracks(){
        return numBacktracks;
    }
    
    ConstraintNetwork getNetwork(){
        return network;
    }
    
    bool checkConsistency(){
        bool isConsistent = false;
        if(cChecks == "None")
            isConsistent = assignmentsCheck();
        else if(cChecks == "ForwardChecking")
            isConsistent = forwardChecking();
        else if(cChecks == "ArcConsistency")
            isConsistent = arcConsistency();
        return isConsistent;
    }
    
    
    bool assignmentsCheck(){
        int i = 0;
		for(Variable* v : network.getVariables()){
            if(v->isAssigned()){
				++i;
                for(Variable* pVOther : network.getNeighborsOfVariable(v)){
                    if (v->getAssignment() == pVOther->getAssignment()){
                        return false;
                    }
                }
            }
        }
		return true;
    }
    
    /**
     * TODO: Implement forward checking.
     */
    bool forwardChecking(){
        return false;
    }
    
    /**
     * TODO: Implement Maintaining Arc Consistency.
     */
    bool arcConsistency(){
        return false;
    }
    
    Variable* selectNextVariable(){
        //if(varHeuristics == "None")
            Variable* next = getfirstUnassignedVariable();
        
        /**
         * TODO: Implement MRV heuristic
         * @return variable with minimum remaining values that isn't assigned, null if all variables are assigned.
         */
        

        //else if(varHeuristics == "MinimumRemainingValue")
        
        /**
         * TODO: Implement Degree heuristic
         * @return variable constrained by the most unassigned variables, null if all variables are assigned.
         */
        //else if(varHeuristics == "Degree")
        return next;
    }
    
    Variable* getfirstUnassignedVariable(){
        for(Variable* v : network.getVariables()){
            if(!(v->isAssigned())){
                return v;
            }
        }
        std::cout<<"all assigned"<<std::endl;
        return nullptr;  //returns a null varialbe if all variables are assigned
    }
    
    std::vector<int> getNextValues(Variable* v){
        std::vector<int> orderedValues;
        if(valHeuristics == "None")
            orderedValues = getValuesInOrder(v);
       //TODO:
       // else if(valHeuristics == "LeastConstrainingValue")
       // orderedValues = getValuesLCVOrder(v);
        return orderedValues;
    }
    
    
    std::vector<int> getValuesInOrder(Variable* v){
        std::vector<int> values = v->getDomain().getValues();
        
        //TODO: sort the values
        return values;
    }
    
    /**
     * TODO: LCV heuristic
     */
//    std::vector<int> getValuesLCVOrder(Variable v){
//    }
    
    void success(){
        hasSolution = true;
        sudokuGrid = ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());
    }
    
    void solve(){
        std::cout<<"solve"<<std::endl;
		startTime = currentTimeMillis();
        try {
            solve(0);
        }catch (...){
            std::cout<<"error with variable selection heuristic."<<std::endl;
        }
        endTime = currentTimeMillis();
        while(!trail.empty())
            trail.pop();
    }
    
    void solve(int level){
		std::cout<<"level: "<<level<<std::endl;
        sudokuGrid = ConstraintNetworkToSudokuFile(network, sudokuGrid.getN(), sudokuGrid.getP(), sudokuGrid.getQ());  //this line is for testing, please comment upon final submission.
		std::cout<<sudokuGrid.toString()<<std::endl;
		if(hasSolution){
            std::cout<<"hasSolution"<<std::endl;
			return;
		}
        Variable* v = selectNextVariable();
		if(v == nullptr){
			for(Variable* var : network.getVariables()){
                if(!var->isAssigned()){
                    std::cout<<"Error"<<std::endl;
                }
            }
            success();
            return;
        }
        
        for(int i : getNextValues(v)){
            breadcrumbs.push(trail.size());
            v->updateDomain(Domain(i));
            trail.push(std::pair<Variable*, Domain>(v,v->getDomain()));
            numAssignments++;
            bool isConsistent = checkConsistency();
            if(isConsistent){
                solve(level+1);
            }
            if(!hasSolution){
                int targetSize = breadcrumbs.top();
                breadcrumbs.pop();
                for (int size = trail.size(); size > targetSize; size--){
                    std::pair<Variable*, Domain> vPair = trail.top();
                    trail.pop();
                    v = vPair.first;
                    v->setDomain(vPair.second);
                }
                numBacktracks++;
            }
            else{
                return;
            }
        }
    }
};
