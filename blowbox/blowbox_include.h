#pragma once

// Core
#include "../blowbox/core/blowbox.h"
#include "../blowbox/core/game_object.h"

// Threading
#include "../blowbox/core/threading/job.h"
#include "../blowbox/core/threading/job_manager.h"
#include "../blowbox/core/threading/worker_thread.h"

// Graphics
#include "../blowbox/graphics/direct3d/camera.h"
#include "../blowbox/graphics/direct3d/command_allocator.h"
#include "../blowbox/graphics/direct3d/command_list.h"
#include "../blowbox/graphics/direct3d/command_queue.h"
#include "../blowbox/graphics/direct3d/descriptor_heap.h"
#include "../blowbox/graphics/direct3d/device.h"
#include "../blowbox/graphics/direct3d/pipeline_state.h"
#include "../blowbox/graphics/direct3d/renderer.h"
#include "../blowbox/graphics/direct3d/root_signature.h"
#include "../blowbox/graphics/direct3d/swap_chain.h"
#include "../blowbox/graphics/direct3d/vertex.h"
#include "../blowbox/graphics/direct3d/vertex_buffer.h"
#include "../blowbox/graphics/direct3d/indexed_vertex_buffer.h"
#include "../blowbox/graphics/direct3d/shader.h"

// Utils
#include "../blowbox/util/macros.h"
#include "../blowbox/util/shape_helper.h"

// Window
#include "../blowbox/window/window.h"