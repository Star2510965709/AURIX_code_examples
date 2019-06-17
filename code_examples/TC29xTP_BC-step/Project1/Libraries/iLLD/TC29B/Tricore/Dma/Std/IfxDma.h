/**
 * \file IfxDma.h
 * \brief DMA  basic functionality
 * \ingroup IfxLld_Dma
 *
 * \version iLLD_1_0_1_9_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Dma_Std_Enum Enumerations
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Reset Reset Functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Channel_Transaction Channel Transaction Functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Move_Engine Move Engine functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Channel_Configure Channel configuration Functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Channel_Halt Channel Halt Functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Double_Buffer Double Buffer functions
 * \ingroup IfxLld_Dma_Std
 * \defgroup IfxLld_Dma_Std_Interrupts Interrupt functions
 * \ingroup IfxLld_Dma_Std
 */

#ifndef IFXDMA_H
#define IFXDMA_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxDma_cfg.h"
#include "IfxDma_bf.h"
#include "Cpu/Std/IfxCpu_Intrinsics.h"
#include "IfxDma_reg.h"
#include "Src/Std/IfxSrc.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Scu/Std/IfxScuCcu.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Dma_Std_Enum
 * \{ */
/** \brief Bus Master Mode definition
 * Definition in Ifx_DMA.MODE[4].B.MODE
 */
typedef enum
{
    IfxDma_BusMasterMode_user       = 0, /**< \brief Selected hardware resource performs Bus access in user mode */
    IfxDma_BusMasterMode_supervisor = 1  /**< \brief Selected hardware resource performs Bus access in supervisor mode */
} IfxDma_BusMasterMode;

/** \brief Channel Bus Priority definition
 */
typedef enum
{
    IfxDma_ChannelBusPriority_low    = 0,  /**< \brief low priority */
    IfxDma_ChannelBusPriority_medium = 1,  /**< \brief medium priority */
    IfxDma_ChannelBusPriority_high   = 2   /**< \brief high priority */
} IfxDma_ChannelBusPriority;

/** \brief DMA circular buffer (wrap around) definition
 * Definition in Ifx_DMA.CH[64].ADICR.B.CBLS and Ifx_DMA.CH[64].ADICR.B.CBLD
 */
typedef enum
{
    IfxDma_ChannelIncrementCircular_none  = 0,   /**< \brief no circular buffer operation */
    IfxDma_ChannelIncrementCircular_2     = 1,   /**< \brief circular buffer size is 2 byte */
    IfxDma_ChannelIncrementCircular_4     = 2,   /**< \brief circular buffer size is 4 byte */
    IfxDma_ChannelIncrementCircular_8     = 3,   /**< \brief circular buffer size is 8 byte */
    IfxDma_ChannelIncrementCircular_16    = 4,   /**< \brief circular buffer size is 16 byte */
    IfxDma_ChannelIncrementCircular_32    = 5,   /**< \brief circular buffer size is 32 byte */
    IfxDma_ChannelIncrementCircular_64    = 6,   /**< \brief circular buffer size is 64 byte */
    IfxDma_ChannelIncrementCircular_128   = 7,   /**< \brief circular buffer size is 128 byte */
    IfxDma_ChannelIncrementCircular_256   = 8,   /**< \brief circular buffer size is 256 byte */
    IfxDma_ChannelIncrementCircular_512   = 9,   /**< \brief circular buffer size is 512 byte */
    IfxDma_ChannelIncrementCircular_1024  = 10,  /**< \brief circular buffer size is 1024 byte */
    IfxDma_ChannelIncrementCircular_2048  = 11,  /**< \brief circular buffer size is 2048 byte */
    IfxDma_ChannelIncrementCircular_4096  = 12,  /**< \brief circular buffer size is 4096 byte */
    IfxDma_ChannelIncrementCircular_8192  = 13,  /**< \brief circular buffer size is 8192 byte */
    IfxDma_ChannelIncrementCircular_16384 = 14,  /**< \brief circular buffer size is 16384 byte */
    IfxDma_ChannelIncrementCircular_32768 = 15   /**< \brief circular buffer size is 32768 byte */
} IfxDma_ChannelIncrementCircular;

/** \brief DMA incrementation direction definition
 * Definition in Ifx_DMA.CH[64].ADICR.B.INCS
 */
typedef enum
{
    IfxDma_ChannelIncrementDirection_negative = 0,  /**< \brief pointer is decremented */
    IfxDma_ChannelIncrementDirection_positive = 1   /**< \brief pointer is incremented */
} IfxDma_ChannelIncrementDirection;

/** \brief DMA incrementation definition
 * Definition in Ifx_DMA.CH[64].ADICR.B.SMF
 */
typedef enum
{
    IfxDma_ChannelIncrementStep_1   = 0, /**< \brief increment by 1 width */
    IfxDma_ChannelIncrementStep_2   = 1, /**< \brief increment by 2 width */
    IfxDma_ChannelIncrementStep_4   = 2, /**< \brief increment by 4 width */
    IfxDma_ChannelIncrementStep_8   = 3, /**< \brief increment by 8 width */
    IfxDma_ChannelIncrementStep_16  = 4, /**< \brief increment by 16 width */
    IfxDma_ChannelIncrementStep_32  = 5, /**< \brief increment by 32 width */
    IfxDma_ChannelIncrementStep_64  = 6, /**< \brief increment by 64 width */
    IfxDma_ChannelIncrementStep_128 = 7  /**< \brief increment by 128 width */
} IfxDma_ChannelIncrementStep;

/** \brief Channel Transfer Interrupt generation mechanism.
 * Definition in Ifx_DMA.CH[64].ADICR.B.INTCT (bit 0)
 */
typedef enum
{
    IfxDma_ChannelInterruptControl_thresholdLimitMatch      = 0, /**< \brief interrupt when transfer count (TCOUNT) equals the threshold limit (IRDV) */
    IfxDma_ChannelInterruptControl_transferCountDecremented = 1  /**< \brief interrupt when transfer count (TCOUNT) is decremented */
} IfxDma_ChannelInterruptControl;

/** \brief DMA transfer definition
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.BLKM and Ifx_DMA.BLK1.ME.CHCR.B.BLKM
 */
typedef enum
{
    IfxDma_ChannelMove_1  = 0,  /**< \brief 1 DMA move per DMA transfer */
    IfxDma_ChannelMove_2  = 1,  /**< \brief 2 DMA move per DMA transfer */
    IfxDma_ChannelMove_4  = 2,  /**< \brief 4 DMA move per DMA transfer */
    IfxDma_ChannelMove_8  = 3,  /**< \brief 8 DMA move per DMA transfer */
    IfxDma_ChannelMove_16 = 4,  /**< \brief 16 DMA move per DMA transfer */
    IfxDma_ChannelMove_3  = 5,  /**< \brief 3 DMA move per DMA transfer */
    IfxDma_ChannelMove_5  = 6,  /**< \brief 5 DMA move per DMA transfer */
    IfxDma_ChannelMove_9  = 7   /**< \brief 9 DMA move per DMA transfer */
} IfxDma_ChannelMove;

/** \brief DMA move size definition
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.CHDW and Ifx_DMA.BLK1.ME.CHCR.B.CHDW
 */
typedef enum
{
    IfxDma_ChannelMoveSize_8bit   = 0,  /**< \brief 1 DMA move is 8 bit wide */
    IfxDma_ChannelMoveSize_16bit  = 1,  /**< \brief 1 DMA move is 16 bit wide */
    IfxDma_ChannelMoveSize_32bit  = 2,  /**< \brief 1 DMA move is 32 bit wide */
    IfxDma_ChannelMoveSize_64bit  = 3,  /**< \brief 1 DMA move is 64 bit wide */
    IfxDma_ChannelMoveSize_128bit = 4,  /**< \brief 1 DMA move is 128 bit wide */
    IfxDma_ChannelMoveSize_256bit = 5   /**< \brief 1 DMA move is 256 bit wide */
} IfxDma_ChannelMoveSize;

/** \brief DMA operation mode
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.CHMODE and Ifx_DMA.BLK1.ME.CHCR.B.CHMODE
 */
typedef enum
{
    IfxDma_ChannelOperationMode_single     = 0, /**< \brief channel disabled after transaction */
    IfxDma_ChannelOperationMode_continuous = 1  /**< \brief channel stays enabled after transaction */
} IfxDma_ChannelOperationMode;

/** \brief Pattern detection selection
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.PATSEL and Ifx_DMA.BLK1.ME.CHCR.B.PATSEL
 */
typedef enum
{
    IfxDma_ChannelPattern_0_disable = 0,  /**< \brief Pattern detect 0 disabled */
    IfxDma_ChannelPattern_0_mode1   = 1,  /**< \brief Compare match configuration 1 : pattern compare of MExR.RD[0] to PAT0[0] masked by PAT0[2] */
    IfxDma_ChannelPattern_0_mode2   = 2,  /**< \brief Compare match configuration 2 : pattern compare of MExR.RD[0] to PAT0[1] masked by PAT0[3] */
    IfxDma_ChannelPattern_0_mode3   = 3,  /**< \brief Compare match configuration 3 : pattern compare of MExR.RD[0] to PAT0[0] masked by PAT0[2] of actual DMA read move and pattern compare of MExR.RD[0] to PAT0[1] masked by PAT0[3] of previous DMA read move */
    IfxDma_ChannelPattern_1_disable = 4,  /**< \brief Pattern detect 1 disabled */
    IfxDma_ChannelPattern_1_mode1   = 5,  /**< \brief Compare match configuration 1 : pattern compare of MExR.RD[0] to PAT1[0] masked by PAT1[2] */
    IfxDma_ChannelPattern_1_mode2   = 6,  /**< \brief Compare match configuration 2 : pattern compare of MExR.RD[0] to PAT1[1] masked by PAT1[3] */
    IfxDma_ChannelPattern_1_mode3   = 7   /**< \brief Compare match configuration 3 : pattern compare of MExR.RD[0] to PAT1[0] masked by PAT1[2] of actual DMA read move and pattern compare of MExR.RD[0] to PAT1[1] masked by PAT1[3] of previous DMA read move */
} IfxDma_ChannelPattern;

/** \brief Channel Priority definition
 */
typedef enum
{
    IfxDma_ChannelPriority_low    = 0,  /**< \brief low priority */
    IfxDma_ChannelPriority_medium = 1,  /**< \brief medium priority */
    IfxDma_ChannelPriority_high   = 2   /**< \brief high priority */
} IfxDma_ChannelPriority;

/** \brief DMA request mode
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.RROAT and Ifx_DMA.BLK1.ME.CHCR.B.RROAT
 */
typedef enum
{
    IfxDma_ChannelRequestMode_oneTransferPerRequest         = 0, /**< \brief a request initiates a single transfer */
    IfxDma_ChannelRequestMode_completeTransactionPerRequest = 1  /**< \brief a request initiates a complete transaction */
} IfxDma_ChannelRequestMode;

/** \brief DMA request selection
 * Definition in Ifx_DMA.BLK0.ME.CHCR.B.PRSEL and Ifx_DMA.BLK1.ME.CHCR.B.PRSEL
 */
typedef enum
{
    IfxDma_ChannelRequestSource_peripheral = 0,  /**< \brief Transfer Request via Hardware Trigger */
    IfxDma_ChannelRequestSource_daisyChain = 1   /**< \brief Transfer Request via next (higher priority) channel */
} IfxDma_ChannelRequestSource;

/** \brief shadow definition definition
 * Definition in Ifx_DMA.CH[64].ADICR.B.SHCT
 */
typedef enum
{
    IfxDma_ChannelShadow_none                                 = 0,   /**< \brief shadow address register not used. Source and destination address register are written directly */
    IfxDma_ChannelShadow_src                                  = 1,   /**< \brief Shadow address register used for source address buffering. When writing to SADRmx, the address is buffered in SHADRmx and transferred to SADRmx with the start of the next DMA transaction */
    IfxDma_ChannelShadow_dst                                  = 2,   /**< \brief Shadow address register used for destination address buffering. When writing to DADRmx, the address is buffered in SHADRmx and transferred to DADRmx with the start of the next DMA transaction */
    IfxDma_ChannelShadow_srcDirectWrite                       = 5,   /**< \brief Shadow address used for source buffering. When writing to SADRz, the address is buffered in SHADRz and transferred to SADRz with the start of the next DMA transaction */
    IfxDma_ChannelShadow_dstDirectWrite                       = 6,   /**< \brief Shadow address used for destination buffering. When writing to DADRz, the address is buffered in SHADRz and transferred to DADRz with the start of the next DMA transaction */
    IfxDma_ChannelShadow_doubleSourceBufferingSwSwitch        = 8,   /**< \brief Software switch only. Shadow address used for double buffering */
    IfxDma_ChannelShadow_doubleSourceBufferingHwSwSwitch      = 9,   /**< \brief Automatic Hardware and Software switch. Shadow address used for double buffering */
    IfxDma_ChannelShadow_doubleDestinationBufferingSwSwitch   = 10,  /**< \brief Software switch only. Shadow address used for double buffering */
    IfxDma_ChannelShadow_doubleDestinationBufferingHwSwSwitch = 11,  /**< \brief Automatic Hardware and Software switch. Shadow address used for double buffering */
    IfxDma_ChannelShadow_linkedList                           = 12,  /**< \brief The DMA controller reads a DMA channel transaction control set and overwrites 8 X words in the corresponding DMARAM channel z */
    IfxDma_ChannelShadow_accumulatedLinkedList                = 13,  /**< \brief The DMA controller reads a DMA channel transaction control set and overwrites 6 X words in the corresponding DMARAM channel z */
    IfxDma_ChannelShadow_safeLinkedList                       = 14,  /**< \brief The DMA controller reads a DMA channel transaction control set. The Linked List only proceeds with the next DMA transaction if the existing SDCRC checksum matches the expected SDCRC checksum in the loaded from the new DMA transaction control set */
    IfxDma_ChannelShadow_conditionalLinkedList                = 15   /**< \brief Shadow address register (MExSHADR) and source and destination address CRC register (MExSDCRC) are used as address pointers to a Linked List. The selection of the address pointer is determined by DMA channel pattern detection conditions */
} IfxDma_ChannelShadow;

typedef enum
{
    IfxDma_HardwareResourcePartition_0 = 0,      /**< \brief "Set of DMA channels are associated with hardware resource partition " + str(x)  */
    IfxDma_HardwareResourcePartition_1,          /**< \brief "Set of DMA channels are associated with hardware resource partition " + str(x)  */
    IfxDma_HardwareResourcePartition_2,          /**< \brief "Set of DMA channels are associated with hardware resource partition " + str(x)  */
    IfxDma_HardwareResourcePartition_3           /**< \brief "Set of DMA channels are associated with hardware resource partition " + str(x)  */
} IfxDma_HardwareResourcePartition;

/** \brief DMA move engine definition
 */
typedef enum
{
    IfxDma_MoveEngine_0 = 0,  /**< \brief first move engine */
    IfxDma_MoveEngine_1 = 1   /**< \brief second move engine */
} IfxDma_MoveEngine;

/** \brief Enable/disable the sensitivity of the module to sleep signal\n
 * Definition in Ifx_DMA.CLC.B.EDIS
 */
typedef enum
{
    IfxDma_SleepMode_enable  = 0, /**< \brief enables sleep mode */
    IfxDma_SleepMode_disable = 1  /**< \brief disables sleep mode */
} IfxDma_SleepMode;

/** \} */

/** \addtogroup IfxLld_Dma_Std_Reset
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Return the status of a DMA channel (reset / not reset)
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if the channel is reset
 * FALSE if the channel is not reset
 *
 * \code
 *     // check whether the channel is reset or not and also the hardware trigger disabled
 *
 *     if (IfxDma_isChannelReset(chn[0].dma, chn[0].channelId) &&
 *         (!IfxDma_isChannelTransactionEnabled(chn[0].dma, chn[0].channelId))) {
 *         // Dma is out of RESET and there is no hardware request enabled
 *         IfxDma_Dma_startChannelTransaction(&chn[0]);
 *     }
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_isChannelReset(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Reset the channel
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Apply reset to the channel
 *     IfxDma_resetChannel(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_resetChannel(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Channel_Transaction
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clear the channel transaction request lost flag status
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Clear the channel transaction request lost flag status
 *     IfxDma_clearChannelTransactionRequestLost(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_clearChannelTransactionRequestLost(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Disable a DMA channel hardware transaction request
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_enableChannelTransaction
 *
 */
IFX_INLINE void IfxDma_disableChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Disable the generation of a channel transaction lost error interrupt
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Disable the transaction request lost interrupt for given channel
 *     IfxDma_disableChannelTransactionLostError(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_disableChannelTransactionLostError(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Enable a DMA channel hardware transaction request
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     unsigned *src = (unsigned *)((unsigned)&SRC_DMACH0.U + 4*NUM_CHANNELS);
 *     for(int chn=0; chn<NUM_CHANNELS; ++chn, ++src) {
 *         IfxSrc_setRequest(src);
 *     }
 *
 *     // Do not restrict the hardware triggering to only one transaction
 *
 *     IfxDma_setChannelContinuousMode(chn[0].dma, chn[0].channelId);
 *     IfxDma_setChannelContinuousMode(chn[1].dma, chn[1].channelId);
 *     IfxDma_setChannelContinuousMode(chn[2].dma, chn[2].channelId);
 *
 *     // Check for end of transaction
 *
 *     while(!(IfxDma_getAndClearChannelInterrupt(chn[0].dma, chn[0].channelId)));
 *
 *     // Enable the hardware trigger for channel 3
 *     IfxDma_enableChannelTransaction(chn[3].dma, chn[3].channelId);
 *
 *     // Disable the hardware trigger for channel 2
 *     IfxDma_disableChannelTransaction(chn[2].dma, chn[2].channelId);
 *     // Hardware triggers for second time
 *
 *     unsigned *SRc = (unsigned *)((unsigned)&SRC_DMACH0.U + 4*NUM_CHANNELS);
 *     for(int chn=0; chn<NUM_CHANNELS; ++chn, ++src) {
 *         IfxSrc_setRequest(src);
 *     }
 *
 *     // Restrict the hardware triggering to only one transaction
 *     IfxDma_setChannelSingleMode(chn[0].dma, chn[0].channelId);
 *     IfxDma_setChannelSingleMode(chn[1].dma, chn[1].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_enableChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Enable the generation of  a channel transaction lost error interrupt
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Enable the transaction request lost interrupt for given channel
 *     IfxDma_enableChannelTransactionLostError(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_enableChannelTransactionLostError(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Check the channel transaction request lost flag status
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if the TRL is set
 * FALSE if the TRL is not set
 *
 * \code
 *     boolean trlFlag;
 *
 *     // Check whether the channel transaction request lost flag is set or not
 *     trlFlag = IfxDma_getChannelTransactionRequestLost(chn[0].dma, chn[0].channelId));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getChannelTransactionRequestLost(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Converts DMA circular range to circular code
 * \param range DMA circular range
 * \return DMA circular code
 */
IFX_INLINE IfxDma_ChannelIncrementCircular IfxDma_getCircularRangeCode(uint16 range);

/** \brief Return the hardware transaction request status of a DMA channel
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if the hardware transaction request is enabled
 * FALSE if the hardware transaction request is disabled
 *
 * A coding example can be found in \ref IfxDma_isChannelReset
 *
 */
IFX_INLINE boolean IfxDma_isChannelTransactionEnabled(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Return the status of a DMA channel (transaction pending)
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if a transaction request for the given channel is pending
 *
 * \code
 *     // check for the channel request pending with the channel
 *     if (IfxDma_isChannelTransactionPending(chn[0].dma, chn[0].channelId) == TRUE) {
 *         // There is channel request pending for channel 0
 *         result |= 0;
 *     }
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_isChannelTransactionPending(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Sets the sensitivity of the module to sleep signal
 * \param dma pointer to DMA registers
 * \param mode mode selection (enable/disable)
 * \return None
 */
IFX_INLINE void IfxDma_setSleepMode(Ifx_DMA *dma, IfxDma_SleepMode mode);

/** \brief Request a DMA channel transaction
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_Dma_startChannelTransaction
 *
 */
IFX_INLINE void IfxDma_startChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Move_Engine
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clear the DMA error status flags
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \param mask value holds the bits to clear or mask
 * \return None
 *
 * \code
 *     // Clear the status of the error flags (as defined in _Impl/IfxDma_cfg.h)
 *     IfxDma_clearErrorFlags(chn[0].dma,IfxDma_MoveEngine_1,
 *                           IFXDMA_ERROR_S |    // move engine source error
 *                           IFXDMA_ERROR_D |    // move engine destination error
 *                           IFXDMA_ERROR_SPB |  // bus error on SPB
 *                           IFXDMA_ERROR_SRI |  // bus error on SRI
 *                           IFXDMA_ERROR_RAM |  // RAM error
 *                           IFXDMA_ERROR_SLL |  // safe linked list CRC checksum error
 *                           IFXDMA_ERROR_DLL);  // failed linked list load error
 * \endcode
 *
 */
IFX_INLINE void IfxDma_clearErrorFlags(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine, uint32 mask);

/** \brief Disable the generation of a Move engine destination error interrupt
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \return None
 *
 * A coding example can be found in \ref IfxDma_disableMoveEngineSourceError
 *
 */
IFX_INLINE void IfxDma_disableMoveEngineDestinationError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine);

/** \brief Disable the generation of a Move engine source error interrupt
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \return None
 *
 * \code
 *     // Disable the move engine source and destination move errors
 *     IfxDma_disableMoveEngineSourceError(chn[0].dma,IfxDma_MoveEngine_1);
 *     IfxDma_disableMoveEngineDestinationError(chn[0].dma,IfxDma_MoveEngine_1);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_disableMoveEngineSourceError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine);

/** \brief Enable the generation of a Move engine destination error interrupt
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \return None
 *
 * A coding example can be found in \ref IfxDma_enableMoveEngineSourceError
 *
 */
IFX_INLINE void IfxDma_enableMoveEngineDestinationError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine);

/** \brief Enable the generation of a Move engine source error interrupt
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \return None
 *
 * \code
 *     // Enable the move engine source and destination move errors
 *     IfxDma_enableMoveEngineSourceError(chn[0].dma,IfxDma_MoveEngine_1);
 *     IfxDma_enableMoveEngineDestinationError(chn[0].dma,IfxDma_MoveEngine_1);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_enableMoveEngineSourceError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine);

/** \brief Return the DMA error status flags
 * \param dma pointer to DMA module
 * \param moveEngine pointer to the DMA move engine
 * \return the content of the DMA.ERRSR register
 *
 * \code
 *     uint32 errorFlags = 0;
 *
 *     // Get the status of the error flags of move engine
 *     errorFlags = IfxDma_getErrorFlags(chn[0].dma,IfxDma_MoveEngine_1);
 *
 *     if( errorFlags & IFXDMA_ERROR_S ) {   // move engine source error
 *         }
 *
 *     if( errorFlags & IFXDMA_ERROR_D ) {   // move engine destination error
 *        // ...
 *        }
 *
 *     if( errorFlags & IFXDMA_ERROR_SPB ) { // bus error on SPB
 *        // ...
 *        }
 *
 *     if( errorFlags & IFXDMA_ERROR_SRI ) { // bus error on SRI
 *        // ...
 *        }
 *
 *     if( errorFlags & IFXDMA_ERROR_RAM ) { // RAM error
 *        // ...
 *        }
 *
 *     if( errorFlags & IFXDMA_ERROR_SLL ) { // safe linked list CRC checksum error
 *        // ...
 *        }
 *
 *     if( errorFlags & IFXDMA_ERROR_DLL ) { // failed linked list load error
 *        // ...
 *        }
 * \endcode
 *
 */
IFX_INLINE uint32 IfxDma_getErrorFlags(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Channel_Configure
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Get a channel source address
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return Actual channel destination address
 *
 * \code
 *     uint32 destAddr = IfxDma_getChannelDestinationAddress(chn[2].dma, chn[2].channelId);
 *
 * \endcode
 *
 */
IFX_INLINE uint32 IfxDma_getChannelDestinationAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Get a channel source address
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return Actual channel source address
 *
 * \code
 *     uint32 sourceAddr = IfxDma_getChannelSourceAddress(chn[2].dma, chn[2].channelId);
 * \endcode
 *
 */
IFX_INLINE uint32 IfxDma_getChannelSourceAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Return the DMA channel suspend Mode status
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return Channel Suspend Mode or Frozen State Active status (1- DMA channel is in channel suspend mode or frozen state)
 */
IFX_INLINE boolean IfxDma_getChannelSuspendModeStatus(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Return remaining DMA transfer count
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return Remaining DMA transfer count
 *
 * \code
 *     // Wait till transfer count (TCOUNT) becomes 0
 *
 *     bool notFinished;
 *     do {
 *         notFinished = false;
 *             if( IfxDma_getChannelTransferCount(chn[0].dma, chn[0].channelId) ) {
 *                 notFinished = true;
 *                 break;
 *             }
 *     } while( notFinished );
 * \endcode
 *
 */
IFX_INLINE uint32 IfxDma_getChannelTransferCount(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief get the time stamp
 * \param dma pointer to DMA module
 * \return the current time stamp
 *
 * \code
 *     uint32 timestamp = IfxDma_getTimestamp(chn[0].dma);
 * \endcode
 *
 */
IFX_INLINE uint32 IfxDma_getTimestamp(Ifx_DMA *dma);

/** \brief Configure the move count for each DMA channel transfer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param blockMode value holds the number of moves with in a DMA transfer
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelTransferCount
 *
 */
IFX_INLINE void IfxDma_setChannelBlockMode(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelMove blockMode);

/** \brief Configure a DMA channel to "continous transaction mode"
 * After a transaction, the hardware request transaction remain enabled
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_enableChannelTransaction
 *
 */
IFX_INLINE void IfxDma_setChannelContinuousMode(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Configure the destination address
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param address is the Initial address of the destination pointer
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelSourceAddress
 *
 */
IFX_INLINE void IfxDma_setChannelDestinationAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId, void *address);

/** \brief Configure a DMA channel destination pointer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param incStep Specifies the pointer incrementation step
 * \param direction Specifies the incrementation direction
 * \param size Specifies the size of the circular buffer
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelSourceIncrementStep
 *
 */
IFX_INLINE void IfxDma_setChannelDestinationIncrementStep(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelIncrementStep incStep, IfxDma_ChannelIncrementDirection direction, IfxDma_ChannelIncrementCircular size);

/** \brief Configure a DMA channel move
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param moveSize value holds the opcode or size of data of individual moves with in a DMA transfer
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelTransferCount
 *
 */
IFX_INLINE void IfxDma_setChannelMoveSize(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelMoveSize moveSize);

/** \brief Configure a DMA channel shadow pointer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param shadow Specifies the shadow pointer
 * \return None
 *
 * \code
 *     // Push the shadow mode into double buffer
 *     IfxDma_setChannelShadow(chn[0].dma, chn[0].channelId,
 *     IfxDma_ChannelShadow_doubleSourceBufferingSwSwitch);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelShadow(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelShadow shadow);

/** \brief Configure a DMA channel to "single transaction mode"
 * After a transaction, the hardware request transaction is disabled, and must be set by software again
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_enableChannelTransaction
 *
 */
IFX_INLINE void IfxDma_setChannelSingleMode(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Configure a DMA channel to "single transaction mode"
 * One transfer request starts a complete DMA transaction
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelTransferCount
 *
 */
IFX_INLINE void IfxDma_setChannelSingleTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Configure a DMA channel to "single transfer mode"
 * A transfer request is required for each transfer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * A coding example can be found in \ref IfxDma_setChannelTransferCount
 *
 */
IFX_INLINE void IfxDma_setChannelSingleTransfer(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Configure the source address
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param address is the Initial address of the source pointer
 * \return None
 *
 * \code
 *     // Check for the end of current transaction and before trigger the channel request for
 *     // for another channel, re configure the source and destination addresses
 *
 *     while(!(IfxDma_getAndClearChannelInterrupt(chn[1].dma, chn[1].channelId)));
 *
 *     // Re-Program the source address for the channel 2
 *     IfxDma_setChannelSourceAddress(chn[2].dma, chn[2].channelId,Sadr);
 *
 *     // Re-Program the destination address for channel 2
 *     IfxDma_setChannelDestinationAddress(chn[2].dma, chn[2].channelId,Dadr);
 *
 *     // Start DMA transaction for channel 2
 *     IfxDma_Dma_startChannelTransaction(&chn[2]);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelSourceAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId, const void *address);

/** \brief Configure a DMA channel source pointer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param incStep Specifies the pointer incrementation step
 * \param direction Specifies the incrementation direction
 * \param size Specifies the size of the circular buffer
 * \return None
 *
 * \code
 *     // Re-program the source and destination circular buffer control fields
 *     IfxDma_setChannelSourceIncrementStep(chn[0].dma,  chn[0].channelId, IfxDma_ChannelIncrementStep_2, IfxDma_ChannelIncrementDirection_negative, IfxDma_ChannelIncrementCircular_16);
 *
 *     IfxDma_setChannelDestinationIncrementStep(chn[0].dma, chn[0].channelId, IfxDma_ChannelIncrementStep_2, IfxDma_ChannelIncrementDirection_negative, IfxDma_ChannelIncrementCircular_16);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelSourceIncrementStep(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelIncrementStep incStep, IfxDma_ChannelIncrementDirection direction, IfxDma_ChannelIncrementCircular size);

/** \brief Configure a DMA channel suspend enable
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param enable enable (1) / disable (0)
 * \return None
 */
IFX_INLINE void IfxDma_setChannelSuspendEnable(Ifx_DMA *dma, IfxDma_ChannelId channelId, boolean enable);

/** \brief Configure the move count of a DMA channel transaction
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param transferCount value holds the DMA transfers within a transaction (1..16383; 0 handled like 1 transaction)
 * \return None
 *
 * \code
 *     // Start DMA transaction
 *     IfxDma_Dma_startChannelTransaction(&chn[0]);
 *
 *     // Wait till end of transaction
 *     while(!(IfxDma_getAndClearChannelInterrupt(chn[0].dma, chn[0].channelId)));
 *
 *     // Change the TREL configuration for channel 1
 *     IfxDma_setChannelTransferCount(chn[1].dma, chn[1].channelId,0x6);
 *
 *     // Change the BLKM configuration for channel 1
 *     IfxDma_setChannelBlockMode(chn[1].dma, chn[1].channelId,IfxDma_ChannelMove_3);
 *
 *     // Change the Move size configuration for channel 1
 *     IfxDma_setChannelMoveSize(chn[1].dma, chn[1].channelId,IfxDma_ChannelMoveSize_64bit);
 *
 *     // Pull down the channel pending request after the first transfer is initiated
 *     IfxDma_setChannelSingleTransfer(chn[1].dma, chn[1].channelId);
 *
 *     // Pull down the channel pending request after the transaction gets over
 *     IfxDma_setChannelSingleTransaction(chn[2].dma, chn[2].channelId);
 *
 *     // Start DMA transaction
 *     IfxDma_Dma_startChannelTransaction(&chn[1]);
 *
 *     // Start DMA transaction
 *     IfxDma_Dma_startChannelTransaction(&chn[2]);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelTransferCount(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint32 transferCount);

/** \brief Configure the shadow pointer register to read only
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Disable the shadow mode to come out of double buffer mode
 *     IfxDma_writeChannelShadowDisable(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_writeChannelShadowDisable(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Configure the shadow pointer register to write-able
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Enable the shadow mode to come out of double buffer mode
 *     IfxDma_writeChannelShadowEnable(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_writeChannelShadowEnable(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Channel_Halt
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clear channel halt request and aknowledgement
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Quit the halt mode of operation
 *     IfxDma_clearChannelHalt(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_clearChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Get channel halt aknowledgement
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return halt aknowledgement
 *
 * \code
 *     // Check for the channel halt aknowledgement
 *     while(!(IfxDma_getChannelHalt(chn[0].dma, chn[0].channelId)));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief setting channel halt request
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Halt the channel processing
 *     IfxDma_setChannelHalt(chn[0].dma,chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Double_Buffer
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief get information on buffer being read by software and clear the notification flag
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE  if one of the buffers is being read by software
 * FALSE if one of the buffers is already read by software
 *
 * \code
 *     // Check the buffer being read (Double buffer operation mode)
 *     while(!(IfxDma_getDoubleBufferRead(chn[0].dma, chn[0].channelId)));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getDoubleBufferRead(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief get Double buffer selection
 * \param dma pointer to DMA module
 * \param channelId channelId DMA channel number
 * \return TRUE if buffer 1 is being filled
 * FALSE if buffer 0 is being filled
 *
 * \code
 *     boolean buffer_being_filled;
 *
 *     // Check the buffer being filled (Double buffer operation mode)
 *     buffer_being_filled = IfxDma_getDoubleBufferSelection(chn[0].dma, chn[0].channelId));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getDoubleBufferSelection(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief keeps the double buffer active
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     IfxDma_keepDoubleBufferActive(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_keepDoubleBufferActive(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Double buffer switch application
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Apply software buffer switch
 *     IfxDma_switchDoubleBuffer(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_switchDoubleBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/** \addtogroup IfxLld_Dma_Std_Interrupts
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Clear a channel transfer interrupt flag
 * \param dma pointer to DMA module
 * \param channelId channel for which the interrupt flag should be cleared
 * \return None
 *
 * see Dma.INTSR
 *
 */
IFX_INLINE void IfxDma_clearChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Disable channel interrupt trigger
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 * IfxDma_disableChannelInterrupt(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_disableChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Enable channel interrupt trigger
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 * IfxDma_enableChannelInterrupt(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_enableChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Return and clear a channel transfer interrupt flag
 * The flag is automatically cleared with the call to this function
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if the interrupt flag is set
 * FALSE if the interrupt flag is not set
 *
 * \code
 *     // wait for the end of transaction for intended channel by checking the channel interrupt flag
 *     // and clear it once it is set and checked
 *
 *     // Wait till end of the transaction
 *     while(!(IfxDma_getAndClearChannelInterrupt(chn[2].dma, chn[2].channelId)));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getAndClearChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns and clears the pattern detection interrupt flag
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE  if pattern detection for a given channel is found
 * FALSE if pattern detection for a given channel is not found
 *
 * \code
 *     // wait till pattern match is found for given channel
 *     // and clear it once it is set and checked
 *
 *     // Wait for the pattern detection
 *     while(!(IfxDma_getAndClearChannelPatternDetectionInterrupt(chn[0].dma, chn[0].channelId)));
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getAndClearChannelPatternDetectionInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns and clears the status of channel wrap destination buffer interrupt trigger flag
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE  if wrap destination buffer interrupt trigger flag is set
 * FALSE if wrap destination buffer interrupt trigger flag is not set or get cleared already
 *
 * \code
 *     // wait for the destination buffer wrap interrupt flag
 *     // and clear it once it is set and checked
 *     boolean destinationWrapFlag;
 *
 *     destinationWrapFlag = IfxDma_getAndClearChannelWrapDestinationBufferInterrupt(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getAndClearChannelWrapDestinationBufferInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns and clears the status of channel wrap source buffer interrupt trigger flag
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE  if wrap source buffer interrupt trigger flag is set
 * FALSE if wrap source buffer interrupt trigger flag is not set or get cleared already
 *
 * \code
 *     // wait for the source buffer wrap interrupt flag
 *     // and clear it once it is set and checked
 *     boolean sourceWrapFlag;
 *
 *     sourceWrapFlag = IfxDma_getAndClearChannelWrapSourceBufferInterrupt(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getAndClearChannelWrapSourceBufferInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Return a channel transfer interrupt flag
 * \param dma pointer to DMA module
 * \param channelId channel for which the interrupt flag should be returned
 * \return TRUE if the interrupt flag is set
 * FALSE if the interrupt flag is not set
 *
 * see Dma.INTSR
 *
 */
IFX_INLINE boolean IfxDma_getChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns whether the old value of pattern detection corresponding pattern comparison operation found a pattern match in previous DMA * read move or not
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return TRUE if corresponding pattern comparison operation found a pattern match in previous DMA read move or not
 * FALSE if corresponding pattern comparison operation did not find a pattern match in previous DMA read move
 *
 * \code
 *     boolean patternDetectOldVal;
 *
 *     // Check the old value of the pattern detection
 *     patternDetectOldVal = IfxDma_getChannelPatternDetectionOldValue(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE boolean IfxDma_getChannelPatternDetectionOldValue(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns the SRC pointer for given DMA channel
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return SRC pointer for given DMA channel
 *
 * \code
 *
 * \endcode
 *
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxDma_getSrcPointer(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Setting of channel interrupt service request by software
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 *
 * \code
 *     // Set the channel interrupt service request through software
 *     IfxDma_setChannelInterruptServiceRequest(chn[0].dma, chn[0].channelId);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelInterruptServiceRequest(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \} */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Configure the hardware resource partition
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param resourcePartition Hardware resource partition
 * \return None
 *
 * \code
 *     // Set the required hardware resource partition
 *     IfxDma_setChannelHardwareResourcePartition(chn[0].dma, chn[0].channelId,setChannelHardwareResourcePartition);
 * \endcode
 *
 */
IFX_INLINE void IfxDma_setChannelHardwareResourcePartition(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_HardwareResourcePartition resourcePartition);

/** \brief Sets the Interrupt control value
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param value Interrupt control value
 * \return None
 */
IFX_INLINE void IfxDma_setInterruptControlValue(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint8 value);

/** \brief Sets the Circular Buffer Destination Length
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param length Circular Buffer Destination Length
 * \return None
 */
IFX_INLINE void IfxDma_setCircularBufferDestinationLength(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint16 length);

/** \brief Sets the Circular Buffer Source Length
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \param length Circular Buffer Source Length
 * \return None
 */
IFX_INLINE void IfxDma_setCircularBufferSourceLength(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint16 length);

/** \brief Enable the Source Circular Buffer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 */
IFX_INLINE void IfxDma_enableSourceCircularBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Enable the Destination Circular Buffer
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return None
 */
IFX_INLINE void IfxDma_enableDestinationCircularBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns the Data CRC
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return The Data CRC value
 */
IFX_INLINE uint32 IfxDma_getDataCRC(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns the Source and Destination CRC
 * \param dma pointer to DMA module
 * \param channelId DMA channel number
 * \return The source and destination CRC values
 */
IFX_INLINE uint32 IfxDma_getSourceAndDestinationCRC(Ifx_DMA *dma, IfxDma_ChannelId channelId);

/** \brief Returns the ERR pointer
 * \param dma pointer to DMA module
 * \return ERR pointer for given DMA
 */
IFX_INLINE volatile Ifx_SRC_SRCR *IfxDma_getErrPointer(Ifx_DMA *dma);

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE void IfxDma_clearChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.HLTCLR = 1;
}


IFX_INLINE void IfxDma_clearChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCSR.B.CICH = 1;
}


IFX_INLINE void IfxDma_clearChannelTransactionRequestLost(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.CTL = 1;
}


IFX_INLINE void IfxDma_clearErrorFlags(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine, uint32 mask)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        dma->BLK1.CLRE.U = mask;
    }
    else
    {
        dma->BLK0.CLRE.U = mask;
    }
}


IFX_INLINE void IfxDma_disableChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.INTCT &= ~(1 << 1);   // TODO: should we define a special bitmask for this bit manipulation?
}


IFX_INLINE void IfxDma_disableChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.DCH = 1;
}


IFX_INLINE void IfxDma_disableChannelTransactionLostError(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.ETRL = 0;
}


IFX_INLINE void IfxDma_disableMoveEngineDestinationError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        dma->BLK1.EER.B.EDER = 0;
    }
    else
    {
        dma->BLK0.EER.B.EDER = 0;
    }
}


IFX_INLINE void IfxDma_disableMoveEngineSourceError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        dma->BLK1.EER.B.ESER = 0;
    }
    else
    {
        dma->BLK0.EER.B.ESER = 0;
    }
}


IFX_INLINE void IfxDma_enableChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.INTCT |= (1 << 1);   // TODO: should we define a special bitmask for this bit manipulation?
}


IFX_INLINE void IfxDma_enableChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.ECH = 1;
}


IFX_INLINE void IfxDma_enableChannelTransactionLostError(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.ETRL = 1;
}


IFX_INLINE void IfxDma_enableMoveEngineDestinationError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        dma->BLK1.EER.B.EDER = 1;
    }
    else
    {
        dma->BLK0.EER.B.EDER = 1;
    }
}


IFX_INLINE void IfxDma_enableMoveEngineSourceError(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        dma->BLK1.EER.B.ESER = 1;
    }
    else
    {
        dma->BLK0.EER.B.ESER = 1;
    }
}


IFX_INLINE boolean IfxDma_getAndClearChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.ICH != 0;

    if (result == 1)
    {
        dma->CH[channelId].CHCSR.B.CICH = TRUE;
    }

    return result;
}


IFX_INLINE boolean IfxDma_getAndClearChannelPatternDetectionInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.IPM != 0;

    if (result == 1)
    {
        dma->CH[channelId].CHCSR.B.CICH = TRUE;
    }

    return result;
}


IFX_INLINE boolean IfxDma_getAndClearChannelWrapDestinationBufferInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.WRPD != 0;

    if (result == 1)
    {
        dma->CH[channelId].CHCSR.B.CWRP = TRUE;
    }

    return result;
}


