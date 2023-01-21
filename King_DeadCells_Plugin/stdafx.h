#pragma once

// Windows Header Files:
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// TODO: reference additional headers your program requires here

#include "Common.hpp"

#include "EventHandler.hpp"
#include "Hook.hpp"
#include "Crypto.hpp"

#include "Addresses.hpp"

#define SPDLOG_HEADER_ONLY
#define SPDLOG_WCHAR_TO_UTF8_SUPPORT
//#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/fmt.h>

#include <fp_call.hpp>
