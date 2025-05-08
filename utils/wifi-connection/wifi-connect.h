//#include <stdio.h>
//#include "pico/stdlib.h"
//#include "pico/cyw43_arch.h"

// Defina as credenciais diretamente (não use getenv)
//#define WIFI_SSID "MAMBEE"
//#define WIFI_PASSWORD "1fp1mamb33"

//void init_wifi();



//#include <stdio.h>
//#include "pico/cyw43_arch.h"
//#include "pico/stdlib.h"



//void init_wifi(void);

// <- Adicione esta linha:
//extern bool wifi_conectado;

//#endif
#ifndef WIFI_CONNECT_H
#define WIFI_CONNECT_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
// coloque o nome e a senha da sua internet
#define WIFI_SSID "" 
#define WIFI_PASSWORD ""

void init_wifi(void);

extern bool wifi_conectado;

#endif
