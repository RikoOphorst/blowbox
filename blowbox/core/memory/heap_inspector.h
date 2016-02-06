#pragma once

#ifdef _DEBUG
#include "HeapInspectorServer.h"
#include "PC_Windows\HeapHooks.h"
#define BB_HEAP_BEGIN_ALLOC() HeapInspectorServer::Mutation __mut__ = HeapInspectorServer::BeginAlloc()
#define BB_HEAP_END_ALLOC(ptr, size) HeapInspectorServer::EndAlloc(__mut__, 0, ptr, size, size)
#else
#define BB_HEAP_BEGIN_ALLOC()
#define BB_HEAP_END_ALLOC(ptr, size)
#endif