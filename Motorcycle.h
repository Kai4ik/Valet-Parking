#pragma once
#ifndef SDDS_MOTORCYCLE_H
#define SDDS_MOTORCYCLE_h
#include "Vehicle.h"
using namespace std;

namespace sdds
{
	//Motorcycle class which inherits entire structure of Vehicle class
	class Motorcycle : public Vehicle
	{
		bool sidecar;
	public:
		//constructors
		Motorcycle();
		Motorcycle(const char* lic_plate, const char* make_panel);

		//functions which overrides functions of Vehicle class
		istream& read(istream& input);
		ostream& write(ostream& out) const;
		ifstream& read(ifstream& fin);
	};
}
#endif // !SDDS_MOTORCYCLE_H