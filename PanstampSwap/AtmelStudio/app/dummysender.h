#include "app.h"

class CAppSender : public CApp
{
  enum {
    Interval = 1000
  };

  uint32_t m_nLastSend;

public:
  CAppSender();

  void OnSecond();

  virtual void Init();
  virtual void Loop();
};
