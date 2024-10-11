# Log
- A customizable, neat, opensource, simple log system, header include only.
- Be able to create log file in target directory
- Handle muti-datatype message (define string output with operator "<<")
# Requirement
- System: Window
- Preprocessor: _CRT_SECURE_NO_WARNINGS; CUSTOM_PLATFORM_WINDOWS
- C++ version: lastest (ISO C++20 standard to support filesystem and args...)
# Usage
Example:
```
#include "include/Log.hpp"

int main() {
	Logger logger;

	logger.Log(Mode::trace, "Hello World ", 3.14f);

	return 0;
}
```