/************************************************************************
* 5 semestre - Eng. da Computao - Insper
* Rafael Corsi - rafael.corsi@insper.edu.br
*
* Material:
*  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
*
* Objetivo:
*  - Demonstrar configuraçao do PIO
*
* Periféricos:
*  - PIO
*  - PMC
*
* Log:
*  - 10/2018: Criação
************************************************************************/

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

// LEDs
#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_IDX      8
#define LED_IDX_MASK (1 << LED_IDX)

// LED 1
#define LED_PIO_1	PIOA
#define LED_PIO_1_ID	ID_PIOA
#define LED_1_IDX	0
#define LED_1_IDX_MASK (1<<LED_1_IDX)

#define LED_PIO_3	PIOB
#define LED_PIO_3_ID	ID_PIOB
#define LED_3_IDX	2
#define LED_3_IDX_MASK (1<<LED_3_IDX)

#define LED_PIO_2	PIOC
#define LED_PIO_2_ID	ID_PIOC
#define LED_2_IDX	30
#define LED_2_IDX_MASK (1<<LED_2_IDX)

// Botão
#define BUT_PIO      PIOA
#define BUT_PIO_ID   ID_PIOA
#define BUT_IDX      11
#define BUT_IDX_MASK (1 << BUT_IDX)

#define BUT_PIO_1      PIOD
#define BUT_PIO_1_ID   ID_PIOD
#define BUT_1_IDX      28
#define BUT_1_IDX_MASK (1 << BUT_1_IDX)

#define BUT_PIO_2      PIOC
#define BUT_PIO_2_ID   ID_PIOC
#define BUT_2_IDX      31
#define BUT_2_IDX_MASK (1 << BUT_2_IDX)

#define BUT_PIO_3      PIOA
#define BUT_PIO_3_ID   ID_PIOA
#define BUT_3_IDX      19
#define BUT_3_IDX_MASK (1 << BUT_3_IDX)

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/


/************************************************************************/
/* constants                                                            */
/************************************************************************/

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* handlers / callbacks                                                 */
/************************************************************************/

/************************************************************************/
/* funções                                                              */
/************************************************************************/

/************************************************************************/
/* Main                                                                 */
/************************************************************************/
/* Funcao principal chamada na inicalizacao do uC.                      */
int main(void)
{
	// Inicializa clock
	sysclk_init();

	// Desativa watchdog
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Ativa PIOs
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	pmc_enable_periph_clk(LED_PIO_1_ID);
	pmc_enable_periph_clk(LED_PIO_2_ID);
	pmc_enable_periph_clk(LED_PIO_3_ID);
	pmc_enable_periph_clk(BUT_PIO_1_ID);
	pmc_enable_periph_clk(BUT_PIO_2_ID);
	pmc_enable_periph_clk(BUT_PIO_3_ID);

	// Configura Pinos
	pio_configure(LED_PIO, PIO_OUTPUT_0, LED_IDX_MASK, PIO_DEFAULT);
	pio_configure(BUT_PIO, PIO_INPUT, BUT_IDX_MASK, PIO_PULLUP);
	
	pio_configure(LED_PIO_1, PIO_OUTPUT_0, LED_1_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED_PIO_2, PIO_OUTPUT_0, LED_2_IDX_MASK, PIO_DEFAULT);
	pio_configure(LED_PIO_3, PIO_OUTPUT_0, LED_3_IDX_MASK, PIO_DEFAULT);
	
	pio_configure(BUT_PIO_1, PIO_INPUT, BUT_1_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT_PIO_2, PIO_INPUT, BUT_2_IDX_MASK, PIO_PULLUP);
	pio_configure(BUT_PIO_3, PIO_INPUT, BUT_3_IDX_MASK, PIO_PULLUP);

	// SUPER LOOP
	// aplicacoes embarcadas no devem sair do while(1).
	while(1) {
		
		if(!pio_get(BUT_PIO_1, PIO_INPUT, BUT_1_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<10; i++) {
				pio_clear(LED_PIO_1, LED_1_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
				pio_set(LED_PIO_1, LED_1_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
			}
			} else  {
			// Ativa o pino LED_IDX (par apagar)
			pio_set(LED_PIO_1, LED_1_IDX_MASK);
		}
		
		if(!pio_get(BUT_PIO_2, PIO_INPUT, BUT_2_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<10; i++) {
				pio_clear(LED_PIO_2, LED_2_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
				pio_set(LED_PIO_2, LED_2_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
			}
			} else  {
			// Ativa o pino LED_IDX (par apagar)
			pio_set(LED_PIO_2, LED_2_IDX_MASK);
		}

		
		if(!pio_get(BUT_PIO_3, PIO_INPUT, BUT_3_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<10; i++) {
				pio_clear(LED_PIO_3, LED_3_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
				pio_set(LED_PIO_3, LED_3_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
			}
			} else  {
			// Ativa o pino LED_IDX (par apagar)
			pio_set(LED_PIO_3, LED_3_IDX_MASK);
		}
		
		// Verifica valor do pino que o botão está conectado
		if(!pio_get(BUT_PIO, PIO_INPUT, BUT_IDX_MASK)) {
			// Pisca LED
			for (int i=0; i<10; i++) {
				pio_clear(LED_PIO, LED_IDX_MASK);  // Limpa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
				pio_set(LED_PIO, LED_IDX_MASK);    // Ativa o pino LED_PIO_PIN
				delay_ms(100);                         // delay
			}
			} else  {
			// Ativa o pino LED_IDX (par apagar)
			pio_set(LED_PIO, LED_IDX_MASK);
		}
	}
	// Nunca devemos chegar aqui !
	return 0;
}