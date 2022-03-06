#ifndef  PROCESSINGITEM_H_
#define PROCESSINGITEM_H_

/*
#include <boost/algorithm/string/replace.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include<iostream>
#include <cassert>
#include <exception>
#include <fstream>
#include <sstream>
*/
#include <map>
#include<vector>
#include <regex>
#include<string>
#include<stdlib.h>
#include<ctime>
#include<cmath>

#include "Product.h"
#include "Simulation.h"
#include "TechnicalProperties.h"


using namespace std;





class ProductProcessingItem : public Product, public ProductProcessingElement {

public:
ProductProcessingItem();
ProductProcessingItem(string id,string n, double w, double sh, STATE cs, double ct, double cp):Product(id,n,w,sh,cs,ct,cp){
	_energyPhases = new vector<double>;
	_phases = new vector<STATE>;
	_currentIndex = -1;
	_energyRequired = 0.0;


}

virtual ~ProductProcessingItem(){}

double getEnergyRequired() { return _energyRequired; }
double getEnergyConsumed() { return _energyConsumed; }

virtual void toSolid();
virtual void toLiquid();
virtual void toGaz();

void setNumTransition(int numT) { _numTransition = numT; }

//executes specified num of temperature transitions and computes the total energy required
//throws exception if numTransitions> _targetTemperature->size()-tTempIdx (current transition index)
virtual void transitionDeltaTemp();

virtual void transitionDeltaPre(){}

virtual void transitionDeltaVol(){}


void setTransitionParams(map<STATE,double*> * trp){
	_transitionParams = trp;
}
int insTransitionParams (STATE s, double *ps);
double getTotalEnergyConsumed();
double getTotalEnergyRequired();

//getters and setters
//protected:
virtual void toState(STATE taget);

virtual double energyDeltaTemp(double fromTemp, double toTemp);

double computeEnergyConsumedKw(int index);

double getTotalEnergy(int who);

private:
	time_t _date_in;
	time_t _date_out;
    double _deltaTemp; //variation from last temperature to current one
    double _deltaPreasure; //variation from last preasure to current one

    double _energyRequired; //in last transition
    double _energyConsumed;
    int _numTransition = 0;
    int _numTotalTransitions = 0;
    vector<double> * _energyPhases;  //FIxme
    vector<STATE> * _phases;
    int _currentIndex;
    //ie:water= SOLID,{0,-50}
    //This means from 0 to margin err. -50, toSolid()= computenewtemperature: ( -50-0 ), setDelta
   //

    map<STATE,double*> *_transitionParams;

    Simulation * _simulation;
    TechnicalProperties * _technicalProps;


};



#endif
