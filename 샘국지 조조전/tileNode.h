#pragma once

// ����� ����
#define MOVE_RANGE_TOP 36
#define MOVE_RANGE_BOTTOM 25

#define ATTRANGE 8

/*
2 = 12
3 = 24
4 = 40
5 = 60
6 = 84
7 = 112
8 = 144
*/

//����ȭ��Ÿ�� (ȭ�� ����) 
#define TILESIZE 64
#define TILEX 32
#define TILEY 32
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)

//�̹���Ÿ�� (ȭ�� �����ʻ��)
#define SAMPLETILEX 4
#define SAMPLETILEY 5

// �̹��� �׵θ� ( ȭ�� ������ ���)
#define EDGESIZE 70
#define BOX_X 4
#define BOX_Y 5

enum PAGE
{
	PAGE_ONE, PAGE_TWO, PAGE_THREE
};

//�������� ����� �̳ѹ�
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAINDRAW, CTRL_OBJDRAW, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//����
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJECT_BLOCK1, OBJECT_BLOCK3, OBJECT_BLOCKS,
	OBJECT_TANK1, OBJECT_TANK2,
	OBJECT_FLAG1, OBJECT_FLAG2,
	OBJECT_NONE
};

//��ġ��ǥ
enum POS
{
	POS_TANK1, POS_TANK2, POS_FLAG1, POS_FLAG2
};

/*Ÿ�ϱ���ü*/
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	image * image;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	int x;
	int y;
};

//�̹��� Ÿ�ϱ���ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};