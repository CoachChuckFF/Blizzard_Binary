/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
#include <stdint.h>

extern uint8_t DMX_ADDRESS;
extern uint8_t DMX[513];
extern uint8_t tick;

void InitApp(void);         /* I/O and Peripheral Initialization */



