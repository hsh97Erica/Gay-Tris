#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class BlockManager;

class BlockI;

class Block:public Entity
{
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

	static const int CellSize = 25;
	static const int BlockWidthCount = 4;

protected:
	CCPoint m_blockData[Block::BlockWidthCount][Block::BlockWidthCount];
	BlockManager* m_manager;
	BlockType m_type;
	int m_timeCounter;
	int m_degree;

public: //System functions
	Block();
	~Block();
	static Block* create(BlockManager* p_blockManagerToBind);
	virtual bool init(BlockManager* p_blockManagerToBind);

public: //Custom functions
	virtual CellPosition doTurn90Degrees(bool saveState); //��ת���鲢������ת���λ����Ϣ saveState�����Ƿ񱣴���ת��Ľ��
	virtual bool doMove(Direction direction);
	void bindManager(BlockManager* manager);
	bool increaseTimeCounter(int updateTime); //ʱ�������󷵻��Ƿ���Ҫ����λ��
	static Block* generateNewBlock(BlockManager* blockManagerToBind);
	CellPosition getCellPosition();
	void resetTimeCounter(); //���ü�����
	void initializeBlock(); //��ʼ�������ڵ�����
	void setBlockData(CCPoint blockPoint, CCPoint stagePoint); //����ͨ���˺����趨blockData�����е�����ֵ
	BlockType getBlockType();
	int getDegree();
	
}; //class Block

#endif //__BLOCK_H__