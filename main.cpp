#define PI 3.141592653589793
//#define SFML_STATIC
#undef UNICODE
#include <winsock2.h>
#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <Winuser.h>
#include <assert.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <dirent.h>
#include <locale.h>
#include <unistd.h>
#include <psapi.h>


#include <stdio.h>
#define NBT_IMPLEMENTATION
#define NBT_OWN_ZLIB
//#define NBT_BUFFER_SIZE 100000

extern int main_nbt();
extern void do_world(char* filename);
extern int xallocator_test(void);
PROCESS_MEMORY_COUNTERS check_memory_tofile(char* name);
//PROCESS_MEMORY_COUNTERS memory;

extern "C" void xalloc_stats_to_file(char* name);
extern uint8_t* load_region_file(char* filename, size_t* size);

extern void READ_WORLD(char* filename);
extern void READ_WORLD_TO_DIRS(char* filename);
extern void READ_WORLD_TO_GZIPS(char* filename);

extern void READ_REGION(char* filename);
extern void READ_REGION_TO_DIR(char* filename);
extern void READ_REGION_TO_GZIP(char* filename);

extern void WRITE_REGION(char* filename);
extern void WRITE_REGION_FROM_DIRS(char* filename);

extern void WRITE_WORLD_TO_MCA(char* filename);
extern void region_header(char* filename);
extern void do_one(char* filename);
extern main_nbt(char* region_name);
extern void MAKE_MCA_FROM_WORLD_NBT_GZIPS(char* worldname);
extern void test_write_to_and_read_from_memory();

extern double tied,tied_total,tied_total_total;
extern void test_tha_shit(int n);

extern char* pretty_number(const long long int input_val);
extern size_t mem_start;
extern size_t mem_now;
extern size_t mem_was;
extern long long int mem_dif;
extern long long int mem_tot_dif1;
extern long long int mem_tot_dif2;
extern size_t mem_first;
extern int loop;
extern long long unsigned int call;
extern long long int total_count;
extern long long unsigned int total_call;
extern int count_loops;
extern PROCESS_MEMORY_COUNTERS memory;
//extern int first_mem;


int fast=1;

int main(int argc, char *argv[]) {
    if (argc>1) {
        int send_message=0;
        int n;
        if (argc>2) n=atoi(argv[2]);

        //program.exe world2nbtdir <WorldSaveDir>
        //reads:    all the r.*.*.mca files from <WorldSaveDir>/region/r.*.*.mca
        //writes:   <WorldSaveDir>/nbt/r.*.*/<ColumnNumber>.gzip.nbt (nbt's containing column from region files)
        //call:     from directory above the <WorldSaveDir>/region/r.*.* director(y/ies).
        if (        strcmp(argv[1],"world2nbtdir"   )==0) { READ_WORLD_TO_DIRS(             argv[2]);   send_message='x';   return 0; }

        //program.exe world2nbt <WorldSaveDir>
        //reads:    all the r.*.*.mca files from <WorldSaveDir>/region/r.*.*.mca
        //writes:   <WorldSaveDir>/nbt/r.*.*.gzip.nbt (nbt's containing one region file)
        //call:     from directory above the <WorldSaveDir>/region/r.*.* director(y/ies).
        if (        strcmp(argv[1],"world2nbt"      )==0) { READ_WORLD_TO_GZIPS(            argv[2]);   send_message='x';   return 0; }

        //program.exe header2nbt <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>.header.gzip.nbt & <r.x.z>.header.txt in current dir
        else if (   strcmp(argv[1],"header2nbt"     )==0) { region_header(                  argv[2]);   send_message='x';   return 0; }

        //program.exe mca2nbtdir <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>/<ColumnNumber>.gzip.nbt files
        else if (   strcmp(argv[1],"mca2nbtdir"    )==0) { READ_REGION_TO_DIR(                    argv[2]);   send_message='x';   return 0; }

        //program.exe mca2nbt <r.x.z>.mca
        //reads:    region file <r.x.z>.mca
        //writes:   <r.x.z>.gzip.nbt file
        else if (   strcmp(argv[1],"mca2nbt"    )==0) { READ_REGION_TO_GZIP(                        argv[2]);   send_message='x';   return 0; }

        //program.exe nbtdir2mca <r.x.z>
        //reads:    <r.x.z>/*.gzip.nbt files (nbt files containing columns)
        //writes:   region file <r.x.z>.mca
        //call:     from directory above <r.x.z>/*.gzip.nbt
        else if (   strcmp(argv[1],"nbtdir2mca"    )==0) { WRITE_REGION_FROM_DIRS(                   argv[2]);   send_message='x';   return 0; }

        //program.exe nbtdir2world <WorldSaveDir>
        //reads:    <WorldSaveDir>/nbt/r.*.*/<ColumnNumber>.gzip.nbt
        //writes:   all the r.*.*.mca to <WorldSaveDir>/nbt/r.*.*.mca
        //call:     from directory above the <WorldSaveDir>/nbt/r.*.* director(y/ies).
        else if (   strcmp(argv[1],"nbtdir2world"  )==0) { MAKE_MCA_FROM_WORLD_NBT_GZIPS(  argv[2]);   send_message='x';   return 0; }

        //program.exe worldnbt2mca <WorldName>.gzip.nbt | <WorldName>.zlib.nbt | <WorldName>.nbt
        //reads:    <WorldName>.gzip.nbt or <WorldName>.zlib.nbt or <WorldName>.nbt
        //writes:   all r.*.*.mca region files contained in <WorldName>.gzip.nbt or <WorldName>.zlib.nbt or <WorldName>.nbt
        //call:     from <WorldSaveDir>/nbt
        else if (   strcmp(argv[1],"nbt2world"  )==0) { WRITE_WORLD_TO_MCA(             argv[2]);   send_message='x';   return 0; }

        //program.exe nbt2mca <r.x.z>.gzip.nbt | <r.x.z>.zlib.nbt | <r.x.z>.nbt
        //reads:    <r.x.z>.gzip.nbt or <r.x.z>.zlib.nbt or <r.x.z>.nbt file
        //writes:   <r.x.z>.mca region file contained in <r.x.z>.gzip.nbt or <r.x.z>.zlib.nbt or <r.x.z>.zlib.nbt
        //call:     from <WorldSaveDir>/nbt
        else if (   strcmp(argv[1],"nbt2mca"    )==0) { WRITE_REGION(                   argv[2]);   send_message='x';   return 0; }
        else if (   strcmp(argv[1],"test"    )==0) { test_tha_shit(n);   send_message='x';   return 0; }
    }
    test_tha_shit(2);
    printf("Flushing memory....trying CTRL_C_EVENT\n");
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
    return 0;
}




