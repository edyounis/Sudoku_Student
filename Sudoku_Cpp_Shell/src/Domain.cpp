#include "Domain.hpp"

Domain::Domain ( int value )
{
	values.push_back( value );
}

Domain::Domain ( Domain::ValueSet vals )
{
	values = vals;
}

Domain::Domain ( const Domain& d )
{
	values = d.values;
}

Domain::ValueSet Domain::getValues ( void ) const
{
	return values;
}

bool Domain::contains ( int value ) const
{
	if ( std::find( values.begin(), values.end(), value ) != values.end() )
		return true;
	return false;
}

int Domain::size ( void ) const
{
	return values.size();
}

bool Domain::isEmpty ( void ) const
{
	return values.empty();
}

bool Domain::isModified ( void ) const
{
	return modified;
}

bool Domain::remove ( int value )
{
	int v = value;

	if ( std::find( values.begin(), values.end(), value ) == values.end() )
		return false;

	setModified( true );
	values.erase( std::remove( values.begin(), values.end(), value ), values.end() );
	return true;
}

void Domain::setModified ( bool modified )
{
	this->modified = modified;
}

bool Domain::equals ( Domain d ) const
{
	return false;
}

Domain::ValueSet::iterator Domain::begin()
{
	return values.begin();
}

Domain::ValueSet::iterator Domain::end()
{
	return values.end();
}

std::string Domain::toString( void ) const
{
	std::stringstream ss;
	ss << "{";
	std::string delim = "";

	for ( int i = 0; i < values.size(); ++i )
	{
		ss << delim << values[i];
		delim = ",";
	}

	ss << "}";
	return ss.str();
}