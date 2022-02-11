#pragma once

// Target Define
#ifdef BASE_TARGET_DEBUG
#define ENGINE_CORE_DEBUG
#endif

#ifdef BASE_TARGET_RELEASE
#define ENGINE_CORE_RELEASE
#endif

#ifdef BASE_TARGET_DIST
#define ENGINE_CORE_DIST
#endif


// Architecture Define
#ifdef BASE_ARCHITECTURE_X86
#define ENGINE_CORE_X86
#endif

#ifdef BASE_ARCHITECTURE_X86_64
#define ENGINE_CORE_X64
#endif


// Platform Define 
#ifdef BASE_PLATFORM_WINDOWS
#define ENGINE_CORE_PLATFORM_WINDOWS
#endif

#ifdef BASE_PLATFORM_LINUX
#define ENGINE_CORE_PLATFORM_LINUX
#endif


// Compiler Define
#ifdef BASE_COMPILER_MSVC
#define ENGINE_CORE_COMPILER_MSVC
#endif

#ifdef BASE_COMPILER_GCC
#define ENGINE_CORE_COMPILER_GCC
#endif


// Include
#include <cstring>
#include <string>

#include <utility>
#include <memory>
#include <limits>
#include <array>
#include <chrono>
#include <bitset>

#include <algorithm>
#include <functional>
#include <type_traits>
#include <concepts>

#include <cmath>

#include <fstream>
#include <iostream>


// Intrinsic
#ifdef ENGINE_CORE_PLATFORM_WINDOWS
#include <intrin.h>
#endif