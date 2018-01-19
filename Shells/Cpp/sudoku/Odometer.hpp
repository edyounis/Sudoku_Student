#ifndef ODOMETER_HPP
#define ODOMETER_HPP

#include<iostream>
#include<string>
#include<stdexcept>
#include<algorithm>

const std::string ODOMETER[] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

int odometerToInt(std::string value);
	
std::string intToOdometer(int num);

#endif
