//----------------------------------------------------------------------------------
//  FIleName : PiScriptLuaCommand.cpp
//                     
//	Class Name:	Lua���� �� C ��ǵ�
//
//  Desc: Lua���� �� C��ǵ��� 
//
//----------------------------------------------------------------------------------
#include ".\PiScript.h"
#include ".\PiScriptLuaCommand.h"

#include "..\\HoNewEffectHeader.h"
#ifndef _HO_NEW_WIN32_
#include "..\\..\\MainWnd.h"
#endif

#ifdef _HO_NEW_WIN32_
#include "..\\HoEffectMain.h"
#endif

/*
//���� ���� �Լ� (���͸�)
LUA_TNIL, 
LUA_TNUMBER, 
LUA_TBOOLEAN, 
LUA_TSTRING, 
LUA_TTABLE, 
LUA_TFUNCTION, 
LUA_TUSERDATA, 
LUA_TTHREAD, 
LUA_TLIGHTUSERDATA

int lua_type            (lua_State *L, int index);
int lua_isnil           (lua_State *L, int index);
int lua_isboolean       (lua_State *L, int index);
int lua_isnumber        (lua_State *L, int index);
int lua_isstring        (lua_State *L, int index);

*/

// ���� �ѱ� �޴��� ���� http://www.lifeisforu.net/programming/lua/
int luaCommand_Begin( lua_State *pLuaState)
{
    //Stack�� �� �ִ� �� ������ ���Ѵ�.(�Լ��� 1���� ���� �ϹǷ� ���ڰ��� �ϳ� �Ѿ���� 2�� �ȴ�)
    int count = lua_gettop( pLuaState );

    //ù��° �Ķ���Ͱ� ���ڿ��̶��
    if (lua_isstring( pLuaState, 1))
        PARTICLEFACTORY->LuaBegin(lua_tostring(pLuaState, 1));

    if (count == 2)
        PARTICLEFACTORY->LuaBegin(lua_tostring(pLuaState, 1), lua_tostring(pLuaState, 2));
	return 1;
}

int luaCommand_End( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaEnd();
	return 1;
}

int luaCommand_InitPos( lua_State *pLuaState)
{

    PARTICLEFACTORY->LuaInitPos((float)lua_tonumber(pLuaState, 1),
                          (float)lua_tonumber(pLuaState, 2),
                          (float)lua_tonumber(pLuaState, 3));
    
	return 1;
}

int luaCommand_InitMeshName( lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
	char buffer1[256];
	char buffer2[256];
	if(count == 1)
	{
		strcpy(buffer1, "Effect\\NewEffect\\");
 		strcat(buffer1, lua_tostring(pLuaState, 1));
        PARTICLEFACTORY->LuaInitMeshName( buffer1, NULL);
	}
    else if(count == 2)
	{
		strcpy(buffer1, "Effect\\NewEffect\\");
 		strcat(buffer1, lua_tostring(pLuaState, 1));

		strcpy(buffer2, "Effect\\NewEffect\\");
 		strcat(buffer2, lua_tostring(pLuaState, 2));
        PARTICLEFACTORY->LuaInitMeshName( buffer1, buffer2);
	}
	return 1;
}

