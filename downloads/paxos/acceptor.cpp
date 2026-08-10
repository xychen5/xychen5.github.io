#include "Acceptor.h"


namespace paxos
{


Acceptor::Acceptor(void)
{
	m_maxSerialNum = 0;
	m_lastAcceptValue.serialNum = 0;
	m_lastAcceptValue.value = 0;
}

Acceptor::~Acceptor(void)
{
}
/***
//投票者
class Acceptor
{
public:
	Acceptor(void);
	virtual ~Acceptor(void);

	//同意投票
	bool Propose(unsigned int serialNum, PROPOSAL &lastAcceptValue);
	//接受提议
	bool Accept(PROPOSAL &value);

private:
	PROPOSAL		m_lastAcceptValue;//最后接受的提议
	unsigned int	m_maxSerialNum;//Propose提交的最大流水号
};


	//提议数据结构
	typedef struct PROPOSAL
	{
		unsigned int	serialNum;//流水号,1开始递增，保证全局唯一
		unsigned int	value;//提议内容
	}PROPOSAL;

***/
bool Acceptor::Propose(unsigned int serialNum, PROPOSAL &lastAcceptValue)
{
	if ( 0 == serialNum ) return false;
	//提议不通过
	if ( m_maxSerialNum > serialNum ) return false;
	//接受提议
    //请完善下面逻辑

	/**********Begin**********/
    //m_lastAcceptValue = lastAcceptValue;
    // If n is higher than every previous proposal number received, from any of the Proposers, by the Acceptor, 
    // then the Acceptor must return a message, which we call a "Promise", to the Proposer, to ignore all future 
    // proposals having a number less than n. If the Acceptor accepted a proposal at some point in the past, it 
    // must include the previous proposal number, say m, and the corresponding accepted value, say w, in its response to the Proposer.
    m_maxSerialNum = serialNum;
    
    lastAcceptValue = m_lastAcceptValue; // which contains m -> w
	/**********End**********/

	return true;
}

bool Acceptor::Accept(PROPOSAL &value)
{
	if ( 0 == value.serialNum ) return false;
	//Acceptor又重新答应了其他提议
   //请完善下面逻辑
	/**********Begin**********/
    if (m_maxSerialNum > value.serialNum ){
        return false;
    }
    // 然后接受新的提案
    m_lastAcceptValue = value;
	/**********End**********/

    
	//批准提议通过
    //请完善下面逻辑
    /**********Begin**********/
    m_maxSerialNum = value.serialNum;
	/**********End**********/

	return true;
}

}
