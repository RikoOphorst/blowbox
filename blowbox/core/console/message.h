#pragma once

#include "../../core/memory/memory_object.h"
#include "../../core/console/message_types.h"

#include <string>

namespace blowbox
{
	enum BB_MESSAGE_TYPES
	{
		BB_MESSAGE_TYPE_LOG,
		BB_MESSAGE_TYPE_ERROR,
		BB_MESSAGE_TYPE_WARNING
	};

	class Message : public memory::MObject
	{
	public:
		Message(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type);
		~Message();

		static Message* Create(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type);

		const ConsoleMessageTextLog& GetActualMessage();
	private:
		ConsoleMessageTextLog actual_message_;
	};
}