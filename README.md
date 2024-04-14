# BLDCMotorDriver
This project heavily references the code seen in the [simpleFOC repository](https://github.com/simplefoc), but is modified to run on the [Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) using [PlatformIO](https://platformio.org/).
## IMPORTANT: USB driver to flash PlatformIO firmware to Pi Pico
If you don't do the following steps on your Pi Pico you'll likely encounter [this error](https://community.platformio.org/t/upload-error-1-on-pio-with-raspberry-pi-pico/36841).

1. Download the [Zadig USB driver installer](https://zadig.akeo.ie/)
2. Connect your Pico to your computer with a USB cable
3. Hold BOOTSEL on your Pico
4. Run Zadig and for RP2 Boot (Interface 1) install `libusb-win32 (v1.2.7.3)` or `WinUSB (v6.1.7600.16385)` \
   &rarr; we were able to get the firmware flashing to work with `libsub` but if you have issues try `WinUSB`
   ![image](https://github.com/zackvega1/BLDCMotorDriver/assets/79417604/b3ce031a-80eb-4ed7-934b-d532f9640b4f)

Once you have installed the USB driver of your choice on the PICO, perform the following steps when you want to reflash firmware:
1. Build your project in PlatformIO
2. Hold BOOTSEL on your Pico and power cycle
3. Manually drag `.pio/build/pico/firmware.uf2` to the mounted Pico drive
