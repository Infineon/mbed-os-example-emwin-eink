# mbed-os-example-emwin-eink

  

## **Introduction**

This code example demonstrates displaying graphics on an EInk display using EmWin graphics library in Mbed OS.

## **Hardware**

This code example can be run using the following Cypress kits.

[CY8CKIT-062 BLE Pioneer Kit](https://www.cypress.com/CY8CKIT-062-BLE) + [CY8CKIT-028-EPD E-Ink Display Shield](https://www.cypress.com/documentation/development-kitsboards/e-ink-display-shield-board-cy8ckit-028-epd)

[CY8CKIT-062-WIFI-BT PSoC 6 WiFi-BT Pioneer Kit](https://www.cypress.com/cy8ckit-062-wifi-bt) + [CY8CKIT-028-EPD E-Ink Display Shield](https://www.cypress.com/documentation/development-kitsboards/e-ink-display-shield-board-cy8ckit-028-epd)

This example uses the kit’s default configuration. Refer to the kit guide to ensure the kit is configured correctly.

**Notes**: 

1. The PSoC 6 BLE Pioneer kit and the PSoC 6 WiFi-BT Pioneer kit ship with KitProg2 installed. Med OS only works with KitProg3. Before using this code example, make sure that the kit is upgraded to KitProg3.  Instructions to upgrade to KitProg3 may be found in the [Firmware Loader](https://github.com/cypresssemiconductorco/Firmware-loader) GitHub repository.

2. Once the firmware is upgraded, the kit has to be put in DAPLINK mode for Mbed to be able to program the board.  Refer the **KitProg3 User Guide** (found in the Documentation tab in the [Cypress Programming Solutions](https://www.cypress.com/products/psoc-programming-solutions) web page) for details of how to put the Pioneer Kit into DAPLINK mode.

## **Instructions to run the code example**

1. Import the code example into your mbed directory using following mbed command.

    `mbed import https://github.com/cypresssemiconductorco/mbed-os-example-emwin-eink`

2. Change working directory to the code example folder

    `cd mbed-os-example-emwin-eink`

3. Compile the code and program the target board.

    `mbed compile --toolchain GCC_ARM --target CY8CKIT_062_BLE --flash`

## **Code Example Operation**

- Once the project is compiled and the board is programmed, reset the board.
- The program first initializes the EInk display controller.  If there is an error in initialization, for example, if the shield board is not present, the red LED is turned on and the program enters an infinite loop.  
- If the initialization is successful, the startup screen with Cypress logo is displayed on the EInk display for 3 seconds.  
- After 3 seconds, another screen with instructions to press SW2 to scroll through the display pages is displayed.
- Press SW2 to scroll through various display pages that demonstrate the EmWin graphic library's 2D graphics features.  Following are the screens displayed.
    - Font sizes - normal fonts
    - Font sizes - bold fonts
    - Text alignments and styles
    - Text wrap and rotation
    - 2D graphics #1
    - 2D graphics #2
- The green LED is turned on when the display is updated with new content.

## **References**

[Segger EmWin User Guide](https://cypresssemiconductorco.github.io/emwin/UM03001_emWin5.pdf)

[Cypress EmWin Middleware Overview](https://cypresssemiconductorco.github.io/emwin/emwin_overview/html/index.html)

### Document History

Document Title: emWin EInk for Mbed OS

| Revision | Orig. of Change | Submission Date | Description of Change                                |
| -------- | --------------- | --------------- | ---------------------------------------------------- |
| **       | GRAA            | 5/23/2019       | New code example. Tested with Mbed OS Version 5.12.2 |
| *A       | GRAA            | 8/23/2019       | Updated to Mbed OS 5.13.3                            |

------

