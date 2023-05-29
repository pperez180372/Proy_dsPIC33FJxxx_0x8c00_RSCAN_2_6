#ifndef _CAN_TYPES_H_
#define _CAN_TYPES_H_

//#include "GenericTypeDefs.h"
//#include <p32xxxx.h>

#define _CAN1



#ifdef _CAN1
    #define CAN1_BASE_ADDRESS			0x0400
#endif

#ifdef _CAN2
    #define CAN2_BASE_ADDRESS 			сссс
#endif

#ifdef _CAN1
    #ifdef _CAN2
          #define CAN_NUM_OF_MODULES 	2
    #else
          #define CAN_NUM_OF_MODULES 	1
    #endif
#endif

#define CAN_NUM_OF_FILTERS 				16
#define CAN_NUM_OF_FILTER_MASKS 		3
#define CAN_NUM_OF_FILTER_CONTROL_REGS 	8
#define CAN_NUM_OF_CHANNELS				2


/*******************************************************************
  This data structure encapsulates the CAN Filter Control registers.
  *******************************************************************/
/*typedef struct _CAN_FILTER_CONTROL_REGS
{
	union
	{
		volatile UINT32 CxFLTCON;
		volatile BYTE CxFLTCONbyte[4];
	};
	volatile UINT32 CxFLTCONCLR  ;
	volatile UINT32 CxFLTCONSET  ;
	volatile UINT32 CxFLTCONINV  ;
	

}CAN_FILTER_CONTROL_REGS;
*/

/*******************************************************************
  This enumerates the total number of CAN filter control registers
  contained in each CAN module.
  *******************************************************************/
/*
typedef enum _CAN_FILTER_CONTROL
{
	CAN_FILTER_CONTROL0,
	CAN_FILTER_CONTROL1,
	CAN_FILTER_CONTROL2,
	CAN_FILTER_CONTROL3,
	CAN_FILTER_CONTROL4,
	CAN_FILTER_CONTROL5,
	CAN_FILTER_CONTROL6,
	CAN_FILTER_CONTROL7
}CAN_FILTER_CONTROL;

typedef struct _CAN_FLTCON_BYTES
{
	CAN_FILTER_CONTROL fltcon;
	UINT byteIndex;
	UINT fltEnMask;
}CAN_FLTCON_BYTES;
*/
/*******************************************************************
  This data structure encapsulates the fifo control registers.
  *******************************************************************/
/*typedef struct {
    unsigned RXNEMPTYIF:1;
    unsigned RXHALFIF:1;
    unsigned RXFULLIF:1;
    unsigned RXOVFLIF:1;
    unsigned :4;
    unsigned TXEMPTYIF:1;
    unsigned TXHALFIF:1;
    unsigned TXNFULLIF:1;
    unsigned :5;
    unsigned RXNEMPTYIE:1;
    unsigned RXHALFIE:1;
    unsigned RXFULLIE:1;
    unsigned RXOVFLIE:1;
    unsigned :4;
    unsigned TXEMPTYIE:1;
    unsigned TXHALFIE:1;
    unsigned TXNFULLIE:1;
} CxFIFOINT_t;

typedef struct {
    unsigned TXPRI:2;
    unsigned RTREN:1;
    unsigned TXREQ:1;
    unsigned TXERR:1;
    unsigned TXLARB:1;
    unsigned TXABAT:1;
    unsigned TXEN:1;
    unsigned :4;
    unsigned DONLY:1;
    unsigned UINC:1;
    unsigned FRESET:1;
    unsigned :1;
    unsigned FSIZE:5;
} CxFIFOCON_t;

typedef struct {
    unsigned DNCNT:5;
    unsigned :6;
    unsigned CANBUSY:1;
    unsigned :1;
    unsigned SIDL:1;
    unsigned FRZ:1;
    unsigned ON:1;
    unsigned :4;
    unsigned CANCAP:1;
    unsigned OPMOD:3;
    unsigned REQOP:3;
    unsigned ABAT:1;
} CxCON_t;


typedef struct {
    unsigned CANTSPRE:16;
    unsigned CANTS:16;
}CxTMR_t;

typedef struct {
    unsigned ICODE:7;
    unsigned :1;
    unsigned FILHIT:5;
} CxVEC_t;

typedef struct {
    unsigned EID:18;
    unsigned :1;
    unsigned EXID:1;
    unsigned :1;
    unsigned SID:11;
} CxRXF_t;

typedef struct {
    unsigned EID:18;
    unsigned :1;
    unsigned MIDE:1;
    unsigned :1;
    unsigned SID:11;
} CxRXM_t;

typedef struct _CAN_FIFO_REGS
{
	union{
		volatile UINT32 CxFIFOCON;
		volatile CxFIFOCON_t CxFIFOCONbits;
	};
	volatile UINT32 CxFIFOCONCLR ;
	volatile UINT32 CxFIFOCONSET ;
	volatile UINT32 CxFIFOCONINV ;
	union
	{
		volatile UINT32 CxFIFOINT    ;
		volatile CxFIFOINT_t CxFIFOINTbits;
	};
	volatile UINT32 CxFIFOINTCLR ;
	volatile UINT32 CxFIFOINTSET ;
	volatile UINT32 CxFIFOINTINV ;
	volatile UINT32 CxFIFOUA     ;
	volatile UINT32 CxFIFOUACLR  ;
	volatile UINT32 CxFIFOUASET  ;
	volatile UINT32 CxFIFOUAINV  ;
	volatile UINT32 CxFIFOCI     ;
	volatile UINT32 CxFIFOCICLR  ;
	volatile UINT32 CxFIFOCISET  ;
	volatile UINT32 CxFIFOCIINV  ;
}CAN_FIFO_REGS;
*/
/*******************************************************************
  This data structure encapsulates the filter specification registers.
  *******************************************************************/
