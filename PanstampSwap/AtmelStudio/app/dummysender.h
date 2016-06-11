#include "app.h"

class CAppSender : public CApp
{
  uint32_t m_nLastSecond;
  uint32_t m_nLastSend;
  uint32_t m_nInhibit;

public:
  CAppSender();

  void OnSecond();
  void OnTimer();

  virtual void Init();
  virtual void Loop();
};
