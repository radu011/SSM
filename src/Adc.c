#include "Adc.h"
#include "Uart.h"

volatile uint8_t flagADC;
uint16_t analog_input;

void ADC0_Init(void)
{
	/* activarea semnalului de ceas pentru modulul periferic ADC */
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

	/* functia de calibrare */
	ADC0_Calibrate();

	/* valoare de reset pentru CFG1 */
	ADC0->CFG1 = 0x00;

	/* selectarea modului de conversie pe 10 biti single-ended --> MODE => pun 2 ca sa fie 10 biti pentru rezolutie (single-ended precision) */
	/* selectarea sursei de ceas pentru generarea ceasului intern --> ADICLK */
	/* selectarea ratei de divizare folosit de periferic pentru generarea ceasului intern --> ADIV */
	ADC0->CFG1 |= ADC_CFG1_MODE(2) |
				  ADC_CFG1_ADICLK(0) |
				  ADC_CFG1_ADLSMP_MASK |
				  ADC_CFG1_ADIV(2);
	ADC0->CFG2 |= ADC_CFG2_ADLSTS_MASK;

	/* DIFF = 0 --> Conversii single-ended (PG. 464) */
	/* reset pentru a le seta ulterior */
	ADC0->SC1[0] = 0x00;
	ADC0->SC3 = 0x00;

	/* selectarea modului de conversii continue, */
	/* pentru a-l putea folosi in tandem cu mecanismul de intreruperi */
	ADC0->SC3 |= ADC_SC3_ADCO_MASK | ADC_SC3_AVGS(3);

	/* activarea subsistemului de conversie prin aproximari succesive pe un anumit canal (PG.464) */
	ADC0->SC1[0] |= ADC_SC1_ADCH(ADC_CHANNEL);

	/* enables conversion complete interrupts */
	ADC0->SC1[0] |= ADC_SC1_AIEN_MASK;

	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);

	flagADC = 0;
}

int ADC0_Calibrate(void)
{

	/* ===== For best calibration results ===== */

	ADC0_CFG1 |= ADC_CFG1_MODE(3) |	  /* 16 bits mode */
				 ADC_CFG1_ADICLK(1) | /* Input Bus Clock divided by 2 */
				 ADC_CFG1_ADIV(3);	  /* Clock divide by 8 */

	/* The calibration will automatically begin if the SC2[ADTRG] is 0. (PG. 495) */
	ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;

	/* Set hardware averaging to maximum, that is, SC3[AVGE]=1 and SC3[AVGS]=0x11 for an average of 32 (PG. 494) */
	ADC0->SC3 |= (ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3));

	/* To initiate calibration, the user sets SC3[CAL] (PG. 495) */
	ADC0->SC3 |= ADC_SC3_CAL_MASK;

	/* At the end of a calibration sequence, SC1n[COCO] will be set (PG. 495) */
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK))
		;

	/* At the end of the calibration routine, if SC3[CALF] is not */
	/* set, the automatic calibration routine is completed successfully. (PG. 495) */
	if (ADC0->SC3 & ADC_SC3_CALF_MASK)
	{
		return (1);
	}

	/* ====== CALIBRATION FUNCTION (PG.495) ===== */

	/* 1. Initialize or clear a 16-bit variable in RAM. */
	uint16_t calibration_var = 0x0000;

	/* 2. Add the plus-side calibration results CLP0, CLP1, CLP2, CLP3, CLP4, and CLPS to the variable. */
	calibration_var += ADC0->CLP0;
	calibration_var += ADC0->CLP1;
	calibration_var += ADC0->CLP2;
	calibration_var += ADC0->CLP3;
	calibration_var += ADC0->CLP4;
	calibration_var += ADC0->CLPS;

	/* 3. Divide the variable by two. */
	calibration_var /= 2;

	/* 4. Set the MSB of the variable. */
	calibration_var |= 0x8000;

	/* 5. Store the value in the plus-side gain calibration register PG. */
	ADC0->PG = ADC_PG_PG(calibration_var);

	/* 6. Repeat the procedure for the minus-side gain calibration value. */
	calibration_var = 0x0000;

	calibration_var += ADC0->CLM0;
	calibration_var += ADC0->CLM1;
	calibration_var += ADC0->CLM2;
	calibration_var += ADC0->CLM3;
	calibration_var += ADC0->CLM4;
	calibration_var += ADC0->CLMS;

	calibration_var /= 2;

	calibration_var |= 0x8000;

	ADC0->MG = ADC_MG_MG(calibration_var);

	/* Incheierea calibrarii */
	ADC0->SC3 &= ~ADC_SC3_CAL_MASK;

	return (0);
}

void ADC0_IRQHandler(void)
{
	analog_input = (uint16_t)ADC0->R[0];

	flagADC = 1;

	/* dezactivare intrerupere */
	ADC0->SC1[0] &= ~ADC_SC1_AIEN_MASK;
}
