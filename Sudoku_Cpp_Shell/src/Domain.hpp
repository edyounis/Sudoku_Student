#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <iterator>
#include <sstream>
#include <vector>
#include <stack>
#include <utility>
#include <iostream>
#include <algorithm>

class Domain
{
public:
	// Typedefs
	typedef std::vector< int > ValueSet;
	typedef ValueSet::iterator iterator;

	// Constructs a domain with a single value
	Domain ( int value );

	// Constructs a domain with many values
	Domain ( ValueSet values );

	// Copy Constructor
	Domain ( const Domain& d );

	// Accessors
	ValueSet getValues  ( void )      const;
	bool     contains   ( int value ) const;
	int      size       ( void )      const;
	bool     isEmpty    ( void )      const;
	bool     isModified ( void )      const;
	bool     equals     ( Domain d )  const;

	// Modifiers
	bool remove      ( int value );
	void setModified ( bool modified );


	// Iterator
	ValueSet::iterator begin();
	ValueSet::iterator end();

	// String representation
	std::string toString ( void ) const;

private:
	ValueSet values;
	bool modified;
};

#endif