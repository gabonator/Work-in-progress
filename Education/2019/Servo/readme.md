# Servomotory a pan-tilt podstavec

## Annotation 

arduino workshop: potenciometer a servo motor

Na tomto workshope si vysvetlime vnutornu konstrukciu potenciometra a modelarskeho servo motora 9g s riadenim so spatnou vazbou. Naucime sa, ako vyuzivat vstupne analogove piny na meranie napatia, a ako naskalovat vysledok analogovo digitalnej konverzie na lubovolny ciselny interval s pomocou linearnej interpolacie.

S pomocou pripravku vytlaceneho na 3d tlaciarni osadeneho dvomi servo motormi sa naucime vychylovat laserovy luc v priestore a premietnuty bod budeme pohybovat takym sposobom, aby na tienidle opisoval tvar niektorych pismen. 

Treba priniest: pocitac s Arduino Uno, USB-B kabel, harok papiera A4, pero

Na co sa mozete pripravit: programovanie Arduino Uno, linearna interpolacia y=y0+(x-x0)*(y1-y0)/(x1-x0), parametricke vyjadrenie usecky, pohyb po kruznici s harmonickymi funkciami sinus a kosinus, casovaci diagram ovladania servo motora
![Servo pan tilt stand with laser](preview.jpg)

## BOM
Pre 8 ucastnikov

| polozka (vypocet poctu kusov a baleni) | pocet baleni | cena balenia | linka |
| -------------------------------------- | ------------ | ------------ | ----- |
| arduino uno (8 * 1 kus) | 8x | 8.80 | https://www.gme.sk/klon-arduino-uno-r3-atmega328p-ch340-mini-usb |
| servo motor 9g | 16x | 4.59 | https://www.gme.sk/servomotor-9g |
| laser | 8x | 2.56 | https://www.gme.sk/modul-s-cervenym-laserom-650nm-5mw |
| potenciometer piher linearny 10k | 8x | 1.22 | https://www.gme.sk/pc16mlk010 |
| kable (8 * 10 kablov, balenie po 40, 8 * 10 / 40) | 2x | 3.9 | https://www.gme.sk/propojovaci-vodice-zasuvka-zasuvka-40-kusu |
| lista rovna (8 * 19, 8 * 19 / 40) | 4x | 0.24 | https://www.gme.sk/oboustranny-kolik-s1g40-2-54mm
| lista lomena (8 * 15, 8 * 15 / 40) | 3x | 0.31 | https://www.gme.sk/oboustranny-kolik-s1g40w-2-54mm |

Rozpocet: 8 * 8.80 + 16 * 4.59 + 8 * 2.56 + 8 * 1.22 + 2 * 3.9 + 4 * 0.24 + 3 * 0.31 = 183.77 eur

Extra: obosjtranna paska, noznice

Extra: papier A4, fixka, USB-A kabel

### Poznamky
S0: potenciometer konstrukcia
S1: potenciometer nahradna schema
S2: meranie cez analog read, aky je rozsah?
S3: aritmetika $PRIDAT typy a rozsahy
S8: linearna interpolacia vzorec
S11: servo timing diagram
S20/U11: funkcia na kreslenie usecky
S22/U13: funkcie sinus kosinus, kruh, jednotkova kruznica

arduino uno pwm asi nepojde na A0..A5 pinoch

void ciara(int x1, int y1, int x2, int y2)
{
  int dlzka = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  for (int i=0; i<dlzka; i++)
  {
     int x = x1 + (x2-x1)*i/dlzka;
     int y = y1 + (y2-y1)*i/dlzka;
     servoX.write(x);
     servoY.write(y);
     delay(20);
  }
}





potenciometer - konstrukcia, princip
servo motor - konstrukcia, princip, ovladanie
servo signaly - casovaci diagram

Ux: urobit 555 s potenciometrom, linear, 555 riadi servo, manualne delay microseconds, intervaly pre delay, tabulka ms us s

U0: blink, natocit na 0%, 50%, 100%
U1: loopy, for 0..100, 100..0
U2: Servo, attach, write
    prepisat for 0..100, 100..0
U3: programovat linearnu funkciu, percenta 0..100
U4: zapojit 2 serva, skusit zistit orientaciu

V1: potenciometer - vypisovat hodnoty, zistit rozsah
V2: roztiahnut na celociselny rozsah 0..100
V3: roztiahnut na celociselny rozsah 100..200

W1: zistit polohu krajnych bodov harku A4, kreslit stvorec po obvode
    suradnicovy system
W0: nakrelslit pismeno L
W1: usecka z bodu X1-Y1 do bodu X2-Y2, kombinovany vypis Serial.print
W2: nakreslit pismeno N
W3: nakreslit pismeno Y
W4: kruznica sin/cos
W5: kruznica s blikanim (zvysok po deleni), vyskusat serial print

pytagorova veta v C
rovnica usecky parametricka t
