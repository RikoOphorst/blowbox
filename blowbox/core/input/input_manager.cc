#include "input_manager.h"

#include "../../window/window.h"
#include "../../core/console/console.h"

using namespace std::placeholders;

namespace blowbox
{
	InputManager* InputManager::instance_ = nullptr;

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Create(Allocator* allocator, Window* input_window)
	{
		return instance_ = MemoryManager::Allocate<InputManager>(allocator, allocator, input_window);
	}

	//------------------------------------------------------------------------------------------------------
	InputManager* InputManager::Instance()
	{
		return instance_;
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::InputManager(Allocator* allocator, Window* input_window) :
		MObject(allocator),
		input_window_(input_window)
	{

		std::function<void(MSG message)> message = std::bind(&InputManager::ProcessWinMessage, this, _1);
		input_window_->SetWindowInputListener(message);
	}

	//------------------------------------------------------------------------------------------------------
	InputManager::~InputManager()
	{

	}

	//------------------------------------------------------------------------------------------------------
	void InputManager::ProcessWinMessage(MSG message)
	{
		switch (message.message)
		{
		case WM_KEYDOWN:
			Console::Instance()->Log(std::to_string(message.wParam), BB_MESSAGE_TYPE_LOG);
			break;
		}
	}
}