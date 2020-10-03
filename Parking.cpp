/* Student name: Kairat Orozobekov
Student email: korozobekov@myseneca.ca
Student id: 104 998 190
Final Project OOP244
I have done all the coding by myself and only copied the code that my professor provided to complete this program */
#include "Parking.h"
#include "Vehicle.h"
#include "Car.h"
#include "Menu.h"
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
const int MAX = 3;

namespace sdds
{
	//function which checks if object of Parking type is in an invalid state or no
	bool Parking::isEmpty() const
	{
		if (this->filename == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//functions which just prints the following text and counts how many available spots left
	void Parking::status() const
	{
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "*****  Available spots: " << setw(4) << left << numb_spots-parked_vehicles << " *****" << endl;
	}


	void Parking::park_vehicle()
	{
		//checks is there are any available spots or no. If no, prints the following
		if (numb_spots - parked_vehicles == 0)
		{
			cout << "Parking is full" << endl;
		}
		//if there is still available spots, does the following
		else
		{
			//displays submenu Vehicle selection menu and based om user's decision does the following
			switch (submenu_obj.run())
			{
				//creates Vehicle pointer
				Vehicle* veh_obj;
				//if user selected first option
			case 1:
				//creates dynamic instance of Car in pointer
					veh_obj = new Car();

					//sets it not to be in comma separated mode
					veh_obj->setCsv(false);

					//calls read function which takes ifstream object as an argument 
					veh_obj->read(cin);

					//searches through Parking spots array
					for (int i = 0; i < numb_spots; i++)
					{
						//finds the first available spot and sets it to the vehicle pointer
					if (park_spots[i] == nullptr)
					{
						park_spots[i] = veh_obj;

						//sets parking spot of object to the spot number it was parked + 1 (because indexs starts with 0)
						park_spots[i]->setParkingSpot(i + 1);
						//prints the following
						cout << endl << "Parking Ticket" << endl;
						//calls write function 
						park_spots[i]->write(cout);		
						parked_vehicles++;
						break;
						}
				}
				cout << endl;
				break;
			case 2:
				//the same steps but creates dynamic instance of Motorcycle in pointer
				veh_obj = new Motorcycle();
				veh_obj->setCsv(false);
				veh_obj->read(cin);
				for (int i = 0; i < numb_spots; i++)
				{
					if (park_spots[i] == nullptr)
					{
						park_spots[i] = veh_obj;
						park_spots[i]->setParkingSpot(i + 1);
						cout << endl << "Parking Ticket" << endl;
						park_spots[i]->write(cout);					
						parked_vehicles++;
						break;
					}
				}
				cout << endl;
				break;
				//if user selects 3rd option (by default) parking of the object will be cancelled and following message will be printed
			default:
				cout << "Parking cancelled" << endl;
				break;
			}
		}
	}

	//function which returns asked by user vehicle
	void Parking::return_vehicle()
	{
		bool result = false;
		int i = 0;
		char temp_lic_plate[SIZE + 1];
		cout << "Return Vehicle" << endl;
		cout << "Enter Licence Plate Number: ";

		//receives license plate value entered by user
		cin.get(temp_lic_plate, SIZE + 1,'\n');
		int lic_size = strlen(temp_lic_plate);
		for (i = 0; i < lic_size; i++)
		{
			temp_lic_plate[i] = toupper(temp_lic_plate[i]);
		}
		while (lic_size > 8 || lic_size < 1)
		{
			cout << "Invalid Licence Plate, try again: ";
			cin.get(temp_lic_plate, SIZE+1, '\n');
			for (i = 0; i < lic_size; i++)
			{
				temp_lic_plate[i] = toupper(temp_lic_plate[i]);
			}
			lic_size = strlen(temp_lic_plate);
		}

		//searches through parked vehicles for a matching license plate
		for (i = 0; i < numb_spots; i++)
		{
			//if finds, prints Vehicle object and all information about it
			if (park_spots[i] !=nullptr) {
				if (strcmp(park_spots[i]->getLicencePlate(), temp_lic_plate) == 0)
				{
					cout << endl << "Returning: " << endl;
					park_spots[i]->setCsv(false);
					park_spots[i]->write(cout);
					cout << endl;

					//deletes it from the memory and sets to nullptr
					delete park_spots[i];
					park_spots[i] = nullptr;

					//decreases amount of parked vehicles on 1
					parked_vehicles--;
					result = true;
					break;
				}
			}
		}

		//if not found, prints the following
		if (result == false)
		{
			cout << endl << "License plate " << temp_lic_plate << " Not found" << endl << endl;;
		}
	}


	//functons which prints all parked vehicles and information about them
	void Parking::list_parked() const
	{
		cout << "*** List of parked vehicles ***" << endl;

		//goes through all parking spot elements up to number of spots
		for (int i = 0; i < numb_spots; i++)
		{
			//prints all that are not null
			if (this->park_spots[i]!= nullptr)
			{
				park_spots[i]->setCsv(false);
				park_spots[i]->write(cout);
				//separates them with such line
				cout << "-------------------------------" << endl;
			}
		}
	}

	//fucntion which closes parking in case of end of the day
	bool Parking::close_parking()
	{
		//checks if parking is in an invalid empty state. If yes, prints the following 
		if (this->isEmpty() == true)
		{
			cout << "Closing Parking" << endl;
			return true;
		}
		else
		{
			//if not empty, prints a confirmation message for the user
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl << "Are you sure? (Y)es/(N)o: ";
			char option[MAX + 1];
			bool result = false;
			bool exit = false;
			while (result == false)
			{
				cin >> option;
				if ((option[0] == 'y' || option[0] == 'Y') && option[1] == '\0')
				{
					result = true;
					exit = true;
				}
				else if ((option[0] == 'n' || option[0] == 'N') && option[1] == '\0')
				{
					result = true;
					exit = false;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
			}

			//if user's respond is yes, does the following
			if (exit == true)
			{
				cout << "Closing Parking" << endl;

				//goes through all the parked vehicles
				for (int i = 0; i < numb_spots; i++)
				{
					if (park_spots[i] != nullptr)
					{
						//prints the following message
						cout << endl << "Towing request" << endl;
						cout << "*********************" << endl;
						//prints Vehicle object and skips a line
						park_spots[i]->write(cout);
						cout << endl;

						//deletes object and sets parking spot to null
						delete park_spots[i];
						park_spots[i] = nullptr;
					}
				}
				return true;
			}

			//if user's respond is no, prints the following message
			else
			{
				cout << "Aborted!" << endl;
				return false;
			}
		}
	}

	//function which exits the program
	bool Parking::exit_park_app() const
	{
		char option[MAX + 1];
		bool result = false;
		bool exit = false;

		//prints a confirmation message for the user, waits for user's respond and does accordingly
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";
		while (result == false)
		{
			cin >> option;
			if ((option[0] == 'y' || option[0] == 'Y') && option[1] == '\0')
			{
				result = true;
				exit = true;
			}
			else if ((option[0] == 'n' || option[0] == 'N') && option[1] == '\0')
			{
				result = true;
				exit = false;
			}
			else
			{
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
			}
		}
		return exit;
	}

	//function that reads vehicle records from the datafile
	bool Parking::load()
	{
		//checks if parking object is in an invalid empty state or no. If no, does the following
		if (this->isEmpty() == false)
		{
			ifstream test_file(this->filename);
			//checks if the opening of the file was successful or no. If yes, does the following
			if (test_file || isEmpty() == true)
			{
				while (parked_vehicles < numb_spots)
				{
					//creates vehicle pointer 
					Vehicle* vehicle_obj = nullptr;
					
					//reads one character from the file
					char readed_char = test_file.get();

					//stores it in uppercase
					readed_char = toupper(readed_char);

					//checks if file ends or no. If yes, deallocates the vehicle
					if (test_file.eof() == true)
					{
						delete[] vehicle_obj;
						break;
					}
					switch (readed_char)
					{
					case 'C':
						//creates dynamic instance of Car in pointer
						vehicle_obj = new Car();
						vehicle_obj->setCsv(true);
						
						//calls the read function which takes iftream object 
						vehicle_obj->read(test_file);
						break;
					case 'M':
						//creates dynamic instance of Car in pointer
						vehicle_obj = new Motorcycle();
						vehicle_obj->setCsv(true);

						//calls the read function which takes iftream object
						vehicle_obj->read(test_file);
						break;
					case ',':
						//if row was empty, it means there is just commas, that is why it ignores till new line
						vehicle_obj = nullptr;
						test_file.ignore('\n');
						break;
					default:
						return false;
					}

					//if object is empty, deallocates the vehicle
						if (vehicle_obj == nullptr)
						{
							delete [] vehicle_obj;
						}

						//if object is not empty, saves the vehicle pointer in the element of the parking spot array which matches to the parking spot of vehicle - 1 
						if (vehicle_obj != nullptr)
						{
							int index = vehicle_obj->getParkingSpot() - 1;
							park_spots[index] = vehicle_obj;

							//adds one vehicle to amount of parked vehicles
							parked_vehicles++;
						}
					}
				return true;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
		
	//function which saves all vehicles into datafile
	void Parking::save() const
	{
		//if parking is not empty, does the following
		if (isEmpty() == false)
		{
			//if program is going to be exited (not closed), prints the following message
			if (close_or_exit == true)
			{
				cout << "Exiting program!" << endl;
			}
			ofstream output(filename);

			//if file was opened successfully, does the following
			if (output)
			{

				//goes through all the elements of the parking spots 
				for (int k = 0; k < numb_spots; k++)
				{

					//all spots that are not null, saves the vehicles pointed by them in the data file
					if (park_spots[k] != nullptr)
					{
						if (park_spots[k]->getMakeModel() != nullptr)
						{
							{
								//sets object into comma separated mode
								park_spots[k]->setCsv(true);
								//calls write function which takes ofstream object as an argument
								park_spots[k]->write(output);
							}
						}
					}
				}
			}
		}

		//cleans buffer
		while ((getchar()) != '\n');
	}

	Parking::Parking(const char* data_file, int noOfspots) : menu_obj("Parking Menu, select an action:"), submenu_obj ("Select type of the vehicle:", 1)
	{
		if (data_file == nullptr || data_file[0] == '\0' || noOfspots>MAX_NUM_PARKING_SPOTS || noOfspots<10)
		{
			filename = nullptr;
		}
		else
		{
			filename = new char[strlen(data_file) + 1];
			strcpy(filename, data_file);
			numb_spots = noOfspots;
			for (int i = 0; i < numb_spots; i++)
			{
				park_spots[i] = nullptr;
			}
		}
		if (load() == true)
		{
			
			menu_obj << "Park Vehicle" << "Return Vehicle" << "List Parked Vehicles" << "Close Parking (End of day)" << "Exit Program";
			submenu_obj << "Car" << "Motorcycle" << "Cancel";
		}
		else
		{
			cout << "Error in data file" << endl;
			filename = nullptr;
		}
	}


	//no-argument constructor
	Parking::Parking()
	{
		for (int l = 0; l < numb_spots; l++)
		{
			park_spots[l] = nullptr;
		}
		numb_spots = 0;
		delete [] filename;
		filename = nullptr;
		
	}


	//destructor which calls save function and prevents from memory leaks
	Parking::~Parking()
	{
		save();
		delete[] filename;
		filename = nullptr;
		for (int i = 0; i < numb_spots; i++)
		{
			delete park_spots[i];
			park_spots[i] = nullptr;
		}
	}

	//function which runs whole parking application
	int Parking::run()
	{
		if (isEmpty() == false)
		{
			bool result = false;
			while (result == false)
			{
				status();
				switch (menu_obj.run())
				{
				case 1:
					park_vehicle();
					break;
				case 2:
					return_vehicle();
					break;
				case 3:
					list_parked();
					break;
				case 4:
					if (close_parking() == true)
					{
						close_or_exit = false;
						result = true;
					}
					break;
				case 5:
					if (exit_park_app() == true)
					{
						close_or_exit = true;
						result = true;
					}
					break;
				}
			}
			return 0;
		}
		else
		{
			return 1;
		}
	}
}