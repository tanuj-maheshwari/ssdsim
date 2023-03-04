/*****************************************************************************************************************************
  This project was supported by the National Basic Research 973 Program of China under Grant No.2011CB302301
  Huazhong University of Science and Technology (HUST)   Wuhan National Laboratory for Optoelectronics

  FileName： initialize.h
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
#ifndef INITIALIZE_H
#define INITIALIZE_H 10000

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include "avlTree.h"

#define SECTOR 512
#define BUFSIZE 200

#define DYNAMIC_ALLOCATION 0
#define STATIC_ALLOCATION 1

#define INTERLEAVE 0
#define TWO_PLANE 1

#define NORMAL 2
#define INTERLEAVE_TWO_PLANE 3
#define COPY_BACK 4

#define AD_RANDOM 1
#define AD_COPYBACK 2
#define AD_TWOPLANE 4
#define AD_INTERLEAVE 8
#define AD_TWOPLANE_READ 16

#define READ 1
#define WRITE 0
#define ERASE 2

/*********************************all states of each objects************************************************
 *一下定义了channel的空闲，命令地址传输，数据传输，传输，其他等状态
 *还有chip的空闲，写忙，读忙，命令地址传输，数据传输，擦除忙，copyback忙，其他等状态
 *还有读写子请求（sub）的等待，读命令地址传输，读，读数据传输，写命令地址传输，写数据传输，写传输，完成等状态

 * Define the channel's idle, command address transmission, data transmission, transmission, other states
 * There are also chip idle, write busy, read busy, command address transmission, data transmission, erase busy, copyback busy, other states, etc.
 *There are also read and write sub-request (sub) waiting, read command address transmission, read, read data transmission, write command address transmission, write data transmission, write transmission, completion and other states
 ************************************************************************************************************/

#define CHANNEL_IDLE 000
#define CHANNEL_C_A_TRANSFER 3
#define CHANNEL_GC 4
#define CHANNEL_DATA_TRANSFER 7
#define CHANNEL_TRANSFER 8
#define CHANNEL_UNKNOWN 9

#define CHIP_IDLE 100
#define CHIP_WRITE_BUSY 101
#define CHIP_READ_BUSY 102
#define CHIP_C_A_TRANSFER 103
#define CHIP_DATA_TRANSFER 107
#define CHIP_WAIT 108
#define CHIP_ERASE_BUSY 109
#define CHIP_COPYBACK_BUSY 110
#define CHIP_PAGEMOVE_BUSY 111
#define CHIP_ERASEOP_WAITING 112
#define UNKNOWN 111

#define SR_WAIT 200
#define SR_R_C_A_TRANSFER 201
#define SR_R_READ 202
#define SR_R_DATA_TRANSFER 203
#define SR_W_C_A_TRANSFER 204
#define SR_W_DATA_TRANSFER 205
#define SR_W_TRANSFER 206
#define SR_E_HC_PM_COMPUTE 207 // Heuristic computation & Page movement
#define SR_E_ERASE 208         // Actual erase operation performing (key remove or block erase)
#define SR_E_DISC 209          // Discarded delete requests
#define SR_COMPLETE 299

#define ERASE_TYPE_KEY 0   // Key is being deleted for erase operation
#define ERASE_TYPE_BLOCK 1 // Block is being erased for erase operation

#define ERASE_GREEDY 0 // Greedy erase

#define REQUEST_IN 300 // 下一条请求到达的时间
#define OUTPUT 301     // 下一次数据输出的时间

#define GC_WAIT 400
#define GC_ERASE_C_A 401
#define GC_COPY_BACK 402
#define GC_COMPLETE 403
#define GC_INTERRUPT 0
#define GC_UNINTERRUPT 1

#define CHANNEL(lsn) (lsn & 0x0000) >> 16
#define chip(lsn) (lsn & 0x0000) >> 16
#define die(lsn) (lsn & 0x0000) >> 16
#define PLANE(lsn) (lsn & 0x0000) >> 16
#define BLOKC(lsn) (lsn & 0x0000) >> 16
#define PAGE(lsn) (lsn & 0x0000) >> 16
#define SUBPAGE(lsn) (lsn & 0x0000) >> 16

