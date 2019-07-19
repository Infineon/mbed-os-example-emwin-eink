# mbed-os-example-emwin-eink

Note: This project is not yet tested with Mbed OS version 5.13.x.  This will be done soon.  

## **Introduction**

This code example demonstrates displaying graphics on an EInk display using EmWin graphics library in Mbed OS.

## **Hardware**

This code example can be run using the following Cypress kits.

[CY8CKIT-062BLE Kit with EInk shield](https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-pioneer-kit-cy8ckit-062-ble)

[CY8CKIT-062-WiFi-BT Kit](https://www.cypress.com/documentation/development-kitsboards/psoc-6-wifi-bt-pioneer-kit-cy8ckit-062-wifi-bt) with [CY8CKIT-028-EPD EInk Shield](https://www.cypress.com/documentation/development-kitsboards/e-ink-display-shield-board-cy8ckit-028-epd)  

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

[Segger EmWin User Guide](https://cypresssemiconductorco.github.io/middleware-emwin/UM03001_emWin5.pdf)

[Cypress EmWin Middleware Overview](https://cypresssemiconductorco.github.io/middleware-emwin/emwin_overview/html/index.html)

### Document History

Document Title: emWin OLED for Mbed OS

| Revision | Orig. of Change | Submission Date | Description of Change |
| -------- | --------------- | --------------- | --------------------- |
| **       | GRAA            | 5/23/2019       | New code example. Tested with Mbed OS Version 5.12.2      |

------

