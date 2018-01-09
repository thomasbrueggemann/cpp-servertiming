#ifndef SERVERTIMING_HPP
#define SERVERTIMING_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <regex>

using namespace std::chrono;

// SERVER - TIMING
class ServerTiming
{
private:
	std::unordered_map<std::string, std::string> metrics;
	std::unordered_map<std::string, unsigned int> timer;
	std::unordered_map<std::string, unsigned int> times;
	bool printTimes;

	// SLUGIFY
	// see https://github.com/thomasbrueggemann/cpp-slugify
	std::string slugify(std::string input)
	{
		std::unordered_map<std::string, std::string> charMap {
			// latin
			{"À", "A"}, {"Á", "A"}, {"Â", "A"}, {"Ã", "A"}, {"Ä", "A"}, {"Å", "A"}, {"Æ", "AE"}, {
			"Ç", "C"}, {"È", "E"}, {"É", "E"}, {"Ê", "E"}, {"Ë", "E"}, {"Ì", "I"}, {"Í", "I"}, {
			"Î", "I"}, {"Ï", "I"}, {"Ð", "D"}, {"Ñ", "N"}, {"Ò", "O"}, {"Ó", "O"}, {"Ô", "O"}, {
			"Õ", "O"}, {"Ö", "O"}, {"Ő", "O"}, {"Ø", "O"}, {"Ù", "U"}, {"Ú", "U"}, {"Û", "U"}, {
			"Ü", "U"}, {"Ű", "U"}, {"Ý", "Y"}, {"Þ", "TH"}, {"ß", "ss"}, {"à", "a"}, {"á", "a"}, {
			"â", "a"}, {"ã", "a"}, {"ä", "a"}, {"å", "a"}, {"æ", "ae"}, {"ç", "c"}, {"è", "e"}, {
			"é", "e"}, {"ê", "e"}, {"ë", "e"}, {"ì", "i"}, {"í", "i"}, {"î", "i"}, {"ï", "i"}, {
			"ð", "d"}, {"ñ", "n"}, {"ò", "o"}, {"ó", "o"}, {"ô", "o"}, {"õ", "o"}, {"ö", "o"}, {
			"ő", "o"}, {"ø", "o"}, {"ù", "u"}, {"ú", "u"}, {"û", "u"}, {"ü", "u"}, {"ű", "u"}, {
			"ý", "y"}, {"þ", "th"}, {"ÿ", "y"}, {"ẞ", "SS"},
			// greek
			{"α", "a"}, {"β", "b"}, {"γ", "g"}, {"δ", "d"}, {"ε", "e"}, {"ζ", "z"}, {"η", "h"}, {"θ", "8"}, {
			"ι", "i"}, {"κ", "k"}, {"λ", "l"}, {"μ", "m"}, {"ν", "n"}, {"ξ", "3"}, {"ο", "o"}, {"π", "p"}, {
			"ρ", "r"}, {"σ", "s"}, {"τ", "t"}, {"υ", "y"}, {"φ", "f"}, {"χ", "x"}, {"ψ", "ps"}, {"ω", "w"}, {
			"ά", "a"}, {"έ", "e"}, {"ί", "i"}, {"ό", "o"}, {"ύ", "y"}, {"ή", "h"}, {"ώ", "w"}, {"ς", "s"}, {
			"ϊ", "i"}, {"ΰ", "y"}, {"ϋ", "y"}, {"ΐ", "i"}, {
			"Α", "A"}, {"Β", "B"}, {"Γ", "G"}, {"Δ", "D"}, {"Ε", "E"}, {"Ζ", "Z"}, {"Η", "H"}, {"Θ", "8"}, {
			"Ι", "I"}, {"Κ", "K"}, {"Λ", "L"}, {"Μ", "M"}, {"Ν", "N"}, {"Ξ", "3"}, {"Ο", "O"}, {"Π", "P"}, {
			"Ρ", "R"}, {"Σ", "S"}, {"Τ", "T"}, {"Υ", "Y"}, {"Φ", "F"}, {"Χ", "X"}, {"Ψ", "PS"}, {"Ω", "W"}, {
			"Ά", "A"}, {"Έ", "E"}, {"Ί", "I"}, {"Ό", "O"}, {"Ύ", "Y"}, {"Ή", "H"}, {"Ώ", "W"}, {"Ϊ", "I"}, {
			"Ϋ", "Y"},
			// turkish
			{"ş", "s"}, {"Ş", "S"}, {"ı", "i"}, {"İ", "I"}, {"ç", "c"}, {"Ç", "C"}, {"ü", "u"}, {"Ü", "U"}, {
			"ö", "o"}, {"Ö", "O"}, {"ğ", "g"}, {"Ğ", "G"},
			// russian
			{"а", "a"}, {"б", "b"}, {"в", "v"}, {"г", "g"}, {"д", "d"}, {"е", "e"}, {"ё", "yo"}, {"ж", "zh"}, {
			"з", "z"}, {"и", "i"}, {"й", "j"}, {"к", "k"}, {"л", "l"}, {"м", "m"}, {"н", "n"}, {"о", "o"}, {
			"п", "p"}, {"р", "r"}, {"с", "s"}, {"т", "t"}, {"у", "u"}, {"ф", "f"}, {"х", "h"}, {"ц", "c"}, {
			"ч", "ch"}, {"ш", "sh"}, {"щ", "sh"}, {"ъ", "u"}, {"ы", "y"}, {"ь", ""}, {"э", "e"}, {"ю", "yu"}, {
			"я", "ya"}, {
			"А", "A"}, {"Б", "B"}, {"В", "V"}, {"Г", "G"}, {"Д", "D"}, {"Е", "E"}, {"Ё", "Yo"}, {"Ж", "Zh"}, {
			"З", "Z"}, {"И", "I"}, {"Й", "J"}, {"К", "K"}, {"Л", "L"}, {"М", "M"}, {"Н", "N"}, {"О", "O"}, {
			"П", "P"}, {"Р", "R"}, {"С", "S"}, {"Т", "T"}, {"У", "U"}, {"Ф", "F"}, {"Х", "H"}, {"Ц", "C"}, {
			"Ч", "Ch"}, {"Ш", "Sh"}, {"Щ", "Sh"}, {"Ъ", "U"}, {"Ы", "Y"}, {"Ь", ""}, {"Э", "E"}, {"Ю", "Yu"}, {
			"Я", "Ya"},
			// ukranian
			{"Є", "Ye"}, {"І", "I"}, {"Ї", "Yi"}, {"Ґ", "G"}, {"є", "ye"}, {"і", "i"}, {"ї", "yi"}, {"ґ", "g"},
			// czech
			{"č", "c"}, {"ď", "d"}, {"ě", "e"}, {"ň", "n"}, {"ř", "r"}, {"š", "s"}, {"ť", "t"}, {"ů", "u"},
			{"ž", "z"}, {"Č", "C"}, {"Ď", "D"}, {"Ě", "E"}, {"Ň", "N"}, {"Ř", "R"}, {"Š", "S"}, {"Ť", "T"},
			{"Ů", "U"}, {"Ž", "Z"},
			// polish
			{"ą", "a"}, {"ć", "c"}, {"ę", "e"}, {"ł", "l"}, {"ń", "n"}, {"ó", "o"}, {"ś", "s"}, {"ź", "z"},
			{"ż", "z"}, {"Ą", "A"}, {"Ć", "C"}, {"Ę", "e"}, {"Ł", "L"}, {"Ń", "N"}, {"Ś", "S"},
			{"Ź", "Z"}, {"Ż", "Z"},
			// latvian
			{"ā", "a"}, {"č", "c"}, {"ē", "e"}, {"ģ", "g"}, {"ī", "i"}, {"ķ", "k"}, {"ļ", "l"}, {"ņ", "n"},
			{"š", "s"}, {"ū", "u"}, {"ž", "z"}, {"Ā", "A"}, {"Č", "C"}, {"Ē", "E"}, {"Ģ", "G"}, {"Ī", "i"},
			{"Ķ", "k"}, {"Ļ", "L"}, {"Ņ", "N"}, {"Š", "S"}, {"Ū", "u"}, {"Ž", "Z"},
			// currency
			{"€", "euro"}, {"₢", "cruzeiro"}, {"₣", "french franc"}, {"£", "pound"},
			{"₤", "lira"}, {"₥", "mill"}, {"₦", "naira"}, {"₧", "peseta"}, {"₨", "rupee"},
			{"₩", "won"}, {"₪", "new shequel"}, {"₫", "dong"}, {"₭", "kip"}, {"₮", "tugrik"},
			{"₯", "drachma"}, {"₰", "penny"}, {"₱", "peso"}, {"₲", "guarani"}, {"₳", "austral"},
			{"₴", "hryvnia"}, {"₵", "cedi"}, {"¢", "cent"}, {"¥", "yen"}, {"元", "yuan"},
			{"円", "yen"}, {"﷼", "rial"}, {"₠", "ecu"}, {"¤", "currency"}, {"฿", "baht"}, {"$", "dollar"},
			// symbols
			{"©", "(c)"}, {"œ", "oe"}, {"Œ", "OE"}, {"∑", "sum"}, {"®", "(r)"}, {"†", "+"},
			{"“", "\""}, {"∂", "d"}, {"ƒ", "f"}, {"™", "tm"},
			{"℠", "sm"}, {"…", "..."}, {"˚", "o"}, {"º", "o"}, {"ª", "a"}, {"•", "*"},
			{"∆", "delta"}, {"∞", "infinity"}, {"♥", "love"}, {"&", "and"}, {"|", "or"},
			{"<", "less"}, {">", "greater"}
		};

		// loop every character in charMap
		for(auto kv : charMap)
		{
			// check if key is in string
			if(input.find(kv.first) != std::string::npos)
			{
				// replace key with value
				input.replace(input.find(kv.first), kv.first.length(), kv.second);
			}
		}

		std::regex e1("[^\\w\\s$*_+~.()\'\"-]");
		input = std::regex_replace(input, e1, "");

		std::regex e2("^\\s+|\\s+$");
		input = std::regex_replace(input, e2, "");

		std::regex e3("[-\\s]+");
		input = std::regex_replace(input, e3, "-");

		std::regex e4("#-$");
		input = std::regex_replace(input, e4, "");

		return input;
	};

