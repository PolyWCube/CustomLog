# CUSTOM Log - CustomL
A simple header-only log library with a pretty good performance and level of customization.

# Features
Custom Log Level Definition mechanism (since v0.1):
``` c++
// Define log level (include text color and background color) in compile time
DEFINE_LOG_LEVEL(Trace, FG_WHITE, NONE);
// Which can later accessed by 
Custom::Log::Trace("Hello world");
```
Log messages with argument-based for type safety, integrated with user-defined streamable object (since v0.1)
``` c++
// Built-in streamable object concept
template <typename T>
concept Streamable = requires(std::ostream& os, const T& t) {
  os << t;
};
// An example of a streamable object
struct Character {
	int id;
	std::string name;

	friend std::ostream& operator<<(std::ostream& os, const Character& ms) {
		os << "ID: " << ms.id << ", Name: " << ms.name;
		return os;
	}
	Character(int id, std::string name) : id(id), name(name) {}
};
```
The streamable object then can later directly pass into the Logger for printout
``` c++
Character character(0001, "User");
Custom::Log::Trace(character);
```
which will now result in
```
ID: 0001, Name: User
```
Allow the user to create simple log files (since v0.2):
``` c++
SET_file("log/", "logfile.txt", true);
// which will create a .txt in the folder containing the executable in log/ directory
```
And compile-time optimization with configuration file

# Purposes:
Create a Custom log system for my Custom engine and try to create new concepts and mechanisms.

# Requirements:
This project was created with MinGW (MinGW-W64 x86_64-ucrt-posix-seh):
* GNU Make 4.4.1
* g++ 14.2.0
Correct versions of `.dll` or `.so` files (`libstdc++.dll`) may be needed to build.
> This project was created on Windows and not properly tested on Unix-system (yet)

# Installations and Setups:
This project includes the source code and some examples. You can either directly use the source code or build the project to a dynamic linking library (`.dll` or `.so`) file using makefile pipeline.

To build the executable (.exe) file for the first time. Run
``` bash
# Or mingw32-make if you're using WinGW (make sure to install the make package)
make build
```
and the example executable file will be located in "./build/**.exe".

# Personal Ratings:
... On going ...