# BLDCMotorDriver
This project heavily references the code seen in the [simpleFOC repository](https://github.com/simplefoc), but is modified to run on the [Raspberry Pi Pico](https://datasheets.raspberrypi.com/pico/pico-datasheet.pdf) using [PlatformIO](https://platformio.org/).

## Prototype BLDC Driver Board
Reference this link for the prototypical BLDC driver board developing during ROB 310 Winter 2024:
[BLDC Motor Driver Board](https://u.easyeda.com/account/user/projects/index/detail?project=8bae73a7920e45f9aaeda30bf190f509&listType=all)
#Table of Contents
1. [IMPORTANT: USB driver](#USB)
2. [PlatformIO Setup](#PlatformIO)
3. [Results](#Results)
## IMPORTANT: USB driver to flash PlatformIO firmware to Pi Pico <a name="USB"></a>
If you don't do the following steps on your Pi Pico you'll likely encounter [this error](https://community.platformio.org/t/upload-error-1-on-pio-with-raspberry-pi-pico/36841).

1. Download the [Zadig USB driver installer](https://zadig.akeo.ie/)
2. Connect your Pico to your computer with a USB cable
3. Hold BOOTSEL on your Pico
4. Run Zadig and for RP2 Boot (Interface 1) install `libusb-win32 (v1.2.7.3)` or `WinUSB (v6.1.7600.16385)` \
   &rarr; we were able to get the firmware flashing to work with `libusb` but if you have issues try `WinUSB`
   ![image](https://github.com/zackvega1/BLDCMotorDriver/assets/79417604/b3ce031a-80eb-4ed7-934b-d532f9640b4f)

Once you have installed the USB driver of your choice on the Pico, perform the following steps when you want to reflash firmware:
1. Build your project in PlatformIO
2. Hold BOOTSEL on your Pico and power cycle
3. Manually drag `.pio/build/pico/firmware.uf2` to the mounted Pico drive

## PlatformIO Setup <a name="PlatformIO"></a>

PlatformIO is the platform used to compile and build for the Raspberry Pi Pico. Follow the instructions below to install PlatformIO:

1. **Download [VSCode](https://code.visualstudio.com/download).**

2. **Open the Extension Manager:**
   
   ![Extension Manager](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/c0954756-525f-4f14-bcf0-7755ecf2ab5f)

4. **Search for PlatformIO and install it:**
   
   ![Search for PlatformIO](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/32f7f32e-b68f-45a6-b3c8-3ce3731a133d)
   *Note: If you have not previously installed it, you'll see an "Install" button.*

5. **Restart VSCode.**
   Once restarted, you should see the PlatformIO icon on the left taskbar:

   ![PlatformIO Icon](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/b7f89b3e-3946-4a94-a979-ec8b93917aab)

6. **Confirmation:**
   If you see this icon, PlatformIO is successfully installed.

7. **For more information about PlatformIO, refer to the [documentation](https://platformio.org/).**

## Running the Code

1. **Clone or download the repository.**

2. **Open VSCode and click on the PlatformIO Icon.**

   ![PlatformIO Icon](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/b7f89b3e-3946-4a94-a979-ec8b93917aab)

4. **Your screen should look like this:**

   ![PlatformIO Screen](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/b1bb9a22-d8a3-49f6-9a26-d2f568d52e41)

6. **Click on "Open Project".**
   
   ![Open Project](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/651eeb70-93d0-4f80-a398-4125c55c5cbc)

8. **Locate the directory where you saved your repository and click "Open".**
   *Note: Make sure to open the folder titled "BLDC".*

9. **PlatformIO will begin installing all necessary dependencies. This may take some time.**

10.**Once PlatformIO finishes installing everything click the build button in project tasks, this will compile the code. This will take a very long time on your first compile and be faster after that.**

![image](https://github.com/zackvega1/BLDCMotorDriver/assets/98603447/972cdf59-b17f-4e3f-9e0e-25a76ede6f96)

### Place the Pico in BOOTSEL Mode by unplugging it, holding down the BOOTSEL button, then plugging it back in. You should see a mounted drive appear on your computer. 

11. **Go to the directory of repository. In the pico/build folder you should see a firmware.uft file once PlatformIO has finished buliding your code. Drag this to the pico**
12. **The Pico should then eject and your code will have been uploaded to the pico**


## Initial Testing Results: <a name="Results"></a>

# Random Setpoint Position Control

https://github.com/zackvega1/BLDCMotorDriver/assets/79417604/a46cdf18-8f71-4b4d-b843-c2d0ab8e5b1c

# Sine Wave Trajectory

https://github.com/zackvega1/BLDCMotorDriver/assets/79417604/abbf2bf4-174d-46f4-b3fa-4214b0e3bb09

# Compliant Operation (Torque Limited)

https://github.com/zackvega1/BLDCMotorDriver/assets/79417604/30a29a10-5d14-485c-8b83-cfc31a08579d









