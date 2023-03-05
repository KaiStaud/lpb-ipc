#include <shmem/doubler.h>
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define NAME "/shmem-example" // Feedback file Rust -> C
#define RQNAME "/fb-shmem-example"
#define NUM 10
#define SIZE 128 //( NUM * sizeof( int ) )

extern "C" {

int r_fd;
int w_fd;
int* r_data;
int* w_data;

void open_ro_od(){
  // Receive Messages:
 r_fd = shm_open( NAME, O_RDONLY, 0666 );
  if ( r_fd < 0 )
  {
    perror( "shm_open()" );
  }

 r_data = (int*)mmap( 0, SIZE, PROT_READ, MAP_SHARED, r_fd, 0 );
}
 void open_wo_od(){
  w_fd = shm_open( RQNAME, O_CREAT | O_EXCL | O_RDWR, 0600 );
  if ( w_fd < 0 )
  {
    perror( "shm_open()" );
  }

  ftruncate( w_fd, SIZE );

  w_data = (int*)mmap( 0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, w_fd, 0 );

}

void close_ro_od(){
  munmap( r_data, SIZE );
  close( r_fd );
  shm_unlink( NAME );
}

void close_wo_od(){
  munmap( w_data, SIZE );
  close( w_fd );
  shm_unlink( RQNAME );
}

void access_shared_od(){

//  for ( int i = 0; i < NUM; ++i )
//  {
    printf("%i\r\n", r_data[0]);// = i;
//  }

}

// Request file: Rust -> C
void create_shared_wo_od(int data){

  for ( int i = 0; i < NUM; ++i )
  {
    w_data[i] = data*40;
  }

}

}