#define PG_SUB 0xffffffff

#define GCSSYNC_BUFFER_TIME 0 // 62800000

/*****************************************
 *函数结果状态代码
 *Status 是函数类型，其值是函数结果状态代码
 ******************************************/
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define ERROR -1
#define INFEASIBLE -2
#define OVERFLOW -3
typedef int Status;

struct user_args
{
    char parameter_filename[80];
    char trace_filename[80];
    char simulation_timestamp[16];
    int is_raid;
    int raid_type;
    int num_disk;

    int is_gcsync;
    int is_gclock;
    int is_gcdefer;
    int diskid;
    int64_t gc_time_window;
};

struct ac_time_characteristics
{
    int tPROG; // program time
    int tDBSY; // bummy busy time for two-plane program
    int tBERS; // block erase time
    int tCLS;  // CLE setup time
    int tCLH;  // CLE hold time
    int tCS;   // CE setup time
    int tCH;   // CE hold time
    int tWP;   // WE pulse width
    int tALS;  // ALE setup time
    int tALH;  // ALE hold time
    int tDS;   // data setup time
    int tDH;   // data hold time
    int tWC;   // write cycle time
    int tWH;   // WE high hold time
    int tADL;  // address to data loading time
    int tR;    // data transfer from cell to register
    int tAR;   // ALE to RE delay
    int tCLR;  // CLE to RE delay
    int tRR;   // ready to RE low
    int tRP;   // RE pulse width
    int tWB;   // WE high to busy
    int tRC;   // read cycle time
    int tREA;  // RE access time
    int tCEA;  // CE access time
    int tRHZ;  // RE high to output hi-z
    int tCHZ;  // CE high to output hi-z
    int tRHOH; // RE high to output hold
    int tRLOH; // RE low to output hold
    int tCOH;  // CE high to output hold
    int tREH;  // RE high to output time
    int tIR;   // output hi-z to RE low
    int tRHW;  // RE high to WE low
    int tWHR;  // WE high to RE low
    int tRST;  // device resetting time
    int tKG;   // key generation time
    int tHC;   // Heuristic computation time
    int tPM;   // Page movement time
} ac_timing;

struct ssd_info
{
    int is_gcsync;
    int is_gclock;
    int is_gcdefer;
    int ndisk;
    int diskid;
    int64_t gc_time_window;
    struct gclock_raid_info *gclock_pointer;

    int64_t simulation_start_time;
    int64_t simulation_end_time;
    int64_t pre_process_time; // Time for pre-processing read requests

    double ssd_energy;    // SSD的能耗，是时间和芯片数的函数,能耗因子
    int64_t current_time; // 记录系统时间
    int64_t next_request_time;
    unsigned int real_time_subreq; // 记录实时的写请求个数，用在全动态分配时，channel优先的情况
    int flag;
    int active_flag; // 记录主动写是否阻塞，如果发现柱塞，需要将时间向前推进,0表示没有阻塞，1表示被阻塞，需要向前推进时间
    unsigned int page;

    unsigned int token;      // In dynamic allocation, in order to prevent each Channel from being assigned to maintain a token, start allocation from the position referred to by the token at each time
    unsigned int gc_request; // 记录在SSD中，当前时刻有多少gc操作的请求

    unsigned int write_request_count; // 记录写操作的次数
    unsigned int read_request_count;  // 记录读操作的次数
    unsigned int erase_request_count; // 记录擦除操作的次数
    int64_t write_avg;                // 记录用于计算写请求平均响应时间的时间
    int64_t read_avg;                 // 记录用于计算读请求平均响应时间的时间
    int64_t erase_avg;                // 记录用于计算擦除请求平均响应时间的时间

    unsigned int write_request_size; // total write size in bytes
    unsigned int read_request_size;  // total read size in bytes
    unsigned int erase_request_size; // total erase size in bytes
    unsigned int in_program_size;    // total internal write (program) size in bytes
    unsigned int in_read_size;       // total internal read size in bytes
    unsigned int write_subreq_count;
    unsigned int read_subreq_count;
    unsigned int erase_subreq_count;
    unsigned int gc_move_page;

