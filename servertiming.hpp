#ifndef SERVERTIMING_HPP
#define SERVERTIMING_HPP

#include <string>
#include <unordered_map>

// SERVER - TIMING
class ServerTiming
{
private:
	unordered_map<std::string, std::string> metrics;
	unordered_map<std::string, double> times;

	// SLUGIFY
	std::string slugify(std:string input)
	{
		return "";
	};

public:

	// START TIMER
	bool startTimer(std::string name)
	{

		return true;
	};

	// STOP TIMER
	double stopTimer(std::string name)
	{

		return 0.0;
	};

	// ADD METRIC
	bool addMetric(std::string name)
	{

		return true;
	};

	// GENERATE HEADER
	std::string generateHeader()
	{

		return "";
	};
}

#endif
