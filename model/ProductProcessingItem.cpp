
#include "ProductProcessingItem.h"
/*

ProcessedProduct::ProcessedProduct(string id,string n, double w, double sh, STATE cs, double ct, double cp){

	 Product::
	_id= id;	_name = n; _weight = w; _specificHeat = sh; _currentState = cs;
		_currentTemperature = ct; _currentPreasure = cp;

	_energyPhases = new vector<double>;
	_phases = new vector<STATE>;
	_currentIndex = -1;
	_energyRequired = 0.0;


}
*/
double ProcessedProduct::getTotalEnergy(int who){
	double v = 0.0;
	vector<double> *energy;
	if(!who)
		energy = _simulation->_energyRequired;
	else
		energy = _simulation->_energyConsumed;

	vector<double>::iterator it;

	for(it=energy->begin();it<energy->end();it++)
		v = v + (*it);
	return v;
}

double ProcessedProduct::getTotalEnergyRequired(){
	return getTotalEnergy(0);
}
double ProcessedProduct::getTotalEnergyConsumed(){
	return getTotalEnergy(1);
}

int  ProcessedProduct::insTransitionParams(STATE s, double * ps){

	int r = 0;

	_transitionParams->insert(pair<STATE,double*>(s,ps));

	return r;
}

void ProcessedProduct::toState(STATE target){
	double rt1=0,t1=0,t2=0,merror=0;
	try{
		t1 = _transitionParams->at(target)[0];
		merror = _transitionParams->at(target)[1];
		rt1 = t1 + merror;
		if(rt1<0){

			t2 =-1* (rand()% -1*(rt1));

		}else if(rt1>0){
			t2 = (rand()% 1*(rt1));
		}
		t2 = t2 + t1;
		_deltaTemp = _currentTemperature - t2;
		//if(_deltaTemp<0) _deltaTemp = -1*_deltaTemp;
		_currentTemperature = t2;

		_energyRequired = _deltaTemp * _specificHeat * _weight;

		_energyPhases->push_back(_energyRequired);
	    _phases->push_back(_currentState);
	    _currentState = target;

	    _currentIndex++;

	}catch(exception e){
		cout<< "Something went wrong : #->" << e.what() << endl;
	}

}

void ProcessedProduct::transitionDeltaTemp(){
vector<double> * tTemperature = _simulation->_targetTemperature;
int  idx = (_simulation->_tTempIdx);
double ex = 0.0;
int numTransition = (this->_numTransition>=0?this->_numTransition:1);
int i=0;
int j = idx;
_energyRequired = 0.0;

	try{
		if((tTemperature->size()- idx)< numTransition)
			throw -10000;
		while(i<numTransition){
			ex = energyDeltaTemp(tTemperature->at(j), tTemperature->at(j+1));
			_energyRequired =  ex;
			_simulation->_energyRequired->push_back(_energyRequired);
			_energyConsumed = computeEnergyConsumedKw(j);
			_simulation->_energyConsumed->push_back(_energyConsumed);
			j++; i++;
		}
		//updating
		_simulation->_tTempIdx = j;

        _numTotalTransitions = _numTotalTransitions + j;
		//log result;

	}catch(exception e){
		cerr << " Exception in transitionDeltaTemp "<< e.what() << endl;
	}

	return;
}

/*
 * Input temperatures are in Celsius

 */
double ProcessedProduct::energyDeltaTemp(double fromTemp, double toTemp){

	double energyR = 0.0;

	vector<double> * criticalT = _technicalProps->_criticalTemperature;
	vector<double> * specificHC = _technicalProps->_specificHeatCapacity;
	vector<double> * latencyH = _technicalProps->_latencyHeat;
	vector<double> * equationTerms = new vector<double>();
	double qx=0.0, deltaTx = 0.0;
	double ft,tt;
	if(fromTemp>toTemp) {
      ft = toTemp;
      tt = fromTemp;
	}
	else{
      ft = fromTemp;
      tt = toTemp;
	}

	int j = (int)(  specificHC->size()-1);
	int Mxi = (int) criticalT->size()-1;
	int i = 0;
	 deltaTx = tt - ft;

	while( i<=j && i<=Mxi ) {



		 if(criticalT->at(Mxi-i)>tt)
					j--;


		if(tt> ft && (int)(i)>= (int)j){

					deltaTx = (tt - ft);
					qx = (specificHC->at(j)) * deltaTx * this->_weight;
					//we add here latencyHeat for any of the states:solid, liquid, gaz
					//qx =+  (latencyH->at(i) * this->_weight);
					equationTerms->push_back(qx);
					break;

		}


		 if(ft <criticalT->at(i) && ft<tt){
		 			//q1
		 			deltaTx = (criticalT->at(i) - ft);
		 			qx = (specificHC->at(i)) * deltaTx * this->_weight;
		 			//we add here latencyHeat for any of the states:solid, liquid, gaz
		 			qx = qx +  (latencyH->at(i) * this->_weight);
		 			equationTerms->push_back(qx);
		 			ft = criticalT->at(i);
		 }

		 i++;

	}
    vector<double>::iterator it;

    for(it= equationTerms->begin();it<equationTerms->end();++it){
    	energyR = energyR + (*it);
    }

return energyR;

}

double ProcessedProduct::computeEnergyConsumedKw(int index){
	double  ekw = 0.0;
	try{
        boost::posix_time::time_duration dur = _simulation->_targetTempDuration->at(index);
		double hours = dur.hours() + (dur.minutes()/60) + (dur.seconds()/3600);

	   if(hours > 0.0001) //maintaining that energy * number of hours
		ekw = _energyRequired *(hours)/  3600; /*passing from KJ/H to KW/H */

	}catch(exception e){

		cout << "Exception calculating Kw" << e.what() << endl;

	}
	return ekw;
}




void ProcessedProduct::toSolid() {

	toState(SOLID);
}
void ProcessedProduct::toLiquid() {
	toState(LIQUID);
}
void ProcessedProduct::toGaz() {

	toState(GAZ);
}
