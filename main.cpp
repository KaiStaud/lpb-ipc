#include <shmem/doubler.h>
#include "stdio.h"
#include <unistd.h>

int main(){
open_wo_od();

printf("Testing for R-OD ...\r\n");
while(access("/dev/shm/shmem-example", 0) != 0);
if (access("/dev/shm/shmem-example", 0) == 0){
    open_ro_od();
    printf("R-OD exists\r\n");

int i=0;
while(1){
access_shared_od();
create_shared_wo_od(i++);
usleep(500000);
}
}

close_ro_od();
close_wo_od();

}