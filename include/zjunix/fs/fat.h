#ifndef _ZJUNIX_FS_FAT_H
#define _ZJUNIX_FS_FAT_H

#include <zjunix/type.h>
#include <zjunix/fs/fscache.h>

/* 4k data buffer number in each file struct */
#define LOCAL_DATA_BUF_NUM 4

#define SECTOR_SIZE 512
#define CLUSTER_SIZE 4096

struct __attribute__((__packed__)) dir_entry_attr {
    u8 name[8];                   /* Name */
    u8 ext[3];                    /* Extension */
    u8 attr;                      /* attribute bits */
    u8 lcase;                     /* Case for base and extension */
    u8 ctime_cs;                  /* Creation time, centiseconds (0-199) */
    u16 ctime;                    /* Creation time */
    u16 cdate;                    /* Creation date */
    u16 adate;                    /* Last access date */
    u16 starthi;                  /* Start cluster (Hight 16 bits) */
    u16 time;                     /* Last modify time */
    u16 date;                     /* Last modify date */
    u16 startlow;                 /* Start cluster (Low 16 bits) */
    u32 size;                     /* file size (in bytes) */
};

union dir_entry {
    u8 data[32];
    struct dir_entry_attr attr;
};

/* for file struct, we do not use clock_head */
struct fat_file {
    u8 path[256];
    /* Current file pointer */
    u32 loc;
    /* Current directory entry position */
    u32 dir_entry_pos;
    
    u32 dir_entry_sector;
    /* current directory entry */
    union dir_entry entry;

};

struct fs_fat_dir {
    u32 cur_sector;
    u32 loc;
    u32 sec;
};

/* the first 79 bits from 0x000B is BPB */
struct __attribute__((__packed__)) BPB_attr {
    // 0x00 ~ 0x0f
    u8  jumpforBS[3];
    u8  oem_name_spa[8];
    u16 ser_per_size;	/* sector_size */
    u8  sec_per_clu;
    u16 res_for_sectors;
    // 0x10 ~ 0x1f
    u8  fat_num;
    u16 root_enter_entries;
    u16 tiny_sec_num;
    u8  my_media_des;
    u16 sectors_per_fat;
    u16 sectors_per_track;
    u16 heads_num;
    u32 hid_sec_num;
    // 0x20 ~ 0x2f
    u32 sec_num;
    u32 sectors_fat_num;
    u16 flags;
    u16 version;
    u32 root_dir_num;
    // 0x30 ~ 0x3f
    u16 fs_info_sec_num;
    u16 bkup_boot_sec_num;
    u8  res_data[12];
    // 0x40 ~ 0x51
    u8  drv_num;
    u8  res_for_BS;
    u8  boot_sig;
    u32 num_for_ser;
    u8  name_of_volab[11];
    // 0x52 ~ 0x1fe
    u8  fat_name[8];
    u8  code_exe[420];
    u8  sign_rec[2];
};

union BPB_info {
    u8 data[512];
    struct BPB_attr attr;
};

struct fs_info {
    u32 base_addr;
    u32 sectors_per_fat;
    u32 total_sectors;
    u32 total_data_clusters;
    u32 total_data_sectors;
    u32 first_data_sector;
    union BPB_info BPB;
    u8 fat_fs_info[SECTOR_SIZE];
};

typedef struct fat_file sfile;

typedef struct fs_fat_dir F_D_FS;

u32 fs_read(sfile *file, unsigned char *buf, u32 count);

u32 fs_write(sfile *file, const unsigned char *buf, u32 count);

u32 fs_find(sfile *file);

u32 init_fs();

u32 fs_open(sfile *file, unsigned char *filename);

u32 fs_close(sfile *file);

u32 fs_cat(unsigned char * path);

void get_filename(unsigned char *entry, unsigned char *buf);

u32 read_block(u8 *buf, u32 addr, u32 count);

u32 write_block(u8 *buf, u32 addr, u32 count);

u32 fs_create(unsigned char *filename);

u32 fs_mkdir(unsigned char *filename);

u32 fs_rm(unsigned char *filename);

u32 fs_mv(unsigned char *src, unsigned char *dest);

u32 fs_open_dir(F_D_FS *dir, unsigned char *filename);

u32 fs_read_dir(F_D_FS *dir, unsigned char *buf);

u32 fs_fflush();

void fs_lseek(sfile *file, u32 new_loc);

u32 get_entry_filesize(u8 *entry);

u32 get_entry_attr(u8 *entry);

#endif  // !_ZJUNIX_FS_FAT_H
