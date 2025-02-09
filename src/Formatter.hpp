#ifndef FORMATTER
#define FORMATTER

#include "FormatCode.hpp"

#include <string>
#include <sstream>
#include <string_view>
#include <type_traits>

namespace Custom {
	namespace Log {
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

			char timestamp[100];
			strftime(timestamp, 100, timestampFormat.c_str(), timeinfo);

			return timestamp;
		}
	}
}

#define DEFINE_LOG_LEVEL(level, fg_color, bg_color) \
namespace Custom { \
	namespace Log { \
		template <typename... Args> \
		inline constexpr void level(const Args&... message) { \
			std::stringstream os; \
			os << fg_color << bg_color << #level << ": " << Custom::Log::GET_string(message...) << RESET_COLOR; \
			std::cout << os.str() << NEW_LINE; \
		} \
	} \
}

#endif