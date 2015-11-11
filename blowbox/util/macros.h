#pragma once

#include <comdef.h>

#define BB_REPORT(cstr) OutputDebugString(cstr); OutputDebugString("\n"); printf(cstr); printf("\n");

#define BB_SAFE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; }
#define BB_SAFE_RELEASE(ptr) if (ptr != nullptr) { ptr->Release(); ptr = nullptr; }

#ifdef _DEBUG
#define BB_CHECK(hr) { HRESULT _hr = hr; if (_hr != S_OK) { _com_error error(_hr); BB_REPORT(error.ErrorMessage()); DebugBreak(); } }
#define BB_GUARANTEE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; } else { BB_REPORT("Trying to delete a pointer that already is null."); DebugBreak(); }
#define BB_GUARANTEE_RELEASE(ptr) if (ptr != nullptr) { ptr->Release(); ptr = nullptr; } else { BB_REPORT("Trying to release a pointer that already is null."); DebugBreak(); }
#define BB_ASSERT_NOTNULL(expr, msg) if (!(expr != NULL && expr != nullptr)) { BB_REPORT(msg); DebugBreak(); }
#define BB_ASSERT(expr, msg) if (!(expr)) { BB_REPORT(msg); DebugBreak(); }
#else
#define BB_CHECK(hr) hr
#define BB_GUARANTEE_DELETE(ptr) BB_SAFE_DELETE(ptr)
#define BB_GUARANTEE_RELEASE(ptr) BB_SAFE_RELEASE(ptr)
#define BB_ASSERT_NOTNULL(expr, msg)
#define BB_ASSERT(expr, msg)
#endif