    unsigned int min_lsn;
    unsigned int max_lsn;
    unsigned long read_count;
    unsigned long program_count;
    unsigned long key_prog_count; // Number of times key pages are programmed
    unsigned long erase_count;
    unsigned long direct_erase_count;
    unsigned long copy_back_count;
    unsigned long m_plane_read_count;
    unsigned long m_plane_prog_count;
    unsigned long interleave_count;
    unsigned long interleave_read_count;
    unsigned long inter_mplane_count;
    unsigned long inter_mplane_prog_count;
    unsigned long interleave_erase_count;
    unsigned long mplane_erase_conut;
    unsigned long interleave_mplane_erase_count;
    unsigned long gc_copy_back;
    unsigned long num_gc;
    unsigned long write_flash_count; // 实际产生的对flash的写操作 | The actual write to flash
    unsigned long waste_page_count;  // 记录因为高级命令的限制导致的页浪费 | Recording page waste due to limitations of advanced commands
    float ave_read_size;
    float ave_write_size;
    float ave_erase_size;
    unsigned int request_queue_length;
    unsigned int update_read_count; // 记录因为更新操作导致的额外读出操作 | Record additional read operations due to update operations

    char parameterfilename[80];
    char tracefilename[80];
    char outputfilename[80];
    char statisticfilename[80];
    char statisticfilename2[80];
    char outfile_gc_name[80];
    char outfile_io_name[80];
    char outfile_io_write_name[80];
    char outfile_io_read_name[80];

    FILE *outputfile;
    FILE *tracefile;
    FILE *statisticfile;
    FILE *statisticfile2;
    FILE *outfile_gc;
    FILE *outfile_io;
    FILE *outfile_io_write;
    FILE *outfile_io_read;

    struct parameter_value *parameter; // SSD参数因子
    struct dram_info *dram;
    struct request *request_queue;   // dynamic request queue
    struct request *request_tail;    // the tail of the request queue
    struct sub_request *subs_w_head; // 当采用全动态分配时，分配是不知道应该挂载哪个channel上，所以先挂在ssd上，等进入process函数时才挂到相应的channel的读请求队列上 | When using full dynamic allocation, the allocation does not know which channel should be mounted, so first hang on the ssd, and then hang on the read request queue of the corresponding channel when entering the process function
    struct sub_request *subs_w_tail;
    struct sub_request *subs_e_c_head; // Erase subrequests which are already completed (because of invalidity of page) are hanged on this queue
    struct sub_request *subs_e_c_tail;
    struct event_node *event;          // 事件队列，每产生一个新的事件，按照时间顺序加到这个队列，在simulate函数最后，根据这个队列队首的时间，确定时间 | Event queue, each time a new event is generated, it is added to this queue in chronological order, and at the end of the simulate function, the time is determined according to the time at the head of this queue
    struct channel_info *channel_head; // 指向channel结构体数组的首地址
};

struct channel_info
{
    int chip; // It means how many particles are on this bus
    unsigned long read_count;
    unsigned long program_count;
    unsigned long erase_count;
    unsigned int token; // In dynamic allocation, in order to prevent each other from being assigned to maintain a token, start allocation from the position referred to by the token at each time

    int current_state; // channel has serveral states, including idle, command/address transfer,data transfer,unknown
    int next_state;
    int64_t current_time;            // record the current time of the channel
    int64_t next_state_predict_time; // the predict time of next state, used to decide the sate at the moment

    struct event_node *event;
    struct sub_request *subs_r_head; // The reading request queue head on Channel first serves the child request in the queue head
    struct sub_request *subs_r_tail; // At the end of the reading request queue on Channel, the newly -entered sub -request is added to the end of the team
    struct sub_request *subs_w_head; // The write request queue head on the channel, the sub-request at the queue head is served first
    struct sub_request *subs_w_tail; // The write request queue on the channel, the newly added sub-request is added to the end of the queue
    struct sub_request *subs_e_head; // The erase request queue head on the channel, the sub-request at the queue head is served first
    struct sub_request *subs_e_tail; // The erase request queue on the channel, the newly added sub-request is added to the end of the queue
    struct gc_operation *gc_command; // Record where gc needs to be generated
    struct chip_info *chip_head;
};

