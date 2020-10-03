#include "ReadWritable.h"

namespace sdds
{
	////no argument constructor which sets the comma separated values flag to false
	ReadWritable::ReadWritable()
	{
		flag = false;
	}

	//query which returns the comma returns comma separated values flag
	bool ReadWritable::isCsv(void) const
	{
		return this->flag;
	}

	//function which sets the comma separated values flag to the incoming value of boolean type 
	void ReadWritable::setCsv(bool value)
	{
		flag = value;
	}

	//helper operators
	istream& operator>>(istream& input, ReadWritable& obj)
	{
		obj.read(input);
		return input;
	}

	ostream& operator<<(ostream& out, const ReadWritable& obj)
	{
		return obj.write(out);
	}
}