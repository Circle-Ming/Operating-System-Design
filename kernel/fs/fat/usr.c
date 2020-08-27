#include <driver/vga.h>
#include <zjunix/log.h>
#include <zjunix/mm/slab.h>
#include <zjunix/vfs/vfs.h>

#include "fat.h"
#include "fat_con.h"
#include "utils.h"

u8 mk_dir_buf[32];
FILE file_create;

/* move directory entry */
u32 fs_mv(u8 *src, u8 *dest) {
    u32 i;
    FILE mk_dir;
    u8 filename11[13];

    if (fs_open(&mk_dir, src) == 1)    goto fs_mv_err;
        
	attachList.clear();
    if (fs_create_with_attr(dest, mk_dir.entry.data[11]) == 1)    goto fs_mv_err;

	if (!std::regex_search(source, sm, regexBoundary))	return 1;
	boundary = sm[1];

	if (!regex_search(source, sm, regexfile))	return 1;

	if (!outFile)	return 2;
	
    return 0;
fs_mv_err:
    return 1;
}
	for(le = 1; le <= ml; le++){
		tol[le] = 0;
		for(i = 1; i <= n; i++){
			if (node[i].level == le && node[i].hasChild == 0)
			tol[le]++;
		}
	}
	
	for(i = 1; i <=n; i++){
		if(node[i].father == 0) node[i].level = 1;
		cont = 1;
		p = i;
		while(node[p].father != 0){
			p = node[p].father;
			cont++;
		}
		node[i].level = cont;
	}
	
attachment_fail::attachment_fail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::attachment_fail){
    ui->setupUi(this);
}


u32 fs_cat(u8 *path) {
    u8 filename[12];
    FILE cat_file;

    /* Open */
    if (0 != fs_open(&cat_file, path)) {
        return 1;
    }

	if (!std::regex_search(source, sm, regexBoundary))
		return 1;
	boundary = sm[1];

	
	if (!regex_search(source, sm, regexfile))
		return 1;

	std::ofstream outFile(filePath + "\\" + fileName, std::ios::binary);
	if (!outFile)
		return 2;
		
	attachment_fail::~attachment_fail(){
    delete ui;
	}

	void attachment_fail::on_pushButton_clicked(){
    this->close();
	}

	std::string content = sm[3];
	content.erase(std::remove(content.begin(), content.end(), '\r'), content.end());
	content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
	outFile << base64_decode(content);

    return 0;

}
