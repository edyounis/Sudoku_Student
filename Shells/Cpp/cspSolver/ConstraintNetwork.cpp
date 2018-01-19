#include "ConstraintNetwork.hpp"

ConstraintNetwork::ConstraintNetwork(){}

// Modifiers

ConstraintNetwork& ConstraintNetwork::operator=(const ConstraintNetwork& rhs){
	constraints = rhs.getConstraints();
	variables = rhs.getVariables();
	return *this;
}

void ConstraintNetwork::add(Constraint c){
    if (std::find(constraints.begin(),constraints.end(),c) == constraints.end()){
        constraints.push_back(c);
    }
}

void ConstraintNetwork::add(Variable* v){
    if(std::find(variables.begin(),variables.end(),v) == variables.end()){
        variables.push_back(v);
    }
}

/**
 * Used for Local Search. Assigns a value to a variable based on the parameter a
 * @param a Assignment to actualize
 */
void ConstraintNetwork::pushAssignment(Assignment a) {
    a.getVariable()->assignValue(a.getValue());
}

// Accessors

std::vector<Constraint> ConstraintNetwork::getConstraints() const{
    return constraints;
}

std::vector<Variable*> ConstraintNetwork::getVariables() const{
    return variables;
}

///************
std::vector<Variable*> ConstraintNetwork::getNeighborsOfVariable(Variable* v) {
    std::vector<Variable*> neighbors;
    
    for(Constraint& c : constraints){
        if(c.contains(v)){
            for(Variable* va : c.vars)
                if(va != v && std::find(neighbors.begin(),neighbors.end(),va) == neighbors.end())
                    neighbors.push_back(va);
        }
    }
    return neighbors;
}

/**
 * Used for local search. Determines if the current assignment is consistent.
 * @return
 */
bool ConstraintNetwork::isConsistent() const{
    for (Constraint c : constraints){
        if (!c.isConsistent()){
            return false;
        }
    }
    return true;
}

/**
 * @param v variable to check
 * @return list of constraints that contains v
 */
std::vector<Constraint*> ConstraintNetwork::getConstraintsContainingVariable(Variable* v) {
    std::vector<Constraint*> outList;
    for(Constraint& c : constraints){
        if(c.contains(v)){
            outList.push_back(&c);
        }
    }
    return outList;
}

/**
 * Returns the constraints that contain variables whose domains were
 * modified since the last call to this method.
 *
 * After getting the constraints, it will reset each variable to
 * unmodified.
 *
 * Note* The first call to this method returns the constraints containing
 * the initialized variables.
 *
 * @return ArrayList of modified constraints
 */
std::vector<Constraint*> ConstraintNetwork::getModifiedConstraints(){
    std::vector<Constraint*> mConstraints;
    
    for (Constraint& c : constraints){
        if (c.isModified()){
            mConstraints.push_back(&c);
        }
    }
    
    for (Variable* v : variables){
        v->setModified(false);
    }
    return mConstraints;
}

// String Representation

std::string ConstraintNetwork::toString() const{
    std::stringstream ss;
    ss<<variables.size()<<" Variables: {";
    std::string delim = "";
    
    for (Variable* v : variables){
        ss<<delim<<v->getName();
        delim = ",";
    }
    ss<<"}";
    
    ss<<"\n"<<constraints.size()<<" Constraints:";
    delim = "\n";
    for (Constraint c: constraints){
        ss<<delim<<c.toString();
    }
    return ss.str();
}
