#include "ConnectionHandler.h"

ConnectionHandler::ConnectionHandler(esl_socket_t server_sock, esl_socket_t client_sock, sockaddr_in* addr, void* user_data)
{
	// Say freeswitch we are connected
	esl_attach_handle(&this->EslHandler, client_sock, addr);
	esl_log(ESL_LOG_INFO, "Connected! %d\n", this->EslHandler.sock);
	// Make configuration for current Connection
	ConfigureConnection();
}

ConnectionHandler::~ConnectionHandler()
{
	esl_log(ESL_LOG_INFO, "Disconnected! %d\n", this->EslHandler.sock);
	esl_disconnect(&this->EslHandler);
}

ESLevent* ConnectionHandler::RecvEvent()
{
	if (esl_recv_event(&this->EslHandler, 1, NULL) == ESL_SUCCESS) {
		esl_event_t* e = this->EslHandler.last_ievent ? this->EslHandler.last_ievent : this->EslHandler.last_event;
		if (e) {
			esl_event_t* event;
			esl_event_dup(&event, e);
			return new ESLevent(event, 1);
		}
	}

	return new ESLevent("server_disconnected");
}

ESLevent* ConnectionHandler::RecvEventTimed(int ms)
{

	if (esl_recv_event_timed(&this->EslHandler, ms, 1, NULL) == ESL_SUCCESS) {
		esl_event_t* e = this->EslHandler.last_ievent ? this->EslHandler.last_ievent : this->EslHandler.last_event;
		if (e) {
			esl_event_t* event;
			esl_event_dup(&event, e);
			return new ESLevent(event, 1);
		}
	}

	return NULL;
}

void ConnectionHandler::HandleIncommingData()
{
	ESLevent* CurrentEvent;
	CurrentEvent = RecvEvent();
	cJSON* jsonParsed = cJSON_Parse(CurrentEvent->getBody());
	esl_log(ESL_LOG_INFO, "Got a disconnection notice dispostion: [%s]\n", jsonParsed->string);
}

void ConnectionHandler::ConfigureConnection()
{
	//Resume our handling
	esl_send_recv(&this->EslHandler, "resume");
	//Tells FreeSWITCH not to close the socket connection when a channel hangs up. Instead, it keeps the socket connection open until the last event related to the channel has been received by the socket client.
	esl_send_recv(&this->EslHandler, "linger");
	// Tell freeswitch we are having this events with us
	esl_events(&this->EslHandler,
		ESL_EVENT_TYPE_JSON,
		"BACKGROUND_JOB CHANNEL_ANSWER CHANNEL_BRIDGE CHANNEL_UNBRIDGE CHANNEL_CALLSTATE CHANNEL_DATA CHANNEL_EXECUTE CHANNEL_EXECUTE_COMPLETE"
		"CHANNEL_HANGUP CHANNEL_HANGUP_COMPLETE DTMF");

	//The divert_events switch is available to allow events that an embedded script would expect to get in the inputcallback to be diverted to the event socket.
	//An inputcallback can be registered in an embedded script using setInputCallback(). Setting divert_events to "on" can be used for chat messages like gtalk channel, ASR events and others.
	esl_send_recv(&this->EslHandler, "divert_events on");
}
