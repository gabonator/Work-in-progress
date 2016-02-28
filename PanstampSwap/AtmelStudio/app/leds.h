#include "app.h"

class CAppLeds : public CApp
{
public:
  virtual void Init();
  virtual void Loop();

  static void Show(uint8_t n);
  static uint8_t GetButtons();
};
