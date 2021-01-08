#include "mbed.h"
#include "rtos.h"
#include "GUI.h"
#include "cyhal.h"
#include "cy8ckit_028_epd_pins.h"
#include "mtb_e2271cs021.h"
#include "LCDConf.h"

DigitalOut led(LED1);
DigitalIn  sw2(CYBSP_USER_BTN, PullUp);

/* Macros for switch press status */
#define BTN_PRESSED        (0u)
#define BTN_RELEASED       (1u)

/* Macros to control LEDs */
#define LED_ON  (0)
#define LED_OFF (1)

/* Macro to set ambient temperature int degree Celsius */
#define AMBIENT_TEMPERATURE_C               (20)
/* Macro to set SPI frequency in Hz */
#define SPI_BAUD_RATE_HZ                    (18000000UL)

/* External global references */
extern GUI_CONST_STORAGE GUI_BITMAP bmCypressLogo_1bpp;

/* Function prototypes */
void ShowFontSizesNormal(void);
void ShowFontSizesBold(void);
void ShowTextModes(void);
void ShowTextWrapAndOrientation(void);
void Show2DGraphics1(void);
void Show2DGraphics2(void);

/* HAL SPI object to interface with display driver */
cyhal_spi_t spi; 

/* Configuration structure defining the necessary pins to communicate with
 * the E-ink display */
const mtb_e2271cs021_pins_t pins =
{
    .spi_mosi = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MOSI,
    .spi_miso = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MISO,
    .spi_sclk = CY8CKIT_028_EPD_PIN_DISPLAY_SPI_SCLK,
    .spi_cs = CY8CKIT_028_EPD_PIN_DISPLAY_CS,
    .reset = CY8CKIT_028_EPD_PIN_DISPLAY_RST,
    .busy = CY8CKIT_028_EPD_PIN_DISPLAY_BUSY,
    .discharge = CY8CKIT_028_EPD_PIN_DISPLAY_DISCHARGE,
    .enable = CY8CKIT_028_EPD_PIN_DISPLAY_EN,
    .border = CY8CKIT_028_EPD_PIN_DISPLAY_BORDER,
    .io_enable = CY8CKIT_028_EPD_PIN_DISPLAY_IOEN,
};

/* Buffer to the previous frame written on the display */
uint8_t previous_frame[PV_EINK_IMAGE_SIZE] = {0};

/* Pointer to the new frame that need to be written */
uint8_t *current_frame;

/*******************************************************************************
* Function Name: void ShowStartupScreen(void)
********************************************************************************
*
* Summary: This function displays the startup screen with Cypress Logo and
*            the demo description text
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowStartupScreen(void)
{
    /* Set foreground and background color and font size */
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();

    GUI_DrawBitmap(&bmCypressLogo_1bpp, 2, 2);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("CYPRESS", 132, 85);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("EMWIN GRAPHICS", 132, 105);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("EINK DISPLAY DEMO", 132, 125);
}


/*******************************************************************************
* Function Name: void ShowInstructionsScreen(void)
********************************************************************************
*
* Summary: This function shows screen with instructions to press SW2 to
*            scroll through various display pages
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowInstructionsScreen(void)
{
    /* Set font size, background color and text mode */
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetColor(GUI_BLACK);
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display instructions text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("PRESS SW2 ON THE KIT", 132, 58);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("TO SCROLL THROUGH ", 132, 78);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("DEMO PAGES!", 132, 98);
}


/*******************************************************************************
* Function Name: void ShowFontSizesNormal(void)
********************************************************************************
*
* Summary: This function shows various font sizes
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowFontSizesNormal(void)
{
    /* Set font size, background color and text mode */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetColor(GUI_BLACK);
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display page title */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("1 OF 6: NORMAL FONTS", 132, 5);

    /* Font8_1*/
    GUI_SetFont(GUI_FONT_8_1);
    GUI_DispStringAt("GUI_Font8_1", 10, 30);

    /* Font10_1*/
    GUI_SetFont(GUI_FONT_10_1);
    GUI_DispStringAt("GUI_Font10_1", 10, 40);

    /* Font13_1*/
    GUI_SetFont(GUI_FONT_13_1);
    GUI_DispStringAt("GUI_Font13_1", 10, 52);

    /* Font16_1*/
    GUI_SetFont(GUI_FONT_16_1);
    GUI_DispStringAt("GUI_Font16_1", 10, 67);

    /* Font20_1*/
    GUI_SetFont(GUI_FONT_20_1);
    GUI_DispStringAt("GUI_Font20_1", 10, 85);

    /* Font24_1*/
    GUI_SetFont(GUI_FONT_24_1);
    GUI_DispStringAt("GUI_Font24_1", 10, 107);

    /* Font32_1*/
    GUI_SetFont(GUI_FONT_32_1);
    GUI_DispStringAt("GUI_Font32_1", 10, 133);
}


