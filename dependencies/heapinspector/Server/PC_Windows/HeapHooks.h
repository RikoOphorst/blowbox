#ifndef _HEAPINSPECTORSERVER_PC_WINDOWS_HEAPHOOKS_H_
#define _HEAPINSPECTORSERVER_PC_WINDOWS_HEAPHOOKS_H_

#include "../HeapInspectorServerTypes.h"

BEGIN_NAMESPACE(HeapInspectorServer)

void InitialiseHeapHooks();
void ShutdownHeapHooks();

END_NAMESPACE(HeapInspectorServer)

#endif // _HEAPINSPECTORSERVER_PC_WINDOWS_HEAPHOOKS_H_