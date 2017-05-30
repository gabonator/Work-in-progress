var word_code_13DF = 0;
var word_code_13E1 = 0;
var word_code_13E3 = 0;
var word_code_13E5 = 0;
var byte_code_13E7 = 0;

function* start()
{
  var _pc = 0x0;
  while (_pc != -1) switch(_pc)
  {
    case 0x0:
      _push(_ds);
      r16[ax] = 0x0000;
      _push(r16[ax]);
      yield* sub_5C60();
      r16[ax] = SEG_DATA;
      _ds = r16[ax];
      yield* sub_13AA();
      memory[0x690] = 4;
      _memoryWrite16(0x6DF8, 0);
      memory[0x69B] = 0;
      yield* sub_1419();
      yield* sub_13E8();
      r16[ax] = _memoryRead16(0x693) + 0x0240;
      _memoryWrite16(0x6E00, r16[ax]);
      r16[ax] = 0x0004;
      _interrupt(0x10);
      r8[al] = 0x04;
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x3F;
        continue;
      };
      r8[al] = 0x06;
    case 0x3F:
      memory[0x690] = r8[al];
      r8[ah] = 0x0b;
      r16[bx] = 0x0101;
      _interrupt(0x10);
      _memoryWrite16(0x416, 0);
      _memoryWrite16(0x4, 0);
      yield* sub_1D31();
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x65;
        continue;
      };
      r16[dx] = 0x03d9;
      r8[al] = 0x20;
      _out(r16[dx], r8[al]);
    case 0x65:
      yield* sub_2E10();
      yield* sub_26E1();
      yield* sub_26DA();
      memory[0x41A] = 0;
      r16[ax] = 0xffff;
      _memoryWrite16(0x41D, r16[ax]);
      _memoryWrite16(0x41F, r16[ax]);
      memory[0x0] = 0xff;
    case 0x81:
      yield* sub_2690();
      _memoryWrite16(0x8, 0);
      _memoryWrite16(0x4, 0);
      yield* sub_1D31();
      yield* sub_5B21();
      yield* sub_5CB0();
      yield* sub_5B21();
      if (memory[adr(_ds, 0x41A)] != 0)
      {
        _pc = 0xAE;
        continue;
      };
    case 0xA3:
      yield* sub_5B21();
      yield* sub_5EE5();
      memory[0x41A] = 1;
    case 0xAE:
      r16[ax] = _memoryRead16(0x6DF8);
      _memoryWrite16(0x8, r16[ax]);
      memory[0x1F80] = 3;
      yield* sub_26DA();
      _memoryWrite16(0x4, 0);
      yield* sub_1D31();
      yield* sub_5B21();
      _memoryWrite16(0x1C30, 0);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x412, r16[dx]);
      _memoryWrite16(0x414, 0);
      memory[0x418] = 0;
      memory[0x419] = 0;
      memory[0x41C] = 0;
      memory[0x41B] = 0;
      yield* sub_5B21();
    case 0xF3:
      if (memory[adr(_ds, 0x1F80)] == 0)
      {
        _pc = 0x81;
        continue;
      };
      if (memory[adr(_ds, 0x41B)] != 0)
      {
        _pc = 0xAE;
        continue;
      };
      if (memory[adr(_ds, 0x41C)] != 0)
      {
        _pc = 0xA3;
        continue;
      };
      yield* sub_2A00();
      yield* sub_5400();
      memory[0x1F81] = 0xff;
      yield* sub_5B21();
      _memoryWrite16(0x4, 0);
      if (memory[adr(_ds, 0x419)] == 0)
      {
        _pc = 0x137;
        continue;
      };
      yield* sub_7A1();
      memory[0x550] = 2;
      memory[0x576] = 1;
      memory[0x578] = 0x20;
      {
        _pc = 0x140;
        continue;
      };
    case 0x137:
      _memoryWrite16(0x579, 0);
      yield* sub_70D();
    case 0x140:
      yield* sub_1E40();
      yield* sub_1830();
      yield* sub_2210();
      yield* sub_2330();
      yield* sub_26F2();
      yield* sub_26FC();
      yield* sub_58BD();
    case 0x155:
      if (memory[adr(_ds, 0x1F80)] != 0)
      {
        _pc = 0x15F;
        continue;
      };
      {
        _pc = 0x81;
        continue;
      };
    case 0x15F:
      yield* sub_1338();
      if (memory[adr(_ds, 0x41C)] == 0)
      {
        _pc = 0x16C;
        continue;
      };
      {
        _pc = 0xA3;
        continue;
      };
    case 0x16C:
      if (memory[adr(_ds, 0x41B)] == 0)
      {
        _pc = 0x176;
        continue;
      };
      {
        _pc = 0xAE;
        continue;
      };
    case 0x176:
      yield* sub_1200();
      yield* sub_8E5();
      yield* sub_1E63();
      if (memory[adr(_ds, 0x1CB8)] != 0)
      {
        _pc = 0x191;
        continue;
      };
      memory[adr(_ds, 0x40F)] += 1;
      if (memory[adr(_ds, 0x40F)] & 3)
      {
        _pc = 0x155;
        continue;
      };
    case 0x191:
      yield* sub_546D();
      yield* sub_4A0();
      yield* sub_1936();
      yield* sub_184B();
      yield* sub_2216();
      yield* sub_237B();
      yield* sub_26B3();
      if (memory[adr(_ds, 0x551)] == 0)
      {
        _pc = 0x155;
        continue;
      };
      if (memory[adr(_ds, 0x1F80)] != 0)
      {
        _pc = 0x1B7;
        continue;
      };
      {
        _pc = 0x81;
        continue;
      };
    case 0x1B7:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x410, r16[dx]);
      r16[ax] = _memoryRead16(0x579);
      _memoryWrite16(0x1, r16[ax]);
      r8[al] = memory[0x57B];
      memory[0x3] = r8[al];
      memory[0x419] = 1;
      if (memory[adr(_ds, 0x418)] == 0)
      {
        _pc = 0x1E5;
        continue;
      };
      memory[0x418] = 0;
      _memoryWrite16(0x4, 7);
      {
        _pc = 0x238;
        continue;
      };
    case 0x1E5:
      yield* sub_2DFD();
      if (!(r8[dl] & 0xa0))
      {
        _pc = 0x20A;
        continue;
      };
      r16[bx] = _memoryRead16(0x8) & 0x0003;
      if (r16[bx] == 0x0003)
      {
        _pc = 0x20A;
        continue;
      };
      r8[cl] = 0x02;
      r16[bx] <<= r8[cl];
      r16[dx] &= 0x0003;
      r16[bx] += r16[dx];
      r8[al] = memory[ofs(r16[bx] + 0x421)];
      {
        _pc = 0x21C;
        continue;
      };
    case 0x20A:
      do {
        yield* sub_2DFD();
        r16[dx] &= 0x0007;
      } while (r16[dx] >= 0x0005);
      r16[bx] = r16[dx];
      r8[al] = memory[ofs(r16[bx] + 0x42d)];
    case 0x21C:
      r8[ah] = 0;
      if (r16[ax] != _memoryRead16(adr(_ds, 0x41D)))
      {
        _pc = 0x22A;
        continue;
      };
      if (r16[ax] == _memoryRead16(adr(_ds, 0x41F)))
      {
        _pc = 0x1E5;
        continue;
      };
    case 0x22A:
      _memoryWrite16(0x4, r16[ax]);
      r16[cx] = _memoryRead16(0x41D);
      _memoryWrite16(0x41F, r16[cx]);
      _memoryWrite16(0x41D, r16[ax]);
    case 0x238:
      _memoryWrite16(0x6, 0);
      r16[bx] = _memoryRead16(0x4);
      if (r16[bx] <= 0x0007)
      {
        _pc = 0x249;
        continue;
      };
      r16[bx] = 0;
    case 0x249:
      r16[bx] <<= 1;
      switch (r16[bx])
      {
        case 0: _pc = 0x3E2; break;
        case 2: _pc = 0x3E2; break;
        case 4: _pc = 0x459; break;
        case 6: _pc = 0x394; break;
        case 8: _pc = 0x349; break;
        case 10: _pc = 0x2FE; break;
        case 12: _pc = 0x2AA; break;
        case 14: _pc = 0x260; break;
        default:
        _ASSERT(0);
      }
      continue;
    case 0x260:
      _memoryWrite16(0x4, 7);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_7A1();
      yield* sub_1E40();
      yield* sub_3405();
      yield* sub_6100();
      yield* sub_4F59();
      yield* sub_58BD();
      do {
        yield* sub_1338();
        yield* sub_1200();
        yield* sub_546D();
        yield* sub_8E5();
        yield* sub_6106();
        yield* sub_2F66();
        yield* sub_2E60();
        yield* sub_4C10();
        r8[al] = ((memory[0x551] | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
      } while (r8[al] == 0);
      {
        _pc = 0x427;
        continue;
      };
    case 0x2AA:
      _memoryWrite16(0x4, 6);
      yield* sub_1BF0();
      yield* sub_2790();
      nullsub_1();
      yield* sub_7A1();
      yield* sub_3405();
      yield* sub_1E40();
      yield* sub_58BD();
    case 0x2C5:
      yield* sub_1338();
      yield* sub_1200();
      yield* sub_546D();
      yield* sub_4943();
      yield* sub_47D6();
      yield* sub_8E5();
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x2E3;
        continue;
      };
      yield* sub_1E63();
      {
        _pc = 0x2E6;
        continue;
      };
    case 0x2E3:
      yield* sub_3150();
    case 0x2E6:
      r8[al] = (((memory[0x551] | memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41B)]) | memory[adr(_ds, 0x41C)];
      if (r8[al] == 0)
      {
        _pc = 0x2C5;
        continue;
      };
      {
        _pc = 0x427;
        continue;
      };
    case 0x2FE:
      _memoryWrite16(0x4, 5);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_457A();
      yield* sub_7A1();
      yield* sub_3405();
      yield* sub_1E40();
      yield* sub_58BD();
      do {
        yield* sub_1338();
        yield* sub_1200();
        yield* sub_546D();
        yield* sub_45AB();
        yield* sub_4340();
        yield* sub_8E5();
        yield* sub_3150();
        yield* sub_1E63();
        r8[al] = (((memory[0x552] | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
      } while (r8[al] == 0);
      {
        _pc = 0x427;
        continue;
      };
    case 0x349:
      _memoryWrite16(0x4, 4);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_7A1();
      yield* sub_3405();
      yield* sub_1E40();
      yield* sub_4090();
      yield* sub_58BD();
      do {
        yield* sub_1338();
        yield* sub_1200();
        yield* sub_546D();
        yield* sub_8E5();
        yield* sub_3E90();
        yield* sub_40C2();
        yield* sub_3150();
        yield* sub_1E63();
        r8[al] = (((memory[0x552] | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
      } while (r8[al] == 0);
      {
        _pc = 0x427;
        continue;
      };
    case 0x394:
      _memoryWrite16(0x4, 3);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_7A1();
      yield* sub_3405();
      yield* sub_1E40();
      yield* sub_3B30();
      yield* sub_3C90();
      yield* sub_58BD();
      do {
        yield* sub_1338();
        yield* sub_1200();
        yield* sub_546D();
        yield* sub_8E5();
        yield* sub_3CB1();
        yield* sub_3B42();
        yield* sub_3150();
        yield* sub_1E63();
        r8[al] = (((memory[0x552] | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
      } while (r8[al] == 0);
      {
        _pc = 0x427;
        continue;
      };
    case 0x3E2:
      _memoryWrite16(0x4, 1);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_7A1();
      yield* sub_3405();
      yield* sub_1E40();
      yield* sub_58BD();
    case 0x3FA:
      yield* sub_1338();
      yield* sub_1200();
      yield* sub_546D();
      yield* sub_8E5();
      yield* sub_3150();
      yield* sub_1E63();
      yield* sub_3850();
      if (memory[adr(_ds, 0x554)] != 0)
      {
        _pc = 0x459;
        continue;
      };
      r8[al] = ((memory[0x552] | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41B)]) | memory[adr(_ds, 0x41C)];
      if (r8[al] == 0)
      {
        _pc = 0x3FA;
        continue;
      };
    case 0x427:
      if (memory[adr(_ds, 0x41B)] == 0)
      {
        _pc = 0x431;
        continue;
      };
      {
        _pc = 0xAE;
        continue;
      };
    case 0x431:
      if (memory[adr(_ds, 0x41C)] == 0)
      {
        _pc = 0x43B;
        continue;
      };
      {
        _pc = 0xA3;
        continue;
      };
    case 0x43B:
      if (memory[adr(_ds, 0x552)] == 0)
      {
        _pc = 0x447;
        continue;
      };
      memory[0x419] = 0;
    case 0x447:
      r16[ax] = _memoryRead16(0x4);
      _memoryWrite16(0x6, r16[ax]);
      _memoryWrite16(0x4, 0);
      yield* sub_1BF0();
      {
        _pc = 0xF3;
        continue;
      };
    case 0x459:
      _memoryWrite16(0x4, 2);
      yield* sub_1BF0();
      yield* sub_2790();
      yield* sub_35C9();
      yield* sub_7A1();
      memory[0x1CBF] = 0;
      memory[0x1CB8] = 0;
      yield* sub_58BD();
      do {
        yield* sub_1338();
        yield* sub_1200();
        yield* sub_546D();
        yield* sub_8E5();
        yield* sub_3675();
        yield* sub_37E5();
        r8[al] = ((memory[0x552] | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
      } while (r8[al] == 0);
      {
        _pc = 0x427;
        continue;
      };
      return;
  }
}

function* sub_4A0()
{
  var _pc = 0x4A0;
  while (_pc != -1) switch(_pc)
  {
    case 0x4A0:
      memory[adr(_ds, 0x531)] -= 1;
      if (memory[adr(_ds, 0x531)] == 0)
      {
        _pc = 0x4A7;
        continue;
      };
      return;
    case 0x4A7:
      memory[adr(_ds, 0x531)] += 1;
      yield* sub_13D8();
      if (r8[al] != 0)
        return;
      if (memory[adr(_ds, 0x55A)] != 0)
        return;
      if (memory[adr(_ds, 0x1673)] != 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] == _memoryRead16(adr(_ds, 0x544)))
        return;
      _memoryWrite16(0x544, r16[dx]);
      r16[bx] = _memoryRead16(0x8);
      r8[al] = memory[ofs(r16[bx] + 0x532)];
      if (memory[adr(_ds, 0x57B)] > 0x60)
      {
        _pc = 0x4DF;
        continue;
      };
      r8[al] >>= 2;
    case 0x4DF:
      memory[0x531] = r8[al];
      r16[bx] = _memoryRead16(0x52F);
      yield* sub_658();
      if (flags.zero)
      {
        _pc = 0x50C;
        continue;
      };
      r8[al] = memory[0x525] + memory[adr(_ds, r16[bx] + 0x529)];
      if (r8[al] < 0x04)
        return;
      do {
        do {
          yield* sub_2DFD();
          r8[dl] &= 0x03;
        } while (r8[dl] == memory[adr(_ds, 0x52F)]);
      } while (r8[dl] == 0x03);
      r8[bl] = r8[dl];
      {
        _pc = 0x535;
        continue;
      };
    case 0x50C:
      r8[al] = memory[ofs(r16[bx] + 0x529)];
      memory[adr(_ds, 0x525)] += r8[al];
      if (memory[adr(_ds, 0x525)] < 4)
      {
        _pc = 0x583;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x40)
      {
        _pc = 0x539;
        continue;
      };
      do {
        do {
          yield* sub_2DFD();
          r8[dl] &= 0x03;
        } while (r8[dl] == 0x03);
        r8[bl] = r8[dl];
        yield* sub_658();
      } while (!flags.zero);
    case 0x535:
      _memoryWrite16(0x52F, r16[bx]);
    case 0x539:
      r8[al] = memory[ofs(r16[bx] + 0x526)];
      memory[0x525] = r8[al];
      r16[ax] = SEG_DATA;
      _es = r16[ax];
      _di = 0x04d7;
      r8[ah] = memory[ofs(r16[bx] + 0x52c)];
      r16[bx] = _memoryRead16(0x8);
      r8[bl] = memory[ofs(r16[bx] + 0x2aba)];
      r8[bh] = r8[ah];
      yield* sub_67D();
      if (_memoryRead16(adr(_ds, 0x52F)) == 1)
      {
        _pc = 0x56E;
        continue;
      };
      memory[adr(_ds, 0x540)] >>= 1;
      yield* sub_633();
      memory[adr(_ds, 0x540)] >>= 1;
      {
        _pc = 0x57C;
        continue;
      };
    case 0x56E:
      r8[al] = memory[0x540] >> 2;
      yield* sub_633();
      memory[adr(_ds, 0x540)] >>= 1;
    case 0x57C:
      yield* sub_633();
      r16[bx] = _memoryRead16(0x52F);
    case 0x583:
      if (memory[adr(_ds, 0x4D6)] == 0)
      {
        _pc = 0x5D0;
        continue;
      };
      r16[ax] = _memoryRead16(0x579);
      if (r8[bl] == 0x01)
      {
        _pc = 0x5BF;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x55F), _memoryRead16(adr(_ds, 0x55F)) + 1);
      r16[ax] += 0x0004;
      if (r16[ax] < 0x0123)
      {
        _pc = 0x5CD;
        continue;
      };
    case 0x59E:
      memory[0x55B] = 0x11;
      memory[0x571] = 1;
      memory[0x576] = 1;
      memory[0x578] = 0x18;
      memory[0x572] = 1;
      memory[0x55C] = 0;
      {
        _pc = 0x5D0;
        continue;
      };
    case 0x5BF:
      _memoryWrite16(adr(_ds, 0x55F), _memoryRead16(adr(_ds, 0x55F)) - 1);
      flags.carry = r16[ax] < 0x0004;
      r16[ax] -= 0x0004;
      if (flags.carry)
      {
        _pc = 0x59E;
        continue;
      };
      if (r16[ax] < 0x0008)
      {
        _pc = 0x59E;
        continue;
      };
    case 0x5CD:
      _memoryWrite16(0x579, r16[ax]);
    case 0x5D0:
      _push(_ds);
      r16[bx] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x51d));
      _memoryWrite16(0x523, r16[ax]);
      _si = _memoryRead16(ofs(r16[bx] + 0x517));
      r16[ax] = 0xb800;
      _ds = r16[ax];
      _es = r16[ax];
      _di = _si;
      if (r16[bx] != 0x0002)
      {
        _pc = 0x5F1;
        continue;
      };
      flags.direction = false;
      _di -= 1;
      {
        _pc = 0x5F3;
        continue;
      };
    case 0x5F1:
      flags.direction = true;
      _di += 1;
    case 0x5F3:
      r16[cx] = 0x027f;
      _push(_di);
      _push(_si);
      _rep_movsb_MemB800_MemB800_DirAuto();
      _si = _pop();
      _di = _pop();
      _si += 0x2000;
      _di += 0x2000;
      r16[cx] = 0x0280;
      _rep_movsb_MemB800_MemB800_DirAuto(); // TODO: auto
      _ds = _pop();
      _di = _memoryRead16(adr(_ds, 0x523));
      r8[bl] = memory[adr(_ds, 0x525)];
      r8[bh] = 0;
      r16[bx] += 0x04d7;
      r16[cx] = 0x10;
    case 0x61B:
      r8[al] = memory[adr(_ds, r16[bx])];
      _videoWrite8(0xb800, _di, r8[al]);
      r16[bx] += 0x0004;
      _di = _di ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x630;
        continue;
      };
      _di += 0x50;
    case 0x630:
      if (--r16[cx])
      {
        _pc = 0x61B;
        continue;
      };
      return;
  }
}

function* sub_633()
{
  var _pc = 0x633;
  while (_pc != -1) switch(_pc)
  {
    case 0x633:
      _ah = flags.toByte();
      r16[bx] = _memoryRead16(0x52F);
      r8[bl] = memory[ofs(r16[bx] + 0x541)];
      r16[cx] = 0x0005;
      if (r8[bl] == 0x09)
      {
        _pc = 0x64E;
        continue;
      };
      do {
        flags.fromByte(_ah);
        memory[adr(_ds, r16[bx] + 0x1016)] = _rcr8(memory[adr(_ds, r16[bx] + 0x1016)], 1);
        _ah = flags.toByte();
        r16[bx] += 1;
      } while (--r16[cx]);
      return;
    case 0x64E:
      do {
        flags.fromByte(_ah);
        memory[adr(_ds, r16[bx] + 0x1016)] = _rcl8(memory[adr(_ds, r16[bx] + 0x1016)], 1);
        _ah = flags.toByte();
        r16[bx] -= 1;
      } while (--r16[cx]);
      return;
  }
}

function* sub_658()
{
  var _pc = 0x658;
  while (_pc != -1) switch(_pc)
  {
    case 0x658:
      memory[0x4D6] = 0;
      r8[al] = memory[0x57C];
      flags.zero = r8[al] == memory[adr(_ds, r16[bx] + 0x53d)];
      if (r8[al] < memory[adr(_ds, r16[bx] + 0x53d)])
      {
        _pc = 0x679;
        continue;
      };
      flags.zero = r8[al] == memory[adr(_ds, r16[bx] + 0x53a)];
      if (r8[al] >= memory[adr(_ds, r16[bx] + 0x53a)])
      {
        _pc = 0x679;
        continue;
      };
      flags.zero = memory[adr(_ds, 0x55C)] == 1;
      if (memory[adr(_ds, 0x55C)] >= 1)
      {
        _pc = 0x674;
        continue;
      };
      return;
    case 0x674:
      memory[0x4D6] = 1;
    case 0x679:
      flags.zero = true;
      return;
  }
}

// class CIReturn
function* sub_67D()
{
  var _pc = 0x67D;
  while (_pc != -1) switch(_pc)
  {
    case 0x67D:
      memory[0x540] = 0;
      flags.direction = false;
      r16[cx] = 0x20;
      r16[ax] = 0xaaaa;
      _rep_stosw_MemData_DirForward();
      _di -= 0x40;
      r16[ax] = 0x4444;
      _memoryWrite16(adr(_es, _di + 4), r16[ax]);
      _memoryWrite16(adr(_es, _di + 6), r16[ax]);
      yield* sub_2DFD();
      if (r8[dl] < r8[bl])
        return;
      if (r8[dh] > r8[bh])
      {
        _pc = 0x6A5;
        continue;
      };
      return;
    case 0x6A5:
      yield* sub_2DFD();
      if (r8[dl] < 0x18)
      {
        _pc = 0x6C7;
        continue;
      };
      if (r8[dl] < 0x60)
      {
        _pc = 0x6D0;
        continue;
      };
      _push(_di);
      yield* sub_6DE();
      r8[al] <<= 1;
      memory[0x540] = r8[al];
      _di = _pop();
      _di += 0x0002;
      yield* sub_6DE();
      memory[adr(_ds, 0x540)] |= r8[al];
      return;
    case 0x6C7:
      r16[cx] = 0x20;
      _si = 0x0490;
      {
        _pc = 0x6D6;
        continue;
      };
    case 0x6D0:
      r16[cx] = 0x10;
      _si = 0x0460;
    case 0x6D6:
      _rep_movsw_MemData_MemData_DirForward();
      memory[0x540] = 3;
      return;
  }
}

function* sub_6DE()
{
  var _pc = 0x6DE;
  while (_pc != -1) switch(_pc)
  {
    case 0x6DE:
      yield* sub_2DFD();
      r16[dx] &= 0x0006;
      if (r8[dl] != 0x06)
      {
        _pc = 0x6ED;
        continue;
      };
      r8[al] = 0;
      return;
    case 0x6ED:
      r16[bx] = r16[dx];
      _si = _memoryRead16(ofs(r16[bx] + 0x4d0));
      r16[cx] = 0x0008;
      do {
        _lodsw_MemData_DirForward();
        _stosw_MemData_DirForward();
        _di += 0x0002;
      } while (--r16[cx]);
      r8[al] = 0x01;
      return;
  }
}

function* sub_700()
{
  _memoryWrite16(0x57D, 0);
  _memoryWrite16(0x684, 0);
}

function* sub_70D()
{
  var _pc = 0x70D;
  while (_pc != -1) switch(_pc)
  {
    case 0x70D:
      r16[cx] = 0x0000;
      r8[ah] = 0x01;
      if (_memoryRead16(adr(_ds, 0x579)) < 0xa0)
      {
        _pc = 0x71F;
        continue;
      };
      r16[cx] = 0x0128;
      r8[ah] = 0xff;
    case 0x71F:
      memory[0x56E] = r8[ah];
      memory[0x558] = 3;
      memory[0x559] = 0x0c;
      r8[dl] = 0xb4;
      _memoryWrite16(0x579, r16[cx]);
      memory[0x57B] = r8[dl];
      memory[0x57C] = 0xe6;
      yield* sub_2CB0();
      _memoryWrite16(0x55F, r16[ax]);
      _memoryWrite16(0x561, 2819);
      yield* sub_1124();
      memory[0x571] = 0;
      _memoryWrite16(0x572, 2);
      memory[0x576] = 1;
      memory[0x55B] = 0;
      memory[0x550] = 0;
      memory[0x55C] = 0;
      memory[0x55A] = 0;
      memory[0x583] = 0;
      memory[0x698] = 0;
      memory[0x699] = 0;
      memory[0x551] = 0;
      memory[0x584] = 0;
      memory[0x552] = 0;
      _memoryWrite16(0x554, 0);
      memory[0x553] = 0;
      memory[0x127C] = 0;
      yield* sub_700();
      return;
  }
}

function* sub_7A1()
{
  var _pc = 0x7A1;
  while (_pc != -1) switch(_pc)
  {
    case 0x7A1:
      r16[bx] = _memoryRead16(0x4);
      if (r16[bx] != 0x0000)
      {
        _pc = 0x7B5;
        continue;
      };
      r16[cx] = _memoryRead16(0x1);
      r8[dl] = memory[0x3];
      {
        _pc = 0x7BF;
        continue;
      };
    case 0x7B5:
      r8[dl] = memory[ofs(r16[bx] + 0x5e9)];
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x5d9));
    case 0x7BF:
      _memoryWrite16(0x579, r16[cx]);
      memory[0x57B] = r8[dl];
      r8[al] = r8[dl] + 0x32;
      memory[0x57C] = r8[al];
      yield* sub_2CB0();
      _memoryWrite16(0x55F, r16[ax]);
      r16[ax] = _memoryRead16(0xFB2);
      _memoryWrite16(0x569, r16[ax]);
      r16[ax] = _memoryRead16(0xFBE);
      _memoryWrite16(0x567, r16[ax]);
      _memoryWrite16(0x561, r16[ax]);
      yield* sub_1124();
      memory[0x571] = 1;
      memory[0x56E] = 0;
      memory[0x576] = 1;
      memory[0x578] = 0x40;
      r8[al] = 0x0a;
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0x805;
        continue;
      };
      r8[al] = 0;
    case 0x805:
      memory[0x55B] = r8[al];
      memory[0x550] = 0;
      memory[0x55C] = 0;
      memory[0x55A] = 0;
      memory[0x583] = 0;
      memory[0x698] = 0;
      memory[0x699] = 0;
      memory[0x551] = 0;
      memory[0x584] = 0;
      memory[0x552] = 0;
      _memoryWrite16(0x554, 0);
      memory[0x553] = 0;
      memory[0x127C] = 0;
      yield* sub_700();
      if (_memoryRead16(adr(_ds, 0x4)) != 2)
        return;
      memory[0x576] = 0x10;
      _memoryWrite16(0x574, 0x10);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x5F1, r16[dx]);
      memory[0x5F3] = 0;
      memory[0x5F4] = 5;
      memory[0x5F5] = 1;
      return;
  }
}

function* sub_872()
{
  var _pc = 0x872;
  while (_pc != -1) switch(_pc)
  {
    case 0x872:
      _memoryWrite16(0x592A, 1024);
      if (memory[adr(_ds, 0x584)] == 0)
      {
        _pc = 0x880;
        continue;
      };
      return;
    case 0x880:
      memory[0x576] = 8;
      r8[dl] = 0xff;
      r8[al] = memory[0x57B];
      if (r8[al] >= memory[adr(_ds, 0x2652)])
      {
        _pc = 0x892;
        continue;
      };
      r8[dl] = 0x01;
    case 0x892:
      memory[0x571] = r8[dl];
      r16[ax] = _memoryRead16(0x579);
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x2650));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x2650));
      r8[dl] = 0xff;
      if (!flags.carry && (r16[ax] != 0))
      {
        _pc = 0x8A5;
        continue;
      };
      r8[dl] = 0x01;
      r16[ax] = (~r16[ax]);
    case 0x8A5:
      memory[0x56E] = r8[dl];
      if (r8[ah] == 0x00)
      {
        _pc = 0x8B1;
        continue;
      };
      r16[ax] = 0xff;
    case 0x8B1:
      r8[al] = (~r8[al]);
      if (r8[al] >= 0x30)
      {
        _pc = 0x8B9;
        continue;
      };
      r8[al] = 0x30;
    case 0x8B9:
      r8[bl] = r8[al] >> 2;
      r8[al] -= r8[bl];
      memory[0x578] = r8[al];
      r8[cl] = 0x05;
      r8[al] >>= r8[cl];
      _memoryWrite16(0x572, r16[ax]);
      memory[0x55C] = 0;
      memory[0x39E0] = 0;
      memory[0x577] = 1;
      memory[0x55B] = 0x10;
      memory[0x584] = 1;
      return;
  }
}

function* sub_8E5()
{
  var _pc = 0x8E5;
  while (_pc != -1) switch(_pc)
  {
    case 0x8E5:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x57D)))
      {
        _pc = 0x8FD;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x684)) == 0)
        return;
      _memoryWrite16(adr(_ds, 0x684), _memoryRead16(adr(_ds, 0x684)) - 1);
      if (_memoryRead16(adr(_ds, 0x684)) == 0)
      {
        _pc = 0x90C;
        continue;
      };
      return;
    case 0x8FD:
      r16[ax] = 0x20;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x909;
        continue;
      };
      r16[ax] >>= 1;
    case 0x909:
      _memoryWrite16(0x684, r16[ax]);
    case 0x90C:
      if (_memoryRead16(adr(_ds, 0x4)) == 2)
      {
        _pc = 0x91D;
        continue;
      };
      r8[cl] = memory[0x571] | memory[adr(_ds, 0x56E)];
      if (r8[cl] != 0)
      {
        _pc = 0x926;
        continue;
      };
    case 0x91D:
      _push(r16[dx]);
      _push(r16[ax]);
      yield* sub_13D8();
      r16[ax] = _pop();
      r16[dx] = _pop();
      if (r8[al] == 0)
        return;
    case 0x926:
      _memoryWrite16(0x57D, r16[dx]);
      _memoryWrite16(0x57F, r16[ax]);
      if (_memoryRead16(adr(_ds, 0x4)) != 4)
      {
        _pc = 0x93B;
        continue;
      };
      if (memory[adr(_ds, 0x39E1)] != 0)
        return;
    case 0x93B:
      if (_memoryRead16(adr(_ds, 0x4)) != 6)
      {
        _pc = 0x949;
        continue;
      };
      if (memory[adr(_ds, 0x44BD)] != 0)
        return;
    case 0x949:
      if (_memoryRead16(adr(_ds, 0x4)) == 2)
      {
        _pc = 0x953;
        continue;
      };
      {
        _pc = 0xBAC;
        continue;
      };
    case 0x953:
      _si = _memoryRead16(0x8) << 1;
      r16[ax] = _memoryRead16(0x57D) - _memoryRead16(adr(_ds, 0x5F1));
      if (r16[ax] < _memoryRead16(adr(_ds, _si + 0x589)))
      {
        _pc = 0x9D6;
        continue;
      };
      if (r16[ax] < _memoryRead16(adr(_ds, _si + 0x599)))
      {
        _pc = 0x971;
        continue;
      };
      memory[0x552] = 1;
    case 0x971:
      memory[adr(_ds, 0x5F5)] -= 1;
      if (memory[adr(_ds, 0x5F5)] != 0)
      {
        _pc = 0x9B9;
        continue;
      };
      yield* sub_597F();
      memory[0x5F5] = 6;
      r8[al] = memory[0x5F4];
      if (memory[adr(_ds, 0x57B)] < 0xb3)
      {
        _pc = 0x992;
        continue;
      };
      if (r8[al] >= 0xc8)
      {
        _pc = 0x992;
        continue;
      };
      r8[al] += 0x1e;
      memory[0x5F4] = r8[al];
    case 0x992:
      r8[dl] = memory[0x57B];
      flags.carry = r8[dl] < r8[al];
      r8[dl] -= r8[al];
      if (!flags.carry)
      {
        _pc = 0x99C;
        continue;
      };
      r8[dl] = 0;
    case 0x99C:
      r16[cx] = _memoryRead16(0x579);
      r8[dl] &= 0xf8;
      yield* sub_2CB0();
      _di = r16[ax];
      _si = 0x064e;
      r16[ax] = 0xb800;
      _es = r16[ax];
      _bp = 0x0e;
      r16[cx] = 0x0503;
      yield* sub_2D35();
    case 0x9B9:
      memory[0x56E] = 0;
      memory[0x571] = 1;
      memory[0x5F3] = 1;
      memory[0x576] = 0x20;
      r16[bx] = 0;
      r8[ah] = 0x0b;
      _interrupt(0x10);
      {
        _pc = 0xA86;
        continue;
      };
    case 0x9D6:
      _si = _memoryRead16(0x8) << 1;
      r16[bx] = 0;
      if (r16[ax] < _memoryRead16(adr(_ds, _si + 0x5a9)))
      {
        _pc = 0x9F6;
        continue;
      };
      r8[bl] += 1;
      if (r16[ax] < _memoryRead16(adr(_ds, _si + 0x5b9)))
      {
        _pc = 0x9F6;
        continue;
      };
      r8[bl] = 0x05;
      if (r16[ax] < _memoryRead16(adr(_ds, _si + 0x5c9)))
      {
        _pc = 0x9F6;
        continue;
      };
      r8[bl] -= 1;
    case 0x9F6:
      r8[ah] = 0x0b;
      _interrupt(0x10);
      r8[al] = memory[0x56E];
      memory[0x56F] = r8[al];
      r8[al] = memory[0x571];
      memory[0x570] = r8[al];
      r8[al] = memory[0x698];
      if (r8[al] != 0x00)
      {
        _pc = 0xA1A;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x574)) < 0x10)
      {
        _pc = 0xA2E;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x574), _memoryRead16(adr(_ds, 0x574)) - 1);
      {
        _pc = 0xA37;
        continue;
      };
    case 0xA1A:
      if (r8[al] != memory[adr(_ds, 0x56E)])
      {
        _pc = 0xA2E;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x574)) >= 0x30)
      {
        _pc = 0xA37;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x574), _memoryRead16(adr(_ds, 0x574)) + 3);
      {
        _pc = 0xA37;
        continue;
      };
    case 0xA2E:
      memory[0x56E] = r8[al];
      _memoryWrite16(0x574, 0x20);
    case 0xA37:
      r16[ax] = _memoryRead16(0x574);
      r8[cl] = 0x03;
      r16[ax] >>= r8[cl];
      r16[bx] = _memoryRead16(0x8);
      r8[bl] <<= 1;
      if (r16[ax] <= _memoryRead16(adr(_ds, r16[bx] + 0x66c)))
      {
        _pc = 0xA4E;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x66c));
    case 0xA4E:
      _memoryWrite16(0x572, r16[ax]);
      yield* sub_FC9();
      r8[al] = memory[0x699];
      if (r8[al] != 0x00)
      {
        _pc = 0xA6A;
        continue;
      };
      r8[al] = (~r8[al]);
      if (memory[adr(_ds, 0x576)] < 0x10)
      {
        _pc = 0xA7E;
        continue;
      };
      memory[adr(_ds, 0x576)] -= 1;
      {
        _pc = 0xA86;
        continue;
      };
    case 0xA6A:
      if (r8[al] != memory[adr(_ds, 0x571)])
      {
        _pc = 0xA7E;
        continue;
      };
      if (memory[adr(_ds, 0x576)] >= 0x40)
      {
        _pc = 0xA86;
        continue;
      };
      memory[adr(_ds, 0x576)] += 4;
      {
        _pc = 0xA86;
        continue;
      };
    case 0xA7E:
      memory[0x571] = r8[al];
      memory[0x576] = 0x20;
    case 0xA86:
      _si = _memoryRead16(0x8);
      r8[dl] = memory[0x57B];
      r8[cl] = 0x04;
      r8[bl] = memory[0x576] >> r8[cl];
      if (r8[bl] <= memory[adr(_ds, _si + 0x67c)])
      {
        _pc = 0xAA0;
        continue;
      };
      r8[bl] = memory[ofs(_si + 0x67c)];
    case 0xAA0:
      r8[al] = memory[0x571];
      if (r8[al] < 0x01)
      {
        _pc = 0xACE;
        continue;
      };
      if (r8[al] != 0x01)
      {
        _pc = 0xAB4;
        continue;
      };
      r8[dl] += r8[bl];
      if (r8[dl] < 0xb4)
      {
        _pc = 0xACE;
        continue;
      };
      r8[dl] = 0xb3;
      {
        _pc = 0xACE;
        continue;
      };
    case 0xAB4:
      flags.carry = r8[dl] < r8[bl];
      r8[dl] -= r8[bl];
      if (flags.carry)
      {
        _pc = 0xABD;
        continue;
      };
      if (r8[dl] > 0x03)
      {
        _pc = 0xACE;
        continue;
      };
    case 0xABD:
      r16[ax] = _memoryRead16(0x9B8);
      if (r16[ax] != _memoryRead16(adr(_ds, 0x55D)))
      {
        _pc = 0xACC;
        continue;
      };
      r16[ax] = _memoryRead16(0x57D);
      _memoryWrite16(0x5F1, r16[ax]);
    case 0xACC:
      r8[dl] = 0x02;
    case 0xACE:
      memory[0x57B] = r8[dl];
      r16[cx] = _memoryRead16(0x579);
      yield* sub_2CB0();
      _memoryWrite16(0x563, r16[ax]);
      if (memory[adr(_ds, 0x5F3)] == 0)
      {
        _pc = 0xAE9;
        continue;
      };
      r16[bx] = 0x10;
      {
        _pc = 0xB64;
        continue;
      };
    case 0xAE9:
      r8[al] = memory[0x56E];
      if (r8[al] != memory[adr(_ds, 0x56F)])
      {
        _pc = 0xAFB;
        continue;
      };
      r8[al] = memory[0x571];
      if (r8[al] == memory[adr(_ds, 0x570)])
      {
        _pc = 0xB00;
        continue;
      };
    case 0xAFB:
      r16[bx] = 0x18;
      {
        _pc = 0xB64;
        continue;
      };
    case 0xB00:
      _memoryWrite16(adr(_ds, 0x587), _memoryRead16(adr(_ds, 0x587)) + 1);
      r16[bx] = _memoryRead16(0x587);
      r8[al] = memory[0x698] | memory[adr(_ds, 0x699)];
      if (r8[al] != 0)
      {
        _pc = 0xB13;
        continue;
      };
      r8[bl] >>= 1;
    case 0xB13:
      if (memory[adr(_ds, 0x57B)] < 0xb3)
      {
        _pc = 0xB21;
        continue;
      };
      if (memory[adr(_ds, 0x571)] == 1)
      {
        _pc = 0xB3C;
        continue;
      };
    case 0xB21:
      if (memory[adr(_ds, 0x57B)] > 4)
      {
        _pc = 0xB2F;
        continue;
      };
      if (memory[adr(_ds, 0x699)] != 0)
      {
        _pc = 0xB53;
        continue;
      };
    case 0xB2F:
      r8[al] = memory[0x576];
      r8[ah] = 0;
      r16[ax] >>= 1;
      if (r16[ax] >= _memoryRead16(adr(_ds, 0x574)))
      {
        _pc = 0xB53;
        continue;
      };
    case 0xB3C:
      if (memory[adr(_ds, 0x56E)] == 0)
      {
        _pc = 0xB53;
        continue;
      };
      r16[bx] &= 0x0006;
      if (memory[adr(_ds, 0x56E)] == 1)
      {
        _pc = 0xB64;
        continue;
      };
      r8[bl] |= 0x08;
      {
        _pc = 0xB64;
        continue;
      };
    case 0xB53:
      r16[bx] &= 0x0002;
      r8[bl] |= 0x10;
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0xB64;
        continue;
      };
      r8[bl] += 0x04;
    case 0xB64:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x9a6));
      _memoryWrite16(0x55D, r16[ax]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x9c0));
      _memoryWrite16(0x565, r16[ax]);
      r8[al] = 0x30;
      r16[cx] = 0x02bc;
      if (memory[adr(_ds, 0x697)] < 0xfd)
      {
        _pc = 0xB97;
        continue;
      };
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0xB85;
        continue;
      };
      r8[al] = 0x08;
      r16[cx] = 0x03e8;
    case 0xB85:
      if (memory[adr(_ds, 0x57B)] > r8[al])
      {
        _pc = 0xB97;
        continue;
      };
      do {
        yield* sub_13D8();
      } while (r8[al] != 0);
      do {
        yield* sub_13D8();
      } while (r8[al] == 0);
      _Sleep(r16[cx]);
    case 0xB97:
      yield* sub_11E3();
      r16[ax] = _memoryRead16(0x563);
      _memoryWrite16(0x55F, r16[ax]);
      yield* sub_1145();
      yield* sub_34A0();
      if (!flags.carry)
        return;
      yield* sub_1145();
      return;
    case 0xBAC:
      yield* sub_1B7A();
      if (!flags.carry)
      {
        _pc = 0xBB2;
        continue;
      };
      return;
    case 0xBB2:
      if (memory[adr(_ds, 0x1CB8)] != 0)
        return;
      if (memory[adr(_ds, 0x558)] == 0)
      {
        _pc = 0xC1C;
        continue;
      };
      if (memory[adr(_ds, 0x559)] == 0)
      {
        _pc = 0xBD3;
        continue;
      };
      if (memory[adr(_ds, 0x1CBF)] != 0)
        return;
      memory[adr(_ds, 0x559)] -= 1;
      return;
    case 0xBD3:
      memory[adr(_ds, 0x558)] -= 1;
      if (memory[adr(_ds, 0x558)] != 0)
      {
        _pc = 0xBE5;
        continue;
      };
      _memoryWrite16(0x572, 8);
      yield* sub_FC9();
      {
        _pc = 0xC1C;
        continue;
      };
    case 0xBE5:
      yield* sub_1020();
      _memoryWrite16(0x55D, r16[bx]);
      r8[al] = memory[0x558];
      r8[ah] = memory[0x56E];
      yield* sub_F87();
      if (memory[adr(_ds, 0x558)] == 2)
      {
        _pc = 0xC00;
        continue;
      };
      yield* sub_11E3();
    case 0xC00:
      yield* sub_1B7A();
      if (flags.carry)
        return;
      yield* sub_20F5();
      if (flags.carry)
        return;
      r8[dl] = memory[0x57B];
      r16[cx] = _memoryRead16(0x579);
      yield* sub_2CB0();
      _memoryWrite16(0x55F, r16[ax]);
      yield* sub_1145();
      return;
    case 0xC1C:
      if (memory[adr(_ds, 0x55C)] < 1)
      {
        _pc = 0xC6A;
        continue;
      };
      if (memory[adr(_ds, 0x55C)] != 1)
      {
        _pc = 0xC5F;
        continue;
      };
      memory[adr(_ds, 0x55C)] += 1;
      _memoryWrite16(0x572, 6);
      r8[dl] = memory[0x57B];
      r16[cx] = _memoryRead16(0x579);
      yield* sub_2CB0();
      _memoryWrite16(0x563, r16[ax]);
      yield* sub_11E3();
      yield* sub_1B7A();
      if (flags.carry)
        return;
      yield* sub_20F5();
      if (flags.carry)
        return;
      r16[ax] = _memoryRead16(0x563);
      _memoryWrite16(0x55F, r16[ax]);
      _memoryWrite16(0x565, 3587);
      _memoryWrite16(0x55D, 2522);
      yield* sub_1145();
    case 0xC5F:
      if (memory[adr(_ds, 0x699)] != 0)
      {
        _pc = 0xE78;
        continue;
      };
      return;
      {
        _pc = 0xE78;
        continue;
      };
    case 0xC6A:
      if (memory[adr(_ds, 0x571)] != 0)
      {
        _pc = 0xC74;
        continue;
      };
      {
        _pc = 0xE23;
        continue;
      };
    case 0xC74:
      yield* sub_FC9();
      if (!flags.carry)
      {
        _pc = 0xC90;
        continue;
      };
      memory[0x56E] = 0;
      memory[0x576] = 2;
      memory[0x571] = 1;
      memory[0x55B] = 0;
      {
        _pc = 0xCC1;
        continue;
      };
    case 0xC90:
      r8[al] = memory[0x578];
      flags.carry = memory[adr(_ds, 0x577)] < r8[al];
      memory[adr(_ds, 0x577)] -= r8[al];
      if (!flags.carry)
      {
        _pc = 0xCC1;
        continue;
      };
      if (memory[adr(_ds, 0x571)] == 1)
      {
        _pc = 0xCB6;
        continue;
      };
      if (memory[adr(_ds, 0x576)] <= 1)
      {
        _pc = 0xCAE;
        continue;
      };
      memory[adr(_ds, 0x576)] -= 1;
      {
        _pc = 0xCC1;
        continue;
      };
    case 0xCAE:
      memory[0x571] = 1;
      {
        _pc = 0xCC1;
        continue;
      };
    case 0xCB6:
      if (memory[adr(_ds, 0x576)] >= 4)
      {
        _pc = 0xCC1;
        continue;
      };
      memory[adr(_ds, 0x576)] += 1;
    case 0xCC1:
      if (memory[adr(_ds, 0x55A)] != 0)
      {
        _pc = 0xCE7;
        continue;
      };
      if (memory[adr(_ds, 0x55B)] == 0)
      {
        _pc = 0xCD5;
        continue;
      };
      memory[adr(_ds, 0x55B)] -= 1;
      if (memory[adr(_ds, 0x55B)] != 0)
      {
        _pc = 0xCE7;
        continue;
      };
    case 0xCD5:
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0xCE7;
        continue;
      };
      yield* sub_1608();
      if (!flags.carry)
      {
        _pc = 0xCE7;
        continue;
      };
      r8[al] = memory[0x57C];
      {
        _pc = 0xD29;
        continue;
      };
    case 0xCE7:
      r8[al] = memory[0x57C];
      if (memory[adr(_ds, 0x571)] == 1)
      {
        _pc = 0xD06;
        continue;
      };
      flags.carry = r8[al] < memory[adr(_ds, 0x576)];
      r8[al] = r8[al] - memory[adr(_ds, 0x576)];
      if (!flags.carry)
      {
        _pc = 0xD4F;
        continue;
      };
      r8[al] = 0;
      memory[0x571] = 1;
      memory[0x576] = 1;
      {
        _pc = 0xD4F;
        continue;
      };
    case 0xD06:
      r8[al] = r8[al] + memory[adr(_ds, 0x576)];
      if (r8[al] <= 0xe6)
      {
        _pc = 0xD4F;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0xD22;
        continue;
      };
      if (r8[al] < 0xf8)
      {
        _pc = 0xD4F;
        continue;
      };
      r8[al] = 0xf8;
      memory[0x551] = 1;
      {
        _pc = 0xD4F;
        continue;
      };
    case 0xD22:
      r8[al] = 0xe6;
      memory[0x550] = 0;
    case 0xD29:
      memory[0x571] = 0;
      memory[0x584] = 0;
      _memoryWrite16(0x572, 2);
      memory[0x55B] = 0;
      memory[0x55A] = 0;
      if (memory[adr(_ds, 0x55C)] == 0)
      {
        _pc = 0xD4F;
        continue;
      };
      _push(r16[ax]);
      yield* sub_5AC2();
      r16[ax] = _pop();
    case 0xD4F:
      memory[0x57C] = r8[al];
      flags.carry = r8[al] < 0x32;
      r8[al] -= 0x32;
      if (!flags.carry)
      {
        _pc = 0xD58;
        continue;
      };
      r8[al] = 0;
    case 0xD58:
      memory[0x57B] = r8[al];
      r8[dl] = memory[0x57B];
      r16[cx] = _memoryRead16(0x579);
      yield* sub_2CB0();
      _memoryWrite16(0x563, r16[ax]);
      if (memory[adr(_ds, 0x583)] != 0)
      {
        _pc = 0xD73;
        continue;
      };
      yield* sub_11E3();
    case 0xD73:
      yield* sub_1B7A();
      if (flags.carry)
      {
        _pc = 0xDC4;
        continue;
      };
      yield* sub_20F5();
      if (flags.carry)
      {
        _pc = 0xDC4;
        continue;
      };
      r16[ax] = _memoryRead16(0x563);
      _memoryWrite16(0x55F, r16[ax]);
      if (memory[adr(_ds, 0x584)] == 0)
      {
        _pc = 0xDA1;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x585), _memoryRead16(adr(_ds, 0x585)) + 2);
      r16[bx] = _memoryRead16(0x585) & 0x0e;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0xfc2));
      r16[bx] = _memoryRead16(ofs(r16[bx] + 0xfd2));
      {
        _pc = 0xDA8;
        continue;
      };
    case 0xDA1:
      r16[ax] = _memoryRead16(0x569);
      r16[bx] = _memoryRead16(0x567);
    case 0xDA8:
      _memoryWrite16(0x55D, r16[ax]);
      _memoryWrite16(0x565, r16[bx]);
      r8[al] = 0x32;
      flags.carry = r8[al] < memory[adr(_ds, 0x57C)];
      r8[al] = r8[al] - memory[adr(_ds, 0x57C)];
      if (r8[al] == 0)
      {
        _pc = 0xDDE;
        continue;
      };
      if (flags.carry)
      {
        _pc = 0xDDE;
        continue;
      };
      r16[cx] = 0x0168;
      _Sleep(r16[cx]);
      flags.carry = r8[bh] < r8[al];
      r8[bh] -= r8[al];
      if (r8[bh] == 0)
      {
        _pc = 0xDC4;
        continue;
      };
      if (!flags.carry)
      {
        _pc = 0xDCA;
        continue;
      };
    case 0xDC4:
      memory[0x583] = 1;
      return;
    case 0xDCA:
      _memoryWrite16(0x565, r16[bx]);
      r8[ah] = r8[bl] << 1;
      r16[ax] = (r8[ah] * r8[al]) + _memoryRead16(adr(_ds, 0x569));
      _memoryWrite16(0x55D, r16[ax]);
      {
        _pc = 0xE1F;
        continue;
      };
    case 0xDDE:
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0xDEE;
        continue;
      };
      r8[al] = memory[0x57B];
      flags.carry = r8[al] < 0xbb;
      r8[al] -= 0xbb;
      if (flags.carry)
      {
        _pc = 0xE1F;
        continue;
      };
      if (!flags.carry)
      {
        _pc = 0xDFC;
        continue;
      };
    case 0xDEE:
      if (memory[adr(_ds, 0x550)] != 2)
      {
        _pc = 0xE1F;
        continue;
      };
      r8[al] = memory[0x57B];
      flags.carry = r8[al] < 0x5e;
      r8[al] -= 0x5e;
      if (flags.carry)
      {
        _pc = 0xE1F;
        continue;
      };
    case 0xDFC:
      flags.carry = r8[bh] < r8[al];
      r8[bh] -= r8[al];
      if (r8[bh] == 0)
      {
        _pc = 0xE02;
        continue;
      };
      if (!flags.carry)
      {
        _pc = 0xE16;
        continue;
      };
    case 0xE02:
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0xE0F;
        continue;
      };
      memory[0x551] = 1;
      return;
    case 0xE0F:
      yield* sub_70D();
      yield* sub_59CB();
      return;
    case 0xE16:
      _memoryWrite16(0x565, r16[bx]);
      memory[0x576] = 2;
    case 0xE1F:
      yield* sub_1145();
      return;
    case 0xE23:
      if (_memoryRead16(adr(_ds, 0x4)) == 7)
      {
        _pc = 0xE31;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] >= 0xb4)
      {
        _pc = 0xE78;
        continue;
      };
    case 0xE31:
      yield* sub_1608();
      if (flags.carry)
      {
        _pc = 0xE43;
        continue;
      };
      memory[0x56E] = 0;
      memory[0x571] = 1;
      {
        _pc = 0xEB1;
        continue;
      };
    case 0xE43:
      if (_memoryRead16(adr(_ds, 0x4)) != 0)
      {
        _pc = 0xE78;
        continue;
      };
      yield* sub_22F7();
      if (flags.carry)
      {
        _pc = 0xE56;
        continue;
      };
      memory[0x56C] = 0;
      {
        _pc = 0xE78;
        continue;
      };
    case 0xE56:
      if (memory[adr(_ds, 0x56C)] != 0)
      {
        _pc = 0xE60;
        continue;
      };
      yield* sub_591F();
    case 0xE60:
      memory[0x699] = 1;
      memory[0x56C] = 1;
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0xE74;
        continue;
      };
      r8[dl] = 0xff;
    case 0xE74:
      memory[0x698] = r8[dl];
    case 0xE78:
      r8[al] = memory[0x56E];
      memory[0x56F] = r8[al];
      r8[al] = memory[0x698];
      memory[0x56E] = r8[al];
      r8[al] = memory[0x699];
      memory[0x571] = r8[al];
      if (r8[al] != 0x00)
      {
        _pc = 0xE91;
        continue;
      };
      {
        _pc = 0xF34;
        continue;
      };
    case 0xE91:
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0xEC9;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] < 0xb4)
      {
        _pc = 0xEB1;
        continue;
      };
      memory[0x571] = 0;
      memory[0x584] = 0;
      memory[0x699] = 0;
      {
        _pc = 0xF34;
        continue;
      };
    case 0xEB1:
      r8[ah] = 0x01;
      r8[al] = 0x20;
      memory[0x55B] = 8;
      if (memory[adr(_ds, 0x550)] != 1)
      {
        _pc = 0xEF1;
        continue;
      };
      memory[0x550] = 0;
      {
        _pc = 0xEF1;
        continue;
      };
    case 0xEC9:
      memory[0x55B] = 0;
      r16[ax] = _memoryRead16(0x572);
      r8[bl] = r8[al];
      if (r8[al] <= 0x02)
      {
        _pc = 0xED9;
        continue;
      };
      r8[al] -= 0x02;
    case 0xED9:
      _memoryWrite16(0x572, r16[ax]);
      r8[ah] = 0x08;
      r8[al] = r8[bl] ^ 0x0f;
      r8[cl] = 0x04;
      r8[al] <<= r8[cl];
      if (memory[adr(_ds, 0x550)] != 1)
      {
        _pc = 0xEF1;
        continue;
      };
      memory[adr(_ds, 0x550)] += 1;
    case 0xEF1:
      memory[0x578] = r8[al];
      memory[0x576] = r8[ah];
      memory[0x577] = 1;
      memory[0x55C] = 0;
      r8[bl] = (memory[0x56E] + 1) << 1;
      if (memory[adr(_ds, 0x571)] == 0xff)
      {
        _pc = 0xF14;
        continue;
      };
      r8[bl] += 0x06;
    case 0xF14:
      r8[bh] = 0;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0xfaa));
      _memoryWrite16(0x569, r16[ax]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0xfb6));
      _memoryWrite16(0x567, r16[ax]);
      memory[0x39E0] = 0;
      if (memory[adr(_ds, 0x127C)] == 0)
        return;
      yield* sub_58F8();
      return;
    case 0xF34:
      if (_memoryRead16(adr(_ds, 0x4)) == 0)
      {
        _pc = 0xF45;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x4)) == 7)
      {
        _pc = 0xF45;
        continue;
      };
      yield* sub_3445();
    case 0xF45:
      yield* sub_FC9();
      r8[dl] = memory[0x57B];
      r16[cx] = _memoryRead16(0x579);
      yield* sub_2CB0();
      _memoryWrite16(0x563, r16[ax]);
      r8[al] = memory[0x56E] | memory[adr(_ds, 0x571)];
      if (r8[al] != 0)
      {
        _pc = 0xF63;
        continue;
      };
      yield* sub_1069();
      return;
    case 0xF63:
      yield* sub_1020();
      _memoryWrite16(0x55D, r16[bx]);
      yield* sub_11E3();
      yield* sub_1B7A();
      if (flags.carry)
        return;
      yield* sub_20F5();
      if (flags.carry)
        return;
      r16[ax] = _memoryRead16(0x563);
      _memoryWrite16(0x55F, r16[ax]);
      _memoryWrite16(0x565, 2819);
      yield* sub_1145();
      return;
  }
}

function* sub_F87()
{
  var _pc = 0xF87;
  while (_pc != -1) switch(_pc)
  {
    case 0xF87:
      r16[cx] = 0x0b03;
      r8[cl] -= r8[al];
      _memoryWrite16(0x565, r16[cx]);
      if (r8[ah] == 0xff)
      {
        _pc = 0xFA6;
        continue;
      };
      r8[ah] = 0;
      r8[al] <<= 1;
      _memoryWrite16(adr(_ds, 0x55D), _memoryRead16(adr(_ds, 0x55D)) + r16[ax]);
      _memoryWrite16(0x579, 0);
      {
        _pc = 0xFB4;
        continue;
      };
    case 0xFA6:
      r8[ah] = 0;
      r8[al] = ((r8[al] << 1) << 1) << 1;
      r16[ax] += 0x0128;
      _memoryWrite16(0x579, r16[ax]);
    case 0xFB4:
      _push(_ds);
      _es = _pop();
      _si = _memoryRead16(0x55D);
      _di = 0x0e;
      r8[al] = 0x03;
      yield* sub_2D70();
      _memoryWrite16(0x55D, 0x0e);
      return;
  }
}

function* sub_FC9()
{
  var _pc = 0xFC9;
  while (_pc != -1) switch(_pc)
  {
    case 0xFC9:
      _memoryWrite16(0x5F6, 8);
      _memoryWrite16(0x5F8, 291);
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0xFE8;
        continue;
      };
      _memoryWrite16(0x5F6, 0x24);
      _memoryWrite16(0x5F8, 271);
    case 0xFE8:
      r16[ax] = _memoryRead16(0x579);
      if (memory[adr(_ds, 0x56E)] < 1)
      {
        _pc = 0x101E;
        continue;
      };
      if (memory[adr(_ds, 0x56E)] != 1)
      {
        _pc = 0x1007;
        continue;
      };
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x572));
      if (r16[ax] < _memoryRead16(adr(_ds, 0x5F8)))
      {
        _pc = 0x101B;
        continue;
      };
      r16[ax] = _memoryRead16(0x5F8) - 1;
      _memoryWrite16(0x579, r16[ax]);
      flags.carry = true;
      return;
    case 0x1007:
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x572));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x572));
      if (flags.carry)
      {
        _pc = 0x1013;
        continue;
      };
      if (r16[ax] >= _memoryRead16(adr(_ds, 0x5F6)))
      {
        _pc = 0x101B;
        continue;
      };
    case 0x1013:
      r16[ax] = _memoryRead16(0x5F6);
      _memoryWrite16(0x579, r16[ax]);
      flags.carry = true;
      return;
    case 0x101B:
      _memoryWrite16(0x579, r16[ax]);
    case 0x101E:
      flags.carry = false;
      return;
  }
}

function* sub_1020()
{
  var _pc = 0x1020;
  while (_pc != -1) switch(_pc)
  {
    case 0x1020:
      r8[al] = memory[0x56E];
      if (r8[al] == memory[adr(_ds, 0x56F)])
      {
        _pc = 0x102F;
        continue;
      };
      _memoryWrite16(0x572, 2);
    case 0x102F:
      if (_memoryRead16(adr(_ds, 0x572)) >= 8)
      {
        _pc = 0x1045;
        continue;
      };
      memory[adr(_ds, 0x577)] -= 1;
      r8[al] = memory[0x577] & 0x03;
      if (r8[al] != 0)
      {
        _pc = 0x1045;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x572), _memoryRead16(adr(_ds, 0x572)) + 1);
    case 0x1045:
      r8[bl] = memory[0x56B] + 1;
      if (r8[bl] < 0x06)
      {
        _pc = 0x1052;
        continue;
      };
      r8[bl] = 0x00;
    case 0x1052:
      memory[0x56B] = r8[bl];
      if (memory[adr(_ds, 0x56E)] != 0xff)
      {
        _pc = 0x1060;
        continue;
      };
      r8[bl] += 0x06;
    case 0x1060:
      r8[bl] <<= 1;
      r8[bh] = 0;
      r16[bx] = _memoryRead16(ofs(r16[bx] + 0xf7a));
      return;
  }
}

function* sub_1069()
{
  var _pc = 0x1069;
  while (_pc != -1) switch(_pc)
  {
    case 0x1069:
      _memoryWrite16(0x572, 2);
      memory[0x577] = 8;
      if (_memoryRead16(adr(_ds, 0x561)) != 3074)
      {
        _pc = 0x1087;
        continue;
      };
      memory[adr(_ds, 0x56D)] += 1;
      if (memory[adr(_ds, 0x56D)] & 7)
        return;
    case 0x1087:
      yield* sub_11E3();
      yield* sub_1B7A();
      if (flags.carry)
        return;
      yield* sub_20F5();
      if (flags.carry)
        return;
      yield* sub_2DFD();
      r8[bl] = r8[dl];
      r16[bx] &= 0x0e;
      _si = _memoryRead16(ofs(r16[bx] + 0xf92));
      r16[ax] = 0xb800;
      _es = r16[ax];
      _di = _memoryRead16(0x55F);
      _bp = 0x05fa;
      _memoryWrite16(0x561, 3074);
      r16[cx] = 0x0602;
      yield* sub_2D35();
      yield* sub_2DFD();
      r8[bl] = r8[dl];
      r16[bx] &= 0x0006;
      _si = _memoryRead16(ofs(r16[bx] + 0xfa2));
      _di = _memoryRead16(0x55F) + 0xf0;
      _bp = 0x0612;
      r16[cx] = 0x0602;
      yield* sub_2D35();
      memory[0x583] = 0;
      return;
  }
}

function* sub_10DD()
{
  memory[0x55C] = 0;
  memory[0x571] = 1;
  memory[0x576] = 2;
  memory[0x578] = 1;
  memory[0x577] = 0xff;
  memory[0x56E] = 0;
  memory[0x55A] = 1;
  r16[ax] = _memoryRead16(0xFAC);
  _memoryWrite16(0x569, r16[ax]);
  r16[ax] = _memoryRead16(0xFB8);
  _memoryWrite16(0x567, r16[ax]);
  memory[0x550] = 2;
}

function* sub_1112()
{
  r16[cx] = _memoryRead16(0x579);
  r8[dl] = memory[0x57B];
  yield* sub_2CB0();
  _memoryWrite16(0x55F, r16[ax]);
  yield* sub_1124();
}

function* sub_1124()
{
  r16[ax] = SEG_DATA;
  _es = r16[ax];
  _di = 0x05fa;
  _push(_ds);
  _si = _memoryRead16(0x55F);
  r16[ax] = 0xb800;
  _ds = r16[ax];
  r16[cx] = _memoryRead16(adr(_es, 1377));
  yield* sub_2DCA();
  _ds = _pop();
  memory[0x583] = 0;
}

function* sub_1145()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x55F);
  _bp = 0x05fa;
  _si = _memoryRead16(0x55D);
  r16[cx] = _memoryRead16(0x565);
  _memoryWrite16(0x561, r16[cx]);
  memory[0x583] = 0;
  yield* sub_2D35();
}

function* sub_1166()
{
  var _pc = 0x1166;
  while (_pc != -1) switch(_pc)
  {
    case 0x1166:
      r8[dl] = memory[0x57B];
      r16[cx] = _memoryRead16(0x579);
      flags.carry = r16[cx] < 0x0c;
      r16[cx] -= 0x0c;
      if (!flags.carry)
      {
        _pc = 0x1175;
        continue;
      };
      r16[cx] = 0;
    case 0x1175:
      if (r16[cx] < 0x010f)
      {
        _pc = 0x117E;
        continue;
      };
      r16[cx] = 0x010e;
    case 0x117E:
      yield* sub_2CB0();
      _memoryWrite16(0x581, r16[ax]);
      _di = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      _bp = 0x0e;
      _si = 0x1679;
      r16[cx] = 0x1205;
      yield* sub_2CCC();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x57F, r16[dx]);
      _memoryWrite16(0x5A3C, 0);
      _memoryWrite16(0x5A3E, 0);
      do {
        yield* sub_5A1C();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x57F));
      } while (r16[dx] < 0x0a);
      yield* sub_5B21();
      _di = _memoryRead16(0x581);
      _si = 0x0e;
      r16[cx] = 0x1205;
      memory[0x583] = 0;
      yield* sub_2D9D();
      if (memory[adr(_ds, 0x1678)] == 0)
        return;
      if (memory[adr(_ds, 0x1F80)] == 0)
        return;
      memory[adr(_ds, 0x1F80)] -= 1;
      return;
  }
}

function* sub_11E3()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x55F);
  _si = 0x05fa;
  r16[cx] = _memoryRead16(0x561);
  yield* sub_2D9D();
}

function* sub_1200()
{
  var _pc = 0x1200;
  while (_pc != -1) switch(_pc)
  {
    case 0x1200:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x69F));
      if (r16[ax] >= 0x0002)
      {
        _pc = 0x1210;
        continue;
      };
      return;
    case 0x1210:
      _memoryWrite16(0x69F, r16[dx]);
      if (memory[adr(_ds, 0x69B)] != 0)
      {
        _pc = 0x122E;
        continue;
      };
      yield* sub_12C1();
      yield* sub_13B7();
      r16[dx] = r16[ax];
      do {
        yield* sub_13B7();
        r16[ax] -= r16[dx];
      } while (r16[ax] < 0xf8ed);
      return;
    case 0x122E:
      r16[dx] = 0x0201;
      r8[al] = _in(r16[dx]);
      r8[al] &= 0x10;
      memory[0x69A] = r8[al];
      memory[0x69E] = 3;
      yield* sub_13B7();
      _memoryWrite16(0x69C, r16[ax]);
      _out(r16[dx], r8[al]);
      r16[cx] = 0x07d0;
    case 0x1246:
      r8[al] = _in(r16[dx]);
      if (r8[al] & 0x01)
      {
        _pc = 0x125E;
        continue;
      };
      if (!(memory[adr(_ds, 0x69E)] & 1))
      {
        _pc = 0x125E;
        continue;
      };
      memory[adr(_ds, 0x69E)] &= 0xfe;
      yield* sub_12A1();
      memory[0x698] = r8[bl];
    case 0x125E:
      if (r8[al] & 0x02)
      {
        _pc = 0x1275;
        continue;
      };
      if (!(memory[adr(_ds, 0x69E)] & 2))
      {
        _pc = 0x1275;
        continue;
      };
      memory[adr(_ds, 0x69E)] &= 0xfd;
      yield* sub_12A1();
      memory[0x699] = r8[bl];
    case 0x1275:
      if (!(memory[adr(_ds, 0x69E)] & 3))
        return;
      yield* sub_13B7();
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x69C));
      if (--r16[cx] && r16[ax] != 0x1964)
      {
        _pc = 0x1246;
        continue;
      };
      if (!(memory[adr(_ds, 0x69E)] & 1))
      {
        _pc = 0x1294;
        continue;
      };
      memory[0x698] = 0xff;
    case 0x1294:
      if (!(memory[adr(_ds, 0x69E)] & 2))
        return;
      memory[0x699] = 0xff;
      return;
  }
}

function* sub_12A1()
{
  var _pc = 0x12A1;
  while (_pc != -1) switch(_pc)
  {
    case 0x12A1:
      _push(r16[ax]);
      yield* sub_13B7();
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x69C));
      r16[bx] = r16[ax];
      r16[ax] = _pop();
      if (r16[bx] >= 0xf5e6)
      {
        _pc = 0x12B5;
        continue;
      };
      r8[bl] = 0x01;
      return;
    case 0x12B5:
      if (r16[bx] >= 0xfafa)
      {
        _pc = 0x12BE;
        continue;
      };
      r8[bl] = 0;
      return;
    case 0x12BE:
      r8[bl] = 0xff;
      return;
  }
}

function* sub_12C1()
{
  var _pc = 0x12C1;
  while (_pc != -1) switch(_pc)
  {
    case 0x12C1:
      r8[al] = memory[0x6BA];
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x12D3;
        continue;
      };
      r8[al] = (r8[al] & memory[adr(_ds, 0x6BD)]) & memory[adr(_ds, 0x6BE)];
    case 0x12D3:
      r8[al] = r8[al] ^ 0x80;
      if (r8[al] == 0)
      {
        _pc = 0x12D9;
        continue;
      };
      r8[al] = 0x01;
    case 0x12D9:
      memory[0x699] = r8[al];
      r8[al] = memory[0x6B8];
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x12EE;
        continue;
      };
      r8[al] = (r8[al] & memory[adr(_ds, 0x6BC)]) & memory[adr(_ds, 0x6BF)];
    case 0x12EE:
      r8[al] = r8[al] ^ 0x80;
      if (r8[al] == 0)
      {
        _pc = 0x12F7;
        continue;
      };
      memory[0x699] = 0xff;
    case 0x12F7:
      r8[al] = memory[0x6B9];
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x1309;
        continue;
      };
      r8[al] = (r8[al] & memory[adr(_ds, 0x6BC)]) & memory[adr(_ds, 0x6BD)];
    case 0x1309:
      r8[al] = r8[al] ^ 0x80;
      if (r8[al] == 0)
      {
        _pc = 0x130F;
        continue;
      };
      r8[al] = 0x01;
    case 0x130F:
      memory[0x698] = r8[al];
      r8[al] = memory[0x6BB];
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x1324;
        continue;
      };
      r8[al] = (r8[al] & memory[adr(_ds, 0x6BE)]) & memory[adr(_ds, 0x6BF)];
    case 0x1324:
      r8[al] = r8[al] ^ 0x80;
      if (r8[al] == 0)
      {
        _pc = 0x132D;
        continue;
      };
      memory[0x698] = 0xff;
    case 0x132D:
      r8[al] = memory[0x6B7];
      r8[cl] = 0x03;
      r8[al] >>= r8[cl];
      memory[0x69A] = r8[al];
      return;
  }
}

function* sub_1338()
{
  var _pc = 0x1338;
  while (_pc != -1) switch(_pc)
  {
    case 0x1338:
      r16[ax] = _memoryRead16(0x693);
      if (r16[ax] == _memoryRead16(adr(_ds, 0x691)))
        return;
      _memoryWrite16(0x691, r16[ax]);
      if (memory[adr(_ds, 0x6C0)] & 0x80)
      {
        _pc = 0x1358;
        continue;
      };
      r16[ax] = _memoryRead16(0x693);
      if (r16[ax] == _memoryRead16(adr(_ds, 0x6E00)))
        return;
      yield* sub_5E70();
      return;
    case 0x1358:
      if (!(memory[adr(_ds, 0x6C9)] & 0x80))
      {
        _pc = 0x1360;
        continue;
      };
      return;
    case 0x1360:
      if (memory[adr(_ds, 0x6CC)] & 0x80)
      {
        _pc = 0x136D;
        continue;
      };
      memory[0x1F80] = 9;
      return;
    case 0x136D:
      if (!(memory[adr(_ds, 0x6C1)] & 0x80))
      {
        _pc = 0x13A5;
        continue;
      };
      if (memory[adr(_ds, 0x6CB)] & 0x80)
      {
        _pc = 0x1381;
        continue;
      };
      memory[0x41C] = 0xff;
      return;
    case 0x1381:
      if (memory[adr(_ds, 0x6C8)] & 0x80)
      {
        _pc = 0x138E;
        continue;
      };
      memory[0x41B] = 0xff;
      return;
    case 0x138E:
      if (memory[adr(_ds, 0x6C7)] & 0x80)
        return;
      memory[adr(_ds, 0x0)] = (~memory[adr(_ds, 0x0)]);
      if (memory[adr(_ds, 0x0)] != 0)
        return;
      yield* sub_5B21();
      return;
      return;
    case 0x13A5:
      yield* sub_147F();
      r16[ax] = _pop();
      return;
  }
}

function* sub_13AA()
{
  r16[ax] = 0xf000;
  _es = r16[ax];
  r8[al] = 0xff;
  memory[0x697] = r8[al];
}

function* sub_13B7()
{
  yield 0; // TODO

  r8[al] = 0x00;
  _out(0x43, r8[al]);
  r8[al] = _in(0x40);
  r8[ah] = r8[al];
  r8[al] = _in(0x40);
  var temp = r8[al];
  r8[al] = r8[ah];
  r8[ah] = temp;
}

// class CICall
// class CIAssignment
// class CIAlu
// class CIAssignment
// class CICompare
// class CIConditionalJump
// class CIReturn
// class CILabel
// class CICompare
// class CIReturn
function* sub_13D8()
{
  yield 0;
  r16[dx] = 0x03da;
  r8[al] = _in(r16[dx]);
  r8[al] &= 0x08;
}

// class CIData
// class CIData
// class CIData
// class CIData
// class CIData
function* sub_13E8()
{
  _push(r16[ax]);
  _push(_es);
  _push(_di);
  _push(r16[cx]);
  r16[ax] = SEG_DATA;
  _es = r16[ax];
  flags.direction = false;
  _di = 0x06b7;
  r16[cx] = 0x16;
  r8[al] = 0x80;
  _rep_stosb_MemData_DirForward();
  r16[ax] = (_memoryRead16(adr(_es, 1683))) - 0x70;
  _memoryWrite16(adr(_es, 1681), r16[ax]);
  r16[ax] = 0x40;
  _es = r16[ax];
  r8[al] = memory[adr(_es, 18)];
  byte_code_13E7 = r8[al];
  r16[cx] = _pop();
  _di = _pop();
  _es = _pop();
  r16[ax] = _pop();
}

function* sub_1419()
{
  var _pc = 0x1419;
  while (_pc != -1) switch(_pc)
  {
    case 0x1419:
      r16[ax] = 0;
      _es = r16[ax];
      r16[ax] = _memoryRead16(adr(_es, 36));
      r16[bx] = _memoryRead16(adr(_es, 38));
      r16[cx] = _memoryRead16(adr(_es, 288));
      r16[dx] = _memoryRead16(adr(_es, 290));
      word_code_13DF = r16[ax];
      word_code_13E1 = r16[bx];
      word_code_13E3 = r16[cx];
      word_code_13E5 = r16[dx];
      r16[bx] = 0x14b3;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x1450;
        continue;
      };
      r16[bx] = 0x14fb;
    case 0x1450:
      flags.interrupt = false;
      _memoryWrite16(adr(_es, 36), r16[bx]);
      _memoryWrite16(adr(_es, 38), _cs);
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x147D;
        continue;
      };
      _memoryWrite16(adr(_es, 288), 0x1554);
      _memoryWrite16(adr(_es, 290), _cs);
      r16[ax] = 0x40;
      _es = r16[ax];
      r8[al] = (memory[adr(_es, 24)]) | 0x01;
      memory[adr(_es, 24)] = r8[al];
    case 0x147D:
      flags.interrupt = true;
      return;
  }
}

function* sub_147F()
{
  var _pc = 0x147F;
  while (_pc != -1) switch(_pc)
  {
    case 0x147F:
      r16[ax] = 0;
      _es = r16[ax];
      r16[ax] = word_code_13DF;
      r16[bx] = word_code_13E1;
      r16[cx] = word_code_13E3;
      r16[dx] = word_code_13E5;
      flags.interrupt = false;
      _memoryWrite16(adr(_es, 36), r16[ax]);
      _memoryWrite16(adr(_es, 38), r16[bx]);
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x14B1;
        continue;
      };
      _memoryWrite16(adr(_es, 288), r16[cx]);
      _memoryWrite16(adr(_es, 290), r16[dx]);
    case 0x14B1:
      flags.interrupt = true;
      return;
  }
}

// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CITwoArgOp
// class CIAssignment
// class CIAlu
// class CITest
// class CIConditionalJump
// class CIAlu
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIZeroArgOp
// class CIString
// class CIConditionalJump
// class CIAlu
// class CIAlu
// class CIAssignment
// class CILabel
// class CITwoArgOp
// class CIAssignment
// class CIAlu
// class CITwoArgOp
// class CIAssignment
// class CITwoArgOp
// class CICall
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CITwoArgOp
// class CISingleArgOp
// class CIReturn
// class CIZeroArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAlu
// class CITest
// class CIConditionalJump
// class CIAlu
// class CILabel
// class CICompare
// class CIConditionalJump
// class CICompare
// class CIConditionalJump
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CISingleArgOp
// class CICompare
// class CIConditionalJump
// class CILabel
// class CICall
// class CIJump
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIZeroArgOp
// class CIString
// class CIConditionalJump
// class CIAlu
// class CIAlu
// class CIAssignment
// class CILabel
// class CICall
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIReturn
// class CILabel
// class CISingleArgOp
// class CIReturn
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIJump
function* sub_1572()
{
  var _pc = 0x1572;
  while (_pc != -1) switch(_pc)
  {
    case 0x1572:
      r8[al] = (memory[adr(_es, 1737)]) | memory[adr(_es, 1719)];
      if (r8[al] != 0x00)
        return;
      if (memory[adr(_es, 1738)] & 0x80)
      {
        _pc = 0x158D;
        continue;
      };
      r8[al] = 0x20;
      _out(0x20, r8[al]);
      {
        _pc = 0x1557;
        continue;
      };
    case 0x158D:
      if (memory[adr(_es, 1721)] & 0x80)
      {
        _pc = 0x15A4;
        continue;
      };
      if (memory[adr(_es, 1680)] < 1)
        return;
      memory[adr(_es, 1680)] -= 1;
      {
        _pc = 0x15B9;
        continue;
      };
    case 0x15A4:
      if (memory[adr(_es, 1723)] & 0x80)
        return;
      if (memory[adr(_es, 1680)] >= 7)
        return;
      memory[adr(_es, 1680)] += 1;
    case 0x15B9:
      _push(r16[dx]);
      r8[al] = 0x02;
      r16[dx] = 0x03d4;
      _out(r16[dx], r8[al]);
      r8[al] = (memory[adr(_es, 1680)]) + 0x27;
      r16[dx] += 1;
      _out(r16[dx], r8[al]);
      r16[dx] = _pop();
      return;
  }
}

function* sub_15D0()
{
  var _pc = 0x15D0;
  while (_pc != -1) switch(_pc)
  {
    case 0x15D0:
      r16[bx] = _memoryRead16(0x8);
      r8[cl] = memory[ofs(r16[bx] + 0x100e)];
      do {
        do {
          yield* sub_2DFD();
          r8[dl] &= 0x07;
        } while (r8[dl] > r8[cl]);
        r8[dl] = r8[dl] + memory[adr(_ds, r16[bx] + 0x1006)];
      } while (r8[dl] == memory[adr(_ds, 0x1028)]);
      memory[0x1028] = r8[dl];
      r8[bl] = r8[dl];
      r8[cl] = memory[ofs(r16[bx] + 0xff0)];
      r8[dl] = 0x88;
      if (r8[cl] & 0x80)
      {
        _pc = 0x15FF;
        continue;
      };
      r8[dl] = 0x90;
    case 0x15FF:
      r16[cx] = ((r16[cx] & 0x7f) << 1) << 1;
      return;
  }
}

function* sub_1608()
{
  var _pc = 0x1608;
  while (_pc != -1) switch(_pc)
  {
    case 0x1608:
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0x1613;
        continue;
      };
      yield* sub_30FA();
      return;
    case 0x1613:
      if (_memoryRead16(adr(_ds, 0x4)) == 0)
      {
        _pc = 0x161E;
        continue;
      };
      yield* sub_16C6();
      return;
    case 0x161E:
      r8[al] = memory[0x57B] & 0xf8;
      if (r8[al] == 0x60)
      {
        _pc = 0x1630;
        continue;
      };
      yield* sub_1657();
      if (flags.carry)
        return;
      yield* sub_17AD();
      return;
    case 0x1630:
      if (memory[adr(_ds, 0x550)] >= 2)
      {
        _pc = 0x1655;
        continue;
      };
      memory[0x57B] = r8[al];
      r8[al] += 0x32;
      memory[0x57C] = r8[al];
      if (memory[adr(_ds, 0x550)] == 1)
      {
        _pc = 0x1653;
        continue;
      };
      memory[0x550] = 1;
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x556, r16[dx]);
    case 0x1653:
      flags.carry = true;
      return;
    case 0x1655:
      flags.carry = false;
      return;
  }
}

function* sub_1657()
{
  var _pc = 0x1657;
  while (_pc != -1) switch(_pc)
  {
    case 0x1657:
      r8[cl] = (memory[0x57B] + 0x02) & 0xf8;
      r16[bx] = _memoryRead16(0x8);
      r8[bl] = memory[ofs(r16[bx] + 0x1006)];
    case 0x1669:
      r8[al] = memory[ofs(r16[bx] + 0xff0)];
      if (r8[al] != 0x00)
      {
        _pc = 0x1678;
        continue;
      };
      memory[0x127C] = 0;
      flags.carry = false;
      return;
    case 0x1678:
      r16[bx] += 1;
      r8[ch] = 0x88;
      if (r8[al] & 0x80)
      {
        _pc = 0x1681;
        continue;
      };
      r8[ch] = 0x90;
    case 0x1681:
      if (r8[cl] != r8[ch])
      {
        _pc = 0x1669;
        continue;
      };
      r16[ax] = ((r16[ax] & 0x7f) << 1) << 1;
      r16[dx] = _memoryRead16(0x579) & 0xfff8;
      if (r16[dx] < r16[ax])
      {
        _pc = 0x1669;
        continue;
      };
      r16[dx] = (_memoryRead16(0x579) - 0x0f) & 0xfff8;
      if (r16[dx] > r16[ax])
      {
        _pc = 0x1669;
        continue;
      };
      r8[ch] -= 0x02;
      memory[0x57B] = r8[ch];
      r8[ch] += 0x32;
      memory[0x57C] = r8[ch];
      if (memory[adr(_ds, 0x127C)] != 0)
      {
        _pc = 0x16C4;
        continue;
      };
      memory[0x127C] = 1;
      yield* sub_590E();
    case 0x16C4:
      flags.carry = true;
      return;
  }
}

function* sub_16C6()
{
  var _pc = 0x16C6;
  while (_pc != -1) switch(_pc)
  {
    case 0x16C6:
      memory[0x39E0] = 0;
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0x16FC;
        continue;
      };
      r16[ax] = _memoryRead16(0x2650) - 0x0004;
      r8[dl] = memory[0x2652] - 0x08;
      _si = 0x0c;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e10;
      yield* sub_2E29();
      if (!flags.carry)
      {
        _pc = 0x16FC;
        continue;
      };
      memory[0x551] = 1;
      flags.carry = false;
      return;
    case 0x16FC:
      if (_memoryRead16(adr(_ds, 0x4)) != 3)
      {
        _pc = 0x170E;
        continue;
      };
      yield* sub_3C43();
      if (!flags.carry)
      {
        _pc = 0x170E;
        continue;
      };
      memory[0x55C] = 1;
      return;
    case 0x170E:
      r8[cl] = memory[0x57B] & 0xf8;
      r16[bx] = _memoryRead16(ofs(r16[bx] + 0x1269));
    case 0x171F:
      r8[ch] = memory[ofs(r16[bx] + 0x1029)];
      if (r8[ch] != 0x00)
      {
        _pc = 0x172A;
        continue;
      };
      flags.carry = false;
      return;
    case 0x172A:
      r8[al] = memory[ofs(r16[bx] + 0x1089)];
      memory[0x127B] = r8[al];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x11a9));
      _memoryWrite16(0x1279, r16[ax]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x10e9));
      r8[bl] >>= 1;
      r16[bx] += 1;
      if (r8[cl] != r8[ch])
      {
        _pc = 0x171F;
        continue;
      };
      r16[dx] = _memoryRead16(0x579) & 0xfff8;
      if (r16[dx] < r16[ax])
      {
        _pc = 0x171F;
        continue;
      };
      r16[dx] = _memoryRead16(0x579);
      flags.carry = r16[dx] < _memoryRead16(adr(_ds, 0x1279));
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x1279));
      if (!flags.carry)
      {
        _pc = 0x175D;
        continue;
      };
      r16[dx] = 0;
    case 0x175D:
      r16[dx] &= 0xfffc;
      if (r16[dx] > r16[ax])
      {
        _pc = 0x171F;
        continue;
      };
      memory[0x57B] = r8[ch];
      r8[ch] += 0x32;
      memory[0x57C] = r8[ch];
      r8[al] = memory[0x127B];
      memory[0x55C] = r8[al];
      if (r8[al] == 0x00)
      {
        _pc = 0x1780;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x579), _memoryRead16(adr(_ds, 0x579)) & 0xfffc);
    case 0x1780:
      if (_memoryRead16(adr(_ds, 0x4)) != 4)
      {
        _pc = 0x1797;
        continue;
      };
      r16[bx] -= 1;
      flags.carry = r16[bx] < 0x27;
      r16[bx] -= 0x27;
      if (flags.carry)
      {
        _pc = 0x1797;
        continue;
      };
      if (r16[bx] >= 0x10)
      {
        _pc = 0x1797;
        continue;
      };
      r16[bx] += 1;
      memory[0x39E0] = r8[bl];
    case 0x1797:
      flags.carry = true;
      return;
  }
}

function* sub_1799()
{
  r8[cl] = 0x03;
  r16[bx] >>= r8[cl];
  r8[ch] = r8[bl];
  r8[cl] = 0x03;
  r16[bx] >>= r8[cl];
  r8[cl] = r8[ch] & 0x07;
  r8[ch] = 0x80 >> r8[cl];
}

function* sub_17AD()
{
  var _pc = 0x17AD;
  while (_pc != -1) switch(_pc)
  {
    case 0x17AD:
      r8[dl] = memory[0x57B] & 0xf8;
      r16[bx] = 0;
      if (r8[dl] == 0x08)
      {
        _pc = 0x17C9;
        continue;
      };
      r8[bl] += 1;
      if (r8[dl] == 0x28)
      {
        _pc = 0x17C9;
        continue;
      };
      r8[bl] += 1;
      if (r8[dl] != 0x48)
      {
        _pc = 0x1810;
        continue;
      };
    case 0x17C9:
      r16[ax] = _memoryRead16(0x579);
      if (r16[bx] != _memoryRead16(adr(_ds, 0x52F)))
      {
        _pc = 0x17FC;
        continue;
      };
      if (memory[adr(_ds, 0x525)] > 3)
      {
        _pc = 0x17FC;
        continue;
      };
      if (r8[bl] == 0x01)
      {
        _pc = 0x17EE;
        continue;
      };
      r16[cx] = 0x0004;
      r8[cl] = ((r8[cl] - memory[adr(_ds, 0x525)]) << 1) << 1;
      r16[ax] += r16[cx];
      {
        _pc = 0x17FC;
        continue;
      };
    case 0x17EE:
      r8[ch] = 0;
      r8[cl] = ((memory[0x525] + 1) << 1) << 1;
      r16[ax] -= r16[cx];
    case 0x17FC:
      r8[bl] = memory[ofs(r16[bx] + 0x1025)];
      _si = r16[bx];
      r16[bx] = r16[ax] + 0x0a;
      yield* sub_1799();
      if (memory[adr(_ds, r16[bx] + _si + 4118)] & r8[ch])
      {
        _pc = 0x1812;
        continue;
      };
    case 0x1810:
      flags.carry = false;
      return;
    case 0x1812:
      memory[0x57B] = r8[dl];
      r8[dl] += 0x32;
      memory[0x57C] = r8[dl];
      _memoryWrite16(adr(_ds, 0x579), _memoryRead16(adr(_ds, 0x579)) & 0xfff8);
      memory[0x55C] = 1;
      flags.carry = true;
      return;
  }
}

function* sub_1830()
{
  memory[0x1665] = 0;
  memory[0x1673] = 0;
  memory[0x1677] = 0;
  memory[0x1678] = 0;
  _memoryWrite16(0x166C, 9);
}

function* sub_184B()
{
  var _pc = 0x184B;
  while (_pc != -1) switch(_pc)
  {
    case 0x184B:
      if (memory[adr(_ds, 0x1673)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x17EC)))
      {
        _pc = 0x185D;
        continue;
      };
      return;
    case 0x185D:
      _memoryWrite16(0x17EC, r16[dx]);
      if (memory[adr(_ds, 0x1677)] == 0)
      {
        _pc = 0x187F;
        continue;
      };
      r16[ax] = _memoryRead16(0x1671) & 0xfff8;
      r16[bx] = _memoryRead16(0x579) & 0xfff8;
      if (r16[ax] != r16[bx])
      {
        _pc = 0x187F;
        continue;
      };
      memory[0x1674] = 0;
    case 0x187F:
      memory[adr(_ds, 0x17E9)] += 1;
      if (_memoryRead16(adr(_ds, 0x17EA)) > 1)
      {
        _pc = 0x188E;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x17EA), _memoryRead16(adr(_ds, 0x17EA)) - 1);
    case 0x188E:
      r16[ax] = _memoryRead16(0x1671);
      r16[dx] = _memoryRead16(0x17EA);
      r8[cl] = 0x03;
      r8[dl] >>= r8[cl];
      if (memory[adr(_ds, 0x1674)] < 1)
      {
        _pc = 0x18B5;
        continue;
      };
      if (memory[adr(_ds, 0x1674)] != 1)
      {
        _pc = 0x18AF;
        continue;
      };
      r16[ax] += r16[dx];
      if (r16[ax] < 0x012f)
      {
        _pc = 0x18B5;
        continue;
      };
      r16[ax] = 0x012e;
      {
        _pc = 0x18B5;
        continue;
      };
    case 0x18AF:
      flags.carry = r16[ax] < r16[dx];
      r16[ax] -= r16[dx];
      if (!flags.carry)
      {
        _pc = 0x18B5;
        continue;
      };
      r16[ax] = 0;
    case 0x18B5:
      _memoryWrite16(0x1671, r16[ax]);
      r16[bx] = _memoryRead16(0x17DF);
      r8[al] = (memory[0x17E9] >> 1) + memory[adr(_ds, 0x1673)];
      r8[dl] = r8[al];
      flags.carry = r8[al] < memory[adr(_ds, 0x1676)];
      r8[al] = r8[al] - memory[adr(_ds, 0x1676)];
      if (flags.carry)
      {
        _pc = 0x18E1;
        continue;
      };
      flags.carry = r8[bh] < r8[al];
      r8[bh] -= r8[al];
      if (r8[bh] == 0)
      {
        _pc = 0x18D3;
        continue;
      };
      if (!flags.carry)
      {
        _pc = 0x18E1;
        continue;
      };
    case 0x18D3:
      memory[0x1673] = 0;
      memory[0x1678] = 0;
      yield* sub_1922();
      return;
    case 0x18E1:
      memory[0x1673] = r8[dl];
      r16[cx] = _memoryRead16(0x1671);
      _memoryWrite16(0x17E1, r16[bx]);
      yield* sub_2CB0();
      _memoryWrite16(0x17E7, r16[ax]);
      if (memory[adr(_ds, 0x17E9)] == 2)
      {
        _pc = 0x18FD;
        continue;
      };
      yield* sub_1922();
    case 0x18FD:
      yield* sub_1B7A();
      if (flags.carry)
        return;
      _di = _memoryRead16(0x17E7);
      _memoryWrite16(0x17E5, _di);
      r16[cx] = _memoryRead16(0x17E1);
      _memoryWrite16(0x17E3, r16[cx]);
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = _memoryRead16(0x17DD);
      _bp = 0x17ee;
      yield* sub_2CCC();
      return;
  }
}

function* sub_1922()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x17E5);
  _si = 0x17ee;
  r16[cx] = _memoryRead16(0x17E3);
  yield* sub_2D9D();
}

function* sub_1936()
{
  var _pc = 0x1936;
  while (_pc != -1) switch(_pc)
  {
    case 0x1936:
      memory[adr(_ds, 0x166A)] -= 1;
      if (memory[adr(_ds, 0x166A)] == 0)
      {
        _pc = 0x193D;
        continue;
      };
      return;
    case 0x193D:
      memory[0x166A] = 0x0d;
      yield* sub_13D8();
      if (r8[al] != 0)
        return;
      if (memory[adr(_ds, 0x1665)] == 0)
      {
        _pc = 0x1951;
        continue;
      };
      yield* sub_1B05();
    case 0x1951:
      if (memory[adr(_ds, 0x1673)] != 0)
        return;
      if (memory[adr(_ds, 0x1665)] != 0)
      {
        _pc = 0x19CD;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] > 0x60)
        return;
      memory[0x1677] = 0;
      if (memory[adr(_ds, 0x550)] != 1)
      {
        _pc = 0x198A;
        continue;
      };
      if (memory[adr(_ds, 0x418)] != 0)
      {
        _pc = 0x198A;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x556));
      if (r16[dx] < 0x48)
      {
        _pc = 0x198A;
        continue;
      };
      memory[adr(_ds, 0x1677)] += 1;
    case 0x198A:
      yield* sub_2DFD();
      if (memory[adr(_ds, 0x1677)] == 0)
      {
        _pc = 0x199A;
        continue;
      };
      r8[dl] &= 0x03;
      {
        _pc = 0x19A2;
        continue;
      };
    case 0x199A:
      r8[dl] &= 0x0f;
      if (r8[dl] >= 0x0c)
        return;
    case 0x19A2:
      memory[0x1669] = r8[dl];
      yield* sub_1AEA();
      _memoryWrite16(0x1666, r16[cx]);
      memory[0x1668] = r8[dl];
      yield* sub_1B05();
      if (flags.carry)
      {
        _pc = 0x198A;
        continue;
      };
      memory[0x1665] = 0x1d;
      r16[bx] = _memoryRead16(0x8);
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x181e));
      _memoryWrite16(0x166C, r16[ax]);
      memory[0x1670] = 1;
    case 0x19CD:
      yield* sub_1B05();
      if (flags.carry)
        return;
      memory[0x1664] = 0;
      yield* sub_1B4C();
      if (!flags.carry)
      {
        _pc = 0x19E1;
        continue;
      };
      memory[adr(_ds, 0x1664)] += 1;
      return;
    case 0x19E1:
      if (memory[adr(_ds, 0x1665)] != 0x10)
      {
        _pc = 0x19F0;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x166E, r16[dx]);
    case 0x19F0:
      if (memory[adr(_ds, 0x1665)] != 0x0f)
      {
        _pc = 0x1A76;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x166E));
      if (r16[dx] >= _memoryRead16(adr(_ds, 0x166C)))
      {
        _pc = 0x1A76;
        continue;
      };
      if (memory[adr(_ds, 0x1670)] == 0)
        return;
      if (memory[adr(_ds, 0x1673)] != 0)
        return;
      if (memory[adr(_ds, 0x418)] != 0)
        return;
      memory[adr(_ds, 0x1670)] -= 1;
      memory[0x1678] = 1;
      r8[al] = memory[0x1668];
      memory[0x1673] = r8[al];
      yield* sub_2DFD();
      r16[dx] = (r16[dx] & 0x0f) + _memoryRead16(adr(_ds, 0x1666));
      _memoryWrite16(0x1671, r16[dx]);
      r8[al] = 0x01;
      if (r16[dx] < _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x1A42;
        continue;
      };
      r8[al] = 0xff;
    case 0x1A42:
      memory[0x1674] = r8[al];
      yield* sub_2DFD();
      r8[bl] = r8[dl];
      r16[bx] &= 0x0006;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x17c9));
      _memoryWrite16(0x17DD, r16[ax]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x17d1));
      _memoryWrite16(0x17DF, r16[ax]);
      r8[bl] >>= 1;
      r8[al] = memory[ofs(r16[bx] + 0x17d9)];
      memory[0x1676] = r8[al];
      _memoryWrite16(0x17EA, 0x20);
      memory[0x17E9] = 1;
      memory[0x1675] = 0;
      return;
    case 0x1A76:
      memory[adr(_ds, 0x1665)] -= 1;
      r16[cx] = _memoryRead16(0x1666);
      r8[dl] = memory[0x1668];
      if (memory[adr(_ds, 0x1665)] <= 0x0e)
      {
        _pc = 0x1A93;
        continue;
      };
      r8[dl] = (r8[dl] + memory[adr(_ds, 0x1665)]) - 0x0e;
      {
        _pc = 0x1A9A;
        continue;
      };
    case 0x1A93:
      r8[dl] = (r8[dl] + 0x0e) - memory[adr(_ds, 0x1665)];
    case 0x1A9A:
      memory[0x166B] = r8[dl];
      yield* sub_2CB0();
      _di = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      flags.direction = false;
      r16[cx] = 0x0004;
      if (memory[adr(_ds, 0x1665)] <= 0x0e)
      {
        _pc = 0x1AD7;
        continue;
      };
      if (memory[adr(_ds, 0x418)] == 0)
      {
        _pc = 0x1AD2;
        continue;
      };
      r8[al] = memory[0x166B] - memory[adr(_ds, 0x1668)];
      r8[ah] = 0;
      r8[cl] = 0x03;
      r16[ax] = (r16[ax] << r8[cl]) + 0x15e0;
      _si = r16[ax];
      r16[cx] = 0x0004;
      _rep_movsw_MemB800_MemData_DirForward();
      return;
    case 0x1AD2:
      r16[ax] = 0;
      _rep_stosw_MemB800_DirForward();
      return;
    case 0x1AD7:
      r8[al] = memory[0x166B] - memory[adr(_ds, 0x1668)];
      r8[ah] = 0x0a;
      r16[ax] = (r8[ah] * r8[al]) + 0x2681;
      _si = r16[ax];
      _rep_movsw_MemB800_MemData_DirForward();
      return;
  }
}

function* sub_1AEA()
{
  r8[bh] = 0;
  r8[bl] = (r8[dl] & 0x03) << 1;
  r16[cx] = _memoryRead16(ofs(r16[bx] + 0x1658));
  r8[bl] = (r8[dl] >> 2) & 0x03;
  r8[dl] = memory[ofs(r16[bx] + 0x1660)];
}

function* sub_1B05()
{
  var _pc = 0x1B05;
  while (_pc != -1) switch(_pc)
  {
    case 0x1B05:
      r16[ax] = _memoryRead16(0x1666);
      r8[dl] = memory[0x1668];
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _si = 0x20;
      _di = 0x18;
      r16[cx] = 0x0e0f;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0x1B4A;
        continue;
      };
      if (memory[adr(_ds, 0x55A)] != 0)
      {
        _pc = 0x1B4A;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] >= 0x60)
      {
        _pc = 0x1B4A;
        continue;
      };
      if (memory[adr(_ds, 0x1665)] < 5)
      {
        _pc = 0x1B4A;
        continue;
      };
      if (memory[adr(_ds, 0x1665)] >= 0x19)
      {
        _pc = 0x1B4A;
        continue;
      };
      memory[0x551] = 1;
    case 0x1B4A:
      flags.carry = true;
      return;
  }
}

function* sub_1B4C()
{
  var _pc = 0x1B4C;
  while (_pc != -1) switch(_pc)
  {
    case 0x1B4C:
      r8[al] = memory[0x1669];
      if (r8[al] >= 0x08)
      {
        _pc = 0x1B78;
        continue;
      };
      r16[bx] = 0x0002;
      if (!(r8[al] & 0x04))
      {
        _pc = 0x1B5C;
        continue;
      };
      r8[bl] <<= 1;
    case 0x1B5C:
      r16[ax] = (_memoryRead16(ofs(r16[bx] + 0x1f30))) + 0x10;
      if (r16[ax] < _memoryRead16(adr(_ds, 0x1666)))
      {
        _pc = 0x1B78;
        continue;
      };
      flags.carry = r16[ax] < 0x30;
      r16[ax] -= 0x30;
      if (!flags.carry)
      {
        _pc = 0x1B70;
        continue;
      };
      r16[ax] = 0;
    case 0x1B70:
      if (r16[ax] > _memoryRead16(adr(_ds, 0x1666)))
      {
        _pc = 0x1B78;
        continue;
      };
      flags.carry = true;
      return;
    case 0x1B78:
      flags.carry = false;
      return;
  }
}

function* sub_1B7A()
{
  var _pc = 0x1B7A;
  while (_pc != -1) switch(_pc)
  {
    case 0x1B7A:
      if (_memoryRead16(adr(_ds, 0x4)) != 0)
      {
        _pc = 0x1BE1;
        continue;
      };
      r8[dl] = memory[0x1673];
      if (r8[dl] == 0x00)
      {
        _pc = 0x1BE1;
        continue;
      };
      r16[cx] = _memoryRead16(0x17DF);
      var temp = r8[cl];
      r8[cl] = r8[ch];
      r8[ch] = temp;
      _si = 0x10;
      r16[ax] = _memoryRead16(0x1671);
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r8[ch] = 0x0e;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      yield* sub_11E3();
      yield* sub_1922();
      yield* sub_10DD();
      if (memory[adr(_ds, 0x1675)] != 0)
      {
        _pc = 0x1BDF;
        continue;
      };
      memory[0x1675] = 1;
      yield* sub_1166();
      r8[dl] = 0x01;
      if (memory[adr(_ds, 0x1674)] == 0xff)
      {
        _pc = 0x1BCB;
        continue;
      };
      r8[dl] = 0xff;
    case 0x1BCB:
      memory[0x1674] = r8[dl];
      _memoryWrite16(0x17EA, 0x60);
      memory[0x17E9] = 1;
      memory[0x55C] = 0;
    case 0x1BDF:
      flags.carry = true;
      return;
    case 0x1BE1:
      flags.carry = false;
      return;
  }
}

function* sub_1BF0()
{
  var _pc = 0x1BF0;
  while (_pc != -1) switch(_pc)
  {
    case 0x1BF0:
      r16[bx] = 0;
      r8[ah] = 0x0b;
      _interrupt(0x10);
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x1C12;
        continue;
      };
      if (memory[adr(_ds, 0x553)] == 0)
      {
        _pc = 0x1C12;
        continue;
      };
      yield* sub_528B();
      _memoryWrite16(0x579, 0x98);
      memory[0x57B] = 0x5f;
    case 0x1C12:
      r16[ax] = 0xb800;
      _es = r16[ax];
      flags.direction = false;
      _memoryWrite16(0x1839, 0);
      yield* sub_1C67();
      yield* sub_5B21();
      yield* sub_1D31();
      if (_memoryRead16(adr(_ds, 0x4)) != 0)
      {
        _pc = 0x1C49;
        continue;
      };
      if (memory[adr(_ds, 0x553)] == 0)
      {
        _pc = 0x1C46;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x1C41;
        continue;
      };
      yield* sub_5313();
      {
        _pc = 0x1C49;
        continue;
      };
    case 0x1C41:
      yield* sub_38B0();
      {
        _pc = 0x1C49;
        continue;
      };
    case 0x1C46:
      yield* sub_1D76();
    case 0x1C49:
      if (_memoryRead16(adr(_ds, 0x4)) == 7)
      {
        _pc = 0x1C5A;
        continue;
      };
      r16[ax] = 0xaaaa;
      if (_memoryRead16(adr(_ds, 0x4)) != 2)
      {
        _pc = 0x1C5D;
        continue;
      };
    case 0x1C5A:
      r16[ax] = 0x5555;
    case 0x1C5D:
      _memoryWrite16(0x1839, r16[ax]);
      yield* sub_1C67();
      yield* sub_5B21();
      return;
  }
}

function* sub_1C67()
{
  var _pc = 0x1C67;
  while (_pc != -1) switch(_pc)
  {
    case 0x1C67:
      nullsub_2();
      _memoryWrite16(0x1835, 1);
      memory[0x1837] = 8;
      r16[cx] = _memoryRead16(0x579);
      r8[dl] = memory[0x57B];
      r16[cx] = (r16[cx] + 0x0c) & 0xfff0;
      r8[dl] += 0x08;
      memory[0x1838] = 0;
    case 0x1C8C:
      yield* sub_5897();
      _memoryWrite16(0x1832, r16[cx]);
      memory[0x1834] = r8[dl];
      yield* sub_2CB0();
      _di = r16[ax];
      r8[bl] = memory[0x1837];
    case 0x1CA0:
      r16[ax] = _memoryRead16(0x1839);
      r16[cx] = _memoryRead16(0x1835) >> 3;
      _rep_stosw_MemB800_DirForward();
      r16[cx] = (_memoryRead16(0x1835) >> 2) & 0xfe;
      _di = (_di - r16[cx]) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x1CCA;
        continue;
      };
      _di += 0x50;
    case 0x1CCA:
      r8[bl] -= 1;
      if (r8[bl] != 0)
      {
        _pc = 0x1CA0;
        continue;
      };
      if (memory[adr(_ds, 0x1838)] != 0x0f)
      {
        _pc = 0x1CD6;
        continue;
      };
      return;
    case 0x1CD6:
      _memoryWrite16(adr(_ds, 0x1835), _memoryRead16(adr(_ds, 0x1835)) + 0x20);
      memory[adr(_ds, 0x1837)] += 0x10;
      r16[cx] = _memoryRead16(0x1832);
      r8[dl] = memory[0x1834];
      flags.carry = r16[cx] < 0x10;
      r16[cx] -= 0x10;
      if (!flags.carry)
      {
        _pc = 0x1CF4;
        continue;
      };
      r16[cx] = 0;
      memory[adr(_ds, 0x1838)] |= 1;
    case 0x1CF4:
      r16[ax] = _memoryRead16(0x1835) + r16[cx];
      if (r16[ax] < 0x0140)
      {
        _pc = 0x1D0B;
        continue;
      };
      r16[ax] = 0x0140 - r16[cx];
      _memoryWrite16(0x1835, r16[ax]);
      memory[adr(_ds, 0x1838)] |= 2;
    case 0x1D0B:
      flags.carry = r8[dl] < 0x08;
      r8[dl] -= 0x08;
      if (!flags.carry)
      {
        _pc = 0x1D17;
        continue;
      };
      r8[dl] = 0;
      memory[adr(_ds, 0x1838)] |= 4;
    case 0x1D17:
      r8[al] = memory[0x1837];
      flags.carry = (r8[al] + r8[dl]) >= 0x100;
      r8[al] += r8[dl];
      if (flags.carry)
      {
        _pc = 0x1D22;
        continue;
      };
      if (r8[al] < 0xc8)
      {
        _pc = 0x1C8C;
        continue;
      };
    case 0x1D22:
      r8[al] = 0xc8 - r8[dl];
      memory[0x1837] = r8[al];
      memory[adr(_ds, 0x1838)] |= 8;
      {
        _pc = 0x1C8C;
        continue;
      };
      return;
  }
}

function* sub_1D31()
{
  var _pc = 0x1D31;
  while (_pc != -1) switch(_pc)
  {
    case 0x1D31:
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x1D48;
        continue;
      };
      r8[ah] = 0x0b;
      r8[bh] = 0x01;
      _si = _memoryRead16(0x4);
      r8[bl] = memory[ofs(_si + 0x1853)];
      _interrupt(0x10);
      {
        _pc = 0x1D67;
        continue;
      };
    case 0x1D48:
      _si = _memoryRead16(0x4);
      r8[bl] = 0x01;
      r8[bh] = memory[ofs(_si + 0x183b)];
      yield* sub_1D6E();
      r8[bl] = 0x02;
      r8[bh] = memory[ofs(_si + 0x1843)];
      yield* sub_1D6E();
      r8[bl] = 0x03;
      r8[bh] = memory[ofs(_si + 0x184b)];
      yield* sub_1D6E();
    case 0x1D67:
      r8[ah] = 0x0b;
      r16[bx] = 0;
      _interrupt(0x10);
      return;
  }
}

function* sub_1D6E()
{
  r16[ax] = 0x1000;
  _push(_si);
  _interrupt(0x10);
  _si = _pop();
}

function* sub_1D76()
{
  var _pc = 0x1D76;
  while (_pc != -1) switch(_pc)
  {
    case 0x1D76:
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x1D81;
        continue;
      };
      yield* sub_6040();
      return;
    case 0x1D81:
      yield* sub_57D5();
      r16[ax] = 0x185b;
      if (memory[adr(_ds, 0x552)] == 0)
      {
        _pc = 0x1DC6;
        continue;
      };
      r16[bx] = _memoryRead16(0x1C30);
      _memoryWrite16(adr(_ds, 0x1C30), _memoryRead16(adr(_ds, 0x1C30)) + 2);
      r16[bx] &= 0x0006;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x1c26));
      if (memory[adr(_ds, 0x1F80)] == 0)
      {
        _pc = 0x1DAA;
        continue;
      };
      memory[adr(_ds, 0x1F80)] -= 1;
    case 0x1DAA:
      if (memory[adr(_ds, 0x552)] != 0xdd)
      {
        _pc = 0x1DC6;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x8)) == 0)
      {
        _pc = 0x1DC6;
        continue;
      };
      if (memory[adr(_ds, 0x1F80)] < 1)
      {
        _pc = 0x1DC6;
        continue;
      };
      yield* sub_5BE0();
      yield* sub_5B21();
      return;
    case 0x1DC6:
      _memoryWrite16(0x1C2E, r16[ax]);
      _memoryWrite16(0x1C1B, 32896);
      memory[0x1C1D] = 0x1c;
    case 0x1DD4:
      yield* sub_1E17();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x1830, r16[dx]);
      do {
        yield* sub_57E4();
        r8[ah] = 0;
        _interrupt(0x1a);
      } while (r16[dx] == _memoryRead16(adr(_ds, 0x1830)));
      if (memory[adr(_ds, 0x1C1D)] > 0x14)
      {
        _pc = 0x1E02;
        continue;
      };
      r8[bh] = 0;
      r8[bl] = memory[0x1C1D] & 0x06;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x1c1e));
      {
        _pc = 0x1E0A;
        continue;
      };
    case 0x1E02:
      r16[ax] = _memoryRead16(0x1C1B);
      flags.carry = true;
      r8[al] = _rcr8(r8[al], 1);
      r8[ah] = r8[al];
    case 0x1E0A:
      _memoryWrite16(0x1C1B, r16[ax]);
      memory[adr(_ds, 0x1C1D)] -= 1;
      if (memory[adr(_ds, 0x1C1D)] != 0)
      {
        _pc = 0x1DD4;
        continue;
      };
      yield* sub_5B21();
      return;
  }
}

function* sub_1E17()
{
  flags.direction = false;
  _push(_ds);
  _es = _pop();
  _si = _memoryRead16(0x1C2E);
  _di = 0x0e;
  r16[cx] = 0x60;
  do {
    _lodsw_MemData_DirForward();
    r16[ax] = r16[ax] & _memoryRead16(adr(_ds, 0x1C1B));
    _stosw_MemData_DirForward();
  } while (--r16[cx]);
  r16[ax] = 0xb800;
  _es = r16[ax];
  _si = 0x0e;
  _di = 0x0ed0;
  r16[cx] = 0x0c08;
  yield* sub_2D9D();
}

function* sub_1E40()
{
  memory[0x1CBF] = 0;
  _memoryWrite16(0x1CE1, 0);
  memory[0x1CC0] = 0;
  memory[0x1CC1] = 0;
  memory[0x1CB8] = 0;
  memory[0x1CC8] = 0xb1;
  yield* sub_5450();
}

function* sub_1E63()
{
  var _pc = 0x1E63;
  while (_pc != -1) switch(_pc)
  {
    case 0x1E63:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[cx] = r16[dx];
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x1CC9));
      r16[ax] = (_memoryRead16(0x1CE1) & 0x0001) + 0x0001;
      if (r16[dx] >= r16[ax])
      {
        _pc = 0x1E7B;
        continue;
      };
      return;
    case 0x1E7B:
      yield* sub_13D8();
      if (r8[al] == 0)
        return;
      _memoryWrite16(0x1CC9, r16[cx]);
      _memoryWrite16(adr(_ds, 0x1CE1), _memoryRead16(adr(_ds, 0x1CE1)) + 1);
      if (memory[adr(_ds, 0x1CC1)] == 0)
      {
        _pc = 0x1EE2;
        continue;
      };
      memory[adr(_ds, 0x1CC1)] -= 1;
      if (memory[adr(_ds, 0x1CC1)] != 0)
      {
        _pc = 0x1EC9;
        continue;
      };
      yield* sub_5B21();
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x1EC2;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x4)) == 0)
      {
        _pc = 0x1EB7;
        continue;
      };
      memory[0x552] = 0xdd;
      _memoryWrite16(0x579, 0xa0);
      memory[0x57B] = 0x60;
      return;
    case 0x1EB7:
      if (memory[adr(_ds, 0x1F80)] == 0)
      {
        _pc = 0x1EC2;
        continue;
      };
      memory[adr(_ds, 0x1F80)] -= 1;
    case 0x1EC2:
      yield* sub_20E1();
      yield* sub_1E40();
      return;
    case 0x1EC9:
      yield* sub_2022();
      r16[ax] = 0x0104;
      r8[al] = r8[al] - memory[adr(_ds, 0x1CC1)];
      if (memory[adr(_ds, 0x1CD0)] == 0xff)
      {
        _pc = 0x1EDC;
        continue;
      };
      r8[ah] = 0xff;
    case 0x1EDC:
      yield* sub_2059();
      {
        _pc = 0x1FFB;
        continue;
      };
    case 0x1EE2:
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x1F0C;
        continue;
      };
      r8[dl] = memory[0x1CB8];
      if (_memoryRead16(adr(_ds, 0x1CB9)) == 0)
      {
        _pc = 0x1F02;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x1CB9), _memoryRead16(adr(_ds, 0x1CB9)) - 1);
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x1F02;
        continue;
      };
      r8[dl] = 0xff;
    case 0x1F02:
      memory[0x1CD0] = r8[dl];
      r16[ax] = _memoryRead16(0x1CC6);
      {
        _pc = 0x1FAB;
        continue;
      };
    case 0x1F0C:
      if (memory[adr(_ds, 0x1CBF)] != 0)
      {
        _pc = 0x1F75;
        continue;
      };
      if (memory[adr(_ds, 0x1CC0)] != 0)
      {
        _pc = 0x1F57;
        continue;
      };
      if (memory[adr(_ds, 0x1D58)] != 0)
      {
        _pc = 0x1F3D;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] < 0xb4)
        return;
      if (memory[adr(_ds, 0x558)] != 0)
        return;
      yield* sub_2DFD();
      r16[bx] = _memoryRead16(0x8);
      if (r8[dl] < memory[adr(_ds, r16[bx] + 0x1cd1)])
      {
        _pc = 0x1F3D;
        continue;
      };
      return;
    case 0x1F3D:
      r8[al] = 0x01;
      _memoryWrite16(0x59BA, 0);
      if (_memoryRead16(adr(_ds, 0x579)) >= 0xa0)
      {
        _pc = 0x1F4F;
        continue;
      };
      r8[al] = 0xff;
    case 0x1F4F:
      memory[0x1CD0] = r8[al];
      memory[0x1CC0] = 4;
    case 0x1F57:
      memory[adr(_ds, 0x1CC0)] -= 1;
      if (memory[adr(_ds, 0x1CC0)] != 0)
      {
        _pc = 0x1F65;
        continue;
      };
      memory[0x1CBF] = 1;
      {
        _pc = 0x1F75;
        continue;
      };
    case 0x1F65:
      yield* sub_2022();
      r8[al] = memory[0x1CC0];
      r8[ah] = memory[0x1CD0];
      yield* sub_2059();
      {
        _pc = 0x1FFB;
        continue;
      };
    case 0x1F75:
      memory[0x1D58] = 0;
      r16[ax] = _memoryRead16(0x1CC6);
      if (memory[adr(_ds, 0x57B)] < 0xb4)
      {
        _pc = 0x1FAB;
        continue;
      };
      if (memory[adr(_ds, 0x558)] != 0)
      {
        _pc = 0x1FAB;
        continue;
      };
      yield* sub_2DFD();
      r16[bx] = _memoryRead16(0x8);
      if (r8[dl] > memory[adr(_ds, r16[bx] + 0x1cd9)])
      {
        _pc = 0x1FAB;
        continue;
      };
      if (r16[ax] > _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x1FA6;
        continue;
      };
      memory[0x1CD0] = 1;
      {
        _pc = 0x1FAB;
        continue;
      };
    case 0x1FA6:
      memory[0x1CD0] = 0xff;
    case 0x1FAB:
      if (memory[adr(_ds, 0x1CD0)] < 1)
      {
        _pc = 0x1FEF;
        continue;
      };
      if (memory[adr(_ds, 0x1CD0)] == 1)
      {
        _pc = 0x1FE2;
        continue;
      };
      flags.carry = r16[ax] < 0x0008;
      r16[ax] -= 0x0008;
      if (!flags.carry)
      {
        _pc = 0x1FEF;
        continue;
      };
      r16[ax] = 0;
    case 0x1FBB:
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x1FCC;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x1CB9)) != 0)
      {
        _pc = 0x1FEF;
        continue;
      };
      {
        _pc = 0x1FDA;
        continue;
      };
    case 0x1FCC:
      if (memory[adr(_ds, 0x57B)] < 0xb4)
      {
        _pc = 0x1FDA;
        continue;
      };
      if (memory[adr(_ds, 0x558)] == 0)
      {
        _pc = 0x1FEF;
        continue;
      };
    case 0x1FDA:
      memory[0x1CC1] = 4;
      {
        _pc = 0x1FEF;
        continue;
      };
    case 0x1FE2:
      r16[ax] += 0x0008;
      if (r16[ax] < 0x011e)
      {
        _pc = 0x1FEF;
        continue;
      };
      r16[ax] = 0x011e;
      {
        _pc = 0x1FBB;
        continue;
      };
    case 0x1FEF:
      _memoryWrite16(0x1CC6, r16[ax]);
      yield* sub_2022();
      _memoryWrite16(0x1CC4, 3844);
    case 0x1FFB:
      r16[cx] = _memoryRead16(0x1CC6);
      r8[dl] = memory[0x1CC8];
      yield* sub_2CB0();
      _memoryWrite16(0x1CCD, r16[ax]);
      if (memory[adr(_ds, 0x1CC0)] == 3)
      {
        _pc = 0x2013;
        continue;
      };
      yield* sub_20E1();
    case 0x2013:
      yield* sub_20F5();
      if (flags.carry)
        return;
      r16[ax] = _memoryRead16(0x1CCD);
      _memoryWrite16(0x1CBD, r16[ax]);
      yield* sub_209B();
      return;
  }
}

function* sub_2022()
{
  var _pc = 0x2022;
  while (_pc != -1) switch(_pc)
  {
    case 0x2022:
      r8[bh] = 0;
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x203B;
        continue;
      };
      memory[adr(_ds, 0x1CCF)] += 1;
      r8[bl] = (memory[0x1CCF] & 0x06) | 0x08;
      if (r8[bl] != 0)
      {
        _pc = 0x2051;
        continue;
      };
    case 0x203B:
      memory[adr(_ds, 0x1CCF)] += 2;
      r8[bl] = memory[0x1CCF] & 0x02;
      if (memory[adr(_ds, 0x1CD0)] != 1)
      {
        _pc = 0x2051;
        continue;
      };
      r8[bl] |= 0x04;
    case 0x2051:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x15c8));
      _memoryWrite16(0x1CBB, r16[ax]);
      return;
  }
}

function* sub_2059()
{
  var _pc = 0x2059;
  while (_pc != -1) switch(_pc)
  {
    case 0x2059:
      r16[cx] = 0x0f04;
      r8[cl] -= r8[al];
      _memoryWrite16(0x1CC4, r16[cx]);
      if (r8[ah] == 0xff)
      {
        _pc = 0x2078;
        continue;
      };
      r8[ah] = 0;
      r8[al] <<= 1;
      _memoryWrite16(adr(_ds, 0x1CBB), _memoryRead16(adr(_ds, 0x1CBB)) + r16[ax]);
      _memoryWrite16(0x1CC6, 0);
      {
        _pc = 0x2086;
        continue;
      };
    case 0x2078:
      r8[ah] = 0;
      r8[al] = ((r8[al] << 1) << 1) << 1;
      r16[ax] += 0x0120;
      _memoryWrite16(0x1CC6, r16[ax]);
    case 0x2086:
      _push(_ds);
      _es = _pop();
      _si = _memoryRead16(0x1CBB);
      _di = 0x0e;
      r8[al] = 0x04;
      yield* sub_2D70();
      _memoryWrite16(0x1CBB, 0x0e);
      return;
  }
}

function* sub_209B()
{
  var _pc = 0x209B;
  while (_pc != -1) switch(_pc)
  {
    case 0x209B:
      r16[cx] = _memoryRead16(0x1CC4);
      _memoryWrite16(0x1CC2, r16[cx]);
      r16[ax] = 0xb800;
      if (memory[adr(_ds, 0x1CB8)] != 0)
      {
        _pc = 0x20BE;
        continue;
      };
      _es = r16[ax];
      _di = _memoryRead16(0x1CBD);
      _si = _memoryRead16(0x1CBB);
      _bp = 0x1c40;
      yield* sub_2CCC();
      return;
    case 0x20BE:
      _push(_ds);
      _ds = r16[ax];
      _es = _pop();
      _push(_es);
      _push(_ds);
      _si = _memoryRead16(adr(_es, 7357));
      _di = 0x1c40;
      yield* sub_2DCA();
      _es = _pop();
      _ds = _pop();
      _si = _memoryRead16(adr(_ds, 0x1CBB));
      _di = _memoryRead16(adr(_ds, 0x1CBD));
      r16[cx] = _memoryRead16(adr(_ds, 0x1CC4));
      yield* sub_2D9D();
      return;
  }
}

function* sub_20E1()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x1CBD);
  _si = 0x1c40;
  r16[cx] = _memoryRead16(0x1CC2);
  yield* sub_2D9D();
}

function* sub_20F5()
{
  var _pc = 0x20F5;
  while (_pc != -1) switch(_pc)
  {
    case 0x20F5:
      if (memory[adr(_ds, 0x1CB8)] != 0)
      {
        _pc = 0x2134;
        continue;
      };
      r8[al] = (memory[0x1CBF] | memory[adr(_ds, 0x1CC0)]) | memory[adr(_ds, 0x1CC1)];
      if (r8[al] == 0)
      {
        _pc = 0x2134;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] < 0xa3)
      {
        _pc = 0x2134;
        continue;
      };
      if (memory[adr(_ds, 0x558)] != 0)
      {
        _pc = 0x2134;
        continue;
      };
      r16[ax] = _memoryRead16(0x1CC6) + 0x20;
      if (r16[ax] < _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x2134;
        continue;
      };
      flags.carry = r16[ax] < 0x38;
      r16[ax] -= 0x38;
      if (!flags.carry)
      {
        _pc = 0x212A;
        continue;
      };
      r16[ax] = 0;
    case 0x212A:
      if (r16[ax] > _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x2134;
        continue;
      };
      yield* sub_2136();
      return;
    case 0x2134:
      flags.carry = false;
      return;
  }
}

function* sub_2136()
{
  var _pc = 0x2136;
  while (_pc != -1) switch(_pc)
  {
    case 0x2136:
      if (_memoryRead16(adr(_ds, 0x4)) != 6)
      {
        _pc = 0x2149;
        continue;
      };
      r8[al] = memory[0x57B];
      memory[0x1CC8] = r8[al];
      r16[ax] = _memoryRead16(0x579);
      _memoryWrite16(0x1CC6, r16[ax]);
    case 0x2149:
      r16[ax] = (_memoryRead16(0x1CC6) + _memoryRead16(adr(_ds, 0x579))) >> 1;
      if (r16[ax] < 0x0118)
      {
        _pc = 0x215A;
        continue;
      };
      r16[ax] = 0x0117;
    case 0x215A:
      _memoryWrite16(0x1CC6, r16[ax]);
      r8[bl] = 0x01;
      if (r16[ax] > 0xa0)
      {
        _pc = 0x216E;
        continue;
      };
      r8[bl] = 0xff;
      r16[dx] = 0xa1 - r16[ax];
      {
        _pc = 0x2173;
        continue;
      };
    case 0x216E:
      r16[ax] -= 0x9f;
      r16[dx] = r16[ax];
    case 0x2173:
      memory[0x1CB8] = r8[bl];
      memory[0x1CBF] = 1;
      memory[0x1CC1] = 0;
      r8[cl] = 0x03;
      r16[dx] >>= r8[cl];
      _memoryWrite16(0x1CB9, r16[dx]);
      if (_memoryRead16(adr(_ds, 0x4)) != 6)
      {
        _pc = 0x21BD;
        continue;
      };
      yield* sub_11E3();
      r8[al] = memory[0x1CB8];
      _push(r16[ax]);
      memory[0x1CB8] = 0;
      _memoryWrite16(0x1CC4, 3844);
      r16[ax] = _memoryRead16(0x15C8);
      _memoryWrite16(0x1CBB, r16[ax]);
      r16[cx] = _memoryRead16(0x1CC6);
      r8[dl] = memory[0x1CC8];
      yield* sub_2CB0();
      _memoryWrite16(0x1CBD, r16[ax]);
      yield* sub_209B();
      r16[ax] = _pop();
      memory[0x1CB8] = r8[al];
    case 0x21BD:
      yield* sub_20E1();
      yield* sub_11E3();
      r16[ax] = 0x0000;
      if (_memoryRead16(adr(_ds, 0x579)) >= 0xa0)
      {
        _pc = 0x21D1;
        continue;
      };
      r16[ax] = 0x0122;
    case 0x21D1:
      _memoryWrite16(0x579, r16[ax]);
      if (_memoryRead16(adr(_ds, 0x4)) != 0)
      {
        _pc = 0x21DE;
        continue;
      };
      yield* sub_70D();
    case 0x21DE:
      flags.carry = true;
      return;
  }
}

function* sub_21E0()
{
  var _pc = 0x21E0;
  while (_pc != -1) switch(_pc)
  {
    case 0x21E0:
      r8[al] = (memory[0x1CBF] | memory[adr(_ds, 0x1CC0)]) | memory[adr(_ds, 0x1CC1)];
      if (r8[al] == 0)
      {
        _pc = 0x2209;
        continue;
      };
      r16[ax] = _memoryRead16(0x327D);
      r8[dl] = memory[0x327F];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x1CC6);
      r8[dh] = memory[0x1CC8];
      _di = 0x20;
      r16[cx] = 0x0f1e;
      yield* sub_2E29();
      return;
    case 0x2209:
      flags.carry = false;
      return;
  }
}

function* sub_2210()
{
  memory[0x1D59] = 0;
}

function* sub_2216()
{
  var _pc = 0x2216;
  while (_pc != -1) switch(_pc)
  {
    case 0x2216:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x1D5A)))
      {
        _pc = 0x2221;
        continue;
      };
      return;
    case 0x2221:
      r16[cx] = r16[dx];
      yield* sub_13D8();
      if (r8[al] == 0)
        return;
      _memoryWrite16(0x1D5A, r16[cx]);
      yield* sub_22F7();
      if (flags.carry)
        return;
      if (memory[adr(_ds, 0x1D59)] != 0)
      {
        _pc = 0x226D;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] == 0x86)
      {
        _pc = 0x224E;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] == 0x8e)
      {
        _pc = 0x224E;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x05)
        return;
    case 0x224E:
      yield* sub_15D0();
      r8[dl] += 0x03;
      memory[0x1D5E] = r8[dl];
      yield* sub_2DFD();
      r16[dx] &= 0x0007;
      r16[cx] = (r16[cx] + r16[dx]) + 0x0006;
      _memoryWrite16(0x1D5C, r16[cx]);
      memory[0x1D59] = 0x1b;
    case 0x226D:
      memory[adr(_ds, 0x1D59)] -= 1;
      r16[cx] = _memoryRead16(0x1D5C);
      r8[dl] = memory[0x1D5E];
      if (memory[adr(_ds, 0x1D59)] <= 0x0d)
      {
        _pc = 0x2291;
        continue;
      };
      r8[dl] = (r8[dl] + memory[adr(_ds, 0x1D59)]) - 0x0f;
      r16[bx] = 0x1b02;
      r8[bh] = r8[bh] - memory[adr(_ds, 0x1D59)];
      {
        _pc = 0x229F;
        continue;
      };
    case 0x2291:
      r8[dl] = (r8[dl] + 0x0c) - memory[adr(_ds, 0x1D59)];
      r16[bx] = 0x0002;
      r8[bh] = r8[bh] + memory[adr(_ds, 0x1D59)];
    case 0x229F:
      _memoryWrite16(0x1D64, r16[bx]);
      memory[0x1D5F] = r8[dl];
      yield* sub_2CB0();
      _memoryWrite16(0x1D62, r16[ax]);
      yield* sub_22DC();
      yield* sub_22F7();
      if (flags.carry)
        return;
      if (memory[adr(_ds, 0x1D59)] != 0)
      {
        _pc = 0x22BD;
        continue;
      };
      return;
    case 0x22BD:
      r16[ax] = 0xb800;
      _es = r16[ax];
      _di = _memoryRead16(0x1D62);
      _si = 0x1cf0;
      _memoryWrite16(0x1D60, _di);
      r16[cx] = _memoryRead16(0x1D64);
      _memoryWrite16(0x1D66, r16[cx]);
      _bp = 0x1d24;
      yield* sub_2CCC();
      return;
  }
}

function* sub_22DC()
{
  if (memory[adr(_ds, 0x1D59)] == 0x1a)
    return;
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x1D60);
  _si = 0x1d24;
  r16[cx] = _memoryRead16(0x1D66);
  yield* sub_2D9D();
}

function* sub_22F7()
{
  var _pc = 0x22F7;
  while (_pc != -1) switch(_pc)
  {
    case 0x22F7:
      if (memory[adr(_ds, 0x1D59)] != 0)
      {
        _pc = 0x2300;
        continue;
      };
      flags.carry = false;
      return;
    case 0x2300:
      r16[cx] = _memoryRead16(0x1D64);
      var temp = r8[ch];
      r8[ch] = r8[cl];
      r8[cl] = temp;
      r16[ax] = _memoryRead16(0x1D5C);
      r8[dl] = memory[0x1D5F];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r8[ch] = 0x0e;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      memory[0x1D58] = 1;
      return;
  }
}

function* sub_2330()
{
  var _pc = 0x2330;
  while (_pc != -1) switch(_pc)
  {
    case 0x2330:
      _memoryWrite16(0x1F6C, 0);
      r16[ax] = 0;
      r8[dl] = 0x01;
      if (_memoryRead16(adr(_ds, 0x579)) > 0xa0)
      {
        _pc = 0x2347;
        continue;
      };
      r16[ax] = 0x012c;
      r8[dl] = 0xff;
    case 0x2347:
      _memoryWrite16(0x1F30, r16[ax]);
      _memoryWrite16(0x1F32, r16[ax]);
      _memoryWrite16(0x1F34, r16[ax]);
      memory[0x1F3C] = r8[dl];
      memory[0x1F3D] = r8[dl];
      memory[0x1F3E] = r8[dl];
      memory[0x1F48] = 1;
      memory[0x1F49] = 1;
      memory[0x1F4A] = 1;
      memory[0x1F50] = 0;
      memory[0x1F51] = 0;
      memory[0x1F52] = 0;
      return;
  }
}

function* sub_237B()
{
  var _pc = 0x237B;
  while (_pc != -1) switch(_pc)
  {
    case 0x237B:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x1F65)))
      {
        _pc = 0x2386;
        continue;
      };
      return;
    case 0x2386:
      _memoryWrite16(0x1F65, r16[dx]);
      if (memory[adr(_ds, 0x55A)] != 0)
        return;
      r16[bx] = _memoryRead16(0x1F6C) + 1;
      if (r16[bx] < 0x0003)
      {
        _pc = 0x239E;
        continue;
      };
      r16[bx] = 0x0000;
    case 0x239E:
      _memoryWrite16(0x1F6C, r16[bx]);
      yield* sub_265E();
      if (flags.carry)
        return;
      yield* sub_2567();
      if (flags.carry)
        return;
      r16[bx] = _memoryRead16(0x1F6C);
      if (memory[adr(_ds, r16[bx] + 0x1f50)] == 0)
      {
        _pc = 0x23EB;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[bx] = _memoryRead16(0x1F6C);
      r8[bl] <<= 1;
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, r16[bx] + 0x1f53));
      if (r16[dx] < 0x36)
        return;
      r8[dl] = 0x01;
      r16[ax] = 0x0000;
      if (_memoryRead16(adr(_ds, 0x579)) > 0xa0)
      {
        _pc = 0x23DC;
        continue;
      };
      r16[ax] = 0x012c;
      r8[dl] = 0xff;
    case 0x23DC:
      _memoryWrite16(ofs(r16[bx] + 0x1f30), r16[ax]);
      r8[bl] >>= 1;
      memory[ofs(r16[bx] + 0x1f50)] = 0;
      memory[ofs(r16[bx] + 0x1f3c)] = r8[dl];
    case 0x23EB:
      r8[dl] = memory[ofs(r16[bx] + 0x1f3c)];
      memory[ofs(r16[bx] + 0x1f3f)] = r8[dl];
      if (memory[adr(_ds, 0x1664)] == 0)
      {
        _pc = 0x2403;
        continue;
      };
      _memoryWrite16(0x1F69, 0x0c);
      {
        _pc = 0x2418;
        continue;
      };
    case 0x2403:
      r16[ax] = 0x0008;
      if (memory[adr(_ds, 0x57B)] <= 0x60)
      {
        _pc = 0x240F;
        continue;
      };
      r8[al] >>= 1;
    case 0x240F:
      _memoryWrite16(0x1F69, r16[ax]);
      if (r16[bx] != _memoryRead16(adr(_ds, 0x52F)))
      {
        _pc = 0x2425;
        continue;
      };
    case 0x2418:
      if (memory[adr(_ds, r16[bx] + 0x1f3c)] != 0)
      {
        _pc = 0x2425;
        continue;
      };
      yield* sub_2DFD();
      {
        _pc = 0x248A;
        continue;
      };
    case 0x2425:
      if (memory[adr(_ds, 0x55C)] == 0)
      {
        _pc = 0x2466;
        continue;
      };
      r8[al] = memory[ofs(r16[bx] + 0x1f36)];
      if (r8[al] > memory[adr(_ds, 0x57B)])
      {
        _pc = 0x2466;
        continue;
      };
      r8[al] += 0x10;
      if (r8[al] < memory[adr(_ds, 0x57B)])
      {
        _pc = 0x2466;
        continue;
      };
      yield* sub_2DFD();
      _si = _memoryRead16(0x8);
      if (r8[dl] > memory[adr(_ds, _si + 0x1f6e)])
      {
        _pc = 0x2466;
        continue;
      };
      _memoryWrite16(0x1F69, 0x0c);
      r8[al] = 0x01;
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x1f30));
      r8[bl] >>= 1;
      if (r16[cx] < _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x2492;
        continue;
      };
      r8[al] = 0xff;
      {
        _pc = 0x2492;
        continue;
      };
    case 0x2466:
      r8[cl] = 0x18;
      if (memory[adr(_ds, 0x57B)] <= 0x60)
      {
        _pc = 0x247A;
        continue;
      };
      r8[cl] = 0x28;
      if (memory[adr(_ds, r16[bx] + 0x1f3c)] != 0)
      {
        _pc = 0x247A;
        continue;
      };
      r8[cl] = 0x10;
    case 0x247A:
      yield* sub_2DFD();
      if (r8[dl] > r8[cl])
      {
        _pc = 0x2496;
        continue;
      };
      r8[al] = 0x00;
      if (memory[adr(_ds, r16[bx] + 0x1f3c)] != 0)
      {
        _pc = 0x2492;
        continue;
      };
    case 0x248A:
      r8[al] = r8[dl] & 0x01;
      if (r8[al] != 0)
      {
        _pc = 0x2492;
        continue;
      };
      r8[al] = 0xff;
    case 0x2492:
      memory[ofs(r16[bx] + 0x1f3c)] = r8[al];
    case 0x2496:
      r8[dl] = memory[ofs(r16[bx] + 0x1f3c)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x1f30));
      if (r8[dl] < 0x01)
      {
        _pc = 0x24C2;
        continue;
      };
      if (r8[dl] != 0x01)
      {
        _pc = 0x24B8;
        continue;
      };
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x1F69));
      if (r16[ax] < 0x012f)
      {
        _pc = 0x24C2;
        continue;
      };
      r16[ax] = 0x012e;
      r8[dl] = 0xff;
      {
        _pc = 0x24C2;
        continue;
      };
    case 0x24B8:
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x1F69));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x1F69));
      if (!flags.carry)
      {
        _pc = 0x24C2;
        continue;
      };
      r16[ax] = 0;
      r8[dl] = 0x01;
    case 0x24C2:
      _memoryWrite16(ofs(r16[bx] + 0x1f30), r16[ax]);
      r8[bl] >>= 1;
      memory[ofs(r16[bx] + 0x1f3c)] = r8[dl];
      r8[dl] = memory[ofs(r16[bx] + 0x1f36)];
      r16[cx] = r16[ax];
      yield* sub_2CB0();
      _memoryWrite16(0x1F4B, r16[ax]);
      r16[bx] = _memoryRead16(0x1F6C);
      if (memory[adr(_ds, r16[bx] + 0x1f48)] != 0)
      {
        _pc = 0x24F0;
        continue;
      };
      r8[al] = (memory[ofs(r16[bx] + 0x1f3c)]) | memory[adr(_ds, r16[bx] + 0x1f3f)];
      if (r8[al] == 0)
      {
        _pc = 0x24F0;
        continue;
      };
      yield* sub_254D();
    case 0x24F0:
      yield* sub_265E();
      if (flags.carry)
        return;
      yield* sub_2567();
      if (!flags.carry)
      {
        _pc = 0x24FB;
        continue;
      };
      return;
    case 0x24FB:
      r16[bx] = _memoryRead16(0x1F6C);
      memory[ofs(r16[bx] + 0x1f48)] = 0;
      if (memory[adr(_ds, r16[bx] + 0x1f3c)] != 0)
      {
        _pc = 0x2518;
        continue;
      };
      if (memory[adr(_ds, r16[bx] + 0x1f3f)] == 0)
        return;
      _si = 0x1e30;
      {
        _pc = 0x2533;
        continue;
      };
    case 0x2518:
      _si = 0x1e50;
      memory[adr(_ds, r16[bx] + 0x1f4d)] += 1;
      if (memory[adr(_ds, r16[bx] + 0x1f4d)] & 1)
      {
        _pc = 0x2529;
        continue;
      };
      _si += 0x20;
    case 0x2529:
      if (memory[adr(_ds, r16[bx] + 0x1f3c)] == 1)
      {
        _pc = 0x2533;
        continue;
      };
      _si += 0x40;
    case 0x2533:
      r8[bl] <<= 1;
      _di = _memoryRead16(0x1F4B);
      _memoryWrite16(ofs(r16[bx] + 0x1f42), _di);
      r16[ax] = 0xb800;
      _es = r16[ax];
      _bp = _memoryRead16(ofs(r16[bx] + 0x1f59));
      r16[cx] = 0x0802;
      yield* sub_2D35();
      return;
  }
}

function* sub_254D()
{
  r16[bx] = _memoryRead16(0x1F6C);
  r8[bl] <<= 1;
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(ofs(r16[bx] + 0x1f42));
  _si = _memoryRead16(ofs(r16[bx] + 0x1f59));
  r16[cx] = 0x0802;
  yield* sub_2D9D();
}

function* sub_2567()
{
  var _pc = 0x2567;
  while (_pc != -1) switch(_pc)
  {
    case 0x2567:
      r16[bx] = _memoryRead16(0x1F6C);
      r8[dl] = memory[ofs(r16[bx] + 0x1f36)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x1f30));
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e08;
      yield* sub_2E29();
      if (flags.carry)
      {
        _pc = 0x258E;
        continue;
      };
      return;
    case 0x258E:
      r16[bx] = _memoryRead16(0x1F6C);
      if (memory[adr(_ds, r16[bx] + 0x1f50)] != 0)
      {
        _pc = 0x260C;
        continue;
      };
      if (memory[adr(_ds, 0x57C)] < 0x26)
      {
        _pc = 0x260C;
        continue;
      };
      if (memory[adr(_ds, 0x55C)] == 0)
      {
        _pc = 0x260E;
        continue;
      };
      memory[0x55C] = 0;
      memory[0x55B] = 0x11;
      memory[0x571] = 1;
      memory[0x56E] = 0;
      r16[bx] = _memoryRead16(0x1F6C);
      r8[bl] <<= 1;
      _di = _memoryRead16(ofs(r16[bx] + 0x1f42));
      if (_memoryRead16(adr(_ds, r16[bx] + 0x1f30)) < 0x10)
      {
        _pc = 0x25CF;
        continue;
      };
      _di -= 0x0004;
    case 0x25CF:
      _memoryWrite16(0x1F67, _di);
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = 0x1d70;
      _bp = 0x0e;
      r16[cx] = 0x0806;
      yield* sub_2CCC();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x1F65, r16[dx]);
      do {
        yield* sub_5A90();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x1F65));
      } while (r16[dx] < 0x0008);
      yield* sub_5B21();
      _di = _memoryRead16(0x1F67);
      _si = 0x0e;
      r16[cx] = 0x0806;
      yield* sub_2D9D();
    case 0x260C:
      flags.carry = true;
      return;
    case 0x260E:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[bx] = _memoryRead16(0x1F6C);
      memory[ofs(r16[bx] + 0x1f50)] = 1;
      memory[ofs(r16[bx] + 0x1f3c)] = 1;
      r8[bl] <<= 1;
      _memoryWrite16(ofs(r16[bx] + 0x1f53), r16[dx]);
      yield* sub_11E3();
      r16[bx] = _memoryRead16(0x1F6C);
      r8[bl] <<= 1;
      _si = _memoryRead16(ofs(r16[bx] + 0x1f5f));
      _di = _memoryRead16(ofs(r16[bx] + 0x1f42));
      r16[ax] = 0xb800;
      _es = r16[ax];
      _bp = 0x0e;
      r16[cx] = 0x0802;
      yield* sub_2CCC();
      yield* sub_1124();
      r16[bx] = _memoryRead16(0x1F6C);
      r8[al] = memory[ofs(r16[bx] + 0x1f39)];
      yield* sub_2706();
      r16[ax] = 0x03e8;
      r16[bx] = 0x02ee;
      yield* sub_593B();
      flags.carry = true;
      return;
  }
}

function* sub_265E()
{
  var _pc = 0x265E;
  while (_pc != -1) switch(_pc)
  {
    case 0x265E:
      if (memory[adr(_ds, 0x1673)] != 0)
      {
        _pc = 0x2667;
        continue;
      };
      flags.carry = false;
      return;
    case 0x2667:
      r16[bx] = _memoryRead16(0x1F6C);
      r8[dl] = memory[ofs(r16[bx] + 0x1f36)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x1f30));
      _si = 0x10;
      _di = _si;
      r16[bx] = _memoryRead16(0x1671);
      r8[dh] = memory[0x1673];
      r16[cx] = 0x0c08;
      yield* sub_2E29();
      return;
  }
}

function* sub_2690()
{
  var _pc = 0x2690;
  while (_pc != -1) switch(_pc)
  {
    case 0x2690:
      _push(_ds);
      _es = _pop();
      r16[cx] = 0x0007;
      _si = 0x1f82;
      do {
        _lodsb_MemData_DirAuto();
        r16[bx] = 0x0007 - r16[cx];
      } while (--r16[cx] && r8[al] == memory[adr(_ds, r16[bx] + 0x1f89)]);
      if (r8[al] > memory[adr(_ds, r16[bx] + 0x1f89)])
      {
        _pc = 0x26A7;
        continue;
      };
      return;
    case 0x26A7:
      _si = 0x1f82;
      _di = 0x1f89;
      r16[cx] = 0x0007;
      _rep_movsb_MemData_MemData_DirAuto();
      return;
  }
}

function* sub_26B3()
{
  var _pc = 0x26B3;
  while (_pc != -1) switch(_pc)
  {
    case 0x26B3:
      r8[al] = memory[0x1F80];
      if (r8[al] != memory[adr(_ds, 0x1F81)])
      {
        _pc = 0x26BD;
        continue;
      };
      return;
    case 0x26BD:
      memory[0x1F81] = r8[al];
      r8[ah] = 0;
      r8[cl] = 0x04;
      r16[ax] = (r16[ax] << r8[cl]) + 0x2720;
      _si = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      _di = 0x1260;
      r16[cx] = 0x0801;
      yield* sub_2D9D();
      return;
  }
}

function* sub_26DA()
{
  _di = 0x1f82;
  yield* sub_26E8();
}

function* sub_26E1()
{
  _di = 0x1f89;
  yield* sub_26E8();
}

function* sub_26E8()
{
  _push(_ds);
  _es = _pop();
  r16[cx] = 0x0007;
  r8[al] = 0;
  _rep_stosb_MemData_DirAuto();
}

function* sub_26F2()
{
  r16[bx] = 0x1f89;
  _di = 0x12ca;
  yield* sub_2739();
}

function* sub_26FC()
{
  r16[bx] = 0x1f82;
  _di = 0x143c;
  yield* sub_2739();
}

function* sub_2706()
{
  r16[cx] = 0x0006;
  do {
    r16[bx] = r16[cx];
    r8[ah] = 0x00;
    flags.carry = (r8[al] + memory[adr(_ds, r16[bx] + 0x1f81)]) >= 0x100;
    r8[al] = r8[al] + memory[adr(_ds, r16[bx] + 0x1f81)];
    _aaa();
    memory[ofs(r16[bx] + 0x1f81)] = r8[al];
    r8[al] = r8[ah];
  } while (--r16[cx]);
  yield* sub_26FC();
}

function* sub_271E()
{
  _push(r16[cx]);
  _push(r16[ax]);
  _push(r16[bx]);
  flags.carry = false;
  _pushf();
  r16[cx] = 0x0007;
  do {
    _popf();
    flags.carry = r16[cx] < 1;
    r16[bx] = r16[cx] - 1;
    r8[al] = _carry8((memory[ofs(r16[bx] + _di)]) + memory[adr(_ds, r16[bx] + _si)] + flags.carry); //
    _aaa();
    memory[ofs(r16[bx] + _di)] = r8[al];
    _pushf();
  } while (--r16[cx]);
  _popf();
  r16[bx] = _pop();
  r16[ax] = _pop();
  r16[cx] = _pop();
}

function* sub_2739()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _memoryWrite16(0x1F90, _di);
  _memoryWrite16(0x1F93, r16[bx]);
  memory[0x1F92] = 0;
  do {
    do {
      r16[bx] = _memoryRead16(0x1F93);
      r8[al] = memory[ofs(r16[bx])];
      r8[ah] = 0;
      r8[cl] = 0x04;
      r16[ax] = (r16[ax] << r8[cl]) + 0x2720;
      _si = r16[ax];
      _di = _memoryRead16(0x1F90);
      r16[cx] = 0x0801;
      yield* sub_2D9D();
      _memoryWrite16(adr(_ds, 0x1F90), _memoryRead16(adr(_ds, 0x1F90)) + 2);
      _memoryWrite16(adr(_ds, 0x1F93), _memoryRead16(adr(_ds, 0x1F93)) + 1);
      memory[adr(_ds, 0x1F92)] += 1;
      if (memory[adr(_ds, 0x1F92)] == 7)
        return;
    } while (memory[adr(_ds, 0x1F92)] != 3);
    _memoryWrite16(adr(_ds, 0x1F90), _memoryRead16(adr(_ds, 0x1F90)) + 2);
  } while (true);
}

function* sub_2790()
{
  var _pc = 0x2790;
  while (_pc != -1) switch(_pc)
  {
    case 0x2790:
      r16[ax] = 0xb800;
      _es = r16[ax];
      if (_memoryRead16(adr(_ds, 0x4)) != 2)
      {
        _pc = 0x27EE;
        continue;
      };
      flags.direction = false;
      _di = 0;
      r16[ax] = 0xaaaa;
      r16[cx] = 0x50;
      _rep_stosw_MemB800_DirForward();
      _di = 0x2000;
      r16[cx] = 0x50;
      _rep_stosw_MemB800_DirForward();
      _memoryWrite16(0x2654, 0);
      do {
        do {
          yield* sub_2DFD();
          r16[dx] &= 0x18;
        } while (r8[dl] == memory[adr(_ds, 0x2653)]);
        memory[0x2653] = r8[dl];
        r16[bx] = _memoryRead16(0x2654);
        memory[ofs(r16[bx] + 0x2656)] = r8[dl];
        r16[dx] += 0x2020;
        _si = r16[dx];
        _di = (r16[bx] << 1) + 0xa0;
        r16[cx] = 0x0401;
        yield* sub_2D9D();
        _memoryWrite16(adr(_ds, 0x2654), _memoryRead16(adr(_ds, 0x2654)) + 1);
      } while (_memoryRead16(adr(_ds, 0x2654)) < 0x28);
      return;
    case 0x27EE:
      if (_memoryRead16(adr(_ds, 0x4)) != 7)
      {
        _pc = 0x27F9;
        continue;
      };
      yield* sub_300F();
      return;
    case 0x27F9:
      if (_memoryRead16(adr(_ds, 0x4)) != 6)
      {
        _pc = 0x283E;
        continue;
      };
      r16[ax] = 0;
      yield* sub_29A0();
      r16[bx] = 0x2570;
      r16[ax] = 0x064a;
      yield* sub_2B24();
      _memoryWrite16(0x2650, 0x48);
      memory[0x2652] = 0x38;
      r16[ax] = 0x0dd2;
      yield* sub_2958();
      r16[ax] = 0x0df6;
      yield* sub_2970();
      _si = 0x1fa0;
      _di = 0x067e;
      r16[cx] = 0x1002;
      yield* sub_2D9D();
      r16[bx] = 0x2344;
      r16[ax] = 0x0b84;
      yield* sub_2B24();
      yield* sub_4B47();
      return;
    case 0x283E:
      if (_memoryRead16(adr(_ds, 0x4)) != 5)
      {
        _pc = 0x288D;
        continue;
      };
      r16[ax] = 0x0640;
      yield* sub_29A0();
      r16[bx] = 0x2570;
      r16[ax] = 0x0cb6;
      yield* sub_2B24();
      _memoryWrite16(0x2650, 0xf8);
      memory[0x2652] = 0x60;
      r16[ax] = 0x140e;
      yield* sub_2958();
      r16[ax] = 0x1434;
      yield* sub_2970();
      r16[ax] = 0x143e;
      yield* sub_2970();
      r16[ax] = 0x16a0;
      yield* sub_2988();
      r16[bx] = 0x2344;
      r16[ax] = 0x1184;
      yield* sub_2B24();
      _si = 0x1fe0;
      _di = 0x0dd6;
      r16[cx] = 0x1002;
      yield* sub_2D9D();
      return;
    case 0x288D:
      if (_memoryRead16(adr(_ds, 0x4)) != 4)
      {
        _pc = 0x28BE;
        continue;
      };
      r16[ax] = 0x0640;
      yield* sub_29A0();
      r16[bx] = 0x2570;
      r16[ax] = 0x0cba;
      yield* sub_2B24();
      _memoryWrite16(0x2650, 264);
      memory[0x2652] = 0x60;
      r16[ax] = 0x1439;
      yield* sub_2958();
      r16[ax] = 0x16c0;
      yield* sub_2945();
      yield* sub_3F9E();
      return;
    case 0x28BE:
      if (_memoryRead16(adr(_ds, 0x4)) != 3)
      {
        _pc = 0x2909;
        continue;
      };
      r16[ax] = 0x0640;
      yield* sub_29A0();
      r16[bx] = 0x2570;
      r16[ax] = 0x0c90;
      yield* sub_2B24();
      _memoryWrite16(0x2650, 0x60);
      memory[0x2652] = 0x60;
      r16[ax] = 0x140c;
      yield* sub_2958();
      r16[ax] = 0x1418;
      yield* sub_2970();
      r16[bx] = 0x2344;
      r16[ax] = 0x1184;
      yield* sub_2B24();
      r16[bx] = 0x2344;
      r16[ax] = 0x11a2;
      yield* sub_2B24();
      r16[bx] = 0x2624;
      r16[ax] = 0;
      yield* sub_2B24();
      yield* sub_3BDB();
      return;
    case 0x2909:
      r16[ax] = 0x0640;
      yield* sub_29A0();
      r16[bx] = 0x2570;
      r16[ax] = 0x0ca0;
      yield* sub_2B24();
      _memoryWrite16(0x2650, 0xa0);
      memory[0x2652] = 0x60;
      r16[ax] = 0x1406;
      yield* sub_2958();
      r16[bx] = 0x2344;
      r16[ax] = 0x11c4;
      yield* sub_2B24();
      r16[ax] = 0x1422;
      yield* sub_2970();
      r16[ax] = 0x1690;
      yield* sub_2988();
      r16[ax] = 0x16b6;
      yield* sub_2945();
      return;
  }
}

function* sub_2945()
{
  _memoryWrite16(0x2634, r16[ax]);
  r16[bx] = 0x2384;
  yield* sub_2B24();
  r16[ax] = _memoryRead16(0x2634);
  r16[bx] = 0x238c;
  yield* sub_2B24();
}

function* sub_2958()
{
  _memoryWrite16(0x2634, r16[ax]);
  _si = 0x0008;
  do {
    r16[ax] = _memoryRead16(0x2634);
    r16[bx] = _memoryRead16(ofs(_si + 0x2634));
    _push(_si);
    yield* sub_2B24();
    _si = _pop();
    _si -= 0x0002;
  } while (_si != 0);
}

function* sub_2970()
{
  _memoryWrite16(0x2634, r16[ax]);
  _si = 0x0a;
  do {
    r16[ax] = _memoryRead16(0x2634);
    r16[bx] = _memoryRead16(ofs(_si + 0x263c));
    _push(_si);
    yield* sub_2B24();
    _si = _pop();
    _si -= 0x0002;
  } while (_si != 0);
}

function* sub_2988()
{
  _memoryWrite16(0x2634, r16[ax]);
  _si = 0x0008;
  do {
    r16[ax] = _memoryRead16(0x2634);
    r16[bx] = _memoryRead16(ofs(_si + 0x2646));
    _push(_si);
    yield* sub_2B24();
    _si = _pop();
    _si -= 0x0002;
  } while (_si != 0);
}

function* sub_29A0()
{
  _memoryWrite16(0x267E, r16[ax]);
  r16[bx] = 0x251c;
  yield* sub_2B24();
  r16[ax] = 0;
  flags.direction = false;
  _di = _memoryRead16(0x267E) + 0x0284;
  r16[cx] = 0x24;
  _rep_stosw_MemB800_DirForward();
  _di = _memoryRead16(0x267E) + 0x1184;
  r16[cx] = 0x24;
  _rep_stosw_MemB800_DirForward();
  _di = _memoryRead16(0x267E) + 0x2284;
  r8[al] = 0x2a;
  yield* sub_29E1();
  _di = _memoryRead16(0x267E) + 0x22cb;
  r8[al] = 0xa8;
  yield* sub_29E1();
}

function* sub_29E1()
{
  var _pc = 0x29E1;
  while (_pc != -1) switch(_pc)
  {
    case 0x29E1:
      r16[cx] = 0x5f;
    case 0x29E4:
      _videoWrite8(0xb800, _di, r8[al]);
      _di = _di ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x29F4;
        continue;
      };
      _di += 0x50;
    case 0x29F4:
      if (--r16[cx])
      {
        _pc = 0x29E4;
        continue;
      };
      return;
  }
}

function* sub_2A00()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  flags.direction = false;
  _di = 0;
  r16[ax] = 0xaaaa;
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
  _di = 0x2000;
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
  yield* sub_2B9E();
  r16[bx] = 0x28a0;
  r16[ax] = 0;
  yield* sub_2B24();
  yield* sub_2A68();
  yield* sub_2C84();
  yield* sub_2B8B();
  yield* sub_2A80();
}

function* sub_2A30()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  flags.direction = false;
  _di = 0;
  r16[ax] = 0xaaaa;
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
  _di = 0x2000;
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
  yield* sub_2B9E();
  r16[bx] = 0x28a0;
  r16[ax] = 0;
  yield* sub_2B24();
  yield* sub_2A68();
  r16[ax] = _memoryRead16(0x8);
  _push(r16[ax]);
  _memoryWrite16(0x8, 1);
  yield* sub_2C84();
  r16[ax] = _pop();
  _memoryWrite16(0x8, r16[ax]);
}

function* sub_2A68()
{
  r16[bx] = _memoryRead16(0x6DF8) & 0x0003;
  r8[bl] <<= 1;
  _si = _memoryRead16(ofs(r16[bx] + 0x2ad1));
  _di = 0x1902;
  r16[cx] = 0x0801;
  yield* sub_2D9D();
}

function* sub_2A80()
{
  r16[bx] = 0x0f;
  do {
    memory[ofs(r16[bx] + 0x1015)] = 0;
    r16[bx] -= 1;
  } while (r16[bx] != 0);
  _di = 0x0140;
  r8[bh] = 0x80;
  _memoryWrite16(0x2ACA, 0);
  yield* sub_2AC6();
  _di = 0x0640;
  r8[bh] = 0x30;
  _memoryWrite16(0x2ACA, 5);
  yield* sub_2AC6();
  _di = 0x0b40;
  r8[bh] = 0x00;
  _memoryWrite16(0x2ACA, 0x0a);
  yield* sub_2AC6();
  memory[0x525] = 0x10;
  _memoryWrite16(0x52F, 0);
  memory[0x531] = 1;
}

function* sub_2AC6()
{
  memory[0x2AC9] = r8[bh];
  memory[0x2AC4] = 0;
  do {
    _push(_di);
    _push(_es);
    r16[bx] = _memoryRead16(0x8);
    r8[bl] = memory[ofs(r16[bx] + 0x2aba)];
    r8[bh] = memory[0x2AC9];
    r16[ax] = SEG_DATA;
    _es = r16[ax];
    _di = 0x04d7;
    yield* sub_67D();
    _es = _pop();
    _di = _pop();
    _push(_di);
    _si = 0x04d7;
    r16[cx] = 0x1002;
    yield* sub_2D9D();
    r8[bh] = 0;
    r8[bl] = memory[0x2AC4];
    r8[cl] = r8[bl];
    r8[bl] >>= 2;
    r8[cl] = ((~r8[cl]) & 0x03) << 1;
    r8[al] = memory[0x540] << r8[cl];
    _si = _memoryRead16(0x2ACA);
    memory[adr(_ds, r16[bx] + _si + 4118)] |= r8[al];
    _di = _pop();
    _di += 0x0004;
    memory[adr(_ds, 0x2AC4)] += 1;
  } while (memory[adr(_ds, 0x2AC4)] < 0x14);
}

function* sub_2B24()
{
  var _pc = 0x2B24;
  while (_pc != -1) switch(_pc)
  {
    case 0x2B24:
      r16[cx] = _memoryRead16(ofs(r16[bx]));
      _memoryWrite16(0x2AC7, r16[cx]);
      _memoryWrite16(0x2ACC, r16[ax]);
      r16[bx] += 0x0002;
    case 0x2B30:
      _si = _memoryRead16(ofs(r16[bx]));
      if (_si != 0xffff)
      {
        _pc = 0x2B39;
        continue;
      };
      return;
    case 0x2B39:
      _di = (_memoryRead16(ofs(r16[bx] + 0x2))) + _memoryRead16(adr(_ds, 0x2ACC));
      flags.direction = false;
      memory[0x2AD0] = r8[ch];
      r8[ch] = 0;
      _memoryWrite16(0x2ACE, r16[cx]);
    case 0x2B4B:
      r16[cx] = _memoryRead16(0x2ACE);
      _rep_movsb_MemB800_MemData_DirForward();
      _di = (_di - _memoryRead16(adr(_ds, 0x2ACE))) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x2B62;
        continue;
      };
      _di += 0x50;
    case 0x2B62:
      memory[adr(_ds, 0x2AD0)] -= 1;
      if (memory[adr(_ds, 0x2AD0)] != 0)
      {
        _pc = 0x2B4B;
        continue;
      };
      r16[bx] += 0x0004;
      r16[cx] = _memoryRead16(0x2AC7);
      {
        _pc = 0x2B30;
        continue;
      };
      return;
  }
}

function* sub_2B71()
{
  memory[0x2AC4] = 4;
  do {
    _si = 0x2680;
    r16[cx] = 0x1005;
    _push(_di);
    yield* sub_2D9D();
    _di = _pop();
    _di += 0x14;
    memory[adr(_ds, 0x2AC4)] -= 1;
  } while (memory[adr(_ds, 0x2AC4)] != 0);
}

function* sub_2B8B()
{
  _di = 0x03c5;
  yield* sub_2B71();
  _di = 0x08c5;
  yield* sub_2B71();
  _di = 0x0dc5;
  yield* sub_2B71();
}

function* sub_2B9E()
{
  var _pc = 0x2B9E;
  while (_pc != -1) switch(_pc)
  {
    case 0x2B9E:
      _memoryWrite16(0x2AC2, 4158);
    case 0x2BA4:
      _memoryWrite16(adr(_ds, 0x2AC2), _memoryRead16(adr(_ds, 0x2AC2)) + 2);
      _di = _memoryRead16(0x2AC2);
      if (_di >= 0x1090)
      {
        _pc = 0x2BD2;
        continue;
      };
      do {
        yield* sub_2DFD();
        r16[dx] &= 0x30;
      } while (r8[dl] == memory[adr(_ds, 0x2AC4)]);
      memory[0x2AC4] = r8[dl];
      r16[dx] += 0x2904;
      _si = r16[dx];
      r16[cx] = 0x0801;
      yield* sub_2D9D();
      {
        _pc = 0x2BA4;
        continue;
      };
    case 0x2BD2:
      _di = 0x1180;
      r16[ax] = 0x5655;
      r16[cx] = 0x0500;
      flags.direction = false;
      _rep_stosw_MemB800_DirForward();
      _di = 0x3180;
      r16[cx] = 0x0500;
      _rep_stosw_MemB800_DirForward();
      _memoryWrite16(0x2AC2, 10564);
      do {
        memory[0x2AC4] = 9;
        do {
          yield* sub_2DFD();
          r16[dx] = (r16[dx] & 0x0776) + 0x12c0;
          _di = r16[dx];
          _si = _memoryRead16(0x2AC2);
          r16[cx] = 0x0501;
          yield* sub_2D9D();
          memory[adr(_ds, 0x2AC4)] -= 1;
        } while (memory[adr(_ds, 0x2AC4)] != 0);
        _memoryWrite16(adr(_ds, 0x2AC2), _memoryRead16(adr(_ds, 0x2AC2)) + 0x0a);
      } while (_memoryRead16(adr(_ds, 0x2AC2)) < 10604);
      memory[0x2AC4] = 5;
      do {
        yield* sub_2DFD();
        r16[dx] = (r16[dx] & 0x3e) + 0x3a98;
        _di = r16[dx];
        _si = 0x296c;
        r16[cx] = 0x0501;
        yield* sub_2D9D();
        memory[adr(_ds, 0x2AC4)] -= 1;
      } while (memory[adr(_ds, 0x2AC4)] != 0);
      return;
  }
}

function* sub_2C3D()
{
  var _pc = 0x2C3D;
  while (_pc != -1) switch(_pc)
  {
    case 0x2C3D:
      _memoryWrite16(0x2AC2, _di);
      r8[al] = 0x03;
      if (_di < 0x1720)
      {
        _pc = 0x2C4B;
        continue;
      };
      r8[al] -= 1;
    case 0x2C4B:
      memory[0x2AC4] = r8[al];
      _memoryWrite16(adr(_ds, 0x2AC2), _memoryRead16(adr(_ds, 0x2AC2)) + 480);
      _si = 0x2976;
      r16[cx] = 0x0c05;
      yield* sub_2D9D();
      do {
        _di = _memoryRead16(0x2AC2);
        _memoryWrite16(adr(_ds, 0x2AC2), _memoryRead16(adr(_ds, 0x2AC2)) + 320);
        _si = 0x29ee;
        r16[cx] = 0x0804;
        yield* sub_2D9D();
        memory[adr(_ds, 0x2AC4)] -= 1;
      } while (memory[adr(_ds, 0x2AC4)] != 0);
      _di = _memoryRead16(0x2AC2);
      _si = 0x2a2e;
      r16[cx] = 0x0b04;
      yield* sub_2D9D();
      return;
  }
}

function* sub_2C84()
{
  var _pc = 0x2C84;
  while (_pc != -1) switch(_pc)
  {
    case 0x2C84:
      r16[bx] = _memoryRead16(0x8);
      r8[bl] = memory[ofs(r16[bx] + 0x2ab2)];
    case 0x2C8C:
      _memoryWrite16(0x2AC5, r16[bx]);
      _di = _memoryRead16(ofs(r16[bx] + 0x2a86));
      if (_di != 0x0000)
      {
        _pc = 0x2C9A;
        continue;
      };
      return;
    case 0x2C9A:
      yield* sub_2C3D();
      r16[bx] = _memoryRead16(0x2AC5) + 0x0002;
      {
        _pc = 0x2C8C;
        continue;
      };
      return;
  }
}

// class CIReturn
function* sub_2CB0()
{
  var _pc = 0x2CB0;
  while (_pc != -1) switch(_pc)
  {
    case 0x2CB0:
      r8[al] = r8[dl];
      r8[ah] = 0x28;
      r16[ax] = r8[ah] * r8[al];
      if (!(r8[dl] & 0x01))
      {
        _pc = 0x2CBE;
        continue;
      };
      r16[ax] += 0x1fd8;
    case 0x2CBE:
      r16[dx] = r16[cx] >> 2;
      r16[ax] += r16[dx];
      r8[cl] = (r8[cl] & 0x03) << 1;
      return;
  }
}

function* sub_2CCC()
{
  var _pc = 0x2CCC;
  while (_pc != -1) switch(_pc)
  {
    case 0x2CCC:
      flags.direction = false;
      memory[0x2AE0] = r8[cl];
      memory[0x2AE2] = r8[ch];
      r8[ch] = 0;
      r16[dx] = 0x0ff0;
    case 0x2CDA:
      r8[cl] = memory[0x2AE0];
    case 0x2CDE:
      r16[dx] = 0x30c0;
      r16[bx] = _videoRead16(_esAssume(0xb800), _di);
      _memoryWrite16(ofs(_bp + 0), r16[bx]);
      _lodsw_MemData_DirForward();
      _memoryWrite16(0x2AE3, r16[ax]);
    case 0x2CEC:
      if (r8[ah] & r8[dl])
      {
        _pc = 0x2CF2;
        continue;
      };
      r8[ah] |= r8[dl];
    case 0x2CF2:
      if (r8[ah] & r8[dh])
      {
        _pc = 0x2CF8;
        continue;
      };
      r8[ah] |= r8[dh];
    case 0x2CF8:
      if (r8[al] & r8[dl])
      {
        _pc = 0x2CFE;
        continue;
      };
      r8[al] |= r8[dl];
    case 0x2CFE:
      if (r8[al] & r8[dh])
      {
        _pc = 0x2D04;
        continue;
      };
      r8[al] |= r8[dh];
    case 0x2D04:
      r16[dx] = r16[dx] ^ 0x33cc;
      if (r8[dh] & 0x03)
      {
        _pc = 0x2CEC;
        continue;
      };
      r16[ax] = (r16[ax] & r16[bx]) | _memoryRead16(adr(_ds, 0x2AE3));
      _stosw_MemB800_DirForward();
      _bp += 0x0002;
      if (--r16[cx])
      {
        _pc = 0x2CDE;
        continue;
      };
      _di = ((_di - _memoryRead16(adr(_ds, 0x2AE0))) - _memoryRead16(adr(_ds, 0x2AE0))) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x2D2E;
        continue;
      };
      _di += 0x50;
    case 0x2D2E:
      memory[adr(_ds, 0x2AE2)] -= 1;
      if (memory[adr(_ds, 0x2AE2)] != 0)
      {
        _pc = 0x2CDA;
        continue;
      };
      return;
  }
}

function* sub_2D35()
{
  var _pc = 0x2D35;
  while (_pc != -1) switch(_pc)
  {
    case 0x2D35:
      flags.direction = false;
      memory[0x2AE0] = r8[cl];
      memory[0x2AE2] = r8[ch];
      r8[ch] = 0;
    case 0x2D40:
      r8[cl] = memory[0x2AE0];
      do {
        r16[bx] = _videoRead16(_esAssume(0xb800), _di);
        _memoryWrite16(ofs(_bp + 0), r16[bx]);
        _lodsw_MemData_DirForward();
        r16[ax] &= r16[bx];
        _stosw_MemB800_DirForward();
        _bp += 0x0002;
      } while (--r16[cx]);
      _di = ((_di - _memoryRead16(adr(_ds, 0x2AE0))) - _memoryRead16(adr(_ds, 0x2AE0))) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x2D69;
        continue;
      };
      _di += 0x50;
    case 0x2D69:
      memory[adr(_ds, 0x2AE2)] -= 1;
      if (memory[adr(_ds, 0x2AE2)] != 0)
      {
        _pc = 0x2D40;
        continue;
      };
      return;
  }
}

function* sub_2D70()
{
  flags.direction = false;
  _memoryWrite16(0x2AE9, _si);
  memory[0x2AE0] = r8[cl];
  memory[0x2AE2] = r8[ch];
  r8[al] <<= 1;
  memory[0x2AEB] = r8[al];
  r8[ch] = 0;
  do {
    r8[cl] = memory[0x2AE0];
    _rep_movsw_MemData_MemData_DirForward();
    r8[cl] = memory[0x2AEB];
    _memoryWrite16(adr(_ds, 0x2AE9), _memoryRead16(adr(_ds, 0x2AE9)) + r16[cx]);
    _si = _memoryRead16(0x2AE9);
    memory[adr(_ds, 0x2AE2)] -= 1;
  } while (memory[adr(_ds, 0x2AE2)] != 0);
}

function* sub_2D9D()
{
  var _pc = 0x2D9D;
  while (_pc != -1) switch(_pc)
  {
    case 0x2D9D:
      flags.direction = false;
      memory[0x2AE0] = r8[cl];
      memory[0x2AE2] = r8[ch];
      r8[ch] = 0;
    case 0x2DA8:
      r8[cl] = memory[0x2AE0];
      _rep_movsw_MemB800_MemData_DirForward();
      _di = ((_di - _memoryRead16(adr(_ds, 0x2AE0))) - _memoryRead16(adr(_ds, 0x2AE0))) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x2DC3;
        continue;
      };
      _di += 0x50;
    case 0x2DC3:
      memory[adr(_ds, 0x2AE2)] -= 1;
      if (memory[adr(_ds, 0x2AE2)] != 0)
      {
        _pc = 0x2DA8;
        continue;
      };
      return;
  }
}

function* sub_2DCA()
{
  var _pc = 0x2DCA;
  while (_pc != -1) switch(_pc)
  {
    case 0x2DCA:
      flags.direction = false;
      memory[adr(_es, 10976)] = r8[cl];
      memory[adr(_es, 10978)] = r8[ch];
      r8[ch] = 0;
    case 0x2DD7:
      r8[cl] = memory[adr(_es, 10976)];
      _rep_movsw_MemData_MemB800_DirForward();
      _si = ((_si - _memoryRead16(adr(_es, 10976))) - _memoryRead16(adr(_es, 10976))) ^ 0x2000;
      if (_si & 0x2000)
      {
        _pc = 0x2DF5;
        continue;
      };
      _si += 0x50;
    case 0x2DF5:
      memory[adr(_es, 10978)] -= 1;
      if (memory[adr(_es, 10978)] != 0)
      {
        _pc = 0x2DD7;
        continue;
      };
      return;
  }
}

function* sub_2DFD()
{
  r16[dx] = _memoryRead16(0x2AE5);
  r8[dl] = (r8[dl] ^ r8[dh]) >> 1;
  flags.carry = r8[dl] & 1;
  r8[dl] = (r8[dl] ^ r8[dh]) >> 1;
  _memoryWrite16(adr(_ds, 0x2AE5), _rcr16(_memoryRead16(adr(_ds, 0x2AE5)), 1)); //TODO! // TODO rcr16
  r16[dx] = _memoryRead16(0x2AE5);
}

function* sub_2E10()
{
  var _pc = 0x2E10;
  while (_pc != -1) switch(_pc)
  {
    case 0x2E10:
      r8[al] = 0x00;
      _out(0x43, r8[al]);
      r8[al] = _in(0x40);
      r8[ah] = r8[al];
      r8[al] = _in(0x40);
      if (r16[ax] != 0x0000)
      {
        _pc = 0x2E25;
        continue;
      };
      r16[ax] = 0xfa59;
    case 0x2E25:
      _memoryWrite16(0x2AE5, r16[ax]);
      return;
  }
}

function* sub_2E29()
{
  var _pc = 0x2E29;
  while (_pc != -1) switch(_pc)
  {
    case 0x2E29:
      r16[ax] += _si;
      if (r16[ax] < r16[bx])
      {
        _pc = 0x2E4F;
        continue;
      };
      r16[ax] -= _si;
      flags.carry = r16[ax] < _di;
      r16[ax] -= _di;
      if (!flags.carry)
      {
        _pc = 0x2E37;
        continue;
      };
      r16[ax] = 0;
    case 0x2E37:
      if (r16[ax] > r16[bx])
      {
        _pc = 0x2E4F;
        continue;
      };
      r8[dl] += r8[cl];
      if (r8[dl] < r8[dh])
      {
        _pc = 0x2E4F;
        continue;
      };
      r8[dl] -= r8[cl];
      flags.carry = r8[dl] < r8[ch];
      r8[dl] -= r8[ch];
      if (!flags.carry)
      {
        _pc = 0x2E49;
        continue;
      };
      r8[dl] = 0;
    case 0x2E49:
      if (r8[dl] > r8[dh])
      {
        _pc = 0x2E4F;
        continue;
      };
      flags.carry = true;
      return;
    case 0x2E4F:
      flags.carry = false;
      return;
  }
}

function* sub_2E60()
{
  var _pc = 0x2E60;
  while (_pc != -1) switch(_pc)
  {
    case 0x2E60:
      if (_memoryRead16(adr(_ds, 0x2E8D)) < 8)
      {
        _pc = 0x2E68;
        continue;
      };
      return;
    case 0x2E68:
      if (memory[adr(_ds, 0x69A)] != 0)
        return;
      _memoryWrite16(0x2E92, 0xffff);
      memory[0x2E91] = 0xff;
      r16[cx] = 0x0007;
    case 0x2E7D:
      r16[bx] = r16[cx] - 1;
      r8[al] = memory[0x57B];
      flags.carry = r8[al] < memory[adr(_ds, r16[bx] + 0x2bd4)];
      r8[al] = r8[al] - memory[adr(_ds, r16[bx] + 0x2bd4)];
      if (!flags.carry)
      {
        _pc = 0x2E8B;
        continue;
      };
      r8[al] = (~r8[al]);
    case 0x2E8B:
      if (r8[al] > memory[adr(_ds, 0x2E91)])
      {
        _pc = 0x2E98;
        continue;
      };
      memory[0x2E91] = r8[al];
      _memoryWrite16(0x2E92, r16[bx]);
    case 0x2E98:
      if (--r16[cx])
      {
        _pc = 0x2E7D;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x2E92)) != 0xffff)
      {
        _pc = 0x2EA8;
        continue;
      };
      _memoryWrite16(0x2E92, 0);
    case 0x2EA8:
      r16[bx] = _memoryRead16(0x2E8D);
      _si = _memoryRead16(0x2E92);
      r8[al] = memory[ofs(_si + 0x2bd4)];
      memory[ofs(r16[bx] + 0x2b6a)] = r8[al];
      memory[0x2E98] = r8[al];
      r16[ax] = _memoryRead16(0x579);
      r8[bl] <<= 1;
      if (r16[ax] < 0x0108)
      {
        _pc = 0x2EC8;
        continue;
      };
      r16[ax] = 0x0107;
    case 0x2EC8:
      r16[ax] &= 0x0ffc;
      _memoryWrite16(ofs(r16[bx] + 0x2b5a), r16[ax]);
      _memoryWrite16(0x2E96, r16[ax]);
      r16[cx] = 0x0008;
    case 0x2ED5:
      r16[bx] = r16[cx] - 1;
      if (r16[bx] == _memoryRead16(adr(_ds, 0x2E8D)))
      {
        _pc = 0x2F07;
        continue;
      };
      if (memory[adr(_ds, r16[bx] + 0x2b72)] == 0)
      {
        _pc = 0x2F07;
        continue;
      };
      _push(r16[cx]);
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      r16[bx] = _memoryRead16(0x2E96);
      r8[dh] = memory[0x2E98];
      _si = 0x18;
      _di = _si;
      r16[cx] = 0x0f0f;
      yield* sub_2E29();
      r16[cx] = _pop();
      if (!flags.carry)
      {
        _pc = 0x2F07;
        continue;
      };
      return;
    case 0x2F07:
      if (--r16[cx])
      {
        _pc = 0x2ED5;
        continue;
      };
      yield* sub_11E3();
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x2F16;
        continue;
      };
      yield* sub_622B();
    case 0x2F16:
      r16[bx] = _memoryRead16(0x2E8D);
      _memoryWrite16(0x2E94, r16[bx]);
      memory[ofs(r16[bx] + 0x2b72)] = 1;
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      yield* sub_2CB0();
      _di = r16[ax];
      _si = 0x2af0;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0f03;
      yield* sub_2D9D();
      _memoryWrite16(0x2E8D, 0xffff);
      r16[bx] = 0;
      r8[ah] = 0x0b;
      _interrupt(0x10);
      yield* sub_4E3E();
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x2F59;
        continue;
      };
      yield* sub_61FA();
    case 0x2F59:
      yield* sub_1145();
      r16[ax] = 0x03e8;
      r16[bx] = 0x04a5;
      yield* sub_593B();
      return;
  }
}

function* sub_2F66()
{
  var _pc = 0x2F66;
  while (_pc != -1) switch(_pc)
  {
    case 0x2F66:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x2E8F)))
      {
        _pc = 0x2F71;
        continue;
      };
      return;
    case 0x2F71:
      _memoryWrite16(0x2E8F, r16[dx]);
      if (_memoryRead16(adr(_ds, 0x2E8D)) < 8)
      {
        _pc = 0x2FAC;
        continue;
      };
      r16[cx] = 0x0008;
    case 0x2F7F:
      r16[bx] = r16[cx] - 1;
      if (memory[adr(_ds, r16[bx] + 0x2b72)] == 0)
      {
        _pc = 0x2FAA;
        continue;
      };
      _push(r16[cx]);
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      _si = 0x18;
      _di = _si;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      r16[cx] = 0x0e0f;
      yield* sub_2E29();
      r16[cx] = _pop();
      if (flags.carry)
      {
        _pc = 0x2FB3;
        continue;
      };
    case 0x2FAA:
      if (--r16[cx])
      {
        _pc = 0x2F7F;
        continue;
      };
    case 0x2FAC:
      _memoryWrite16(0x2E94, 0xffff);
      return;
    case 0x2FB3:
      r16[bx] = r16[cx] - 1;
      if (r16[bx] == _memoryRead16(adr(_ds, 0x2E94)))
        return;
      _push(r16[bx]);
      yield* sub_11E3();
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x2FCA;
        continue;
      };
      yield* sub_622B();
    case 0x2FCA:
      r16[bx] = _pop();
      memory[ofs(r16[bx] + 0x2b72)] = 0;
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      _memoryWrite16(0x2E8D, r16[bx]);
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      yield* sub_2CB0();
      _di = r16[ax];
      _si = 0x2b7a;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0f03;
      yield* sub_2D9D();
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x2FFB;
        continue;
      };
      yield* sub_61FA();
    case 0x2FFB:
      yield* sub_1145();
      r16[bx] = 0x0001;
      r8[ah] = 0x0b;
      _interrupt(0x10);
      r16[ax] = 0x03e8;
      r16[bx] = 0x0349;
      yield* sub_593B();
      return;
  }
}

function* sub_300F()
{
  var _pc = 0x300F;
  while (_pc != -1) switch(_pc)
  {
    case 0x300F:
      r16[ax] = 0;
      r16[bx] = 0x2e24;
      yield* sub_2B24();
      memory[0x2E8A] = 0xbf;
      _memoryWrite16(0x2E8B, 0);
    case 0x3022:
      _memoryWrite16(0x2E88, 0x20);
    case 0x3028:
      r16[bx] = 0;
      if (memory[adr(_ds, 0x2E8A)] == 0xbf)
      {
        _pc = 0x3039;
        continue;
      };
      yield* sub_2DFD();
      r8[bl] = r8[dl] & 0x02;
    case 0x3039:
      r16[cx] = _memoryRead16(0x2E88);
      r8[dl] = memory[0x2E8A];
      _push(r16[bx]);
      yield* sub_30E3();
      r16[bx] = _pop();
      _si = _memoryRead16(0x2E8B);
      r16[ax] = _memoryRead16(0x2E88);
      r8[cl] = 0x04;
      r16[ax] >>= r8[cl];
      flags.carry = r16[ax] < 0x0002;
      r16[ax] -= 0x0002;
      if (!flags.carry)
      {
        _pc = 0x3058;
        continue;
      };
      r16[ax] = 0;
    case 0x3058:
      if (r16[ax] < 0x12)
      {
        _pc = 0x3060;
        continue;
      };
      r16[ax] = 0x11;
    case 0x3060:
      r8[dl] = memory[ofs(_si + 0x2bdb)];
      r8[dh] = 0;
      r16[ax] += r16[dx];
      _si = r16[ax];
      memory[ofs(_si + 0x2be2)] = r8[bl];
      _memoryWrite16(adr(_ds, 0x2E88), _memoryRead16(adr(_ds, 0x2E88)) + 0x10);
      if (_memoryRead16(adr(_ds, 0x2E88)) < 273)
      {
        _pc = 0x3028;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x2E8B), _memoryRead16(adr(_ds, 0x2E8B)) + 1);
      memory[adr(_ds, 0x2E8A)] -= 0x18;
      if (memory[adr(_ds, 0x2E8A)] >= 0x2f)
      {
        _pc = 0x3022;
        continue;
      };
      r16[ax] = 0xffff;
      _memoryWrite16(0x2E8D, r16[ax]);
      _memoryWrite16(0x2E94, r16[ax]);
      r16[ax] = 0;
      _memoryWrite16(0x2B72, r16[ax]);
      _memoryWrite16(0x2B74, r16[ax]);
      _memoryWrite16(0x2B76, r16[ax]);
      _memoryWrite16(0x2B78, r16[ax]);
      r16[cx] = _memoryRead16(0x414);
      if (r16[cx] != 0x0000)
      {
        _pc = 0x30B0;
        continue;
      };
      r16[cx] += 1;
      _memoryWrite16(0x414, r16[cx]);
    case 0x30B0:
      if (r16[cx] <= 0x0008)
      {
        _pc = 0x30B8;
        continue;
      };
      r16[cx] = 0x0008;
    case 0x30B8:
      do {
        r16[bx] = r16[cx] - 1;
        memory[ofs(r16[bx] + 0x2b72)] = 1;
        r8[dl] = 0xb0;
        memory[ofs(r16[bx] + 0x2b6a)] = r8[dl];
        _push(r16[cx]);
        r8[bl] <<= 1;
        r16[cx] = _memoryRead16(ofs(r16[bx] + 0x2b4a));
        _memoryWrite16(ofs(r16[bx] + 0x2b5a), r16[cx]);
        yield* sub_2CB0();
        _di = r16[ax];
        _si = 0x2af0;
        r16[cx] = 0x0f03;
        yield* sub_2D9D();
        r16[cx] = _pop();
      } while (--r16[cx]);
      return;
  }
}

function* sub_30E3()
{
  _push(r16[bx]);
  yield* sub_2CB0();
  _di = r16[ax];
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[bx] = _pop();
  _si = _memoryRead16(ofs(r16[bx] + 0x2e20));
  r16[cx] = 0x0802;
  yield* sub_2D9D();
}

function* sub_30FA()
{
  var _pc = 0x30FA;
  while (_pc != -1) switch(_pc)
  {
    case 0x30FA:
      r8[al] = (memory[0x57B] - 0x05) & 0xf8;
      r16[cx] = 0x0007;
    case 0x3104:
      r16[bx] = r16[cx] - 1;
      if (r8[al] == memory[adr(_ds, r16[bx] + 0x2bd4)])
      {
        _pc = 0x3111;
        continue;
      };
      if (--r16[cx])
      {
        _pc = 0x3104;
        continue;
      };
      {
        _pc = 0x314D;
        continue;
      };
    case 0x3111:
      r8[ch] = r8[al];
      r16[ax] = _memoryRead16(0x579) + 0x0007;
      r8[cl] = 0x04;
      r16[ax] >>= r8[cl];
      flags.carry = r16[ax] < 0x0002;
      r16[ax] -= 0x0002;
      if (!flags.carry)
      {
        _pc = 0x3124;
        continue;
      };
      r16[ax] = 0;
    case 0x3124:
      if (r16[ax] < 0x12)
      {
        _pc = 0x312C;
        continue;
      };
      r16[ax] = 0x11;
    case 0x312C:
      r8[dl] = memory[ofs(r16[bx] + 0x2bdb)];
      r8[dh] = 0;
      r16[ax] += r16[dx];
      _si = r16[ax];
      if (memory[adr(_ds, _si + 0x2be2)] != 0)
      {
        _pc = 0x314D;
        continue;
      };
      r8[ch] += 0x05;
      memory[0x57B] = r8[ch];
      r8[ch] += 0x32;
      memory[0x57C] = r8[ch];
      flags.carry = true;
      return;
    case 0x314D:
      flags.carry = false;
      return;
  }
}

function* sub_3150()
{
  var _pc = 0x3150;
  while (_pc != -1) switch(_pc)
  {
    case 0x3150:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[bx] = _memoryRead16(0x4);
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x32f2));
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x328C));
      if (r16[ax] >= r16[cx])
      {
        _pc = 0x3169;
        continue;
      };
      return;
    case 0x3169:
      _memoryWrite16(0x328C, r16[dx]);
      yield* sub_33BA();
      if (flags.carry)
        return;
      yield* sub_21E0();
      if (flags.carry)
        return;
      memory[adr(_ds, 0x32EA)] += 1;
      yield* sub_2DFD();
      r8[al] = memory[0x32EA] & r8[dl];
      memory[adr(_ds, 0x32EB)] = memory[adr(_ds, 0x32EB)] ^ r8[al];
      r16[ax] = _memoryRead16(0x327D);
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x579));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x579));
      r8[dl] = 0xff;
      if (!flags.carry)
      {
        _pc = 0x3196;
        continue;
      };
      r16[ax] = (~r16[ax]);
      r8[dl] = 0x01;
    case 0x3196:
      memory[0x32ED] = r8[dl];
      r8[bl] = memory[0x327F] + 0x14;
      flags.carry = r8[bl] < memory[adr(_ds, 0x57B)];
      r8[bl] = r8[bl] - memory[adr(_ds, 0x57B)];
      r8[dl] = 0xff;
      if (!flags.carry)
      {
        _pc = 0x31AD;
        continue;
      };
      r8[bl] = (~r8[bl]);
      r8[dl] = 0x01;
    case 0x31AD:
      memory[0x32EE] = r8[dl];
      r16[ax] >>= 2;
      r8[bl] >>= 1;
      r8[al] += r8[bl];
      memory[0x32EC] = r8[al];
      r16[bx] = _memoryRead16(0x328A);
      if (r16[bx] < 0x27)
      {
        _pc = 0x31CC;
        continue;
      };
      r16[bx] = 0x26;
      _memoryWrite16(0x328A, r16[bx]);
    case 0x31CC:
      if (memory[adr(_ds, r16[bx] + 0x328e)] != 0)
      {
        _pc = 0x324B;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x328A), _memoryRead16(adr(_ds, 0x328A)) - 1);
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x410));
      r8[cl] = 0x03;
      r16[dx] >>= r8[cl];
      r8[al] = memory[0x32EC];
      flags.carry = r8[al] < r8[dl];
      r8[al] -= r8[dl];
      if (!flags.carry)
      {
        _pc = 0x31EC;
        continue;
      };
      r8[al] = 0;
    case 0x31EC:
      if (r8[al] < memory[adr(_ds, 0x32EB)])
      {
        _pc = 0x3212;
        continue;
      };
      memory[0x3281] = 1;
      yield* sub_2DFD();
      if (r8[dl] == 0x00)
      {
        _pc = 0x320B;
        continue;
      };
      if (r8[dl] > 0x07)
      {
        _pc = 0x32AC;
        continue;
      };
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x320B;
        continue;
      };
      r8[dl] = 0xff;
    case 0x320B:
      memory[0x3280] = r8[dl];
      {
        _pc = 0x32AC;
        continue;
      };
    case 0x3212:
      r8[al] = memory[0x32EB] & 0x2f;
      if (r8[al] != 0)
      {
        _pc = 0x3238;
        continue;
      };
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x3223;
        continue;
      };
      r8[dl] = 0xff;
    case 0x3223:
      memory[0x3280] = r8[dl];
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x3231;
        continue;
      };
      r8[dl] = 0xff;
    case 0x3231:
      memory[0x3281] = r8[dl];
      {
        _pc = 0x32AC;
        continue;
      };
    case 0x3238:
      r8[al] &= 0x07;
      if (r8[al] != 0)
      {
        _pc = 0x32AC;
        continue;
      };
      r8[al] = memory[0x32ED];
      memory[0x3280] = r8[al];
      r8[al] = memory[0x32EE];
      memory[0x3281] = r8[al];
      {
        _pc = 0x32AC;
        continue;
      };
    case 0x324B:
      memory[0x3281] = 1;
      r16[ax] = r16[bx];
      r8[cl] = 0x03;
      r16[ax] <<= r8[cl];
      if (_memoryRead16(adr(_ds, 0x327D)) == r16[ax])
      {
        _pc = 0x3269;
        continue;
      };
      r8[dl] = 0x01;
      if (_memoryRead16(adr(_ds, 0x327D)) < r16[ax])
      {
        _pc = 0x3262;
        continue;
      };
      r8[dl] = 0xff;
    case 0x3262:
      memory[0x3280] = r8[dl];
      {
        _pc = 0x32AC;
        continue;
      };
    case 0x3269:
      memory[0x3280] = 0;
      if (memory[adr(_ds, 0x327F)] != 0xa5)
      {
        _pc = 0x32AC;
        continue;
      };
      memory[0x3281] = 0;
      if (_memoryRead16(adr(_ds, 0x327A)) == 6)
      {
        _pc = 0x3288;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x327A)) != 0x12)
      {
        _pc = 0x32AC;
        continue;
      };
    case 0x3288:
      _push(r16[bx]);
      _si = 0x31e8;
      _di = _memoryRead16(0x3282);
      r16[cx] = 0x1e02;
      r16[ax] = 0xb800;
      _es = r16[ax];
      yield* sub_2D9D();
      r16[bx] = _pop();
      memory[adr(_ds, r16[bx] + 0x328e)] -= 1;
      r8[al] = memory[ofs(r16[bx] + 0x328e)];
      yield* sub_347F();
      memory[0x3286] = 1;
    case 0x32AC:
      r16[cx] = _memoryRead16(0x327D);
      r8[dl] = memory[0x327F];
      _memoryWrite16(0x32EF, r16[cx]);
      memory[0x32F1] = r8[dl];
      if (memory[adr(_ds, 0x3280)] < 1)
      {
        _pc = 0x32DA;
        continue;
      };
      if (memory[adr(_ds, 0x3280)] != 1)
      {
        _pc = 0x32D3;
        continue;
      };
      r16[cx] += 0x0008;
      if (r16[cx] < 0x0131)
      {
        _pc = 0x32DA;
        continue;
      };
      r16[cx] = 0x0130;
      {
        _pc = 0x32DA;
        continue;
      };
    case 0x32D3:
      flags.carry = r16[cx] < 0x0008;
      r16[cx] -= 0x0008;
      if (!flags.carry)
      {
        _pc = 0x32DA;
        continue;
      };
      r16[cx] = 0;
    case 0x32DA:
      r16[cx] &= 0xfff8;
      _memoryWrite16(0x327D, r16[cx]);
      if (memory[adr(_ds, 0x3281)] < 1)
      {
        _pc = 0x32FE;
        continue;
      };
      if (memory[adr(_ds, 0x3281)] != 1)
      {
        _pc = 0x32F7;
        continue;
      };
      r8[dl] += 0x02;
      if (r8[dl] < 0xa6)
      {
        _pc = 0x32FE;
        continue;
      };
      r8[dl] = 0xa5;
      {
        _pc = 0x32FE;
        continue;
      };
    case 0x32F7:
      flags.carry = r8[dl] < 0x02;
      r8[dl] -= 0x02;
      if (!flags.carry)
      {
        _pc = 0x32FE;
        continue;
      };
      r8[dl] = 0;
    case 0x32FE:
      memory[0x327F] = r8[dl];
      yield* sub_2CB0();
      _memoryWrite16(0x3284, r16[ax]);
      yield* sub_33BA();
      if (!flags.carry)
      {
        _pc = 0x3328;
        continue;
      };
    case 0x330D:
      memory[0x3280] = 0;
      memory[0x3281] = 0;
      r16[cx] = _memoryRead16(0x32EF);
      _memoryWrite16(0x327D, r16[cx]);
      r8[dl] = memory[0x32F1];
      memory[0x327F] = r8[dl];
      return;
    case 0x3328:
      yield* sub_21E0();
      if (flags.carry)
      {
        _pc = 0x330D;
        continue;
      };
      yield* sub_33A0();
      _memoryWrite16(adr(_ds, 0x327A), _memoryRead16(adr(_ds, 0x327A)) + 2);
      yield* sub_3339();
      return;
  }
}

function* sub_3339()
{
  var _pc = 0x3339;
  while (_pc != -1) switch(_pc)
  {
    case 0x3339:
    case 0x3339:
      r16[bx] = _memoryRead16(0x327A);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x3260));
      if (r16[ax] != 0x0000)
      {
        _pc = 0x334B;
        continue;
      };
      _memoryWrite16(0x327A, r16[ax]);
      {
        _pc = 0x3339;
        continue;
      };
    case 0x334B:
      _si = r16[ax];
      _di = _memoryRead16(0x3284);
      _memoryWrite16(0x3282, _di);
      _bp = 0x31e8;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x1e02;
      memory[0x3286] = 0;
      flags.direction = false;
      memory[0x3289] = r8[ch];
      r8[ch] = 0;
      _memoryWrite16(0x3287, r16[cx]);
    case 0x3370:
      r16[cx] = _memoryRead16(0x3287);
      do {
        r16[bx] = _videoRead16(_esAssume(0xb800), _di);
        _memoryWrite16(ofs(_bp + 0), r16[bx]);
        _lodsw_MemData_DirForward();
        r16[ax] |= r16[bx];
        _stosw_MemB800_DirForward();
        _bp += 0x0002;
      } while (--r16[cx]);
      _di = ((_di - _memoryRead16(adr(_ds, 0x3287))) - _memoryRead16(adr(_ds, 0x3287))) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x3399;
        continue;
      };
      _di += 0x50;
    case 0x3399:
      memory[adr(_ds, 0x3289)] -= 1;
      if (memory[adr(_ds, 0x3289)] != 0)
      {
        _pc = 0x3370;
        continue;
      };
      return;
  }
}

function* sub_33A0()
{
  if (memory[adr(_ds, 0x3286)] != 0)
    return;
  r16[ax] = 0xb800;
  _es = r16[ax];
  _si = 0x31e8;
  _di = _memoryRead16(0x3282);
  r16[cx] = 0x1e02;
  yield* sub_2D9D();
}

function* sub_33BA()
{
  var _pc = 0x33BA;
  while (_pc != -1) switch(_pc)
  {
    case 0x33BA:
      if (memory[adr(_ds, 0x1CB8)] != 0)
      {
        _pc = 0x3403;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x4)) != 6)
      {
        _pc = 0x33D3;
        continue;
      };
      if (memory[adr(_ds, 0x44BD)] == 0)
      {
        _pc = 0x33D3;
        continue;
      };
      yield* sub_47B0();
      return;
    case 0x33D3:
      r16[ax] = _memoryRead16(0x327D);
      r8[dl] = memory[0x327F];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e1e;
      yield* sub_2E29();
      if (!flags.carry)
      {
        _pc = 0x3403;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x4)) != 4)
      {
        _pc = 0x33FE;
        continue;
      };
      if (memory[adr(_ds, 0x39E1)] != 0)
      {
        _pc = 0x3401;
        continue;
      };
    case 0x33FE:
      yield* sub_872();
    case 0x3401:
      flags.carry = true;
      return;
    case 0x3403:
      flags.carry = false;
      return;
  }
}

function* sub_3405()
{
  flags.direction = false;
  r16[ax] = 0;
  _push(_ds);
  _es = _pop();
  _di = 0x328e;
  r16[cx] = 0x14;
  _rep_stosw_MemData_DirForward();
  _memoryWrite16(0x32B6, 0xff);
  _memoryWrite16(0x327A, 0);
  _memoryWrite16(0x327D, 0);
  memory[0x327F] = 0xa0;
  memory[0x3286] = 1;
  memory[0x3280] = 0;
  memory[0x3281] = 0;
  yield* sub_2DFD();
  memory[0x32EB] = r8[dl];
  memory[0x32EA] = 0x6c;
}

function* sub_3445()
{
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    return;
  if (memory[adr(_ds, 0x56E)] == 0)
    return;
  r16[ax] = _memoryRead16(0x579) + 0x0c;
  r8[cl] = 0x03;
  r16[ax] >>= r8[cl];
  if (r16[ax] > 0x27)
    return;
  if (r16[ax] == _memoryRead16(adr(_ds, 0x32B6)))
    return;
  _memoryWrite16(0x32B6, r16[ax]);
  r16[bx] = r16[ax];
  r8[al] = memory[ofs(r16[bx] + 0x328e)];
  if (r8[al] >= 0x04)
    return;
  r8[al] += 1;
  memory[ofs(r16[bx] + 0x328e)] = r8[al];
  yield* sub_347F();
}

function* sub_347F()
{
  r8[ah] = 0x0a;
  r16[ax] = (r8[ah] * r8[al]) + 0x32b8;
  _si = r16[ax];
  _di = (r16[bx] << 1) + 0x1e00;
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[cx] = 0x0501;
  yield* sub_2D9D();
}

function* sub_34A0()
{
  var _pc = 0x34A0;
  while (_pc != -1) switch(_pc)
  {
    case 0x34A0:
      _memoryWrite16(0x3511, 0);
      memory[0x351B] = 0;
    case 0x34AB:
      r16[bx] = _memoryRead16(0x3511);
      flags.zero = memory[adr(_ds, r16[bx] + 0x34a7)] == 0; flags.carry = memory[adr(_ds, r16[bx] + 0x34a7)] < 0;
      if (memory[adr(_ds, r16[bx] + 0x34a7)] == 0)
      {
        _pc = 0x34B9;
        continue;
      };
      {
        _pc = 0x35AD;
        continue;
      };
    case 0x34B9:
      _si = r16[bx] << 1;
      r16[ax] = _memoryRead16(ofs(_si + 0x3447));
      r8[dl] = memory[ofs(r16[bx] + 0x3477)];
      _di = 0x0000;
      flags.zero = r16[bx] == 0x0c; flags.carry = r16[bx] < 0x0c;
      if (r16[bx] < 0x0c)
      {
        _pc = 0x34D0;
        continue;
      };
      _di = 0x0002;
    case 0x34D0:
      _si = _memoryRead16(ofs(_di + 13587));
      r16[cx] = _memoryRead16(ofs(_di + 13591));
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r8[ch] = 0x0e;
      yield* sub_2E29();
      if (!flags.carry)
      {
        _pc = 0x35AD;
        continue;
      };
      r16[bx] = _memoryRead16(0x3511);
      flags.zero = r16[bx] == 0x0c; flags.carry = r16[bx] < 0x0c;
      if (r16[bx] < 0x0c)
      {
        _pc = 0x356F;
        continue;
      };
      flags.zero = memory[adr(_ds, 0x553)] == 0; flags.carry = memory[adr(_ds, 0x553)] < 0;
      if (memory[adr(_ds, 0x553)] != 0)
      {
        _pc = 0x356F;
        continue;
      };
      flags.zero = memory[adr(_ds, 0x5F3)] == 0; flags.carry = memory[adr(_ds, 0x5F3)] < 0;
      if (memory[adr(_ds, 0x5F3)] != 0)
      {
        _pc = 0x356F;
        continue;
      };
      memory[0x552] = 1;
      r16[cx] = _memoryRead16(0x579);
      flags.carry = r16[cx] < 0x0008;
      r16[cx] -= 0x0008;
      if (!flags.carry)
      {
        _pc = 0x3511;
        continue;
      };
      r16[cx] = 0;
    case 0x3511:
      flags.zero = r16[cx] == 0x0117; flags.carry = r16[cx] < 0x0117;
      if (r16[cx] < 0x0117)
      {
        _pc = 0x351A;
        continue;
      };
      r16[cx] = 0x0116;
    case 0x351A:
      r8[dl] = memory[0x57B];
      flags.zero = r8[dl] == 0xb5; flags.carry = r8[dl] < 0xb5;
      if (r8[dl] < 0xb5)
      {
        _pc = 0x3525;
        continue;
      };
      r8[dl] = 0xb4;
    case 0x3525:
      yield* sub_2CB0();
      _di = r16[ax];
      _si = 0x3350;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x1205;
      yield* sub_2D9D();
      yield* sub_5797();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x3509, r16[dx]);
    case 0x3543:
      _push(r16[dx]);
      do {
        yield* sub_57A6();
        yield* sub_13D8();
      } while (r8[al] == 0);
      yield* sub_57A6();
      r16[dx] = _pop();
      r16[bx] = 0x0001;
      if (r8[dl] & 0x01)
      {
        _pc = 0x355A;
        continue;
      };
      r8[bl] = 0x0f;
    case 0x355A:
      r8[ah] = 0x0b;
      _interrupt(0x10);
      yield* sub_57A6();
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x3509));
      flags.zero = r16[dx] == 0x0d; flags.carry = r16[dx] < 0x0d;
      if (r16[dx] < 0x0d)
      {
        _pc = 0x3543;
        continue;
      };
      return;
    case 0x356F:
      memory[adr(_ds, 0x351B)] += 1;
      r16[ax] = 0x05dc;
      r16[bx] = 0x0425;
      yield* sub_593B();
      flags.zero = memory[adr(_ds, 0x351B)] == 1; flags.carry = memory[adr(_ds, 0x351B)] < 1;
      if (memory[adr(_ds, 0x351B)] != 1)
      {
        _pc = 0x3586;
        continue;
      };
      yield* sub_11E3();
    case 0x3586:
      r16[bx] = _memoryRead16(0x3511);
      yield* sub_37C1();
      r16[bx] = _memoryRead16(0x3511);
      memory[ofs(r16[bx] + 0x34a7)] = 1;
      flags.zero = r16[bx] == 0x0c; flags.carry = r16[bx] < 0x0c;
      if (r16[bx] >= 0x0c)
      {
        _pc = 0x35AD;
        continue;
      };
      memory[adr(_ds, 0x3410)] -= 1;
      if (memory[adr(_ds, 0x3410)] != 0)
      {
        _pc = 0x35AD;
        continue;
      };
      flags.zero = memory[adr(_ds, 0x5F3)] == 0; flags.carry = memory[adr(_ds, 0x5F3)] < 0;
      if (memory[adr(_ds, 0x5F3)] != 0)
      {
        _pc = 0x35AD;
        continue;
      };
      memory[0x553] = 1;
    case 0x35AD:
      _memoryWrite16(adr(_ds, 0x3511), _memoryRead16(adr(_ds, 0x3511)) + 1);
      flags.zero = _memoryRead16(adr(_ds, 0x3511)) == 0x18; flags.carry = _memoryRead16(adr(_ds, 0x3511)) < 0x18;
      if (_memoryRead16(adr(_ds, 0x3511)) >= 0x18)
      {
        _pc = 0x35BB;
        continue;
      };
      {
        _pc = 0x34AB;
        continue;
      };
    case 0x35BB:
      flags.zero = memory[adr(_ds, 0x351B)] == 0; flags.carry = memory[adr(_ds, 0x351B)] < 0;
      if (memory[adr(_ds, 0x351B)] == 0)
      {
        _pc = 0x35C7;
        continue;
      };
      yield* sub_363D();
      flags.carry = true;
      return;
    case 0x35C7:
      flags.carry = false;
      return;
  }
}

function* sub_35C9()
{
  var _pc = 0x35C9;
  while (_pc != -1) switch(_pc)
  {
    case 0x35C9:
      _memoryWrite16(0x3411, 0);
      _memoryWrite16(0x3415, 0);
      memory[0x3410] = 0x0c;
      r16[cx] = 0x18;
    case 0x35DD:
      r16[bx] = r16[cx] - 1;
      memory[ofs(r16[bx] + 0x348f)] = 1;
      memory[ofs(r16[bx] + 0x34a7)] = 0;
      r8[al] = memory[ofs(r16[bx] + 0x34f1)];
      memory[ofs(r16[bx] + 0x3477)] = r8[al];
      memory[ofs(r16[bx] + 0x342f)] = 1;
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x3601;
        continue;
      };
      r8[dl] = (~r8[dl]);
    case 0x3601:
      memory[ofs(r16[bx] + 0x3417)] = r8[dl];
      r16[bx] <<= 1;
      yield* sub_2DFD();
      r8[dh] = 0;
      _memoryWrite16(ofs(r16[bx] + 0x3447), r16[dx]);
      if (--r16[cx])
      {
        _pc = 0x35DD;
        continue;
      };
      r16[bx] = _memoryRead16(0x8);
      r8[cl] = memory[ofs(r16[bx] + 0x351c)];
      r8[ch] = 0;
      do {
        do {
          do {
            yield* sub_2DFD();
            r8[dl] &= 0x0f;
          } while (r8[dl] >= 0x0c);
          r8[bl] = r8[dl] + 0x0c;
          r8[bh] = 0;
        } while (memory[adr(_ds, r16[bx] + 0x34a7)] != 0);
        memory[ofs(r16[bx] + 0x34a7)] = 1;
      } while (--r16[cx]);
      return;
  }
}

function* sub_363D()
{
  var _pc = 0x363D;
  while (_pc != -1) switch(_pc)
  {
    case 0x363D:
    case 0x363D:
      r16[cx] = 0x0c;
    case 0x3640:
      r16[bx] = r16[cx] + 0x0b;
      if (memory[adr(_ds, r16[bx] + 0x34a7)] == 0)
      {
        _pc = 0x3672;
        continue;
      };
      r16[ax] = 0;
      r8[dl] = 0x01;
      memory[ofs(r16[bx] + 0x34a7)] = r8[al];
      if (_memoryRead16(adr(_ds, 0x579)) > 0xa0)
      {
        _pc = 0x3661;
        continue;
      };
      r16[ax] = 0x012e;
      r8[dl] = 0xff;
    case 0x3661:
      memory[ofs(r16[bx] + 0x3417)] = r8[dl];
      r8[bl] <<= 1;
      _memoryWrite16(ofs(r16[bx] + 0x3447), r16[ax]);
      memory[adr(_ds, 0x351B)] -= 1;
      if (memory[adr(_ds, 0x351B)] != 0)
      {
        _pc = 0x363D;
        continue;
      };
      return;
    case 0x3672:
      if (--r16[cx])
      {
        _pc = 0x3640;
        continue;
      };
      return;
  }
}

function* sub_3675()
{
  var _pc = 0x3675;
  while (_pc != -1) switch(_pc)
  {
    case 0x3675:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x3509)))
      {
        _pc = 0x3680;
        continue;
      };
      return;
    case 0x3680:
      _memoryWrite16(0x350B, r16[dx]);
      _memoryWrite16(adr(_ds, 0x3415), _memoryRead16(adr(_ds, 0x3415)) + 1);
      r16[bx] = _memoryRead16(0x3415);
      if (r16[bx] < 0x18)
      {
        _pc = 0x36A4;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x3415, r16[bx]);
      _memoryWrite16(adr(_ds, 0x3411), _memoryRead16(adr(_ds, 0x3411)) ^ 0x0c);
      _memoryWrite16(adr(_ds, 0x3413), _memoryRead16(adr(_ds, 0x3413)) + 8);
      {
        _pc = 0x36B7;
        continue;
      };
    case 0x36A4:
      if (r16[bx] != 0x0c)
      {
        _pc = 0x36BD;
        continue;
      };
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x36B7;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] < 0x30)
      {
        _pc = 0x36BD;
        continue;
      };
    case 0x36B7:
      r16[ax] = _memoryRead16(0x350B);
      _memoryWrite16(0x3509, r16[ax]);
    case 0x36BD:
      _si = r16[bx] << 1;
      if (memory[adr(_ds, r16[bx] + 0x34a7)] != 0)
        return;
      yield* sub_2DFD();
      if (r8[dl] > 0x10)
      {
        _pc = 0x36E9;
        continue;
      };
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x36D7;
        continue;
      };
      r8[dl] = (~r8[dl]);
    case 0x36D7:
      memory[ofs(r16[bx] + 0x3417)] = r8[dl];
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x36E5;
        continue;
      };
      r8[dl] = (~r8[dl]);
    case 0x36E5:
      memory[ofs(r16[bx] + 0x342f)] = r8[dl];
    case 0x36E9:
      r16[cx] = 0x0004;
      if (r16[bx] < 0x0c)
      {
        _pc = 0x36F3;
        continue;
      };
      r8[cl] >>= 1;
    case 0x36F3:
      r16[ax] = _memoryRead16(ofs(_si + 0x3447));
      if (memory[adr(_ds, r16[bx] + 0x3417)] == 1)
      {
        _pc = 0x370B;
        continue;
      };
      flags.carry = r16[ax] < r16[cx];
      r16[ax] -= r16[cx];
      if (!flags.carry)
      {
        _pc = 0x371A;
        continue;
      };
      r16[ax] = 0;
      memory[ofs(r16[bx] + 0x3417)] = 1;
      {
        _pc = 0x371A;
        continue;
      };
    case 0x370B:
      r16[ax] += r16[cx];
      if (r16[ax] < 0x012f)
      {
        _pc = 0x371A;
        continue;
      };
      r16[ax] = 0x012e;
      memory[ofs(r16[bx] + 0x3417)] = 0xff;
    case 0x371A:
      _memoryWrite16(ofs(_si + 0x3447), r16[ax]);
      r8[al] = memory[ofs(r16[bx] + 0x3477)];
      if (memory[adr(_ds, r16[bx] + 0x342f)] == 1)
      {
        _pc = 0x373C;
        continue;
      };
      r8[al] -= 1;
      if (r8[al] >= memory[adr(_ds, r16[bx] + 0x34f1)])
      {
        _pc = 0x3750;
        continue;
      };
      r8[al] = memory[ofs(r16[bx] + 0x34f1)];
      memory[ofs(r16[bx] + 0x342f)] = 1;
      {
        _pc = 0x3750;
        continue;
      };
    case 0x373C:
      r8[al] += 1;
      r8[dl] = (memory[ofs(r16[bx] + 0x34f1)]) + 0x18;
      if (r8[al] <= r8[dl])
      {
        _pc = 0x3750;
        continue;
      };
      r8[al] = r8[dl];
      memory[ofs(r16[bx] + 0x342f)] = 0xff;
    case 0x3750:
      memory[ofs(r16[bx] + 0x3477)] = r8[al];
      r8[dl] = r8[al];
      r16[cx] = _memoryRead16(ofs(_si + 0x3447));
      yield* sub_2CB0();
      _memoryWrite16(0x34EF, r16[ax]);
      r16[bx] = _memoryRead16(0x3415);
      yield* sub_37C1();
      r16[bx] = _memoryRead16(0x3415);
      _si = r16[bx] << 1;
      _di = _memoryRead16(0x34EF);
      _memoryWrite16(ofs(_si + 0x34bf), _di);
      memory[ofs(r16[bx] + 0x348f)] = 0;
      r16[ax] = 0xb800;
      _es = r16[ax];
      if (r16[bx] < 0x0c)
      {
        _pc = 0x379F;
        continue;
      };
      _si = r16[bx];
      r8[cl] = 0x03;
      _si = (((_si << r8[cl]) + _memoryRead16(adr(_ds, 0x3413))) & 0x18) + 0x3330;
      r16[cx] = 0x0202;
      yield* sub_2D9D();
      return;
    case 0x379F:
      _si = _memoryRead16(0x3411);
      if (r8[bl] & 0x01)
      {
        _pc = 0x37AC;
        continue;
      };
      _si = _si ^ 0x0c;
    case 0x37AC:
      if (memory[adr(_ds, r16[bx] + 0x3417)] == 1)
      {
        _pc = 0x37B6;
        continue;
      };
      _si += 0x18;
    case 0x37B6:
      _si += 0x3300;
      r16[cx] = 0x0601;
      yield* sub_2D9D();
      return;
  }
}

function* sub_37C1()
{
  var _pc = 0x37C1;
  while (_pc != -1) switch(_pc)
  {
    case 0x37C1:
      if (memory[adr(_ds, r16[bx] + 0x348f)] != 0)
        return;
      r16[bx] <<= 1;
      _si = 0x3404;
      _di = _memoryRead16(ofs(r16[bx] + 0x34bf));
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0601;
      if (r16[bx] < 0x18)
      {
        _pc = 0x37E1;
        continue;
      };
      r16[cx] = 0x0202;
    case 0x37E1:
      yield* sub_2D9D();
      return;
  }
}

function* sub_37E5()
{
  var _pc = 0x37E5;
  while (_pc != -1) switch(_pc)
  {
    case 0x37E5:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x350F));
      if (r16[ax] < 0x0008)
        return;
      _memoryWrite16(adr(_ds, 0x350D), _memoryRead16(adr(_ds, 0x350D)) + 1);
      r16[bx] = _memoryRead16(0x350D);
      if (r16[bx] < 0x28)
      {
        _pc = 0x380B;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x350D, r16[bx]);
      _memoryWrite16(0x350F, r16[dx]);
    case 0x380B:
      _di = r16[bx] << 1;
      if (memory[adr(_ds, 0x57B)] > 7)
      {
        _pc = 0x3829;
        continue;
      };
      r16[ax] = _memoryRead16(0x579);
      r8[cl] = 0x02;
      r16[ax] = (r16[ax] >> r8[cl]) + 1;
      flags.carry = r16[ax] < _di;
      r16[ax] -= _di;
      if (!flags.carry)
      {
        _pc = 0x3824;
        continue;
      };
      r16[ax] = (~r16[ax]);
    case 0x3824:
      if (r16[ax] < 0x0004)
        return;
    case 0x3829:
      _di += 0xa0;
      r8[al] = (memory[ofs(r16[bx] + 0x2656)]) + 0x08;
      memory[ofs(r16[bx] + 0x2656)] = r8[al];
      r16[ax] = (r16[ax] & 0x18) + 0x2020;
      _si = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0401;
      yield* sub_2D9D();
      return;
  }
}

function* sub_3850()
{
  var _pc = 0x3850;
  while (_pc != -1) switch(_pc)
  {
    case 0x3850:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x35DA));
      if (r16[ax] >= 0x0006)
      {
        _pc = 0x3860;
        continue;
      };
      return;
    case 0x3860:
      _memoryWrite16(0x35DA, r16[dx]);
      _memoryWrite16(adr(_ds, 0x35D8), _memoryRead16(adr(_ds, 0x35D8)) + 2);
      r16[bx] = _memoryRead16(0x35D8) & 0x0006;
      _si = _memoryRead16(ofs(r16[bx] + 0x35d0));
      _di = 0x15c9;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0a02;
      yield* sub_2D9D();
      r16[ax] = 0xe4;
      r8[dl] = 0x8a;
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e0a;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      memory[0x554] = 1;
      return;
  }
}

function* sub_38B0()
{
  var _pc = 0x38B0;
  while (_pc != -1) switch(_pc)
  {
    case 0x38B0:
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x38BA;
        continue;
      };
      {
        _pc = 0x38D3;
        continue;
      };
    case 0x38BA:
      _memoryWrite16(adr(_ds, 0x414), _memoryRead16(adr(_ds, 0x414)) + 1);
      memory[0x418] = 1;
      r16[dx] = 0xaaaa;
      yield* sub_3A96();
      r16[ax] = 0;
      memory[0x369F] = 0;
      yield* sub_3AAC();
    case 0x38D3:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x38EF;
        continue;
      };
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x412));
      r16[ax] = 0x2a30;
      flags.carry = r16[ax] < r16[dx];
      r16[ax] -= r16[dx];
      if (!flags.carry)
      {
        _pc = 0x38EB;
        continue;
      };
      r16[ax] = 0;
    case 0x38EB:
      r16[ax] >>= 1;
      {
        _pc = 0x390E;
        continue;
      };
    case 0x38EF:
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x410));
      r16[ax] = 0x0546;
      if (_memoryRead16(adr(_ds, 0x6)) != 6)
      {
        _pc = 0x38FF;
        continue;
      };
      r16[ax] <<= 1;
    case 0x38FF:
      flags.carry = r16[ax] < r16[dx];
      r16[ax] -= r16[dx];
      if (!flags.carry)
      {
        _pc = 0x3905;
        continue;
      };
      r16[ax] = 0;
    case 0x3905:
      if (_memoryRead16(adr(_ds, 0x6)) == 6)
      {
        _pc = 0x390E;
        continue;
      };
      r16[ax] <<= 1;
    case 0x390E:
      _memoryWrite16(0x3697, r16[ax]);
      yield* sub_3AF4();
      r16[bx] = _memoryRead16(0x6);
      r8[bl] <<= 1;
      _si = _memoryRead16(ofs(r16[bx] + 0x36cc));
      _di = 0x368d;
      yield* sub_271E();
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x396E;
        continue;
      };
      r16[bx] = _memoryRead16(0x8);
      r8[bl] <<= 1;
      r16[ax] = r16[bx];
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x36dc));
      if (_memoryRead16(adr(_ds, 0x2E8D)) >= 8)
      {
        _pc = 0x3943;
        continue;
      };
      r16[cx] <<= 1;
      r16[ax] += 0x10;
    case 0x3943:
      _memoryWrite16(0x370C, r16[ax]);
      do {
        _si = 0x368d;
        _di = 0x1f82;
        _push(r16[cx]);
        yield* sub_271E();
        r16[cx] = _pop();
      } while (--r16[cx]);
      yield* sub_39FA();
      memory[0x369E] = 0x38;
      memory[0x3699] = 1;
      _memoryWrite16(0x3722, 0x44);
      yield* sub_3A3A();
      yield* sub_3A6C();
      {
        _pc = 0x39A7;
        continue;
      };
    case 0x396E:
      _si = 0x368d;
      _di = 0x1f82;
      yield* sub_271E();
      memory[0x3699] = 2;
      _memoryWrite16(0x3722, 0x1e);
      r16[dx] = 0xffff;
      yield* sub_3A96();
      r16[ax] = 0x0a8c - _memoryRead16(adr(_ds, 0x3697));
      r8[cl] = 0x04;
      r16[ax] >>= r8[cl];
      r8[al] &= 0xf0;
      memory[0x369E] = r8[al];
      r8[ah] = 0x28;
      r16[ax] = r8[ah] * r8[al];
      memory[0x369F] = 1;
      yield* sub_3AAC();
      yield* sub_3A3A();
    case 0x39A7:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x3695, r16[dx]);
    case 0x39AF:
      if (_memoryRead16(adr(_ds, 0x6)) != 7)
      {
        _pc = 0x39BB;
        continue;
      };
      yield* sub_5B63();
      {
        _pc = 0x39BE;
        continue;
      };
    case 0x39BB:
      yield* sub_5835();
    case 0x39BE:
      yield* sub_3A1C();
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x3695));
      if (r16[dx] < _memoryRead16(adr(_ds, 0x3722)))
      {
        _pc = 0x39AF;
        continue;
      };
      r16[bx] = 0;
      r8[ah] = 0x0b;
      _interrupt(0x10);
      if (_memoryRead16(adr(_ds, 0x6)) == 7)
      {
        _pc = 0x39DC;
        continue;
      };
      yield* sub_5B21();
      return;
    case 0x39DC:
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = 0x0e;
      _di = 0x08e4;
      r16[cx] = 0x0804;
      yield* sub_2D9D();
      _si = 0x4e;
      _di = 0x0c94;
      r16[cx] = 0x0814;
      yield* sub_2D9D();
      return;
  }
}

function* sub_39FA()
{
  _push(_ds);
  _es = _pop();
  r16[ax] = 0xb800;
  _ds = r16[ax];
  r16[cx] = 0x0804;
  _di = 0x0e;
  _si = 0x08e4;
  yield* sub_2DCA();
  r16[cx] = 0x0814;
  _di = 0x4e;
  _si = 0x0c94;
  yield* sub_2DCA();
  _push(_es);
  _ds = _pop();
}

function* sub_3A1C()
{
  var _pc = 0x3A1C;
  while (_pc != -1) switch(_pc)
  {
    case 0x3A1C:
      r8[ah] = 0;
      _interrupt(0x1a);
      _push(r16[dx]);
      do {
        yield* sub_13D8();
      } while (r8[al] == 0);
      r16[dx] = _pop();
      _push(r16[dx]);
      r16[bx] = 0;
      if (r16[dx] & 0x0004)
      {
        _pc = 0x3A34;
        continue;
      };
      r8[bl] = memory[0x3699];
    case 0x3A34:
      r8[ah] = 0x0b;
      _interrupt(0x10);
      r16[dx] = _pop();
      return;
  }
}

function* sub_3A3A()
{
  r8[ah] = 0x02;
  r8[dh] = memory[0x369E];
  r8[cl] = 0x03;
  r8[dh] >>= r8[cl];
  r8[dl] = 0x12;
  r8[bh] = 0;
  _interrupt(0x10);
  _memoryWrite16(0x36A0, 3);
  do {
    r16[bx] = _memoryRead16(0x36A0);
    r8[al] = (memory[ofs(r16[bx] + 0x368d)]) + 0x30;
    r8[ah] = 0x0e;
    r8[bl] = 0x03;
    _interrupt(0x10);
    _memoryWrite16(adr(_ds, 0x36A0), _memoryRead16(adr(_ds, 0x36A0)) + 1);
  } while (_memoryRead16(adr(_ds, 0x36A0)) < 7);
}

function* sub_3A6C()
{
  r8[ah] = 0x02;
  r8[dl] = 0x0a;
  r8[dh] = r8[dl];
  r16[bx] = 0;
  _interrupt(0x10);
  r16[bx] = _memoryRead16(0x370C);
  r16[ax] = _memoryRead16(ofs(r16[bx] + 0x36ec));
  _memoryWrite16(0x3720, r16[ax]);
  r16[bx] = 0;
  do {
    r8[ah] = 0x0e;
    r8[al] = memory[ofs(r16[bx] + 0x370e)];
    _push(r16[bx]);
    r8[bl] = 0x03;
    _interrupt(0x10);
    r16[bx] = _pop();
    r16[bx] += 1;
  } while (r16[bx] < 0x14);
}

function* sub_3A96()
{
  flags.direction = false;
  r16[ax] = SEG_DATA;
  _es = r16[ax];
  _di = 0x0e;
  _si = 0x35e0;
  r16[cx] = 0x1e;
  do {
    _lodsw_MemData_DirForward();
    r16[ax] &= r16[dx];
    _stosw_MemData_DirForward();
  } while (--r16[cx]);
}

function* sub_3AAC()
{
  var _pc = 0x3AAC;
  while (_pc != -1) switch(_pc)
  {
    case 0x3AAC:
      _memoryWrite16(0x369A, r16[ax]);
      r16[ax] = 0xb800;
      _es = r16[ax];
      yield* sub_5829();
      r16[ax] = 0x1b80;
    case 0x3ABA:
      r16[bx] = 0x361c;
      _memoryWrite16(0x369C, r16[ax]);
      yield* sub_2B24();
      if (memory[adr(_ds, 0x369F)] == 0)
      {
        _pc = 0x3AE2;
        continue;
      };
      yield* sub_5869();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x3695, r16[dx]);
      do {
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x3695));
      } while (r16[dx] < 0x0002);
    case 0x3AE2:
      r16[ax] = _memoryRead16(0x369C);
      flags.carry = r16[ax] < 0x0280;
      r16[ax] -= 0x0280;
      if (flags.carry)
      {
        _pc = 0x3AF0;
        continue;
      };
      if (r16[ax] >= _memoryRead16(adr(_ds, 0x369A)))
      {
        _pc = 0x3ABA;
        continue;
      };
    case 0x3AF0:
      yield* sub_5B21();
      return;
  }
}

function* sub_3AF4()
{
  var _pc = 0x3AF4;
  while (_pc != -1) switch(_pc)
  {
    case 0x3AF4:
      _memoryWrite16(0x368B, r16[ax]);
      r16[ax] = 0;
      _memoryWrite16(0x368D, r16[ax]);
      _memoryWrite16(0x368F, r16[ax]);
      _memoryWrite16(0x3691, r16[ax]);
      _memoryWrite16(0x3693, r16[ax]);
      r16[bx] = 0x3684;
      r16[dx] = 0x1000;
    case 0x3B0B:
      if (!(_memoryRead16(adr(_ds, 0x368B)) & r16[dx]))
      {
        _pc = 0x3B19;
        continue;
      };
      _si = r16[bx];
      _di = 0x368d;
      yield* sub_271E();
    case 0x3B19:
      r16[bx] -= 0x0007;
      flags.carry = r16[dx] & 1;
      r16[dx] >>= 1;
      if (!flags.carry)
      {
        _pc = 0x3B0B;
        continue;
      };
      return;
  }
}

function* sub_3B30()
{
  memory[0x37AF] = 3;
  r16[ax] = 0x0001;
  _memoryWrite16(0x37B0, r16[ax]);
  _memoryWrite16(0x37B2, r16[ax]);
  _memoryWrite16(0x37B4, r16[ax]);
}

function* sub_3B42()
{
  var _pc = 0x3B42;
  while (_pc != -1) switch(_pc)
  {
    case 0x3B42:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x37B8)))
      {
        _pc = 0x3B4D;
        continue;
      };
      return;
    case 0x3B4D:
      _memoryWrite16(0x37B8, r16[dx]);
      _memoryWrite16(0x37B6, 4);
    case 0x3B57:
      r16[bx] = _memoryRead16(0x37B6);
      if (_memoryRead16(adr(_ds, r16[bx] + 0x37b0)) == 0)
      {
        _pc = 0x3B9B;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x37a3));
      r8[dl] = 0x18;
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e10;
      yield* sub_2E29();
      if (!flags.carry)
      {
        _pc = 0x3B9B;
        continue;
      };
      r16[ax] = 0x0c00;
      r16[bx] = 0x08fd;
      yield* sub_593B();
      yield* sub_11E3();
      yield* sub_3E38();
      r16[bx] = _memoryRead16(0x37B6);
      yield* sub_3BA3();
      yield* sub_1124();
      yield* sub_3E14();
      return;
    case 0x3B9B:
      flags.carry = _memoryRead16(adr(_ds, 0x37B6)) < 2;
      _memoryWrite16(adr(_ds, 0x37B6), _memoryRead16(adr(_ds, 0x37B6)) - 2);
      if (!flags.carry)
      {
        _pc = 0x3B57;
        continue;
      };
      return;
  }
}

function* sub_3BA3()
{
  _memoryWrite16(ofs(r16[bx] + 0x37b0), 0);
  _push(_ds);
  _es = _pop();
  flags.direction = false;
  r16[ax] = 0xaaaa;
  _di = 0x0e;
  _si = _di;
  r16[cx] = 0x20;
  _rep_stosw_MemData_DirForward();
  _di = _memoryRead16(ofs(r16[bx] + 0x37a9));
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[cx] = 0x1002;
  yield* sub_2D9D();
  memory[adr(_ds, 0x37AF)] -= 1;
  if (memory[adr(_ds, 0x37AF)] != 0)
    return;
  if (memory[adr(_ds, 0x552)] != 0)
    return;
  memory[0x553] = 1;
}

function* sub_3BDB()
{
  var _pc = 0x3BDB;
  while (_pc != -1) switch(_pc)
  {
    case 0x3BDB:
      r16[ax] = 0xb800;
      _es = r16[ax];
      _memoryWrite16(0x37A0, 1642);
      r16[cx] = 0x10;
    case 0x3BE9:
      r16[ax] = 0;
      r16[bx] = r16[ax];
    case 0x3BED:
      memory[0x37A2] = r8[al];
      r8[ah] = 0;
      r16[ax] += 0x3730;
      _si = r16[ax];
      _di = _memoryRead16(0x37A0) + r16[bx];
      _push(r16[cx]);
      r16[cx] = 0x0801;
      _push(r16[bx]);
      yield* sub_2D9D();
      r16[bx] = _pop();
      r16[cx] = _pop();
      r16[bx] += 0x0002;
      if (r16[bx] < 0x1e)
      {
        _pc = 0x3C1E;
        continue;
      };
      if (r16[bx] != 0x1e)
      {
        _pc = 0x3C15;
        continue;
      };
      r8[al] = 0x20;
      {
        _pc = 0x3BED;
        continue;
      };
    case 0x3C15:
      _memoryWrite16(adr(_ds, 0x37A0), _memoryRead16(adr(_ds, 0x37A0)) + 320);
      if (--r16[cx])
      {
        _pc = 0x3BE9;
        continue;
      };
      return;
    case 0x3C1E:
      if (memory[adr(_ds, 0x37A2)] == 0x50)
      {
        _pc = 0x3C36;
        continue;
      };
      if (r8[cl] & 0x01)
      {
        _pc = 0x3C36;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] < 0x40)
      {
        _pc = 0x3C36;
        continue;
      };
      r8[al] = 0x10;
      {
        _pc = 0x3BED;
        continue;
      };
    case 0x3C36:
      yield* sub_2DFD();
      r8[al] = ((r8[dl] - r8[bl]) & 0x30) + 0x30;
      {
        _pc = 0x3BED;
        continue;
      };
      return;
  }
}

function* sub_3C43()
{
  var _pc = 0x3C43;
  while (_pc != -1) switch(_pc)
  {
    case 0x3C43:
      r16[ax] = _memoryRead16(0x579) & 0xfffc;
      if (r16[ax] < 0xa4)
      {
        _pc = 0x3C7F;
        continue;
      };
      if (r16[ax] > 0x0118)
      {
        _pc = 0x3C7F;
        continue;
      };
      r8[dl] = (memory[0x57B] - 0x02) & 0xf8;
      if (!(r8[dl] & 0x08))
      {
        _pc = 0x3C7F;
        continue;
      };
      if (r8[dl] < 0x28)
      {
        _pc = 0x3C7F;
        continue;
      };
      if (r8[dl] > 0xa0)
      {
        _pc = 0x3C7F;
        continue;
      };
      _memoryWrite16(0x579, r16[ax]);
      r8[dl] += 0x02;
      memory[0x57B] = r8[dl];
      r8[dl] += 0x32;
      memory[0x57C] = r8[dl];
      flags.carry = true;
      return;
    case 0x3C7F:
      flags.carry = false;
      return;
  }
}

function* sub_3C90()
{
  memory[0x3966] = 8;
  memory[0x396A] = 1;
  memory[0x3967] = 0;
  memory[0x396D] = 2;
  _memoryWrite16(0x3964, 280);
  _memoryWrite16(0x396B, 0);
}

function* sub_3CB1()
{
  var _pc = 0x3CB1;
  while (_pc != -1) switch(_pc)
  {
    case 0x3CB1:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x39C8));
      if (r16[ax] >= 0x0002)
      {
        _pc = 0x3CC1;
        continue;
      };
      return;
    case 0x3CC1:
      _memoryWrite16(0x39C8, r16[dx]);
      yield* sub_3E52();
      if (flags.carry)
        return;
      yield* sub_3E6E();
      if (!flags.carry)
      {
        _pc = 0x3CD2;
        continue;
      };
      {
        _pc = 0x3D90;
        continue;
      };
    case 0x3CD2:
      r16[bx] = _memoryRead16(0x8);
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x39cc));
      _memoryWrite16(0x39C6, r16[ax]);
      r16[ax] = _memoryRead16(0x3964);
      _memoryWrite16(0x39C3, r16[ax]);
      r8[dl] = memory[0x3966];
      memory[0x39C5] = r8[dl];
      if (r8[dl] != 0x08)
      {
        _pc = 0x3D25;
        continue;
      };
      r16[ax] &= 0xfff8;
      r16[dx] = _memoryRead16(0x579) & 0xfff8;
      if (r16[ax] != r16[dx])
      {
        _pc = 0x3D0D;
        continue;
      };
      memory[0x3967] = 1;
      memory[0x396E] = 1;
      {
        _pc = 0x3D25;
        continue;
      };
    case 0x3D0D:
      r16[ax] = _memoryRead16(0x3964);
      if (r16[ax] < r16[dx])
      {
        _pc = 0x3D1C;
        continue;
      };
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x39C6));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x39C6));
      if (!flags.carry)
      {
        _pc = 0x3D20;
        continue;
      };
      r16[ax] = 0;
      {
        _pc = 0x3D20;
        continue;
      };
    case 0x3D1C:
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x39C6));
    case 0x3D20:
      _memoryWrite16(0x3964, r16[ax]);
      {
        _pc = 0x3D79;
        continue;
      };
    case 0x3D25:
      r8[al] = memory[0x3966];
      memory[adr(_ds, 0x396E)] += 1;
      r8[dl] = ((memory[0x396E] >> 2) & 0x03) + 0x02;
      if (memory[adr(_ds, 0x3967)] == 1)
      {
        _pc = 0x3D52;
        continue;
      };
      flags.carry = r8[al] < r8[dl];
      r8[al] -= r8[dl];
      if (flags.carry)
      {
        _pc = 0x3D49;
        continue;
      };
      if (r8[al] >= 0x09)
      {
        _pc = 0x3D76;
        continue;
      };
    case 0x3D49:
      r8[al] = 0x08;
      memory[0x3967] = 0;
      {
        _pc = 0x3D76;
        continue;
      };
    case 0x3D52:
      r8[al] += r8[dl];
      if (r8[al] > memory[adr(_ds, 0x57B)])
      {
        _pc = 0x3D71;
        continue;
      };
      r16[bx] = _memoryRead16(0x3964);
      flags.carry = r16[bx] < _memoryRead16(adr(_ds, 0x579));
      r16[bx] = r16[bx] - _memoryRead16(adr(_ds, 0x579));
      if (!flags.carry)
      {
        _pc = 0x3D66;
        continue;
      };
      r16[bx] = (~r16[bx]);
    case 0x3D66:
      if (r16[bx] > 0x30)
      {
        _pc = 0x3D71;
        continue;
      };
      if (r8[al] < 0xa0)
      {
        _pc = 0x3D76;
        continue;
      };
      r8[al] = 0x9f;
    case 0x3D71:
      memory[0x3967] = 0xff;
    case 0x3D76:
      memory[0x3966] = r8[al];
    case 0x3D79:
      yield* sub_3E52();
      if (!flags.carry)
      {
        _pc = 0x3D8B;
        continue;
      };
      r16[ax] = _memoryRead16(0x39C3);
      _memoryWrite16(0x3964, r16[ax]);
      r8[al] = memory[0x39C5];
      memory[0x3966] = r8[al];
      return;
    case 0x3D8B:
      yield* sub_3E6E();
      if (!flags.carry)
      {
        _pc = 0x3DEE;
        continue;
      };
    case 0x3D90:
      if (memory[adr(_ds, 0x553)] == 0)
      {
        _pc = 0x3D98;
        continue;
      };
      return;
    case 0x3D98:
      r16[cx] = _memoryRead16(0x579);
      flags.carry = r16[cx] < 0x0c;
      r16[cx] -= 0x0c;
      if (!flags.carry)
      {
        _pc = 0x3DA3;
        continue;
      };
      r16[cx] = 0;
    case 0x3DA3:
      if (r16[cx] < 0x010f)
      {
        _pc = 0x3DAC;
        continue;
      };
      r16[cx] = 0x010e;
    case 0x3DAC:
      r8[dl] = memory[0x57B];
      flags.carry = r8[dl] < 0x04;
      r8[dl] -= 0x04;
      if (!flags.carry)
      {
        _pc = 0x3DB7;
        continue;
      };
      r8[dl] = 0;
    case 0x3DB7:
      yield* sub_2CB0();
      _di = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = 0x37c0;
      _bp = 0x0e;
      r16[cx] = 0x1506;
      yield* sub_2CCC();
      yield* sub_56F4();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x39C8, r16[dx]);
      do {
        yield* sub_5704();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x39C8));
      } while (r16[dx] < 0x0009);
      memory[0x552] = 1;
      return;
    case 0x3DEE:
      r16[cx] = _memoryRead16(0x3964);
      r8[dl] = memory[0x3966];
      yield* sub_2CB0();
      _memoryWrite16(0x39CA, r16[ax]);
      yield* sub_3E38();
      memory[adr(_ds, 0x396D)] -= 1;
      if (memory[adr(_ds, 0x396D)] != 0)
      {
        _pc = 0x3E10;
        continue;
      };
      memory[0x396D] = 2;
      _memoryWrite16(adr(_ds, 0x396B), _memoryRead16(adr(_ds, 0x396B)) ^ 0x54);
    case 0x3E10:
      yield* sub_3E14();
      return;
  }
}

function* sub_3E14()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x39CA);
  _memoryWrite16(0x3968, _di);
  _bp = 0x396f;
  memory[0x396A] = 0;
  _si = _memoryRead16(0x396B) + 0x38bc;
  r16[cx] = 0x0e03;
  yield* sub_2CCC();
}

function* sub_3E38()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  if (memory[adr(_ds, 0x396A)] != 0)
    return;
  _di = _memoryRead16(0x3968);
  _si = 0x396f;
  r16[cx] = 0x0e03;
  yield* sub_2D9D();
}

function* sub_3E52()
{
  r16[ax] = _memoryRead16(0x3964);
  r8[dl] = memory[0x3966];
  _si = 0x18;
  r16[bx] = _memoryRead16(0x327D);
  r8[dh] = memory[0x327F];
  _di = 0x10;
  r16[cx] = 0x1e0e;
  yield* sub_2E29();
}

function* sub_3E6E()
{
  r16[ax] = _memoryRead16(0x3964);
  r8[dl] = memory[0x3966];
  _si = 0x18;
  _di = _si;
  r16[bx] = _memoryRead16(0x579);
  r8[dh] = memory[0x57B];
  r16[cx] = 0x0e0e;
  yield* sub_2E29();
}

function* sub_3E90()
{
  var _pc = 0x3E90;
  while (_pc != -1) switch(_pc)
  {
    case 0x3E90:
      if (memory[adr(_ds, 0x39E1)] == 0)
      {
        _pc = 0x3EA4;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] == _memoryRead16(adr(_ds, 0x3D16)))
        return;
      {
        _pc = 0x3F35;
        continue;
      };
    case 0x3EA4:
      if (memory[adr(_ds, 0x584)] != 0)
        return;
      if (memory[adr(_ds, 0x69A)] != 0)
        return;
      if (memory[adr(_ds, 0x39E0)] != 0)
      {
        _pc = 0x3EBA;
        continue;
      };
      return;
    case 0x3EBA:
      yield* sub_4065();
      if (flags.carry)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x3D18));
      if (r16[ax] < 0x0c)
        return;
      _memoryWrite16(0x3D18, r16[dx]);
      memory[0x55C] = 0;
      r8[bl] = memory[0x39E0] - 1;
      r8[bh] = 0;
      _si = r16[bx];
      r8[cl] = 0x02;
      _si <<= r8[cl];
      r16[ax] = _memoryRead16(ofs(_si + 0x3c5a));
      _memoryWrite16(0x39E2, r16[ax]);
      r16[ax] = 0;
      if (r8[bl] >= 0x03)
      {
        _pc = 0x3EF5;
        continue;
      };
      r8[al] = 0x80;
    case 0x3EF5:
      _memoryWrite16(0x39E4, r16[ax]);
      r8[bl] = memory[ofs(r16[bx] + 0x3ce3)];
      _si = r16[bx];
      r8[cl] = 0x02;
      _si <<= r8[cl];
      r16[ax] = _memoryRead16(ofs(_si + 0x3c5a));
      _memoryWrite16(0x39E6, r16[ax]);
      r16[ax] = 0;
      if (r8[bl] >= 0x03)
      {
        _pc = 0x3F12;
        continue;
      };
      r8[al] = 0x80;
    case 0x3F12:
      _memoryWrite16(0x39E8, r16[ax]);
      r8[al] = memory[ofs(r16[bx] + 0x1050)];
      memory[0x3D05] = r8[al];
      r8[bl] <<= 1;
      r16[ax] = (_memoryRead16(ofs(r16[bx] + 0x1137))) + 0x0008;
      _memoryWrite16(0x3D03, r16[ax]);
      yield* sub_11E3();
      memory[0x39E1] = 0x0e;
      memory[0x69A] = 0x10;
    case 0x3F35:
      if (memory[adr(_ds, 0x1CBF)] != 0)
      {
        _pc = 0x3F3F;
        continue;
      };
      yield* sub_33A0();
    case 0x3F3F:
      memory[adr(_ds, 0x39E1)] -= 2;
      r8[bh] = 0;
      r8[bl] = memory[0x39E1];
      if (r8[bl] < 0x08)
      {
        _pc = 0x3F58;
        continue;
      };
      _di = _memoryRead16(0x39E2);
      r16[ax] = _memoryRead16(0x39E4);
      {
        _pc = 0x3F70;
        continue;
      };
    case 0x3F58:
      _di = _memoryRead16(0x39E6);
      r8[al] = memory[0x3D05];
      memory[0x57B] = r8[al];
      r8[al] += 0x32;
      memory[0x57C] = r8[al];
      r16[ax] = _memoryRead16(0x3D03);
      _memoryWrite16(0x579, r16[ax]);
      r16[ax] = _memoryRead16(0x39E8);
    case 0x3F70:
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, r16[bx] + 0x3d06));
      _si = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x1002;
      yield* sub_2D9D();
      if (memory[adr(_ds, 0x1CBF)] != 0)
      {
        _pc = 0x3F8B;
        continue;
      };
      yield* sub_3339();
    case 0x3F8B:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x3D16, r16[dx]);
      if (memory[adr(_ds, 0x39E1)] != 0)
        return;
      yield* sub_1112();
      return;
  }
}

function* sub_3F9E()
{
  var _pc = 0x3F9E;
  while (_pc != -1) switch(_pc)
  {
    case 0x3F9E:
      r16[ax] = 0xb800;
      _es = r16[ax];
      memory[0x39E0] = 0;
      memory[0x39E1] = 0;
      _memoryWrite16(0x3CBF, 1286);
      _memoryWrite16(0x3CC1, 0);
    case 0x3FB9:
      r16[bx] = _memoryRead16(0x3CC1);
      r8[cl] = memory[ofs(r16[bx] + 0x3cae)];
      r16[bx] = 0;
      r8[ch] = r8[bl];
    case 0x3FC5:
      _si = 0x3aea;
      yield* sub_2DFD();
      if (r8[dl] > 0x30)
      {
        _pc = 0x3FDB;
        continue;
      };
      _si = 0x3af8;
      if (r8[dl] & 0x04)
      {
        _pc = 0x3FDB;
        continue;
      };
      _si = 0x3b02;
    case 0x3FDB:
      _di = _memoryRead16(0x3CBF) + r16[bx];
      _push(r16[cx]);
      _push(r16[bx]);
      r16[cx] = 0x0801;
      yield* sub_2D9D();
      r16[bx] = _pop();
      r16[cx] = _pop();
      r16[bx] += 0x0002;
      if (--r16[cx])
      {
        _pc = 0x3FC5;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x3CBF), _memoryRead16(adr(_ds, 0x3CBF)) + 320);
      _memoryWrite16(adr(_ds, 0x3CC1), _memoryRead16(adr(_ds, 0x3CC1)) + 1);
      if (_memoryRead16(adr(_ds, 0x3CC1)) < 0x11)
      {
        _pc = 0x3FB9;
        continue;
      };
      r16[bx] = 0x3c22;
      r16[ax] = 0;
      yield* sub_2B24();
      r16[bx] = 0x3c3e;
      r16[ax] = 0;
      yield* sub_2B24();
      r16[bx] = 0x3c9a;
      r16[ax] = 0;
      yield* sub_2B24();
      r16[bx] = 0x3c56;
      r16[ax] = 0;
      yield* sub_2B24();
      _si = 0x3caa;
      _di = 0x08ec;
      r16[cx] = 0x0102;
      _bp = 0x0e;
      yield* sub_2D35();
      _si = 0;
      r16[bx] = _memoryRead16(0x8);
      r8[cl] = 0x03;
      r8[bl] = (r8[bl] & r8[cl]) << r8[cl];
      do {
        r8[al] = memory[ofs(r16[bx] + 0x3cc3)];
        r8[ah] = r8[al];
        r8[cl] = 0x04;
        r8[al] >>= r8[cl];
        memory[ofs(_si + 0x3ce3)] = r8[al];
        memory[ofs(_si + 0x3cf3)] = 0;
        r8[ah] &= 0x0f;
        memory[ofs(_si + 0x3ce4)] = r8[ah];
        memory[ofs(_si + 0x3cf4)] = 0;
        _si += 0x0002;
        r16[bx] += 1;
      } while (_si < 0x10);
      return;
  }
}

function* sub_4065()
{
  r16[ax] = _memoryRead16(0x327D);
  r8[dl] = memory[0x327F];
  _si = 0x10;
  r16[bx] = _memoryRead16(0x579);
  r8[dh] = memory[0x57B];
  _di = 0x18;
  r16[cx] = 0x0e1e;
  yield* sub_2E29();
}

function* sub_4090()
{
  r16[cx] = 0x0004;
  do {
    r16[bx] = r16[cx] - 1;
    _si = r16[bx] << 1;
    memory[ofs(r16[bx] + 0x3eae)] = 1;
    memory[ofs(r16[bx] + 0x3eb2)] = 0;
    yield* sub_4277();
    yield* sub_2DFD();
    r8[dl] = (r8[dl] & 0x0f) + 0x14;
    memory[ofs(r16[bx] + 0x3eb6)] = r8[dl];
  } while (--r16[cx]);
  _memoryWrite16(0x3EDA, 0);
  memory[0x3ED8] = 4;
}

function* sub_40C2()
{
  var _pc = 0x40C2;
  while (_pc != -1) switch(_pc)
  {
    case 0x40C2:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x3EDC)))
      {
        _pc = 0x40CD;
        continue;
      };
      return;
    case 0x40CD:
      _memoryWrite16(adr(_ds, 0x3EDA), _memoryRead16(adr(_ds, 0x3EDA)) + 1);
      r16[bx] = _memoryRead16(0x3EDA);
      if (r16[bx] <= 0x0002)
      {
        _pc = 0x40E5;
        continue;
      };
      if (r16[bx] < 0x0004)
      {
        _pc = 0x40E9;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x3EDA, r16[bx]);
    case 0x40E5:
      _memoryWrite16(0x3EDC, r16[dx]);
    case 0x40E9:
      _si = r16[bx] << 1;
      if (memory[adr(_ds, r16[bx] + 0x3eb2)] != 0)
        return;
      yield* sub_42DB();
      if (!flags.carry)
      {
        _pc = 0x40FC;
        continue;
      };
      {
        _pc = 0x4124;
        continue;
      };
    case 0x40FC:
      yield* sub_42FC();
      if (flags.carry)
        return;
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] != 0)
      {
        _pc = 0x4118;
        continue;
      };
      yield* sub_4277();
      yield* sub_2DFD();
      r8[dl] = (r8[dl] & 0x07) + 0x14;
      memory[ofs(r16[bx] + 0x3eb6)] = r8[dl];
    case 0x4118:
      memory[adr(_ds, r16[bx] + 0x3eb6)] -= 1;
      yield* sub_42DB();
      if (flags.carry)
      {
        _pc = 0x4124;
        continue;
      };
      {
        _pc = 0x4181;
        continue;
      };
    case 0x4124:
      if (memory[adr(_ds, r16[bx] + 0x3eae)] != 0)
        return;
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] < 0x14)
      {
        _pc = 0x4133;
        continue;
      };
      return;
    case 0x4133:
      yield* sub_11E3();
      yield* sub_4254();
      r16[bx] = _memoryRead16(0x3EDA);
      memory[ofs(r16[bx] + 0x3eb2)] = 1;
      yield* sub_1124();
      memory[0x55C] = 0;
      memory[adr(_ds, 0x3ED8)] -= 1;
      if (memory[adr(_ds, 0x3ED8)] != 0)
      {
        _pc = 0x4155;
        continue;
      };
      memory[0x553] = 1;
    case 0x4155:
      r8[al] = 0x04 - memory[adr(_ds, 0x3ED8)];
      r8[cl] = 0x02;
      r8[al] <<= r8[cl];
      r8[ah] = 0;
      r16[ax] += 0x51;
      _di = r16[ax];
      _bp = 0x0e;
      _si = 0x3d20;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0c02;
      yield* sub_2D35();
      r16[ax] = 0x03e8;
      r16[bx] = 0x02ee;
      yield* sub_593B();
      return;
    case 0x4181:
      yield* sub_42B4();
      _di = _memoryRead16(0x8) << 1;
      _bp = _memoryRead16(ofs(_di + 16094));
      yield* sub_431C();
      if (!flags.carry)
      {
        _pc = 0x41B0;
        continue;
      };
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] < 2)
      {
        _pc = 0x41B0;
        continue;
      };
      r8[al] = 0x01;
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] <= 0x11)
      {
        _pc = 0x41AC;
        continue;
      };
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] >= 0x14)
      {
        _pc = 0x41B0;
        continue;
      };
      r8[al] -= 1;
    case 0x41AC:
      memory[ofs(r16[bx] + 0x3eb6)] = r8[al];
    case 0x41B0:
      r8[al] = memory[ofs(r16[bx] + 0x3eb6)];
      if (r8[al] <= 0x01)
      {
        _pc = 0x41D8;
        continue;
      };
      if (r8[al] < 0x12)
      {
        _pc = 0x41F8;
        continue;
      };
      r8[al] = 0x01;
      if (_memoryRead16(adr(_ds, _si + 0x3eba)) >= 3)
      {
        _pc = 0x41C7;
        continue;
      };
      r8[al] = 0x03;
    case 0x41C7:
      memory[adr(_ds, r16[bx] + 0x3ed4)] += r8[al];
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] < 0x13)
      {
        _pc = 0x41F3;
        continue;
      };
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] == 0x13)
      {
        _pc = 0x41EE;
        continue;
      };
      r16[ax] = 0;
      {
        _pc = 0x4204;
        continue;
      };
    case 0x41D8:
      r8[al] = 0x01;
      if (_memoryRead16(adr(_ds, _si + 0x3eba)) >= 3)
      {
        _pc = 0x41E3;
        continue;
      };
      r8[al] = 0x03;
    case 0x41E3:
      memory[adr(_ds, r16[bx] + 0x3ed4)] += r8[al];
      if (memory[adr(_ds, r16[bx] + 0x3eb6)] >= 1)
      {
        _pc = 0x41F3;
        continue;
      };
    case 0x41EE:
      r16[ax] = 0x3db0;
      {
        _pc = 0x4204;
        continue;
      };
    case 0x41F3:
      r16[ax] = 0x3d80;
      {
        _pc = 0x4204;
        continue;
      };
    case 0x41F8:
      r8[al] <<= 1;
      _di = r16[ax] & 0x0002;
      r16[ax] = _memoryRead16(ofs(_di + 15840));
    case 0x4204:
      _memoryWrite16(0x3ECA, r16[ax]);
      r8[dl] = memory[ofs(r16[bx] + 0x3ed4)];
      r16[cx] = _memoryRead16(ofs(_si + 0x3ecc));
      yield* sub_2CB0();
      _memoryWrite16(0x3DE4, r16[ax]);
      yield* sub_4254();
      r16[bx] = _memoryRead16(0x3EDA);
      _si = r16[bx] << 1;
      yield* sub_42FC();
      if (!flags.carry)
      {
        _pc = 0x4226;
        continue;
      };
      return;
    case 0x4226:
      if (_memoryRead16(adr(_ds, 0x3ECA)) != 0)
      {
        _pc = 0x4233;
        continue;
      };
      memory[ofs(r16[bx] + 0x3eae)] = 1;
      return;
    case 0x4233:
      memory[ofs(r16[bx] + 0x3eae)] = 0;
      _di = _memoryRead16(0x3DE4);
      _memoryWrite16(ofs(_si + 0x3ea6), _di);
      r16[ax] = 0xb800;
      _es = r16[ax];
      _bp = _memoryRead16(ofs(_si + 0x3ec2));
      r16[cx] = 0x0c02;
      _si = _memoryRead16(0x3ECA);
      yield* sub_2D35();
      return;
  }
}

function* sub_4254()
{
  r16[bx] = _memoryRead16(0x3EDA);
  _si = r16[bx] << 1;
  if (memory[adr(_ds, r16[bx] + 0x3eae)] != 0)
    return;
  _di = _memoryRead16(ofs(_si + 0x3ea6));
  r16[cx] = 0x0c02;
  _si = _memoryRead16(ofs(_si + 0x3ec2));
  r16[ax] = 0xb800;
  _es = r16[ax];
  yield* sub_2D9D();
}

function* sub_4277()
{
  var _pc = 0x4277;
  while (_pc != -1) switch(_pc)
  {
    case 0x4277:
      memory[0x3ED9] = 0x20;
    case 0x427C:
      yield* sub_2DFD();
      r16[dx] &= 0x0f;
      _di = 0;
    case 0x4285:
      if (_di == _si)
      {
        _pc = 0x428F;
        continue;
      };
      if (r16[dx] == _memoryRead16(adr(_ds, _di + 16058)))
      {
        _pc = 0x427C;
        continue;
      };
    case 0x428F:
      _di += 0x0002;
      if (_di < 0x0008)
      {
        _pc = 0x4285;
        continue;
      };
      _memoryWrite16(ofs(_si + 0x3eba), r16[dx]);
      yield* sub_42B4();
      if (memory[adr(_ds, 0x3ED9)] == 0)
        return;
      _bp = 0x32;
      yield* sub_431C();
      if (!flags.carry)
        return;
      memory[adr(_ds, 0x3ED9)] -= 1;
      {
        _pc = 0x427C;
        continue;
      };
      return;
  }
}

function* sub_42B4()
{
  var _pc = 0x42B4;
  while (_pc != -1) switch(_pc)
  {
    case 0x42B4:
      _di = _memoryRead16(ofs(_si + 0x3eba));
      r8[al] = memory[ofs(_di + 4176)];
      r8[dl] = 0x0a;
      if (_di >= 0x0003)
      {
        _pc = 0x42C5;
        continue;
      };
      r8[dl] = 0;
    case 0x42C5:
      r8[al] = (r8[al] - r8[dl]) + 0x03;
      memory[ofs(r16[bx] + 0x3ed4)] = r8[al];
      _di <<= 1;
      r16[ax] = (_memoryRead16(ofs(_di + 4407))) + 0x0008;
      _memoryWrite16(ofs(_si + 0x3ecc), r16[ax]);
      return;
  }
}

function* sub_42DB()
{
  _push(_si);
  _push(r16[bx]);
  r16[ax] = _memoryRead16(ofs(_si + 0x3ecc));
  r8[dl] = memory[ofs(r16[bx] + 0x3ed4)];
  _si = 0x10;
  r16[bx] = _memoryRead16(0x579);
  r8[dh] = memory[0x57B];
  _di = 0x18;
  r16[cx] = 0x0e0c;
  yield* sub_2E29();
  r16[bx] = _pop();
  _si = _pop();
}

function* sub_42FC()
{
  _push(_si);
  _push(r16[bx]);
  r16[ax] = _memoryRead16(ofs(_si + 0x3ecc));
  r8[dl] = memory[ofs(r16[bx] + 0x3ed4)];
  _si = 0x10;
  r16[bx] = _memoryRead16(0x327D);
  r8[dh] = memory[0x327F];
  _di = _si;
  r16[cx] = 0x1e0c;
  yield* sub_2E29();
  r16[bx] = _pop();
  _si = _pop();
}

function* sub_431C()
{
  var _pc = 0x431C;
  while (_pc != -1) switch(_pc)
  {
    case 0x431C:
      r16[ax] = _memoryRead16(ofs(_si + 0x3ecc));
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x579));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x579));
      if (!flags.carry)
      {
        _pc = 0x4328;
        continue;
      };
      r16[ax] = (~r16[ax]);
    case 0x4328:
      r8[dl] = memory[ofs(r16[bx] + 0x3ed4)];
      flags.carry = r8[dl] < memory[adr(_ds, 0x57B)];
      r8[dl] = r8[dl] - memory[adr(_ds, 0x57B)];
      if (!flags.carry)
      {
        _pc = 0x4334;
        continue;
      };
      r8[dl] = (~r8[dl]);
    case 0x4334:
      r8[dh] = 0;
      r16[ax] += r16[dx];
      if (r16[ax] < _bp)
      {
        _pc = 0x433E;
        continue;
      };
      flags.carry = false;
      return;
    case 0x433E:
      flags.carry = true;
      return;
  }
}

function* sub_4340()
{
  var _pc = 0x4340;
  while (_pc != -1) switch(_pc)
  {
    case 0x4340:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x40B5)))
      {
        _pc = 0x434B;
        continue;
      };
      return;
    case 0x434B:
      memory[adr(_ds, 0x40FF)] += 1;
      if (!(memory[adr(_ds, 0x40FF)] & 3))
      {
        _pc = 0x435A;
        continue;
      };
      _memoryWrite16(0x40B5, r16[dx]);
    case 0x435A:
      if (memory[adr(_ds, 0x40AA)] < 0xa4)
        return;
      yield* sub_452D();
      yield* sub_4557();
      if (flags.carry)
        return;
      yield* sub_2DFD();
      if (r8[dl] > 0x30)
      {
        _pc = 0x439C;
        continue;
      };
      yield* sub_44FB();
      _si = _memoryRead16(0x8) << 1;
      r16[ax] = _memoryRead16(ofs(_si + 0x40ce));
      if (_memoryRead16(adr(_ds, 0x40CC)) > r16[ax])
      {
        _pc = 0x439C;
        continue;
      };
      yield* sub_595D();
      _memoryWrite16(0x40C8, 0xff);
      r8[al] = memory[0x40CA];
      memory[0x40B7] = r8[al];
      r8[al] = memory[0x40CB];
      memory[0x40B8] = r8[al];
      {
        _pc = 0x442E;
        continue;
      };
    case 0x439C:
      if (_memoryRead16(adr(_ds, 0x40C8)) > 0x0a)
      {
        _pc = 0x4402;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x06)
      {
        _pc = 0x43B4;
        continue;
      };
      _memoryWrite16(0x40C8, 0xff);
      {
        _pc = 0x4402;
        continue;
      };
    case 0x43B4:
      r16[bx] = _memoryRead16(0x40C8);
      _si = r16[bx] << 1;
      r8[dl] = 0;
      r16[ax] = _memoryRead16(0x40B2) & 0x0ffc;
      if (r16[ax] == _memoryRead16(adr(_ds, _si + 0x40de)))
      {
        _pc = 0x43D0;
        continue;
      };
      r8[dl] += 1;
      if (_char(r8[dl]) < 0)
      {
        _pc = 0x43D0;
        continue;
      };
      r8[dl] = 0xff;
    case 0x43D0:
      memory[0x40B7] = r8[dl];
      r8[dl] = 0;
      r8[al] = memory[0x40B4] & 0xfe;
      if (r8[al] == memory[adr(_ds, r16[bx] + 0x40f4)])
      {
        _pc = 0x43E7;
        continue;
      };
      r8[dl] += 1;
      if (_char(r8[dl]) < 0)
      {
        _pc = 0x43E7;
        continue;
      };
      r8[dl] = 0xff;
    case 0x43E7:
      memory[0x40B8] = r8[dl];
      r8[dl] = r8[dl] | memory[adr(_ds, 0x40B7)];
      if (r8[dl] != 0)
      {
        _pc = 0x442E;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x10)
      {
        _pc = 0x442E;
        continue;
      };
      _memoryWrite16(0x40C8, 0xff);
      yield* sub_595D();
    case 0x4402:
      yield* sub_2DFD();
      if (r8[dl] > 0x30)
      {
        _pc = 0x4423;
        continue;
      };
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x4411;
        continue;
      };
      r8[dl] = 0xff;
    case 0x4411:
      memory[0x40B7] = r8[dl];
      yield* sub_2DFD();
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x441F;
        continue;
      };
      r8[dl] = 0xff;
    case 0x441F:
      memory[0x40B8] = r8[dl];
    case 0x4423:
      yield* sub_2DFD();
      r16[dx] &= 0xff;
      _memoryWrite16(0x40C8, r16[dx]);
    case 0x442E:
      r8[al] = memory[0x40B4];
      if (memory[adr(_ds, 0x40B8)] < 1)
      {
        _pc = 0x4459;
        continue;
      };
      if (memory[adr(_ds, 0x40B8)] != 1)
      {
        _pc = 0x4449;
        continue;
      };
      r8[al] += 0x02;
      if (r8[al] < 0xa8)
      {
        _pc = 0x4456;
        continue;
      };
      r8[al] = 0xa7;
      memory[0x40B8] = 0xff;
      {
        _pc = 0x4456;
        continue;
      };
    case 0x4449:
      r8[al] -= 0x02;
      if (r8[al] >= 0x30)
      {
        _pc = 0x4456;
        continue;
      };
      r8[al] = 0x30;
      memory[0x40B8] = 1;
    case 0x4456:
      memory[0x40B4] = r8[al];
    case 0x4459:
      r16[ax] = _memoryRead16(0x40B2);
      if (memory[adr(_ds, 0x40B7)] < 1)
      {
        _pc = 0x4486;
        continue;
      };
      if (memory[adr(_ds, 0x40B7)] != 1)
      {
        _pc = 0x4477;
        continue;
      };
      r16[ax] += 0x0004;
      if (r16[ax] < 0x0136)
      {
        _pc = 0x4483;
        continue;
      };
      r16[ax] = 0x0135;
      memory[0x40B7] = 0xff;
      {
        _pc = 0x4483;
        continue;
      };
    case 0x4477:
      flags.carry = r16[ax] < 0x0004;
      r16[ax] -= 0x0004;
      if (!flags.carry)
      {
        _pc = 0x4483;
        continue;
      };
      r16[ax] = 0;
      memory[0x40B7] = 1;
    case 0x4483:
      _memoryWrite16(0x40B2, r16[ax]);
    case 0x4486:
      yield* sub_452D();
      r16[cx] = _memoryRead16(0x40B2);
      r8[dl] = memory[0x40B4];
      yield* sub_2CB0();
      _memoryWrite16(0x40BC, r16[ax]);
      r16[ax] = 0xb800;
      _es = r16[ax];
      if (memory[adr(_ds, 0x40B9)] != 0)
      {
        _pc = 0x44B0;
        continue;
      };
      _si = 0x3f2c;
      _di = _memoryRead16(0x40BA);
      r16[cx] = 0x0501;
      yield* sub_2D9D();
    case 0x44B0:
      yield* sub_4557();
      if (flags.carry)
        return;
      memory[0x40B9] = 0;
      _memoryWrite16(adr(_ds, 0x40BE), _memoryRead16(adr(_ds, 0x40BE)) + 2);
      r16[bx] = _memoryRead16(0x40BE) & 0x0006;
      _si = _memoryRead16(ofs(r16[bx] + 0x40c0));
      if (memory[adr(_ds, 0x40B7)] != 0xff)
      {
        _pc = 0x44D5;
        continue;
      };
      _si += 0x1e;
    case 0x44D5:
      _di = _memoryRead16(0x40BC);
      _memoryWrite16(0x40BA, _di);
      _bp = 0x3f2c;
      r16[cx] = 0x0501;
      yield* sub_2CCC();
      return;
  }
}

function* sub_44E7()
{
  var _pc = 0x44E7;
  while (_pc != -1) switch(_pc)
  {
    case 0x44E7:
      if (memory[adr(_ds, 0x571)] != 0)
      {
        _pc = 0x44F9;
        continue;
      };
      r8[al] = memory[0x57B] & 0xf8;
      if (r8[al] != 0x88)
      {
        _pc = 0x44F9;
        continue;
      };
      flags.carry = true;
      return;
    case 0x44F9:
      flags.carry = false;
      return;
  }
}

function* sub_44FB()
{
  var _pc = 0x44FB;
  while (_pc != -1) switch(_pc)
  {
    case 0x44FB:
      r16[ax] = _memoryRead16(0x40B2);
      r8[dl] = 0x01;
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x579));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x579));
      if (!flags.carry)
      {
        _pc = 0x450A;
        continue;
      };
      r16[ax] = (~r16[ax]);
      r8[dl] = 0xff;
    case 0x450A:
      memory[0x40CA] = r8[dl];
      _memoryWrite16(0x40CC, r16[ax]);
      r8[al] = memory[0x40B4];
      r8[dl] = 0x01;
      flags.carry = r8[al] < memory[adr(_ds, 0x57B)];
      r8[al] = r8[al] - memory[adr(_ds, 0x57B)];
      if (!flags.carry)
      {
        _pc = 0x4520;
        continue;
      };
      r8[al] = (~r8[al]);
      r8[dl] = 0xff;
    case 0x4520:
      memory[0x40CB] = r8[dl];
      r8[ah] = 0;
      r16[ax] <<= 1;
      _memoryWrite16(adr(_ds, 0x40CC), _memoryRead16(adr(_ds, 0x40CC)) + r16[ax]);
      return;
  }
}

function* sub_452D()
{
  r16[ax] = _memoryRead16(0x40B2);
  r8[dl] = memory[0x40B4];
  _si = 0x0008;
  r16[bx] = _memoryRead16(0x579);
  r8[dh] = memory[0x57B];
  _di = 0x18;
  r16[cx] = 0x0e05;
  yield* sub_2E29();
  if (!flags.carry)
    return;
  if (memory[adr(_ds, 0x552)] != 0)
    return;
  memory[0x553] = 1;
}

function* sub_4557()
{
  r16[ax] = _memoryRead16(0x40B2);
  r8[dl] = memory[0x40B4];
  _si = 0x0008;
  r16[bx] = _memoryRead16(0x327D);
  r8[dh] = memory[0x327F];
  _di = 0x10;
  r16[cx] = 0x1e05;
  yield* sub_2E29();
  if (!flags.carry)
    return;
  memory[0x40B8] = 0xff;
}

function* sub_457A()
{
  r16[cx] = 0x90;
  r8[dl] = 0x86;
  _memoryWrite16(0x40A8, r16[cx]);
  memory[0x40AA] = r8[dl];
  yield* sub_2CB0();
  _memoryWrite16(0x40AB, r16[ax]);
  yield* sub_4759();
  memory[0x40AF] = 0;
  memory[0x40B1] = 0;
  memory[0x40B9] = 1;
  memory[0x40B8] = 0;
  _memoryWrite16(0x40C8, 0xff);
}

function* sub_45AB()
{
  var _pc = 0x45AB;
  while (_pc != -1) switch(_pc)
  {
    case 0x45AB:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x40AD)))
      {
        _pc = 0x45B6;
        continue;
      };
      return;
    case 0x45B6:
      _memoryWrite16(0x40AD, r16[dx]);
      if (memory[adr(_ds, 0x40AA)] >= 0xa4)
        return;
      yield* sub_4786();
      if (!flags.carry)
      {
        _pc = 0x45D6;
        continue;
      };
      yield* sub_44E7();
      if (!flags.carry)
        return;
      memory[0x571] = 1;
      memory[0x55B] = 0x10;
      return;
    case 0x45D6:
      yield* sub_473E();
      if (!flags.carry)
      {
        _pc = 0x4649;
        continue;
      };
      if (memory[adr(_ds, 0x40AF)] != 0)
      {
        _pc = 0x45FA;
        continue;
      };
      r8[al] = memory[0x56E];
      if (r8[al] != 0x00)
      {
        _pc = 0x45F7;
        continue;
      };
      r8[al] += 1;
      r16[bx] = _memoryRead16(0x40A8);
      if (r16[bx] > _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x45F7;
        continue;
      };
      r8[al] = 0xff;
    case 0x45F7:
      memory[0x40B0] = r8[al];
    case 0x45FA:
      memory[0x40AF] = 1;
      r16[cx] = 0x20;
    case 0x4602:
      r16[ax] = _memoryRead16(0x579);
      r8[dl] = 0x01;
      if (memory[adr(_ds, 0x40B0)] != 1)
      {
        _pc = 0x4615;
        continue;
      };
      r16[ax] -= 0x0008;
      r8[dl] = 0xff;
      {
        _pc = 0x4618;
        continue;
      };
    case 0x4615:
      r16[ax] += 0x0008;
    case 0x4618:
      _memoryWrite16(0x579, r16[ax]);
      memory[0x56E] = r8[dl];
      r8[al] = memory[0x57B];
      if (memory[adr(_ds, 0x571)] < 1)
      {
        _pc = 0x4639;
        continue;
      };
      if (memory[adr(_ds, 0x571)] != 1)
      {
        _pc = 0x462F;
        continue;
      };
      r8[al] -= 0x03;
      {
        _pc = 0x4631;
        continue;
      };
    case 0x462F:
      r8[al] += 0x03;
    case 0x4631:
      memory[0x57B] = r8[al];
      r8[al] += 0x32;
      memory[0x57C] = r8[al];
    case 0x4639:
      _push(r16[cx]);
      yield* sub_473E();
      r16[cx] = _pop();
      if (!flags.carry)
      {
        _pc = 0x4642;
        continue;
      };
      if (--r16[cx])
      {
        _pc = 0x4602;
        continue;
      };
    case 0x4642:
      yield* sub_11E3();
      yield* sub_1112();
      return;
    case 0x4649:
      if (memory[adr(_ds, 0x40B1)] != 0)
      {
        _pc = 0x46A2;
        continue;
      };
      if (memory[adr(_ds, 0x40AF)] == 0)
        return;
      r16[ax] = _memoryRead16(0x40A8);
      if (memory[adr(_ds, 0x40B0)] != 1)
      {
        _pc = 0x4666;
        continue;
      };
      r16[ax] += 0x0008;
      {
        _pc = 0x4669;
        continue;
      };
    case 0x4666:
      r16[ax] -= 0x0008;
    case 0x4669:
      _memoryWrite16(0x40A8, r16[ax]);
      yield* sub_473E();
      if (!flags.carry)
      {
        _pc = 0x4672;
        continue;
      };
      return;
    case 0x4672:
      r16[ax] = 0x0c00;
      r16[bx] = 0x0b54;
      yield* sub_593B();
      memory[0x40AF] = 0;
      r16[cx] = _memoryRead16(0x40A8);
      r8[dl] = memory[0x40AA];
      yield* sub_2CB0();
      _memoryWrite16(0x40AB, r16[ax]);
      yield* sub_4773();
      yield* sub_4759();
      r16[ax] = _memoryRead16(0x40A8);
      if (r16[ax] < 0x78)
      {
        _pc = 0x46A2;
        continue;
      };
      if (r16[ax] > 0xa8)
      {
        _pc = 0x46A2;
        continue;
      };
      return;
    case 0x46A2:
      memory[0x40B1] = 1;
      if (memory[adr(_ds, 0x1CBF)] == 0)
      {
        _pc = 0x46BE;
        continue;
      };
      yield* sub_44E7();
      if (!flags.carry)
        return;
      memory[0x571] = 1;
      memory[0x55B] = 0x10;
      return;
    case 0x46BE:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] == _memoryRead16(adr(_ds, 0x40AD)))
      {
        _pc = 0x46A2;
        continue;
      };
      _memoryWrite16(0x40AD, r16[dx]);
      if (memory[adr(_ds, 0x0)] == 0)
      {
        _pc = 0x46EC;
        continue;
      };
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r8[al] = memory[0x40AA];
      r8[ah] = 0;
      r16[ax] = (r16[ax] << 1) << 1;
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
    case 0x46EC:
      r8[dl] = memory[0x40AA];
      if (r8[dl] >= 0xa4)
      {
        _pc = 0x470E;
        continue;
      };
      r8[dl] += 0x05;
      memory[0x40AA] = r8[dl];
      r16[cx] = _memoryRead16(0x40A8);
      yield* sub_2CB0();
      _memoryWrite16(0x40AB, r16[ax]);
      yield* sub_4773();
      yield* sub_4759();
      {
        _pc = 0x46BE;
        continue;
      };
    case 0x470E:
      yield* sub_5B21();
      yield* sub_4773();
      _bp = 0x401e;
      _memoryWrite16(adr(_ds, 0x40A6), _memoryRead16(adr(_ds, 0x40A6)) - 1);
      _di = _memoryRead16(0x40A6);
      _si = 0x3f36;
      r16[cx] = 0x1104;
      yield* sub_2D35();
      r16[ax] = _memoryRead16(0x40A8);
      _memoryWrite16(0x40B2, r16[ax]);
      r8[al] = memory[0x40AA];
      memory[0x40B4] = r8[al];
      yield* sub_44FB();
      r8[al] = memory[0x40CA];
      memory[0x40B7] = r8[al];
      return;
  }
}

function* sub_473E()
{
  r16[ax] = _memoryRead16(0x40A8);
  r8[dl] = memory[0x40AA];
  _si = 0x18;
  r16[bx] = _memoryRead16(0x579);
  r8[dh] = memory[0x57B];
  _di = _si;
  r16[cx] = 0x0e10;
  yield* sub_2E29();
}

function* sub_4759()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _bp = 0x401e;
  _si = 0x3fbe;
  _di = _memoryRead16(0x40AB);
  _memoryWrite16(0x40A6, _di);
  r16[cx] = 0x1003;
  yield* sub_2D35();
}

function* sub_4773()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _si = 0x401e;
  _di = _memoryRead16(0x40A6);
  r16[cx] = 0x1003;
  yield* sub_2D9D();
}

function* sub_4786()
{
  var _pc = 0x4786;
  while (_pc != -1) switch(_pc)
  {
    case 0x4786:
      if (memory[adr(_ds, 0x327F)] < 0x66)
      {
        _pc = 0x47A4;
        continue;
      };
      r16[ax] = _memoryRead16(0x40A8) - 0x14;
      if (r16[ax] > _memoryRead16(adr(_ds, 0x327D)))
      {
        _pc = 0x47A4;
        continue;
      };
      r16[ax] += 0x30;
      if (r16[ax] < _memoryRead16(adr(_ds, 0x327D)))
      {
        _pc = 0x47A4;
        continue;
      };
      flags.carry = true;
      return;
    case 0x47A4:
      flags.carry = false;
      return;
  }
}

function* sub_47B0()
{
  var _pc = 0x47B0;
  while (_pc != -1) switch(_pc)
  {
    case 0x47B0:
      r16[ax] = _memoryRead16(0x327D);
      r8[dl] = memory[0x327F];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      flags.carry = r16[bx] < 0x0008;
      r16[bx] -= 0x0008;
      if (!flags.carry)
      {
        _pc = 0x47C5;
        continue;
      };
      r16[bx] = 0;
    case 0x47C5:
      r8[dh] = memory[0x57B] + 0x03;
      _di = 0x28;
      r16[cx] = 0x0e1e;
      yield* sub_2E29();
      return;
  }
}

function* sub_47D6()
{
  var _pc = 0x47D6;
  while (_pc != -1) switch(_pc)
  {
    case 0x47D6:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x44D7));
      _si = _memoryRead16(0x8) << 1;
      if (r16[ax] > _memoryRead16(adr(_ds, _si + 0x44dc)))
      {
        _pc = 0x47ED;
        continue;
      };
      return;
    case 0x47ED:
      _memoryWrite16(0x44D7, r16[dx]);
      if (memory[adr(_ds, 0x1CB8)] != 0)
        return;
      memory[0x44FC] = 0;
      r16[cx] = 0x0c;
    case 0x4800:
      r16[bx] = r16[cx] - 1;
      r8[bl] <<= 1;
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4441)) == 0)
      {
        _pc = 0x487D;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x43f9));
      if (r8[al] != memory[adr(_ds, 0x57B)])
      {
        _pc = 0x485D;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x43e1));
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x579));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x579));
      if (!flags.carry)
      {
        _pc = 0x4822;
        continue;
      };
      r16[ax] = (~r16[ax]);
    case 0x4822:
      _si = _memoryRead16(0x8) << 1;
      if (r16[ax] > _memoryRead16(adr(_ds, _si + 0x44ec)))
      {
        _pc = 0x485D;
        continue;
      };
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4459)) < 2)
      {
        _pc = 0x484C;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4411));
      _memoryWrite16(0x44DA, r16[ax]);
      yield* sub_488D();
      yield* sub_48A1();
      yield* sub_3339();
      yield* sub_1145();
      yield* sub_2136();
      return;
    case 0x484C:
      _memoryWrite16(adr(_ds, r16[bx] + 0x4459), _memoryRead16(adr(_ds, r16[bx] + 0x4459)) + 1);
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4459)) < 2)
      {
        _pc = 0x4870;
        continue;
      };
      memory[adr(_ds, 0x44FC)] += 1;
      {
        _pc = 0x4870;
        continue;
      };
    case 0x485D:
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4459)) == 0)
      {
        _pc = 0x487D;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x38)
      {
        _pc = 0x4870;
        continue;
      };
      _memoryWrite16(adr(_ds, r16[bx] + 0x4459), _memoryRead16(adr(_ds, r16[bx] + 0x4459)) - 1);
    case 0x4870:
      _push(r16[cx]);
      _push(r16[bx]);
      yield* sub_48D7();
      r16[bx] = _pop();
      yield* sub_4916();
      yield* sub_48C1();
      r16[cx] = _pop();
    case 0x487D:
      if (--r16[cx])
      {
        _pc = 0x4800;
        continue;
      };
      if (memory[adr(_ds, 0x44FC)] == 0)
        return;
      yield* sub_5691();
      return;
      {
        _pc = 0x4800;
        continue;
      };
      return;
  }
}

function* sub_488D()
{
  var _pc = 0x488D;
  while (_pc != -1) switch(_pc)
  {
    case 0x488D:
      if (memory[adr(_ds, 0x44BD)] == 0)
      {
        _pc = 0x489D;
        continue;
      };
      yield* sub_4B03();
      memory[0x44BD] = 0;
      return;
    case 0x489D:
      yield* sub_11E3();
      return;
  }
}

function* sub_48A1()
{
  _push(_ds);
  _es = _pop();
  flags.direction = false;
  _di = 0x0e;
  _si = _di;
  r16[ax] = 0xaaaa;
  r16[cx] = 0x41;
  _rep_stosw_MemData_DirForward();
  r16[ax] = 0xb800;
  _es = r16[ax];
  _di = _memoryRead16(0x44DA);
  r16[cx] = 0x0d05;
  yield* sub_2D9D();
}

function* sub_48C1()
{
  var _pc = 0x48C1;
  while (_pc != -1) switch(_pc)
  {
    case 0x48C1:
      if (memory[adr(_ds, 0x44D9)] == 0)
        return;
      if (memory[adr(_ds, 0x44BD)] == 0)
      {
        _pc = 0x48D3;
        continue;
      };
      yield* sub_4B1D();
      return;
    case 0x48D3:
      yield* sub_1145();
      return;
  }
}

function* sub_48D7()
{
  var _pc = 0x48D7;
  while (_pc != -1) switch(_pc)
  {
    case 0x48D7:
      memory[0x44D9] = 0;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x43e1));
      r16[dx] = _memoryRead16(ofs(r16[bx] + 0x43f9));
      r16[ax] -= 0x14;
      _si = 0x28;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      r16[cx] = 0x0e06;
      _di = 0x18;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      memory[0x44D9] = 1;
      do {
        yield* sub_13D8();
      } while (r8[al] == 0);
      if (memory[adr(_ds, 0x44BD)] == 0)
      {
        _pc = 0x4912;
        continue;
      };
      yield* sub_4B03();
      return;
    case 0x4912:
      yield* sub_11E3();
      return;
  }
}

function* sub_4916()
{
  var _pc = 0x4916;
  while (_pc != -1) switch(_pc)
  {
    case 0x4916:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4411));
      _si = ((_memoryRead16(ofs(r16[bx] + 0x4459))) << 1) + 0x4100;
      r16[ax] += 0xa7;
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4429)) == 17052)
      {
        _pc = 0x4935;
        continue;
      };
      r16[ax] -= 0x0006;
      _si += 0x0006;
    case 0x4935:
      _di = r16[ax];
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0101;
      yield* sub_2D9D();
      return;
  }
}

function* sub_4943()
{
  var _pc = 0x4943;
  while (_pc != -1) switch(_pc)
  {
    case 0x4943:
      if (memory[adr(_ds, 0x1CB8)] != 0)
        return;
      if (memory[adr(_ds, 0x44BE)] == 0)
      {
        _pc = 0x495C;
        continue;
      };
      r8[al] = memory[0x44BE];
      memory[0x698] = r8[al];
      memory[0x699] = 0;
    case 0x495C:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x44D3)))
      {
        _pc = 0x4967;
        continue;
      };
      return;
    case 0x4967:
      _memoryWrite16(0x44D3, r16[dx]);
      if (memory[adr(_ds, 0x584)] == 0)
      {
        _pc = 0x4995;
        continue;
      };
      if (memory[adr(_ds, 0x44BD)] == 0)
        return;
      yield* sub_4B03();
      yield* sub_33A0();
      yield* sub_1124();
      yield* sub_3339();
      memory[0x44BD] = 0;
      memory[0x43E0] = 1;
      memory[0x44BE] = 0;
      return;
    case 0x4995:
      if (memory[adr(_ds, 0x69A)] == 0)
      {
        _pc = 0x499F;
        continue;
      };
      {
        _pc = 0x49F9;
        continue;
      };
    case 0x499F:
      r16[ax] = 0xffff;
      _memoryWrite16(0x44C1, r16[ax]);
      _memoryWrite16(0x44BF, r16[ax]);
      r16[cx] = 0x0c;
      _si = _memoryRead16(0x579);
      r8[dl] = memory[0x57B] + 0x08;
    case 0x49B6:
      r16[bx] = r16[cx] - 1;
      if (memory[adr(_ds, r16[bx] + 0x44c4)] < 1)
      {
        _pc = 0x49F0;
        continue;
      };
      if (r8[dl] != memory[adr(_ds, r16[bx] + 0x4499)])
      {
        _pc = 0x49F0;
        continue;
      };
      r16[ax] = _si;
      r8[bl] <<= 1;
      r8[dh] = 0xff;
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, r16[bx] + 0x4481));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, r16[bx] + 0x4481));
      if (!flags.carry)
      {
        _pc = 0x49D6;
        continue;
      };
      r16[ax] = (~r16[ax]);
      r8[dh] = 0x01;
    case 0x49D6:
      if (r16[ax] > _memoryRead16(adr(_ds, 0x44BF)))
      {
        _pc = 0x49F0;
        continue;
      };
      _memoryWrite16(0x44BF, r16[ax]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x44a5));
      _memoryWrite16(0x44D1, r16[ax]);
      r8[bl] >>= 1;
      _memoryWrite16(0x44C1, r16[bx]);
      memory[0x44C3] = r8[dh];
    case 0x49F0:
      if (--r16[cx])
      {
        _pc = 0x49B6;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x44C1)) < 0x0c)
      {
        _pc = 0x4A20;
        continue;
      };
    case 0x49F9:
      if (memory[adr(_ds, 0x44BD)] == 0)
      {
        _pc = 0x4A0B;
        continue;
      };
      yield* sub_4B03();
      yield* sub_1145();
      memory[0x69A] = 0x10;
    case 0x4A0B:
      memory[0x44BD] = 0;
      memory[0x43E0] = 1;
      memory[0x44D0] = 0;
      memory[0x44BE] = 0;
      return;
    case 0x4A20:
      if (_memoryRead16(adr(_ds, 0x44BF)) < 4)
      {
        _pc = 0x4A4B;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x44BF)) > 8)
      {
        _pc = 0x4A33;
        continue;
      };
      memory[0x572] = 4;
    case 0x4A33:
      r8[al] = memory[0x44C3];
      memory[0x698] = r8[al];
      memory[0x56E] = r8[al];
      memory[0x44BE] = r8[al];
      memory[0x699] = 0;
      memory[0x571] = 0;
      {
        _pc = 0x49F9;
        continue;
      };
    case 0x4A4B:
      memory[0x44BE] = 0;
      if (memory[adr(_ds, 0x44BD)] != 0)
      {
        _pc = 0x4A5D;
        continue;
      };
      yield* sub_11E3();
      yield* sub_1124();
    case 0x4A5D:
      memory[0x44BD] = 1;
      r8[al] = 0;
      flags.carry = (memory[adr(_ds, 0x44D0)] + 0x30) >= 0x100;
      memory[adr(_ds, 0x44D0)] += 0x30;
      if (!flags.carry)
      {
        _pc = 0x4A6D;
        continue;
      };
      r8[al] += 1;
    case 0x4A6D:
      memory[0x44D5] = r8[al];
      r16[cx] = _memoryRead16(0x579) & 0x0ffc;
      r8[dl] = memory[0x57B] + 0x03;
      if (_memoryRead16(adr(_ds, 0x44D1)) == 16652)
      {
        _pc = 0x4A95;
        continue;
      };
      r16[cx] += 0x0008;
      if (r16[cx] < 0x0127)
      {
        _pc = 0x4A9C;
        continue;
      };
      r16[cx] = 0x0126;
      {
        _pc = 0x4A9C;
        continue;
      };
    case 0x4A95:
      flags.carry = r16[cx] < 0x0008;
      r16[cx] -= 0x0008;
      if (!flags.carry)
      {
        _pc = 0x4A9C;
        continue;
      };
      r16[cx] = 0;
    case 0x4A9C:
      yield* sub_2CB0();
      _memoryWrite16(0x43DC, r16[ax]);
      do {
        yield* sub_13D8();
      } while (r8[al] == 0);
      yield* sub_4B03();
      if (memory[adr(_ds, 0x44D5)] == 0)
      {
        _pc = 0x4AFF;
        continue;
      };
      r16[bx] = _memoryRead16(0x44C1);
      if (memory[adr(_ds, r16[bx] + 0x44c4)] == 0)
      {
        _pc = 0x4AFF;
        continue;
      };
      memory[adr(_ds, r16[bx] + 0x44c4)] -= 1;
      if (memory[adr(_ds, r16[bx] + 0x44c4)] != 0)
      {
        _pc = 0x4AE7;
        continue;
      };
      _push(r16[bx]);
      r16[ax] = 0x08fd;
      r16[bx] = 0x0723;
      yield* sub_593B();
      r16[bx] = _pop();
      memory[0x698] = 0;
      memory[0x44BE] = 0;
      memory[0x69A] = 0x10;
      memory[adr(_ds, 0x44D6)] -= 1;
      if (memory[adr(_ds, 0x44D6)] != 0)
      {
        _pc = 0x4AE7;
        continue;
      };
      memory[0x553] = 1;
    case 0x4AE7:
      _push(r16[bx]);
      yield* sub_47B0();
      r16[bx] = _pop();
      if (!flags.carry)
      {
        _pc = 0x4AFC;
        continue;
      };
      _push(r16[bx]);
      yield* sub_33A0();
      r16[bx] = _pop();
      yield* sub_4BC8();
      yield* sub_3339();
      {
        _pc = 0x4AFF;
        continue;
      };
    case 0x4AFC:
      yield* sub_4BC8();
    case 0x4AFF:
      yield* sub_4B1D();
      return;
  }
}

function* sub_4B03()
{
  if (memory[adr(_ds, 0x43E0)] != 0)
    return;
  _di = _memoryRead16(0x43DE);
  _si = 0x43a0;
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[cx] = 0x0a03;
  yield* sub_2D9D();
}

function* sub_4B1D()
{
  var _pc = 0x4B1D;
  while (_pc != -1) switch(_pc)
  {
    case 0x4B1D:
      memory[0x43E0] = 0;
      r16[ax] = 0xb800;
      _es = r16[ax];
      _di = _memoryRead16(0x43DC);
      _memoryWrite16(0x43DE, _di);
      _bp = 0x43a0;
      _si = _memoryRead16(0x44D1);
      if (memory[adr(_ds, 0x44D0)] < 0x80)
      {
        _pc = 0x4B40;
        continue;
      };
      _si += 0x3c;
    case 0x4B40:
      r16[cx] = 0x0a03;
      yield* sub_2D35();
      return;
  }
}

function* sub_4B47()
{
  _push(_ds);
  _es = _pop();
  r16[ax] = 0;
  _di = 0x4441;
  r16[cx] = 0x0c;
  _rep_stosw_MemData_DirForward();
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[bx] = _memoryRead16(0x8);
  r8[cl] = memory[ofs(r16[bx] + 0x4471)];
  r8[ch] = 0;
  do {
    do {
      do {
        yield* sub_2DFD();
        r8[bl] = r8[dl];
        r16[bx] &= 0x1e;
      } while (r8[bl] >= 0x18);
    } while (_memoryRead16(adr(_ds, r16[bx] + 0x4441)) != 0);
    _memoryWrite16(ofs(r16[bx] + 0x4459), 0);
    _memoryWrite16(ofs(r16[bx] + 0x4441), 1);
    _push(r16[cx]);
    _si = _memoryRead16(ofs(r16[bx] + 0x4429));
    _di = _memoryRead16(ofs(r16[bx] + 0x4411));
    r16[cx] = 0x0d05;
    yield* sub_2D9D();
    r16[cx] = _pop();
  } while (--r16[cx]);
  r16[cx] = 0x0c;
  do {
    r16[bx] = r16[cx] - 1;
    _si = _memoryRead16(0x8);
    r8[dl] = memory[ofs(_si + 0x4479)];
    memory[ofs(r16[bx] + 0x44c4)] = r8[dl];
    _push(r16[cx]);
    yield* sub_4BC8();
    r16[cx] = _pop();
  } while (--r16[cx]);
  memory[0x44D0] = 0;
  memory[0x44BD] = 0;
  memory[0x43E0] = 1;
  memory[0x44D6] = 0x0c;
  memory[0x44BE] = 0;
}

function* sub_4BC8()
{
  yield* sub_4BE8();
  _di = r16[ax];
  r8[al] = memory[ofs(r16[bx] + 0x44c4)];
  r8[ah] = 0;
  r8[cl] = 0x05;
  r16[ax] = (r16[ax] << r8[cl]) + 0x41fc;
  _si = r16[ax];
  r16[cx] = 0x0802;
  r16[ax] = 0xb800;
  _es = r16[ax];
  yield* sub_2D9D();
}

function* sub_4BE8()
{
  _push(r16[bx]);
  r8[dl] = memory[ofs(r16[bx] + 0x4499)];
  r8[bl] <<= 1;
  r16[cx] = _memoryRead16(ofs(r16[bx] + 0x4481));
  yield* sub_2CB0();
  r16[bx] = _pop();
}

// class CIReturn
// class CIReturn
// class CIReturn
// class CIZeroArgOp
// class CIReturn
// class CIZeroArgOp
// class CIReturn
// class CIReturn
function* sub_4C10()
{
  var _pc = 0x4C10;
  while (_pc != -1) switch(_pc)
  {
    case 0x4C10:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x45B8)))
      {
        _pc = 0x4C1B;
        continue;
      };
      return;
    case 0x4C1B:
      _memoryWrite16(adr(_ds, 0x45B6), _memoryRead16(adr(_ds, 0x45B6)) + 1);
      r16[bx] = _memoryRead16(0x45B6);
      if (r16[bx] == 0x0001)
      {
        _pc = 0x4C38;
        continue;
      };
      if (r16[bx] == 0x0004)
      {
        _pc = 0x4C38;
        continue;
      };
      if (r16[bx] < 0x0007)
      {
        _pc = 0x4C3C;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x45B6, r16[bx]);
    case 0x4C38:
      _memoryWrite16(0x45B8, r16[dx]);
    case 0x4C3C:
      yield* sub_4FCD();
      yield* sub_502D();
      if (!flags.carry)
      {
        _pc = 0x4C45;
        continue;
      };
      return;
    case 0x4C45:
      if (_memoryRead16(adr(_ds, 0x454F)) == 0)
      {
        _pc = 0x4C8C;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x454F));
      r16[bx] = _memoryRead16(0x8);
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x45c7));
      if (_memoryRead16(adr(_ds, 0x45B6)) != 0)
      {
        _pc = 0x4C67;
        continue;
      };
      r16[ax] <<= 1;
    case 0x4C67:
      if (r16[dx] < r16[ax])
        return;
      _memoryWrite16(0x454F, 0);
      memory[0x454E] = 1;
      r16[ax] = 0x24;
      if (_memoryRead16(adr(_ds, 0x579)) > 0xa0)
      {
        _pc = 0x4C84;
        continue;
      };
      r16[ax] = 0x0108;
    case 0x4C84:
      _memoryWrite16(0x4548, r16[ax]);
      memory[0x454A] = 0;
    case 0x4C8C:
      yield* sub_4DD0();
      if (!flags.carry)
      {
        _pc = 0x4C99;
        continue;
      };
      r16[bx] = _memoryRead16(0x45B6);
      yield* sub_4FBB();
      return;
    case 0x4C99:
      if (memory[adr(_ds, 0x4553)] == 0)
      {
        _pc = 0x4CB8;
        continue;
      };
      memory[adr(_ds, 0x4553)] -= 1;
      if (memory[adr(_ds, 0x4553)] != 0)
      {
        _pc = 0x4D14;
        continue;
      };
      r8[dl] = 0x01;
      if (memory[adr(_ds, 0x454A)] == 0xff)
      {
        _pc = 0x4CB1;
        continue;
      };
      r8[dl] = 0xff;
    case 0x4CB1:
      memory[0x454A] = r8[dl];
      {
        _pc = 0x4D14;
        continue;
      };
    case 0x4CB8:
      r8[al] = memory[0x454B];
      if (r8[al] > memory[adr(_ds, 0x57B)])
      {
        _pc = 0x4D14;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x45B6)) != 6)
      {
        _pc = 0x4CCF;
        continue;
      };
      if (memory[adr(_ds, 0x57B)] < 0x28)
      {
        _pc = 0x4CDC;
        continue;
      };
    case 0x4CCF:
      yield* sub_2DFD();
      r16[bx] = _memoryRead16(0x8);
      if (r8[dl] > memory[adr(_ds, r16[bx] + 0x45bf)])
      {
        _pc = 0x4D14;
        continue;
      };
    case 0x4CDC:
      r8[dl] = 0;
      r16[ax] = _memoryRead16(0x4548) & 0x0ff8;
      r16[cx] = _memoryRead16(0x579) & 0x0ff8;
      if (r16[ax] == r16[cx])
      {
        _pc = 0x4CF6;
        continue;
      };
      r8[dl] = 0x01;
      if (r16[ax] < r16[cx])
      {
        _pc = 0x4CF6;
        continue;
      };
      r8[dl] = 0xff;
    case 0x4CF6:
      memory[0x454A] = r8[dl];
      if (memory[adr(_ds, 0x57B)] < 0x28)
      {
        _pc = 0x4D14;
        continue;
      };
      if (_memoryRead16(adr(_ds, 0x45B6)) != 6)
      {
        _pc = 0x4D14;
        continue;
      };
      r8[al] = 0x01;
      if (r8[dl] == 0xff)
      {
        _pc = 0x4D11;
        continue;
      };
      r8[al] = 0xff;
    case 0x4D11:
      memory[0x454A] = r8[al];
    case 0x4D14:
      _memoryWrite16(0x45BC, 8);
      if (memory[adr(_ds, 0x4553)] == 0)
      {
        _pc = 0x4D27;
        continue;
      };
      _memoryWrite16(0x45BC, 4);
    case 0x4D27:
      r16[ax] = _memoryRead16(0x4548);
      if (memory[adr(_ds, 0x454A)] >= 1)
      {
        _pc = 0x4D46;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x10)
      {
        _pc = 0x4DA1;
        continue;
      };
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x4D40;
        continue;
      };
      r8[dl] = 0xff;
    case 0x4D40:
      memory[0x454A] = r8[dl];
      {
        _pc = 0x4DA1;
        continue;
      };
    case 0x4D46:
      if (memory[adr(_ds, 0x454A)] != 1)
      {
        _pc = 0x4D60;
        continue;
      };
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x45BC));
      if (r16[ax] < 0x010b)
      {
        _pc = 0x4D78;
        continue;
      };
      r16[ax] = 0x010a;
      memory[0x454A] = 0xff;
      memory[0x4553] = 0;
      {
        _pc = 0x4D78;
        continue;
      };
    case 0x4D60:
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x45BC));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x45BC));
      if (flags.carry)
      {
        _pc = 0x4D6B;
        continue;
      };
      if (r16[ax] > 0x24)
      {
        _pc = 0x4D78;
        continue;
      };
    case 0x4D6B:
      r16[ax] = 0x25;
      memory[0x454A] = 1;
      memory[0x4553] = 0;
    case 0x4D78:
      _memoryWrite16(0x4548, r16[ax]);
      _memoryWrite16(adr(_ds, 0x4551), _memoryRead16(adr(_ds, 0x4551)) + 2);
      if (_memoryRead16(adr(_ds, 0x4551)) < 0x0c)
      {
        _pc = 0x4D8D;
        continue;
      };
      _memoryWrite16(0x4551, 0);
    case 0x4D8D:
      if (memory[adr(_ds, 0x4553)] != 0)
      {
        _pc = 0x4DA1;
        continue;
      };
      yield* sub_2DFD();
      if (r8[dl] > 0x08)
      {
        _pc = 0x4DA1;
        continue;
      };
      memory[0x454A] = 0;
    case 0x4DA1:
      r16[cx] = _memoryRead16(0x4548);
      r8[dl] = memory[0x454B];
      yield* sub_2CB0();
      _memoryWrite16(0x45BA, r16[ax]);
      yield* sub_502D();
      if (!flags.carry)
      {
        _pc = 0x4DB5;
        continue;
      };
      return;
    case 0x4DB5:
      yield* sub_4DD0();
      if (flags.carry)
      {
        _pc = 0x4DC8;
        continue;
      };
      yield* sub_4F4A();
      yield* sub_4F10();
      memory[0x45BE] = 0;
      yield* sub_4E75();
    case 0x4DC8:
      r16[bx] = _memoryRead16(0x45B6);
      yield* sub_4FBB();
      return;
  }
}

function* sub_4DD0()
{
  var _pc = 0x4DD0;
  while (_pc != -1) switch(_pc)
  {
    case 0x4DD0:
      r16[ax] = _memoryRead16(0x579);
      r8[dl] = memory[0x57B];
      _si = 0x18;
      _di = _si;
      r16[bx] = _memoryRead16(0x4548);
      r8[dh] = memory[0x454B];
      r16[cx] = 0x0c0e;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      if (_memoryRead16(adr(_ds, 0x45B6)) != 6)
      {
        _pc = 0x4E00;
        continue;
      };
      memory[0x553] = 1;
      yield* sub_11E3();
      yield* sub_4F4A();
      flags.carry = true;
      return;
    case 0x4E00:
      yield* sub_11E3();
      yield* sub_4F4A();
      yield* sub_1145();
      memory[0x55B] = 4;
      memory[0x571] = 1;
      memory[0x576] = 4;
      memory[0x578] = 8;
      memory[0x4553] = 4;
      r8[dl] = 0x01;
      r16[ax] = _memoryRead16(0x4548);
      if (r16[ax] > _memoryRead16(adr(_ds, 0x579)))
      {
        _pc = 0x4E2F;
        continue;
      };
      r8[dl] = 0xff;
    case 0x4E2F:
      memory[0x454A] = r8[dl];
      r16[ax] = 0x0ce4;
      r16[bx] = 0x123b;
      yield* sub_593B();
      flags.carry = true;
      return;
  }
}

function* sub_4E3E()
{
  var _pc = 0x4E3E;
  while (_pc != -1) switch(_pc)
  {
    case 0x4E3E:
      memory[0x45BE] = 1;
      r16[ax] = _memoryRead16(0x45B6);
      _push(r16[ax]);
      _memoryWrite16(0x45B6, 0);
    case 0x4E4D:
      r16[bx] = _memoryRead16(0x45B6);
      yield* sub_4FCD();
      if (_memoryRead16(adr(_ds, 0x454F)) != 0)
      {
        _pc = 0x4E65;
        continue;
      };
      yield* sub_4E75();
      r16[bx] = _memoryRead16(0x45B6);
      yield* sub_4FBB();
    case 0x4E65:
      _memoryWrite16(adr(_ds, 0x45B6), _memoryRead16(adr(_ds, 0x45B6)) + 1);
      if (_memoryRead16(adr(_ds, 0x45B6)) < 7)
      {
        _pc = 0x4E4D;
        continue;
      };
      r16[ax] = _pop();
      _memoryWrite16(0x45B6, r16[ax]);
      return;
  }
}

function* sub_4E75()
{
  var _pc = 0x4E75;
  while (_pc != -1) switch(_pc)
  {
    case 0x4E75:
      r16[cx] = 0x0008;
    case 0x4E78:
      r16[bx] = r16[cx] - 1;
      if (memory[adr(_ds, r16[bx] + 0x2b72)] == 0)
      {
        _pc = 0x4EA3;
        continue;
      };
      _push(r16[cx]);
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      r8[bl] <<= 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      _si = 0x18;
      _di = _si;
      r16[bx] = _memoryRead16(0x4548);
      r8[dh] = memory[0x454B];
      r16[cx] = 0x0c0f;
      yield* sub_2E29();
      r16[cx] = _pop();
      if (flags.carry)
      {
        _pc = 0x4EA6;
        continue;
      };
    case 0x4EA3:
      if (--r16[cx])
      {
        _pc = 0x4E78;
        continue;
      };
      return;
    case 0x4EA6:
      _push(r16[cx]);
      if (memory[adr(_ds, 0x45BE)] != 0)
      {
        _pc = 0x4EBB;
        continue;
      };
      yield* sub_11E3();
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x4EBB;
        continue;
      };
      yield* sub_622B();
    case 0x4EBB:
      yield* sub_4F4A();
      r16[cx] = _pop();
      r16[bx] = r16[cx] - 1;
      memory[ofs(r16[bx] + 0x2b72)] = 0;
      r8[dl] = memory[ofs(r16[bx] + 0x2b6a)];
      r8[bl] <<= 1;
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x2b5a));
      yield* sub_2CB0();
      _di = r16[ax];
      _si = 0x2b7a;
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[cx] = 0x0f03;
      yield* sub_2D9D();
      if (memory[adr(_ds, 0x45BE)] != 0)
      {
        _pc = 0x4EF8;
        continue;
      };
      if (memory[adr(_ds, 0x70F2)] == 0)
      {
        _pc = 0x4EF5;
        continue;
      };
      yield* sub_61FA();
    case 0x4EF5:
      yield* sub_1145();
    case 0x4EF8:
      r16[dx] = 0;
      if (_memoryRead16(adr(_ds, 0x45B6)) == 6)
      {
        _pc = 0x4F0B;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != 0x0000)
      {
        _pc = 0x4F0B;
        continue;
      };
      r16[dx] -= 1;
    case 0x4F0B:
      _memoryWrite16(0x454F, r16[dx]);
      return;
  }
}

function* sub_4F10()
{
  var _pc = 0x4F10;
  while (_pc != -1) switch(_pc)
  {
    case 0x4F10:
      memory[0x454E] = 0;
      _si = 0x4500;
      if (memory[adr(_ds, 0x454A)] == 0)
      {
        _pc = 0x4F3E;
        continue;
      };
      r16[bx] = _memoryRead16(0x4551);
      if (memory[adr(_ds, 0x4553)] == 0)
      {
        _pc = 0x4F30;
        continue;
      };
      r8[bl] = (r8[bl] & 0x02) + 0x0c;
    case 0x4F30:
      if (memory[adr(_ds, 0x454A)] != 0xff)
      {
        _pc = 0x4F3A;
        continue;
      };
      r16[bx] += 0x10;
    case 0x4F3A:
      _si = _memoryRead16(ofs(r16[bx] + 0x4a60));
    case 0x4F3E:
      _di = _memoryRead16(0x45BA);
      _memoryWrite16(0x454C, _di);
      yield* sub_4FDF();
      return;
  }
}

function* sub_4F4A()
{
  if (memory[adr(_ds, 0x454E)] != 0)
    return;
  _di = _memoryRead16(0x454C);
  yield* sub_5008();
}

function* sub_4F59()
{
  var _pc = 0x4F59;
  while (_pc != -1) switch(_pc)
  {
    case 0x4F59:
      _memoryWrite16(0x45B6, 0);
    case 0x4F5F:
      yield* sub_2DFD();
      r16[dx] = (r16[dx] & 0x7f) + 0x60;
      _memoryWrite16(0x4548, r16[dx]);
      memory[0x454A] = 0;
      memory[0x454E] = 1;
      _memoryWrite16(0x4551, 0);
      memory[0x4553] = 0;
      r16[dx] = 0;
      if (_memoryRead16(adr(_ds, 0x45B6)) != 0)
      {
        _pc = 0x4F95;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != 0x0000)
      {
        _pc = 0x4F95;
        continue;
      };
      r16[dx] -= 1;
    case 0x4F95:
      _memoryWrite16(0x454F, r16[dx]);
      r16[bx] = _memoryRead16(0x45B6);
      r8[al] = (memory[ofs(r16[bx] + 0x2bd4)]) + 0x03;
      memory[0x454B] = r8[al];
      yield* sub_4FBB();
      _memoryWrite16(adr(_ds, 0x45B6), _memoryRead16(adr(_ds, 0x45B6)) + 1);
      if (_memoryRead16(adr(_ds, 0x45B6)) < 7)
      {
        _pc = 0x4F5F;
        continue;
      };
      _memoryWrite16(0x45B6, 0);
      return;
  }
}

function* sub_4FBB()
{
  _push(_ds);
  _es = _pop();
  r8[bl] <<= 1;
  flags.direction = false;
  _di = _memoryRead16(ofs(r16[bx] + 0x45a8));
  _si = 0x4548;
  r16[cx] = 0x0c;
  _rep_movsb_MemData_MemData_DirForward();
}

function* sub_4FCD()
{
  _push(_ds);
  _es = _pop();
  r8[bl] <<= 1;
  flags.direction = false;
  _si = _memoryRead16(ofs(r16[bx] + 0x45a8));
  _di = 0x4548;
  r16[cx] = 0x0c;
  _rep_movsb_MemData_MemData_DirForward();
}

function* sub_4FDF()
{
  var _pc = 0x4FDF;
  while (_pc != -1) switch(_pc)
  {
    case 0x4FDF:
      r16[ax] = 0xb800;
      _es = r16[ax];
      flags.direction = false;
      r8[dh] = 0x0c;
    case 0x4FE7:
      r16[cx] = 0x0003;
      do {
        r16[bx] = _videoRead16(_esAssume(0xb800), _di);
        _lodsw_MemData_DirForward();
        r16[ax] |= r16[bx];
        _stosw_MemB800_DirForward();
      } while (--r16[cx]);
      _di = (_di - 0x0006) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x5003;
        continue;
      };
      _di += 0x50;
    case 0x5003:
      r8[dh] -= 1;
      if (r8[dh] != 0)
      {
        _pc = 0x4FE7;
        continue;
      };
      return;
  }
}

function* sub_5008()
{
  var _pc = 0x5008;
  while (_pc != -1) switch(_pc)
  {
    case 0x5008:
      r16[ax] = 0xb800;
      _es = r16[ax];
      flags.direction = false;
      r8[dh] = 0x0c;
      r16[ax] = 0x5555;
    case 0x5013:
      r16[cx] = 0x0003;
      _rep_stosw_MemB800_DirForward();
      _di = (_di - 0x0006) ^ 0x2000;
      if (_di & 0x2000)
      {
        _pc = 0x5028;
        continue;
      };
      _di += 0x50;
    case 0x5028:
      r8[dh] -= 1;
      if (r8[dh] != 0)
      {
        _pc = 0x5013;
        continue;
      };
      return;
  }
}

function* sub_502D()
{
  var _pc = 0x502D;
  while (_pc != -1) switch(_pc)
  {
    case 0x502D:
      if (memory[adr(_ds, 0x70F2)] != 0)
      {
        _pc = 0x5036;
        continue;
      };
      flags.carry = false;
      return;
    case 0x5036:
      r16[ax] = _memoryRead16(0x70F3);
      r8[dl] = memory[0x70F5];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x4548);
      r8[dh] = memory[0x454B];
      _di = 0x18;
      r16[cx] = 0x0c08;
      yield* sub_2E29();
      return;
  }
}

function* sub_5060()
{
  var _pc = 0x5060;
  while (_pc != -1) switch(_pc)
  {
    case 0x5060:
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[ax] = _memoryRead16(0x579);
      if (r16[ax] < 0x0117)
      {
        _pc = 0x5070;
        continue;
      };
      r16[ax] = 0x0116;
    case 0x5070:
      flags.carry = r16[ax] < 0x10;
      r16[ax] -= 0x10;
      if (!flags.carry)
      {
        _pc = 0x5077;
        continue;
      };
      r16[ax] = 0;
    case 0x5077:
      r16[ax] &= 0x0ff0;
      _memoryWrite16(0x579, r16[ax]);
      memory[0x57B] = 0x14;
      flags.carry = r16[ax] < 0x80;
      r16[ax] -= 0x80;
      if (!flags.carry)
      {
        _pc = 0x5089;
        continue;
      };
      r16[ax] = (~r16[ax]);
    case 0x5089:
      r8[cl] = 0x03;
      r16[ax] >>= r8[cl];
      if (r16[ax] <= 0x0d)
      {
        _pc = 0x5095;
        continue;
      };
      r16[ax] = 0x0d;
    case 0x5095:
      r16[ax] += 0x0002;
      _memoryWrite16(0x4D6A, r16[ax]);
      _memoryWrite16(0x4DD6, 0x0a);
    case 0x50A1:
      if (_memoryRead16(adr(_ds, 0x4DD6)) == 0x0a)
      {
        _pc = 0x50AB;
        continue;
      };
      yield* sub_5B63();
    case 0x50AB:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x4A80, r16[dx]);
      r16[ax] = _memoryRead16(0x579);
      r16[cx] = r16[ax] & 0x0ff0;
      if (r16[cx] != 0x80)
      {
        _pc = 0x50C6;
        continue;
      };
      r16[ax] = r16[cx];
      {
        _pc = 0x50D2;
        continue;
      };
    case 0x50C6:
      if (r16[cx] < 0x80)
      {
        _pc = 0x50CE;
        continue;
      };
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x4D6A));
      {
        _pc = 0x50D2;
        continue;
      };
    case 0x50CE:
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x4D6A));
    case 0x50D2:
      _memoryWrite16(0x579, r16[ax]);
      if (memory[adr(_ds, 0x57B)] < 0x54)
      {
        _pc = 0x50DD;
        continue;
      };
      return;
    case 0x50DD:
      memory[adr(_ds, 0x57B)] += 8;
      r16[cx] = _memoryRead16(0x579) + 0x0004;
      r8[dl] = memory[0x57B];
      yield* sub_2CB0();
      _di = r16[ax];
      _memoryWrite16(0x4DD8, _di);
      _si = 0x4b8a;
      _bp = 0x0e;
      r16[cx] = 0x2007;
      yield* sub_2CCC();
      _di = _memoryRead16(0x4DD8) + 0xf3;
      _si = 0x4a82;
      r16[cx] = 0x0d04;
      yield* sub_2D9D();
      if (_memoryRead16(adr(_ds, 0x4DD6)) != 0x0a)
      {
        _pc = 0x5120;
        continue;
      };
      yield* sub_572E();
      yield* sub_5B54();
    case 0x5120:
      do {
        yield* sub_5B63();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x4A80));
      } while (r16[dx] < _memoryRead16(adr(_ds, 0x4DD6)));
      if (_memoryRead16(adr(_ds, 0x4DD6)) != 0x0a)
      {
        _pc = 0x5141;
        continue;
      };
      yield* sub_38B0();
      r16[bx] = 0;
      r8[ah] = 0x0b;
      _interrupt(0x10);
    case 0x5141:
      _memoryWrite16(0x4DD6, 2);
      {
        _pc = 0x50A1;
        continue;
      };
      return;
  }
}

function* sub_514A()
{
  r16[cx] = 0x0003;
  do {
    r16[bx] = (0x0003 - r16[cx]) << 1;
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4da4));
    _memoryWrite16(0x4D6A, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4daa));
    _memoryWrite16(0x4D6C, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4d98));
    _memoryWrite16(0x4DCC, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4d9e));
    _memoryWrite16(0x4DCE, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4db0));
    _memoryWrite16(0x4DD0, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4db6));
    _memoryWrite16(0x4DD2, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4dbc));
    _memoryWrite16(0x4DD4, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4d92));
    _memoryWrite16(0x4DCA, r16[ax]);
    r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4dc2));
    _memoryWrite16(0x4DC8, r16[ax]);
    _push(r16[cx]);
    yield* sub_519B();
    r16[cx] = _pop();
  } while (--r16[cx]);
}

function* sub_519B()
{
  var _pc = 0x519B;
  while (_pc != -1) switch(_pc)
  {
    case 0x519B:
      r16[cx] = 0x0008;
      memory[0x4D91] = 1;
      do {
        _push(r16[cx]);
        yield* sub_5B63();
        r16[cx] = _pop();
        r16[bx] = (r16[cx] - 1) << 1;
        r16[ax] = _memoryRead16(0x4DCC);
        _memoryWrite16(ofs(r16[bx] + 0x4d4a), r16[ax]);
        r16[ax] = _memoryRead16(0x4DCE);
        _memoryWrite16(ofs(r16[bx] + 0x4d5a), r16[ax]);
      } while (--r16[cx]);
      r16[ax] = 0xb800;
      _es = r16[ax];
      memory[0x4D6E] = 0;
    case 0x51C7:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x4A80, r16[dx]);
      r16[cx] = 0x0008;
    case 0x51D2:
      _push(r16[cx]);
      yield* sub_5B63();
      r16[cx] = _pop();
      r16[bx] = (r16[cx] - 1) << 1;
      _push(r16[cx]);
      _push(r16[bx]);
      if (memory[adr(_ds, 0x4D91)] == 0)
      {
        _pc = 0x51EA;
        continue;
      };
      if (r16[cx] != 0x0008)
      {
        _pc = 0x5205;
        continue;
      };
    case 0x51EA:
      r16[cx] = _memoryRead16(ofs(r16[bx] + 0x4d4a));
      r16[dx] = _memoryRead16(ofs(r16[bx] + 0x4d5a));
      yield* sub_2CB0();
      _di = r16[ax];
      _si = _memoryRead16(0x4DCA);
      _bp = 0x0e;
      r16[cx] = _memoryRead16(0x4DD4);
      yield* sub_2CCC();
    case 0x5205:
      r16[bx] = _pop();
      r16[cx] = _pop();
      yield* sub_522A();
      if (--r16[cx])
      {
        _pc = 0x51D2;
        continue;
      };
      do {
        yield* sub_5B63();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x4A80));
      } while (r16[dx] < _memoryRead16(adr(_ds, 0x4DC8)));
      memory[0x4D91] = 0;
      if (memory[adr(_ds, 0x4D6E)] == 0)
      {
        _pc = 0x51C7;
        continue;
      };
      return;
  }
}

function* sub_522A()
{
  var _pc = 0x522A;
  while (_pc != -1) switch(_pc)
  {
    case 0x522A:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4d4a));
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4d6f)) < 1)
      {
        _pc = 0x525A;
        continue;
      };
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4d6f)) != 1)
      {
        _pc = 0x524A;
        continue;
      };
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x4D6A));
      if (r16[ax] <= _memoryRead16(adr(_ds, 0x4DD0)))
      {
        _pc = 0x5256;
        continue;
      };
      r16[ax] = _memoryRead16(0x4DD0);
      memory[adr(_ds, 0x4D6E)] += 1;
      {
        _pc = 0x5256;
        continue;
      };
    case 0x524A:
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x4D6A));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x4D6A));
      if (!flags.carry)
      {
        _pc = 0x5256;
        continue;
      };
      r16[ax] = 0;
      memory[adr(_ds, 0x4D6E)] += 1;
    case 0x5256:
      _memoryWrite16(ofs(r16[bx] + 0x4d4a), r16[ax]);
    case 0x525A:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x4d5a));
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4d7f)) < 1)
        return;
      if (_memoryRead16(adr(_ds, r16[bx] + 0x4d7f)) != 1)
      {
        _pc = 0x527A;
        continue;
      };
      r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x4D6C));
      if (r16[ax] <= _memoryRead16(adr(_ds, 0x4DD2)))
      {
        _pc = 0x5286;
        continue;
      };
      r16[ax] = _memoryRead16(0x4DD2);
      memory[adr(_ds, 0x4D6E)] += 1;
      {
        _pc = 0x5286;
        continue;
      };
    case 0x527A:
      flags.carry = r16[ax] < _memoryRead16(adr(_ds, 0x4D6C));
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x4D6C));
      if (!flags.carry)
      {
        _pc = 0x5286;
        continue;
      };
      r16[ax] = 0;
      memory[adr(_ds, 0x4D6E)] += 1;
    case 0x5286:
      _memoryWrite16(ofs(r16[bx] + 0x4d5a), r16[ax]);
      return;
  }
}

function* sub_528B()
{
  var _pc = 0x528B;
  while (_pc != -1) switch(_pc)
  {
    case 0x528B:
      yield* sub_5B54();
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x529C;
        continue;
      };
      r8[ah] = 0x0b;
      r16[bx] = 0x0101;
      _interrupt(0x10);
    case 0x529C:
      yield* sub_5060();
      yield* sub_514A();
      yield* sub_5BBF();
      if (memory[adr(_ds, 0x1F80)] >= 9)
      {
        _pc = 0x52B0;
        continue;
      };
      memory[adr(_ds, 0x1F80)] += 1;
    case 0x52B0:
      if (_memoryRead16(adr(_ds, 0x8)) >= 7)
      {
        _pc = 0x52BB;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x8), _memoryRead16(adr(_ds, 0x8)) + 1);
    case 0x52BB:
      _memoryWrite16(0x414, 0);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x412, r16[dx]);
      yield* sub_5B21();
      return;
  }
}

function* sub_52D0()
{
  var _pc = 0x52D0;
  while (_pc != -1) switch(_pc)
  {
    case 0x52D0:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] == _memoryRead16(adr(_ds, 0x52C4)))
        return;
      _memoryWrite16(0x52C4, r16[dx]);
      r16[bx] = _memoryRead16(0x52C6);
      _memoryWrite16(adr(_ds, 0x52C6), _memoryRead16(adr(_ds, 0x52C6)) + 2);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x52ca));
      if (r16[ax] != _memoryRead16(adr(_ds, 0x52C8)))
      {
        _pc = 0x52FC;
        continue;
      };
      yield* sub_5B21();
      return;
    case 0x52FC:
      _memoryWrite16(0x52C8, r16[ax]);
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _memoryRead16(0x52C8);
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5313()
{
  if (_memoryRead16(adr(_ds, 0x8)) < 2)
    return;
  _memoryWrite16(0x5016, 0);
  r8[ah] = 0;
  _interrupt(0x1a);
  _memoryWrite16(0x52C0, r16[dx]);
  _memoryWrite16(0x52C2, r16[dx]);
  _memoryWrite16(0x52C4, r16[dx]);
  _memoryWrite16(0x52C6, 0);
  _memoryWrite16(0x52C8, 0);
  do {
    yield* sub_5368();
    _memoryWrite16(adr(_ds, 0x5016), _memoryRead16(adr(_ds, 0x5016)) ^ 2);
    do {
      yield* sub_52D0();
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x52C0));
    } while (r16[ax] < 0x0005);
    _memoryWrite16(0x52C0, r16[dx]);
    r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x52C2));
  } while (r16[dx] < 0x28);
  yield* sub_5B21();
}

function* sub_5368()
{
  var _pc = 0x5368;
  while (_pc != -1) switch(_pc)
  {
    case 0x5368:
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[bx] = _memoryRead16(0x8) << 1;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x52ae));
      _memoryWrite16(0x5010, r16[ax]);
    case 0x537A:
      r16[bx] = _memoryRead16(0x5010);
      _di = _memoryRead16(ofs(r16[bx]));
      if (_di != 0x0000)
      {
        _pc = 0x5386;
        continue;
      };
      return;
    case 0x5386:
      r16[bx] = ((_memoryRead16(ofs(r16[bx] + 0x2))) ^ _memoryRead16(adr(_ds, 0x5016))) & 0x0002;
      _si = _memoryRead16(ofs(r16[bx] + 0x5012));
      r16[cx] = 0x2304;
      yield* sub_2D9D();
      yield* sub_52D0();
      _memoryWrite16(adr(_ds, 0x5010), _memoryRead16(adr(_ds, 0x5010)) + 4);
      {
        _pc = 0x537A;
        continue;
      };
      return;
  }
}

function* sub_53B0()
{
  var _pc = 0x53B0;
  while (_pc != -1) switch(_pc)
  {
    case 0x53B0:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] == _memoryRead16(adr(_ds, 0x5322)))
        return;
      _memoryWrite16(0x5322, r16[dx]);
      r16[bx] = _memoryRead16(0x5320);
      r8[bl] = memory[ofs(r16[bx] + 0x538c)];
      if (r8[bl] == 0x66)
      {
        _pc = 0x53DD;
        continue;
      };
      r8[bh] = 0;
      _memoryWrite16(adr(_ds, 0x5320), _memoryRead16(adr(_ds, 0x5320)) + 1);
      if (r16[bx] != 0x0000)
      {
        _pc = 0x53E1;
        continue;
      };
    case 0x53DD:
      yield* sub_5B21();
      return;
    case 0x53E1:
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5324));
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5400()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[bx] = (_memoryRead16(0x8) & 0x0007) << 1;
  r16[ax] = r16[bx];
  r16[bx] = _memoryRead16(ofs(r16[bx] + 0x5908));
  r8[cl] = 0x03;
  r16[ax] <<= r8[cl];
  _memoryWrite16(0x5918, r16[ax]);
  do {
    _di = _memoryRead16(ofs(r16[bx]));
    if (_di == 0xffff)
      return;
    yield* sub_2DFD();
    r16[dx] = (r16[dx] & 0x0e) + _memoryRead16(adr(_ds, 0x5918));
    _si = _memoryRead16(ofs(r16[dx] + 0x5888));
    r16[cx] = _memoryRead16(ofs(_si + 0x5858));
    _si = _memoryRead16(ofs(_si + 0x584c));
    _push(r16[bx]);
    yield* sub_2D9D();
    r16[bx] = _pop();
    r16[bx] += 0x0002;
  } while (true);
}

function* sub_5450()
{
  memory[0x5B0F] = 0x0c;
  _memoryWrite16(0x5B0C, 1);
  _memoryWrite16(0x5B12, 511);
  _memoryWrite16(0x5B0A, 0x0f);
  memory[0x5B0E] = 1;
}

function* sub_546D()
{
  var _pc = 0x546D;
  while (_pc != -1) switch(_pc)
  {
    case 0x546D:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      if (memory[adr(_ds, 0x1CB8)] == 0)
      {
        _pc = 0x54F8;
        continue;
      };
      r8[ah] = 0;
      _interrupt(0x1a);
      if (memory[adr(_ds, 0x5B0F)] != 0)
      {
        _pc = 0x54A6;
        continue;
      };
      if (r16[dx] == _memoryRead16(adr(_ds, 0x5B10)))
        return;
      _memoryWrite16(0x5B10, r16[dx]);
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = (_memoryRead16(0x5B12) & 0x01ff) + 0xc8;
      yield* sub_5889();
      _memoryWrite16(adr(_ds, 0x5B12), _memoryRead16(adr(_ds, 0x5B12)) - 0x4b);
      return;
    case 0x54A6:
      if (r16[dx] == _memoryRead16(adr(_ds, 0x5B10)))
      {
        _pc = 0x54B4;
        continue;
      };
      _memoryWrite16(0x5B10, r16[dx]);
      memory[adr(_ds, 0x5B0F)] -= 1;
    case 0x54B4:
      memory[adr(_ds, 0x5B0E)] -= 1;
      if (memory[adr(_ds, 0x5B0E)] != 0)
        return;
      r8[al] = 0x01;
      if (memory[adr(_ds, 0x697)] == 0xfd)
      {
        _pc = 0x54C5;
        continue;
      };
      r8[al] <<= 1;
    case 0x54C5:
      memory[0x5B0E] = r8[al];
      yield* sub_2DFD();
      if (r8[dl] > 0x04)
      {
        _pc = 0x54D4;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x5B0C), _memoryRead16(adr(_ds, 0x5B0C)) + 1);
    case 0x54D4:
      if (!(_memoryRead16(adr(_ds, 0x5B0C)) & 1))
      {
        _pc = 0x54E1;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x5B0A), _memoryRead16(adr(_ds, 0x5B0A)) + 7);
    case 0x54E1:
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      yield* sub_2DFD();
      r16[ax] = ((r16[dx] & _memoryRead16(adr(_ds, 0x5B0A))) & 0x01ff) + 0x0190;
      yield* sub_5889();
      return;
    case 0x54F8:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (memory[adr(_ds, 0x5920)] == 0)
      {
        _pc = 0x5522;
        continue;
      };
      if (r16[dx] == _memoryRead16(adr(_ds, 0x5921)))
        return;
      _memoryWrite16(0x5921, r16[dx]);
      memory[adr(_ds, 0x5920)] -= 1;
      if (memory[adr(_ds, 0x5920)] == 0)
      {
        _pc = 0x551E;
        continue;
      };
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _memoryRead16(0x5923);
      yield* sub_5889();
      return;
    case 0x551E:
      yield* sub_5B21();
      return;
    case 0x5522:
      if (r16[dx] == _memoryRead16(adr(_ds, 0x5925)))
        return;
      _si = 0x0003;
      r8[al] = memory[0x1CBF] | memory[adr(_ds, 0x5B07)];
      if (r8[al] != 0)
      {
        _pc = 0x5549;
        continue;
      };
      _si = 0x0001;
      if (_memoryRead16(adr(_ds, 0x4)) != 0)
      {
        _pc = 0x5549;
        continue;
      };
      _si -= 1;
      if (memory[adr(_ds, 0x1673)] == 0)
      {
        _pc = 0x5549;
        continue;
      };
      _si = 0x0002;
    case 0x5549:
      _di = _si << 1;
      r8[al] = memory[0x584] | memory[adr(_ds, 0x5B07)];
      if (r8[al] != 0)
      {
        _pc = 0x5563;
        continue;
      };
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x5925));
      if (r16[ax] >= _memoryRead16(adr(_ds, _di + 23026)))
      {
        _pc = 0x5563;
        continue;
      };
      return;
    case 0x5563:
      _memoryWrite16(0x5925, r16[dx]);
      if (memory[adr(_ds, 0x1CBF)] != 0)
      {
        _pc = 0x5579;
        continue;
      };
      if (memory[adr(_ds, 0x5B07)] == 0)
      {
        _pc = 0x559E;
        continue;
      };
      memory[adr(_ds, 0x5B07)] -= 1;
    case 0x5579:
      _memoryWrite16(0x592E, 4608);
      r16[bx] = _memoryRead16(0x59BA);
      if (r16[bx] < 0x0006)
      {
        _pc = 0x558E;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x59BA, r16[bx]);
    case 0x558E:
      _memoryWrite16(adr(_ds, 0x59BA), _memoryRead16(adr(_ds, 0x59BA)) + 2);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a44));
      _memoryWrite16(0x592A, r16[ax]);
      yield* sub_5B28();
      return;
    case 0x559E:
      if (_si != 0x0002)
      {
        _pc = 0x55BB;
        continue;
      };
      r8[al] = memory[0x1673];
      r8[ah] = 0;
      r8[cl] = 0x04;
      r16[ax] = (r16[ax] << r8[cl]) + 0x0200;
      _memoryWrite16(0x592A, r16[ax]);
      _memoryWrite16(0x592E, 6144);
      {
        _pc = 0x568D;
        continue;
      };
    case 0x55BB:
      r16[ax] = _memoryRead16(ofs(_di + 23042));
      _memoryWrite16(0x592E, r16[ax]);
      flags.carry = memory[adr(_ds, 0x5927)] & 1;
      memory[adr(_ds, 0x5927)] >>= 1;
      if (!flags.carry)
      {
        _pc = 0x5623;
        continue;
      };
      _memoryWrite16(0x592E, 4096);
      memory[0x5927] = 0x80;
      memory[adr(_ds, 0x5928)] += 1;
      r8[al] = memory[0x5928] & memory[adr(_ds, _si + 0x59fa)];
      if (r8[al] != 0)
      {
        _pc = 0x5616;
        continue;
      };
      r8[dl] = memory[ofs(_si + 0x5a0a)];
      memory[adr(_ds, 0x5929)] += r8[dl];
      yield* sub_2DFD();
      if (r8[dl] > memory[adr(_ds, _si + 0x5a0c)])
      {
        _pc = 0x55F8;
        continue;
      };
      r8[dl] &= 0x07;
      memory[0x592D] = r8[dl];
    case 0x55F8:
      yield* sub_2DFD();
      r16[dx] = (r16[dx] & 0xff) << 1;
      r8[cl] = 0x01;
      if (!(r8[dl] & 0x02))
      {
        _pc = 0x560E;
        continue;
      };
      r8[cl] = 0xff;
      r16[dx] += 0x0300;
    case 0x560E:
      _memoryWrite16(0x592A, r16[dx]);
      memory[0x592C] = r8[cl];
    case 0x5616:
      r8[ah] = memory[0x5929] & memory[adr(_ds, _si + 0x59fc)];
      r8[al] |= r8[ah];
      memory[0x5928] = r8[al];
    case 0x5623:
      if (memory[adr(_ds, 0x592C)] == 0xff)
      {
        _pc = 0x5640;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x5A54), _memoryRead16(adr(_ds, 0x5A54)) + 2);
      r16[bx] = _memoryRead16(0x5A54) & 0x0e;
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a44));
      _memoryWrite16(0x592A, r16[ax]);
      {
        _pc = 0x5653;
        continue;
      };
    case 0x5640:
      if (_memoryRead16(adr(_ds, 0x592A)) > 0xc8)
      {
        _pc = 0x564E;
        continue;
      };
      _memoryWrite16(0x592A, 1280);
    case 0x564E:
      _memoryWrite16(adr(_ds, 0x592A), _memoryRead16(adr(_ds, 0x592A)) - 0x19);
    case 0x5653:
      if (memory[adr(_ds, 0x584)] == 0)
      {
        _pc = 0x5667;
        continue;
      };
      _memoryWrite16(0x592E, 8192);
      memory[0x592C] = 0xff;
      if (memory[adr(_ds, 0x584)] != 0)
      {
        _pc = 0x568D;
        continue;
      };
    case 0x5667:
      r8[bl] = memory[0x5928];
      r8[bh] = 0;
      r16[bx] = r16[bx] + _memoryRead16(adr(_ds, _di + 23038));
      r8[al] = (memory[ofs(r16[bx] + 0x59c2)]) & memory[adr(_ds, 0x5927)];
      if (r8[al] != 0)
      {
        _pc = 0x568D;
        continue;
      };
      if (memory[adr(_ds, 0x592D)] == 0)
        return;
      memory[adr(_ds, 0x592D)] -= 1;
      r16[ax] = _memoryRead16(ofs(_di + 23046));
      _memoryWrite16(0x592E, r16[ax]);
    case 0x568D:
      yield* sub_5B28();
      return;
  }
}

function* sub_5691()
{
  var _pc = 0x5691;
  while (_pc != -1) switch(_pc)
  {
    case 0x5691:
      yield* sub_5B21();
      r8[ah] = 0x0b;
      r16[bx] = 0x0004;
      _interrupt(0x10);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x5AE2, r16[dx]);
      _memoryWrite16(0x5AE4, 0);
      r8[al] = 0x02;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x56B4;
        continue;
      };
      r8[al] >>= 1;
    case 0x56B4:
      memory[0x5B06] = r8[al];
    case 0x56B7:
      if (memory[adr(_ds, 0x0)] == 0)
      {
        _pc = 0x56D8;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x5AE4), _memoryRead16(adr(_ds, 0x5AE4)) + 1);
      r16[bx] = _memoryRead16(0x5AE4);
      r8[cl] = memory[0x5B06];
      r16[bx] = (r16[bx] >> r8[cl]) & 0x1f;
      r8[al] = _in(0x61);
      r8[al] = r8[al] ^ memory[adr(_ds, r16[bx] + 0x5ae6)];
      _out(0x61, r8[al]);
    case 0x56D8:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x5AE2));
      if (r16[dx] < 0x0002)
      {
        _pc = 0x56B7;
        continue;
      };
      r8[ah] = 0x0b;
      r16[bx] = 0;
      _interrupt(0x10);
      memory[0x5B07] = 0x0c;
      yield* sub_5B21();
      return;
  }
}

function* sub_56F4()
{
  var _pc = 0x56F4;
  while (_pc != -1) switch(_pc)
  {
    case 0x56F4:
      r16[ax] = 0x0200;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x5700;
        continue;
      };
      r16[ax] <<= 1;
    case 0x5700:
      _memoryWrite16(0x5AD0, r16[ax]);
      return;
  }
}

function* sub_5704()
{
  _memoryWrite16(adr(_ds, 0x5AD0), _memoryRead16(adr(_ds, 0x5AD0)) + 1);
  r16[bx] = _memoryRead16(0x5AD0);
  r16[dx] = r16[bx];
  r8[cl] = 0x09;
  r16[dx] >>= r8[cl];
  r8[cl] = r8[dl] & 0x0f;
  r16[bx] = (r16[bx] >> r8[cl]) & 0x0f;
  r8[dl] = (memory[ofs(r16[bx] + 0x5ad2)]) & memory[adr(_ds, 0x0)];
  r8[al] = _in(0x61);
  r8[al] = (r8[al] & 0xfc) | r8[dl];
  _out(0x61, r8[al]);
}

function* sub_572E()
{
  _memoryWrite16(0x5ACB, 500);
  do {
    yield* sub_576E();
    _memoryWrite16(adr(_ds, 0x5ACB), _memoryRead16(adr(_ds, 0x5ACB)) - 0x1e);
  } while (_memoryRead16(adr(_ds, 0x5ACB)) > 0xc8);
  _memoryWrite16(0x5ACB, 500);
  do {
    yield* sub_576E();
    _memoryWrite16(adr(_ds, 0x5ACB), _memoryRead16(adr(_ds, 0x5ACB)) - 0x14);
  } while (_memoryRead16(adr(_ds, 0x5ACB)) > 300);
  do {
    yield* sub_576E();
    _memoryWrite16(adr(_ds, 0x5ACB), _memoryRead16(adr(_ds, 0x5ACB)) + 0x1e);
  } while (_memoryRead16(adr(_ds, 0x5ACB)) < 800);
  yield* sub_5B21();
}

function* sub_576E()
{
  var _pc = 0x576E;
  while (_pc != -1) switch(_pc)
  {
    case 0x576E:
      r16[cx] = 0x1000;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x577A;
        continue;
      };
      r16[cx] >>= 1;
    case 0x577A:
      _Sleep(r16[cx]);
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _memoryRead16(0x5ACB);
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5797()
{
  yield* sub_5B21();
  memory[0x5ACF] = 0;
  _memoryWrite16(0x5ACD, 8);
}

function* sub_57A6()
{
  var _pc = 0x57A6;
  while (_pc != -1) switch(_pc)
  {
    case 0x57A6:
      memory[adr(_ds, 0x5ACF)] += 1;
      r8[dl] = 0;
      r8[al] = memory[0x5ACF] & 0x3f;
      if (r8[al] != 0)
      {
        _pc = 0x57B7;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x5ACD), _memoryRead16(adr(_ds, 0x5ACD)) + 1);
    case 0x57B7:
      r16[bx] = _memoryRead16(0x5ACD);
      r8[cl] = 0x02;
      r16[bx] >>= r8[cl];
      r8[bl] &= 0x1f;
      if (r8[al] < r8[bl])
      {
        _pc = 0x57C8;
        continue;
      };
      r8[dl] = 0x02;
    case 0x57C8:
      r8[dl] = r8[dl] & memory[adr(_ds, 0x0)];
      r8[al] = _in(0x61);
      r8[al] = (r8[al] & 0xfd) | r8[dl];
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_57D5()
{
  _memoryWrite16(0x5A85, 0);
  r8[ah] = 0;
  _interrupt(0x1a);
  _memoryWrite16(0x5A83, r16[dx]);
}

function* sub_57E4()
{
  var _pc = 0x57E4;
  while (_pc != -1) switch(_pc)
  {
    case 0x57E4:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x5A83));
      if (r16[ax] < 0x0002)
        return;
      _memoryWrite16(0x5A83, r16[dx]);
      r16[bx] = _memoryRead16(0x5A85);
      _memoryWrite16(adr(_ds, 0x5A85), _memoryRead16(adr(_ds, 0x5A85)) + 2);
      if (memory[adr(_ds, 0x552)] == 0)
      {
        _pc = 0x581B;
        continue;
      };
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5aa3));
      if (r16[ax] != 0x0000)
      {
        _pc = 0x581F;
        continue;
      };
      yield* sub_5B21();
      return;
    case 0x581B:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a87));
    case 0x581F:
      _push(r16[ax]);
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _pop();
      yield* sub_5889();
      return;
  }
}

function* sub_5829()
{
  _memoryWrite16(0x5A62, 0);
  memory[0x5A82] = 0;
}

function* sub_5835()
{
  var _pc = 0x5835;
  while (_pc != -1) switch(_pc)
  {
    case 0x5835:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x5A80)))
      {
        _pc = 0x5847;
        continue;
      };
      return;
    case 0x5847:
      _memoryWrite16(0x5A80, r16[dx]);
      memory[adr(_ds, 0x5A82)] += 1;
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[bx] = _memoryRead16(0x5A62);
      if (memory[adr(_ds, 0x5A82)] & 1)
      {
        _pc = 0x5861;
        continue;
      };
      r16[bx] += 0x0002;
    case 0x5861:
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a64));
      yield* sub_5889();
      return;
  }
}

function* sub_5869()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _push(r16[bx]);
  _push(r16[ax]);
  r8[al] = 0xb6;
  _out(0x43, r8[al]);
  r16[bx] = _memoryRead16(0x5A62);
  _memoryWrite16(adr(_ds, 0x5A62), _memoryRead16(adr(_ds, 0x5A62)) + 2);
  r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a64));
  yield* sub_5889();
  r16[ax] = _pop();
  r16[bx] = _pop();
}

function* sub_5889()
{
  _out(0x42, r8[al]);
  r8[al] = r8[ah];
  _out(0x42, r8[al]);
  r8[al] = _in(0x61);
  r8[al] |= 0x03;
  _out(0x61, r8[al]);
}

function* sub_5897()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _push(r16[ax]);
  _push(r16[cx]);
  _push(r16[dx]);
  r8[al] = 0xb6;
  _out(0x43, r8[al]);
  r16[bx] = _memoryRead16(0x5A56) & 0x0006;
  _memoryWrite16(adr(_ds, 0x5A56), _memoryRead16(adr(_ds, 0x5A56)) + 2);
  r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5a5a));
  yield* sub_5889();
  r16[dx] = _pop();
  r16[cx] = _pop();
  r16[ax] = _pop();
}

function* sub_58BD()
{
  memory[0x5927] = 0x80;
  memory[0x5928] = 0;
  memory[0x5929] = 0;
  _memoryWrite16(0x592A, 1280);
  memory[0x592C] = 0xff;
  memory[0x592D] = 0;
  memory[0x5920] = 0;
  memory[0x5B07] = 0;
  _memoryWrite16(0x5B08, 0);
  _memoryWrite16(0x5B0C, 1);
  memory[0x5B0E] = 1;
}

function* sub_58F8()
{
  var _pc = 0x58F8;
  while (_pc != -1) switch(_pc)
  {
    case 0x58F8:
      if (memory[adr(_ds, 0x1CBF)] != 0)
      {
        _pc = 0x5908;
        continue;
      };
      r16[bx] = 0x0390;
      r16[cx] = 0x1800;
      yield* sub_59A3();
    case 0x5908:
      memory[0x127C] = 0;
      return;
  }
}

function* sub_590E()
{
  if (memory[adr(_ds, 0x1CBF)] != 0)
    return;
  r16[bx] = 0x0400;
  r16[cx] = 0x1800;
  yield* sub_59A3();
}

function* sub_591F()
{
  r16[bx] = 0x07d0;
  r16[cx] = 0x1800;
  yield* sub_59A3();
  r16[bx] = 0x0a6e;
  r16[cx] = 0x1800;
  yield* sub_59A3();
  r16[bx] = 0x0dec;
  r16[cx] = 0x1800;
  yield* sub_59A3();
}

function* sub_593B()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _memoryWrite16(0x5923, r16[bx]);
  _push(r16[ax]);
  r8[al] = 0xb6;
  _out(0x43, r8[al]);
  r16[ax] = _pop();
  yield* sub_5889();
  memory[0x5920] = 2;
  r8[ah] = 0;
  _interrupt(0x1a);
  _memoryWrite16(0x5921, r16[dx]);
}

function* sub_595D()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  if (memory[adr(_ds, 0x5920)] != 0)
    return;
  yield* sub_2DFD();
  r16[ax] = (r16[dx] & 0x7f) + 0xaa;
  r16[bx] = r16[ax];
  r16[ax] += 0x1e;
  yield* sub_593B();
}

function* sub_597F()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  r16[ax] = 0x1200;
  r16[bx] = 0x1312;
  r16[ax] = r16[ax] + _memoryRead16(adr(_ds, 0x5B08));
  r16[bx] = r16[bx] + _memoryRead16(adr(_ds, 0x5B08));
  _memoryWrite16(adr(_ds, 0x5B08), _memoryRead16(adr(_ds, 0x5B08)) + 350);
  yield* sub_593B();
  memory[0x5B07] = 0x18;
}

function* sub_59A3()
{
  var _pc = 0x59A3;
  while (_pc != -1) switch(_pc)
  {
    case 0x59A3:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = r16[bx];
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x59C5;
        continue;
      };
      r16[cx] >>= 1;
    case 0x59C5:
      _Sleep(r16[cx]);
      yield* sub_5B21();
      return;
  }
}

function* sub_59CB()
{
  var _pc = 0x59CB;
  while (_pc != -1) switch(_pc)
  {
    case 0x59CB:
      r8[al] = _in(0x61);
      r8[al] &= 0xfe;
      _out(0x61, r8[al]);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x5A40, r16[dx]);
      _memoryWrite16(0x5A42, 0);
    case 0x59DF:
      r16[ax] = _memoryRead16(0x5A42);
      r8[cl] = 0x06;
      r16[ax] >>= r8[cl];
      if (r16[ax] != 0)
      {
        _pc = 0x59E9;
        continue;
      };
      r16[ax] += 1;
    case 0x59E9:
      r16[cx] = r16[ax];
    case 0x59EB:
      do {
        _push(r16[cx]);
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[cx] = _pop();
        r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x5A40));
      } while (r16[dx] < 0x0002);
      if (r16[dx] >= 0x0007)
      {
        _pc = 0x5A18;
        continue;
      };
      if (--r16[cx])
      {
        _pc = 0x59EB;
        continue;
      };
      yield* sub_2DFD();
      r8[dl] = (r8[dl] & 0x02) & memory[adr(_ds, 0x0)];
      r8[al] = _in(0x61);
      r8[al] = r8[al] ^ r8[dl];
      _out(0x61, r8[al]);
      _memoryWrite16(adr(_ds, 0x5A42), _memoryRead16(adr(_ds, 0x5A42)) + 7);
      {
        _pc = 0x59DF;
        continue;
      };
    case 0x5A18:
      yield* sub_5B21();
      return;
  }
}

function* sub_5A1C()
{
  var _pc = 0x5A1C;
  while (_pc != -1) switch(_pc)
  {
    case 0x5A1C:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      yield* sub_13B7();
      r16[bx] = _memoryRead16(0x5A16);
      flags.carry = r16[bx] < r16[ax];
      r16[bx] -= r16[ax];
      if (flags.carry)
      {
        _pc = 0x5A35;
        continue;
      };
      if (r16[bx] > 0x0260)
      {
        _pc = 0x5A35;
        continue;
      };
      return;
    case 0x5A35:
      _memoryWrite16(0x5A16, r16[ax]);
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      _memoryWrite16(adr(_ds, 0x5A18), _memoryRead16(adr(_ds, 0x5A18)) + 1);
      r16[bx] = _memoryRead16(0x5A18) & 0x1e;
      r16[ax] = _memoryRead16(0x5A3C) & 0x03ff;
      if (r16[ax] < 0x0180)
      {
        _pc = 0x5A59;
        continue;
      };
      r16[cx] = 0x0180 - r16[ax];
      var temp = r16[ax];
      r16[ax] = r16[cx];
      r16[cx] = temp;
    case 0x5A59:
      r16[ax] = (r16[ax] >> 2) + _memoryRead16(adr(_ds, r16[bx] + 0x5a1a));
      r16[bx] = 0x0001;
      if (memory[adr(_ds, 0x697)] != 0xfd)
      {
        _pc = 0x5A6D;
        continue;
      };
      r8[bl] <<= 1;
    case 0x5A6D:
      _memoryWrite16(adr(_ds, 0x5A3E), _memoryRead16(adr(_ds, 0x5A3E)) + r16[bx]);
      r16[bx] = (r16[bx] << 1) << 1;
      _memoryWrite16(adr(_ds, 0x5A3C), _memoryRead16(adr(_ds, 0x5A3C)) + r16[bx]);
      r16[dx] = _memoryRead16(0x5A3E);
      r8[cl] = 0x03;
      r16[dx] >>= r8[cl];
      r16[ax] += r16[dx];
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5A90()
{
  var _pc = 0x5A90;
  while (_pc != -1) switch(_pc)
  {
    case 0x5A90:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x5A14)))
      {
        _pc = 0x5AA2;
        continue;
      };
      return;
    case 0x5AA2:
      _memoryWrite16(0x5A14, r16[dx]);
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      yield* sub_2DFD();
      r16[ax] = (r16[dx] & 0x70) + 0x0200;
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5AC2()
{
  var _pc = 0x5AC2;
  while (_pc != -1) switch(_pc)
  {
    case 0x5AC2:
      _memoryWrite16(0x5A12, 824);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x5A10, r16[dx]);
      yield* sub_13B7();
      _memoryWrite16(0x5A0E, r16[ax]);
    case 0x5AD6:
      yield* sub_13B7();
      r16[dx] = r16[ax];
      r16[ax] = r16[ax] - _memoryRead16(adr(_ds, 0x5A0E));
      if (r16[ax] < 0x9c40)
      {
        _pc = 0x5B10;
        continue;
      };
      _memoryWrite16(0x5A0E, r16[dx]);
      if (memory[adr(_ds, 0x0)] == 0)
      {
        _pc = 0x5B10;
        continue;
      };
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      yield* sub_2DFD();
      r16[ax] = (r16[dx] & 0x07ff) + _memoryRead16(adr(_ds, 0x5A12));
      _memoryWrite16(adr(_ds, 0x5A12), _memoryRead16(adr(_ds, 0x5A12)) - 2);
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
    case 0x5B10:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x5A10));
      if (r16[dx] < 0x0002)
      {
        _pc = 0x5AD6;
        continue;
      };
      yield* sub_5B21();
      return;
  }
}

function* sub_5B21()
{
  r8[al] = _in(0x61);
  r8[al] &= 0xfc;
  _out(0x61, r8[al]);
}

function* sub_5B28()
{
  return; // play tone

  r8[al] = 0xb6;
  _out(0x43, r8[al]);
  r16[ax] = _memoryRead16(0x592A);
  _out(0x42, r8[al]);
  r8[al] = r8[ah];
  _out(0x42, r8[al]);
  r8[al] = _in(0x61);
  r8[al] |= 0x03;
  _out(0x61, r8[al]);
  yield* sub_13B7();
  r16[cx] = r16[ax];
  do {
    yield* sub_13B7();
    r16[dx] = r16[cx] - r16[ax];
  } while (r16[dx] < _memoryRead16(adr(_ds, 0x592E)));
  r8[al] = _in(0x61);
  r8[al] &= 0xfc;
  _out(0x61, r8[al]);
}

function* sub_5B54()
{
  _memoryWrite16(0x59BE, 0);
  r8[ah] = 0;
  _interrupt(0x1a);
  _memoryWrite16(0x59C0, r16[dx]);
}

function* sub_5B63()
{
  var _pc = 0x5B63;
  while (_pc != -1) switch(_pc)
  {
    case 0x5B63:
      if (memory[adr(_ds, 0x0)] == 0)
        return;
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x59C0));
      if (r16[ax] >= 0x0002)
      {
        _pc = 0x5B7A;
        continue;
      };
      return;
    case 0x5B7A:
      _memoryWrite16(0x59C0, r16[dx]);
      r16[bx] = _memoryRead16(0x59BE) & 0xfe;
      if (r16[bx] < 0x86)
      {
        _pc = 0x5B92;
        continue;
      };
      r16[bx] = 0;
      _memoryWrite16(0x59BE, r16[bx]);
    case 0x5B92:
      _memoryWrite16(adr(_ds, 0x59BE), _memoryRead16(adr(_ds, 0x59BE)) + 2);
      r16[ax] = _memoryRead16(ofs(r16[bx] + 0x5934));
      r16[cx] = _memoryRead16(0x59BC);
      _memoryWrite16(0x59BC, r16[ax]);
      if (r16[ax] != r16[cx])
      {
        _pc = 0x5BAA;
        continue;
      };
      yield* sub_5B21();
      return;
    case 0x5BAA:
      r16[cx] = r16[ax];
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = r16[cx];
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
      return;
  }
}

function* sub_5BBF()
{
  do {
    if (memory[adr(_ds, 0x0)] == 0)
      return;
    yield* sub_5B63();
  } while (_memoryRead16(adr(_ds, 0x59BE)) < 0x7c);
}

function* sub_5BE0()
{
  var _pc = 0x5BE0;
  while (_pc != -1) switch(_pc)
  {
    case 0x5BE0:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x5F66, r16[dx]);
      _memoryWrite16(0x5F60, 0);
    case 0x5BEE:
      r16[ax] = 0xb800;
      _es = r16[ax];
      r16[bx] = _memoryRead16(0x5F60);
      _memoryWrite16(adr(_ds, 0x5F60), _memoryRead16(adr(_ds, 0x5F60)) + 2);
      r16[bx] &= 0x0002;
      _si = _memoryRead16(ofs(r16[bx] + 0x5f62));
      _di = 0x0a74;
      r16[cx] = 0x4404;
      yield* sub_2D9D();
      do {
        yield* sub_57E4();
        r8[ah] = 0;
        _interrupt(0x1a);
        r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x5F66));
      } while (r16[ax] < 0x0004);
      _memoryWrite16(0x5F66, r16[dx]);
      if (_memoryRead16(adr(_ds, 0x5F60)) != 4)
      {
        _pc = 0x5C36;
        continue;
      };
      _si = 0x5f68;
      _di = 0x0668;
      r16[cx] = 0x1004;
      yield* sub_2D9D();
    case 0x5C36:
      r16[bx] = _memoryRead16(0x5F60);
      flags.carry = r16[bx] < 0x0008;
      r16[bx] -= 0x0008;
      if (flags.carry)
      {
        _pc = 0x5C51;
        continue;
      };
      if (r16[bx] >= 0x0006)
      {
        _pc = 0x5C51;
        continue;
      };
      _si = 0x5fe8;
      _di = _memoryRead16(ofs(r16[bx] + 0x60e4));
      r16[cx] = 0x1506;
      yield* sub_2D9D();
    case 0x5C51:
      if (_memoryRead16(adr(_ds, 0x5F60)) < 0x10)
      {
        _pc = 0x5BEE;
        continue;
      };
      yield* sub_5B21();
      return;
  }
}

function* sub_5C60()
{
  var _pc = 0x5C60;
  while (_pc != -1) switch(_pc)
  {
    case 0x5C60:
      _interrupt(0x11);
      r8[al] &= 0x30;
      if (r8[al] != 0x30)
        return;
      r16[ax] = 0xb800;
      _ds = r16[ax];
      r16[ax] = 0x55aa;
      _memoryWrite16(adr(_ds, 0x0), r16[ax]);
      r16[ax] = _memoryRead16(adr(_ds, 0x0));
      if (r16[ax] != 0x55aa)
      {
        _pc = 0x5C96;
        continue;
      };
      _si = 0x60f0;
      yield* sub_5C9E();
      r16[ax] = 0x40;
      _ds = r16[ax];
      r16[ax] = _memoryRead16(adr(_ds, 0x10));
      r8[al] = (r8[al] & 0xcf) | 0x10;
      _memoryWrite16(adr(_ds, 0x10), r16[ax]);
      r16[ax] = 0x0004;
      _interrupt(0x10);
      return;
    case 0x5C96:
      _si = 0x6112;
      yield* sub_5C9E();
      _InfiniteLoop();
      return;
  }
}

function* sub_5C9E()
{
  r16[ax] = SEG_DATA;
  _ds = r16[ax];
  yield* sub_5E2B();
}

function* sub_5CB0()
{
  var _pc = 0x5CB0;
  while (_pc != -1) switch(_pc)
  {
    case 0x5CB0:
      flags.direction = false;
      _memoryWrite16(0x4, 0);
      yield* sub_1830();
      yield* sub_2330();
      yield* sub_2A30();
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = 0x6152;
      r16[cx] = 0x1d0b;
      _di = 0xbd;
      yield* sub_2D9D();
      _si = 0x63d0;
      r16[cx] = 0x160e;
      _di = 0x069e;
      yield* sub_2D9D();
      _si = 0x6638;
      r16[cx] = 0x0c03;
      _di = 0x0a78;
      yield* sub_2D9D();
      _si = 0x6680;
      r16[cx] = 0x080e;
      _di = 0x0ca8;
      yield* sub_2D9D();
      _si = 0x6760;
      r16[cx] = 0x0b0c;
      _di = 0x1d6e;
      yield* sub_2D9D();
      _si = 0x6868;
      r16[cx] = 0x0804;
      _di = 0x1dec;
      yield* sub_2D9D();
      _memoryWrite16(0x6A8D, 0);
      yield* sub_5E3B();
      _memoryWrite16(0x579, 0);
      yield* sub_70D();
      memory[0x57B] = 0x60;
      memory[0x57C] = 0x92;
      yield* sub_26F2();
      yield* sub_26FC();
      memory[0x1F80] = 9;
      memory[0x1F81] = 0xff;
      yield* sub_26B3();
      yield* sub_1E40();
      memory[0x698] = 0;
      memory[0x699] = 0;
      memory[0x6A8A] = 0;
      r16[ax] = _memoryRead16(0x693);
      _memoryWrite16(0x6150, r16[ax]);
    case 0x5D54:
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x6A8B, r16[dx]);
      _memoryWrite16(0x5322, r16[dx]);
      _memoryWrite16(0x6A93, r16[dx]);
      r16[dx] -= 0x30;
      _memoryWrite16(0x6A88, r16[dx]);
      _memoryWrite16(0x5320, 0);
    case 0x5D71:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x6A93));
      if (r16[ax] < 0x24)
      {
        _pc = 0x5D89;
        continue;
      };
      _memoryWrite16(0x6A93, r16[dx]);
      _push(r16[dx]);
      yield* sub_5E3B();
      r16[dx] = _pop();
    case 0x5D89:
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x6A8B));
      r16[ax] = _memoryRead16(0x56DA);
      if (memory[adr(_ds, 0x41A)] == 0)
      {
        _pc = 0x5DA0;
        continue;
      };
      r16[ax] += 0x48;
      if (r16[dx] >= r16[ax])
      {
        _pc = 0x5D54;
        continue;
      };
      {
        _pc = 0x5DA7;
        continue;
      };
    case 0x5DA0:
      r16[ax] += 0x0006;
      if (r16[dx] > r16[ax])
        return;
    case 0x5DA7:
      yield* sub_53B0();
      yield* sub_5DD4();
      if (memory[adr(_ds, 0x69B)] == 0)
      {
        _pc = 0x5DCA;
        continue;
      };
      r16[dx] = 0x0201;
      r8[al] = _in(r16[dx]);
      r8[al] &= 0x10;
      if (r8[al] == 0)
      {
        _pc = 0x5DC3;
        continue;
      };
      memory[0x6A8A] = 1;
      {
        _pc = 0x5DCA;
        continue;
      };
    case 0x5DC3:
      if (memory[adr(_ds, 0x6A8A)] != 0)
        return;
    case 0x5DCA:
      r16[ax] = _memoryRead16(0x6150);
      if (r16[ax] == _memoryRead16(adr(_ds, 0x693)))
      {
        _pc = 0x5D71;
        continue;
      };
      return;
  }
}

function* sub_5DD4()
{
  var _pc = 0x5DD4;
  while (_pc != -1) switch(_pc)
  {
    case 0x5DD4:
      if (_memoryRead16(adr(_ds, 0x579)) > 0x20)
      {
        _pc = 0x5DE2;
        continue;
      };
      memory[0x698] = 1;
      {
        _pc = 0x5E1C;
        continue;
      };
    case 0x5DE2:
      if (_memoryRead16(adr(_ds, 0x579)) < 288)
      {
        _pc = 0x5DF1;
        continue;
      };
      memory[0x698] = 0xff;
      {
        _pc = 0x5E1C;
        continue;
      };
    case 0x5DF1:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[ax] = r16[dx] - _memoryRead16(adr(_ds, 0x6A88));
      if (r16[ax] < 0x12)
      {
        _pc = 0x5E1C;
        continue;
      };
      _memoryWrite16(0x6A88, r16[dx]);
      yield* sub_2DFD();
      memory[0x698] = 0;
      if (r8[dl] > 0xa0)
      {
        _pc = 0x5E1C;
        continue;
      };
      r8[dl] &= 0x01;
      if (r8[dl] != 0)
      {
        _pc = 0x5E18;
        continue;
      };
      r8[dl] = 0xff;
    case 0x5E18:
      memory[0x698] = r8[dl];
    case 0x5E1C:
      yield* sub_13D8();
      if (r8[al] == 0)
        return;
      _memoryWrite16(0x572, 4);
      yield* sub_8E5();
      return;
  }
}

function* sub_5E2B()
{
  do {
    _lodsb_MemData_DirForward();
    if (r8[al] == 0x00)
      return;
    _push(_si);
    r8[bl] = 0x02;
    r8[ah] = 0x0e;
    _interrupt(0x10);
    _si = _pop();
  } while (true);
}

function* sub_5E3B()
{
  r16[ax] = 0xb800;
  _es = r16[ax];
  _memoryWrite16(adr(_ds, 0x6A8D), _memoryRead16(adr(_ds, 0x6A8D)) + 2);
  r16[bx] = _memoryRead16(0x6A8D) & 0x0002;
  _si = _memoryRead16(ofs(r16[bx] + 0x6a8f));
  r16[cx] = 0x0c0a;
  _di = 0x1d38;
  yield* sub_2D9D();
}

function* sub_5E5B()
{
  r8[dl] = 0x00;
  r8[bh] = r8[dl];
  r8[ah] = 0x02;
  _interrupt(0x10);
}

function* sub_5E70()
{
  var _pc = 0x5E70;
  while (_pc != -1) switch(_pc)
  {
    case 0x5E70:
      yield* sub_5B21();
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x6DFC, r16[dx]);
      _memoryWrite16(0x6DFE, r16[cx]);
      _push(_ds);
      _push(_ds);
      _es = _pop();
      r16[ax] = 0xb800;
      _ds = r16[ax];
      _si = 0x0dca;
      _di = 0x0e;
      r16[cx] = 0x1020;
      yield* sub_2DCA();
      _ds = _pop();
      r16[dx] = 0x0b05;
      r8[bh] = 0x00;
      r8[ah] = 0x02;
      _interrupt(0x10);
      _si = 0x6d91;
      flags.direction = false;
      yield* sub_5E2B();
      r16[dx] = 0x0c05;
      r8[bh] = 0x00;
      r8[ah] = 0x02;
      _interrupt(0x10);
      _si = 0x6db2;
      if (memory[adr(_ds, 0x69B)] == 0)
      {
        _pc = 0x5EBA;
        continue;
      };
      _si = 0x6dd3;
    case 0x5EBA:
      flags.direction = false;
      yield* sub_5E2B();
      yield* sub_5F97();
      r16[ax] = 0xb800;
      _es = r16[ax];
      _si = 0x0e;
      _di = 0x0dca;
      r16[cx] = 0x1020;
      yield* sub_2D9D();
      r8[ah] = 0x01;
      r16[cx] = _memoryRead16(0x6DFE);
      r16[dx] = _memoryRead16(0x6DFC);
      _interrupt(0x1a);
      r16[ax] = _memoryRead16(0x693);
      _memoryWrite16(0x6E00, r16[ax]);
      return;
  }
}

function* sub_5EE5()
{
  var _pc = 0x5EE5;
  while (_pc != -1) switch(_pc)
  {
    case 0x5EE5:
      yield* sub_5B21();
    case 0x5EE8:
      yield* sub_5FCD();
      _memoryWrite16(0x6D8F, 0);
      yield* sub_5FB1();
    case 0x5EF4:
      r16[ax] = _memoryRead16(0x693);
      do {
        yield* _DeadLoop();
      } while (r16[ax] == _memoryRead16(adr(_ds, 0x693)));
      if (!(memory[adr(_ds, 0x6C1)] & 0x80))
      {
        _pc = 0x5F12;
        continue;
      };
      if (memory[adr(_ds, 0x6C2)] & 0x80)
      {
        _pc = 0x5EF4;
        continue;
      };
      memory[0x69B] = 0;
      {
        _pc = 0x5F1C;
        continue;
      };
    case 0x5F12:
      yield* sub_5FE5();
      if (flags.carry)
      {
        _pc = 0x5EE8;
        continue;
      };
      memory[0x69B] = 1;
    case 0x5F1C:
      r16[cx] = 0x0005;
      do {
        _push(r16[cx]);
        yield* sub_5FB1();
        r16[cx] = _pop();
      } while (--r16[cx]);
    case 0x5F26:
      r16[ax] = _memoryRead16(0x693);
      do {
        yield* _DeadLoop();
      } while (r16[ax] == _memoryRead16(adr(_ds, 0x693)));
      r16[ax] = 0;
      if (!(memory[adr(_ds, 0x6C3)] & 0x80))
      {
        _pc = 0x5F50;
        continue;
      };
      r16[ax] += 1;
      if (!(memory[adr(_ds, 0x6C4)] & 0x80))
      {
        _pc = 0x5F50;
        continue;
      };
      r16[ax] += 1;
      if (!(memory[adr(_ds, 0x6C5)] & 0x80))
      {
        _pc = 0x5F50;
        continue;
      };
      r16[ax] += 1;
      if (memory[adr(_ds, 0x6C6)] & 0x80)
      {
        _pc = 0x5F26;
        continue;
      };
    case 0x5F50:
      _memoryWrite16(0x6DF8, r16[ax]);
      r16[cx] = 0x0005;
      do {
        _push(r16[cx]);
        yield* sub_5FB1();
        r16[cx] = _pop();
      } while (--r16[cx]);
      if (memory[adr(_ds, 0x69B)] == 0)
      {
        _pc = 0x5F7E;
        continue;
      };
      _memoryWrite16(0x6D8F, 0x20);
      yield* sub_5FB1();
      yield* sub_5FB1();
      _memoryWrite16(0x6D8F, 0x18);
      yield* sub_5FB1();
      yield* sub_5FB1();
      {
        _pc = 0x5F93;
        continue;
      };
    case 0x5F7E:
      _memoryWrite16(0x6D8F, 0x1c);
      yield* sub_5FB1();
      yield* sub_5FB1();
      _memoryWrite16(0x6D8F, 0x16);
      yield* sub_5FB1();
    case 0x5F93:
      yield* sub_5F97();
      return;
  }
}

function* sub_5F97()
{
  var _pc = 0x5F97;
  while (_pc != -1) switch(_pc)
  {
    case 0x5F97:
      if (memory[adr(_ds, 0x69B)] == 0)
      {
        _pc = 0x5FA7;
        continue;
      };
      do {
        r16[dx] = 0x0201;
        r8[al] = _in(r16[dx]);
        r8[al] &= 0x10;
      } while (r8[al] != 0);
      return;
    case 0x5FA7:
      r16[ax] = _memoryRead16(0x693);
      do {
        yield* _DeadLoop();
      } while (r16[ax] == _memoryRead16(adr(_ds, 0x693)));
      return;
  }
}

function* sub_5FB1()
{
  r16[bx] = _memoryRead16(0x6D8F);
  r16[dx] = _memoryRead16(ofs(r16[bx] + 0x6d63));
  yield* sub_5E5B();
  r16[bx] = _memoryRead16(0x6D8F);
  _memoryWrite16(adr(_ds, 0x6D8F), _memoryRead16(adr(_ds, 0x6D8F)) + 2);
  _si = _memoryRead16(ofs(r16[bx] + 0x6d37));
  yield* sub_5E2B();
}

function* sub_5FCD()
{
  flags.direction = false;
  r16[ax] = 0xb800;
  _es = r16[ax];
  r16[ax] = 0;
  _di = r16[ax];
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
  _di = 0x2000;
  r16[cx] = 0x0fa0;
  _rep_stosw_MemB800_DirForward();
}

function* sub_5FE5()
{
  var _pc = 0x5FE5;
  while (_pc != -1) switch(_pc)
  {
    case 0x5FE5:
      _interrupt(0x11);
      if (!(r16[ax] & 0x1000))
      {
        _pc = 0x5FF6;
        continue;
      };
      yield* sub_600F();
      if (!flags.carry)
        return;
      yield* sub_600F();
      if (!flags.carry)
        return;
    case 0x5FF6:
      _memoryWrite16(0x6D8F, 0x24);
      r16[cx] = 0x0004;
      do {
        yield* sub_5FB1();
      } while (--r16[cx]);
      r16[ax] = _memoryRead16(0x693);
      do {
        yield* _DeadLoop(); // TODO: yield
      } while (r16[ax] == _memoryRead16(adr(_ds, 0x693)));
      flags.carry = true;
      return;
  }
}

function* sub_600F()
{
  var _pc = 0x600F;
  while (_pc != -1) switch(_pc)
  {
    case 0x600F:
      r16[dx] = 0x0201;
      _out(r16[dx], r8[al]);
      r8[ah] = 0;
      _interrupt(0x1a);
      _memoryWrite16(0x6DFA, r16[dx]);
    case 0x601B:
      r16[dx] = 0x0201;
      r8[al] = _in(r16[dx]);
      if (r8[al] & 0x03)
      {
        _pc = 0x6025;
        continue;
      };
      flags.carry = false;
      return;
    case 0x6025:
      r8[ah] = 0;
      _interrupt(0x1a);
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x6DFA));
      if (r16[dx] < 0x12)
      {
        _pc = 0x601B;
        continue;
      };
      flags.carry = true;
      return;
  }
}

function* sub_6040()
{
  var _pc = 0x6040;
  while (_pc != -1) switch(_pc)
  {
    case 0x6040:
      flags.direction = false;
      _push(_ds);
      _es = _pop();
      _di = 0x0e;
      r16[cx] = 0x24;
      r16[ax] = 0;
      _rep_stosw_MemData_DirForward();
      _memoryWrite16(0x6F24, 0x25);
      r16[ax] = 0xb800;
      _es = r16[ax];
    case 0x6058:
      do {
        yield* sub_13D8();
      } while (r8[al] == 0);
      _si = 0x0e;
      _di = _memoryRead16(0x6F24);
      r16[cx] = 0x0c03;
      yield* sub_2D9D();
      _memoryWrite16(adr(_ds, 0x6F24), _memoryRead16(adr(_ds, 0x6F24)) + 480);
      _si = 0x6e10;
      _di = _memoryRead16(0x6F24);
      r16[cx] = 0x0c03;
      yield* sub_2D9D();
      do {
        r8[ah] = 0;
        _interrupt(0x1a);
      } while (r16[dx] == _memoryRead16(adr(_ds, 0x6F26)));
      _memoryWrite16(0x6F26, r16[dx]);
      if (memory[adr(_ds, 0x0)] == 0)
      {
        _pc = 0x60A7;
        continue;
      };
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = _memoryRead16(0x6F24) >> 1;
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
      r8[al] = _in(0x61);
      r8[al] |= 0x03;
      _out(0x61, r8[al]);
    case 0x60A7:
      if (_memoryRead16(adr(_ds, 0x6F24)) < 6720)
      {
        _pc = 0x6058;
        continue;
      };
      _si = 0x6e58;
      _di = _memoryRead16(0x6F24);
      r16[cx] = 0x1106;
      yield* sub_2D9D();
    case 0x60BC:
      do {
        r8[ah] = 0;
        _interrupt(0x1a);
      } while (r16[dx] == _memoryRead16(adr(_ds, 0x6F28)));
      _memoryWrite16(0x6F28, r16[dx]);
      if (memory[adr(_ds, 0x0)] == 0)
      {
        _pc = 0x60E6;
        continue;
      };
      r8[al] = 0xb6;
      _out(0x43, r8[al]);
      r16[ax] = 0x0c00;
      if (!(r8[dl] & 0x01))
      {
        _pc = 0x60E0;
        continue;
      };
      r16[ax] = 0x0b54;
    case 0x60E0:
      _out(0x42, r8[al]);
      r8[al] = r8[ah];
      _out(0x42, r8[al]);
    case 0x60E6:
      r16[dx] = r16[dx] - _memoryRead16(adr(_ds, 0x6F26));
      if (r16[dx] < 0x12)
      {
        _pc = 0x60BC;
        continue;
      };
      yield* sub_5B21();
      return;
  }
}

function* sub_6100()
{
  memory[0x70F2] = 0;
}

function* sub_6106()
{
  var _pc = 0x6106;
  while (_pc != -1) switch(_pc)
  {
    case 0x6106:
      r8[ah] = 0;
      _interrupt(0x1a);
      if (r16[dx] != _memoryRead16(adr(_ds, 0x70EE)))
      {
        _pc = 0x6111;
        continue;
      };
      return;
    case 0x6111:
      _memoryWrite16(0x70EE, r16[dx]);
      yield* sub_62A6();
      if (!flags.carry)
      {
        _pc = 0x6129;
        continue;
      };
      yield* sub_11E3();
      yield* sub_622B();
      yield* sub_1145();
      memory[0x70F2] = 0;
      return;
    case 0x6129:
      if (memory[adr(_ds, 0x70F2)] != 0)
      {
        _pc = 0x619E;
        continue;
      };
    case 0x6130:
      yield* sub_2DFD();
      r16[bx] = r16[dx] & 0x1f;
      if (r8[bl] < 0x10)
      {
        _pc = 0x6166;
        continue;
      };
      r8[bl] -= 0x10;
      if (r8[bl] > 0x09)
      {
        _pc = 0x6130;
        continue;
      };
      r8[dl] = 0x01;
      if (r8[bl] < 0x05)
      {
        _pc = 0x614F;
        continue;
      };
      r8[dl] = 0xff;
    case 0x614F:
      memory[0x70F6] = r8[dl];
      memory[0x70F5] = 6;
      r8[bl] <<= 1;
      r16[ax] = (_memoryRead16(ofs(r16[bx] + 0x70b8))) + 0x0004;
      _memoryWrite16(0x70F3, r16[ax]);
      {
        _pc = 0x6188;
        continue;
      };
    case 0x6166:
      r16[ax] = 0x0c;
      r8[dl] = 0x01;
      if (!(r8[bl] & 0x08))
      {
        _pc = 0x6175;
        continue;
      };
      r16[ax] = 0x0120;
      r8[dl] = 0xff;
    case 0x6175:
      _memoryWrite16(0x70F3, r16[ax]);
      memory[0x70F6] = r8[dl];
      r8[bl] &= 0x07;
      r8[al] = (memory[ofs(r16[bx] + 0x70b0)]) + 0x08;
      memory[0x70F5] = r8[al];
    case 0x6188:
      memory[0x70F2] = 1;
      memory[0x70F7] = 1;
      _memoryWrite16(0x70F0, 0);
      _memoryWrite16(0x70EC, 0xffff);
    case 0x619E:
      if (_memoryRead16(adr(_ds, 0x70F0)) >= 0xa0)
      {
        _pc = 0x61AB;
        continue;
      };
      _memoryWrite16(adr(_ds, 0x70F0), _memoryRead16(adr(_ds, 0x70F0)) + 4);
    case 0x61AB:
      memory[adr(_ds, 0x70F5)] += 2;
      if (memory[adr(_ds, 0x70F5)] > 0xbf)
      {
        _pc = 0x61D4;
        continue;
      };
      if (memory[adr(_ds, 0x70F6)] == 1)
      {
        _pc = 0x61C7;
        continue;
      };
      flags.carry = _memoryRead16(adr(_ds, 0x70F3)) < 5;
      _memoryWrite16(adr(_ds, 0x70F3), _memoryRead16(adr(_ds, 0x70F3)) - 5);
      if (flags.carry)
      {
        _pc = 0x61D4;
        continue;
      };
      {
        _pc = 0x61DD;
        continue;
      };
    case 0x61C7:
      _memoryWrite16(adr(_ds, 0x70F3), _memoryRead16(adr(_ds, 0x70F3)) + 5);
      if (_memoryRead16(adr(_ds, 0x70F3)) < 300)
      {
        _pc = 0x61DD;
        continue;
      };
    case 0x61D4:
      memory[0x70F2] = 0;
      yield* sub_622B();
      return;
    case 0x61DD:
      r16[cx] = _memoryRead16(0x70F3);
      r8[dl] = memory[0x70F5];
      yield* sub_2CB0();
      _memoryWrite16(0x70FA, r16[ax]);
      yield* sub_62A6();
      if (flags.carry)
      {
        _pc = 0x61D4;
        continue;
      };
      yield* sub_6245();
      yield* sub_622B();
      yield* sub_61FA();
      return;
  }
}

function* sub_61FA()
{
  var _pc = 0x61FA;
  while (_pc != -1) switch(_pc)
  {
    case 0x61FA:
      r16[ax] = 0xb800;
      _es = r16[ax];
      memory[0x70F7] = 0;
      r16[ax] = (_memoryRead16(0x70F0) & 0x01e0) + 0x6f30;
      if (memory[adr(_ds, 0x70F6)] == 0xff)
      {
        _pc = 0x6217;
        continue;
      };
      r16[ax] += 0xc0;
    case 0x6217:
      _si = r16[ax];
      _di = _memoryRead16(0x70FA);
      _memoryWrite16(0x70F8, _di);
      _bp = 0x70cc;
      r16[cx] = 0x0802;
      yield* sub_2CCC();
      return;
  }
}

function* sub_622B()
{
  if (memory[adr(_ds, 0x70F7)] != 0)
    return;
  r16[ax] = 0xb800;
  _es = r16[ax];
  _si = 0x70cc;
  _di = _memoryRead16(0x70F8);
  r16[cx] = 0x0802;
  yield* sub_2D9D();
}

function* sub_6245()
{
  var _pc = 0x6245;
  while (_pc != -1) switch(_pc)
  {
    case 0x6245:
      r8[al] = (memory[0x70F5] - 0x08) & 0xf8;
      r16[cx] = 0x0007;
    case 0x624F:
      r16[bx] = r16[cx] - 1;
      if (r8[al] == memory[adr(_ds, r16[bx] + 0x2bd4)])
      {
        _pc = 0x625B;
        continue;
      };
      if (--r16[cx])
      {
        _pc = 0x624F;
        continue;
      };
      return;
    case 0x625B:
      r16[ax] = _memoryRead16(0x70F3);
      r8[cl] = 0x04;
      r16[ax] >>= r8[cl];
      flags.carry = r16[ax] < 0x0002;
      r16[ax] -= 0x0002;
      if (flags.carry)
        return;
      if (r16[ax] >= 0x10)
        return;
      _di = r16[ax];
      r8[dl] = memory[ofs(r16[bx] + 0x2bdb)];
      r8[dh] = 0;
      r16[ax] += r16[dx];
      if (r16[ax] == _memoryRead16(adr(_ds, 0x70EC)))
        return;
      _memoryWrite16(0x70EC, r16[ax]);
      _si = r16[ax];
      memory[adr(_ds, _si + 0x2be2)] = memory[adr(_ds, _si + 0x2be2)] ^ 2;
      r8[al] = memory[ofs(_si + 0x2be2)];
      r8[ah] = 0;
      _di <<= 1;
      r16[cx] = _memoryRead16(ofs(_di + 28924));
      r8[dl] = memory[ofs(r16[bx] + 0x7120)];
      _push(r16[ax]);
      _push(r16[cx]);
      _push(r16[dx]);
      yield* sub_622B();
      r16[dx] = _pop();
      r16[cx] = _pop();
      r16[bx] = _pop();
      yield* sub_30E3();
      yield* sub_61FA();
      return;
  }
}

function* sub_62A6()
{
  var _pc = 0x62A6;
  while (_pc != -1) switch(_pc)
  {
    case 0x62A6:
      if (memory[adr(_ds, 0x70F2)] != 0)
      {
        _pc = 0x62AF;
        continue;
      };
      flags.carry = false;
      return;
    case 0x62AF:
      r16[ax] = _memoryRead16(0x70F3);
      r8[dl] = memory[0x70F5];
      _si = 0x10;
      r16[bx] = _memoryRead16(0x579);
      r8[dh] = memory[0x57B];
      _di = 0x18;
      r16[cx] = 0x0e08;
      yield* sub_2E29();
      if (!flags.carry)
        return;
      memory[0x571] = 1;
      memory[0x576] = 2;
      memory[0x578] = 0x20;
      memory[0x55B] = 8;
      r16[ax] = 0x091d;
      r16[bx] = 0x0ce4;
      yield* sub_593B();
      flags.carry = true;
      return;
  }
}

