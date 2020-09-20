```
# windbg_labeller
windbg extension to label a range of address 
.load label.dll to load the extension
create a txtfile that contains a series of space delimited commands of the form

$$ cmd  symbol                  RVA     size        Module
!label  Fun_main                1000    1b          tmsgbox
!label  Str_This_Is_stripped    2010    00000010    tmsgbox
!label  Str_IamMalware          2020    00000010    tmsgbox
!label  Fun_MessageBoxA         2008    00000004    tmsgbox
!label  Fun_Exitprocess         2000    00000004    tmsgbox

use the script execution command to label repeatedly 

a sample usage 

Disassembly Prior to Labelling

0:000> u 401000
tmsgbox+0x1000:
00401000 6a00            push    0
00401002 6810204000      push    offset tmsgbox+0x2010 (00402010)
00401007 6820204000      push    offset tmsgbox+0x2020 (00402020)
0040100c 6a00            push    0
0040100e ff1508204000    call    dword ptr [tmsgbox+0x2008 (00402008)]
00401014 6a00            push    0
00401016 ff1500204000    call    dword ptr [tmsgbox+0x2000 (00402000)]
0040101c cc              int     3

loading extension
0:000> .load label.dll

running a script that executes several !label commands

0:000> $$>a< label.wds

Disassembly Post Labelling

0:000> u 401000
tmsgbox!Fun_main:
00401000 6a00            push    0
00401002 6810204000      push    offset tmsgbox!Str_This_Is_stripped (00402010)
00401007 6820204000      push    offset tmsgbox!Str_IamMalware (00402020)
0040100c 6a00            push    0
0040100e ff1508204000    call    dword ptr [tmsgbox!Fun_MessageBoxA (00402008)]
00401014 6a00            push    0
00401016 ff1500204000    call    dword ptr [tmsgbox!Fun_Exitprocess (00402000)]
0040101c cc              int     3
```
