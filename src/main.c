#include "stm8s.h"
#include "milis.h"

#include <stdio.h>
#include "uart1.h"
#include "swi2c.h"

#define _ISOC99_SOURCE
#define _GNU_SOURCE


void setup(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz


    init_milis();
    init_uart1();
    swi2c_init();
}


int main(void)
{
    uint32_t time = 0;
    uint8_t precteno[10] = {0,0,0,0,0,0,0,0,0,0};
    uint8_t zapsano[10] = {0,0,0,0,0,0,0,0,0,0};
    uint8_t err;


    setup();


    zapsano[0] = 0x40;  // sekundy
    zapsano[1] = 0x32;  // minuty
    zapsano[2] = 0x17;  // hodiny
    zapsano[3] = 0x07;  // den v týdnu
    zapsano[4] = 0x24;  // den
    zapsano[5] = 0x04;  // měsíc
    zapsano[6] = 0x22;  // rok

    

    while (1) {
        if (milis() - time > 1000) {

            // rtc read
            err = swi2c_read_buf(0x68, 0x00, precteno, 7);

            printf("%d%d.%d%d. 20%d%d %d%d:%d%d:%d%d \r\n",       // time in bdc
                   precteno[4] >> 4, precteno[4] & 0x0F,
                   precteno[5] >> 4, precteno[5] & 0x0F,
                   precteno[6] >> 4, precteno[6] & 0x0F,
                   precteno[2] >> 4, precteno[2] & 0x0F,
                   precteno[1] >> 4, precteno[1] & 0x0F,
                   precteno[0] >> 4, precteno[0] & 0x0F);


            time = milis();
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
