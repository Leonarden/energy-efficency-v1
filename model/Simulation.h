#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <string>
#include <vector>
#include "ProductProcessingElement.h"



using namespace std;

using namespace boost::date_time;
//using  boost::posix_time;
using namespace boost::gregorian;

class Simulation {


public:
	long _id;
	ProductProcessingElement * _productProcessedElem;

	vector<double> * _energyRequired; //OUT:at every step of simulation there will result a value of energy req.

	vector<double> * _energyConsumed; //OUT:at every step of simulation there will result a value of energy consumed in KW

	vector<boost::posix_time::time_duration> * _targetTempDuration;

	vector<double> * _percentages; //OUT: Resulting of simulation the rate of consumption of total energy ie: 30% or -15%
								  //
	vector<double> * _targetTemperature; //IN:specified temperature transitions 0 to N in Celsius
    vector<boost::posix_time::ptime> * _targetTempDatetime;

	int  _tTempIdx;
    int _tPreIdx;
    int  tVolIdx; // current vector indexes for each target state modification
	vector<double> * _targetPreasure;  //IN(optional): specified preasure transitions
	vector<double> * _targetVolume; //IN(optional):


};




#endif // SIMULATION_H_INCLUDED
