/* ===========================================================================
* @path $(IPNCPATH)\sys_adm\system_server
*
* @desc 
* .
* Copyright (c) Appro Photoelectron Inc.  2009
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* =========================================================================== */
/**
* @file serial_config.h
* @brief Functions about SD Card control.
*/
#ifndef __SERIAL_CONFIG_H__
#define __SERIAL_CONFIG_H__

#include     <stdio.h>      /*��׼�����������*/ 
#include     <stdlib.h>     /*��׼�����ⶨ��*/ 
#include     <unistd.h>     /*Unix ��׼��������*/ 
#include     <sys/types.h>   
#include     <sys/stat.h>    
#include     <fcntl.h>      /*�ļ����ƶ���*/ 
#include     <termios.h>    /*PPSIX �ն˿��ƶ���*/ 
#include     <errno.h>      /*����Ŷ���*/ 
int vl_SetSpeed(int rs232ch,int speed);
int vl_Set_data_stop_parity(int rs232ch,int databit,int stopbit,int parity);
int vl_SetDatabit(int rs232ch,int databit);
int vl_SetStopbit(int rs232ch,int stopbit);
int vl_SetParity(int rs232ch,int parity);
int vl_SetStreamCtrl(int rs232ch,int streamctrl);

#endif /*__SERIAL_CONFIG_H__*/

