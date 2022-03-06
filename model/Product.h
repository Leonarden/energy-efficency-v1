#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED


#include <string>


enum typeState {
	SOLID=0,LIQUID=1,GAZ=2

};

typedef typeState STATE;



class Product{
public:

Product(string id,string n, double w, double sh, STATE cs, double ct, double cp){
_id= id;	_name = n; _weight = w; _specificHeat = sh; _currentState = cs;
	_currentTemperature = ct; _currentPreasure = cp;

}

virtual ~Product(){}

protected:

    string _id;
    string _name;
	//physical properties
	double _weight; //in Kg
	double _specificHeat;
	STATE _currentState;
	double _currentTemperature;
    double _currentPreasure;

};


#endif // PRODUCT_H_INCLUDED