struct chip_info
{
    unsigned int die_num;          // Indicates how many die are in a particle
    unsigned int plane_num_die;    // indicate how many planes in a die
    unsigned int block_num_plane;  // indicate how many blocks in a plane
    unsigned int page_num_block;   // indicate how many pages in a block
    unsigned int subpage_num_page; // indicate how many subpage in a page
    unsigned int ers_limit;        // The number of times each block in the chip can be erased
    unsigned int token;            // In dynamic allocation, in order to prevent the need to maintain a token in the first die for each allocation, each allocation starts from the position pointed by the token

    int current_state; // channel has serveral states, including idle, command/address transfer,data transfer,unknown
    int next_state;
    int64_t current_time;            // record the current time of the channel
    int64_t next_state_predict_time; // the predict time of next state, used to decide the sate at the moment

    unsigned long read_count; // how many read count in the process of workload
    unsigned long program_count;
    unsigned long erase_count;

    struct ac_time_characteristics ac_timing;
    struct die_info *die_head;
};

struct die_info
{

    unsigned int token; // In dynamic allocation, in order to prevent the need to maintain a token in the first plane for each allocation, the allocation starts from the position pointed to by the token each time
    struct plane_info *plane_head;
};

struct plane_info
{
    int add_reg_ppn;                 // When reading and writing, the address is transferred to this variable, which represents the address register. When die changes from busy to idle, clear the address //It is possible that because of one-to-many mapping, there are multiple identical lpn in a read request, so ppn is needed to distinguish
    unsigned int free_page;          // How many free pages are in the plane
    unsigned int ers_invalid;        // Record the number of blocks erased and invalidated in this plane
    unsigned int active_block;       // if a die has a active block, this item represents its physical block number
    int can_erase_block;             // Record the block that is ready to be erased in the gc operation in a plane, and -1 means that no suitable block has been found
    struct direct_erase *erase_node; // It is used to record the block number that can be deleted directly. When obtaining a new ppn, whenever invalid_page_num==64 appears, add it to this pointer and delete it directly for GC operation
    struct blk_info *blk_head;
};

struct blk_info
{
    unsigned int is_key_block;     // Indicates whether it is a key block
    unsigned int erase_count;      // The number of erasures of the block, this item is recorded in ram and used for GC
    unsigned int free_page_num;    // Record the number of free pages in the block, same as above
    unsigned int invalid_page_num; // Record the number of invalid pages in the block, same as above
    int last_write_page;           // Record the number of pages performed by the last write operation, -1 means that no page has been written in the block
    struct page_info *page_head;   // Record the status of each subpage
};

struct page_info
{
    int valid_state;            // indicate the page is valid or invalid
    int free_state;             // each bit indicates the subpage is free or occupted. 1 indicates that the bit is free and 0 indicates that the bit is used
    unsigned int lpn;           // lpn records the logical page stored in the physical page. When the logical page is valid, valid_state is greater than 0, and free_state is greater than 0;
    unsigned int written_count; // Record the number of times the page was written
};

struct dram_info
{
    unsigned int dram_capacity;
    int64_t current_time;

    struct dram_parameter *dram_paramters;
    struct map_info *map;
    struct buffer_info *buffer;
};

/*********************************************************************************************
 *buffer中的已写回的页的管理方法:在buffer_info中维持一个队列:written。这个队列有队首，队尾。
 *每次buffer management中，请求命中时，这个group要移到LRU的队首，同时看这个group中是否有已
 *写回的lsn，有的话，需要将这个group同时移动到written队列的队尾。这个队列的增长和减少的方法
 *如下:当需要通过删除已写回的lsn为新的写请求腾出空间时，在written队首中找出可以删除的lsn。
 *当需要增加新的写回lsn时，找到可以写回的页，将这个group加到指针written_insert所指队列written
 *节点前。我们需要再维持一个指针，在buffer的LRU队列中指向最老的一个写回了的页，下次要再写回时，
 *只需由这个指针回退到前一个group写回即可。
 **********************************************************************************************/
