#pragma once

#include <unordered_map>
#include <memory>
#include "UIData.h"
typedef std::string(*_MSGPROC)(const std::string&);
class CFastCgiAction
{
public:
	CFastCgiAction();
	~CFastCgiAction();
	void InitMsgProcMap();

	std::string DisPatchFastCgiMsg(const std::string& strMsg, const std::string& strParameter);
private:
	std::unordered_map<std::string, _MSGPROC> mMsgProcTable;
};

