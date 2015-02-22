unsigned char
_eeprom_read(unsigned char addr)
{
	while (WR) continue;
	return EEPROM_READ(addr);
}

void
_eeprom_write(unsigned char addr, unsigned char value)
{
	EEPROM_WRITE(addr, value);
}

