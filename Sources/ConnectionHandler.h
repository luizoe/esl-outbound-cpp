#include <esl.h>
#include <esl_oop.h>

class ConnectionHandler
{
	public:
		ConnectionHandler(esl_socket_t server_sock, esl_socket_t client_sock, struct sockaddr_in* addr, void* user_data);
		~ConnectionHandler();
		void HandleIncommingData();
	private:
		void ConfigureConnection();
		ESLevent* RecvEvent();
		ESLevent* RecvEventTimed(int ms);
		esl_handle_t EslHandler = { {0} };
};