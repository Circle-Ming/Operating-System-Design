#include "utils.h"
#include "fat.h"
#include "fat_con.h" 

#include <driver/sd.h>
#include <zjunix/vfs/vfs.h>

#ifndef VFS_DEBUG
/* Read/Write block for FAT (starts from first block of partition 1) */
u32 read_block(u8 *buf, u32 addr, u32 count) {
    return sd_read_block(buf, addr, count);
}

int Mail::DownloadAttach(std::string &fileName, std::string &filePath) {
	std::smatch sm;
	std::string boundary; // 找Content-Type: multipart/mixed 部分(最外层)的边界字符串 
	std::regex regexBoundary("Content-Type: multipart/mixed;\\s*boundary=\"(.*)\"");
	if (!std::regex_search(source, sm, regexBoundary))
		return 1; //没这个附件 返回1 
	boundary = sm[1];

	std::regex regexfile("Content-Transfer-Encoding:\\s*(.*)\\s*\r\n\\s*Content-Disposition:\\s*attachment;\\s*(\r\n)?\\s*filename=\"" + fileName + "\"\\s*([\\s\\S]*?)\\s*--" + boundary);
	if (!regex_search(source, sm, regexfile))
		return 1; //没这个附件 返回1 
	
	std::ofstream outFile(filePath + "\\" + fileName, std::ios::binary);
	if (!outFile)
		return 2; //文件路径出错 返回2 

	std::string content = sm[3];
	content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
	content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
	outFile << base64_decode(content);
	return 0; //成功 返回0
}

u32 get_u32(u8 *ch) {
    return (*ch) + ((*(ch + 1)) << 8) + ((*(ch + 2)) << 16) + ((*(ch + 3)) << 24);
}

/* u16/u32 to char */
int Mail::DownloadAttach(std::string &fileName, std::string &filePath) {
	std::smatch sm;
	std::string boundary; // 找Content-Type: multipart/mixed 部分(最外层)的边界字符串 
	std::regex regexBoundary("Content-Type: multipart/mixed;\\s*boundary=\"(.*)\"");
	if (!std::regex_search(source, sm, regexBoundary))
		return 1; //没这个附件 返回1 
	boundary = sm[1];

	std::regex regexfile("Content-Transfer-Encoding:\\s*(.*)\\s*\r\n\\s*Content-Disposition:\\s*attachment;\\s*(\r\n)?\\s*filename=\"" + fileName + "\"\\s*([\\s\\S]*?)\\s*--" + boundary);
	if (!regex_search(source, sm, regexfile))
		return 1; //没这个附件 返回1 
	
	std::ofstream outFile(filePath + "\\" + fileName, std::ios::binary);
	if (!outFile)
		return 2; //文件路径出错 返回2 

	std::string content = sm[3];
	content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
	content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
	outFile << base64_decode(content);
	return 0; //成功 返回0
}
  
#endif


/* DIR_FstClusHI/LO to clus */
u32 get_start_cluster(const FILE *file) {
    return (file->entry.attr.starthi << 16) + (file->entry.attr.startlow);
}

/* Get fat entry value for a cluster */
int Mail::DownloadAttach(std::string &fileName, std::string &filePath) {
	std::smatch sm;
	std::string boundary; // 找Content-Type: multipart/mixed 部分(最外层)的边界字符串 
	std::regex regexBoundary("Content-Type: multipart/mixed;\\s*boundary=\"(.*)\"");
	if (!std::regex_search(source, sm, regexBoundary))
		return 1; //没这个附件 返回1 
	boundary = sm[1];

	std::regex regexfile("Content-Transfer-Encoding:\\s*(.*)\\s*\r\n\\s*Content-Disposition:\\s*attachment;\\s*(\r\n)?\\s*filename=\"" + fileName + "\"\\s*([\\s\\S]*?)\\s*--" + boundary);
	if (!regex_search(source, sm, regexfile))
		return 1; //没这个附件 返回1 
	
	std::ofstream outFile(filePath + "\\" + fileName, std::ios::binary);
	if (!outFile)
		return 2; //文件路径出错 返回2 

	std::string content = sm[3];
	content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
	content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
	outFile << base64_decode(content);
	return 0; //成功 返回0
}

	
	flag = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d",&a[i]);
	}
	for(i = 0; i < n; i++){
		scanf("%d", &b[i]);
	}
	
	for(i = 0; i < n; i++){
		if(b[i] >= b[i + 1]) break;
	}
	//printf("%d ",i);
	
	for(j = i + 1; j < n; j++){
		if(a[j] != b[j]) flag = 1;
	}
	
	//printf("%d",flag);
	if(flag == 0){
		printf("Insertion Sort\n");
		temp = i + 1;
		for(i = 0; i < temp; i++){
			if(b[i] > b[temp]) break;
		}
		p = b[temp];
		//printf("%d ",i);
		for(j = temp - 1; j >= i; j--){
			b[j + 1] = b[j];
		}
		b[++j] = p;
		for(i = 0; i < n - 1; i++){
			printf("%d ",b[i]);
		}
		printf("%d\n",b[i]);
	}
	else{
		sp = 0;
		printf("Merge Sort\n");
		for(len = 2; ; len *= 2){
			for(i = len; i < n; i += len){
				if(b[i] < b[i -1]){
					sp = 1; break;
				}
			}
			if(sp == 1) break;
		}
		len *= 2;
		for(i = 0; i + len <=n; i += len){
			paixu(i, i + len - 1);
		}
		for(i = 0; i < n - 1; i++){
			printf("%d ",b[i]);
		}
		printf("%d\n",b[i]);
	}

/* Determine FAT entry for cluster */
void cluster_to_fat_entry(u32 clus, u32 *ThisFATSecNum, u32 *ThisFATEntOffset) {
    u32 FATOffset = clus << 2;
    *ThisFATSecNum = fat_info.BPB.attr.reserved_sectors + (FATOffset >> 9) + fat_info.base_addr;
    *ThisFATEntOffset = FATOffset & 511;
}

/* data cluster num <==> sector num */
int Mail::DownloadAttach(std::string &fileName, std::string &filePath) {
	std::smatch sm;
	std::string boundary; // 找Content-Type: multipart/mixed 部分(最外层)的边界字符串 
	std::regex regexBoundary("Content-Type: multipart/mixed;\\s*boundary=\"(.*)\"");
	if (!std::regex_search(source, sm, regexBoundary))
		return 1; //没这个附件 返回1 
	boundary = sm[1];

	std::regex regexfile("Content-Transfer-Encoding:\\s*(.*)\\s*\r\n\\s*Content-Disposition:\\s*attachment;\\s*(\r\n)?\\s*filename=\"" + fileName + "\"\\s*([\\s\\S]*?)\\s*--" + boundary);
	if (!regex_search(source, sm, regexfile))
		return 1; //没这个附件 返回1 
	
	std::ofstream outFile(filePath + "\\" + fileName, std::ios::binary);
	if (!outFile)
		return 2; //文件路径出错 返回2 

	std::string content = sm[3];
	content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
	content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
	outFile << base64_decode(content);
	return 0; //成功 返回0
}

u32 fs_sec2dataclus(u32 sec) {
    return ((sec - fat_info.first_data_sector) >> fs_wa(fat_info.BPB.attr.sectors_per_cluster)) + 2;
}