/*******************************************************************************
* Function Name: void ShowFontSizesBold(void)
********************************************************************************
*
* Summary: This function shows various font sizes
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowFontSizesBold(void)
{
    /* Set font size, background color and text mode */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetColor(GUI_BLACK);
    GUI_SetTextMode(GUI_TM_NORMAL);

    /* Clear the display */
    GUI_Clear();

    /* Display page title */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("2 OF 6: BOLD FONTS", 132, 5);

    /* Font13B_1*/
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_DispStringAt("GUI_Font13B_1", 5, 25);

    /* Font13HB_1*/
    GUI_SetFont(GUI_FONT_13HB_1);
    GUI_DispStringAt("GUI_Font13HB_1", 5, 40);

    /* Font16B_1*/
    GUI_SetFont(GUI_FONT_16B_1);
    GUI_DispStringAt("GUI_Font16B_1", 5, 55);

    /* FontComic18B_1*/
    GUI_SetFont(GUI_FONT_COMIC18B_1);
    GUI_DispStringAt("GUI_FontComic18B_1", 5, 73);

    /* Font20B_1*/
    GUI_SetFont(GUI_FONT_20B_1);
    GUI_DispStringAt("GUI_Font20B_1", 5, 93);

    /* Font24B_1*/
    GUI_SetFont(GUI_FONT_24B_1);
    GUI_DispStringAt("GUI_Font24B_1", 5, 115);

    /* Font32B_1*/
    GUI_SetFont(GUI_FONT_32B_1);
    GUI_DispStringAt("GUI_Font32B_1", 5, 141);
}


/*******************************************************************************
* Function Name: void ShowTextModes(void)
********************************************************************************
*
* Summary: This function displays the following
*            1. Left, Center and Right aligned text
*            2. Underline, overline and strikethrough style text
*            3. Normal, reverse, transparent and XOR text modes
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowTextModes(void)
{
    /* Set font size, foreground and background colors */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_SetTextStyle(GUI_TS_NORMAL);

    /* Clear the screen */
    GUI_Clear();

    /* Display page title */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("3 OF 6: TEXT ALIGNMENTS, STYLES AND MODES", 132, 5);

    /* Display left aligned text */
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt("TEXT ALIGNMENT LEFT", 0, 30);

    /* Display center aligned text */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("TEXT ALIGNMENT CENTER", 132, 45);

    /* Display right aligned text */
    GUI_SetTextAlign(GUI_TA_RIGHT);
    GUI_DispStringAt("TEXT ALIGNMENT RIGHT", 263, 60);

    /* Display underlined text */
    GUI_SetTextStyle(GUI_TS_UNDERLINE);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt("TEXT STYLE UNDERLINE", 0, 75);

    /* Display overlined text */
    GUI_SetTextStyle(GUI_TS_OVERLINE);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt("TEXT STYLE OVERLINE", 0, 90);

    /* Display strikethrough text */
    GUI_SetTextStyle(GUI_TS_STRIKETHRU);
    GUI_SetTextAlign(GUI_TA_LEFT);
    GUI_DispStringAt("TEXT STYLE STRIKETHROUGH", 0, 105);

    /* Create a rectangle filled with Black color */
    GUI_SetColor(GUI_BLACK);
    GUI_FillRect(0, 120, 263, 175);

    /* Draw two diagonal lines */
    GUI_SetColor(GUI_WHITE);
    GUI_SetPenSize(3);
    GUI_DrawLine(0, 120, 263, 175);
    GUI_DrawLine(0, 175, 263, 120);

    /* Set text color to white with black background */
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);

    /* Set text style to normal */
    GUI_SetTextStyle(GUI_TS_NORMAL);

    /* Display text in normal mode. This will print black text in
        a white box */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_DispStringAt("TEXT MODE NORMAL", 132, 135);

    /* Display text in reverse mode. This will print black text n
        a white box */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_SetTextMode(GUI_TM_REV);
    GUI_DispStringAt("TEXT MODE REVERSE", 132, 150);
}