typedef struct buffer_group
{
    TREE_NODE node;                     // 树节点的结构一定要放在用户自定义结构的最前面，注意!
    struct buffer_group *LRU_link_next; // next node in LRU list
    struct buffer_group *LRU_link_pre;  // previous node in LRU list

    unsigned int group;       // the first data logic sector number of a group stored in buffer
    unsigned int stored;      // indicate the sector is stored in buffer or not. 1 indicates the sector is stored and 0 indicate the sector isn't stored.EX.  00110011 indicates the first, second, fifth, sixth sector is stored in buffer.
    unsigned int dirty_clean; // it is flag of the data has been modified, one bit indicates one subpage. EX. 0001 indicates the first subpage is dirty
    int flag;                 // indicates if this node is the last 20% of the LRU list
} buf_node;

struct dram_parameter
{
    float active_current;
    float sleep_current;
    float voltage;
    int clock_time;
};

struct map_info
{
    struct entry *map_entry;         // 该项是映射表结构体指针,each entry indicate a mapping information
    struct buffer_info *attach_info; // info about attach map
};

struct controller_info
{
    unsigned int frequency; // 表示该控制器的工作频率
    int64_t clock_time;     // 表示一个时钟周期的时间
    float power;            // 表示控制器单位时间的能耗
};

struct request
{
    int64_t time;           // The time when the request arrives, the unit is us. This is different from the usual habit. Usually, the unit is ms. There needs to be a unit conversion process here.
    unsigned int lsn;       // Request starting address, logical address
    unsigned int size;      // The size of the request, i.e. how many sectors
    unsigned int operation; // Type of request, 1 for read, 0 for write

    unsigned int *need_distr_flag;
    unsigned int complete_lsn_count; // record the count of lsn served by buffer

    int distri_flag;  // indicate whether this request has been distributed already
    int meet_gc_flag; // indicate whether this request is blocked by GC process
    int64_t meet_gc_remaining_time;

    int64_t begin_time;
    int64_t response_time;
    double energy_consumption; // Record the energy consumption of the request, in uJ

    struct sub_request *subs;  // Link to all subrequests belonging to this request
    struct request *next_node; // point to the next request structure

    struct raid_sub_request *subreq_on_raid;
};

struct sub_request
{
    unsigned int lpn;       // This represents the logical page number of the subrequest
    unsigned int ppn;       // Allocate that physical subpage to this subrequest. In multi_chip_page_mapping, the value of psn may be known when a subpage request is generated. In other cases, the value of psn is generated by the bottommost FTL functions such as page_map_read and page_map_write.
    unsigned int operation; // Indicates the type of the sub-request. In addition to reading 1 and writing 0, there are also operations such as erase, two plane, etc.
    int size;

    unsigned int current_state; // Indicates the state of the sub request, see macro definition sub request
    int64_t current_time;
    unsigned int next_state;
    int64_t next_state_predict_time;
    unsigned int state; // Use the highest bit of the state to indicate whether the sub-request is one of the one-to-many mapping relationships, and if so, it needs to be read into the buffer. 1 means one-to-many, 0 means do not write to the buffer
    // Read requests do not need this member, and lsn plus size can identify the status of the page; but write requests require this member, most of the write sub-requests come from the buffer write-back operation, and there may be situations similar to the discontinuity of sub-pages, so it is necessary to maintain the member alone

    unsigned int key_generated_flag; // Indicates whether a key was generated for this subrequest. Only write requests need to generate keys, and read requests do not need to generate keys.

    unsigned int num_pages_move; // The number of pages that need to be moved when an erase subrequest is processed.
    unsigned int erase_type;     // Weather key is deleted or block is erased.

    int64_t begin_time;    // Subrequest start time
    int64_t complete_time; // Record the processing time of the sub-request, that is, the time when the data is actually written or read

