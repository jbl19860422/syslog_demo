#ifndef SVC_LOGGER_H
#define SVC_LOGGER_H

#include <syslog.h>
#include <string>
#include <sstream>

enum
{
	Fatal = LOG_EMERG,
	Error = LOG_ERR,
	Warn = LOG_WARNING,
	Notice = LOG_NOTICE,
	Info = LOG_INFO,
	Debug = LOG_DEBUG
};

void log_init();
void log(int error, const char *fmt, ...);
void setLogLevel(int level);
void setLogLevel(const std::string &level);
int getLogLevel();

#define log_trace(level, fmt, ...)                                                       \
	if (level <= getLogLevel())                                                          \
	{                                                                                    \
		log(level, "[%s:%s:%d]: " fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}
#define log_raw(level, fmt, ...)        \
	if (level <= getLogLevel())         \
	{                                   \
		log(level, fmt, ##__VA_ARGS__); \
	}

#define LOGTRACE(level, logObject) 							\
	do {												\
		std::ostringstream oss;							\
		oss << logObject;								\
		log_trace(level, "%s", oss.str().c_str());		\		
	} while(0)
#endif
