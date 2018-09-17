#include "stdafx.h"
#include "aStarTile.h"
#include "aStar.h"

HRESULT aStarTile::init()
{

	return init(0,0);
}

HRESULT aStarTile::init(int x, int y)
{
	_index = { x,y };
	_pos = { x * TILESIZE + TILESIZE / 2,y * TILESIZE + TILESIZE / 2 };

	_totalCost = _costFromStart = _costToGoal = 0;

	_state = NONE;
	
	_parentNode = NULL;

	return S_OK;
}

void aStarTile::release(void)
{
}

void aStarTile::update(void)
{
}

void aStarTile::render(void)
{
}
