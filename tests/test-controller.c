#include <errno.h>

#include <limits.h>
#include <fcntl.h>
#include "test-utils.h"
#include <signal.h>
#include <stdarg.h>

#ifdef __linux__
    #include <sys/wait.h>
    #include <unistd.h>
#elif _WIN32
#endif

#define TEST_CASES 4

enum TestType{
    NONE,
    IN,
    OUT
};

enum processHierarchy {
    MAIN, 
    PREPARE,
    BUILD,
    EXECUTE
};

enum typeHeader {
    STARTS,
    OK,
    DONE,
    WAITING,
    WARNING,
    FAILED,
    NOTE
};

/**
 * A struct to store parent-child pid
 * @param initialprocessID : stored process id of a parent or a child
 * @param testStatus : the returned exit result of the child.
 */
struct testID {
    int initialprocessID;
    int testStatus;
};

/**
 * Stores the statistics of executing tests.
 * @param test_processes Stores a test's parent-child interaction
 * @param nTestOrder Current test to execute
 * @param nTestErrors Current number of test errors
 * @param nTestOk Current number of successful tests
 */
struct statsExecuteTest {
    struct testStatistics test_stats[TEST_CASES];
    struct testID test_processes[TEST_CASES];
    int failedTests[TEST_CASES];
    int nTestOrder;
    int nTestErrors;
    int nTestOk;
};

/**
 * @brief  
 * @note   
 * @retval 
 */
struct statsExecuteTest initializeExecutionStats(){
    struct statsExecuteTest stats;
    int i = 0, j = 0;

    for (i = 0; i < TEST_CASES; i++){
        stats.test_processes[i].initialprocessID = 0;
        stats.test_processes[i].testStatus = 0;

        stats.failedTests[i] = 0;

        stats.test_stats[i].currentFailureTop = 0;
        stats.test_stats[i].currentTestNumber = 1;
        stats.test_stats[i].failedTests = 0;
        stats.test_stats[i].successfulTests = 0;

        for (j = 0; j < 5; j++){
            stats.test_stats[i].failedTestNumber[j] = 0;
        }
    }
    stats.nTestOk = 0;
    stats.nTestOrder = 0;
    stats.nTestErrors = 0;
    return stats;
}

void printExecuteStats(struct statsExecuteTest *stats){
    int nOverall =0, nOverallCorrect = 0, nOverallErrors = 0;
    int i = 0;
    printf("\n");
    printf("#=- RESULT of Executing the Tests -=#\n|\n");
    printf("|  ALL: %d\n", stats->nTestOrder);
    printf("|  %sOKS%s: %d\n", F_GREEN, F_NORMAL, stats->nTestOk);
    printf("|  %sERS%s: %d\n", F_RED, F_NORMAL, stats->nTestErrors);
    printf("|  %sFAILED%s : [ ", F_RED, F_NORMAL);
    for (i = 0; i < TEST_CASES; i++){
        printf("%d ", stats->failedTests[i]);
    }
    printf("]\n");
    printf("|\n.\n");

    for (i = 0; i < TEST_CASES; i++){
        printf("\n### Tests %d\n", i+1);
        printTestStatistics(stats->test_stats + i);
        printf("\n");
        nOverall += (stats->test_stats + i)->currentTestNumber - 1;
        nOverallCorrect += (stats->test_stats + i)->successfulTests;
        nOverallErrors += (stats->test_stats + i)->failedTests;
    }
    
    float Grade = nOverallCorrect*1.0/nOverall * 100;
    printf("Overall done unit tests: %d\n", nOverall);
    printf("Overall corrects :>    : %d\n", nOverallCorrect);
    printf("Overall errors :(      : %d\n", nOverallErrors);
    printf("DLSU GRADE: %.1f%%\n", Grade);

    if (Grade >= 90.0)
        printf("LETS GOOOO! PERFECT MCO1!!!\n\n");
}

void printRelationshipState(int processHierarchy, int typeHeader, char * formattedString,...){
    switch(processHierarchy) {
        default:
        case MAIN:
            printf("[Parent]");
            break;
        case PREPARE:
            printf("[Prepar]");
            break;
        case BUILD:
            printf("[Buildr]");
            break;
        case EXECUTE:
            printf("[Excutr]");
            break;
    }

    switch (typeHeader) {
        case STARTS:
            printf("%s[STARTS]%s:", F_GREEN, F_NORMAL);
            break;
        case OK:
            printf("%s[  OK  ]%s:", F_GREEN, F_NORMAL);
            break;
        case DONE:
            printf("%s[ DONE ]%s:", F_GREEN, F_NORMAL);
            break;
        case WARNING:
            printf("%s[ !!!! ]%s:", F_YELLOW, F_NORMAL);
            break;
        case WAITING:
            printf("%s[WAIT..]%s", F_YELLOW, F_NORMAL);
            break;
        case NOTE:
            printf("%s[ NOTE ]%s:", F_YELLOW, F_NORMAL);
            break;
        case FAILED:
            printf("%s[FAILED]%s:", F_RED, F_NORMAL);
            break;   
    }
    printf(" ");
    va_list arguments;
    va_start(arguments, formattedString);
    vprintf(formattedString, arguments);
    va_end(arguments);
}

