extern "C" {
pub fn write_wo_od(data:i64);
pub fn access_ro_od();
pub fn close_ro_od();
pub fn open_wo_od();
pub fn close_wo_od();
pub fn open_ro_od();
}

use std::path::Path;
use std::{thread, time};

fn main() {
    unsafe {
        open_wo_od();
    
        loop {
            if Path::new("/dev/shm/fb-shmem-example").exists()
            {
                break;
            }  
        } 
        let mut i= 10;
        loop{
            i = i+1;
            open_ro_od();
            access_ro_od();  
            write_wo_od(i);
            let delay = time::Duration::from_millis(500);
            thread::sleep(delay)   
        }
         //   open_ro_od();
         //   access_ro_od();
            close_ro_od();
            close_wo_od();
        }

}
