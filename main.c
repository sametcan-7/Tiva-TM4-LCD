#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "lcd.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"




int snbirlerb = 0;
int snonlarb = 0;
int dkbirlerb = 0;
int dkonlarb = 0;
int saatbirlerb = 0;
int saatonlarb = 0;


void timer0IntHandler(void);

int main(void) {

    SysCtlClockSet(SYSCTL_SYSDIV_20 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);


    LCDIlkayarlar();


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    IntMasterEnable();
    IntEnable(INT_TIMER0A);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet() - 1); // 1 saniyelik zamanlama istersen -1 kýsmýný silebilirsin
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntRegister(TIMER0_BASE, TIMER_A, timer0IntHandler);
    TimerEnable(TIMER0_BASE, TIMER_A);


    while (1) {

    }
}

void timer0IntHandler(void) {

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);



    LCDgit(2,8);
    lcdkarakteryaz(83);

    LCDgit(2,9);
    lcdkarakteryaz('C');

    LCDgit(1, 12);
    lcdkarakteryaz(48 + snbirlerb);

    LCDgit(1, 11);
    lcdkarakteryaz(48 + snonlarb);
    LCDgit(1, 10);
    lcdkarakteryaz(58); // ':'

    LCDgit(1, 9);
    lcdkarakteryaz(48 + dkbirlerb);

    LCDgit(1, 8);
    lcdkarakteryaz(48 + dkonlarb);
    LCDgit(1, 7);
    lcdkarakteryaz(58); // ':'

    LCDgit(1, 6);
    lcdkarakteryaz(48 + saatbirlerb);

    LCDgit(1, 5);
    lcdkarakteryaz(48 + saatonlarb);


    snbirlerb++;
    if (snbirlerb > 9) {
        snbirlerb = 0;
        snonlarb++;
    }
    if (snonlarb > 5) {
        snonlarb = 0;
        dkbirlerb++;
    }
    if (dkbirlerb > 9) {
        dkbirlerb = 0;
        dkonlarb++;
    }
    if (dkonlarb > 5) {
        dkonlarb = 0;
        saatbirlerb++;
    }
    if (saatbirlerb > 9) {
        saatbirlerb = 0;
        saatonlarb++;
    }
    if (saatonlarb == 2 && saatbirlerb == 4) { // 23:59:59'dan sonra sýfýrla
        saatonlarb = 0;
        saatbirlerb = 0;
    }
}
