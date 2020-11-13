//Header files

#include <stdio.h>                  // printf statements
#include <stdlib.h>                 // exit() statement
#include <stdint.h>                 // uint8_t 
#include <unistd.h>                 // standard symbolic constants and types 
#include <sys/ioctl.h>              // ioctl function call
#include <linux/spi/spidev.h>       // All the functions -- spi read,spi write
#include <linux/types.h>
#include <fcntl.h>
#include "pushAndLed.h" 	    // The code related to push button and led

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a)[0])

static void pabort(const char *s)
{
    perror(s);
    abort();
}


static const char *device = "/dev/spidev0.1";
static uint8_t mode;
static uint8_t bits = 8;
static uint32_t speed=500000;
static uint16_t delay;


static void Transmitter(int fd)
{
    int ret;
    uint8_t Tx[]= {0x01,};

    struct spi_ioc_transfer tr ={
        .tx_buf = (unsigned long)Tx,
        .len = ARRAY_SIZE(Tx),
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bits,
    };

    ret = ioctl(fd,SPI_IOC_MESSAGE(1),&tr);
    if(ret<1)
    {
        pabort("Cannot send the spi message");
    }
    for(ret=0;ret<ARRAY_SIZE(Tx);ret++)
    {
        printf("Starting the Ultrasonic in STM32\n");
    }
}

int main()
{
    int ret=0,fd;
    int syson=0;
    //Opening the device file for reading and writing
    fd =open(device,O_RDWR);
    if(fd<0)
    {
        pabort("Cannot open the device");
    }

    //Setting write mode --SPI
    ret=ioctl(fd,SPI_IOC_WR_MODE,&mode);
    if(ret==-1)
        pabort("Cannot set SPI Mode");
    //Setting the number of bits per word
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if(ret==-1)
        pabort("Cannot set bits per word");
    
    //Setting the speed
    ret = ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if(ret==-1)
        pabort("Cannot set max speed");
    printf("\nCOMMUNICATION BETWEEN BEAGLEBONE BLACK AND STM32\n");
    printf("     VIA SPI TO ACTIVATE ULTRASONIC SENSOR\n");
    printf("\nDesigned by:\n");
    printf("\tRajini R-99002566\n");
    printf("\tSankalpa S-99002582\n");
    printf("\tRohith Pandith-99002531\n");
    printf("\tSanthosh Kumar-99002552\n");
    printf("\nSPI Mode: %d\n",mode);
    printf("Bits per word: %d\n",bits);
    printf("Max speed: %d KHz\n",speed/1000);
    printf("\n");
    printf("To turn the ultra Sonic sensor in STM32 press the push button\n");
    printf("\n");

    //Calling the transmitter function which is responsible for sending data to slave
while(1){   
syson+=pushbutton();
if(syson==1)
{
	Transmitter(fd);
        printf("STARTED\n");
	ledon();
	syson++;
}
else if(syson==3)
{
	printf("System is turned OFF\n");
	    syson=0;
            ledoff();
}
sleep(1);
}
    close(fd);

    return ret;
}



