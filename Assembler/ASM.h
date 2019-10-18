
#ifndef ASM_ASM_H
#define ASM_ASM_H

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctype.h>

const char Input_File[]  = "/Users/albatraozrus/Desktop/Input_File.txt";
const char Output_File[] = "/Users/albatraozrus/Desktop/Output_File.txt";
const char ErrorWhichCommand = 255;
const int Poison = -666;

struct Line {
    char *ptrbuffer;
    unsigned long length;
};



int Assembler (char *bytecode, size_t *amount);
struct Line * Reading(size_t *amount);
size_t CounterOfLines(char *buffer, long size);
void SurgeryOfLines(char *buffer, long size);
size_t CounterOfSymbols(FILE * readfile);
struct Line* CreateStruct(char *buffer, size_t size, size_t amount);
char WhichCommand (char *Command, int amount);
void DeleteComments (struct Line *ptrstruct, size_t amount);
void Writing (char *bytecode, int size);
bool PassTrash(char *Command);
bool ScanCommand (char *Command, struct Line *ptrstruct, int NumberOfLine);
int WhichSpec (struct Line *ptrstruct, int NumberOfLine);
void ScanParam (int Spec, struct Line *ptrstruct, int NumberOfLine, int *Param);
void FullBytecode (int *PC, char *bytecode, char *Command_Number, char *Command,
                   int NumberOfLine, struct Line *ptrstruct, int *Param);

#endif //ASM_ASM_H
