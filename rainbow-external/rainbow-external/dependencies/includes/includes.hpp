#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <d3d11.h>
#include <vector>
#include <thread>
#include <algorithm>

#include "math.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "memory.hpp"

#include "classes.hpp"
#include "cache.hpp"

#include "overlay.hpp"