#ifndef _MY_CUSTOM_SHELL_H_
#define _MY_CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH_FLAG -1

#define CMD_NORMAL 0
#define CMD_OR_OPERATOR 1
#define CMD_AND_OPERATOR 2
#define CMD_CHAIN_OPERATOR 3

#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

#define USE_CUSTOM_GETLINE 0
#define USE_CUSTOM_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define HISTORY_MAX_LINES 4096

extern char **custom_environment;


typedef struct StringListNode {
    int number;
    char *string;
    struct StringListNode *next;
} StringList;

typedef struct CommandInfo {
    char *argument;
    char **argumentVector;
    char *path;
    int argumentCount;
    unsigned int lineCounter;
    int errorNumber;
    int lineCounterFlag;
    char *filename;
    StringList *env;
    StringList *history;
    StringList *alias;
    char **customEnvironment;
    int environmentChanged;
    int commandStatus;

    char **commandBuffer;
    int commandBufferType;
    int readDescriptor;
    int historyCounter;
} Info;

#define INFO_INITIALIZER \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

typedef struct BuiltInCommand {
    char *commandType;
    int (*function)(Info *);
} BuiltInCommandTable;

int customShellLoop(Info *, char **);
int findCustomBuiltIn(Info *);
void findCommand(Info *);
void forkCommand(Info *);

int isCustomCommand(Info *, char *);
char *duplicateCharacters(char *, int, int);
char *findExecutablePath(Info *, char *, char *);

void printError(char *);
int errorPutCharacter(char);
int putToDescriptor(char c, int descriptor);
int putsToDescriptor(char *str, int descriptor);

int customStringLength(char *);
int customStringCompare(char *, char *);
char *startsWith(const char *, const char *);
char *customStringConcatenate(char *, char *);

char *customStringCopy(char *, char *);
char *customStringDuplicate(const char *);
void customPrint(char *);
int customPutCharacter(char);

char *customStringCopyN(char *, char *, int);
char *customStringConcatenateN(char *, char *, int);
char *customStringFindCharacter(char *, char);

char **customStringTokenize(char *, char *);
char **customStringTokenizeV2(char *, char);

char *customMemorySet(char *, char, unsigned int);
void customFree(char **);
void *customReallocate(void *, unsigned int, unsigned int);

int customFreeBlock(void **);

int customAtoi(info_t *);
int isDelimiter(char, char *);
int isAlphabetic(int);
int customAtoi(char *);

int customErrorAtoi(char *);
void printCustomError(info_t *, char *);
int printInteger(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

int customExit(info_t *);
int customChangeDirectory(info_t *);
int customHelp(info_t *);

int customHistory(info_t *);
int customAlias(info_t *);

ssize_t getCustomInput(info_t *);
int customGetLine(info_t *, char **, size_t *);
void handleSigInt(int);

void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

char *_getCustomEnvironment(info_t *, const char *);
int customEnvironment(info_t *);
int customSetEnvironment(info_t *);
int customUnsetEnvironment(info_t *);
int populateEnvironmentList(info_t *);

char **getCustomEnvironment(info_t *);
int customUnsetEnvironment(info_t *, char *);
int customSetEnvironment(info_t *, char *, char *);

char *getHistoryFile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHistoryList(info_t *info, char *buffer, int lineCount);
int renumberHistory(info_t *info);

StringList *addStringListNode(StringList **, const char *, int);
StringList *addStringListNodeToEnd(StringList **, const char *, int);
size_t printStringList(const StringList *);
int deleteNodeAtIndex(StringList **, unsigned int);
void freeStringList(StringList **);

size_t listLength(const StringList *);
char **listToStrings(StringList *);
size_t printList(const StringList *);
StringList *nodeStartsWith(StringList *, char *, char);
ssize_t getNodeIndex(StringList *, StringList *);

int isCommandChain(info_t *, char *, size_t *);
void checkCommandChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVariables(info_t *);
int replaceString(char **, char *);

#endif
