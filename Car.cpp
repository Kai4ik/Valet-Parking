#include "Car.h"
#include <iostream>
using namespace std;

namespace sdds
{
	const int MAX = 3;
	//no-argument constructor which sets Car object to safe invalid empty state
	Car::Car()
	{
		carwash = false;
	}

	//2-argument constructor which sets the properties of the Car object to a given values.
	Car::Car(const char* lic_plate, const char* make_panel) : Vehicle(lic_plate, make_panel)
	{
		carwash = false;
	}

	//overrided read function which reads from file  
	ifstream& Car::read(ifstream& fin)
	{
		if (Vehicle::isCsv() == true)
		{
			//calls read function of Vehicle class with ifstream object as an argument 
			Vehicle::read(fin);
			int zero_or_one = fin.get() - '0';
			if (zero_or_one == 1)
			{
				carwash = true;
			}
			else
			{
				carwash = false;
			}
			fin.ignore(1, '\n');
			return fin;
		}
	}

	//overrided read function
	istream& Car::read(istream& input)
	{
		//checks if object is set to comma separated mode or no. If yes, will do following
		if (Vehicle::isCsv() == true)
		{
			//calls read function of the Vehicle (base) class
			Vehicle::read(input);
			//reads boolean value into the carwash flag
			input >> carwash;
			input.ignore(2000, '\n');
		}
		else
		{
			//if not in comma separated mode, read as follows
			char option [MAX+1];
			bool result = false;
			cout << endl << "Car information entry" << endl;
			Vehicle::read(input);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			while (result == false)
			{
				cin >> option;
				if ((option[0] == 'y' || option[0] == 'Y') && option[1] == '\0')
				{
					result = true;
					carwash = true;
				}
				else if ((option[0] == 'n' || option[0] == 'N') && option[1] == '\0')
				{
					result = true;
					carwash = false;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			}
		}
		return input;
	}

	//overrided write function
	ostream& Car::write(ostream& out) const
	{
		//if object is in an invalid empty state.prints the following
		if (Vehicle::isEmpty() == true)
		{
			out << "Invalid Car Object" << endl;
			return out;
		}
		else
		{
			//checks if object is set to comma separated mode or no. If yes, prints as follows
			if (Vehicle::isCsv() == true)
			{
				out << "C,";
				//calls write function of its base class
				Vehicle::write(out);
				out << carwash << endl;
			}
			else
			{
				//if not in comma separated mode, prints as follows
				out << "Vehicle type: Car" << endl;
				//calls write function of its base class
				Vehicle::write(out);
				if (this->carwash == true)
				{
					out << "With Carwash";
				}
				else
				{
					out << "Without Carwash";
				}
				out << endl;
			}
		}
		return out;
	}
}

