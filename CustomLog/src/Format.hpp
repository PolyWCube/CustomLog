#pragma once

#ifdef CUSTOM_PLATFORM_WINDOWS
	#define DAY "%d"
	#define SDAY "%a"
	#define FDAY "%A"

	#define MONTH "%m"
	#define SMONTH "%b"
	#define FMONTH "%B"

	#define SYEAR "%y"
	#define FYEAR "%Y"

	#define SECOND "%S"
	#define MINUTE "%M"
	#define HOUR "%H"

	#define TIMEZONE "%Z"

	#define NEW_LINE '\n'
#else Only support Windows
#endif