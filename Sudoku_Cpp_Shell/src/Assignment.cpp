#include"Assignment.hpp"

Assignment::Assignment ( Variable* v, int val )
{
	variable = v;
	value = val;
}

Assignment::Assignment ( Variable* v, int val, int score )
{
	variable = v;
	value = val;
}

Variable* Assignment::getVariable ( void )
{
    return variable;
}

int Assignment::getValue ( void ) const
{

    return value;
}

int Assignment::getScore ( void ) const
{
    return score;
}

void Assignment::setValue ( int val )
{
    this->value = val;
}

void Assignment::setScore ( int score )
{
    this->score = score;
}

int Assignment::compareTo ( Assignment a )
{
    return this->score - a.score;
}

std::string Assignment::toString()
{
    std::stringstream ss;
    ss << "Variable: " << variable->getName();
    ss << "\tValue: " << this->value;
    ss << "\tscore: " << this->score;
    return ss.str();
}

