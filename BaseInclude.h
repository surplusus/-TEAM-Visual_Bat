#pragma once
#include <Windows.h>
#include <iostream>
#include <memory>
#include <d3dx9.h>
#include <d3d9.h>

#pragma comment("")
#include <fmod.hpp>
#include <fmod_errors.h>

#include <unordered_map>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include <dinput.h>
#include <stdlib.h>
#include <list>
#include "Device.h"
#include "SystemFunc.h"
#include "ResourceFunc.h"
#include "Include.h"

#include <assert.h>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <deque>
#include <atomic>

extern HWND g_hWnd;
extern HINSTANCE g_hInst;
extern float g_fDeltaTime;
using namespace std;

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif
