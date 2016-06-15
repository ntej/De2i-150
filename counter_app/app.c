//
//  counter.c
//  
//
//  Created by K.NavatejaReddy on 5/26/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "PCIE.h"

#define DEMO_PCIE_USER_BAR			PCIE_BAR0
#define DEMO_PCIE_COUNTER_ADDR	    0x4000

int main(void)
{
    void *lib_handle;
    PCIE_HANDLE hPCIE;
    BOOL bQuit = FALSE;
    int select0 = 0;
    int temp_sel;
    
    printf("== Terasic: PCIe counter Demo Program ==\r\n");
    
    lib_handle = PCIE_Load();
    if (!lib_handle)
    {
        printf("PCIE_Load failed!\r\n");
        return 0;
    }
    hPCIE = PCIE_Open(0,0,0);
    if (!hPCIE)
    {
        printf("PCIE_Open failed\r\n");
    }
    else
    {
        while(!bQuit)
        {
            
            printf("select your option: 0-counter read, AnyOtherDecimalNumber-exit \r\n");
            scanf("%d",temp_sel);
            if(temp_sel==select0)
            {
               PCIE_Read_counter(hPCIE);
            }
            else
            {
               bQuit = TRUE;
               printf("Bye!\r\n");
            }
            
            
            
        }//while
        PCIE_Close(hPCIE);
    }//else
    
    PCIE_Unload(lib_handle);
    return 0;
    
}//main


BOOL PCIE_Read_counter(PCIE_HANDLE hPCIe)
{
    BOOL bpass = TRUE;
    DWORD Status;
    bpass = PCIE_Read32(hPCIe,DEMO_PCIE_USER_BAR,DEMO_PCIE_COUNTER_ADDR,&Status);
    if (bpass)
        printf("Counter Value:=%xh\r\n", Status);
    else
        printf("Failed to read counter value\r\n");
    
    return bpass;
}

