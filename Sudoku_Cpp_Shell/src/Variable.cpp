#include"Variable.hpp"

int Variable::namingCounter = 1;

Variable::Variable ( Domain::ValueSet possible_Values, int row, int col, int block ) : domain(possible_Values)
{
	if ( domain.size() == 1 )
	{
		modified = true;
		unchangeable = true;
	}

	r = row;
	c = col;
	b = block;
	name = "v" + std::to_string(namingCounter++);
	oldSize = size();
}

Variable::Variable ( const Variable& v ) : domain(v.domain)
{
	r = v.row();
	c = v.col();
	b = v.block();
	modified = v.isModified();
	name = v.getName();
}

void Variable::modify ( const Variable& other )
{
	r = other.row();
	c = other.col();
	b = other.block();
	modified = other.isModified();
	name = other.getName();
	domain = other.getDomain();
	oldSize = other.oldSize;
}

bool Variable::operator== ( const Variable &other ) const
{
	return (row() == other.row()) && (col() == other.col()) && (block() == other.block());
}

bool Variable::operator!= ( const Variable &other ) const
{
	return !(*this == other);
}

bool Variable::isChangeable( void ) const
{
	return domain.size() != 1;
}

bool Variable::isAssigned( void ) const
{
	return size() == 1 ? true : false;
}

bool Variable::isModified( void ) const
{
	return modified;
}

void Variable::setModified( bool modified )
{
	this->modified = modified;
	this->domain.setModified(modified);
}

int Variable::row ( void ) const
{
	return r;
}

int Variable::col ( void ) const
{
	return c;
}

int Variable::block ( void ) const
{
	return b;
}

int Variable::getAssignment ( void ) const
{
	if ( !isAssigned() )
	{
		return 0;
	}
	else
	{
		if ( domain.getValues().size() != 1 )
			std::cout << "ERROR!" << std::endl;
		return domain.getValues()[0];
	}
}

Domain::ValueSet Variable::getValues ( void ) const
{
	return domain.getValues();
}

int Variable::size ( void ) const
{
	return domain.size();
}

Domain Variable::getDomain ( void ) const
{
	return domain;
}

std::string Variable::getName ( void ) const
{
	return name;
}

void Variable::assignValue ( int val )
{
	setDomain(Domain(val));
}

void Variable::updateDomain ( Domain d )
{
	methodModifiesDomain();

	domain = d;
	modified = true;
}

void Variable::setDomain ( Domain d )
{
	domain = d;
	modified = true;
}

void Variable::removeValueFromDomain ( int val )
{
	methodModifiesDomain();
	domain.remove(val);
	modified = domain.isModified();
}

void Variable::methodModifiesDomain ( void )
{
	int newSize = size();

	if (oldSize > newSize)
	{
		oldSize = newSize;
	}
}

Domain::iterator Variable::begin()
{
	return domain.begin();
}

Domain::iterator Variable::end()
{
	return domain.end();
}

std::string Variable::toString()
{
	std::stringstream ss;
	std::string sep = "";
	ss << " Name: " << name;
	ss << "\tdomain: {";

	for ( int i = 0; i < domain.getValues().size(); ++i )
	{
		ss<<sep<<domain.getValues()[i];
		sep = ",";
	}

	ss<<"}";
	return ss.str();
}
