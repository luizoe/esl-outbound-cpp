#include <string>
#include <esl.h>

enum eCOMMAND_TYPE
{
	COMMAND_BEGIN = 0,
	COMMAND_API,
	COMMAND_BGAPI,
	COMMAND_SEND_MSG,
	COMMAND_SEND_EVENT,
	COMMAND_END
};

class CommandDispatcher 
{
	public:
		CommandDispatcher(esl_handle_t* eslHandlerFromParent);
		~CommandDispatcher();
		void SendCommand(std::string sFullCommandAsString, eCOMMAND_TYPE eTypeCommand);
	private:
		/* Pointer to property in ConnectionHandler */
		esl_handle_t* EslHandler;
};