int isThisAChildProcess(int childID){
    return childID == 0;
}

int hasFailedToCreateChild(int childID){
    return childID == -1;
}

void useStreamInputFile(char *nameFile){
    #if __linux__
    int fileIn = open(nameFile, O_RDONLY, 0777);

    if (fileIn == -1) 
        returnErrorTrace();

    dup2(fileIn, STDIN_FILENO); 
    close(fileIn);
    #endif
}

void createStreamOutputFile(char *nameFile){
    #if __linux__
    String127 outputFileName = "";
    sprintf(outputFileName, "%s-RESULT.txt", nameFile);

    int fileOut = open(outputFileName, O_CREAT | O_TRUNC | O_RDWR, 07777);

    if (fileOut == -1) 
       returnErrorTrace();

    dup2(fileOut, STDOUT_FILENO);
    close(fileOut);
    #endif
}

/**
 * Rebuilds the test code and executes it.
 * @param  testType: Type of test
 * @param  *nameFile: Name of testing file
 * @param  *inputFileName: Name of input file
 * @retval None
 */
void prepareTestCase(int testType, char *nameFile, char *inputFileName, int communicatingPipe[]){
    String127 buildcodeFileName = "";
    String127 executingFileName = "";
    int childExitStatus = 0;

    sprintf(buildcodeFileName, "%s.c", nameFile);
    sprintf(executingFileName, "./%s", nameFile);

    #if __linux__
    printf("[ChildA]%s[EXECUT]%s %s.c\n", F_YELLOW, F_NORMAL, nameFile);
    printf("  Test-Type ID: %d\n", testType);
    printf("  %sChild's  PID%s: %d\n", F_YELLOW, F_NORMAL, getpid());
    printf("  %sParent's PID%s: %d\n", F_YELLOW, F_NORMAL, getppid());

    close(communicatingPipe[0]);
    dup2(communicatingPipe[1], STDERR_FILENO);
    close(communicatingPipe[1]);


    int prepareID = fork();

    if (prepareID == 0){
        printf("[ChildB][REBUILD]: Deleting and Compliling .c code...\n");
        remove(nameFile);
        execl("/usr/bin/gcc", "gcc", buildcodeFileName, "-o", nameFile, (char *) NULL);
        returnErrorTrace();
    } else {
        printf("[ChildC][WAITIN]: Waiting for ChildB to finish...\n");
        wait(&childExitStatus);
        
        if (WEXITSTATUS(childExitStatus) == 0) {
            printf("[ChildC]\n");
            printf("Test Type: %d\n", testType);

            if ((testType & IN ) > 0){
                printf("Test's Input: %s\n", inputFileName);
                useStreamInputFile(inputFileName);
            }    

            if ((testType & OUT) > 0){
                printf("Test's Output: %s\n", nameFile);
                createStreamOutputFile(nameFile);
            }
            execl(executingFileName, nameFile, (char *) NULL);
            returnErrorTrace();
        }
        exit(-2);
    }
    #endif
}

void interpretExecutionResult(struct statsExecuteTest *stats, int resultingProcessID, int *thisTestNumber, int *thisTestChildStatus){
    int hasChildExited;
    int ChildExitStatus;
    #if __linux__
    hasChildExited = WIFEXITED(*thisTestChildStatus);
    ChildExitStatus = WEXITSTATUS(*thisTestChildStatus);
    #elif __WIN32__
        hasChildExited = -1;
        ChildExitStatus = 253;
    #endif
    int hasChildSuccessfulDoneTest = ChildExitStatus == 0;

    if (!hasChildExited) {
        return;
    }

    if (hasChildSuccessfulDoneTest) {
        printRelationshipState(MAIN, DONE, "Child Process Done, PID: %d\n", resultingProcessID);
        (stats->nTestOk)++;
        return;
    } 

    printRelationshipState(MAIN, DONE, "PID: %d -> Status code: %d\n", resultingProcessID, ChildExitStatus);
    switch(ChildExitStatus){
        case 255:
            printRelationshipState(MAIN, FAILED, "Result shows SEGFAULT! Check code.\n");
            break;
        case 254:
            printRelationshipState(MAIN, WARNING, "Result shows FAILED GCC! Check filenames\n");
            break;
        case 253:
            printRelationshipState(MAIN, WARNING, "Result shows Windows OS! Change Systems in order for auto-test to work.\n");
            break;
        
    }
    stats->failedTests[stats->nTestErrors] = *thisTestNumber;
    (stats->nTestErrors)++;
    printf("\n");
}



#if __linux__
/**
 * Decodes the STRERR to figure out what the test statistics are for each tests.
 * @note   
 * @param  communicatingPipe[]: 
 * @retval None
 */
