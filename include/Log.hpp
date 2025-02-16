#ifndef LOG
#define LOG

#include "../source/Logger.hpp"
#include "../source/Formatter.hpp"

#define DEFINE_LOG_LEVEL(level, fg_color, bg_color) \
namespace Custom { \
	namespace Log { \
		template <typename... Args> \
		inline constexpr void level(const Args&... message) { \
			std::stringstream os, ofs; \
			std::string timestamp = GET_timestamp(); \
			os << fg_color << bg_color << timestamp << #level << ": " << Custom::Log::GET_string(message...) << RESET_COLOR; \
			ofs << timestamp << #level << ": " << Custom::Log::GET_string(message...) << "\n"; \
			std::cout << os.str() << NEW_LINE; \
			Logger::GET_instance().WRITE(ofs.str()); \
		} \
	} \
}

#endif