IFX_INLINE boolean IfxDma_getAndClearChannelWrapSourceBufferInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.WRPS != 0;

    if (result == 1)
    {
        dma->CH[channelId].CHCSR.B.CWRP = TRUE;
    }

    return result;
}


IFX_INLINE uint32 IfxDma_getChannelDestinationAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].DADR.U;
}


IFX_INLINE boolean IfxDma_getChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->TSR[channelId].B.HLTACK != 0;
}


IFX_INLINE boolean IfxDma_getChannelInterrupt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.ICH;

    return result;
}


IFX_INLINE boolean IfxDma_getChannelPatternDetectionOldValue(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].CHCSR.B.LXO != 0;
}


IFX_INLINE uint32 IfxDma_getChannelSourceAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].SADR.U;
}


IFX_INLINE boolean IfxDma_getChannelSuspendModeStatus(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->SUSACR[channelId].B.SUSAC;
}


IFX_INLINE boolean IfxDma_getChannelTransactionRequestLost(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->TSR[channelId].B.TRL != 0;
}


IFX_INLINE uint32 IfxDma_getChannelTransferCount(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].CHCSR.B.TCOUNT;
}


IFX_INLINE IfxDma_ChannelIncrementCircular IfxDma_getCircularRangeCode(uint16 range)
{
    return (IfxDma_ChannelIncrementCircular)(31 - __clz((uint32)range));
}


