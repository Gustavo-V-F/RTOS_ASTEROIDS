#ifndef NOKIA5110_H_
#define NOKIA5110_H_

#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "defPrincipais.h"
#include "_delay.h"

//-------------------------------------------------------------------------------------
// RST (A7)
#define SET_RST()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)
#define CLR_RST()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)

// CE (A6)
#define SET_CE()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)
#define CLR_CE()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)

// DC (A5)
#define SET_DC()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define CLR_DC()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)

// DIN (A4)
#define SET_DIN()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define CLR_DIN()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

// CLK (A3)
#define SET_CLK()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define CLR_CLK()		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)

//-------------------------------------------------------------------------------------
#define PULSO_CLK() _delay_us(1); SET_CLK(); _delay_us(1); CLR_CLK()

#define INVERTE_PIXELS()		cmd_LCD(0x0D)
#define NORMALIZA_PIXELS()		cmd_LCD(0x0C)
//-------------------------------------------------------------------------------------

struct pontos_t{
	uint32_t x1;
	uint32_t y1;
	uint32_t x2;
	uint32_t y2;
	uint32_t x3;
	uint32_t y3;
};

struct sig_pontos_t{
	int32_t x1;
	int32_t y1;
	int32_t x2;
	int32_t y2;
	int32_t x3;
	int32_t y3;
};

struct figura_t
{
	unsigned char largura;
	unsigned char altura;
	unsigned char pixels[];
};

void cmd_LCD(uint32_t data);
void data_LCD(uint32_t data);
void inic_LCD(); 
void goto_XY(uint32_t x, uint32_t y);
uint32_t index_XY(uint32_t x, uint32_t y);
void rotate_clock_wise(uint32_t *x, uint32_t *y, int32_t *x0, int32_t *y0);
void rotate_counter_clock_wise(uint32_t *x, uint32_t *y, int32_t *x0, int32_t *y0);
void escreve2fb(unsigned char imagem[])	;
void imprime_LCD();
void imprime_area_LCD(struct pontos_t *p);
void caractere_LCD(char character);
void string_LCD(char *msg);
void limpa_LCD(); 

// Funções do Borges
void string_LCD_Nr(char * msg, uint32_t valor, uint32_t quant2Print);

void desenha_pixel(uint32_t x, uint32_t y, uint32_t propriedade);
void desenha_linha(struct pontos_t *coord, uint32_t prop);
void desenha_circulo(int32_t x0, int32_t y0, int32_t radius, uint32_t prop);
void desenha_retangulo(struct  pontos_t *t, uint32_t prop);
void desenha_triangulo(struct  pontos_t *p, struct sig_pontos_t *ref, uint32_t prop);
void desenha_fig(struct  pontos_t *p, const struct figura_t *figura);

void escreve_Nr_Peq(uint32_t x, uint32_t y, int32_t valor, uint32_t quant2Print);

// New Functions
void desenha_hexagono(struct pontos_t *coord, struct sig_pontos_t *ref, uint32_t prop);

// Sin and cos functions
signed int sin30(signed int angle);
signed int cos30(signed int angle);

// Math functions
uint32_t round_number(uint32_t number, uint32_t digits);

//-------------------------------------------------------------------------------------
#endif /* NOKIA5110_H_ */
