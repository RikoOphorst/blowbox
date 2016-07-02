#pragma once

#include "../blowbox/core/console/console.h"
//#include "../blowbox/core/console/message.h"

// Core
#include "../blowbox/core/blowbox.h"
#include "../blowbox/core/game_object.h"

// Threading
#include "../blowbox/core/threading/job.h"
#include "../blowbox/core/threading/job_manager.h"
#include "../blowbox/core/threading/worker_thread.h"

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
#include "../blowbox/util/linked_list.h"

// Window
#include "../blowbox/window/window.h"