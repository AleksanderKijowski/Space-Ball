#pragma once

class Exception : public std::exception
{
	private:
		string _message;
	
	public:
		Exception(string message);

		virtual string ToString();
};
