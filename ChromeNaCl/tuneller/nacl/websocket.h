#include "ppapi/cpp/websocket.h"

extern std::vector<std::pair<std::string, std::string> > g_arrMainArgs;

class CNaclWebsocket : public CNet 
{
  pp::WebSocket* m_pWebsocket;
  pp::Var m_varReceive;
  CNet::THandler m_handler;
  PVOID m_handlerData;
  EConnectionState m_eState;

  std::string m_strServer;

public:             
  CNaclWebsocket()
  {
    m_pWebsocket = NULL;
    m_handler = NULL;
    m_handlerData = NULL;
    m_eState = CNet::Error;
    m_strServer = "ws://localhost:1337/test";
  }

  bool Create()
  {
//    std::string url = "ws://192.168.1.140:1337/test";
//    std::string url = "ws://91.230.44.236:1337/test";
    for ( int i = 0; i < g_arrMainArgs.size(); i++ )
      if ( g_arrMainArgs[i].first == "server" )
        m_strServer = g_arrMainArgs[i].second;

    m_pWebsocket = new pp::WebSocket(g_pMainApp);
    _ASSERT( m_pWebsocket );
    m_pWebsocket->Connect(pp::Var(m_strServer), NULL, 0, pp::CompletionCallback(_OnConnect, this));

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

  virtual std::string GetServerUrl()
  {
    return m_strServer;
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
