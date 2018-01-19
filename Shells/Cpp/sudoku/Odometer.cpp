#include"Odometer.hpp"

int odometerToInt(std::string value) {
    int retVal = 0;
    const std::string* found = std::find(std::begin(ODOMETER), std::end(ODOMETER), value);
    if(found != ODOMETER + 36){
        retVal = found - ODOMETER;
    } else {
        std::cout<<"odometerToInt failed. Invlaid value "<<value<<"Replaced with 0"<<std::endl;
        retVal = 0;
    }
    return retVal;
}

std::string intToOdometer(int num){
    std::string retVal;
    try{
        retVal = ODOMETER[num];
    }catch(const std::out_of_range& oor){
        std::cout<<"intToOdometer failed. Invalid number "<<num <<" Replaced with 0"<<std::endl;
        retVal = "0";
    }
    return retVal;
}
