#pragma once
#ifndef SDDS_CAR_H
#define SDDS_CAR_h
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	//Car class which inherits entire structure of Vehicle class
	class Car : public Vehicle
	{
		bool carwash;
	public:
		//constructors
		Car();
		Car(const char* lic_plate, const char* make_panel);

		//functions which overrides functions of Vehicle class
		istream& read(istream& input);
		ostream& write(ostream& out) const;
		ifstream& read(ifstream& fin);
	};
}
#endif // !SDDS_CAR_H