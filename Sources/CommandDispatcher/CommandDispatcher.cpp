#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(esl_handle_t* eslHandlerFromParent)
{
	this->EslHandler = eslHandlerFromParent;
}

CommandDispatcher::~CommandDispatcher()
{
	this->EslHandler = NULL;
}

void CommandDispatcher::SendCommand(std::string sFullCommandAsString, eCOMMAND_TYPE eTypeCommand)
{
	switch (eTypeCommand)
	{
		case eCOMMAND_TYPE::COMMAND_API:
		break;
		case eCOMMAND_TYPE::COMMAND_BGAPI:
		break;
		case eCOMMAND_TYPE::COMMAND_SEND_EVENT:
		break;
		case eCOMMAND_TYPE::COMMAND_SEND_MSG:
		break;
	}
}
