#include "engextcpp.cpp"
class EXT_CLASS : public ExtExtension
{
public:
    EXT_COMMAND_METHOD(label);
};
EXT_DECLARE_GLOBALS();
EXT_COMMAND(label,"","{;s,d="";"";Label}{;e,d=0;"";Start}{;e32,d=0;"";Size}{;e,d=0;"";Base}")
{
    PCSTR LName = GetUnnamedArgStr(0);    
    if(strlen(LName) == 0 ) 
    {
        Out("provide a label\n");
        return;
    }
    ULONG64 LStart = GetUnnamedArgU64(1);     
    if(LStart == 0) 
    {
        Out("Start Address Required\n");
        return;
    }
    ULONG LSize = GetUnnamedArgU64(2) & 0x00000000ffffffff;    
    if( LSize == 0) 
    {
        Out("Size Required\n");
        return;
    }
    ULONG64 LBase = GetUnnamedArgU64(3);
    if(LBase == 0) 
    {
        Out("ModBase Required\n");
        return;
    }    
    m_Symbols3->AddSyntheticSymbol( LBase+LStart, LSize, LName, DEBUG_ADDSYNTHSYM_DEFAULT, NULL );
}