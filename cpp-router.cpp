// cpp-router.cpp : Defines the entry point for the application.
//

#include "cpp-router.h"
#include "Sources/ConnectionHandler.h"

static void HandleIncommingCall(esl_socket_t server_sock, esl_socket_t client_sock, struct sockaddr_in* addr, void* user_data)
{
    ConnectionHandler* CurrentConnection = new ConnectionHandler(server_sock, client_sock, addr, user_data);
    CurrentConnection->HandleIncommingData();
}

int main()
{
    try
    {
        std::string sHost = "10.158.0.46";
        int iPort = 8085;
        esl_global_set_default_logger(ESL_LOG_LEVEL_DEBUG);
        esl_listen_threaded(
            sHost.data(),
            iPort,
			HandleIncommingCall,
			NULL,
			100000);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