/*
typedef struct _CAN_FILTER_REGS
{
	union
	{
		volatile UINT32 CxRXF;
		volatile CxRXF_t CxRXFbits;
	};
	volatile UINT32 CxRXFCLR     ;
	volatile UINT32 CxRXFSET     ;
	volatile UINT32 CxRXFINV     ;
	

}CAN_FILTER_REGS;
*/
/*******************************************************************
  This data structure encapsulates the filter mask specification
  registers.
  *******************************************************************/
/*
typedef struct _CAN_FILTER_MASK_REGS
{
	union
	{
		volatile UINT32 CxRXM;
		volatile CxRXM_t CxRXMbits;
	};
	volatile UINT32 CxRXMCLR     ;
	volatile UINT32 CxRXMSET     ;
	volatile UINT32 CxRXMINV     ;

}CAN_FILTER_MASK_REGS;
*/
/*******************************************************************
  This data structure encapsulates all the CAN module registers.
  *******************************************************************/


#define T_SFR unsigned int

typedef struct {
  
    unsigned PRSEG:3;
    unsigned SEG1PH:3;
    unsigned SAM:1;
    unsigned SEG2PHTS:1;
    unsigned SEG2PH:3;
    unsigned :3;
    unsigned WAKFIL:1;
 	unsigned :1;
} CFG2_t;


typedef struct {
    unsigned BRP:6;
    unsigned SJW:2;
    unsigned :8;
} CFG1_t;

typedef struct {
    unsigned DNCNT:5;
 	unsigned :11;
} CTRL2_t;


typedef struct {

	unsigned WIN:1;
	unsigned :2;
	unsigned CANCAP:1;
	unsigned :1;
	unsigned OPMODE:3;
	unsigned REQOP:3;
	unsigned CANCKS:1;
    unsigned ABAT:1;
    unsigned CSIDL:1;
    unsigned :2;
} CTRL1_t;


typedef union 
	{
		unsigned long int DWORD;
		struct {
				unsigned EID_17_16:2;
				unsigned :1;
				unsigned MIME:1;
				unsigned :1;
				unsigned SID:11;
				unsigned EID_00_15:16;
			   }MASKbits;
	} T_MASK;


typedef union 
	{
		unsigned long int DWORD;
		struct {
				unsigned EID_17_16:2;
				unsigned :1;
				unsigned EXIDE:1;
				unsigned :1;
				unsigned SID:11;
				unsigned EID_00_15:16;
			   }IDbits;
	} T_ID;

typedef struct _CAN_DSPIC_33F_RX_TX_MESSAGE
{
	unsigned IDE:1;
	unsigned SRR:1;
	unsigned SID:11;
	unsigned :3;

	unsigned EID_06_17:12;
	unsigned :4;

	unsigned DLC:4;
	unsigned RB0:1;
	unsigned :3;
	unsigned RB1:1;
	unsigned RTR:1;
	unsigned EID_00_05:6;
	
	unsigned char DATA [8];

	unsigned :8;
	unsigned FILHIT:5;
	unsigned :3;

}
CAN_DSPIC_33F_RX_TX_MESSAGE;

