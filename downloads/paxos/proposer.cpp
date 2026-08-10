#include "Proposer.h"

namespace paxos
{

Proposer::Proposer()
{
	SetPlayerCount(0, 0);
}

Proposer::Proposer(short proposerCount, short acceptorCount)
{
	SetPlayerCount(proposerCount, acceptorCount);
}

Proposer::~Proposer()
{
}

void Proposer::SetPlayerCount(short proposerCount, short acceptorCount)
{
	m_proposerCount = proposerCount;
	m_acceptorCount = acceptorCount;

	return;
}

void Proposer::StartPropose(PROPOSAL &value)
{
	m_value = value;
	m_proposeFinished = false;
	m_isAgree = false;
	m_maxAcceptedSerialNum = 0;
	m_okCount = 0;
	m_refuseCount = 0;
	m_start = time(NULL);

	return;
}

PROPOSAL& Proposer::GetProposal()
{
	return m_value;
}
/**
//提议者
class Proposer
{
public:
	Proposer();
	Proposer(short proposerCount, short acceptorCount);
	virtual ~Proposer();
	//设置参与者数量
	void SetPlayerCount(short proposerCount, short acceptorCount);
	//开始Propose阶段
	void StartPropose(PROPOSAL &value);
	//取得提议
	PROPOSAL& GetProposal();
	//提议被投票，Proposed失败则重新开始Propose阶段
	bool Proposed(bool ok, PROPOSAL &lastAcceptValue);
	//开始Accept阶段,满足条件成功开始accept阶段返回ture，不满足开始条件返回false
	bool StartAccept();
	//提议被接受，Accepted失败则重新开始Propose阶段
	bool Accepted(bool ok);
	//提议被批准
	bool IsAgree();

private:
	short			m_proposerCount;///proposer数量
	short			m_acceptorCount;//acceptor数量
	PROPOSAL		m_value;//预备提议
	bool			m_proposeFinished;//完成拉票，准备开始二阶段
	bool			m_isAgree;//m_value被批准
	unsigned int	m_maxAcceptedSerialNum;//已被接受的提议中流水号最大的
	time_t			m_start;//阶段开始时间，阶段一，阶段二共用
	short			m_okCount;//投票数量，阶段一，阶段二共用
	short			m_refuseCount;//拒绝数量，阶段一，阶段二共用
};


	//提议数据结构
	typedef struct PROPOSAL
	{
		unsigned int	serialNum;//流水号,1开始递增，保证全局唯一
		unsigned int	value;//提议内容
	}PROPOSAL;
**/
bool Proposer::Proposed(bool ok, PROPOSAL &lastAcceptValue)
{
	if ( m_proposeFinished ) return true;//可能是一阶段迟到的回应，直接忽略消息

	if ( !ok ) 
	{
		m_refuseCount++;
		//已有半数拒绝，不需要等待其它acceptor投票了，重新开始Propose阶段
		//使用StartPropose(m_value)重置状态
	
        //请完善下面逻辑
 		/**********Begin**********/
        if ( m_refuseCount > m_acceptorCount/2 ){
            // 重新开始投票阶段，将提案号自增
            m_value.serialNum += 5;
            StartPropose(m_value);
            return false;
        }
	    /**********End**********/





	

		//拒绝数不到一半
		return true;
	}

	m_okCount++;
	/*
		没有必要检查分支：serialNum为null
		因为serialNum>m_maxAcceptedSerialNum，与serialNum非0互为必要条件
	*/
	//如果已经有提议被接受，修改成已被接受的提议
	//请完善下面逻辑
 	/**********Begin**********/
     
    if(lastAcceptValue.serialNum > m_maxAcceptedSerialNum){
        m_value.value = lastAcceptValue.value;
        m_maxAcceptedSerialNum = lastAcceptValue.serialNum;
        return true;
    }
	/**********End**********/	





	//如果自己的提议被接受
	if ( m_okCount > m_acceptorCount / 2 ) 
	{
		m_okCount = 0;
		m_proposeFinished = true;
	}
	return true;
}

bool Proposer::StartAccept()
{
	return m_proposeFinished;
}

bool Proposer::Accepted(bool ok)
{
	if ( !m_proposeFinished ) return true;//可能是上次第二阶段迟到的回应，直接忽略消息

	if ( !ok ) 
	{
		m_refuseCount++;
		//已有半数拒绝，不需要等待其它acceptor投票了，重新开始Propose阶段
		//使用StartPropose(m_value)重置状态
	    //请完善下面逻辑
        /**********Begin**********/
        if ( m_refuseCount > m_acceptorCount/2 ){
            // 重新开始投票阶段，将提案号自增
            m_value.serialNum += 5;
            StartPropose(m_value);
            return false;
        }
        /**********End**********/
 		





	
		return true;
	}

	m_okCount++;
	if ( m_okCount > m_acceptorCount / 2 ) m_isAgree = true;

	return true;
}

bool Proposer::IsAgree()
{
	return m_isAgree;
}

}
