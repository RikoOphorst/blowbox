#pragma once

#define BB_SAFE_DELETE(ptr) if (ptr != nullptr) { delete ptr; ptr = nullptr; }
#define BB_SAFE_RELEASE(ptr) if (ptr != nullptr) { ptr->Release(); ptr = nullptr; }