IFX_INLINE boolean IfxDma_getDoubleBufferRead(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    boolean result;

    result = dma->CH[channelId].CHCSR.B.FROZEN != 0;

    if (result == 1)
    {
        dma->CH[channelId].CHCSR.B.FROZEN = FALSE;
    }

    return result;
}


IFX_INLINE boolean IfxDma_getDoubleBufferSelection(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].CHCSR.B.BUFFER != 0;
}


IFX_INLINE uint32 IfxDma_getErrorFlags(Ifx_DMA *dma, IfxDma_MoveEngine moveEngine)
{
    if (moveEngine == IfxDma_MoveEngine_1)
    {
        return dma->BLK1.ERRSR.U;
    }
    else
    {
        return dma->BLK0.ERRSR.U;
    }
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxDma_getSrcPointer(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    // only a single DMA available, therefore no check for the dma pointer required
    return &MODULE_SRC.DMA.DMA[0].CH[channelId];
}


IFX_INLINE uint32 IfxDma_getTimestamp(Ifx_DMA *dma)
{
    return dma->TIME.U;
}


IFX_INLINE boolean IfxDma_isChannelReset(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->TSR[channelId].B.RST != 0;
}


IFX_INLINE boolean IfxDma_isChannelTransactionEnabled(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->TSR[channelId].B.HTRE != 0;
}


IFX_INLINE boolean IfxDma_isChannelTransactionPending(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->TSR[channelId].B.CH != 0;
}


IFX_INLINE void IfxDma_keepDoubleBufferActive(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCSR.U = 0U << IFX_DMA_CH_CHCSR_FROZEN_OFF;
}


IFX_INLINE void IfxDma_resetChannel(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.RST = 1;
}


IFX_INLINE void IfxDma_setChannelBlockMode(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelMove blockMode)
{
    dma->CH[channelId].CHCFGR.B.BLKM = blockMode;
}


IFX_INLINE void IfxDma_setChannelContinuousMode(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCFGR.B.CHMODE = 1;
}


IFX_INLINE void IfxDma_setChannelDestinationAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId, void *address)
{
    dma->CH[channelId].DADR.U = (uint32)address;
}


