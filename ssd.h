/*****************************************************************************************************************************
  This project was supported by the National Basic Research 973 Program of China under Grant No.2011CB302301
  Huazhong University of Science and Technology (HUST)   Wuhan National Laboratory for Optoelectronics

FileName: ssd.h
Author: Hu Yang		Version: 2.1	Date:2011/12/02
Description:

History:
<contributor>     <time>        <version>       <desc>                   <e-mail>
Yang Hu	        2009/09/25	      1.0		    Creat SSDsim       yanghu@foxmail.com
2010/05/01        2.x           Change
Zhiming Zhu     2011/07/01        2.0           Change               812839842@qq.com
Shuangwu Zhang  2011/11/01        2.1           Change               820876427@qq.com
Chao Ren        2011/07/01        2.0           Change               529517386@qq.com
Hao Luo         2011/01/01        2.0           Change               luohao135680@gmail.com
 *****************************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "initialize.h"
#include "flash.h"
#include "pagemap.h"

#define MAX_INT64 0x7fffffffffffffffll

void simulate_ssd(struct user_args *);
struct ssd_info *simulate(struct ssd_info *);
int get_requests(struct ssd_info *);
struct ssd_info *buffer_management(struct ssd_info *);
unsigned int lpn2ppn(struct ssd_info *, unsigned int lsn);
struct ssd_info *distribute(struct ssd_info *);
void trace_output(struct ssd_info *);
void statistic_output(struct ssd_info *);
unsigned int size(unsigned int);
unsigned int transfer_size(struct ssd_info *, int, unsigned int, struct request *);
int64_t find_nearest_event(struct ssd_info *);
void free_all_node(struct ssd_info *);
struct ssd_info *make_aged(struct ssd_info *);
struct ssd_info *no_buffer_distribute(struct ssd_info *);
struct ssd_info *warmup(struct ssd_info *);
struct ssd_info *init_gc(struct ssd_info *);
void print_gc_node(struct ssd_info *ssd);

int parse_user_args(int, char *[], struct user_args *);
struct ssd_info *initialize_ssd(struct ssd_info *, struct user_args *);
struct ssd_info *parse_args(struct ssd_info *, int, char *[]);
void close_file(struct ssd_info *);

void get_current_time(char *current_time);
float get_crt_free_page_prct(struct ssd_info *);
float get_crt_free_block_prct(struct ssd_info *);
float get_crt_nonempty_free_page_prct(struct ssd_info *);
float get_crt_nonempty_free_block_prct(struct ssd_info *);

/********************************************
 * Function to display info and help
 * Added by Fadhil Imam (fadhilimamk@gmail.com)
 * to print help and usage info | 29/06/2018
 *********************************************/
void display_title();
void display_help();
void display_simulation_intro(struct ssd_info *);
void display_freepage(struct ssd_info *);
void display_state(struct ssd_info *);