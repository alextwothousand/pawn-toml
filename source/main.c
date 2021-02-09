//
// Created by alex on 08/02/2021.
//

#include "main.h"

PAWN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PAWN_EXPORT bool PLUGIN_CALL Load(void** ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	return true;
}

const AMX_NATIVE_INFO native_list[] = {
	PAWN_NATIVE_DECL("Toml_Parse", TomlParse),
	{ nullptr, nullptr }
};

PAWN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx)
{
	return amx_Register(amx, native_list, -1);
}

PAWN_EXPORT int PLUGIN_CALL Unload()
{
	return 1;
}

PAWN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx)
{
	return 1;
}