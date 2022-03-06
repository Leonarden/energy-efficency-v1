#ifndef TECHNICALPROPERTIES_H_INCLUDED
#define TECHNICALPROPERTIES_H_INCLUDED

#include <string>
#include <vector>


class TechnicalProperties {

public:

vector<double> * _specificHeatCapacity;
vector<double> * _criticalTemperature;
vector<double> * _latencyHeat;
vector<string> * _formula;
vector<double> * _molarity;
vector<double> * _electrolysis;

};


#endif // TECHNICALPROPERTIES_H_INCLUDED