void readingIndividualTestStatistics(struct testStatistics *ts, int communicatingPipe[] ){
    char receiverChar = '\0';
    char statisticsString[1024] = "";
    String255 infoToken = "";
    int nReturn = 0;
    int isDecodingMessage = true;
    int charReaderPosition    = 0;
    int numberReceived = 0;
    do {
        nReturn = read(communicatingPipe[0], &receiverChar, 1);
        strncat(statisticsString, &receiverChar, 1);
        if ((int) strlen(statisticsString) >= 1023)
            strcpy(statisticsString, "");
    } while (nReturn > 0);

    while (isDecodingMessage && (int) strlen(statisticsString) > 0) {
        receiverChar = statisticsString[charReaderPosition];
        
        if (receiverChar != ' ' && receiverChar != '\0' && receiverChar != '\n' && receiverChar != '\t'){
            strncat(infoToken, &receiverChar, 1);
        } else if (receiverChar == '\0') {
            isDecodingMessage = false;
        } else {

            switch (numberReceived){
                case 0:
                    ts->currentFailureTop = atoi(infoToken);
                    break;
                case 1:
                    ts->currentTestNumber = atoi(infoToken);
                    break;
                case 2:
                    ts->successfulTests = atoi(infoToken);
                    break;
                case 3:
                    ts->failedTests = atoi(infoToken);
                    break;
                default:
                    *(ts->failedTestNumber + numberReceived - 4) = atoi(infoToken);
            }
            
            if (numberReceived == 2 + MAX_FAILED_TESTS){
                isDecodingMessage = false;
            }

            numberReceived++;
            strcpy(infoToken, "");
        }


        charReaderPosition++;
    }
}
#endif

/**
 * Prepares an environment for testing 
 * @param  *stats: stats to update
 * @param  TestType: 
 * @param  *fileName: 
 * @param  *inputFileName: 
 * @retval None
 */
void handleTestCase(struct statsExecuteTest *stats, int TestType, char *fileName, char *inputFileName){
    int *thisTestNumber = &stats->nTestOrder;
    // Parent-Child Details
    struct testID *thisTestDetails  = stats->test_processes + *thisTestNumber;
    int *thisTestPID                = &thisTestDetails->initialprocessID;
    int *thisTestChildStatus        = &thisTestDetails->testStatus;
    
    int resultingProcessID;
    #if __linux__
    
    // Communication for future statistics.
    int communicatingPipe[2];
    pipe(communicatingPipe);

    *thisTestPID = fork();

    // Check if proccess was forked/split into parent and child process successfully.
    if (hasFailedToCreateChild(*thisTestNumber)){
        returnErrorTrace();
    }

    // Make child process do the performance
    if (isThisAChildProcess(*thisTestPID)){
        prepareTestCase(TestType, fileName, inputFileName, communicatingPipe);
    }
    close(communicatingPipe[1]);

    // Parent should read the test statistics.

    readingIndividualTestStatistics(stats->test_stats + stats->nTestOrder, communicatingPipe);
    close(communicatingPipe[0]);

    // Checking of results
    resultingProcessID = wait(thisTestChildStatus);
    #endif
    interpretExecutionResult(stats, resultingProcessID, thisTestNumber, thisTestChildStatus);
    
    (*thisTestNumber)++;
}


/**
 * @brief Executes tests automatically given their test type, name of the file, and any input files.
 * @note Only works with linux-based systems.
 * @param  configNames[][3]: String separated config. First is test type (3 - with input file and output, 2 - with output only, 1 with input only, 0 - none), name of `.c` file, and the name of the input
 * @retval None
 */
void test_controller(String63 configNames[][3]){
    struct statsExecuteTest stats = initializeExecutionStats();
    int thisPID = 0;
    printf("\n");
    #if __linux
        thisPID = getpid();
    #elif __WIN32__
        printRelationshipState(MAIN, WARNING, "\n\tDetected Windows OS, please use a Linux-based system.\n\tThat, or implement Windows Equivalent Code.\n\n");
    #endif

    printRelationshipState(MAIN, STARTS, "test-controller.c, PID: %d\n", thisPID);

    int i = 0;
    for(i = 0; i < TEST_CASES; i++){
        printf("\n");
        printRelationshipState(MAIN, STARTS, "No: %d: %s%s.c%s\n", stats.nTestOrder, F_YELLOW, configNames[i][1], F_NORMAL);
        handleTestCase(&stats, atoi(configNames[i][0]), configNames[i][1], configNames[i][2]);
    }
        
    printRelationshipState(MAIN, NOTE, "All Tests are Complete!\n");
    printExecuteStats(&stats);
    // printf("ALL: %d, DONE: %d, FAILED: %d\n", TEST_CASES, stats.nTestOk, stats.nTestErrors);
    printRelationshipState(MAIN, NOTE, "\n\tThis file automatically compiles tests within the same folder.\n\tMay need to change code to separate it per folder.\n\n");

    #if __WIN32__
        printRelationshipState(MAIN, WARNING, "\n\tDetected Windows OS, please use a Linux-based system.\n\tThat, or implement Windows Equivalent Code.\n\n");
    #endif
}

int main(){
    signal(SIGSEGV, detectCrash);
    
    String63 configNames[TEST_CASES][3] = {
        {"2", "test-01-stack", ""},
        {"2", "test-02-queue", ""},
        {"2", "test-04-evaluate-postfix"             , ""},
        {"2", "test-05-main"}
    };

    test_controller(configNames);

    return 0;
}