/*******************************************************************************
* Function Name: void ShowTextWrapAndOrientation(void)
********************************************************************************
*
* Summary: This function shows the text orientation and text wrap functions
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ShowTextWrapAndOrientation(void)
{
    GUI_RECT leftRect = {4, 19, 24, 166};
    GUI_RECT rightRect = {238, 19, 258, 166};
    GUI_RECT middleRect = {29, 19, 233, 166};
    GUI_RECT middleRectMargins = {31, 20, 232, 165};

    const char leftText[] = "ROTATED TEXT CCW";
    const char rightText[] = "ROTATED TEXT CW";

    const char middleText[] = "This project demonstrates displaying 2D graphics in an EInk display using Segger EmWin Graphics Library. \n\nThis page shows the text wrap and text rotation features. In the left rectangle, the text is rotated counter clockwise and in the right rectangle, the text is rotated clockwise.";


    /* Set font size, foreground and background colors */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_SetTextStyle(GUI_TS_NORMAL);

    /* Clear the screen */
    GUI_Clear();

    /* Display page title */
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("4 OF 6: TEXT WRAP AND ROTATION", 132, 5);

    /* Draw rectangles to hold text */
    GUI_DrawRectEx(&leftRect);
    GUI_DrawRectEx(&rightRect);
    GUI_DrawRectEx(&middleRect);

    /* Display string in left rectangle rotated counter clockwise */
    GUI_DispStringInRectEx(leftText, &leftRect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen(leftText), GUI_ROTATE_CCW);

    /* Display string in right rectangle rotated clockwise */
    GUI_DispStringInRectEx(rightText, &rightRect, GUI_TA_HCENTER | GUI_TA_VCENTER, strlen(rightText), GUI_ROTATE_CW);

    /* Display string in middle rectangle with word wrap */
    GUI_DispStringInRectWrap(middleText, &middleRectMargins, GUI_TA_LEFT, GUI_WRAPMODE_WORD);

}


/*******************************************************************************
* Function Name: void Show2DGraphics1(void)
********************************************************************************
*
* Summary: This function displays the following 2D graphics
*            1. Horizontal lines with various pen widths
*            2. Vertical lines with various pen widths
*            3. Arcs
*            4. Filled rounded rectangle
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Show2DGraphics1(void)
{
    /* Set font size, foreground and background colors */
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_SetTextStyle(GUI_TS_NORMAL);

    /* Clear the screen */
    GUI_Clear();

    /* Display page title */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("5 OF 6: 2D GRAPHICS - 1", 136, 5);

    /* Display labels */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("H-LINES", 68, 85);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("V-LINES", 204, 85);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("ARCS", 68, 163);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("ROUNDED RECT", 204, 163);

    /* Horizontal lines */
    GUI_SetPenSize(1);
    GUI_DrawLine(10, 25, 125, 25);
    GUI_SetPenSize(2);
    GUI_DrawLine(10, 35, 125, 35);
    GUI_SetPenSize(3);
    GUI_DrawLine(10, 45, 125, 45);
    GUI_SetPenSize(4);
    GUI_DrawLine(10, 55, 125, 55);
    GUI_SetPenSize(5);
    GUI_DrawLine(10, 65, 125, 65);
    GUI_SetPenSize(6);
    GUI_DrawLine(10, 75, 125, 75);

    /* Vertical lines */
    GUI_SetPenSize(1);
    GUI_DrawLine(168, 20, 168, 80);
    GUI_SetPenSize(2);
    GUI_DrawLine(180, 20, 180, 80);
    GUI_SetPenSize(3);
    GUI_DrawLine(192, 20, 192, 80);
    GUI_SetPenSize(4);
    GUI_DrawLine(204, 20, 204, 80);
    GUI_SetPenSize(5);
    GUI_DrawLine(216, 20, 216, 80);
    GUI_SetPenSize(6);
    GUI_DrawLine(228, 20, 228, 80);
    GUI_SetPenSize(7);
    GUI_DrawLine(240, 20, 240, 80);

    /* Arcs */
    GUI_SetPenSize(2);
    GUI_DrawArc(68, 160, 10, 10, 0, 180);
    GUI_DrawArc(68, 160, 20, 20, 0, 180);
    GUI_DrawArc(68, 160, 30, 30, 0, 180);
    GUI_DrawArc(68, 160, 40, 40, 0, 180);
    GUI_DrawArc(68, 160, 50, 50, 0, 180);

    /* Rounded rectangle */
    GUI_FillRoundedRect(146, 108, 262, 160, 5);
}


/*******************************************************************************
* Function Name: void Show2DGraphics2(void)
********************************************************************************
*
* Summary: This function displays the following 2D graphics
*            1. Concentric circles
*            2. Concentric ellipses
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Show2DGraphics2(void)
{
    /* Set font size, foreground and background colors */
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_SetTextMode(GUI_TM_NORMAL);
    GUI_SetTextStyle(GUI_TS_NORMAL);

    /* Clear the screen */
    GUI_Clear();

    /* Display page title */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("6 OF 6: 2D GRAPHICS - 2", 132, 5);

    /* Display labels */
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("CIRCLE", 68, 85);
    GUI_SetTextAlign(GUI_TA_HCENTER);
    GUI_DispStringAt("ELLIPSE", 204, 85);

    /* Concentric Circles */
    GUI_DrawCircle(68, 51, 30);
    GUI_DrawCircle(68, 51, 25);
    GUI_DrawCircle(68, 51, 20);
    GUI_DrawCircle(68, 51, 15);
    GUI_DrawCircle(68, 51, 10);

    /* Concentric Ellipses */
    GUI_DrawEllipse(204, 51, 50, 30);
    GUI_DrawEllipse(204, 51, 40, 25);
    GUI_DrawEllipse(204, 51, 30, 20);
    GUI_DrawEllipse(204, 51, 20, 15);
}