typedef struct _CAN_DSPIC_33F_FIFO
{
	unsigned nextbusy:6;
	unsigned :2;
	unsigned nextfree:6;
	unsigned :2;

}
CAN_DSPIC_33F_FIFO;

typedef struct _CAN_DSPIC_33F_TX_BUFFER_CONTROL_SEG
{
	unsigned char TXPRI:2;
	unsigned char RTREN:1;
	unsigned char TXREQ:1;
	unsigned char TXERR:1;
	unsigned char TXLARB:1;
	unsigned char TXABT:1;
	unsigned char TXEN:1;
}
CAN_DSPIC_33F_TX_BUFFER_CONTROL_SEG;


typedef struct _CAN_DSPIC_33F_REGISTERS
{
    
	struct
	{
		CTRL1_t CTRL1;
		CTRL2_t CTRL2;
		T_SFR VEC;
		T_SFR FCTRL;
		CAN_DSPIC_33F_FIFO FIFO;
		T_SFR INTF;
		T_SFR INTE;
		T_SFR EC;
		CFG1_t CFG1;
		CFG2_t CFG2;
		T_SFR FEN1;
		T_SFR PAD1[1];
		T_SFR FMSKSEL1;
		T_SFR FMSKSEL2;	 
		T_SFR PAD2[2];
		}CONF;
	union
	{
		struct {
				T_SFR RXFUL1;	
				T_SFR RXFUL2;
				T_SFR PAD1[2];
				T_SFR RXOVF1;
				T_SFR RXOVF2;
				T_SFR PAD[2];
				CAN_DSPIC_33F_TX_BUFFER_CONTROL_SEG TRmnCON[8] ;	
				T_SFR PAD_1[4];
				T_SFR RXD;
				T_SFR TXD;
			  }W_0;

		struct {
				T_SFR BUFPNT1;
				T_SFR BUFPNT2;
				T_SFR BUFPNT3;
				T_SFR BUFPNT4;
//PASCU MIERCOLES 7 				T_SFR PAD_2[4];

				T_SFR PAD_2[4];
				T_MASK RXM[3];
				T_SFR PAD_3[2];
				T_ID   RXF[16];
	} W_1;
	} WIN; 
	
} CAN_DSPIC_33F_REGISTERS;




extern const CAN_DSPIC_33F_REGISTERS * canModules[CAN_NUM_OF_MODULES];

//extern const CAN_FLTCON_BYTES canFilterControlMap[CAN_NUM_OF_FILTERS]; 



#define CxFIFOCON_TXPRI_POSITION               0x00000000
#define CxFIFOCON_TXPRI_MASK                   0x00000003
#define CxFIFOCON_TXPRI_LENGTH                 0x00000002

#define CxFIFOCON_RTREN_POSITION               0x00000002
#define CxFIFOCON_RTREN_MASK                   0x00000004
#define CxFIFOCON_RTREN_LENGTH                 0x00000001

#define CxFIFOCON_TXREQ_POSITION               0x00000003
#define CxFIFOCON_TXREQ_MASK                   0x00000008
#define CxFIFOCON_TXREQ_LENGTH                 0x00000001

#define CxFIFOCON_TXERR_POSITION               0x00000004
#define CxFIFOCON_TXERR_MASK                   0x00000010
#define CxFIFOCON_TXERR_LENGTH                 0x00000001

#define CxFIFOCON_TXLARB_POSITION              0x00000005
#define CxFIFOCON_TXLARB_MASK                  0x00000020
#define CxFIFOCON_TXLARB_LENGTH                0x00000001

#define CxFIFOCON_TXABAT_POSITION              0x00000006
#define CxFIFOCON_TXABAT_MASK                  0x00000040
#define CxFIFOCON_TXABAT_LENGTH                0x00000001

#define CxFIFOCON_TXEN_POSITION                0x00000007
#define CxFIFOCON_TXEN_MASK                    0x00000080
#define CxFIFOCON_TXEN_LENGTH                  0x00000001

#define CxFIFOCON_DONLY_POSITION               0x0000000C
#define CxFIFOCON_DONLY_MASK                   0x00001000
#define CxFIFOCON_DONLY_LENGTH                 0x00000001

#define CxFIFOCON_UINC_POSITION                0x0000000D
#define CxFIFOCON_UINC_MASK                    0x00002000
#define CxFIFOCON_UINC_LENGTH                  0x00000001

#define CxFIFOCON_FRESET_POSITION              0x0000000E
#define CxFIFOCON_FRESET_MASK                  0x00004000
#define CxFIFOCON_FRESET_LENGTH                0x00000001