int luaCommand_InitMaxFrame( lua_State *pLuaState )
{
    PARTICLEFACTORY->LuaInitMaxFrame( (float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitStartDelayTime( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitStartDelayTime( (float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitLoop( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitLoop( (int)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitTextureName ( lua_State *pLuaState)
{
    char buffer[256];
 	strcpy(buffer, "Effect\\NewEffect\\");
	strcat(buffer, lua_tostring(pLuaState, 1));
 	PARTICLEFACTORY->LuaInitTextureName( buffer);
	return 1;
}

int luaCommand_InitAniTextureName ( lua_State *pLuaState)
{
    char buffer[256];
 	strcpy(buffer, "Effect\\NewEffect\\");
 	strcat(buffer, lua_tostring(pLuaState, 1));
 	PARTICLEFACTORY->LuaInitTextureName( buffer);

	PARTICLEFACTORY->LuaInitAniTextureName( buffer,
                                      (int)lua_tonumber(pLuaState, 2),
                                      (float)lua_tonumber(pLuaState, 3));
	return 1;
}

int luaCommand_InitColor( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitColor( (float)lua_tonumber(pLuaState, 1),
                             (float)lua_tonumber(pLuaState, 2),
                             (float)lua_tonumber(pLuaState, 3),
                             (float)lua_tonumber(pLuaState, 4));
	return 1;
}

int luaCommand_EventColor ( lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 5)
    {
        PARTICLEFACTORY->LuaEventColor((float)lua_tonumber(pLuaState, 1),
                                 (float)lua_tonumber(pLuaState, 2),
                                 (float)lua_tonumber(pLuaState, 3),
                                 (float)lua_tonumber(pLuaState, 4),
                                 (float)lua_tonumber(pLuaState, 5));
    }
	return 1;
}

int luaCommand_EventSize ( lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 4)
    {
        PARTICLEFACTORY->LuaEventSize( (float)lua_tonumber(pLuaState, 1),
                                 (float)lua_tonumber(pLuaState, 2),
                                 (float)lua_tonumber(pLuaState, 3),
                                 (float)lua_tonumber(pLuaState, 4));
    }
	return 1;
}

int luaCommand_EventFadeColor (lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 5) //���ڰ� 4���̴�(eventtime, r, g, b, a)
    {
        PARTICLEFACTORY->LuaEventFadeColor( (float)lua_tonumber(pLuaState, 1),
                                      (float)lua_tonumber(pLuaState, 2),
                                      (float)lua_tonumber(pLuaState, 3),
                                      (float)lua_tonumber(pLuaState, 4),
                                      (float)lua_tonumber(pLuaState, 5));
    }
	return 1;
}

int luaCommand_EventFadeSize (lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 4) //���ڰ� 4���̴�(eventtime, r, g, b, a)
    {
        PARTICLEFACTORY->LuaEventFadeSize( (float)lua_tonumber(pLuaState, 1),
                                     (float)lua_tonumber(pLuaState, 2),
                                     (float)lua_tonumber(pLuaState, 3),
                                     (float)lua_tonumber(pLuaState, 4));
    }
	return 1;
}


int luaCommand_InitEndTime(lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 1)
        PARTICLEFACTORY->LuaInitEndTime( (float)lua_tonumber(pLuaState, 1));
    if(count == 2)
        PARTICLEFACTORY->LuaInitEndTime( (float)lua_tonumber(pLuaState, 1), (float)lua_tonumber(pLuaState, 2));
	return 1;
}

int luaCommand_InitSize(lua_State *pLuaState)
{
    int count = lua_gettop( pLuaState );
    if(count == 2)
    {
        PARTICLEFACTORY->LuaInitSize( (float)lua_tonumber(pLuaState, 1),
                                (float)lua_tonumber(pLuaState, 2));
    }

    if(count == 4)
    {
        PARTICLEFACTORY->LuaInitSize( (float)lua_tonumber(pLuaState, 1),
                                (float)lua_tonumber(pLuaState, 2),
                                (float)lua_tonumber(pLuaState, 3),
                                (float)lua_tonumber(pLuaState, 4));
    }
	return 1;
}

int luaCommand_InitBlendType(lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitBlendType( lua_tostring(pLuaState, 1) );
	return 1;
}

int luaCommand_InitSpawnBoundingBox(lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitSpawnBoundingBox( (float)lua_tonumber(pLuaState, 1),
                                        (float)lua_tonumber(pLuaState, 2),
                                        (float)lua_tonumber(pLuaState, 3),
                                        (float)lua_tonumber(pLuaState, 4),
                                        (float)lua_tonumber(pLuaState, 5),
                                        (float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitSpawnBoundingSphere(lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitSpawnBoundingSphere( (float)lua_tonumber(pLuaState, 1),
                                           (float)lua_tonumber(pLuaState, 2));
	return 1;
}

int luaCommand_InitSpawnBoundingDoughnut ( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitSpawnBoundingDoughnut( (float)lua_tonumber(pLuaState, 1),
                                             (float)lua_tonumber(pLuaState, 2),
                                             (float)lua_tonumber(pLuaState, 3),
                                             (float)lua_tonumber(pLuaState, 4));
    return 1;
}

int luaCommand_InitParticleNum ( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitParticleNum( (float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitEmitRate ( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitEmitRate( (float)lua_tonumber(pLuaState, 1));
	return 1;
}

int luaCommand_InitAxialPos( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitAxialPos( (float)lua_tonumber(pLuaState, 1),
                              (float)lua_tonumber(pLuaState, 2),
                              (float)lua_tonumber(pLuaState, 3),
                              (float)lua_tonumber(pLuaState, 4),
                              (float)lua_tonumber(pLuaState, 5),
                              (float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitVelocity( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitVelocity( (float)lua_tonumber(pLuaState, 1),
                              (float)lua_tonumber(pLuaState, 2),
                              (float)lua_tonumber(pLuaState, 3),
                              (float)lua_tonumber(pLuaState, 4),
                              (float)lua_tonumber(pLuaState, 5),
                              (float)lua_tonumber(pLuaState, 6));
	return 1;
}

int luaCommand_InitParticleType( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitParticleType( lua_tostring(pLuaState, 1) );
	return 1;
}

int luaCommand_InitVelocityType( lua_State *pLuaState)
{
    PARTICLEFACTORY->LuaInitVelocityType( lua_tostring(pLuaState, 1) );
	return 1;
}



