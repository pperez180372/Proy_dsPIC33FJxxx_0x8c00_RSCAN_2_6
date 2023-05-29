#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=BRIDGE/SRC/Thread_BRIDGE.c FreeRTOS/Source/croutine.c FreeRTOS/Source/event_groups.c FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S FreeRTOS/Source/portable/MemMang/heap_3.c SCoCAN/SRC/Thread_ecan.c SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c SCoCAN/SRC/CAN_DSPIC_33F_Stack.c SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c util/util.c UX/Thread_UX_ISC.c serial/serial.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o ${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/event_groups.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o ${OBJECTDIR}/util/util.o ${OBJECTDIR}/UX/Thread_UX_ISC.o ${OBJECTDIR}/serial/serial.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o.d ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d ${OBJECTDIR}/FreeRTOS/Source/event_groups.o.d ${OBJECTDIR}/FreeRTOS/Source/list.o.d ${OBJECTDIR}/FreeRTOS/Source/queue.o.d ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d ${OBJECTDIR}/FreeRTOS/Source/timers.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.d ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o.d ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o.d ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o.d ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o.d ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o.d ${OBJECTDIR}/util/util.o.d ${OBJECTDIR}/UX/Thread_UX_ISC.o.d ${OBJECTDIR}/serial/serial.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o ${OBJECTDIR}/FreeRTOS/Source/croutine.o ${OBJECTDIR}/FreeRTOS/Source/event_groups.o ${OBJECTDIR}/FreeRTOS/Source/list.o ${OBJECTDIR}/FreeRTOS/Source/queue.o ${OBJECTDIR}/FreeRTOS/Source/tasks.o ${OBJECTDIR}/FreeRTOS/Source/timers.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o ${OBJECTDIR}/util/util.o ${OBJECTDIR}/UX/Thread_UX_ISC.o ${OBJECTDIR}/serial/serial.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=BRIDGE/SRC/Thread_BRIDGE.c FreeRTOS/Source/croutine.c FreeRTOS/Source/event_groups.c FreeRTOS/Source/list.c FreeRTOS/Source/queue.c FreeRTOS/Source/tasks.c FreeRTOS/Source/timers.c FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S FreeRTOS/Source/portable/MemMang/heap_3.c SCoCAN/SRC/Thread_ecan.c SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c SCoCAN/SRC/CAN_DSPIC_33F_Stack.c SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c util/util.c UX/Thread_UX_ISC.c serial/serial.c main.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script="p33FJ128MC804_0x8c00_with_FreeRTOS"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o: BRIDGE/SRC/Thread_BRIDGE.c  .generated_files/flags/default/5bb0891a34626e3e995817511da0ad6346bbf4c1 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/BRIDGE/SRC" 
	@${RM} ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o.d 
	@${RM} ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BRIDGE/SRC/Thread_BRIDGE.c  -o ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  .generated_files/flags/default/5a4b1da41ff540dcc7dd868ed871451cf4a4532b .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/croutine.c  -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/event_groups.o: FreeRTOS/Source/event_groups.c  .generated_files/flags/default/cafbe005e73b53ab0138b22950bcaa9afb09037f .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/event_groups.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/event_groups.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/event_groups.c  -o ${OBJECTDIR}/FreeRTOS/Source/event_groups.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/event_groups.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  .generated_files/flags/default/340f67d73c592b8d381b1e9bd594277cb2ec5d1f .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/list.c  -o ${OBJECTDIR}/FreeRTOS/Source/list.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  .generated_files/flags/default/2415c802010db80006f9b5452816e3a1487e6b4a .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/queue.c  -o ${OBJECTDIR}/FreeRTOS/Source/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  .generated_files/flags/default/6033a9760125dbb682b14476d5b9df038a014411 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/tasks.c  -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  .generated_files/flags/default/21b257a2165fe6c74d4e8171a1c7d092b64a2417 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/timers.c  -o ${OBJECTDIR}/FreeRTOS/Source/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o: FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c  .generated_files/flags/default/23dec7fa0597ccfa6ef21aaab6e1862dfc12446e .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o: FreeRTOS/Source/portable/MemMang/heap_3.c  .generated_files/flags/default/81b88e8bbfcabe90adbfe63185d8ad3c5264ee7 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/portable/MemMang/heap_3.c  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o: SCoCAN/SRC/Thread_ecan.c  .generated_files/flags/default/78b120ef52177d0bd6e14fff368abf8a2a4a123c .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/Thread_ecan.c  -o ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o: SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c  .generated_files/flags/default/634409025b917d21f143566e89152d03a512a49b .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o: SCoCAN/SRC/CAN_DSPIC_33F_Stack.c  .generated_files/flags/default/11105ffea80ee579b0a213559fc87d18e657b7e0 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Stack.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o: SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c  .generated_files/flags/default/7cf2fb69b5d41a9ecd04542d7f5964e6fcd311ba .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/util/util.o: util/util.c  .generated_files/flags/default/68fc66b2cb698a8e17d65e38183ce1275d75340e .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/util.o.d 
	@${RM} ${OBJECTDIR}/util/util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  util/util.c  -o ${OBJECTDIR}/util/util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/util/util.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UX/Thread_UX_ISC.o: UX/Thread_UX_ISC.c  .generated_files/flags/default/5aaaf3d79c6b626559515c9ed8153668cf031ee1 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/UX" 
	@${RM} ${OBJECTDIR}/UX/Thread_UX_ISC.o.d 
	@${RM} ${OBJECTDIR}/UX/Thread_UX_ISC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UX/Thread_UX_ISC.c  -o ${OBJECTDIR}/UX/Thread_UX_ISC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UX/Thread_UX_ISC.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/serial/serial.o: serial/serial.c  .generated_files/flags/default/9a7de8d58cc4802878a7e12be4dcae9623812133 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/serial" 
	@${RM} ${OBJECTDIR}/serial/serial.o.d 
	@${RM} ${OBJECTDIR}/serial/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  serial/serial.c  -o ${OBJECTDIR}/serial/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/serial/serial.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/4e8009037e4e252d70df0716ab06114f2d3649d0 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o: BRIDGE/SRC/Thread_BRIDGE.c  .generated_files/flags/default/d3a1140f6d8cc114f2128b62fc2365746c899ad8 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/BRIDGE/SRC" 
	@${RM} ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o.d 
	@${RM} ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  BRIDGE/SRC/Thread_BRIDGE.c  -o ${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/BRIDGE/SRC/Thread_BRIDGE.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/croutine.o: FreeRTOS/Source/croutine.c  .generated_files/flags/default/a26ec0d34c93f60c6b2b07cc9d6634679049c522 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/croutine.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/croutine.c  -o ${OBJECTDIR}/FreeRTOS/Source/croutine.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/croutine.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/event_groups.o: FreeRTOS/Source/event_groups.c  .generated_files/flags/default/a7626eba80703c7b56bd66ac578fd6e653c0b786 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/event_groups.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/event_groups.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/event_groups.c  -o ${OBJECTDIR}/FreeRTOS/Source/event_groups.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/event_groups.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/list.o: FreeRTOS/Source/list.c  .generated_files/flags/default/133259ae7fbaba1226c7a8fc9587d18112720ce8 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/list.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/list.c  -o ${OBJECTDIR}/FreeRTOS/Source/list.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/list.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/queue.o: FreeRTOS/Source/queue.c  .generated_files/flags/default/f201beb64822b3100dbc7f17cf899dea513e7414 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/queue.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/queue.c  -o ${OBJECTDIR}/FreeRTOS/Source/queue.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/queue.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/tasks.o: FreeRTOS/Source/tasks.c  .generated_files/flags/default/78739f7748cf5e0df9101c7635b4ae431800ae5b .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/tasks.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/tasks.c  -o ${OBJECTDIR}/FreeRTOS/Source/tasks.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/tasks.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/timers.o: FreeRTOS/Source/timers.c  .generated_files/flags/default/979a5b3c8d50d0ffd95f016028cba4dfef186895 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/timers.c  -o ${OBJECTDIR}/FreeRTOS/Source/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/timers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o: FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c  .generated_files/flags/default/3c807f41b136a35b5a98e87d9a8fe9a44b78e7fa .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.c  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/port.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o: FreeRTOS/Source/portable/MemMang/heap_3.c  .generated_files/flags/default/4fefe3a8aa82a5d6f6c6db520a6e0c58a0acf181 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  FreeRTOS/Source/portable/MemMang/heap_3.c  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MemMang/heap_3.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o: SCoCAN/SRC/Thread_ecan.c  .generated_files/flags/default/74494129f0335818d62af51fdce9da8f35fddf9d .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/Thread_ecan.c  -o ${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/Thread_ecan.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o: SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c  .generated_files/flags/default/98dd520ca72d060f1d6f1940aaadbd09cdf860b4 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Configuration.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Configuration.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o: SCoCAN/SRC/CAN_DSPIC_33F_Stack.c  .generated_files/flags/default/9258bf92db69991f2508def40b0ed99d5e8e52d2 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Stack.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o: SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c  .generated_files/flags/default/2ba69abbe9eda435403004ab058e00951c6ba9d0 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/SCoCAN/SRC" 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o.d 
	@${RM} ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.c  -o ${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/SCoCAN/SRC/CAN_DSPIC_33F_Stack_Overflow.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/util/util.o: util/util.c  .generated_files/flags/default/c38fc864c7e924a0efae005c85e0af5befaa024e .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/util" 
	@${RM} ${OBJECTDIR}/util/util.o.d 
	@${RM} ${OBJECTDIR}/util/util.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  util/util.c  -o ${OBJECTDIR}/util/util.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/util/util.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/UX/Thread_UX_ISC.o: UX/Thread_UX_ISC.c  .generated_files/flags/default/7b5ebf4c54b0b1496a2f2aada08a461167453c78 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/UX" 
	@${RM} ${OBJECTDIR}/UX/Thread_UX_ISC.o.d 
	@${RM} ${OBJECTDIR}/UX/Thread_UX_ISC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  UX/Thread_UX_ISC.c  -o ${OBJECTDIR}/UX/Thread_UX_ISC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/UX/Thread_UX_ISC.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/serial/serial.o: serial/serial.c  .generated_files/flags/default/a5852232c6fdca7ea7710dbc5a5e530204ae0c5d .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/serial" 
	@${RM} ${OBJECTDIR}/serial/serial.o.d 
	@${RM} ${OBJECTDIR}/serial/serial.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  serial/serial.c  -o ${OBJECTDIR}/serial/serial.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/serial/serial.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/main.o: main.c  .generated_files/flags/default/febd66bd6cbce15a286f7cff3e6cf187b22a5d2f .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"FreeRTOS/Source/include" -I"serial" -I"FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" -I"CONFIG" -I"SCoCAN/INC" -I"util" -I"BRIDGE/INC" -I"UX" -I"SCoCAN/INC" -DMPLAB_DSPIC_PORT -DNAMEPRJ=${CND_ARTIFACT_NAME_default} -DCOMPILATIONTIME=${COMPILATIONTIME} -DCOMPILATIONTIME1 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o: FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S  .generated_files/flags/default/2f6ab512cadfd458ca3cb9415f44e23e4df55eb5 .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.d"  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.asm.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o: FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S  .generated_files/flags/default/fbf5223808840cf188c4c48d6ff4d363abfb03e .generated_files/flags/default/74d464f3899599845d713a1d015fd0bf2695bd19
	@${MKDIR} "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC" 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.d 
	@${RM} ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.S  -o ${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.d"  -omf=elf -DXPRJ_default=$(CND_CONF)    -Wa,-MD,"${OBJECTDIR}/FreeRTOS/Source/portable/MPLAB/PIC24_dsPIC/portasm_dsPIC.o.asm.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)  -mdfp="${DFP_DIR}/xc16"
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    p33FJ128MC804_0x8c00_with_FreeRTOS
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=4096,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   p33FJ128MC804_0x8c00_with_FreeRTOS
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=4096,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
	@echo Normalizing hex file
	@"C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../bin/hexmate" --edf="C:/Program Files/Microchip/MPLABX/v6.00/mplab_platform/platform/../mplab_ide/modules/../../dat/en_msgs.txt" ${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.hex -o${DISTDIR}/Proy_dsPIC33FJxxx_0x8c00_RSCAN_2_6.X.${IMAGE_TYPE}.hex

endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
