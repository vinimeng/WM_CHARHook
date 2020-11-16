// Dll1.cpp : Define as funções exportadas para a DLL.
//

#include "pch.h"
#include "framework.h"
#include "Dll1.h"


// Isto é um exemplo de uma variável exportada
DLL1_API int nDll1=0;

// Isto é um exemplo de uma função exportada.
DLL1_API int fnDll1(void)
{
    return 0;
}

// Este é o construtor de uma classe que foi exportada.
CDll1::CDll1()
{
    return;
}
