#include "app.h"

class CModem : public CApp
{
  unsigned long nLastCall;
  char strCommand[80];
  int iCommand;

private:
  void eval(char* strCommand);

public:
  CModem();
  virtual void Init();
  virtual void Loop();
};
