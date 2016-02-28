#include "app.h"

class CAppSender : public CApp
{
  uint32_t m_nLastSend;
  uint32_t m_nInterval;

public:
  CAppSender();

  void OnSecond();

  virtual void Init();
  virtual void Loop();
};
