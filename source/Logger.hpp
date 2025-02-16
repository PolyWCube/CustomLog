#ifndef LOGGER
#define LOGGER

#include <fstream>
#include <iostream>
#include <filesystem>
#include <system_error>
#include "Formatter.hpp"

namespace Custom {
	namespace Log {
		template <typename... Args>
		inline constexpr void Program(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::GET_string(message...) << RESET_COLOR;
			std::cout << os.str() << NEW_LINE;
		}

		template <typename... Args>
		inline constexpr void ProgramError(const Args&... message) {
			std::stringstream os;
			os << FG_BLACK << BG_WHITE << "PROGRAM: " << Custom::Log::GET_string(message...) << RESET_COLOR;
			std::cerr << os.str() << NEW_LINE;
		}

		class Logger {
		public:
			static Logger& GET_instance() {
				static Logger instance;
				return instance;
			}

			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;
			Logger(Logger&&) = delete;
			Logger& operator=(Logger&&) = delete;

			inline void SET_file(const std::string& directory, const std::string& name, bool createDirectory) {
				if (createDirectory) {
					try {
						std::filesystem::path path(directory);
						if (!std::filesystem::exists(path)) {
							std::filesystem::create_directory(path);
							Program("SUCCESS create log directory : ", directory);
						}
						else Program("WARN log directory already created : ", directory);
					} catch (const std::filesystem::filesystem_error& error) {
						ProgramError("ERROR create log directory : ", error.what(), ' ', error.code());
					} catch (const std::exception& exception) {
						ProgramError("ERROR create log directory : ", exception.what());
					} catch (...) { std::cerr << "ERROR create log directory : unknown" << std::endl; }
				}
				try {
					file.open(directory + name, std::ios::app);
					if (file.is_open()) Program("SUCCESS open log file : ", directory + name);
					else Program("FAIL open log file : ", directory + name);
					warn = false;
				} catch (const std::exception& exception) { ProgramError("ERROR open log file : ", exception.what()); }
			}
	
			inline void WRITE(const std::string& message) {
				if (!file.is_open() && !warn) { ProgramError("ERROR log file null"); warn = true; }
				file << message;
				file.flush();
			}
		private:
			Logger() {}

			std::ofstream file;
			bool warn = false;
		};

		void SET_file(const std::string& directory, const std::string& name = GET_fileName(), bool createDirectory = false) { Logger::GET_instance().SET_file(directory, name, createDirectory); }
		void SET_file(const std::string& directory, bool createDirectory) { Logger::GET_instance().SET_file(directory, GET_fileName(), createDirectory); }
	}
}

#endif