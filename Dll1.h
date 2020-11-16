// O bloco ifdef a seguir é a forma padrão de criar macros que tornam a exportação
// de uma DLL mais simples. Todos os arquivos nessa DLL são compilados com DLL1_EXPORTS
// símbolo definido na linha de comando. Esse símbolo não deve ser definido em nenhum projeto
// que usa esta DLL. Desse modo, qualquer projeto cujos arquivos de origem incluem este arquivo veem
// Funções DLL1_API como importadas de uma DLL, enquanto esta DLL vê símbolos
// definidos com esta macro conforme são exportados.
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif

// Esta classe é exportada da DLL
class DLL1_API CDll1 {
public:
	CDll1(void);
	// TODO: adicione seus métodos aqui.
};

extern DLL1_API int nDll1;

DLL1_API int fnDll1(void);
