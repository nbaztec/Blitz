/*
 * Log.hpp
 *
 *  Created on: Oct 4, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

class LogManager
{
private:
	std::ostream* _c;
	std::ofstream* _f;
	bool _file;
	bool _single;
	
protected:
	std::ostream& out() const
	{
		if(this->_file)
			return *(this->_f);
		else
			return *(this->_c);
	}

public:	
	LogManager()
	{
		this->_c = &std::cout;
		this->_file = false;
		this->_single = false;
	}
	
	LogManager(const char* file)
	{
		this->_f = new std::ofstream(file, std::ios::out);		
		if(this->_f != NULL)
			this->_file = true;
		else
		{
			this->_c = &std::cout;
			this->_file = false;
		}
		this->_single = false;
	}

	~LogManager()
	{
		if(this->_file)
		{			
			if(this->_f != NULL)
				this->_f->close();
			delete this->_f;
		}
		
	}

	inline LogManager& newline()
	{
		this->out() << std::endl;
		return *this;
	}

	template<typename T>
	friend const LogManager& operator << (const LogManager& log, const T& obj);
	
	template<typename T>
	inline const LogManager& println(const T& value) const
	{
		this->out() << value << std::endl;
		return *this;
	}
	
	inline const LogManager& println(const bool& value) const
	{
		this->out() << (value? "True" : "False") << std::endl;
		return *this;
	}

	template<typename T>
	inline const LogManager& print(const T& value) const
	{
		return this->print(value, 0, ' ');
	}
	
	template<typename T>
	inline const LogManager& print(const T& value, const int& w) const
	{		
		return this->print(value, w, ' ');
	}

	template<typename T>
	inline const LogManager& print(const T& value, const int& w, const char& fill) const
	{		
		if(w > 0)
			this->out() << std::setfill(fill) << std::setw(w) << std::right << value;
		else
			this->out() << std::setfill(fill) << std::setw(-w) << std::left << value;		
		return *this;
	}
	
	inline const LogManager& print(const bool& value, const int& w, const char& fill) const
	{		
		if(w > 0)
			this->out() << std::setfill(fill) << std::setw(w) << std::right << (value? "True" : "False");
		else
			this->out() << std::setfill(fill) << std::setw(-w) << std::left << (value? "True" : "False");		
		return *this;
	}

	void setSingleLine(const bool& value)
	{
		this->_single = value;
	}

	bool isSingleLine()
	{
		return this->_single;
	}

	// Debug Functions
	template<typename T>
	inline const LogManager& errorln(const T& value) const
	{
		this->out() << "[ERROR] ";
		return this->println(value);
	}

	template<typename T>
	inline const LogManager& error(const T& value, const int& w=0, const char& fill=' ') const
	{		
		this->out() << "[ERROR] ";
		return this->print(value, w, fill);
	}

	// Debug Functions
	template<typename T>
	inline const LogManager& debugln(const T& value) const
	{
		this->out() << "[DEBUG] ";
		return this->println(value);
	}

	template<typename T>
	inline const LogManager& debug(const T& value, const int& w=0, const char& fill=' ') const
	{		
		this->out() << "[DEBUG] ";
		return this->print(value, w, fill);
	}
};

template<typename T>
const LogManager& operator << (const LogManager& log, const T& obj)
{ 
	if(log._single)
		log.print(obj);
	else
		log.println(obj);
	return log;
}

static LogManager Log;