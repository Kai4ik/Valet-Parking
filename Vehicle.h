#pragma once
#ifndef SDDS_VEHICLE_H
#define SDDS_VEHICLE_H
#include <iostream>
#include <fstream>
#include "ReadWritable.h"
using namespace std;
//maximum size of license plate
const int SIZE = 8;

namespace sdds
{
	//class Vehicle which is derived from ReadWritable class
	class Vehicle : public ReadWritable
	{
		//license plate variable which could be 1 up to 8 characters 
		char license_plate[SIZE + 1];

		//make and model variable that cannot be a null address and can not be empty
		char* make_model;

		//parking spot variable which can be 0 or positive integer number
		int parking_spot_numb;

	//functions with protected access - which means only derived classes have access to these functions
	protected:
		void setEmpty();
		bool isEmpty() const;
		void setMakeModel(const char* value);

	public:
		//copy constructor and assignment operator are denied in Vehicle class - means object of Vehicle type can not be copied or assigned to another Parking object
		Vehicle(const Vehicle& obj) = delete;
		Vehicle& operator=(const Vehicle& item) = delete;

		//constructors and destrcutor 
		Vehicle();
		Vehicle(const char* lic_plate, const char* make_panel);
		~Vehicle();

		//member functions and operator overloads
		const char* getMakeModel() const;
		const char* getLicencePlate() const;
		int getParkingSpot() const;
		void setParkingSpot(int park_spot);
		bool operator==(const Vehicle& sec_obj) const;
		bool operator==(string str)const;

		//functions which overrides functions of ReadWritable class
		istream& read(istream& input);
		ostream& write(ostream& out) const;
		ifstream& read(ifstream& fin);

	};
}
#endif // !SDDS_VEHICLE_H