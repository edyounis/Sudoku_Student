#include"Variable.hpp"

int Variable::namingCounter = 1;


Variable::Variable(std::vector<int> possible_Values, int row, int col, int block) : domain(possible_Values){
    if (domain.size() == 1){
        modified = true;
        unchangeable = true;
    } 
    r = row;
    c = col;
    b = block;
    name = "v" + std::to_string(namingCounter++);
    oldSize = size();
}

Variable& Variable::operator=(const Variable& other){
	r = other.row();
	c = other.col();
	b = other.block();
	modified = other.isModified();
	name = other.getName();
	domain = other.getDomain();
	oldSize = other.oldSize;
	return *this;
}

void Variable::modify(const Variable& other){
	r = other.row();
	c = other.col();
	b = other.block();
	modified = other.isModified();
	name = other.getName();
	domain = other.getDomain();
	oldSize = other.oldSize;
}

Variable::Variable(const Variable& v) : domain(v.domain){
    r = v.row();
    c = v.col();
    b = v.block();
    modified = v.isModified();
    name = v.getName();
}

bool Variable::operator==(const Variable &other) const{
    return (row() == other.row()) && (col() == other.col()) && (block() == other.block());
}

bool Variable::operator!=(const Variable &other) const{
    return !(*this == other);
}

bool Variable::isChangeable() const{
    return domain.size() != 1;
}

bool Variable::isAssigned() const{
    return size() == 1 ? true : false;
}

bool Variable::isModified() const{
    return modified;
}

void Variable::setModified(bool modified){
    this->modified = modified;
    this->domain.setModified(modified);
}

int Variable::row() const{
    return r;
}

int Variable::col() const{
    return c;
}

int Variable::block() const{
    return b;
}

int Variable::getAssignment() const{
    if (!isAssigned()){
        return 0;
    }
    else{
		if(domain.getValues().size() != 1)
			std::cout<<"ERROR!"<<std::endl;
        return domain.getValues()[0];
    }
}

std::vector<int> Variable::Values() const{
    return domain.getValues();
}

int Variable::size() const{
    return domain.size();
}

Domain Variable::getDomain() const{
    return domain;
}

std::string Variable::getName() const{
    return name;
}

void Variable::assignValue(int val){
    setDomain(Domain(val));
}

void Variable::updateDomain(Domain d){
    methodModifiesDomain();
    
    domain = d;
//	std::cout<<size()<<std::endl;
//	std::cout<<isAssigned()<<std::endl;
    modified = true;
}

void Variable::setDomain(Domain d){
    domain = d;
    modified = true;
}

void Variable::removeValueFromDomain(int val) {
    methodModifiesDomain();
    domain.remove(val);
    modified=domain.isModified();
}

void Variable::methodModifiesDomain(){
    int newSize = size();
    if (oldSize > newSize){
        oldSize = newSize;
    }
    //**********
    //trail.push(this);
}

Domain::iterator Variable::begin(){
    return domain.begin();
}

Domain::iterator Variable::end(){
    return domain.end();
}

std::string Variable::toString(){
    //prints node stats
    std::stringstream ss;
    //StringBuilder sb = StringBuilder();
    std::string sep = "";
    ss<<" Name: "<<name;
    ss<<"\tdomain: {";
    //		sb.append(" Name: "+name);
    //		sb.append("\tdomain: {");
    for(int i = 0; i < domain.getValues().size(); ++i){
        ss<<sep<<domain.getValues()[i];
        sep = ",";
        //sb.append(i + ",");
    }
    ss<<"}";
    return ss.str();
}


Domain::Domain(int value){
    values.push_back(value);
}

Domain& Domain::operator=(const Domain& other){
	values = other.getValues();
	modified = other.isModified();
	return *this;
}
//Domain::Domain(int* values){
//    for(int i = 0; i < values.length; i++){
//        this.values.add(values[i]);
//    }
//}

Domain::Domain(std::vector<int> vals)
{
	values = vals;
}

Domain::Domain(const Domain& d){
    for(int i = 0; i < d.getValues().size(); ++i)
        values.push_back(d.getValues()[i]);
}

std::vector<int> Domain::getValues() const{
    return values;
}

bool Domain::contains(int value) const{
    if(std::find(values.begin(), values.end(), value) != values.end())
	    return true;
    return false;
}

int Domain::size() const{
    return values.size();
}

bool Domain::isEmpty() const{
    return values.empty();
}

/**
 * Returns whether or not the domain has been modified.
 *
 * @return true if the domain has been modified
 */
bool Domain::isModified() const{
    return modified;
}


bool Domain::remove(int value){
    int v = value;
    
    if(std::find(values.begin(), values.end(), value) == values.end())
    	return false;
    
    setModified(true);
    values.erase(std::remove(values.begin(), values.end(), value), values.end());
    return true;
}

void Domain::setModified(bool modified){
    this->modified = modified;
}

bool Domain::equals(Domain d) const{
    return false;
}

std::vector<int>::iterator Domain::begin(){
    return values.begin();
}

std::vector<int>::iterator Domain::end(){
    return values.end();
}

std::string Domain::toString(){
    std::stringstream ss;//new StringBuilder("{");
    ss<<"{";
    std::string delim = "";
    for (int i = 0; i < values.size(); ++i){
        ss<<delim<<values[i];
        delim = ",";
    }
    ss<<"}";
    return ss.str();
}
