#include "message.h"

#include <time.h>

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	Message::Message(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type) :
		MObject(allocator)
	{
		actual_message_.dateSend = time(0);
		memcpy(actual_message_.log, message.c_str(), message.size());
		actual_message_.log_length = static_cast<short>(message.size());
		
		switch (message_type)
		{
		case BB_MESSAGE_TYPE_LOG:
			actual_message_.foregroundR = 150;
			actual_message_.foregroundG = 150;
			actual_message_.foregroundB = 150;
			actual_message_.foregroundA = 255;
			actual_message_.backgroundR = 25;
			actual_message_.backgroundG = 25;
			actual_message_.backgroundB = 35;
			actual_message_.backgroundA = 255;
			break;
		case BB_MESSAGE_TYPE_WARNING:
			actual_message_.foregroundR = 50;
			actual_message_.foregroundG = 50;
			actual_message_.foregroundB = 50;
			actual_message_.foregroundA = 255;
			actual_message_.backgroundR = 255;
			actual_message_.backgroundG = 204;
			actual_message_.backgroundB = 0;
			actual_message_.backgroundA = 150;
			break;
		case BB_MESSAGE_TYPE_ERROR:
			actual_message_.foregroundR = 150;
			actual_message_.foregroundG = 150;
			actual_message_.foregroundB = 150;
			actual_message_.foregroundA = 255;
			actual_message_.backgroundR = 116;
			actual_message_.backgroundG = 12;
			actual_message_.backgroundB = 17;
			actual_message_.backgroundA = 255;
			break;
		};
	}

	//------------------------------------------------------------------------------------------------------
	Message::~Message()
	{

	}

	//------------------------------------------------------------------------------------------------------
	Message* Message::Create(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type)
	{
		return memory::MemoryManager::Allocate<Message>(allocator, allocator, message, message_type);
	}

	//------------------------------------------------------------------------------------------------------
	const ConsoleMessageTextLog& Message::GetActualMessage()
	{
		return actual_message_;
	}
}