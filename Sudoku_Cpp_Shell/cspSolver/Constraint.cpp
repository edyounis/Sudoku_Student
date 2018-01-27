#include"Constraint.hpp"

Constraint::Constraint(){}

Constraint::Constraint(std::vector<Variable*> vars){
    this->vars = vars;
}

bool Constraint::operator==(const Constraint &other) const{
    if(vars.size() == other.vars.size()){
        for(Variable* v : vars){
            if(std::find(other.vars.begin(), other.vars.end(),v) == other.vars.end())
                return false;
        }
        return true;
    }
    return false;
}

void Constraint::addVariable(Variable* v){
    vars.push_back(v);
}

int Constraint::size(){
    return vars.size();
}

bool Constraint::contains(Variable* v){
    if (std::find(vars.begin(), vars.end(), v)!=vars.end())
        return true;
    return false;
}

bool Constraint::isModified(){
    for (Variable* var:vars){
        if (var->isModified()){
            return true;
        }
    }
    return false;
}

int Constraint::getConflicts(){
    int numConflicts = 0;
    for (Variable* var:vars){
        for (Variable* otherVar : vars){
            if (*var == *otherVar){
                continue;
            }
            else if (var->getAssignment() == otherVar->getAssignment()){
                numConflicts++;
            }
        }
    }
    return numConflicts;
}

bool Constraint::propagateConstraint(){
    for (Variable* var:vars){
        if (!var->isAssigned())
            continue;
        int varAssignment = var->getAssignment();
        for (Variable* otherVar:vars){
            if (var == otherVar){
//				std::cout<<"continue"<<std::endl;
                continue;
            }
            if (otherVar->size() == 1 && otherVar->getAssignment() == varAssignment){
//				std::cout<<"false"<<std::endl;
				return false;
            }
//			std::cout<<"assign: "<<varAssignment<<" size: "<<otherVar.size();
			if(otherVar->size() == 1)
//				std::cout<<"other: "<<otherVar.getAssignment();
//			std::cout<<std::endl;
            otherVar->removeValueFromDomain(varAssignment);
        }
    }
    return true;
}

bool Constraint::isConsistent(){
    return propagateConstraint();
}

std::string Constraint::toString(){
    std::stringstream ss;
    ss<<"{";
    std::string delim = "";
    for (Variable* v:vars){
        ss<<delim<<v->getName();
        delim = ",";
    }
    ss<<"}";
    return ss.str();
}
