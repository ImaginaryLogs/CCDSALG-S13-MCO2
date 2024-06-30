#include "../src/utils.h"
#include "../src/queue.h"

#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#ifdef __linux__
    #include <unistd.h>
#endif

#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

// How much delay there must be for each repeat in a unit test.
#define UNIT_TEST_REPEAT_DELAY (1)
#define LOG_ENABLE_TEST_VERBOSE (1)
#define LTEST LOG_ENABLE_TEST_VERBOSE

#if LTEST 
  /**
  * A developer's version of printf that is togglable - useful for debugging.
  */
  #define OUT(X, ...) do {if (X) fprintf(stdout, __VA_ARGS__);}while(0)
#else
  #define OUT(X, ...)
#endif

/**
 * Reference: https://www.youtube.com/watch?v=IZiUT-ipnj0&list=WL
 * [1] Uses errno from <errno.h> to trace errors in code. Libraries uses errno to store error information. 
 * [2] __FILE__ is a preprocessor macro for the name of the file
 * [3] __LINE__ is also a macro, but the for the line number at which the macro is executed.
 */
#define returnErrorTrace(...) do{ fprintf(stdout, "%s[ERROR ]%s %s (LINE: ~%d): %s\n", F_RED, F_NORMAL, __FILE__, __LINE__, strerror(errno)); exit(errno);}while(0)

/**
 * When a SIGSEGV signal is sent, then print what happened and exit.  
 * @param receivingSignal: The signal response the process will insert to
 * @retval None
 */
void detectCrash(int receivingSignal){
    if (receivingSignal == SIGSEGV){
        printf("%s[ERROR ]%s Segfault happened :(. Check Testcases. \nError: %s\n", F_RED, F_NORMAL, strerror(errno));
        exit(-1);
    } else if (receivingSignal == SIGABRT) {
        printf("%s[ERROR ]%s Stack Smashing :(. Check Testcases. \nError: %s\n", F_RED, F_NORMAL, strerror(errno));
        exit(-4);
    }
}

// How many failed tests to tolerate
#define MAX_FAILED_TESTS 5
#define MAX_INPUTLINES 56

/** 
 * This struct stores statistics within testing.
 * @param currentTestNumber - stores the current test
 * @param currentFailutureTop - stores the amount of savable failed test there are
 * @param succesfulTests - stores succesful tests
 * @param failedTests - stores failed tests
 * @param failedTestNumber - an array of which tests failed 
 */ 
struct testStatistics {
    short currentTestNumber;
    short currentFailureTop;
    short successfulTests;
    short failedTests;
    short failedTestNumber[MAX_FAILED_TESTS];
};

/**
 * Prints the header of a unit test
 * @param  isActualExpected: The type of test changes the printed header
 * @retval None
 */
void printTestHeader(int isActualExpected){
    if (isActualExpected == true){
        printf("\n%s#=----= [Example] =----=#%s\n", B_GREEN, F_NORMAL);
    } else {
        printf("\n%s#=----= [Counter] =----=#%s\n", B_YELLOW, F_NORMAL);
    }
}



/**
 * A unit test that tests one actual value to the one expected and see if its the same with actual.
 * @brief String version of testing. Checks even for null values.
 * @param  *Description: Description of the Test
 * @param  actualValue: The actual code output
 * @param  expectedValue: The value that is expected 
 * @param  isActualExpected: Boolean whether or not they match
 * @retval Boolean whether testing is successful
 */
int assertCaseString(char *Description, char *actualValue, char *expectedValue, int isActualExpected){
    String7 strTruth = "TRUE";
    String7 strFalse = "FALSE";
    int nResult = 0;
    printTestHeader(isActualExpected);
    printf("| \n| %s\n", Description);
    OUT(LTEST, "| \n|  Actual: %s\n", actualValue);
    OUT(LTEST, "|  Expect: %s\n| \n", expectedValue);
    if (actualValue != NULL && expectedValue != NULL){
        nResult = (strcmp(actualValue, expectedValue) == 0) == isActualExpected ;
    } else {
        nResult = (actualValue == expectedValue) == isActualExpected ;
    }
    printf("| Result: %s\n| \n", nResult ? strTruth : strFalse);
    return nResult;
}

