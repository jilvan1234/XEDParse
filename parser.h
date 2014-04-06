#ifndef _PARSER_H
#define _PARSER_H

#include "XEDParse.h"

//enums
enum PREFIX
{
    PREFIX_NONE,
    PREFIX_LOCK, //LOCK F0
    PREFIX_REP, //REP/REPE/REPZ F3
    PREFIX_REPNEZ //REPNE/REPNZ F2
};

enum OPTYPE
{
    TYPE_NONE,
    TYPE_VALUE,
    TYPE_REGISTER,
    TYPE_MEMORY
};

enum OPSIZE
{
    SIZE_BYTE,
    SIZE_WORD,
    SIZE_DWORD,
#ifdef _WIN64
    SIZE_QWORD,
#endif //_WIN64
    SIZE_UNSET
};

typedef OPSIZE MEMSIZE;
typedef OPSIZE SCALE;
typedef OPSIZE REGSIZE;

#include "regtable.h"

//structures
struct OPVAL
{
    OPSIZE size; //value size
    ULONG_PTR val; //actual data
};

struct OPMEM //size seg:[base+index*scale+displ]
{
    MEMSIZE size; //byte/word/dword/qword
    SEG seg; //segment
    REG base; //base register
    REG index; //index register
    SCALE scale; //scale
    OPVAL displ; //displacement
};

struct OPREG
{
    REGSIZE size;
    REG reg;
};

struct OPERAND
{
    char raw[XEDPARSE_MAXBUFSIZE/2]; //raw text
    OPTYPE type; //operand type
    union
    {
        OPVAL val;
        OPREG reg;
        OPMEM mem;
    } u;
};


struct INSTRUCTION
{
    PREFIX prefix;
    char mnemonic[10];
    OPERAND operand1;
    OPERAND operand2;
    OPERAND operand3;
};

//functions
bool parse(XEDPARSE* raw, INSTRUCTION* parsed);

#endif // _PARSER_H
