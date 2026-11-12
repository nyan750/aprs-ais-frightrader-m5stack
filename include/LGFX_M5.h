#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// M5Stack Basic display configuration (HYPOTHESIS - to be confirmed by m5 v1 diag)
//   Panel : ILI9342C, 320x240 native landscape (Panel_ILI9342 defaults)
//   Bus   : SPI SCLK=18 MOSI=23 MISO=19 DC=27, CS=14, RST=33
//   Light : GPIO32 (PWM)
//   Buttons (separate, not in this file): BtnA=GPIO39 BtnB=GPIO38 BtnC=GPIO37, active LOW
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ILI9342 _panel;
  lgfx::Bus_SPI       _bus;
  lgfx::Light_PWM     _light;

public:
  LGFX() {
    {
      auto cfg = _bus.config();
      cfg.spi_host    = VSPI_HOST;
      cfg.spi_mode    = 0;
      cfg.freq_write  = 40000000;
      cfg.freq_read   = 16000000;
      cfg.spi_3wire   = false;
      cfg.use_lock    = true;
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk = 18;
      cfg.pin_mosi = 23;
      cfg.pin_miso = 19;
      cfg.pin_dc   = 27;
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }
    {
      auto cfg = _panel.config();
      cfg.pin_cs   = 14;
      cfg.pin_rst  = 33;
      cfg.pin_busy = -1;
      cfg.panel_width   = 320;
      cfg.panel_height  = 240;
      cfg.memory_width  = 320;
      cfg.memory_height = 240;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.offset_rotation = 0;
      cfg.readable  = false;
      cfg.invert    = true;    // M5Stack Basic panels are commonly inversion ON
      cfg.rgb_order = false;   // RGB order (hypothesis)
      cfg.dlen_16bit = false;
      cfg.bus_shared = true;   // SD card shares this SPI bus on M5Stack Basic
      _panel.config(cfg);
    }
    {
      auto cfg = _light.config();
      cfg.pin_bl      = 32;    // M5Stack Basic backlight
      cfg.invert      = false;
      cfg.freq        = 44100;
      cfg.pwm_channel = 7;
      _light.config(cfg);
      _panel.setLight(&_light);
    }
    setPanel(&_panel);
  }
};