/**
 * A unit test that tests one actual value to the one expected and see if its the same with actual.
 * @brief Integer version of testing.
 * @param  *Description: Description of the Test
 * @param  actualValue: The actual code output
 * @param  expectedValue: The value that is expected 
 * @param  isActualExpected: Boolean whether or not they match
 * @retval Boolean whether testing is successful
 */
int assertCaseInteger(char *Description, int actualValue, int expectedValue, int isActualExpected){
    String7 strTruth = "TRUE";
    String7 strFalse = "FALSE";

    printTestHeader(isActualExpected);
    printf("| \n| %s\n", Description);
    OUT(LTEST, "| \n| Actual: %d", actualValue);
    OUT(LTEST, " Expect: %d\n| \n", expectedValue);
    printf("| Result: %s\n| \n", (actualValue == expectedValue) == isActualExpected ? strTruth : strFalse);
    return (actualValue == expectedValue) == isActualExpected;
}

/**
 * A unit test that tests one actual value to the one expected and see if its the same with actual. 
 * @brief Character Version of testing.
 * @param  *Description: Description of the Test
 * @param  actualValue: The actual code output
 * @param  expectedValue: The value that is expected 
 * @param  isActualExpected: Boolean whether or not they match
 * @retval Boolean whether testing is successful
 */
int assertCaseChar(char *Description, char actualValue, char expectedValue, int isActualExpected){
    String7 strTruth = "TRUE";
    String7 strFalse = "FALSE";

    printTestHeader(isActualExpected);

    printf("| \n| %s\n", Description);
    OUT(LTEST, "| \n| Actual: %c", actualValue);
    OUT(LTEST, " Expect: %c\n| \n", expectedValue);
    printf("| Result: %s\n| \n", (actualValue == expectedValue) == isActualExpected ? strTruth : strFalse);
    return (actualValue == expectedValue) == isActualExpected;
}

/**
 * @brief Initialize and create an empty Test Statistics struct for use.
 * @return Empty struct testStatistics 
 */
struct testStatistics createTestStatistics(){
    struct testStatistics testStats;
    testStats.currentFailureTop = 0;
    testStats.currentTestNumber = 1;
    testStats.successfulTests = 0;
    testStats.failedTests = 0;
    int i = 0;
    for(i = 0; i < MAX_FAILED_TESTS; i++){
        testStats.failedTestNumber[i] = 0;
    }
    return testStats;
}


/**
 * Update tests statistics whether or not it works.
 * @param *testStats: Test Statistics
 * @param assertReturn: The return statement of the assertion. 
 * @retval None
 */
void testCase(struct testStatistics *testStats, int assertReturn){
    if (assertReturn == 0){
        if (testStats->currentFailureTop < MAX_FAILED_TESTS) {
            testStats->failedTestNumber[testStats->currentFailureTop] = testStats->currentTestNumber;
        } else {
            printf("%s[CRITICAL][FAILED]%s TOO MANY TESTS FAILED, check changes NOW!\n", F_RED, F_NORMAL);
        }
        ++(testStats->failedTests);
        ++(testStats->currentFailureTop);
    } else
        ++(testStats->successfulTests);
    
    printf("#=---= Test No: %02d =---=#\n\n", testStats->currentTestNumber);

    ++(testStats->currentTestNumber);
}

/**
 * Print tests statistics to the console for viewing.
 * @note   
 * @param  *testStats: 
 * @retval None
 */
void printTestStatistics(struct testStatistics *testStats){
    int i = 0;
    printf("#=---=[ TESTING STATISTICS ]=---=#\n|\n");
    printf("|  No. of Tests Units: %d\n", testStats->currentTestNumber - 1);
    printf("|  %sSuccess%s  : %d\n", F_GREEN, F_NORMAL, testStats->successfulTests);
    printf("|  %sFailed%s   : %d\n", F_RED, F_NORMAL, testStats->failedTests);
    printf("|  %sCases Failed%s : [ ", F_RED, F_NORMAL);
    for (i = 0; i < MAX_FAILED_TESTS; i++)
       printf("%d ", testStats->failedTestNumber[i]);
    printf("]\n|\n");
    printf("#=------------------------------=#\n");
}

