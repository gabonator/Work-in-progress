# Servomotory a pan-tilt podstavec

![Servo pan tilt stand with laser](preview.jpg)

## BOM
Pre 8 ucastnikov

| polozka (vypocet poctu kusov a baleni) | pocet baleni | cena balenia | linka |
| -------------------------------------- | ------------ | ------------ | ----- |
| arduino uno (8 * 1 kus) | 8x | 8.80 | https://www.gme.sk/klon-arduino-uno-r3-atmega328p-ch340-mini-usb |
| servo motor 9g | 8x | 4.59 | https://www.gme.sk/servomotor-9g |
| potenciometer piher linearny 10k | 8x | 1.22 | https://www.gme.sk/pc16mlk010 |
| kable (8 * 10 kablov, balenie po 40, 8 * 10 / 40) | 2x | 3.9 | https://www.gme.sk/propojovaci-vodice-zasuvka-zasuvka-40-kusu |
| lista rovna (8 * 21, 8 * 21 / 40) | 5x | 0.24 | https://www.gme.sk/oboustranny-kolik-s1g40-2-54mm
| lista lomena (8 * 15, 8 * 15 / 40) | 3x | 0.31 | https://www.gme.sk/oboustranny-kolik-s1g40w-2-54mm |

Rozpocet: 8 * 8.80 + 8 * 4.59 + 8 * 1.22 + 2 * 3.9 + 5 * 0.24 + 3 * 0.31 = 126.81 eur

Extra: obosjtranna paska

Extra: papier A4, fixka, USB-A kabel

### Poznamky

potenciometer - konstrukcia, princip
servo motor - konstrukcia, princip, ovladanie
servo signaly - casovaci diagram

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