IFX_INLINE void IfxDma_setChannelDestinationIncrementStep(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelIncrementStep incStep, IfxDma_ChannelIncrementDirection direction, IfxDma_ChannelIncrementCircular size)
{
    Ifx_DMA_CH_ADICR adicr;
    adicr.U                    = dma->CH[channelId].ADICR.U;
    adicr.B.DMF                = incStep;
    adicr.B.INCD               = direction;
    adicr.B.CBLD               = size;
    dma->CH[channelId].ADICR.U = adicr.U;
}


IFX_INLINE void IfxDma_setChannelHalt(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->TSR[channelId].B.HLTREQ = 1;
}


IFX_INLINE void IfxDma_setChannelInterruptServiceRequest(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCSR.B.SIT = 1;
}


IFX_INLINE void IfxDma_setChannelMoveSize(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelMoveSize moveSize)
{
    dma->CH[channelId].CHCFGR.B.CHDW = moveSize;
}


IFX_INLINE void IfxDma_setChannelShadow(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelShadow shadow)
{
    dma->CH[channelId].ADICR.B.SHCT = shadow;
}


IFX_INLINE void IfxDma_setChannelSingleMode(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCFGR.B.CHMODE = 0;
}


IFX_INLINE void IfxDma_setChannelSingleTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCFGR.B.RROAT = 1;
}


