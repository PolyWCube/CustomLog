#ifndef LOGGER
#define LOGGER

#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdarg.h>

namespace Custom {
	namespace Log {
		class Logger {
		public:
			static Logger& GET_instance() {
				static Logger instance;
				return instance;
			}

			void SET_file(const std::string& name, bool create_directory = false) {
				if (create_directory) {
					std::filesystem::path path(name);
					std::filesystem::path directory = path.parent_path();
					if (!directory.empty() && !std::filesystem::exists(directory)) {
						if (!std::filesystem::create_directories(directory)) {
							std::cerr << "FAILED create log directory - " << directory << std::endl;
							return;
						}
					}
					file.open(name, std::ios::app);
					if (file.is_open()) outStream = &file;
					else std::cerr << "FAILED open log file - " << name << std::endl;
				}
			}
		private:
			Logger() {}
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;

			std::ostream* outStream = &std::cout;
			std::ofstream file;
		};
	}
}

#endif