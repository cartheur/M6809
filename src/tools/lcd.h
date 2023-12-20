char *const LCD_command_write = (char *) 0x60000;
char *const LCD_data_write = (char *)    0x60001;
char *const LCD_command_read = (char *)  0x60002;
char *const LCD_data_read = (char *)     0x60003;

#define BUSY 0x80

int timeout;

void LcdReady(void)
{
   timeout=0;
    while(*LCD_command_read&BUSY && ++timeout<200)
    continue; // wait until busy flag =0
}

void clr_screen(void)
{
    LcdReady();
    *LCD_command_write=0x01;
}


void goto_xy(int x,int y)
{
    LcdReady();
    switch(y)
    {
    case 0: *LCD_command_write=0x80+x; break;
    case 1: *LCD_command_write=0xC0+x; break;
    case 2: *LCD_command_write=0x94+x; break;
    case 3: *LCD_command_write=0xd4+x; break;
    }
}


void InitLcd(void)
{
    LcdReady();
    *LCD_command_write=0x38;
    LcdReady();
    *LCD_command_write=0x0c;
    clr_screen();
    goto_xy(0,0);
}


char *Puts(char *str)
{
    unsigned char i;
    for (i=0; str[i] != '\0'; i++){
    LcdReady();
    *LCD_data_write=str[i];
}

return str;
}

void putch_lcd(char ch)
{
    LcdReady();
    *LCD_data_write=ch;
}