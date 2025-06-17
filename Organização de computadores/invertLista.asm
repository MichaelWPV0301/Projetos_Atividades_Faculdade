DATA r2, 0x01
DATA r0, 0xf9


DATA r1, 0x30
ST r0,r1
ADD r2,r0
DATA r1, 0x29 ;fa
ST r0,r1
ADD r2,r0
DATA r1, 0x28 ;fb
ST r0,r1
ADD r2,r0
DATA r1, 0x27 ;fc
ST r0,r1
ADD r2,r0
DATA r1, 0x26 ;fd
ST r0,r1
ADD r2,r0
DATA r1, 0x25 ;fe
ST r0,r1
ADD r2,r0
DATA r1, 0x24 ;ff
ST r0,r1




Data r0, 0xf9
Data r2, 0xff
CMP r0,r2 ;loop
JAE 0x34 ;final
LD r0,r1
LD r2,r3
ST r0,r3
ST r2,r1
DATA r1, 0x01
ADD r1,r0
DATA r3,0x01
NOT r1,r1
ADD r3,r1
ADD r1,r2
JMP 0x23 ;loop
CLF 
JMP 0x34 ;final