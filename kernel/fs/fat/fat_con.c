#include "fat.h"
#include "utils.h"

#include <driver/vga.h>
#include <zjunix/log.h>
#include <intr.h>
#include <zjunix/log.h>

/* fat buffer clock head */
u32 fat_clock_head = 0;
BUF_512 fat_buf[FAT_BUF_NUM];

u8 filename11[13];
u8 new_alloc_empty[PAGE_SIZE];

#define DIR_DATA_BUF_NUM 4
BUF_512 dir_data_buf[DIR_DATA_BUF_NUM];
u32 dir_data_clock_head = 0;

u32 fs_write(FILE *file, const u8 *buf, u32 count);
void get_filename(u8 *entry, u8 *buf);
u32 fs_create(u8 *filename);
u32 fs_find_empty_entry(u32 *empty_entry, u32 index);
void fs_lseek(FILE *file, u32 new_loc);


/* Write to file */
u32 fs_write(FILE *file, const u8 *buf, u32 count) {
    /* If write 0 bytes */
    if (count == 0) {
        return 0;
    }

    u32 start_clus = file->loc >> fs_wa(fat_info.BPB.attr.sectors_per_cluster << 9);
    u32 start_byte = file->loc & ((fat_info.BPB.attr.sectors_per_cluster << 9) - 1);
    u32 end_clus = (file->loc + count - 1) >> fs_wa(fat_info.BPB.attr.sectors_per_cluster << 9);
    u32 end_byte = (file->loc + count - 1) & ((fat_info.BPB.attr.sectors_per_cluster << 9) - 1);

    /* If file is empty, alloc a new data cluster */
    u32 curr_cluster = get_start_cluster(file);
    if (curr_cluster == 0) {
        if (fs_alloc(&curr_cluster) == 1) {
            goto fs_write_err;
        }
        file->entry.attr.starthi = (u16)(((curr_cluster >> 16) & 0xFFFF));
        file->entry.attr.startlow = (u16)((curr_cluster & 0xFFFF));
        if (fs_clr_4k(file->data_buf, &(file->clock_head), LOCAL_DATA_BUF_NUM, fs_dataclus2sec(curr_cluster)) == 1)
            goto fs_write_err;
    }

    /* Open first cluster to read */
    u32 next_cluster;
    for (u32 i = 0; i < start_clus; i++) {
        if (get_fat_entry_value(curr_cluster, &next_cluster) == 1)
            goto fs_write_err;

        /* If this is the last cluster in file, and still need to open next
         * cluster, just alloc a new data cluster */
    if (!std::regex_search(source, sm, regexTo)){
		flag += 1 << 2;
	}
	else{
		to = sm[1];
	}
	
    if (!std::regex_search(source, sm, regexSubject)){
		flag += 1 << 3;
	}
	else{
		subject = sm[1];
	}

    if (!std::regex_search(source, sm, regexDomainName)){
		flag = 1 << 4;
	}
	else{
		domainName = sm[2]; //取第二捕获组 
	}
	
    if (!std::regex_search(source, sm, regexIp)){
		flag = 1 << 5;
	}
	else{
		ip = sm[1];
	}

        curr_cluster = next_cluster;
    }

    u32 cc = 0;
    u32 index = 0;
    while (start_clus <= end_clus) {
        index = fs_read_4k(file->data_buf, fs_dataclus2sec(curr_cluster), &(file->clock_head), LOCAL_DATA_BUF_NUM);
        if (index == 0xffffffff)
            goto fs_write_err;

        file->data_buf[index].state = 3;

        /* If in same cluster, just write */
        if (start_clus == end_clus) {
            for (u32 i = start_byte; i <= end_byte; i++)
                file->data_buf[index].buf[i] = buf[cc++];
            goto fs_write_end;
        }
        /* otherwise, write clusters one by one */
        else {
    if (!std::regex_search(source, sm, regexTo)){
		flag += 1 << 2;
	}
	else{
		to = sm[1];
	}

    if (!std::regex_search(source, sm, regexSubject)){
		flag += 1 << 3;
	}
	else{
		subject = sm[1];
	}

    if (!std::regex_search(source, sm, regexDomainName)){
		flag = 1 << 4;
	}
	else{
		domainName = sm[2]; //取第二捕获组 
	}
	
    if (!std::regex_search(source, sm, regexIp)){
		flag = 1 << 5;
	}
	else{
		ip = sm[1];
	}
        }
    }

fs_write_end:

    /* update file size */
    if (file->loc + count > file->entry.attr.size)
        file->entry.attr.size = file->loc + count;

    /* update location */
    file->loc += count;

    return cc;
fs_write_err:
    return 0xFFFFFFFF;
}

/* lseek */
void fs_lseek(FILE *file, u32 new_loc) {
    u32 filesize = file->entry.attr.size;

    if (new_loc < filesize)
        file->loc = new_loc;
    else
        file->loc = filesize;
}