    struct local *location;        // In the static allocation and mixed allocation methods, the known lpn knows which channel, chip, die, and plane the lpn should be allocated to. This structure is used to store the calculated address.
    struct sub_request *next_subs; // points to subrequests belonging to the same request
    struct sub_request *next_node; // Points to the next subrequest structure in the same channel
    struct sub_request *update;    // Because there is an update operation in the write operation, because the copyback operation cannot be used in the dynamic allocation mode, the original page needs to be read out before the write operation can be performed, so the read operation caused by the update is hung on this pointer.
};

/***********************************************************************
 *事件节点控制时间的增长，每次时间的增加是根据时间最近的一个事件来确定的
 ************************************************************************/
struct event_node
{
    int type;             // Record the type of the event, 1 indicates the command type, 2 indicates the data transmission type
    int64_t predict_time; // Record the estimated time of the start of this time to prevent the execution of this time in advance
    struct event_node *next_node;
    struct event_node *pre_node;
};

struct parameter_value
{
    unsigned int chip_num;      // How many particles are in a SSD
    unsigned int dram_capacity; // 记录SSD中DRAM capacity
    unsigned int cpu_sdram;     // How much is there in the documentary

    unsigned int channel_number;    // How many channels are there in SSD, each channel is separate bus
    unsigned int chip_channel[100]; // Set the number of Channel in SSD and the number of particles on each chanel

    unsigned int die_chip;
    unsigned int plane_die;
    unsigned int block_plane;
    unsigned int page_block;
    unsigned int subpage_page;

    unsigned int block_chunk; // How many blocks are there in a chunk. Note that this is not used for addressing purposes. Addressing is done using the plane_block model only.

    unsigned int page_capacity;
    unsigned int subpage_capacity;

    unsigned int ers_limit;  // 记录每个块可擦除的次数
    int address_mapping;     // 记录映射的类型，1：page；2：block；3：fast
    int wear_leveling;       // WL算法
    int gc;                  // 记录gc策略
    int clean_in_background; // 清除操作是否在前台完成
    int alloc_pool;          // allocation pool 大小(plane，die，chip，channel),也就是拥有active_block的单位
    float overprovide;
    float gc_threshold; // 当达到这个阈值时，开始GC操作，在主动写策略中，开始GC操作后可以临时中断GC操作，服务新到的请求；在普通策略中，GC不可中断

    double operating_current; // NAND FLASH的工作电流单位是uA
    double supply_voltage;
    double dram_active_current;  // cpu sdram work current   uA
    double dram_standby_current; // cpu sdram work current   uA
    double dram_refresh_current; // cpu sdram work current   uA
    double dram_voltage;         // cpu sdram work voltage  V

    int buffer_management;    // indicates that there are buffer management or not
    int scheduling_algorithm; // 记录使用哪种调度算法，1:FCFS
    float quick_radio;
    int related_mapping;

    unsigned int time_step;
    unsigned int small_large_write; // the threshould of large write, large write do not occupt buffer, which is written back to flash directly

    int striping; // 表示是否使用了striping方式，0表示没有，1表示有
    int interleaving;
    int pipelining;
    int threshold_fixed_adjust;
    int threshold_value;
    int active_write;        // Indicates whether to perform active write operation 1, yes; 0, no
    float gc_hard_threshold; // This parameter is not used in ordinary strategies, only in active write strategies, when this threshold is met, GC operations cannot be interrupted
    int allocation_scheme;   // The choice of record distribution method, 0 indicates dynamic allocation, 1 indicates static allocation
    int static_allocation;   // The record is that kind of static allocation, as all static allocations described in the ICS09 article
    int dynamic_allocation;  // How to record dynamic allocation
    int advanced_commands;
    int ad_priority;  // record the priority between two plane operation and interleave operation
    int ad_priority2; // record the priority of channel-level, 0 indicates that the priority order of channel-level is highest; 1 indicates the contrary
    int greed_CB_ad;  // 0 don't use copyback advanced commands greedily; 1 use copyback advanced commands greedily
    int greed_MPW_ad; // 0 don't use multi-plane write advanced commands greedily; 1 use multi-plane write advanced commands greedily
    int aged;         // 1 means that you need to turn this SSD into aged, 0 means that you need to keep this SSD NON-AGED
    float aged_ratio;
    int queue_length;  // 请求队列的长度限制
    int ers_heuristic; // Erase heuristic type to be used, 0 means GREEDY

