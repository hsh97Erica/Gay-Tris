#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "cocos2d.h"
#include "Block.h"
#include "DisplayManager.h"

using namespace cocos2d;

class BlockManager:public CCNode
{
public: 
	typedef enum
	{
		Empty,
		Dropping,
		Dead
	}CellState;
	static const int CellMatrixWidth = 10;
	static const int CellMatrixHeight = 20;
	static const int DefaultRefreshTime = 80;
	static const int RequiredUpdateTime = 2;

protected:
	int m_periodDropping;
	bool m_isKeyboardPressed;

	Block* m_blockDropping;
	Block* m_blockWaiting;

	CellState m_matrixCellState[BlockManager::CellMatrixWidth][BlockManager::CellMatrixHeight];
	CCSprite* m_matrixDeadBlockSprites[BlockManager::CellMatrixWidth][BlockManager::CellMatrixHeight];

	DisplayManger* m_boundDisplayManager;
	CCSpriteBatchNode* m_spriteBatchNodeDeadBlocks;


public: //ϵͳ����
	
	BlockManager();
	~BlockManager();
	
	static BlockManager* create(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerTobind);
	virtual bool init(CCPoint p_pointToDisplayOnScreen, DisplayManger* p_displayManagerTobind);

	virtual void update(float p_delta); //��ʱˢ�º���

	virtual void triggerKeyboard(int p_valueKey);

public: //�����Զ��庯��
	int getUpdateTime(); //��ȡ����ʱ��
	void setUpdateTime(int p_updateTime);
	virtual CCPoint convertBlockPositionToPixelPosition(CCPoint p_pointBlock); //����������ת��Ϊʵ�����꣨���½ǣ�
	virtual inline CCPoint convertPositionToCenterPosition(CCPoint p_pointRightBottom)
	{
		CCPoint pointResult = ccp(p_pointRightBottom.x + Block::CellSize / 2, p_pointRightBottom.y + Block::CellSize / 2);
		return pointResult;
	}
	void setKeyboardState(bool p_isKeyPressed); //�趨��������״̬ 

protected: //˽���Զ��庯��
	virtual Block* _createNewBlock(); //�����µķ���
	virtual void _pushNewBlock(); //�����µ�nextBlock �޸�Stage���� ����ԭnextBlock������̨

	virtual bool _shouldBlockTryDrop(int updateTime); //�жϵ�ǰ�����Ƿ�Ӧ������һ��
	virtual void _donotTryDrop(); //����������
	virtual void _doTryUpdateDrop(); //���Զ�ʱ����
	virtual void _doTryMove(Block::Direction direction); //����ƽ��
	virtual void _doTryRequiredDrop(); //���Դ�������
	virtual void _doTryTurn90Degrees(); //������ת90��

	virtual bool _currentBlockCanMove(Block::Direction direction); //�жϷ����Ƿ�������ض������ƶ�
	virtual void _currentBlockDoMove(Block::Direction direction); //ʹ��ǰ�����ƶ�
	virtual void _currentBlockStopDrop(); //ֹͣ��ǰ��������
	virtual bool _currentBlockCanTurn90Degrees(); //�жϷ����Ƿ������ת90��
	virtual void _currentBlockDoTurn90Degrees(); //ʹ��ǰ������ת

	virtual void _updateCellMatrixBeforeMove(Block::Direction direction); //ΪBlock�ƶ����µ�Ԫ����
	virtual void _updateCellMatrixBeforeDie(); //ΪBlock�������µ�Ԫ����
	virtual void _updateCellMatrixAfterChanged(Block::CellPosition originalPosition, Block::CellPosition newPosition); //��position���¾���
	virtual int _eliminateLines(); //��������
	bool BlockManager::_blockOverlayed(Block::CellPosition p_block1, Block::CellPosition p_block2);
	virtual void _endGame(); //������Ϸ

	virtual void _eliminateSingleLine(int lineNum); //�������У�����Ч��,������ݵȣ�
	virtual inline bool _isLineFilled(int lineNum)
	{
		for (int i = 0; i < BlockManager::CellMatrixWidth; i++)
		{
			if (this->m_matrixCellState[i][lineNum] != BlockManager::CellState::Dead)
			{
				return false;
			}
		}
		return true;
	} //�жϸ����Ƿ�����
	virtual void _isTetris(int startLine); //Tetris����
	virtual void _rePaintDeadBlocks(); //�ػ�dead blocks
	

}; //class BlockManager

#endif //!__BLOCK_MANAGER_H__