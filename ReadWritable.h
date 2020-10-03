#pragma once
#ifndef SDDS_READWRITABLE_H
#define SDDS_READWRITABLE_H

#include <iostream>
using namespace std;

namespace sdds
{
	//class which forces Read and Write capability to all its derived classes in two different ways - comma separated values or screen format. 
	class ReadWritable
	{
		//comma separated values flag
		bool flag;
	public:
		ReadWritable(); //no argument constructor
		bool isCsv(void) const;
		//function which sets the flag to the incoming bool value
		void setCsv(bool value);

		//2 pure virtual functions to read and write object (in derived class implementations)
		virtual istream& read(istream& input) = 0;
		virtual ostream& write(ostream& out) const = 0;

		//pure virtual function to read from file
		virtual ifstream& read(ifstream& fin) = 0;

		//virtual destructor with empty body
		virtual ~ReadWritable() {};
	};
	//helper insertion and extractions operator overloads for istream and ostream 
	istream& operator>> (istream& input, ReadWritable& obj);
	ostream& operator<< (ostream& out, const ReadWritable& obj);
}
#endif // !SDDS_READWRITABLE_H