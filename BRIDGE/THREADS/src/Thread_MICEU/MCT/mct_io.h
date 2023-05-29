#ifndef __MCT_IO_H__
#define __MCT_IO_H__

#include <mg_int.h>
#include <sbor_int.h>

#define MAX_PROGRAMAS 3     /* almacena hasta tres programas */

#define ECO_MINIMO 5    /* 5 escalones de discretizacion */ 


struct PROP {
                byte comandos[MAX_PROGRAMAS];
                word linea;
                byte ganancia;
    dword tiempo;
                struct P_SO dir;
                byte talladedatos;    /* 1 un byte */
                byte long_datos;
            };


extern struct PROP Prop_paso[N_PASOS];     /* alacena los datos de la captura */
extern float temperatura;              /* Mantiene la tempetatura */
extern word prog_act;                  /* programa actual */
extern byte MCT_st;                    /* resultado del ultimo comando */
extern byte ret_status;                /* true si devuelve el estado por
                                          cada comando */
extern idata struct t_mess_in mensaje_act; /* mensaje en curso */


extern word ROOTS[200];                 /* mantiene los cuadrados desde 0 hasta 199 */
extern struct P_SO RAICES;              /* direccion del banco donde est n los modulos */

extern unsigned int MCT_n_muestras;     /* numero de muestras */


typedef SAMPLE_TYPE T_CANAL[N_CANTSAMPLES];
typedef SAMPLE_TYPE T_ECO[N_CANTSAMPLES];
typedef T_CANAL T_CANALES[2];

struct ESP_TEMP {
                  T_CANALES A_D;
                  T_ECO tr_senal;
                };



/* Funciones del modulo de inicializaci¢n de MCT */

void Inicializar_programas(void);         /* borrar el contenido de los programas */
void Asignar_buffers(void);               /* asigna los buffers para la captura */

/* Funciones del modulo de configuraci¢n de MCT */

void Configurar(void);
byte Programa_correcto(byte num);
byte Programa_vacio(byte num_prog);
void Estable_n_muestras(byte n_muestras);
void Borrar_prog(void);
void Declare_prog(void);

/* Funciones del modulo ejecutivo de MCT */

void Programar_orden(void);
void Ejecutar_programa(void);
void Ejecutarex_programa(void);
void ExecuteCommand(byte count,byte num_prog);

/* Funciones del modulo de gestion de peticiones de MCT */
void Tratar_peticion(void);

/* Funciones del modulo de algoritmos */

void Conf_Tabla_ROOTS(void);
void Conf_vel_sonido(float temperatura);  /* configura la velocidad del ultrasonidos para una
                                             temperatura data */

void Realizar_captura(byte count,byte num_prog);

byte Raiz(data word N);
void Calcula_modulovector(byte * Buffer,struct P_SO dir);
word Trans_tiempo_us_distancia(word usvuelo);
word Calculo_distancia(void);
void Devuelve_DISTANCIA(byte count);
void Devuelve_ECO(byte count);
void Devuelve_CANAL(byte count,byte canal);
void Devuelve_TEST(byte count);


#endif
