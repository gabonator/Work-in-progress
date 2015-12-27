#include "ppapi/cpp/websocket.h"

class CNaclWebsocket : public CNet 
{
  pp::WebSocket* m_pWebsocket;
  pp::Var m_varReceive;
  CNet::THandler m_handler;
  PVOID m_handlerData;
  EConnectionState m_eState;

public:             
  CNaclWebsocket()
  {
    m_pWebsocket = NULL;
    m_handler = NULL;
    m_handlerData = NULL;
    m_eState = CNet::Error;
  }

  bool Create()
  {
    std::string url = "ws://192.168.1.140:1337/test";

    m_pWebsocket = new pp::WebSocket(g_pMainApp);
    _ASSERT( m_pWebsocket );
    m_pWebsocket->Connect(pp::Var(url), NULL, 0, pp::CompletionCallback(_OnConnect, this));

    m_eState = CNet::Connecting;

    return m_pWebsocket ? true : false;
  }

  ~CNaclWebsocket()
  {
    delete m_pWebsocket;
  }

	virtual void Do()
  {
  }

	virtual void Send(std::string str)
  {
    if (!IsConnected())
      return;

    m_pWebsocket->SendMessage(pp::Var(str));
  }

	virtual void SetReceiveHandler(THandler handler, PVOID data)
  {
    m_handler = handler;
    m_handlerData = data;
  }

  virtual EConnectionState GetState()
  {
    if ( m_eState != CNet::Open )
      return m_eState;
    return IsConnected() ? CNet::Open : CNet::Error;
  } 

public:
  void Receive()
  {
    // start receiving
    // |receive_var_| must be valid until |callback| is invoked.
    // Just use a member variable.
    m_pWebsocket->ReceiveMessage(&m_varReceive, pp::CompletionCallback(_OnReceive, this));
  }

  bool IsConnected() 
  {
    if (!m_pWebsocket)
      return false;

    return m_pWebsocket->GetReadyState() == PP_WEBSOCKETREADYSTATE_OPEN;
  }

public:
  // handlers
  void OnConnect(int32_t result) 
  {
    if (result != PP_OK) 
    {
      m_eState = CNet::Error;
      return;
    }

    m_eState = CNet::Open;
    Receive();
  }

  void OnDisconnect(int32_t result)
  {
    m_eState = CNet::Closed;
  }

  void OnReceive(int32_t result) 
  {
    if (result != PP_OK)
    {
      m_eState = CNet::Error;
      return;
    }

    if (m_varReceive.is_array_buffer()) 
    {
      _ASSERT(0);
      return;
    }

    if (m_handler)
      m_handler(m_varReceive.AsString(), m_handlerData);

    Receive();
  }

public: 
  // public handler stubs
  static void _OnConnect(void* user_data, int32_t result) 
  {
    static_cast<CNaclWebsocket*>(user_data)->OnConnect(result);
  }

  static void _OnDisconnect(void* user_data, int32_t result) 
  {
    static_cast<CNaclWebsocket*>(user_data)->OnDisconnect(result);
  }

  static void _OnReceive(void* user_data, int32_t result) 
  {
    static_cast<CNaclWebsocket*>(user_data)->OnReceive(result);
  }
};


