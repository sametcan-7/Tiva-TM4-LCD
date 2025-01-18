/*
 * lcd.h
 *
 *  Created on: 10 Kas 2024
 *      Author: Samet CAN
 */

#ifndef LCD_H_
#define LCD_H_

#define LCDPORT     GPIO_PORTB_BASE
#define RS          GPIO_PIN_0
#define E           GPIO_PIN_1
#define D4          GPIO_PIN_4
#define D5          GPIO_PIN_5
#define D6          GPIO_PIN_6
#define D7          GPIO_PIN_7


void lcdkomut(unsigned char); // 0 la 255 arasında veri
// rs=0
// d4-d7 arasında veri yaz
// ve en ac kapa

void lcdkarakteryaz(unsigned char);
// rs=1
// d4-d7 arasında veri yaz
// ve en ac kapa


void LCDIlkayarlar();

// Giriş kipini seç 0 0 0 0 0 0 0 1 I/D S 40μs
// Ekran aç/kapa 0 0 0 0 1 D C B 40μs
// Kursor kaydır 0 0 0 0 0 0 0 1 S/C R/L * * 40μs




void LCDTemizle();
// rs=0
// d4-d7 arasında veri yaz 01h
// ve en ac kapa

void LCDgit(unsigned char, unsigned char);
// 1.satır 5.sütun  85



// 2.satır 7.sütun c7





#endif /* LCD_H_ */
