//
// Created by alex on 08/02/2021.
//

#ifndef PAWN_TOML_PAWN_NATIVES_H
#define PAWN_TOML_PAWN_NATIVES_H

#define PAWN_NATIVE_DECL(export, func) \
	{ export, n_##func }

#define PAWN_NATIVE_DEFN(native) \
	cell n_##native(AMX* amx, cell* params)

#define PAWN_EXPORT PLUGIN_EXPORT


#endif //PAWN_TOML_PAWN_NATIVES_H
