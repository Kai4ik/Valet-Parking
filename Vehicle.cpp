#include "Vehicle.h"
#include "ReadWritable.h"
#include <iostream>
#include <string>
#include <string.h>
#pragma warning(disable : 4996)
using namespace std;

namespace sdds
{
	//no-argument constructor which sets Vehicle object to safe invalid empty state
	Vehicle::Vehicle()
	{
		license_plate[0] = '\0';
		make_model = nullptr;
		parking_spot_numb = 0;
	}

	//2-argument constructor which sets the properties of the Vehicle object to a given values and parking spot to zero.
	Vehicle::Vehicle(const char* lic_plate, const char* make_panel)
	{
		//if license plate or make and model are invalid values or pointing to null, object is set into an invalid empty state 
		if (lic_plate == nullptr || make_panel == nullptr || strlen(lic_plate) < 1 || 
			strlen(lic_plate) > 8 || make_panel == 0 || strlen(make_panel) < 2)
		{
			setEmpty();
		}
		else
		{
			parking_spot_numb = 0;
			strcpy(license_plate, lic_plate);
			setMakeModel(make_panel);
		}
	}

	//destructor which prevents from memory leaks
	Vehicle::~Vehicle()
	{
		delete[] make_model;
	}


	//overrided read function
	istream& Vehicle::read(istream& input)
	{
		unsigned int lic_size = 0;
		unsigned int i = 0;
		char lic[9];
		char makeModel[61];
		//first, this function checks if object is set to comma separated mode or no. If yes, will do following
		if (this->isCsv() == true)
		{
			delete[] make_model;
			//reads an integer for parking spot number
			input >> parking_spot_numb;
			//ignores one character for comma delimiter
			input.ignore(1, ',');
			//reads up to 8 characters/comma character for the license plate
			input.getline(lic, 8, ',');
			lic_size = strlen(lic);
			//stores its' value in all uppercase
			for (i = 0; i < lic_size; i++)
			{
				lic[i] = toupper(lic[i]);
			}
			strcpy(license_plate, lic);
			//reads up to 60 characters/comma character for make and model
			input.getline(makeModel, 60, ',');
			//dynamically stores entered by user value in the make and model of the object
			make_model = new char[strlen(makeModel) + 1];
			strcpy(make_model, makeModel);
			////ignores one character for comma delimiter
			input.ignore(1, ',');
		}
		//if not in comma separated mode
		else
		{
			delete[] make_model;
			cout << "Enter Licence Plate Number: ";
			//reads for the license plate
			input.getline(lic, '\n');
			lic_size = strlen(lic);
			//if value entered by user more than 8 symbols or user entered nothing, user will be asked to enter value one more time until a proper value
			while (lic_size > 8 || lic_size <= 0)
			{
				cout << "Invalid Licence Plate, try again: ";
				input.getline(lic,'\n');
				lic_size = strlen(lic);
			}
			//stores value in all uppercase
			for (i = 0; i < lic_size; i++)
				{
					lic[i] = toupper(lic[i]);
				}
			strcpy(license_plate, lic);
			cout << "Enter Make and Model: ";
			//reads for make and model
			input.getline(makeModel, '\n');
			int make_size = strlen(makeModel);
			//if value entered by user more than 60 symbols or less than 2, user will be asked to enter value one more time until a proper value
			while (make_size < 2 || make_size > 60)
			{
				cout << "Invalid Make and model, try again: ";
				input.getline(makeModel, '\n');
				make_size = strlen(makeModel);
			}
			make_model = new char[make_size + 1];
			strcpy(make_model, makeModel);\
			//sets parking spot to zero
			parking_spot_numb = 0;
		}
		//checks if th istream object failed while reading or not. If yes, will set object to an invalid empty state
		if (input.fail() == true)
		{
			setEmpty();
		}
		return input;
	}

	//overrided write function
	ostream& Vehicle::write(ostream& out) const
	{
		//checks if Vehicle object is in invalid empty state or no. If yes, prints the following message 
		if (make_model == nullptr || getParkingSpot() < 0)
		{
			out << "Invalid Vehicle Object" << endl;
		}
		else
		{
			//checks if object is in comma separated mode or no. If yes, prints everything separated by a comma
			if (this->isCsv() == true)
			{
				out << getParkingSpot() << "," << getLicencePlate() << "," << getMakeModel() << ",";
			}
			else
			{
				//if not in comma separated mode, prints in the following order
				out << "Parking Spot Number: ";
				if (parking_spot_numb == 0)
				{
					out << "N/A" << endl;
				}
				else
				{
					out << getParkingSpot() << endl;
				}
				out << "Licence Plate: " << getLicencePlate() << endl;
				out << "Make and Model: " << getMakeModel() << endl;
			}
		}
		return out;
	}
	
