/*
 ***************************************************************************
 * MediaTek Inc.
 *
 * All rights reserved. source code is an unpublished work and the
 * use of a copyright notice does not imply otherwise. This source code
 * contains confidential trade secret material of MediaTek. Any attemp
 * or participation in deciphering, decoding, reverse engineering or in any
 * way altering the source code is stricitly prohibited, unless the prior
 * written consent of MediaTek, Inc. is obtained.
 ***************************************************************************

    Module Name:
    safe_cbhn.h//Fancy20200810
*/


#ifndef _SAFE_CHN_H_
#define _SAFE_CHN_H_

#ifdef WIFI_MD_COEX_SUPPORT

#include "rt_config.h"


/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/
#define UNSAFE_CHN_PROC_INTVL         60000      /* unit: msec */

#define SAFE_CHN_START_IDX_2G4 	0	/* To keep align with modem/FW, bit 1 is channel 1 */
#define SAFE_CHN_END_IDX_2G4 	14
#define SAFE_CHN_START_IDX_5G0 	36
#define SAFE_CHN_END_IDX_5G0 	144
#define SAFE_CHN_START_IDX_5G1 	149
#define SAFE_CHN_END_IDX_5G1 	181

typedef enum _ENUM_SAFE_CHN_TYPE_T
{
	SAFE_CHN_TYPE_NONE = 0x0,
	SAFE_CHN_TYPE_2G4 = 0x1,
	SAFE_CHN_TYPE_5G = 0x2
}ENUM_SAFE_CHN_TYPE_T, *P_SAFE_CHN_TYPE_T;

typedef enum _ENUM_SAFE_CHN_MASK_IDX_T
{
	SAFE_CHN_MASK_BAND_2G4 = 0,	/*2.4G, ch1~14 */
	SAFE_CHN_MASK_BAND_5G_0 = 1, /* 5G, ch36~144 */
	SAFE_CHN_MASK_BAND_5G_1 = 2, /* 5G, ch149~181 */
	SAFE_CHN_MASK_IDX_NUM = 3
} ENUM_SAFE_CHN_MASK_IDX_T, *P_ENUM_SAFE_CHN_MASK_IDX_T;

typedef struct _LTE_SAFE_CH_CTRL
{
	BOOLEAN bQueryLteDone;	/* Whether query lte unsafe channel cmd send or not, to avoid multiple query */
	NDIS_SPIN_LOCK SafeChDbLock;	/* Lock of self DB */
	UINT_32 SafeChnProcIntvl;	/* Interval of processing safe channel change, to avoid trigger channel switch too frequently. */
	UINT_32 RcvLteEventCnt;		/* Used for stats. */
	UINT_32 SafeChnChgCnt;	/* Used for stats. */
	UINT_32 ChnSwitchCnt[DBDC_BAND_NUM];	/* Used for stats. */
	UINT_32 BandBanCnt[DBDC_BAND_NUM];	/* Used for stats. */
	UINT_32	FailCnt[DBDC_BAND_NUM];	/* Used for stats. */
	UINT_32 BandUpCnt[DBDC_BAND_NUM];	/* Used for stats. */
	UINT_32	WaitForSafeChOpCnt[DBDC_BAND_NUM];	/* Count for LTE event waiting for operting */
	BOOLEAN bAllUnsafe[DBDC_BAND_NUM];	/* TRUE/FALSE: all available channels are unsafe on the band /or not */
	UINT_32 SafeChnBitmask[SAFE_CHN_MASK_IDX_NUM];	/* Safe channel bitmask (not filter unavailable channels) 1: safe, 0: unsafe */
	UINT_32 AvaChnBitmask[SAFE_CHN_MASK_IDX_NUM];	/* All available channel bitmask (not filter unsafe channels) 1: safe, 0: unsafe */
}LTE_SAFE_CH_CTRL, *P_LTE_SAFE_CH_CTRL;

/**
* LteSafeChannelInit - Init LTE safe channel.
* @pAd: pointer of the RTMP_ADAPTER
**/
VOID LteSafeChannelInit(IN PRTMP_ADAPTER	pAd);

/**
* LteSafeChannelDeinit - Deinit LTE safe channel.
* @pAd: pointer of the RTMP_ADAPTER
**/
VOID LteSafeChannelDeinit(IN PRTMP_ADAPTER pAd);

/**
* ProcessSafeChannelChange - Process unsafe channel change.
* @pAd: pointer of the RTMP_ADAPTER
*
**/
VOID ProcessSafeChannelChange(RTMP_ADAPTER *pAd);

/**
* LteSafeBuildChnBitmask - Build available channel bit mask.
* @pAd: pointer of the RTMP_ADAPTER
* @band_idx: band index
*
* This function translate basic available channel list to bitmask, for safe channel process use.
*
**/
VOID LteSafeBuildChnBitmask(PRTMP_ADAPTER pAd, UINT8 band_idx);

/**
* IsChannelSafe - Check whether the input channel is safe or not.
* @pAd: pointer of the RTMP_ADAPTER
* @channel: the channel number
*
* The return value is - TRUE if safe, FALSE if unsafe.
**/
BOOLEAN IsChannelSafe(PRTMP_ADAPTER pAd, UCHAR channel);

/**
* LteSafeChnEventHandle - Handle LTE safe channel event.
* @pAd: pointer of the RTMP_ADAPTER
* @channel_bit_mask: the channel bit mask
*
**/
VOID LteSafeChnEventHandle(RTMP_ADAPTER *pAd, UINT32 *channel_bit_mask);

/**
* LteSafeChannelChangeProcess - Process lte safe channel change event after dequeue from cmd queue.
* @pAd: pointer of the RTMP_ADAPTER
* @CMDQelmt: band index
*
**/
NTSTATUS LteSafeChannelChangeProcess(PRTMP_ADAPTER pAd, PCmdQElmt CMDQelmt);

/**
* Set_UnsafeChannel_Proc - Configure unsafe channel list.
* @pAd: pointer of the RTMP_ADAPTER
* @arg: unsafe channel list (ex. 1:36:40)
*
* This function is for feature debug
*
**/
INT Set_UnsafeChannel_Proc(RTMP_ADAPTER *pAd, RTMP_STRING *arg);

/**
* Show_UnsafeChannel_Info - Display unsafe channel info
* @pAd: pointer of the RTMP_ADAPTER
* @arg: Null
*
* This function is for feature debug
*
**/
INT Show_UnsafeChannel_Info(PRTMP_ADAPTER	 pAd, RTMP_STRING *arg);


#endif
#endif