IFX_INLINE void IfxDma_setChannelSingleTransfer(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCFGR.B.RROAT = 0;
}


IFX_INLINE void IfxDma_setChannelSourceAddress(Ifx_DMA *dma, IfxDma_ChannelId channelId, const void *address)
{
    dma->CH[channelId].SADR.U = (uint32)address;
}


IFX_INLINE void IfxDma_setChannelSourceIncrementStep(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_ChannelIncrementStep incStep, IfxDma_ChannelIncrementDirection direction, IfxDma_ChannelIncrementCircular size)
{
    Ifx_DMA_CH_ADICR adicr;
    adicr.U                    = dma->CH[channelId].ADICR.U;
    adicr.B.SMF                = incStep;
    adicr.B.INCS               = direction;
    adicr.B.CBLS               = size;
    dma->CH[channelId].ADICR.U = adicr.U;
}


IFX_INLINE void IfxDma_setChannelSuspendEnable(Ifx_DMA *dma, IfxDma_ChannelId channelId, boolean enable)
{
    dma->SUSENR[channelId].B.SUSEN = enable;
}


IFX_INLINE void IfxDma_setChannelTransferCount(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint32 transferCount)
{
    dma->CH[channelId].CHCFGR.B.TREL = transferCount;
}


IFX_INLINE void IfxDma_setSleepMode(Ifx_DMA *dma, IfxDma_SleepMode mode)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
    IfxScuWdt_clearCpuEndinit(passwd);
    dma->CLC.B.EDIS = mode;
    IfxScuWdt_setCpuEndinit(passwd);
}


