#include "stdafx.h"
#include "aStar.h"


HRESULT aStar::init(int maxWidthIndex, int maxHeightIndex)
{
	_maxWidthIndex = maxWidthIndex;
	_maxHeightIndex = maxHeightIndex;

	aStarTile * node;

	for (int i = 0; i < maxHeightIndex; ++i)
	{
		for (int j = 0; j < maxWidthIndex; ++i)
		{
			node = new aStarTile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}

	_count = 0;
	_isStart = false;
	return S_OK;
}

void aStar::release(void)
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->release();
		SAFE_DELETE(_vTotalList[i]);
	}
}

void aStar::update(void)
{

}

void aStar::render(void)
{

}

void aStar::seting(POINT start, POINT end)
{
	setting(start.x, start.y, end.x, end.y);
}

void aStar::setting(int startX, int startY, int endX, int endY)
{
	_startTile = _vTotalList[startY * _maxWidthIndex + startX];
	_endTile = _vTotalList[endY * _maxWidthIndex + endX];

	_currentTile = _startTile;
}

HRESULT aStar::initNode()
{
	_vOpenList.clear();

	for (int i = 0; i < _maxHeightIndex; ++i)
	{
		for (int j = 0; j < _maxWidthIndex; ++j)
		{
			_vTotalList[i * _maxWidthIndex + j]->init(j, i);
		}
	}

	return S_OK;
}

vector<POINT> aStar::startPathFind(POINT start, POINT end)
{
	return startPathFind(start.x, start.y, end.x, end.y);
}

vector<POINT> aStar::startPathFind(int startX, int startY, int endX, int endY)
{
	initNode();

	setting(startX, startY, endX, endY);

	aStarTile * tempTile;
	int closedTileIndex;

	while (true)
	{
		addOpenList(_currentTile);
		if (_vOpenList.size() <= 0) return vector<POINT>();
	}

	int totalCost = 100000000;
	for (int i = 0; i < _vOpenList.size(); ++i)
	{
		if (totalCost > _vOpenList[i]->getTotalCost())
		{
			totalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
			closedTileIndex = i;
		}
	}

	if (tempTile == _endTile)
	{
		vector<POINT> routing;

		routing.push_back(tempTile->getIndex());

		while (_currentTile->getParentNode() != NULL)
		{
			routing.push_back(_currentTile->getIndex());
			_currentTile = _currentTile->getParentNode();
		}

		return routing;
	}

	tempTile->setState(CLOSE);
	_vOpenList.erase(_vOpenList.begin() + closedTileIndex);

	_currentTile = tempTile;
}

void aStar::addOpenList(aStarTile * currentTile)
{
	POINT temp = currentTile->getIndex();
	int startX = temp.x - 1,
		startY = temp.y - 1,
		endX = temp.x + 1,
		endY = temp.y + 1;

	if (startX < 0) startX = 0;
	else if (startX >= _maxWidthIndex) startX = _maxWidthIndex - 1;
	if (startY < 0) startY = 0;
	else if (startY >= _maxHeightIndex) startY = _maxHeightIndex - 1;

	if (endX < 0) endX = 0;
	else if (endX >= _maxWidthIndex) endX = _maxWidthIndex - 1;
	if (endY < 0) endY = 0;
	else if (endY >= _maxHeightIndex) endY = _maxHeightIndex - 1;

	aStarTile * node;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			if (i == temp.y && j == temp.x) continue;

			node = _vTotalList[i * _maxWidthIndex + j];
			if (node->getState() == CLOSE) continue;
			if (node == _startTile)continue;
			if ((getDistance(currentTile->getPos().x, currentTile->getPos().y, node->getPos().x, node->getPos().y) > TILESIZE))
			{
				continue;
			}

			int costToEnd = ((abs(_endTile->getIndex().x - node->getIndex().x) + abs(_endTile->getIndex().y - node->getIndex().y)) * 10);
			POINT center1 = currentTile->getPos();
			POINT center2 = node->getPos();

			int costFromStart = currentTile->getCostFromStart() + ((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10);
			int totalCost = (costToEnd + costFromStart);

			if (node->getState() == NONE)
			{
				node->setParentNode(currentTile);
				node->setState(OPEN);

				node->setCostToGoal(costToEnd);
				node->setCostFromStart(costFromStart);
				node->setTotalCost(totalCost);

				_vOpenList.push_back(node);
			}
			else if (node->getState() == OPEN)
			{
				if (totalCost < node->getTotalCost() || (totalCost == node->getTotalCost() && costFromStart < node->getCostFromStart()))
				{
					node->setParentNode(currentTile);
					node->setCostToGoal(costToEnd);
					node->setCostFromStart(costFromStart);
					node->setTotalCost(totalCost);
				}
			}

		}
	}
}
