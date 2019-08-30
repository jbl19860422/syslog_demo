#include "logger.h"

#include <stddef.h>
#include <stdarg.h>
//stl
#include <map>
#include <algorithm>

static std::map<std::string, int> syslog_level_map__ = {
    {"fatal", Fatal},
    {"error", Error},
    {"warn", Warn},
    {"notice", Notice},
    {"info", Info},
    {"debug", Debug}};

static int internal_syslog_level = Info;

void setLogLevel(int level)
{
  internal_syslog_level = level;
}

void setLogLevel(const std::string &level)
{
  std::string level_lower_str;
  level_lower_str.resize(level.size());
  std::transform(level.begin(), level.end(), level_lower_str.begin(), ::tolower);
  auto it = syslog_level_map__.find(level_lower_str);
  if (it != syslog_level_map__.end())
  {
    setLogLevel(it->second);
  }
}

int getLogLevel()
{
  return internal_syslog_level;
}

void log_init()
{
  openlog(0, LOG_PID, LOG_LOCAL0);
}

void log(int l, const char *fmt, ...)
{
  if (l > internal_syslog_level)
    return;

  va_list param;
  va_start(param, fmt);
  vsyslog(l, fmt, param);
  va_end(param);
}
