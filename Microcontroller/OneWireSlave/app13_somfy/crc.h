#define POLYNOMIAL 0x47

unsigned char crcPush(unsigned char remainder, unsigned char data)
{
  unsigned char b;
  remainder ^= data;

  for (b = 8; b > 0; b--)
  {
      if (remainder & 0x80)
          remainder = (remainder << 1) ^ POLYNOMIAL;
      else
          remainder = (remainder << 1);
  }
  return remainder;
}