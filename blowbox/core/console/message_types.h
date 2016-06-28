#pragma once

#include <MessageIdentifiers.h>

namespace blowbox
{
	enum BB_CONSOLE_MESSAGE_TYPES
	{
		BB_CONSOLE_MESSAGE_TEXT_LOG = ID_USER_PACKET_ENUM + 1,
	};

#pragma pack(push, 1)

	struct ConsoleMessageTextLog
	{
		__int64 dateSend;
		short foregroundR;
		short foregroundG;
		short foregroundB;
		short foregroundA;
		short backgroundR;
		short backgroundG;
		short backgroundB;
		short backgroundA;
		char log[512];
		short log_length;
	};

#pragma pack(pop)
}