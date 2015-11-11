#pragma once

#include <comdef.h>

#define BB_REPORT(cstr) printf(cstr);

#ifdef _DEBUG
#define BB_CHECK(hr) { HRESULT _hr = hr; if (_hr != S_OK) { _com_error error(_hr); BB_REPORT(error.ErrorMessage()); DebugBreak(); } }
#define BB_SAFE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; } else { BB_REPORT("Trying to delete a pointer that already is null."); DebugBreak(); }
#define BB_SAFE_RELEASE(ptr) if (ptr != nullptr) { ptr->Release(); ptr = nullptr; } else { BB_REPORT("Trying to release a pointer that already is null."); DebugBreak(); }
#else
#define BB_CHECK(hr) hr
#define BB_SAFE_DELETE(ptr) delete ptr; ptr = nullptr;
#define BB_SAFE_RELEASE(ptr) ptr->Release(); ptr = nullptr;
#endif