#define OFFSET_orp 0        //zero drift voltage
#define ArrayLenth_orp  50    //times of collection

extern float orpArray[ArrayLenth_orp];
extern int orpArrayIndex;
extern float ORP,ORP1;
extern float ORP_value;  

extern char Liquid_TX[5];
extern float Liquid_Value;

extern float PH_Value;
extern char TX_PH[5];

double avergearray(float* arr, int number);
void ORP_Value_Conversion(void);
void ORP_Value_get(void);

void Liquid_Value_Conversion(float value);

void PH_Value_Conversion(void);