/*
class WebSocketInstance : public pp::Instance {
 public:
  explicit WebSocketInstance(PP_Instance instance)
      : pp::Instance(instance), websocket_(NULL) {}
  virtual ~WebSocketInstance() {}
  virtual void HandleMessage(const pp::Var& var_message);

 private:
  bool IsConnected();

  void Open(const std::string& url);
  void Close();
  void SendAsBinary(const std::string& message);
  void SendAsText(const std::string& message);
  void Receive();

  void OnConnectCompletion(int32_t result);
  void OnCloseCompletion(int32_t result);
  void OnReceiveCompletion(int32_t result);

  static void OnConnectCompletionCallback(void* user_data, int32_t result);
  static void OnCloseCompletionCallback(void* user_data, int32_t result);
  static void OnReceiveCompletionCallback(void* user_data, int32_t result);

  pp::WebSocket* websocket_;
  pp::Var receive_var_;
};

#define MAX_TO_CONVERT 8
#define BYTES_PER_CHAR 4
#define TAIL_AND_NUL_SIZE 4

static std::string ArrayToString(pp::VarArrayBuffer& array) {
  char tmp[MAX_TO_CONVERT * BYTES_PER_CHAR + TAIL_AND_NUL_SIZE];
  uint32_t offs = 0;
  uint8_t* data = static_cast<uint8_t*>(array.Map());

  for (offs = 0; offs < array.ByteLength() && offs < MAX_TO_CONVERT; offs++)
    sprintf(&tmp[offs * BYTES_PER_CHAR], "%02Xh ", data[offs]);

  sprintf(&tmp[offs * BYTES_PER_CHAR], "...");
  array.Unmap();
  return std::string(tmp);
}

void WebSocketInstance::HandleMessage(const pp::Var& var_message) {
  if (!var_message.is_string())
    return;
  std::string message = var_message.AsString();
  // This message must contain a command character followed by ';' and
  // arguments like "X;arguments".
  if (message.length() < 2 || message[1] != ';')
    return;
  switch (message[0]) {
    case 'o':
      // The command 'o' requests to open the specified URL.
      // URL is passed as an argument like "o;URL".
      Open(message.substr(2));
      break;
    case 'c':
      // The command 'c' requests to close without any argument like "c;"
      Close();
      break;
    case 'b':
      // The command 'b' requests to send a message as a binary frame. The
      // message is passed as an argument like "b;message".
      SendAsBinary(message.substr(2));
      break;
    case 't':
      // The command 't' requests to send a message as a text frame. The message
      // is passed as an argument like "t;message".
      SendAsText(message.substr(2));
      break;
  }
}

bool WebSocketInstance::IsConnected() {
  if (!websocket_)
    return false;
  if (websocket_->GetReadyState() != PP_WEBSOCKETREADYSTATE_OPEN)
    return false;
  return true;
}

void WebSocketInstance::Open(const std::string& url) {
  pp::CompletionCallback callback(OnConnectCompletionCallback, this);
  websocket_ = new pp::WebSocket(this);
  if (!websocket_)
    return;
  websocket_->Connect(pp::Var(url), NULL, 0, callback);
  PostMessage(pp::Var("connecting..."));
}

void WebSocketInstance::Close() {
  if (!IsConnected())
    return;
  pp::CompletionCallback callback(OnCloseCompletionCallback, this);
  websocket_->Close(
      PP_WEBSOCKETSTATUSCODE_NORMAL_CLOSURE, pp::Var("bye"), callback);
}

void WebSocketInstance::SendAsBinary(const std::string& message) {
  if (!IsConnected())
    return;
  uint32_t size = message.size();
  pp::VarArrayBuffer array_buffer(size);
  char* data = static_cast<char*>(array_buffer.Map());
  for (uint32_t i = 0; i < size; ++i)
    data[i] = message[i];
  array_buffer.Unmap();
  websocket_->SendMessage(array_buffer);
  std::string message_text = ArrayToString(array_buffer);
  PostMessage(pp::Var("send (binary): " + message_text));
}

void WebSocketInstance::SendAsText(const std::string& message) {
  if (!IsConnected())
    return;
  websocket_->SendMessage(pp::Var(message));
  PostMessage(pp::Var("send (text): " + message));
}

void WebSocketInstance::Receive() {
  pp::CompletionCallback callback(OnReceiveCompletionCallback, this);
  // |receive_var_| must be valid until |callback| is invoked.
  // Just use a member variable.
  websocket_->ReceiveMessage(&receive_var_, callback);
}

void WebSocketInstance::OnConnectCompletion(int32_t result) {
  if (result != PP_OK) {
    PostMessage(pp::Var("connection failed"));
    return;
  }
  PostMessage(pp::Var("connected"));
  Receive();
}

void WebSocketInstance::OnCloseCompletion(int32_t result) {
  PostMessage(pp::Var(PP_OK == result ? "closed" : "abnormally closed"));
}

void WebSocketInstance::OnReceiveCompletion(int32_t result) {
  if (result == PP_OK) {
    if (receive_var_.is_array_buffer()) {
      pp::VarArrayBuffer array_buffer(receive_var_);
      std::string message_text = ArrayToString(array_buffer);
      PostMessage("receive (binary): " + message_text);
    }
    else {
      PostMessage("receive (text): " + receive_var_.AsString());
    }
  }
  Receive();
}

void WebSocketInstance::OnConnectCompletionCallback(void* user_data,
                                                    int32_t result) {
  WebSocketInstance* instance = static_cast<WebSocketInstance*>(user_data);
  instance->OnConnectCompletion(result);
}

void WebSocketInstance::OnCloseCompletionCallback(void* user_data,
                                                  int32_t result) {
  WebSocketInstance* instance = static_cast<WebSocketInstance*>(user_data);
  instance->OnCloseCompletion(result);
}

void WebSocketInstance::OnReceiveCompletionCallback(void* user_data,
                                                    int32_t result) {
  WebSocketInstance* instance = static_cast<WebSocketInstance*>(user_data);
  instance->OnReceiveCompletion(result);
}

*/