BOOL GetProcessMemoryInfo(
  HANDLE                   Process,
  PPROCESS_MEMORY_COUNTERS ppsmemCounters,
  DWORD                    cb
);


PROCESS_MEMORY_COUNTERS check_memory2()
{
    PROCESS_MEMORY_COUNTERS memory;
    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
    static PROCESS_MEMORY_COUNTERS memory_old=memory;

//    static FILE* file=fopen("memory.txt","w");
//    fprintf(file,"            WorkingSetSize = %u\n", memory.WorkingSetSize);

    printf("                        cb =                                      \r");
    printf("                        cb = %ld\n", memory.cb);
    printf("            PageFaultCount =                                      \r");
    printf("            PageFaultCount = %ld\n", memory.PageFaultCount);
    printf("        PeakWorkingSetSize =                                      \r");
    printf("        PeakWorkingSetSize = %u\n", memory.PeakWorkingSetSize);
    printf("            WorkingSetSize =                                      \r");
    printf("            WorkingSetSize = %u\n", memory.WorkingSetSize);
    printf("   QuotaPeakPagedPoolUsage =                                      \r");
    printf("   QuotaPeakPagedPoolUsage = %u\n", memory.QuotaPeakPagedPoolUsage);
    printf("       QuotaPagedPoolUsage =                                      \r");
    printf("       QuotaPagedPoolUsage = %u\n", memory.QuotaPagedPoolUsage);
    printf("QuotaPeakNonPagedPoolUsage =                                      \r");
    printf("QuotaPeakNonPagedPoolUsage = %u\n", memory.QuotaPeakNonPagedPoolUsage);
    printf("    QuotaNonPagedPoolUsage =                                      \r");
    printf("    QuotaNonPagedPoolUsage = %u\n", memory.QuotaNonPagedPoolUsage);
    printf("             PagefileUsage =                                      \r");
    printf("             PagefileUsage = %u\n", memory.PagefileUsage);
    printf("         PeakPagefileUsage =                                      \r");
    printf("         PeakPagefileUsage = %u\n", memory.PeakPagefileUsage);
    return memory;
}
#ifdef SFML_ONBOARD
extern int first_mem;
#else
int first_mem=0;
#endif
PROCESS_MEMORY_COUNTERS check_memory_tofile(char* name)
{
    FILE* file;

    GetProcessMemoryInfo(GetCurrentProcess(), &memory, sizeof(memory));
    static PROCESS_MEMORY_COUNTERS memory_old=memory;
    int skip=0;
    if (strlen(name)==0) {
        skip=1;
    }

    if (skip==0)file=fopen("memory.txt","a");
    if (first_mem==1) {
        first_mem=0;
        if (skip==1) {
            file=fopen("memory.txt","a");
        }
        fprintf(file,"   TIME   LOOPS   TOTAL       MEM FIRST   DIFFERENCE!       MEM START    DIFFERENCE         MEM NOW      LOOPS        LOOP AVG      LOOPS       TOTAL AVG      CALL        CALL AVG       CALL       TOTAL AVG\n");
        if (skip==1) {
            fclose(file);
        }
    }
    if (skip==0) fprintf(file,"%7.3f %7.3f %7.0f ",tied,tied_total,tied_total_total);
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_first));
    if (skip==0) fprintf(file,"%13s ",pretty_number(mem_tot_dif2));
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_start));
    if (skip==0) fprintf(file,"%13s ",pretty_number(mem_tot_dif1));
    if (skip==0) fprintf(file,"%15s ",pretty_number(mem_now));
    if (skip==0) if (count_loops>1) {
        fprintf(file,  "%10d %15s ", count_loops-1, pretty_number(mem_tot_dif1/(long long int)(count_loops-1) ) );
        if (total_count!=0) fprintf(file,  "%10d %15s", total_count, pretty_number(mem_tot_dif2/(long long int)total_count) );
        else fprintf(file,  "                          ");
    } else if (skip==0) fprintf(file,  "                                                     ");
    if (skip==0) if (call>0) {
        fprintf(file,  "%10d %15s ", call, pretty_number( mem_tot_dif1/(long long int)(call) ) );
        if (total_call!=0) fprintf(file,  "%10d %15s", total_call, pretty_number(mem_tot_dif2/(long long int)total_call) );
        else fprintf(file,  "                          ");
    } else if (skip==0) fprintf(file,  "                                                     ");
    if (skip==0) fprintf(file," %s\n",name);

    if (skip==0) fclose(file);

    return memory;
}


bool file_exists(const char * filename)
{
    struct stat stat_buffer;
    int exist = stat(filename,&stat_buffer);
    if (exist==0)
    {
        return true;
    }
//    strcpy(error_msg,"FILE NOT FOUND: ");
//    strcat(error_msg,filename);
//    error_flag=1;
    return false;
}
