#pragma once

#include "../core/console/console.h"

#define BB_LOGSTREAM std::stringstream()

#define BB_BREAK(msg) { Console::Instance()->Log(msg, blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); }
#define BB_CHECK(hr) { HRESULT _hr = hr; if (_hr != S_OK) { _com_error error(_hr); Console::Instance()->Log(error.ErrorMessage(), blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); } }
#define BB_GUARANTEE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; } else { Console::Instance()->Log("Trying to delete a pointer that already is null.", blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); }
#define BB_GUARANTEE_RELEASE(ptr) if (ptr != nullptr) { ptr->Release(); ptr = nullptr; } else { Console::Instance()->Log("Trying to release a pointer that already is null.", blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); }
#define BB_ASSERT_NOTNULL(expr, msg) if (!(expr != NULL && expr != nullptr)) { Console::Instance()->Log(msg, blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); }
#define BB_ASSERT(expr, msg) if (!(expr)) { Console::Instance()->Log(msg, blowbox::BB_MESSAGE_TYPE_ERROR); DebugBreak(); }