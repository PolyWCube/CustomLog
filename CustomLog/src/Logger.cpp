#include "Logger.hpp"

namespace Custom {
	namespace Log {
		void Logger::SetTimestampFormat(const std::string& format) { TimestampFormat(format); }
		void Logger::SetLogFormat(const std::string& format) { LogFormat(format); }

		void Logger::SetFileDirectory(const std::string& directory) {
			FlushDirectory();
			logDirectory = directory;
			std::filesystem::create_directory(logDirectory);
		}
		void Logger::SetFileNameFormat(const std::string& format) { fileFormat = TimestampFormat(format) + ".txt"; }

		void Logger::CreateFile(const std::string& name) {
			std::string filePath = logDirectory + name;
			file.open(filePath);
			if (!file.is_open()) {
				std::cerr << "Error opening file: " << filePath << std::endl;
			}
		}

		void Logger::CreateFile() {
			std::string filePath = logDirectory + GetTimestamp(fileFormat);
			file.open(filePath);
			if (!file.is_open()) {
				std::cerr << "Error opening file: " << filePath << std::endl;
			}
		}

		void Logger::LogFormat(std::string format) {
			logFormat = std::vector<std::string>();

			std::string currentToken;
			for (size_t i = 0; i < format.length(); ++i) {
				currentToken = "";
				for (size_t j = i; j < format.length(); ++j) {
					currentToken += format[j];
					for (const std::string& t : token) {
						if (currentToken == t) {
							logFormat.push_back(currentToken);
							i = j;
							break;
						}
					}
				}
			}
		}

		std::string Logger::TimestampFormat(std::string format) {
			std::string timestampFormat = "";

			std::string currentFormat;
			for (size_t i = 0; i < format.length(); ++i) {
				currentFormat = "";
				for (size_t j = i; j < format.length(); ++j) {
					currentFormat += format[j];
					for (const std::string& t : timestampToken) {
						if (currentFormat == t) {
							if (currentFormat == "day")			currentFormat = DAY;
							else if (currentFormat == "month")	currentFormat = MONTH;
							else if (currentFormat == "year")	currentFormat = YEAR;
							else if (currentFormat == "second") currentFormat = SECOND;
							else if (currentFormat == "minute") currentFormat = MINUTE;
							else if (currentFormat == "hour")	currentFormat = HOUR;
							timestampFormat += currentFormat;
							i = j;
							break;
						}
					}
				}
			}
			return timestampFormat;
		}

		std::string Logger::GetTimestamp(const std::string& format) {
			time_t now = time(0);
			tm* timeinfo = localtime(&now);

			char timestamp[50];
			strftime(timestamp, 50, format.c_str(), timeinfo);

			return timestamp;
		}

		void Logger::FlushDirectory() {
			if (file.is_open()) {
				file.close();
			}
			std::filesystem::remove(logDirectory);
		}
	}
}