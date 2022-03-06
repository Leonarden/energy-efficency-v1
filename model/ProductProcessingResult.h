
#ifndef  PROCESSINGRESULT_H_
#define PROCESSINGRESULT_H_


class <typename T>
class ProductProcessingResult {
public:
    virtual ~ProductProcessingResult(){}
    T getValue() {}

protected:

    vector<T>* _value; /* we may have more than 1 result, defaulting in ->at(0) */

    T _deviationrate; /* given boundaries between target value and computed we calculate deviation -10%, 25%...*/
    double _def_dev_efficiency; /* 1..0 */
    time_t _started;
    time_t ended;

};

/*
class SimulationCostsResult: public SimResult<double> {
public:
    virtual ~SimulationCostsResult() {}

protected:


};


class SimulationPhysicsResult: public SimResult<double> {
public:
    virtual ~SimulationPhysicsResult() {}
protected:

};
template<typename T>
class Params {
public:

protected:

 T _maxvalue;
 T _minvalue;
 string unit;
 long _periodoftime;
 string _sim_unit; // define which unit will be used: KJ, Kw, Kcal.../h

};

*/
