
```
# windbg_labeller
windbg extension to label a range of address &nbsp;
.load label.dll to load the extension &nbsp;
create a txtfile that contains a series of space delimited commands of the form&nbsp;

$$ cmd  symbol                  RVA     size        Module&nbsp;
!label  Fun_main                1000    1b          tmsgbox&nbsp;
!label  Str_This_Is_stripped    2010    00000010    tmsgbox&nbsp;
!label  Str_IamMalware          2020    00000010    tmsgbox&nbsp;
!label  Fun_MessageBoxA         2008    00000004    tmsgbox&nbsp;
!label  Fun_Exitprocess         2000    00000004    tmsgbox&nbsp;

use the script execution command to label repeatedly &nbsp;

a sample usage &nbsp;

Disassembly Prior to Labelling&nbsp;

0:000> u 401000&nbsp;
tmsgbox+0x1000:&nbsp;
00401000 6a00            push    0&nbsp;
00401002 6810204000      push    offset tmsgbox+0x2010 (00402010)&nbsp;
00401007 6820204000      push    offset tmsgbox+0x2020 (00402020)&nbsp;
0040100c 6a00            push    0&nbsp;
0040100e ff1508204000    call    dword ptr [tmsgbox+0x2008 (00402008)]&nbsp;
00401014 6a00            push    0&nbsp;
00401016 ff1500204000    call    dword ptr [tmsgbox+0x2000 (00402000)]&nbsp;
0040101c cc              int     3&nbsp;

loading extension&nbsp;
0:000> .load label.dll&nbsp;

running a script that executes several !label commands&nbsp;

0:000> $$>a< label.wds&nbsp;

Disassembly Post Labelling&nbsp;

0:000> u 401000&nbsp;
tmsgbox!Fun_main:&nbsp;
00401000 6a00            push    0&nbsp;
00401002 6810204000      push    offset tmsgbox!Str_This_Is_stripped (00402010)&nbsp;
00401007 6820204000      push    offset tmsgbox!Str_IamMalware (00402020)&nbsp;
0040100c 6a00            push    0&nbsp;
0040100e ff1508204000    call    dword ptr [tmsgbox!Fun_MessageBoxA (00402008)]&nbsp;
00401014 6a00            push    0&nbsp;
00401016 ff1500204000    call    dword ptr [tmsgbox!Fun_Exitprocess (00402000)]&nbsp;
0040101c cc              int     3&nbsp;
```
