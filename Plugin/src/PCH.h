#pragma once

// c
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// cxx
#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <barrier>
#include <bit>
#include <bitset>
#include <charconv>
#include <chrono>
#include <compare>
#include <complex>
#include <concepts>
#include <condition_variable>
#include <deque>
#include <exception>
#include <execution>
#include <filesystem>
#include <format>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <latch>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <new>
#include <numbers>
#include <numeric>
#include <optional>
#include <ostream>
#include <queue>
#include <random>
#include <ranges>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <semaphore>
#include <set>
#include <shared_mutex>
#include <source_location>
#include <span>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <string_view>
#include <syncstream>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <variant>
#include <vector>
#include <version>

// Clib
#include "F4SE/F4SE.h"
#include "RE/Fallout.h"

// winnt
#include <ShlObj_core.h>

#undef min
#undef max
#undef GetComputerName
#undef GetForm

using namespace std::literals;

#define DLLEXPORT extern "C" [[maybe_unused]] __declspec(dllexport)

// Plugin
#include "Plugin.h"

namespace RuntimeCompat
{
	[[nodiscard]] inline bool IsVR() noexcept
	{
		return REL::Module::get().filename().find(L"Fallout4VR.exe") != std::wstring::npos;
	}

	[[nodiscard]] inline bool IsNG() noexcept
	{
		return !IsVR() && REL::Module::get().version() >= F4SE::RUNTIME_1_10_980;
	}
}

// DKUtil compatibility for newer CommonLibF4 REL::Module API.
#if defined(F4SEAPI)
#	if !defined(LOG_PATH)
#		define LOG_PATH "My Games\\Fallout4\\F4SE"sv
#	endif
#	if !defined(LOG_PATH_VR)
#		define LOG_PATH_VR "My Games\\Fallout4VR\\F4SE"sv
#	endif
#	if !defined(IS_VR)
#		define IS_VR RuntimeCompat::IsVR()
#	endif
#	if !defined(IS_F4)
#		define IS_F4 (!IS_VR)
#	endif
#	if !defined(IS_NG)
#		define IS_NG RuntimeCompat::IsNG()
#	endif
#endif

// DKUtil
#include "DKUtil/Config.hpp"
#include "DKUtil/Hook.hpp"
#include "DKUtil/Logger.hpp"

// Config
#include "Config/Config.h"

// Extras
#include <fmt/chrono.h>

// F4SEPlugin_Version
DLLEXPORT constinit auto F4SEPlugin_Version = []() noexcept
{
	F4SE::PluginVersionData data{};

	data.PluginVersion(Plugin::Version);
	data.PluginName(Plugin::NAME);
	data.AuthorName(Plugin::AUTHOR);
	data.UsesAddressLibrary(true);
	data.UsesSigScanning(false);
	data.IsLayoutDependent(true);
	data.HasNoStructUse(false);
	data.CompatibleVersions({ F4SE::RUNTIME_LATEST });

	return data;
}();
