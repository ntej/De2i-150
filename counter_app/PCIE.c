
#include <stdio.h>
#include <dlfcn.h> // dlopen/dlclsoe
#include "PCIE.h"


LPPCIE_Open 		PCIE_Open;
LPPCIE_Close 		PCIE_Close;
LPPCIE_Read32 		PCIE_Read32;
LPPCIE_Write32 		PCIE_Write32;
LPPCIE_DmaWrite		PCIE_DmaWrite;
LPPCIE_DmaRead		PCIE_DmaRead;
LPPCIE_DmaFifoWrite	PCIE_DmaFifoWrite;
LPPCIE_DmaFifoRead	PCIE_DmaFifoRead;


	
void *PCIE_Load(void){

	BOOL bSuccess = TRUE;
	void *lib_handle;

	lib_handle = dlopen("./teraisc_pcie_qsys.so", RTLD_NOW);
	if (!lib_handle){
		printf("%s\r\n", dlerror());
		bSuccess = FALSE;
	}

	if(bSuccess){
		PCIE_Open = dlsym(lib_handle, "PCIE_Open");
		PCIE_Close = dlsym(lib_handle, "PCIE_Close");
		PCIE_Read32 = dlsym(lib_handle, "PCIE_Read32");
		PCIE_Write32 = dlsym(lib_handle, "PCIE_Write32");
		PCIE_DmaWrite = dlsym(lib_handle, "PCIE_DmaWrite");
		PCIE_DmaRead = dlsym(lib_handle, "PCIE_DmaRead");
		PCIE_DmaFifoWrite = dlsym(lib_handle, "PCIE_DmaFifoWrite");
		PCIE_DmaFifoRead = dlsym(lib_handle, "PCIE_DmaFifoRead");
		if (!PCIE_Open || !PCIE_Close ||
		    !PCIE_Read32 || !PCIE_Write32 ||
		    !PCIE_DmaWrite || !PCIE_DmaRead ||
		    !PCIE_DmaFifoWrite || !PCIE_DmaFifoRead
		)
			bSuccess = FALSE;
		
		
		if (!bSuccess){
			dlclose(lib_handle);
			lib_handle = 0;
		}
	}

	return lib_handle;
}

void PCIE_Unload(void *lib_handle){
	dlclose(lib_handle);
}


