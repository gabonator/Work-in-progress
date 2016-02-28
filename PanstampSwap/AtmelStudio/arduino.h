#pragma once

#define Serial CSerial::m_Instance

class CSerial
{
public:
  static CSerial m_Instance;

public:
  enum EFormat
  {
    DEC = 0,
    HEX = 1
  };

public:
  void print(char ch);
  void print(int ch, EFormat eFormat);
  void print(char* msg);
  void print(const char* msg);
  uint8_t available();
  uint8_t read();
};

