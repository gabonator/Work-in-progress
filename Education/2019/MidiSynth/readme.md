# DIY Klavir

![Generator melodie](keyboard.jpg)

## Anotacia
Kedy sa z kmitania stáva tón? Ako vypočítať frekvencie tónov chromatickej stupice? Ako zahrať akord alebo melódiu s Arduinom Micro? Tieto, ako aj mnohé ďalšie otázky si zodpovieme na tomto workshope. Zoznámime sa taktiež s protokolom MIDI, ktorý slúži na vzájomnú komunikáciu medzi hudobnými nástrojmi a softvérmi na tvorbu hudby. Skúsime s arduinom prehrať jednoduchú melódiu jednak na reproduktore fyzicky pripojenom na arduine, na MIDI syntezátore a taktiež na počítači pomocou emulácie USB MIDI periférie.
V druhej časti workshopu si vysvetlíme ako fungujú kapacitné dotykové senzory a na tomto princípe si vyrobíme jednoduché MIDI klávesy z obojstrannej dosky plošných spojov. Program v arduine bude sledovať dotyky na klávesách a prevádzať ich na MIDI eventy, ktoré v pripojenom zariadení zahrajú syntetizovaný tón.

Treba si priniesť počítač s nainštalovaným prostredím Arduino IDE a USB kábel s koncovkou usb micro, sluchadla.

## BOM
Pre 8 ucastnikov

| polozka (vypocet poctu kusov a baleni) | pocet baleni | cena balenia | linka |
| -------------------------------------- | ------------ | ------------ | ----- |
| arduino micro (8*1 kus) | 8x | 11.77 | https://www.gme.sk/100-kompatibilny-klon-arduino-micro-atmega32u4-5v |
| kable (8*15 kablov, balenie po 40, 8*15/40) | 3x | 3.9 | https://www.gme.sk/propojovaci-vodice-zasuvka-zasuvka-40-kusu |
| piezo (8*1 kus) | 8x | 0.59 | https://www.gme.sk/piezomenic-pt-2038wq |
| rezistor 1M (8*(12 kusov+3 rezerva)) | 120 | 0.08 | https://www.gme.sk/rm-1m2-0207-0-6w-1-yageo |
| rezistor 100R (8 kusov, 2 rezerva) | 10 | 0.06 | https://www.gme.sk/rm-100r-0309-1w-1 |
| lista lomena (8 * (14 kusov + 4 rezerva) = 8*18/36) | 4 | 0.28 | https://www.gme.sk/oboustranny-kolik-s1g36w-2-54mm |
| dps obojstranna | (vyjdu 3-4 kusy na 30x20cm) 8/3 | 3 | 8.27 | https://www.gme.sk/cuprextit-300x200x1-5-dvouvrstvy |

Rozpocet: 8*11.77+3*3.9+8*0.59+120*0.08+10*0.06+4*0.28+3*8.27 = 146.71 eur

Extra: na prepojenie viacerych klavesnic dokopy 8x2pin header + 8x2pin socket 
Extra: prepojovaci kabel na midi socket

## Vypocet frekvencie

| nota |   x   | f(x)  |  x-69 | (x-69)/12 | f(x)/440 |
|------|-------|-------|-------|-----------|----------|
| A3   |   57  |  220  |  -12  |   -1      |  0.5     |
| A4   |   69  |  440  |  0    |    0      |  1       |
| A5   |   81  |  880  |  12   |    1      |  2       |
| A6   |   93  | 1760  |  24   |    2      |  4       |
| A7   |  105  | 3520  |  36   |    3      |  8       |

    y = (x-69)/12
    g(y) = f(x)/440

| y    | g(y) |
|------|------|
| -1   | 0.5  |
| 0    | 1    |
| 1    | 2    |
| 2    | 4    |
| 3    | 8    |

    g(y) = 2^y
    f(x)/440 = 2^((x-69)/12)

    f(x) = 440*2^((x-69)/12)