IFX_INLINE void IfxDma_startChannelTransaction(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCSR.B.SCH = 1;
}


IFX_INLINE void IfxDma_switchDoubleBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].CHCSR.B.SWB = 1;
}


IFX_INLINE void IfxDma_writeChannelShadowDisable(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.SHCT &= ~(3 << 2);
}


IFX_INLINE void IfxDma_writeChannelShadowEnable(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.SHCT |= (1 << 2);
    dma->CH[channelId].ADICR.B.SHCT &= ~(1 << 3);
}


IFX_INLINE void IfxDma_setChannelHardwareResourcePartition(Ifx_DMA *dma, IfxDma_ChannelId channelId, IfxDma_HardwareResourcePartition resourcePartition)
{
    uint16 endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPasswordInline();
    IfxScuWdt_clearSafetyEndinitInline(endinitSfty_pw);
    dma->HRR[channelId].B.HRP = resourcePartition;
    IfxScuWdt_setSafetyEndinitInline(endinitSfty_pw);
}


IFX_INLINE void IfxDma_setInterruptControlValue(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint8 value)
{
    dma->CH[channelId].ADICR.B.INTCT = value;
}


IFX_INLINE void IfxDma_setCircularBufferDestinationLength(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint16 length)
{
    dma->CH[channelId].ADICR.B.CBLD = length;
}


IFX_INLINE void IfxDma_setCircularBufferSourceLength(Ifx_DMA *dma, IfxDma_ChannelId channelId, uint16 length)
{
    dma->CH[channelId].ADICR.B.CBLS = length;
}


IFX_INLINE void IfxDma_enableSourceCircularBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.SCBE = 0x1U;
}


IFX_INLINE void IfxDma_enableDestinationCircularBuffer(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    dma->CH[channelId].ADICR.B.DCBE = 0x1U;
}


IFX_INLINE uint32 IfxDma_getDataCRC(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].RDCRCR.U;
}


IFX_INLINE uint32 IfxDma_getSourceAndDestinationCRC(Ifx_DMA *dma, IfxDma_ChannelId channelId)
{
    return dma->CH[channelId].SDCRCR.U;
}


IFX_INLINE volatile Ifx_SRC_SRCR *IfxDma_getErrPointer(Ifx_DMA *dma)
{
    return &MODULE_SRC.DMA.DMA[0].ERR;
}


#endif /* IFXDMA_H */
