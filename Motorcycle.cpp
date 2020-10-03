#include "Motorcycle.h"
#include <iostream>
using namespace std;

namespace sdds
{
	const int MAX = 3;
	//no-argument constructor which sets Motorcycle object to safe invalid empty state
	Motorcycle::Motorcycle()
	{
		sidecar = false;
	}

	//2-argument constructor which sets the properties of the Motorcycle object to a given values.
	Motorcycle::Motorcycle(const char* lic_plate, const char* make_panel) : Vehicle(lic_plate, make_panel)
	{
		sidecar = false;
	}

	//overrided read function
	istream& Motorcycle::read(istream& input)
	{
		//checks if object is set to comma separated mode or no. If yes, will do following
		if (Vehicle::isCsv() == true)
		{
			//calls read function of the Vehicle (base) class
			Vehicle::read(input);
			//reads boolean value into the sidecar flag
			input >> sidecar;
			input.ignore(2000, '\n');
		}
		else
		{
			//if not in comma separated mode, read as follows
			char option [MAX+1];
			bool result = false;
			cout << endl << "Motorcycle information entry" << endl;
			Vehicle::read(input);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			while (result == false)
			{
				cin >> option;
				if ((option[0] == 'y' || option[0] == 'Y') && option[1] == '\0')
				{
					result = true;
					sidecar = true;
				}
				else if ((option[0] == 'n' || option[0] == 'N') && option[1] == '\0')
				{
					result = true;
					sidecar = false;
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
	ostream& Motorcycle::write(ostream& out) const
	{
		//if object is in an invalid empty state.prints the following
		if (Vehicle::isEmpty() == true)
		{
			out << "Invalid Motorcycle Object" << endl;
			return out;
		}
		else
		{
			//checks if object is set to comma separated mode or no. If yes, prints as follows
			if (Vehicle::isCsv() == true)
			{
				out << "M,";
				//calls write function of its base class
				Vehicle::write(out);
				out << sidecar << endl;
			}
			else
			{
				//if not in comma separated mode, prints as follows
				out << "Vehicle type: Motorcycle" << endl;
				//calls write function of its base class
				Vehicle::write(out);
				if (this->sidecar == true)
				{
					out << "With Sidecar";
				}
				else
				{
					out << "Without Sidecar";
				}
				out << endl;
			}
		}
		return out;
	}


	//overrided read function which reads from file  
	ifstream& Motorcycle::read(ifstream& fin)
	{
		if (Vehicle::isCsv() == true)
		{
			//calls read function of Vehicle class with ifstream object as an argument 
			Vehicle::read(fin);
			int zero_or_one = fin.get() - '0';
			if (zero_or_one == 1)
			{
				sidecar = true;
			}
			else
			{
				sidecar = false;
			}
			fin.ignore(1, '\n');
			return fin;
		}
	}
}

