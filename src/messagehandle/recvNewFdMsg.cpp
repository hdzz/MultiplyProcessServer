/*
 * handleReqSendfdMsg.cpp
 *
 *  Created on: 2013-2-1
 *      Author: keym
 */
#include"childProcess.h"

#include"messagehandle/recvNewFdMsg.h"
#include"commonfunction/netSocketFun.h"
#include<unistd.h>
commontype::headInfo *recvNewFdMsg::packDataHead()
{
	childProcess *_tempuser = (childProcess *)this->_uperuser;
	_tempuser->acceptClientSocket();
	_tempuser->AddEpollSocket(_tempuser->GetSocketfd('c'));
	return NULL;
}

char *recvNewFdMsg::packDataBody()
{
	int readbytes;
	char *readbuf = new char[this->_recvDatasize];
	if((readbytes=RepeatRecv(this->_recvSocketfd,readbuf,this->_recvDatasize)) < 0)
	{
		//这里可能是客户端关闭或出现错误
		return 0;
	}
	this->_dataBodysize = 0;
	return NULL;
}
