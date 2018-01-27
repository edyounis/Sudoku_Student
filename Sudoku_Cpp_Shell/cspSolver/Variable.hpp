#ifndef VARIABLE_HPP
#define VARIABLE_HPP

#include<iterator>
#include<sstream>
#include<vector>
#include<stack>
#include<utility>
#include<iostream>
#include<algorithm>

class Domain{
    // Properties
    
    private:
    std::vector<int> values;
    bool modified;

    // Constructors

    public:
    typedef std::vector<int>::iterator iterator;
    /**
     * Constructs a domain with a single value
     * @param value the sole value within the domain
     */
    Domain(int value);
    
    /**
     * Constructs a domain with an array of values
     * @param values all possible values for the domain
     */
    //    Domain(int* values);
    
    /**
     * Constructs a domain with an ArrayList<Integer> of values
     * @param values all possible values for the domain
     */
	Domain& operator= (const Domain& other);
    Domain(std::vector<int> values);
    
    /**
     * Copy Constructor. Used to keep a copy of assignments in the Trail.
     * @param d the domain to copy
     * @see Trail
     */
    Domain(const Domain& d);

    // Accessors

    /**
     * *Note, Domain is iterable. You can use
     * 	for(Integer i : Domain)
     *  {
     *  	...
     *  }
     *
     * @return ArrayList of values in Domain
     */
    std::vector<int> getValues() const;
    
    /**
     * Checks if a value exists within the domain
     * @param value to check
     * @return true if <tt>value</tt> exists within the domain, false otherwise.
     */
    bool contains(int value) const;
    
    /**
     * @return number of values in the domain
     */
    int size() const;
    
    /**
     * @return true if no values are contained in the domain.
     */
    bool isEmpty() const;
    
    
    /**
     * Returns whether or not the domain has been modified.
     *
     * @return true if the domain has been modified
     */
    bool isModified() const;
    
    // Modifiers

    /**
     * Removes <tt>value</tt> from the domain.
     * @param value the int to be removed
     */
    bool remove(int value);
    
    
    /**
     * Sets modified flag.
     * @param modified value to set the modified flag.
     */
    void setModified(bool modified);
    
    // Iterator
    
    //	@Override
    //	public Iterator<Integer> iterator() {
    //		return values.iterator();
    //	}
    bool equals(Domain d) const;
    
    std::vector<int>::iterator begin();
    
    std::vector<int>::iterator end();

    // String representation
    
    std::string toString();
};


class Variable
{
	// Properties
public:
	Domain domain;
	int r, c, b;
	bool modified;
	bool unchangeable;
    std::string name;
	int oldSize;
    //static Trail trail = Trail::getTrail();
	
	// Constructors
	
    Variable(std::vector<int> possible_Values, int row, int col, int block);
	
	Variable& operator=(const Variable& other);
    Variable(const Variable& v);
    static int namingCounter;
    //Variable::namingCounter = 0;

    bool operator==(const Variable &other) const;
    bool operator!=(const Variable &other) const;

	// Accessors
	
	/**
	 * Used for local search. Used to differentiate between intialized assignments
	 * and user assignments.
	 * @return false if this variable was assigned at initialization.
	 */
	
	void modify(const Variable& other);

    bool isChangeable() const;
    bool isAssigned() const;
    bool isModified() const;
	
    void setModified(bool modified);
	
    int row() const;
    int col() const;
    int block() const;
	
	/**
	 * Returns the value currently assigned to the IntVariable.
	 * If the IntVariable is currently unassigned, returns 0
	 * @return 0 if IntVariable is unassigned, Assignment otherwise
	 */
    int getAssignment()const;
    std::vector<int> Values() const;
    int size() const;
    Domain getDomain() const;
    std::string getName() const;
	
	// Modifiers
	
	/** 
	 * Used for local Search
	 * @param val new assignment
	 */
    void assignValue(int val);
	
	/**
	 * Used for Backtracking. Adds the changed domain to the Trail.
	 * @param d new domain
	 */
    void updateDomain(Domain d);
	
	/**
	 * Performs a change to the domain without changing the Trail.
	 * @param d new domain 
	 */
    void setDomain(Domain d);
	
	/**
	 * Removes a single value from the domain of V.
	 * @param val value to remove
	 */
    void removeValueFromDomain(int val);
	
	// Helper Methods
	
    void methodModifiesDomain();

	// Iterator

//	@Override
//	public Iterator<Integer> iterator() {
//		return domain.iterator();
//	}
    
    Domain::iterator begin();
    Domain::iterator end();
	
	// String Representation

    std::string toString();
};

/**
 * Represents the domain of a variable, i.e. the possible values that each
 * variable may assign.
 */

//friend bool operator== (Variable& v1, Variable& v2);

#endif
