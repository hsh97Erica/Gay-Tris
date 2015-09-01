#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "cocos2d.h"
#include "Block.h"
#include "DisplayManager.h"

#define CELL_MATRIX_WIDTH 10
#define CELL_MATRIX_HEIGHT 15
#define DEFAULT_REFRESH_TIME 30

using namespace cocos2d;

class BlockManager:public CCNode
{
public: //ϵͳ����
	
	BlockManager();
	~BlockManager();
	
	static BlockManager* create(CCPoint position);
	virtual bool init(CCPoint position);

	virtual void update(float delta); //��ʱˢ�º���

// 	virtual void pressedLeft();
// 	virtual void pressedRight();
// 	virtual void pressedDown();
// 	virtual void pressedUp();

public: //�����Զ��庯��
	int getUpdateTime(); //��ȡ����ʱ��
	void bindDisplayManager(DisplayManger* manager);
	virtual CCPoint convertBlockToPixel(CCPoint blockPoint); //����������ת��Ϊʵ�����꣨���½ǣ�
	virtual inline CCPoint convertRBToCenter(CCPoint rightBottomPoint)
	{
		CCPoint point = ccp(rightBottomPoint.x + CELL_SIZE / 2, rightBottomPoint.y + CELL_SIZE / 2);
		return point;
	}
	
public:
	typedef enum
	{
		Empty,
		Dropping,
		Dead
	}CellState;

private: //˽���Զ��庯��
	virtual Block* _createNewBlock(); //�����µķ���
	virtual void _pushNewBlock(); //�����µ�nextBlock �޸�Stage���� ����ԭnextBlock������̨

	virtual bool _shouldBlockTryDrop(); //�жϵ�ǰ�����Ƿ�Ӧ������һ��
	virtual void _donotTryDrop(); //����������
	virtual void _doTryDrop(); //��������

	virtual bool _currentBlockCanMove(Block::Direction direction); //�жϷ����Ƿ�������ض������ƶ�
	virtual void _currentBlockDoMove(Block::Direction direction); //ʹ��ǰ�����ƶ�
	virtual void _currentBlockStopDrop(); //ֹͣ��ǰ��������

	virtual void _updateCellMatrixForMove(Block::Direction direction); //ΪBlock�ƶ����µ�Ԫ����
	virtual void _updateCellMatrixForDie(); //ΪBlock�������µ�Ԫ����
	virtual int _eliminateLines(); //��������
	virtual bool _blockOverlayed(Block::CellPosition block1, Block::CellPosition block2); //�жϷ����Ƿ��ص�
	virtual void _endGame(); //������Ϸ

	virtual void _eliminateSingleLine(int lineNum); //�������У�����Ч��,������ݵȣ�
	virtual inline bool _isLineFilled(int linNum)
	{
		for (int i = 0; i < CELL_MATRIX_WIDTH; i++)
		{
			if (this->m_cellMatrix[linNum][i] != BlockManager::CellState::Dead)
			{
				return false;
			}
		}
		return true;
	} //�жϸ����Ƿ�����
	virtual void _eliminateMultiLine(int startLine); //�������������Ķ���
	virtual void _isTetris(int startLine); //Tetris����
	virtual void _rePaintDeadBlocks(); //�ػ�dead blocks
	

private:
	int m_updateTime;

	Block* m_currentBlock;
	Block* m_nextBlock;

	CellState m_cellMatrix[CELL_MATRIX_WIDTH][CELL_MATRIX_HEIGHT];
	DisplayManger* m_displayManager;
	CCSpriteBatchNode* m_deadBlockBatch;

}; //class BlockManager

#endif //!__BLOCK_MANAGER_H__