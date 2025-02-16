#ifndef FORMATTER
#define FORMATTER

#include "../configuration/Configuration.hpp"

#include <string>
#include <sstream>
#include <string_view>
#include <type_traits>

namespace Custom {
	namespace Log {
		constexpr size_t BUFFER_SIZE_T = 100;

		template <typename T>
		concept Streamable = requires(std::ostream& os, const T& t) {
			os << t;
		};

		template <typename T>
		inline std::string GET_stream(const T& val) {
			if constexpr (std::is_convertible_v<T, std::string>) return val;
			else if constexpr (Streamable<T>) {
				std::ostringstream oss;
				oss << val;
				return oss.str();
			} else return "[ERROR]";
		}

		template <typename... Args>
		inline std::string GET_string(const Args&... args) {
			std::ostringstream oss;
			((oss << GET_stream(args)), ...);
			return oss.str();
		}

		const std::string timestampFormat = TIMESTAMP_FORMAT;
		inline std::string GET_timestamp() {
			time_t now = time(0);
			tm* timeinfo = localtime(&now);

			std::array<char, BUFFER_SIZE_T> timestamp;
			strftime(timestamp.data(), timestamp.size(), timestampFormat.c_str(), timeinfo);

			return std::string(timestamp.data());
		}

		const std::string fileNameFormat = FILE_NAME_FORMAT;
		inline std::string GET_fileName() {
			time_t now = time(0);
			tm* timeinfo = localtime(&now);

			std::array<char, BUFFER_SIZE_T> fileName;
			strftime(fileName.data(), fileName.size(), fileNameFormat.c_str(), timeinfo);

			return std::string(fileName.data());
		}
	}
}

#endif