#define CxFIFOCON_FSIZE_POSITION               0x00000010
#define CxFIFOCON_FSIZE_MASK                   0x001F0000
#define CxFIFOCON_FSIZE_LENGTH                 0x00000005

#define CxCON_DNCNT_POSITION                    0x00000000
#define CxCON_DNCNT_MASK                        0x0000001F
#define CxCON_DNCNT_LENGTH                      0x00000005

#define CxCON_CANBUSY_POSITION                  0x0000000B
#define CxCON_CANBUSY_MASK                      0x00000800
#define CxCON_CANBUSY_LENGTH                    0x00000001

#define CxCON_SIDL_POSITION                     0x0000000D
#define CxCON_SIDL_MASK                         0x00002000
#define CxCON_SIDL_LENGTH                       0x00000001

#define CxCON_FRZ_POSITION                      0x0000000E
#define CxCON_FRZ_MASK                          0x00004000
#define CxCON_FRZ_LENGTH                        0x00000001

#define CxCON_ON_POSITION                       0x0000000F
#define CxCON_ON_MASK                           0x00008000
#define CxCON_ON_LENGTH                         0x00000001

#define CxCON_CANCAP_POSITION                   0x00000014
#define CxCON_CANCAP_MASK                       0x00100000
#define CxCON_CANCAP_LENGTH                     0x00000001

#define CxCON_OPMOD_POSITION                    0x00000015
#define CxCON_OPMOD_MASK                        0x00E00000
#define CxCON_OPMOD_LENGTH                      0x00000003

#define CxCON_REQOP_POSITION                    0x00000018
#define CxCON_REQOP_MASK                        0x07000000
#define CxCON_REQOP_LENGTH                      0x00000003

#define CxCON_ABAT_POSITION                     0x0000001B
#define CxCON_ABAT_MASK                         0x08000000
#define CxCON_ABAT_LENGTH                       0x00000001

#define CxCFG_BRP_POSITION                      0x00000000
#define CxCFG_BRP_MASK                          0x0000003F
#define CxCFG_BRP_LENGTH                        0x00000006

#define CxCFG_SJW_POSITION                      0x00000006
#define CxCFG_SJW_MASK                          0x000000C0
#define CxCFG_SJW_LENGTH                        0x00000002

#define CxCFG_PRSEG_POSITION                    0x00000008
#define CxCFG_PRSEG_MASK                        0x00000700
#define CxCFG_PRSEG_LENGTH                      0x00000003

#define CxCFG_SEG1PH_POSITION                   0x0000000B
#define CxCFG_SEG1PH_MASK                       0x00003800
#define CxCFG_SEG1PH_LENGTH                     0x00000003

#define CxCFG_SAM_POSITION                      0x0000000E
#define CxCFG_SAM_MASK                          0x00004000
#define CxCFG_SAM_LENGTH                        0x00000001

#define CxCFG_SEG2PHTS_POSITION                 0x0000000F
#define CxCFG_SEG2PHTS_MASK                     0x00008000
#define CxCFG_SEG2PHTS_LENGTH                   0x00000001

#define CxCFG_SEG2PH_POSITION                   0x00000010
#define CxCFG_SEG2PH_MASK                       0x00070000
#define CxCFG_SEG2PH_LENGTH                     0x00000003

#define CxCFG_WAKFIL_POSITION                   0x00000016
#define CxCFG_WAKFIL_MASK                       0x00400000
#define CxCFG_WAKFIL_LENGTH                     0x00000001

#define CxRXF_EID_POSITION                     0x00000000
#define CxRXF_EID_MASK                         0x0003FFFF
#define CxRXF_EID_LENGTH                       0x00000012

#define CxRXF_EXID_POSITION                    0x00000013
#define CxRXF_EXID_MASK                        0x00080000
#define CxRXF_EXID_LENGTH                      0x00000001

#define CxRXF_SID_POSITION                     0x00000015
#define CxRXF_SID_MASK                         0xFFE00000
#define CxRXF_SID_LENGTH                       0x0000000B

#define CxRXM_EID_POSITION                     0x00000000
#define CxRXM_EID_MASK                         0x0003FFFF
#define CxRXM_EID_LENGTH                       0x00000012

#define CxRXM_MIDE_POSITION                    0x00000013
#define CxRXM_MIDE_MASK                        0x00080000
#define CxRXM_MIDE_LENGTH                      0x00000001

#define CxRXM_SID_POSITION                     0x00000015
#define CxRXM_SID_MASK                         0xFFE00000
#define CxRXM_SID_LENGTH                       0x0000000B
#endif

