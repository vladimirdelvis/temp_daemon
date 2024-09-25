#include "sensors/sensors.h"
#include <libserialport.h>
#include <nvml.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

int main(){/*
    sensors_init(NULL); // chip adı
    sensors_chip_name name;
    printf("%d\n",sensors_parse_chip_name("coretemp-isa-0000",&name));
    const sensors_chip_name* p_chip;
    const sensors_feature *feat;
    const sensors_subfeature *sub_feat;
    int nr = 0,nr_feat = 0,nr_subfeat = 0;
    while(1){
        p_chip = sensors_get_detected_chips(&name, &nr);
        if(p_chip == NULL)
            break;
        printf("%s-%d\n",p_chip->prefix,nr);
        while(1){
            feat = sensors_get_features(p_chip,&nr_feat);
            if(feat == NULL)
                break;
            printf("%s-%d\n",feat->name,nr_feat);
            while(1){
            sub_feat = sensors_get_all_subfeatures(p_chip,feat,&nr_subfeat);
            if(sub_feat == NULL)
                break;
            printf("%d-%s-%d\n",sub_feat->number,feat->name,nr_subfeat);
        }
        }
    }
    sensors_free_chip_name(&name);
    sensors_cleanup();*/


//////////////////////////////////////////////////////////////////////////////////////////

    double cpu_temp = 0.0;
    unsigned int gpu_temp = 0;

    sensors_init(NULL);
    nvmlInit_v2();
    sensors_chip_name cpu_device;
    const sensors_chip_name *temp_chip;
    nvmlDevice_t gpu_device;
    struct sp_port *port;

    sensors_parse_chip_name("coretemp-isa-0000",&cpu_device);
    temp_chip = sensors_get_detected_chips(&cpu_device, &(int){0});
    nvmlDeviceGetHandleByIndex_v2(0,&gpu_device);
    sp_get_port_by_name("/dev/ttyUSB0",&port);

    sp_open(port,SP_MODE_WRITE);
    sp_set_baudrate(port,9600);
    sp_set_parity(port,SP_PARITY_NONE);
    sp_set_bits(port,8);
    sp_set_stopbits(port,1);
    sp_set_flowcontrol(port,SP_FLOWCONTROL_NONE);
    sleep(3);
    char *temp_tuple;
    temp_tuple = malloc(8);
    while(1){
        sensors_get_value(temp_chip,0,&cpu_temp);
        nvmlDeviceGetTemperature(gpu_device,NVML_TEMPERATURE_GPU,&gpu_temp);
        snprintf(temp_tuple,4,"%-3d",(int)cpu_temp);
        snprintf(temp_tuple + 4,4,"%-3d",(int)gpu_temp);
        sp_blocking_write(port,temp_tuple,8,1000);
        sp_drain(port);
        //printf("CPU: %u - GPU: %u\n",(unsigned int)cpu_temp,gpu_temp);
        sleep(1);
    }
}
