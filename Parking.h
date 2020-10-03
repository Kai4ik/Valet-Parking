#pragma once
#ifndef SDDS_PARKING_H
#define SDDS_PARKING_H
#include <iostream>
#include <string>
#include "Menu.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Vehicle.h"
using namespace std;
#pragma warning(disable : 4996)

namespace sdds
{
	const int MAX_NUM_PARKING_SPOTS = 100;
	class Parking
	{
		char* filename;
		int numb_spots;
		int parked_vehicles = 0;
		bool close_or_exit = false;
		Menu menu_obj;
		Menu submenu_obj;
		Vehicle* park_spots[MAX_NUM_PARKING_SPOTS];

		//private member functions
		bool isEmpty() const;
		void status() const;
		void park_vehicle();
		void  return_vehicle();
		void list_parked() const;
		bool close_parking();
		bool exit_park_app() const;
		bool load();
		void save() const;

		//copy constructor and assignment operator are denied in Vehicle class - means object of Vehicle type can not be copied or assigned to another Parking object
		Parking(const Parking& park_obj) = delete;
		Parking& operator=(const Parking& obj) = delete;

	public:
		//constructors and destructor
		Parking(const char* data_file, int noOfSpots);
		Parking();
		~Parking();
		int run();
	};
}
#endif // !SDDS_PARKING_H
