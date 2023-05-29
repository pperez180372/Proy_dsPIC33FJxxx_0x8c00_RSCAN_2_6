#ifndef __MESSAGE_ID_H__
#define __MESSAGE_ID_H__

//Comunicaciones

/* compatible con canopen
                               */
#define ID_NODO     0x54    /* los 4 bits menos significativos para variable */

/* mensajes por los que se interesa el modulo */

#define FILTRO_CAN_YAIR_VEL_FILTRO_FIFO  9    /* número de filtro de aceptacion de recepcion, tiene hasta 16 filtros de aceptacion */
#define YAIR_Result_Emergent 		0x207


/* variables comunes */
#define VAR_CAN_MODE		   1    /* byte 0 variable de modo de funcionamiento de CAN */
	 	#define VAR_CAN_MODE_SILENT    1 /* no transmite mensajes */
		#define VAR_CAN_MODE_NORMAL    0 /* SI transmite mensajes */


/////////////////////////////////////////////////////////////
// YAIR_VEL
/////////////////////////////////////////////////////////////



#define CANID_YAIR_VEL_1    ((long int)(ID_NODO33|0x200)) /*RPDO_1 0x200 */
#define CANID_YAIR_VEL     ((long int)(ID_NODO|0x08))
#define CANID_YAIR_VEL_IN  ((long int)(ID_NODO|0x09))

#define BUFFER_CAN_YAIR_VEL_IN 14   /* buffer de recepción */ 
#define BUFFER_CAN_YAIR_VEL_1   3    /* número buffer de transmisión  */
#define BUFFER_CAN_YAIR_VEL     4    /* número buffer de transmisión  */
#define FILTRO_CAN_YAIR_VEL_IN  8    /* número de filtro de aceptacion de recepcion  */

/////////////////////////////////////////////////////////////
// YAIR_SERVOS
/////////////////////////////////////////////////////////////

#define CANID_SERVOS_1    ((long int)(ID_NODO|0x0A))
#define CANID_SERVOS   ((long int)(ID_NODO|0x0B))
#define CANID_SERVOS_IN  ((long int)(ID_NODO|0x0C))

#define BUFFER_CAN_SERVOS_IN 12  /* buffer de recepción */ 
#define BUFFER_CAN_SERVOS_1   5    /* número buffer de transmisión  */
#define BUFFER_CAN_SERVOS     6    /* número buffer de transmisión  */
#define FILTRO_CAN_SERVOS_IN  6   /* número de filtro de aceptacion de recepcion  */


/* variables comunes */
#define VAR_SERVOS_CAN_MODE		   1    /* byte 0 variable de modo de funcionamiento de CAN */
	 	#define VAR_CAN_MODE_SILENT    1 /* no transmite mensajes */
		#define VAR_CAN_MODE_NORMAL    0 /* SI transmite mensajes */
#define VAR_SERVOS_POS1       2
#define VAR_SERVOS_POS2		  3



/////////////////////////////////////////////////////////////
// YAIR_INFRA
/////////////////////////////////////////////////////////////
/*
#define CANID_INFRA_1    ((long int)(ID_NODO|0x05))
#define CANID_INFRA     ((long int)(ID_NODO|0x04))
#define CANID_INFRA_IN  ((long int)(ID_NODO|0x06))
		// 0x346 esta multiplexado
		 

// buffer de recepción 
#define BUFFER_CAN_INFRA_IN 13   
// número buffer de transmisión  
#define BUFFER_CAN_INFRA_1   2
// número buffer de transmisión  
#define BUFFER_CAN_INFRA     1
// número de filtro de aceptacion de recepcion  
#define FILTRO_CAN_INFRA_IN 7 
*/

// BRIDGE 

// en conflicto con INFRA 
#define BRIDGE_BUFFER_CAN_IN 14   /* buffer de recepción */ 
#define BRIDGE_BUFFER_CAN   2    /* número buffer de transmisión  */
#define BRIDGE_FILTRO_CAN_IN 7    /* número de filtro de aceptacion de recepcion  */

// en conflicto con UXHEAD_BRIDGE
#define CANID_UX_HEAD              ((long int)(ID_NODO|0x200)) /*RPDO_1 0x200 */
#define UX_HEAD_BUFFER_CAN_IN 14   
#define UX_HEAD_BUFFER_CAN   6    
#define UX_HEAD_FILTRO_CAN_IN 6   





#endif