/**
 * Prints Tests Statistcs to STDERR since pipe of test_controller communicates there.
 * @param *testStats: 
 * @param communicatingPipe[]: 
 * @retval None
 */
void printCommunicatingPipeTestStatistics(struct testStatistics *testStats){
    int i = 0;
    fprintf(stderr, "%d ", testStats->currentFailureTop);
    fprintf(stderr, "%d ", testStats->currentTestNumber);
    fprintf(stderr, "%d ", testStats->successfulTests);
    fprintf(stderr, "%d ", testStats->failedTests);
    for(i = 0; i < MAX_FAILED_TESTS; i++){
        fprintf(stderr, "%d ", *(testStats->failedTestNumber + i));
    }
}

enum textlineState {
    EMPTY_READ,
    LAST_STRING_EOF = -1,
    SUCCESFUL_READ,
    OVERFLOWING_STRING
};

/**
 * Reads a line in a textfile and updates strOutput. Depending on how it is, and where it is located, it will return the corresponding reading state.
 * @param  *fileToRead: file to read
 * @param  *strOutput: the Output
 * @retval LAST_STRING_EOF      (-1) if the string read is the last one
 * @retval SUCCESFUL_READ       (0)  if succesfully read string
 * @retval OVERFLOWING_STRING   (1)  if the string cannot fit the 255 string limit
 */
int textline255Reader(FILE *fileToRead, char *strOutput){
    String255 currentLine = "";
    int maxLength = 255;
    int hasOverwrittenSecondLast    = 0;
    int hasOverwrittenLastChar      = 0;
    int hasPossibleOverflow         = 0;
    int hasExcessWhitespace         = 0;
    int errTextReaderState = EMPTY_READ;

    currentLine[maxLength] = 'A';

    fgets(currentLine, maxLength + 1, fileToRead); 
    // size of array = maxCharLength + 1, allows exact
    // 255-character-length input

    // ### Overwrite flags for checking ###
    hasOverwrittenSecondLast  = currentLine[maxLength - 1] != '\n';
    hasOverwrittenLastChar    = currentLine[maxLength] == '\0';
    hasPossibleOverflow       = hasOverwrittenSecondLast && hasOverwrittenLastChar;
    hasExcessWhitespace       = (hasPossibleOverflow) ? (fgetc(fileToRead) == '\n') : false; 
    // If input string length matches maxCharLength, then it
    // should have '\n' only as excess.

    // ### Error handling ###
    if (feof(fileToRead)) {
        errTextReaderState = LAST_STRING_EOF;
    } else if (!hasPossibleOverflow || hasExcessWhitespace) {
        errTextReaderState = SUCCESFUL_READ;
    } else {
        errTextReaderState = OVERFLOWING_STRING;
    }

    // ### Clean-up of '\n' ###
    if (!hasExcessWhitespace) {
      currentLine[maxLength] = '\0'; // erases 'A' normally and '\n' if exact 255 = 255 limit.
      currentLine[strlen(currentLine) - 1] = '\0'; // erase the '\n' that fgets() appends normally
    }
    strcpy(strOutput, currentLine);
    return errTextReaderState;  
}


/**
 * Opens a file and returns a file pointer. Exits the program if it does not detect it.
 * @param  *fileName: Name of file
 * @retval FILE * 
 */
FILE *fileValidOpen(char *fileName){
    String127 errMessage = "";
    FILE *fOutput = fopen(fileName, "r");

    if (fOutput == NULL) {
        sprintf(errMessage, "Filename %s does not exist.", fileName);
        printf("%s\n", errMessage);
        returnErrorTrace();
    }
    return fOutput;
}

/**
 * Turns tokens separated by space to be placed on to the queue
 * @param  *strInput: string of tokens to enqueue on the queue
 * @param  *Queue: The Queue 
 * @retval None
 */
void stringTokensToQueue(char *strInput, Queue *Queue){
    String255 token = "";
    int i;
    for (i = 0; i < strlen(strInput); i++){
        if (strInput[i] != ' ')
            strncat(token, strInput + i, 1);
        else {
            enqueue(Queue, token);
            strcpy(token, "");
        }
    }
}


#endif 