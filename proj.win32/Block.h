#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Entity.h"

#define CELL_SIZE 25
#define BLOCK_WIDTH_COUNT 4

using namespace cocos2d;

class BlockManager;

class BlockI;

class Block:public Entity
{
public: //System functions
	Block();
	~Block();
	CREATE_FUNC(Block);
	virtual bool init();

public:
	typedef enum
	{
		Up,
		Down,
		Left,
		Right
	}Direction;
	typedef enum
	{
		I,
		L,
		L_Reverse,
		T,
		Z,
		Z_Reverse,
		O
	}BlockType;
	typedef struct
	{
		CCPoint points[4];
	}CellPosition;

public: //Custom functions
	virtual CellPosition doTurn90Degrees(bool saveState); //��ת���鲢������ת���λ����Ϣ saveState�����Ƿ񱣴���ת��Ľ��
	virtual bool doMove(Direction direction);
	void bindManager(BlockManager* manager);
//	void setIndexInArray(int index);
	bool increaseTimeCounter(int updateTime); //ʱ�������󷵻��Ƿ���Ҫ����λ��
	static Block* generateNewBlock();
	CellPosition getCellPosition();
	void resetTimeCounter(); //���ü�����
	void initializeBlock(); //��ʼ�������ڵ�����
	void setBlockData(CCPoint blockPoint, CCPoint stagePoint); //����ͨ���˺����趨blockData�����е�����ֵ
	BlockType getBlockType();
	int getDegree();
	

private:
//	virtual void _limitLine(Direction direction);
//	virtual bool _canMove(Direction direction);

protected:
	CCPoint m_blockData[BLOCK_WIDTH_COUNT][BLOCK_WIDTH_COUNT];
	BlockManager* m_manager;
	BlockType m_type;
	int m_timeCounter;
//	CCPoint m_position; //�Ծ�������Ϊ��׼ �ڹ������� ��Ӧ�������½ǵ�λ��
	int m_degree;
//	int m_indexInArray;

}; //class Block

#endif //__BLOCK_H__