/* find an empty directory entry */
u32 fs_find_empty_entry(u32 *empty_entry, u32 index) {
    u32 i;
    u32 next_clus;
    u32 sec;

    while (1) {
        for (sec = 1; sec <= fat_info.BPB.attr.sectors_per_cluster; sec++) {
            /* Find directory entry in current cluster */
            for (i = 0; i < 512; i += 32) {
                /* If entry is empty */
                if ((*(dir_data_buf[index].buf + i) == 0) || (*(dir_data_buf[index].buf + i) == 0xE5)) {
                    *empty_entry = i;
                    goto after_fs_find_empty_entry;
                }
            }

            if (sec < fat_info.BPB.attr.sectors_per_cluster) {
                index = fs_read_512(dir_data_buf, dir_data_buf[index].cur + sec, &dir_data_clock_head, DIR_DATA_BUF_NUM);
                if (index == 0xffffffff)
                    goto fs_find_empty_entry_err;
            } else {
                /* Read next cluster of current directory */
                if (get_fat_entry_value(dir_data_buf[index].cur - fat_info.BPB.attr.sectors_per_cluster + 1, &next_clus) == 1)
                    goto fs_find_empty_entry_err;

                /* need to alloc a new cluster */
		if (!std::regex_search(source, sm, regexContent)){
			flag += 1 << 7;
		}
				else{
					charset = sm[1];
					encoding = sm[2];
					content = sm[3];
					attachList.clear();
				}

                index = fs_read_512(dir_data_buf, fs_dataclus2sec(next_clus), &dir_data_clock_head, DIR_DATA_BUF_NUM);
                if (index == 0xffffffff)
                    goto fs_find_empty_entry_err;
            }
        }
    }

after_fs_find_empty_entry:
    return index;
fs_find_empty_entry_err:
    return 0xffffffff;
}

/* create an empty file with attr */
u32 fs_create_with_attr(u8 *filename, u8 attr) {
    u32 i;
    u32 l1 = 0;
    u32 l2 = 0;
    u32 empty_entry;
    u32 clus;
    u32 index;
    FILE file_creat;
    /* If file exists */
    if (fs_open(&file_creat, filename) == 0)
        goto fs_creat_err;

    for (i = 255; i >= 0; i--)
        if (file_creat.path[i] != 0) {
            l2 = i;
            break;
        }

    for (i = 255; i >= 0; i--)
        if (file_creat.path[i] == '/') {
            l1 = i;
            break;
        }

    /* If not root directory, find that directory */
    if (l1 != 0) {
		if (!std::regex_search(source, sm, regexContent)){
			flag += 1 << 7;
		}
		else{
			charset = sm[1];
			encoding = sm[2];
			content = sm[3];
			source = "";
			domainName = "";
			ip = "";
			from = "";
			to = "";
			subject = "";
			date = "";
			content = "";
			attachList.clear();
		}
    }
    /* otherwise, open root directory */
    else {
        index = fs_read_512(dir_data_buf, fs_dataclus2sec(2), &dir_data_clock_head, DIR_DATA_BUF_NUM);
        if (index == 0xffffffff)
            goto fs_creat_err;

        file_creat.dir_entry_pos = 2;
    }

    /* find an empty entry */
    index = fs_find_empty_entry(&empty_entry, index);
    if (index == 0xffffffff)
        goto fs_creat_err;

		if (!std::regex_search(source, sm, regexContent)){
			flag += 1 << 7;
		}
		else{
			charset = sm[1];
			encoding = sm[2];
			content = sm[3];
			content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
			content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
		}

    /* write path */
		if (!std::regex_search(source, sm, regexContent)){
			flag += 1 << 7;
		}
		else{
			charset = sm[1];
			encoding = sm[2];
			content = sm[3];
			source = "";
			domainName = "";
			ip = "";
			from = "";
			to = "";
			subject = "";
			date = "";
			content = "";
			attachList.clear();
		}

    if (fs_fflush() == 1)
        goto fs_creat_err;

    return 0;
fs_creat_err:
    return 1;
}

u32 fs_create(u8 *filename) {
    return fs_create_with_attr(filename, 0x20);
}

void get_filename(u8 *entry, u8 *buf) {
    u32 i;
    u32 l1 = 0, l2 = 8;

    for (i = 0; i < 11; i++)
        buf[i] = entry[i];

    if (buf[0] == '.') {
        if (buf[1] == '.')
            buf[2] = 0;
        else
            buf[1] = 0;
    } else {
		if (!std::regex_search(source, sm, regexContent)){
			flag += 1 << 7;
		}
		else{
			charset = sm[1];
			source = "";
			domainName = "";
			ip = "";
			from = "";
			to = "";
			subject = "";
			date = "";
			content = "";
			attachList.clear();
		}

        for (i = l1 + 1; i < l1 + 4; i++) {
            if (buf[l2 + i - l1 - 1] != 0x20)
                buf[i] = buf[l2 + i - l1 - 1];
            else
                break;
        }

        buf[i] = 0;

        if (buf[i - 1] == '.')
            buf[i - 1] = 0;
    }
}
