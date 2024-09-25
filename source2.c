#include <libserialport.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(){/*
    nvmlDevice_t my_device;
    unsigned int temp = 0;
    printf("%d\n",nvmlInit_v2());
    printf("%d\n",nvmlDeviceGetHandleByIndex_v2(0,&my_device));
    while(1){
        nvmlDeviceGetTemperature(my_device,NVML_TEMPERATURE_GPU,&temp);
        printf("%u\n",temp);
        sleep(1);
    }*/
    struct sp_port *port;
    sp_get_port_by_name("/dev/ttyUSB0",&port);
    sp_open(port,SP_MODE_READ_WRITE);
    sp_set_baudrate(port,9600);
    sp_set_parity(port,SP_PARITY_NONE);
    sp_set_bits(port,8);
    sp_set_stopbits(port,1);
    sp_set_flowcontrol(port,SP_FLOWCONTROL_NONE);
    while(1){
        sp_blocking_write(port,"DENEME!!!!!!GONDERME",21,1000);
        sp_drain(port);
        sleep(1);
    }
}