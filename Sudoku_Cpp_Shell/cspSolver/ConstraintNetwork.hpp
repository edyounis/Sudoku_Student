#ifndef ConstraintNetwork_hpp
#define ConstraintNetwork_hpp

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<algorithm>
#include<unordered_set>
#include"Variable.hpp"
#include"Constraint.hpp"
#include"Assignment.hpp"

class ConstraintNetwork {

    // Properties
    
private:
    std::vector<Constraint> constraints;
    std::vector<Variable*> variables;
//    std::vector<Varialbe*> pVariables; 
    // Constructor
    
public:
    ConstraintNetwork();

	ConstraintNetwork& operator=(const ConstraintNetwork& rhs);    
    // Modifiers
    
    void add(Constraint c);
    void add(Variable* v);    /**
     * Used for Local Search. Assigns a value to a variable based on the parameter a
     * @param a Assignment to actualize
     */
    void pushAssignment(Assignment a);    // Accessors
    
    std::vector<Constraint> getConstraints() const;
    std::vector<Variable*> getVariables() const;
 ///************
    std::vector<Variable*> getNeighborsOfVariable(Variable* v);
    /**
     * Used for local search. Determines if the current assignment is consistent.
     * @return
     */
    bool isConsistent() const;
    /**
     * @param v variable to check
     * @return list of constraints that contains v
     */
    std::vector<Constraint*> getConstraintsContainingVariable(Variable* v);    /**
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
    std::vector<Constraint*> getModifiedConstraints();    // String Representation
    
    std::string toString() const;
};

#endif 
