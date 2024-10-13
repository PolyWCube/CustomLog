# Log
- A customizable, neat, opensource, simple log system, header include only.
- Be able to create log file in target directory.
- Handle muti-datatype message (define string output with operator "<<").
# Requirement
- System: Window
- Preprocessor: _CRT_SECURE_NO_WARNINGS; CUSTOM_PLATFORM_WINDOWS;
- C++ version: lastest (ISO C++20 standard)
# Usage
- Link directly in solution or build (run the GenerateProject.bat file) using premake
- Exposed function
```
Logger(const std::string& logDirectory = "./log/",
				const std::string& fileFormat = "day-month-fYear...hour-minute",
				const std::string& timestampFormat = "fDay/fMonth-day/month/fYear|second:minute:hour|timezone",
				const std::string& logFormat = "[timestamp] color mode reset : message", const std::string& breakFormat = "-----------------------------------------------------------------------------------"
			) -> default value

void Log(Mode mode, const Args&... message);		-> Log message
void Break();										-> Create break line

void SetBreakFormat(const std::string& format);

void SetTimestampFormat(const std::string& format);
void SetLogFormat(const std::string& format);

void SetFileDirectory(const std::string& directory);
void SetFileNameFormat(const std::string& format);
void CreateFile(const std::string& name);
void CreateFile();
```
Example:
```
#include "include/Log.hpp"

int main() {
	Logger logger;

	logger.Log(TRACE, "Hello World ", 3.14f);

	return 0;
}
```
# Credit
- Premake for build system