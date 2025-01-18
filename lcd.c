/*
 * lcd.c
 *
 *  Created on: 10 Kas 2024
 *      Author: Samet CAN
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"
#include "lcd.h"


void otuzhexgonder()
{
    SysCtlDelay(100000);

    GPIOPinWrite(LCDPORT, RS, 0);

    GPIOPinWrite(LCDPORT, D4|D5|D6|D7, 0x30);

    GPIOPinWrite(LCDPORT, E, 2);

    SysCtlDelay(50000);

    GPIOPinWrite(LCDPORT, E, 0);

    SysCtlDelay(50000);




}

void lcdkomut(unsigned char c)
{


    // rs = 0 lcdkomutta
    GPIOPinWrite(LCDPORT, RS, 0);


    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xF0));
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0);
    SysCtlDelay(50000);


    GPIOPinWrite(LCDPORT, RS, 0);
    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0F) << 4);
    GPIOPinWrite(LCDPORT, E, 2);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0);
    SysCtlDelay(50000);



}

void LCDIlkayarlar() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);


    otuzhexgonder();

    otuzhexgonder();

    otuzhexgonder();

        GPIOPinWrite(GPIO_PORTB_BASE, D4 | D5 | D6 | D7,  0x20 );
        GPIOPinWrite(GPIO_PORTB_BASE, E, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, E, 0x00);
        SysCtlDelay(50000);

        LCDTemizle();
        lcdkomut(0x28);//fonksiyon sec 001dl nf00
        lcdkomut(0x06);//Giriş kipini seç
        lcdkomut(0x0c);//ekran aç /kursorü kapa
        LCDTemizle();


}





void lcdkarakteryaz(unsigned char c)
{
    // rs=1 karakteryaz
       GPIOPinWrite(LCDPORT, RS, 1);


       GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0xF0));
       GPIOPinWrite(LCDPORT, E, 2);
       SysCtlDelay(10);
       GPIOPinWrite(LCDPORT, E, 0);
       SysCtlDelay(50000);


       GPIOPinWrite(LCDPORT, RS, 1);
       GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7, (c & 0x0F) << 4);
       GPIOPinWrite(LCDPORT, E, 2);
       SysCtlDelay(10);
       GPIOPinWrite(LCDPORT, E, 0);
       SysCtlDelay(50000);

}

void LCDgit(unsigned char satir, unsigned char sutun) {
    if (satir == 1) {
        lcdkomut(0x80 + (sutun - 1)); // 1. satırın başlangıç adresi
    } else if (satir == 2) {
        lcdkomut(0xC0 + (sutun - 1)); // 2. satırın başlangıç adresi
    }

}
    void LCDTemizle() {
        lcdkomut(0x01);
        SysCtlDelay(10);
    }






// ayarlar devam
//lcd komut kullan
