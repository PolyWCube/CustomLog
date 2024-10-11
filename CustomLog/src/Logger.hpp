#pragma once

#include <string>
#include <iostream>

#include <fstream>

#include <ctime>
#include <chrono>

#include <vector>
#include <filesystem>


#include "Format.hpp"
#include "ColorCode.hpp"

namespace Custom {
	namespace Log {
		enum Mode { trace, debug, status, success, warn, error, fatal, unknown };
		enum Color { lGray, blue, green, dGreen, yellow, red, dRed, pink };

		const std::string timestampToken[23]{
			"day",
			"month",
			"year",
			"second",
			"minute",
			"hour",
			"/", "|", ":", ";", "-", "+",
			"[", "]", "(", ")", "{", "}", "<", ">",
			",", ".", " "
		};

		const std::string token[22]{
			"timestamp",
			"mode",
			"message",
			"color ",
			"reset ",
			"/", "|", ":", ";", "-", "+",
			"[", "]", "(", ")", "{", "}", "<", ">",
			",", ".", " "
		};

		class Logger {
		public:
			Logger(const std::string& logDirectory = "./log/", const std::string& fileFormat = "day-month-year...hour-minute", const std::string& timestampFormat = "second:minute:hour", const std::string& logFormat = "[timestamp] color mode reset : message") : timestampFormat(TimestampFormat(timestampFormat)), fileFormat(TimestampFormat(fileFormat) + ".txt"), logDirectory(logDirectory) {
				LogFormat(logFormat);

				std::filesystem::create_directory(logDirectory);

				CreateFile();
			}
			~Logger() { file.close(); }

			template <typename... Args>
			void Log(Mode mode, const Args&... message) {
				std::string outputConsole = "";
				std::string outputFile = "";
				for (auto token : logFormat) {
					if (token == "message") {
						std::string token = Stringify(message...);
						outputConsole += token;
						outputFile += token;
					}
					else if (token == "timestamp") {
						std::string token = GetTimestamp(timestampFormat);
						outputConsole += token;
						outputFile += token;
					}
					else if (token == "mode") {
						std::string token = GetMode(mode);
						outputConsole += token;
						outputFile += token;
					}
					else if (token == "color ") outputConsole += GetColor(mode);
					else if (token == "reset ") outputConsole += RESET;
					else {
						outputConsole += token;
						outputFile += token;
					}
				}
				std::cout << outputConsole << NEW_LINE;
				if (file.is_open()) {
					file << outputFile << NEW_LINE;
				}
				else {
					std::cout << "Can not open log file..." << NEW_LINE;
				}
			}

			void SetTimestampFormat(const std::string& format);
			void SetLogFormat(const std::string& format);

			void SetFileDirectory(const std::string& directory);
			void SetFileNameFormat(const std::string& format);
			void CreateFile(const std::string& name);
			void CreateFile();
		private:
			void LogFormat(std::string format);
			std::string TimestampFormat(std::string format);

			inline std::string GetTimestamp(const std::string& format);

			template <typename T>
			inline std::string GetStream(const T& val) {
				if constexpr (std::is_convertible_v<T, std::string>) return static_cast<std::string>(val);

				std::ostringstream oss;
				oss << val;

				return oss.str();
			}

			template <typename... Args>
			std::string Stringify(const Args&... args) {
				std::ostringstream oss;
				((oss << GetStream(args)), ...);
				return oss.str();
			}

			inline static std::string GetMode(Mode mode) {
				switch (mode) {
				case trace: return "TRACE  ";
				case debug: return "DEBUG  ";
				case status: return "STATUS ";
				case success: return "SUCCESS";
				case error: return "ERROR  ";
				case warn: return "WARN   ";
				case fatal: return "FATAL  ";
				case unknown: return "UNKNOWN";
				}
				return "Fatal  ";
			}
			inline static std::string GetColor(Mode mode) {
				switch (mode) {
				case trace: return L_GRAY;
				case debug: return BLUE;
				case status: return GREEN;
				case success: return D_GREEN;
				case warn: return YELLOW;
				case error: return RED;
				case fatal: return D_RED;
				case unknown: return PINK;
				}
				return ";";
			}
			inline static std::string GetColor(Color color) {
				switch (color) {
				case lGray: return L_GRAY;
				case blue: return BLUE;
				case green: return GREEN;
				case dGreen: return D_GREEN;
				case yellow: return YELLOW;
				case red: return RED;
				case dRed: return D_RED;
				case pink: return PINK;
				}
				return D_RED;
			}

			void FlushDirectory();

			std::ofstream file;
			std::string logDirectory;

			std::vector<std::string> logFormat;
			std::string timestampFormat;
			std::string fileFormat;
		};
	}
}