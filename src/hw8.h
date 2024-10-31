#ifndef __HW8_H
#define __HW8_H

void fatInit();
long fatOpen(char* filepath, struct root_directory_entry* r);
void fatRead(char* buf, struct root_directory_entry *r, int n);

#endif
