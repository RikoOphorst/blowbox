#pragma once

// Console
#include "../blowbox/core/console/console.h"

// Threading
#include "../blowbox/core/threading/task_manager.h"
#include "../blowbox/core/threading/task.h"

// Core
#include "../blowbox/util/macros.h"
#include "../blowbox/core/blowbox.h"
#include "../blowbox/core/game_object.h"

// Memory
#include "../blowbox/core/memory/memory_manager.h"
#include "../blowbox/core/memory/memory_pool.h"
#include "../blowbox/core/memory/memory_object.h"
#include "../blowbox/core/memory/stl_allocator.h"
#include "../blowbox/core/memory/linear_allocator.h"
#include "../blowbox/core/memory/free_list_allocator.h"
#include "../blowbox/core/memory/stack_allocator.h"
#include "../blowbox/core/memory/pool_allocator.h"
#include "../blowbox/core/memory/pointer_util.h"

// Smart pointers
#include "../blowbox/core/memory/smart_ptrs/shared_ptr.h"

// Utils
#include "../blowbox/util/shape_helper.h"

// Window
#include "../blowbox/window/window.h"