/*
 * messageHandleInterface.h
 *
 *  Created on: 2013-1-31
 *      Author: keym
 */

#ifndef MESSAGEHANDLEINTERFACE_H_
#define MESSAGEHANDLEINTERFACE_H_
#include"commondata/dataInfo.h"
#include"commondata/magicNum.h"
#include"commonfunction/netSocketFun.h"
#include"../handleEpollSocket.h"
#include<string.h>
//所有信息处理类的父类
class messageHandleInterface{
protected:
	unsigned _dataBodysize;
	unsigned _recvDatasize;
	void *_uperuser;
	int _recvSocketfd;
	int _sendSocketfd;
	commontype::headInfo *phead;
protected:
	messageHandleInterface():_uperuser(NULL)
	{
		this->phead = new commontype::headInfo;
	}
	virtual void packDataHead() = 0;
	virtual char *packDataBody() = 0;

	void mergeDataHeadAndBody()
	{
		char *pbody = this->packDataBody();//顺序不能换
		this->packDataHead();

		if(this->phead->_type == magicnum::messagetype::NULLTYPENUM)
		{
			return;
		}
		dataInfo *pdataInfo = new dataInfo;
		pdataInfo->PackMsg(this->_dataBodysize,(char*)this->phead,pbody);

		handleEpollSocket *_tempuser = (handleEpollSocket *)this->_uperuser;
		_tempuser->packData(pdataInfo);
		_tempuser->modEpollSocket(this->_sendSocketfd,true);
	}
public:
	void HandleMsg(unsigned size,int recvfd,void *uperuser)
	{
		this->_recvDatasize = size;
		this->_recvSocketfd = recvfd;
		this->_uperuser = uperuser;
		mergeDataHeadAndBody();
	}
public:
	virtual ~messageHandleInterface()
	{
		if(this->phead != NULL)
		{
			delete this->phead;
		}
	}
};

#endif /* MESSAGEHANDLEINTERFACE_H_ */
