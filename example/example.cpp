#include "../include/Log.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <string_view>

DEFINE_LOG_LEVEL(Trace, FG_WHITE, NONE);
DEFINE_LOG_LEVEL(Info, FG_GREEN, NONE);
DEFINE_LOG_LEVEL(Success, FG_WHITE, BG_GREEN);
DEFINE_LOG_LEVEL(Warn, FG_YELLOW, NONE);
DEFINE_LOG_LEVEL(Error, FG_RED, NONE);
DEFINE_LOG_LEVEL(Fatal, FG_WHITE, BG_RED);
DEFINE_LOG_LEVEL(Debug, FG_BLUE, NONE);

DEFINE_LOG_LEVEL(CustomL, FG_BLACK, BG_WHITE);

struct Character {
	int id;
	std::string name;

	friend std::ostream& operator<<(std::ostream& os, const Character& ms) {
		os << "ID: " << ms.id << ", Name: " << ms.name;
		return os;
	}
	Character(int id, std::string name) : id(id), name(name) {}
};

int main() {
	double pi = 3.14159265359;
	Custom::Log::Trace("This is the start of the example.");
	Custom::Log::Info("You can log out variable. Pi is equal to: ", pi);
	int status = 1;
	Custom::Log::Success("Log out status. ", (status) ? "Logging successfully..." : "");
	
	Custom::Log::Warn("Internet connection lost...");
	Character character(1430, "PWC");
	Custom::Log::Error("Create a rich log informations with custom data type (using ostream operator).", " An error have occurred(!). Error code ", 404, " by user ", character);
	Custom::Log::Fatal("Or custom color and level text by macro. ", "SYSTEM FAILED");

	std::string_view example = "So basically, you can create your very own log level.";
	Custom::Log::CustomL(example);
	Custom::Log::CustomL("AND THIS IS CUSTOM LOG :>");

	int a;
	std::cin >> a;
	return 0;
}