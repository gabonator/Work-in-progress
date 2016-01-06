#ifndef _WIN32
#include "ppapi/cpp/var_dictionary.h"
extern pp::Instance* g_pMainApp;

class CApi
{
  typedef pp::Var Message;

private:
  static pp::CompletionCallbackFactory<CApi>* m_pCallbackFactory;

public:
  CApi()
  {
    m_pCallbackFactory = new pp::CompletionCallbackFactory<CApi>(this);
  }

  ~CApi() 
  {
    delete m_pCallbackFactory;
  }

  static void SendMessage(char* msg)
  {
    return;
/*
    message.Set("subject", "settingsBroadcast");

    // While we can rely on the compiler to automatically generated a call to
    // the pp::Var constructor to convert our atomic value into a pp::Var, we
    // better cast it explicitly to the desired type in order to avoid nasty
    // surprises.
    message.Set("bleed",    static_cast<double>(settings.Bleed()));
    message.Set("decayLin", static_cast<int32_t>(settings.Decay_lin()));
    message.Set("decayExp", static_cast<double>(settings.Decay_exp()));
    message.Set("radius",   static_cast<int32_t>(settings.Radius()));
    message.Set("fps",      static_cast<int32_t>(settings.Fps()));

    return message;
*/

    pp::VarDictionary message;

    message.Set("subject", "settingsBroadcast");
/*
    message.Set("bleed",    static_cast<double>(settings.Bleed()));
    message.Set("decayLin", static_cast<int32_t>(settings.Decay_lin()));
    message.Set("decayExp", static_cast<double>(settings.Decay_exp()));
    message.Set("radius",   static_cast<int32_t>(settings.Radius()));
    message.Set("fps",      static_cast<int32_t>(settings.Fps()));
*/
    message.Set("content", msg);
    _ASSERT(g_pMainApp);
    g_pMainApp->PostMessage(message);

    pp::Module::Get()->core()->CallOnMainThread(0,
        m_pCallbackFactory->NewCallback(&CApi::_DoPostMessage, message));

  }

  static void OnMessage(const Message& var_message)
  {
  }

  //
private:
  void _DoPostMessage(uint32_t result, const pp::Var& message)
  {
    if (result == PP_OK) 
      g_pMainApp->PostMessage(message);
  }


};

/*static*/ pp::CompletionCallbackFactory<CApi>* CApi::m_pCallbackFactory = NULL;

#else
class CApi
{
  typedef char* Message;

public:
  static void SendMessage(char* msg)
  {
  }

  static void OnMessage(const Message& var_message)
  {
  }

};
#endif
