#pragma once

#include <MessageIdentifiers.h>

namespace blowbox
{
	/**
	* @enum blowbox::BB_CONSOLE_MESSAGE_TYPES
	* @brief All packet types to the console
	*/
	enum BB_CONSOLE_MESSAGE_TYPES
	{
		BB_CONSOLE_MESSAGE_TEXT_LOG = ID_USER_PACKET_ENUM + 1,
	};

#pragma pack(push, 1)

	/**
	* @struct blowbox::ConsoleMessageTextLog
	* @brief Packet to send a text log
	*/
	struct ConsoleMessageTextLog
	{
		__int64 dateSend; //!< The send date
		short foregroundR; //!< Color (red channel) of the foreground text
		short foregroundG; //!< Color (green channel) of the foreground text
		short foregroundB; //!< Color (blue channel) of the foreground text
		short foregroundA; //!< Color (alpha channel) of the foreground text
		short backgroundR; //!< Color (red channel) of the background text
		short backgroundG; //!< Color (green channel) of the background text
		short backgroundB; //!< Color (blue channel) of the background text
		short backgroundA; //!< Color (alpha channel) of the background text
		char log[512]; //!< The actual text-log
		short log_length; //!< The length of the log
	};

#pragma pack(pop)
}