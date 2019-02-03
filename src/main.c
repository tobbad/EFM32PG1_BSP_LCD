#include "em_device.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_chip.h"
#include "bspconfig.h"

#include "display.h"
#include "render.h"

#include "img/qrcode.xbm"
#include "img/splash.xbm"

#define DISPLAY_DEVICE_NO       (0)

#include "hal-config.h"

static void showWelcomeScreen(void)
{
  RENDER_SetFramebuffer(splash);
  RENDER_Write(4, 96, "PB0   : Play/Pause");
  RENDER_Write(4, 104, "PB1   : Fire missile");
  RENDER_Write(4, 112, "Touch : Move tank");
}

int main(void)
{
	EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_STK_DEFAULT;
	CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_STK_DEFAULT;
	/* Chip errata */
	CHIP_Init();
	/* Init DCDC regulator and HFXO with kit specific parameters */
	EMU_DCDCInit(&dcdcInit);
	CMU_HFXOInit(&hfxoInit);

	/* Switch HFCLK to HFXO and disable HFRCO */
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
	CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

	/* Setup SysTick Timer for 1 msec interrupts  */
	if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
	while (1) ;
	}

	showWelcomeScreen();

	/* Infinite loop */
	while (1) {
	}
}


