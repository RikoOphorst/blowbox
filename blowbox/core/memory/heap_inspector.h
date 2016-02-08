#pragma once

#ifdef _DEBUG
#include "HeapInspectorServer.h"
#include "PC_Windows\HeapHooks.h"
#define BB_HEAP_BEGIN_ALLOC() HeapInspectorServer::Mutation __mut__ = HeapInspectorServer::BeginAlloc()
#define BB_HEAP_END_ALLOC(ptr, size) HeapInspectorServer::EndAlloc(__mut__, 0, ptr, size, size)
#define BB_HEAP_ALLOC(ptr, size) { BB_HEAP_BEGIN_ALLOC(); BB_HEAP_END_ALLOC(ptr, size); }
#define BB_HEAP_BEGIN_FREE() HeapInspectorServer::Mutation __mut__ = HeapInspectorServer::BeginFree()
#define BB_HEAP_END_FREE(ptr) HeapInspectorServer::EndFree(__mut__, 0, ptr)
#define BB_HEAP_FREE(ptr) { BB_HEAP_BEGIN_FREE(); BB_HEAP_END_FREE(ptr); }
#else
#define BB_HEAP_BEGIN_ALLOC()
#define BB_HEAP_END_ALLOC(ptr, size)
#define BB_HEAP_ALLOC(ptr, size) 
#define BB_HEAP_BEGIN_FREE()
#define BB_HEAP_END_FREE(ptr)
#define BB_HEAP_FREE(ptr)
#endif