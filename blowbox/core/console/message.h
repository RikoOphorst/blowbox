#pragma once

#include "../../core/memory/memory_object.h"
#include "../../core/console/message_types.h"

#include <string>

namespace blowbox
{
	/**
	* @enum blowbox::BB_MESSAGE_TYPES
	* @author Riko Ophorst
	* @brief All available message types
	*/
	enum BB_MESSAGE_TYPES
	{
		BB_MESSAGE_TYPE_LOG,
		BB_MESSAGE_TYPE_ERROR,
		BB_MESSAGE_TYPE_WARNING
	};

	/**
	* @class blowbox::Message
	* @author Riko Ophorst
	* @brief A send-able message to the external console
	*/
	class Message : public memory::MObject
	{
	public:
		/**
		* @brief Message constructor
		* @param[in]	allocator		The allocator used to allocate this message
		* @param[in]	message			The message that should be send
		* @param[in]	message_type	The type of message to send
		*/
		Message(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type);
		
		~Message(); //<! Message destructor

		/**
		* @brief Factory to create messages
		* @param[in]	allocator		The allocator that should be used to allocate this message
		* @param[in]	message			The message that should be send
		* @param[in]	message_type	The type of message to send
		*/
		static Message* Create(memory::Allocator* allocator, const std::string& message, const BB_MESSAGE_TYPES& message_type);

		const ConsoleMessageTextLog& GetActualMessage(); //<! Get the actual packet that will be send
	private:
		ConsoleMessageTextLog actual_message_; //<! The actual packet that will be send
	};
}