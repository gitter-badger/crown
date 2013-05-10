#pragma once

#include "lua.hpp"

#include "Types.h"
#include "String.h"
#include "ScriptResource.h"

#include "Vec3.h"
#include "Mat4.h"
#include "Quat.h"


namespace crown
{

/// Abstraction of lua state.
/// It provides 2 ways for loading lua code, as a buffer or as a string.
/// It must be included only by ScriptSystem. 
class LuaState
{
public:
							/// Constructor, private for singleton
							LuaState();
							/// Destructor
							~LuaState();
							/// Load lua chunk as buffer
	int32_t 				load_buffer(const char* buf, size_t len);
							/// Load lua chunk as string
	int32_t					load_string(const char* str);
							/// Executes lua chunk loaded in stack
	int32_t 				execute();

private:

							/// Lua state incapsulated by this class
	lua_State*				m_state;
};

/// ScriptSystem allows to execute lua code or bytecode chunks
///
class ScriptSystem
{
public:
								/// Constructor
								ScriptSystem();
								///	Destructor
								~ScriptSystem();
								/// Load script resource
	void						load(ScriptResource* script);
								/// Execute 
	void						execute();
								/// Unload script resource
	void						unload(ScriptResource* script);
								/// Returns the first free Vec3
	Vec3*						get_next_vec3(float nx, float ny, float nz);
								/// Returns the first free Mat4
	Mat4*						get_next_mat4(float r1c1, float r2c1, float r3c1, float r1c2, float r2c2, float r3c2, float r1c3, float r2c3, float r3c3);	
								/// Return the first free Quat
	Quat*						get_next_quat(float angle, const Vec3* v);

								/// Max number of temporary objects allowed
	static const uint32_t		MAX_TEMP_OBJECTS = 2048;


private:
								// Disable coping
								ScriptSystem(const ScriptSystem&);
								ScriptSystem& operator=(const ScriptSystem&);

	LuaState 					m_state;

								/// Vectors used by lua environment
	Vec3						m_vec3_list[MAX_TEMP_OBJECTS];
								/// Counter which points to the next free Vec3
	uint32_t					m_vec3_count;
								/// Matrix used by lua environment
	Mat4						m_mat4_list[MAX_TEMP_OBJECTS];
								/// Counter which points to the next free Mat4
	uint32_t					m_mat4_count;
								/// Quaternions used by lua environment
	Quat						m_quat_list[MAX_TEMP_OBJECTS];
								/// Counter which points to the nect free Quat
	uint32_t					m_quat_count;
};

ScriptSystem* scripter();

} // namespace crown