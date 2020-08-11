#include "plugin.h"
#include <errno.h>

static FORMATRESULT formatcpy_s(char* dest, size_t destCount, const char* source)
{
	switch (strncpy_s(dest, destCount, source, _TRUNCATE))
	{
	case 0:
		return FORMAT_SUCCESS;
	case ERANGE:
	case STRUNCATE:
		return FORMAT_BUFFER_TOO_SMALL;
	default:
		return FORMAT_ERROR;
	}
}

//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
	_plugin_registerformatfunction(pluginHandle, "timestamp", [](char* dest, size_t destCount, int argc, char* argv[], duint value, void* userdata)
	{
		SYSTEMTIME st;
		GetSystemTime(&st);
		char str[256] = "";
		sprintf_s(str, "%04d-%02d-%02dT%02d:%02d:%02d.%03d",
			st.wYear,
			st.wMonth,
			st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond,
			st.wMilliseconds
		);
		return formatcpy_s(dest, destCount, str);
	}, nullptr);
	return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
}
