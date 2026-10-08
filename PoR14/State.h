#pragma once

enum class ActState
{
	attack,
	heal,
	buff,
	debuff
};


enum class EntityState
{
	player,
	enemy
};

struct LogState
{
	EntityState entityState;
	ActState actState;
	int32 value;
};
