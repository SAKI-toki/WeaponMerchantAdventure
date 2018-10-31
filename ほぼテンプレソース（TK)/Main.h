#pragma once
#ifdef _DEBUG 
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW 
#endif 
#endif  // _DEBUG
#include "pch.h"
#include "Game.h"
#include <Dbt.h>
#include "Audio.h"

#include "src/common/common.h"
namespace
{
	std::unique_ptr<Game> g_game;
};