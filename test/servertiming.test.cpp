#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include "catch.hpp"
#include "servertiming.hpp"

ServerTiming timing(true);

TEST_CASE("Start a timer", "[ServerTiming]" ) {

	bool t = timing.startTimer("Test Timer");

	REQUIRE(t == true);
}

TEST_CASE("Stop a timer", "[ServerTiming]" ) {

	bool t = timing.stopTimer("Test Timer");

	REQUIRE(t == true);
}

TEST_CASE("Add a metric manually", "[ServerTiming]" ) {

	bool t = timing.addMetric("Add Metric", 1234);

	REQUIRE(t == true);
}

TEST_CASE("Generate the header string", "[ServerTiming]" ) {

	std::string header = timing.generateHeader();
	std::cout << header << std::endl;

	REQUIRE(header.length() > 0);
}