    struct ac_time_characteristics time_characteristics;
};

/********************************************************
 *mapping information,state的最高位表示是否有附加映射关系
 *********************************************************/
struct entry
{
    unsigned int pn; // Physical number, which can represent either the physical page number, the physical sub-page number, or the physical block number
    int state;       // The hexadecimal expressed is 0000-FFFF, and each bit means whether the corresponding subpage is valid (page mapping).For example, on this page, the 0, No. 1 page is valid, 2,3 is invalid. This should be 0x0003.
};

struct local
{
    unsigned int channel;
    unsigned int chip;
    unsigned int die;
    unsigned int plane;
    unsigned int block;
    unsigned int page;
    unsigned int sub_page;
};

struct gc_info
{
    int64_t begin_time; // 记录一个plane什么时候开始gc操作的
    int copy_back_count;
    int erase_count;
    int64_t process_time;      // 该plane花了多少时间在gc操作上
    double energy_consumption; // 该plane花了多少能量在gc操作上
};

struct direct_erase
{
    unsigned int block;
    struct direct_erase *next_node;
};

/**************************************************************************************
 *当产生一个GC操作时，将这个结构挂在相应的channel上，等待channel空闲时，发出GC操作命令
 *When a GC operation is generated, the structure is hung on the corresponding channel, and when the channel is idle, the GC operation command is issued.
 ***************************************************************************************/
struct gc_operation
{
    unsigned int chip;
    unsigned int die;
    unsigned int plane;
    unsigned int block;    // 该参数只在可中断的gc函数中使用（gc_interrupt），用来记录已近找出来的目标块号 | This parameter is only used in the interruptible gc function (gc_interrupt) to record the target block number that has been found nearby.
    unsigned int page;     // 该参数只在可中断的gc函数中使用（gc_interrupt），用来记录已经完成的数据迁移的页号 | This parameter is only used in the interruptible gc function (gc_interrupt), which is used to record the page number of the completed data migration.
    unsigned int state;    // 记录当前gc请求的状态 | Record the status of the current gc request
    unsigned int priority; // 记录该gc操作的优先级，1表示不可中断，0表示可中断（软阈值产生的gc请求） | Record the priority of the gc operation, 1 means uninterruptible, 0 means interruptable (gc request generated by soft threshold)
    struct gc_operation *next_node;

    int64_t x_init_time;           // time when gc initialized, when the threshold is reached.
    int64_t x_expected_start_time; // (for time window mechanism) expected start time, beggining of current or next time window
    int64_t x_start_time;          // time when gc is started
    int64_t x_end_time;            // time when gc is done
    double x_free_percentage;      // free page percentage in the plane when gc is initialized.
    unsigned int x_moved_pages;    // the number of page moved during the gc process
};

/*
 *add by ninja
 *used for map_pre function
 */
typedef struct Dram_write_map
{
    unsigned int state;
} Dram_write_map;

struct ssd_info *initiation(struct ssd_info *);
struct parameter_value *load_parameters(char parameter_file[30]);
struct page_info *initialize_page(struct page_info *p_page);
struct blk_info *initialize_block(struct blk_info *p_block, struct parameter_value *parameter);
struct plane_info *initialize_plane(struct plane_info *p_plane, struct parameter_value *parameter);
struct die_info *initialize_die(struct die_info *p_die, struct parameter_value *parameter, long long current_time);
struct chip_info *initialize_chip(struct chip_info *p_chip, struct parameter_value *parameter, long long current_time);
struct ssd_info *initialize_channels(struct ssd_info *ssd);
struct dram_info *initialize_dram(struct ssd_info *ssd);

#endif