/*******************************************************************************
* Function Name: void ClearScreen(void)
********************************************************************************
*
* Summary: This function clears the screen
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ClearScreen(void)
{
    GUI_SetColor(GUI_BLACK);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();
}


/*******************************************************************************
* Function Name: bool IsBtnClicked
********************************************************************************
*
* Summary: This function implements SW2 button click check.
*
* Parameters:
*  None
*
* Return:
*  Status of the SW2 button:
*  true when button was pressed and then released and
*  false in other cases
*
*******************************************************************************/
bool IsBtnClicked(void)
{
    int currBtnState;
    static int prevBtnState  = BTN_RELEASED;

    bool result = false;

    currBtnState = sw2;

    if((prevBtnState == BTN_RELEASED) && (currBtnState == BTN_PRESSED))
    {
        result = true;
    }

    prevBtnState = currBtnState;

    ThisThread::sleep_for(chrono::milliseconds(5));

    return result;
}

int main()
{
    /* Variable to store return value */
    cy_rslt_t result;
    
    /* Variable to point to current page number */
    uint8_t pageNumber = 0;

    /* Array of demo pages functions */
    void (*demoPageArray[])(void) = {
                    ShowFontSizesNormal,
                    ShowFontSizesBold,
                    ShowTextModes,
                    ShowTextWrapAndOrientation,
                    Show2DGraphics1,
                    Show2DGraphics2
    };
    
    /* Number of demo pages */
    uint8_t num_of_demo_pages = (sizeof(demoPageArray)/sizeof(demoPageArray[0]));
    
    /* Turn off LED */
    led = LED_OFF;

    /* Initialize SPI and EINK display */
    result = cyhal_spi_init(&spi, CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MOSI,
            CY8CKIT_028_EPD_PIN_DISPLAY_SPI_MISO,
            CY8CKIT_028_EPD_PIN_DISPLAY_SPI_SCLK, NC, NULL, 8,
            CYHAL_SPI_MODE_00_MSB, false);
     if (CY_RSLT_SUCCESS == result)
     {
        result = cyhal_spi_set_frequency(&spi, SPI_BAUD_RATE_HZ);
        if(CY_RSLT_SUCCESS != result)
        {
            led = LED_ON;
            printf("Unable to set SPI frequency, Error: %ld\r\n",(long)result);
            while(1);
        }
     }

    result = mtb_e2271cs021_init(&pins, &spi);
    if (CY_RSLT_SUCCESS != result)
    {
        led = LED_ON;
        printf("Error in initializing mtb_e2271cs021, Error: %ld", (long)result);
        while(1);
    }

    /* Set ambient temperature, in degree C, in order to perform temperature
     * compensation of E-INK parameters */
    mtb_e2271cs021_set_temp_factor(AMBIENT_TEMPERATURE_C);

    /* Get the pointer to EmWin's display buffer */
    current_frame = (uint8_t*)LCD_GetDisplayBuffer();
    
    /* Initialize EmWin driver */
    GUI_Init();
    
    /* Show the startup screen */
    ShowStartupScreen();
    
    /* Update the display */
    mtb_e2271cs021_show_frame(previous_frame, current_frame,
                          MTB_E2271CS021_FULL_4STAGE, true);
    
    /* Display startup screen for 3 seconds */
    ThisThread::sleep_for(3s);

    /* Show the instructions screen */
    ShowInstructionsScreen();
    
    /* Update the display */
    mtb_e2271cs021_show_frame(previous_frame, current_frame,
                              MTB_E2271CS021_FULL_4STAGE, true);
                              
    for(;;)
    {
        if(IsBtnClicked())
        {
            led = LED_ON;
            
            /* Using pageNumber as index, update the display with a demo screen
            Following are the functions that are called in sequence
                ShowFontSizesNormal()
                ShowFontSizesBold()
                ShowTextModes()
                ShowTextWrapAndOrientation()
                Show2DGraphics1()
                Show2DGraphics2()
            */
            (*demoPageArray[pageNumber])();
            
             /* Update the display */
             mtb_e2271cs021_show_frame(previous_frame, current_frame,
                              MTB_E2271CS021_FULL_4STAGE, true);
            
            /* Cycle through page numbers */
            pageNumber = (pageNumber+1) % num_of_demo_pages;
            
            led = LED_OFF;
        }
    }
}