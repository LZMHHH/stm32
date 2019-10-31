#ifndef __SHOW_H
#define __SHOW_H
#include "sys.h"


/* ×´Ì¬»ú±í */
typedef enum
{
    SHOW_Close,          /*  */
    SHOW_Load,      /*  */
    SHOW_Date,       /* */
}SHOW_Status;



void Show_ZUI(void);
void Para_Update(void);
void Para_Prepare(void);

#endif