	//overrided read function which reads from file
	ifstream& Vehicle::read(ifstream& fin)
	{
		unsigned int i = 0;
		char numb[3];
		char lic[8];
		char makeModel[61];
			delete[] make_model;
			fin.ignore(1, ',');
			fin.getline(numb, 3, ',');
			parking_spot_numb = stoi(numb);
			fin.getline(lic, SIZE + 1, ',');
			unsigned int lic_lenght = strlen(lic);
			//stores value in all uppercase
			for (i = 0; i < lic_lenght; i++)
			{
				lic[i] = toupper(lic[i]);
			}
			strcpy(license_plate, lic);
			fin.getline(makeModel, 60, ',');
			make_model = new char[strlen(makeModel) + 1];
			strcpy(make_model, makeModel);
		//checks if th istream object failed while reading or not. If yes, will set object to an invalid empty state
		if (fin.fail() == true)
		{
			setEmpty();
		}
		return fin;
	}

	//setter function, which sets make and model to
	//a new given value
	void Vehicle::setMakeModel(const char* value)
	{
		if (value != nullptr)
		{
			make_model = new char[strlen(value) + 1];
			strcpy(make_model, value);
		}
		else
		{
			setEmpty();
		}
	}

	//setter function, which sets parking spot number to a new given value
	void Vehicle::setParkingSpot(int park_spot)
	{
		if (park_spot != 0)
		{
			parking_spot_numb = park_spot;
		}
		else
		{
			setEmpty();
		}
	}

	//operator which compares the license plate of the Vehcile object with a license plate value
	bool Vehicle::operator==(string str) const
	{
		unsigned int count = 0;
		unsigned int i;
		//if license plate of vehicle or given license plate value is invalid, function returns false
		if (this->isEmpty() == true || str[0] == '\0')
		{
			return false;
		}
		else
		{
			if (strlen(this->license_plate) != str.length())
			{
				return false;
			}
			else
			{
				//because the comparison is not case sensitive I compare both values in lowercase
				for (i = 0; i < strlen(this->license_plate); i++)
				{
					if (tolower(this->license_plate[i]) == tolower(str[i]))
					{
						count++;
					}
				}
				//returns true if values are identical and false if not
				if (count == strlen(this->license_plate))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}

	//operator that compares 2 Vehicle objects
	bool Vehicle::operator==(const Vehicle& sec_obj) const
	{
		unsigned int count = 0;
		unsigned int i = 0;
		//if license plate of vehicle or given license plate value is invalid, function returns false
		if (this->isEmpty() == true || sec_obj.isEmpty() == true)
		{
			return false;
		}
		else
		{
			if (strlen(this->license_plate) != strlen(sec_obj.license_plate))
			{
				return false;
			}
			else
			{
				//because the comparison is not case sensitive I compare both values in lowercase
				for (i = 0; i < strlen(this->license_plate); i++)
				{
					if (tolower(license_plate[i]) == tolower(sec_obj.license_plate[i]))
					{
						count++;
					}
				}
				//returns true if values are identical and false if not
				if (count == strlen(this->license_plate))
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}


	//getter function which returns read only address of the make and model
	const char* Vehicle::getMakeModel() const
	{
		return make_model;
	}

	//getter function which returns parking spot number
	int Vehicle::getParkingSpot() const
	{
		return parking_spot_numb;
	}

	//getter function which returns read only address of the license plate
	const char* Vehicle::getLicencePlate() const
	{
		return &license_plate[0];
	}

	//function which checks if vehicle is in an invalid empty state or no
	bool Vehicle::isEmpty() const
	{
		if (make_model == nullptr || license_plate == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//function which sets Vehicle to an invalid empty state
	void Vehicle::setEmpty()
	{
		license_plate[0] = '\0';
		make_model = nullptr;
		parking_spot_numb = 0;
	}
}