	// PRINT NUMBER
	std::string printNumber(unsigned int input)
	{
		std::string value = std::to_string((double)input / 1000.0);
		value.erase(value.find_last_not_of('0') + 1, std::string::npos);

		if(value[value.length()-1] == '.')
		{
			value.pop_back();
		}

		return value;
	}

public:

	ServerTiming()
	{
		printTimes = false;
	};

	ServerTiming(bool pTimes)
	{
		printTimes = pTimes;
	};

	// START TIMER
	bool startTimer(std::string name)
	{
		// slugify name
		std::string slug = slugify(name);
		std::transform(slug.begin(), slug.end(), slug.begin(), ::tolower);

		if(slug.length() == 0)
		{
			return false;
		}

		metrics[slug] = name;

		// start timer
		milliseconds now = duration_cast<milliseconds>(
    		system_clock::now().time_since_epoch()
		);

		timer[slug] = now.count();

		return true;
	};

	// STOP TIMER
	bool stopTimer(std::string name)
	{
		// slugify name
		std::string slug = slugify(name);
		std::transform(slug.begin(), slug.end(), slug.begin(), ::tolower);

		// check if timer even exists
		if(timer.find(slug) == timer.end())
		{
			return false;
		}

		// get current timestamp
		milliseconds now = duration_cast<milliseconds>(
    		system_clock::now().time_since_epoch()
		);

		// stop timer
		times[slug] = now.count() - timer[slug];
		timer.erase(slug);

		// print times to stdout
		if(printTimes == true)
		{
			std::cout << metrics[slug] << ": " << printNumber(times[slug]) << "s" << std::endl;
		}

		return true;
	};

	// READ TIMES
	double readTimes(std::string name)
	{
		// slugify name
		std::string slug = slugify(name);
		std::transform(slug.begin(), slug.end(), slug.begin(), ::tolower);

		// check if time even exists
		if(times.find(slug) == times.end())
		{
			return -1.0;
		}

		return (double)times[slug];
	};

	// ADD METRIC
	bool addMetric(std::string name, unsigned int value)
	{
		// slugify name
		std::string slug = slugify(name);
		std::transform(slug.begin(), slug.end(), slug.begin(), ::tolower);

		// store metric values
		metrics[slug] = name;
		times[slug] = value;

		return true;
	};

	// GENERATE HEADER
	std::string generateHeader()
	{
		std::string header = "";

		// loop metrics
		for(auto kv : metrics)
		{
			header += kv.first + ";dur=" + printNumber(times[kv.first]) + ";desc=\"" + kv.second + "\",";
		}

		// remove trailing comma and return header string
		header.pop_back();
		return header;
	};
};

#endif
