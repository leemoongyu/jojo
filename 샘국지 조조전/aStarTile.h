#pragma once
#include "gameNode.h"

enum { NONE, OPEN, CLOSE };

class aStarTile : public gameNode
{
private:
	POINT _index, _pos;

	float _totalCost;				//�� ��� : f = g + h
	float _costFromStart;			//���������� ���� ������ ��κ�� - g
	float _costToGoal;				//���� ������ ���������� ��κ�� - h

	bool _isOpen;

	int _state;

	aStarTile * _parentNode;

	string _attribute;
	RECT _rcAttribute;

public:

	HRESULT init();
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	POINT getIndex() { return _index; }
	POINT getPos() { return _pos; }

	string getAttribute(void) { return _attribute; }
	void setAttribute(string atr) { _attribute = atr; }

	RECT getRcAttribute(void) { return _rcAttribute; }
	void setRcAttribute(RECT rcAttribute) { _rcAttribute = rcAttribute; }

	int getState() { return _state; }
	void setState(int state) { _state = state; }

	float getTotalCost(void) { return _totalCost; }
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getCostToGoal(void) { return _costToGoal; }
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostFromStart(void) { return _costFromStart; }
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }

	aStarTile * getParentNode(void) { return _parentNode; }
	void setParentNode(aStarTile* t) { _parentNode = t; }

	bool getIsOpen(void) { return _isOpen; }
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	

	aStarTile() { init(); }
	~aStarTile(){}
};

