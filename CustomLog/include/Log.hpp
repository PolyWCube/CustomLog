#pragma once

#include "../src/Logger.hpp"

#define TRACE Custom::Log::Mode::trace
#define STATUS Custom::Log::Mode::status
#define SUCCESS Custom::Log::Mode::success
#define WARN Custom::Log::Mode::warn
#define ERROR Custom::Log::Mode::error
#define FATAL Custom::Log::Mode::fatal
#define UNKNOWN Custom::Log::Mode::unknown
#define DEBUG Custom::Log::Mode::debug

/*
* 
* EXAMPLE TIME: Sunday(Sun)/October(Oct) - 13/10/2024 08:29:44 SE Asia Standard Time
* 
supported timestamp format
	"day",		-> 13
	"sDay",		-> Sun
	"fDay",		-> Sunday
	"month",	-> 10
	"sMonth",	-> Oct
	"fMonth",	-> October
	"sYear",	-> 24
	"fYear",	-> 2024
	"second",	-> 44
	"minute",	-> 29
	"hour",		-> 08
	"timezone",	-> SE Asia Standard Time

	"/", "|", ":", ";", "-", "+",
	"[", "]", "(", ")", "{", "}", "<", ">",
	",", ".", " " -> safe character

supported message format
	"timestamp",-> get timestamp base on timestame format
	"mode",		-> get log level
	"message",	-> message (argument)
	"color ",	-> use ascii color code
	"reset ",	-> reset ascii color code

	"/", "|", ":", ";", "-", "+",
	"[", "]", "(", ")", "{", "}", "<", ">",
	",", ".", " " -> safe character
*/