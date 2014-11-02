#include "ESTADO.h"
/*
valida retorna apenas LEI_CondRetOK ou LEI_CondRetInvalido
*/
typedef enum{
    LEI_CondRetOK,
    LEI_CondRetInvalido,
    LEI_CondRetSemOpcao         
} LEI_tpCondRet;
/*
trunca em 50
*/
LEI_tpCondRet LEI_LeString(char* dst, LEI_tpCondRet (*valida) (char*));
LEI_tpCondRet LEI_LeInt(int* dst, LEI_tpCondRet (*valida) (int));
LEI_tpCondRet LEI_LeCmd(EST_tppEstado e);
