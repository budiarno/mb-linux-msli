/* iId: */
/******************************************************************************
*
*       XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"
*       AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND
*       SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,
*       OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,
*       APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION
*       THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,
*       AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE
*       FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY
*       WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE
*       IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR
*       REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF
*       INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*       FOR A PARTICULAR PURPOSE.
*
*       (c) Copyright 2004-2006 Xilinx Inc.
*       All rights reserved.
*
******************************************************************************/

/*****************************************************************************/
/**
 *
 * @file xlltemac_hw.h
 *
 * This header file contains identifiers and low-level driver functions (or
 * macros) that can be used to access the Tri-Mode MAC Ethernet (TEMAC) device.
 * High-level driver functions are defined in xlltemac.h.
 *
 * @note
 *
 * Some registers are not accessible when a HW instance is configured for SGDMA.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who  Date     Changes
 * ----------------------------------------------------------------------------
 * 1.00a jvb  11/10/06 First release
 * </pre>
 *
 ******************************************************************************/

#ifndef XTEMAC_HW_H		/* prevent circular inclusions */
#define XTEMAC_HW_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include <linux/jiffies.h>
#include "xbasic_types.h"
#include "xio.h"
#include "xdebug.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

#define XTE_RESET_HARD_DELAY_US 4    /**< Us to delay for hard core reset */

/* Register offset definitions. Unless otherwise noted, register access is
 * 32 bit.
 */

/** @name Direct registers
 *  @{
 */
#define XTE_RAF_OFFSET  XXXXXXXXXX /*0x00000000*/  /**< Reset and address filter */
#define XTE_TPF_OFFSET  XXXXXXXXXX /*0x00000004*/  /**< Transmit pause frame */
#define XTE_IFGP_OFFSET XXXXXXXXXX /*0x00000008*/  /**< Transmit inter-frame gap adjustment */
#define XTE_IS_OFFSET   XXXXXXXXXX /*0x0000000C*/  /**< Interrupt status */
#define XTE_IP_OFFSET   XXXXXXXXXX /*0x00000010*/  /**< Interrupt pending */
#define XTE_IE_OFFSET   XXXXXXXXXX /*0x00000014*/  /**< Interrupt enable */

#define XTE_MSW_OFFSET  XXXXXXXXXX /*0x00000020*/  /**< Most significant word data */
#define XTE_LSW_OFFSET  XXXXXXXXXX /*0x00000024*/  /**< Least significant word data */
#define XTE_CTL_OFFSET  XXXXXXXXXX /*0x00000028*/  /**< Control */
#define XTE_RDY_OFFSET  XXXXXXXXXX /*0x0000002C*/  /**< Ready status */
/*@}*/


/* 
 * Lab X Tri-mode MAC register definitions 
 * The first half of the address space maps to registers used for
 * PHY control and interrupts.  The second half is passed through to the
 * actual MAC registers.
 */
#define MDIO_CONTROL_REG      (0x00000000)
#  define PHY_MDIO_BUSY       (0x80000000)
#  define PHY_REG_ADDR_MASK   (0x01F)
#  define PHY_ADDR_MASK       (0x01F)
#  define PHY_ADDR_SHIFT      (5)
#  define PHY_MDIO_READ       (0x0400)
#  define PHY_MDIO_WRITE      (0x0000)
#  define PHY_10G_MDIO_WRITE  (0x0400)
#  define PHY_10G_MDIO_READ   (0x0C00)
#  define PHY_10G_MDIO_ADDR   (0x0000)
#  define PHY_10G_MDIO_RINC   (0x0800)
#define PHY_10G_DEVTYPE_MASK  (0x01F)
#define MDIO_DATA_REG         (0x00000004)
#  define PHY_DATA_MASK       (0x0000FFFF)
#define INT_MASK_REG          (0x00000008)
#  define PHY_IRQ_LOW         (0x00000000)
#  define PHY_IRQ_HIGH        (0x80000000)
#define INT_FLAGS_REG         (0x0000000C)
#  define NO_IRQS             (0x00000000)
#  define MDIO_IRQ_MASK       (0x00000001)
#  define PHY_IRQ_MASK        (0x00000002)

#define VLAN_MASK_REG         (0x00000010)
#define MAC_SELECT_REG        (0x00000014)
#define MAC_CONTROL_REG       (0x00000018)
#define   MAC_ADDRESS_LOAD_ACTIVE 0x00000100
#define   MAC_ADDRESS_LOAD_LAST   0x00000200
#define MAC_LOAD_REG          (0x0000001C)
#define BAD_PACKET_REG        (0x00000020)
#define REVISION_REG          (0x0000003C)
#  define REVISION_MINOR_MASK  0x0000000F
#  define REVISION_MINOR_SHIFT 0
#  define REVISION_MAJOR_MASK  0x000000F0
#  define REVISION_MAJOR_SHIFT 4
#  define REVISION_MATCH_MASK  0x0000FF00
#  define REVISION_MATCH_SHIFT 8


#define LABX_MAC_REGS_BASE    (0x00000200)

/* Timeout for any MDIO operation */
#define MDIO_TIMEOUT_JIFFIES  (msecs_to_jiffies(100))

/** @name HARD_TEMAC Core Registers
 * These are registers defined within the device's hard core located in the
 * processor block. They are accessed indirectly through the registers, MSW,
 * LSW, and CTL.
 *
 * Access to these registers should go through macros XLlTemac_ReadIndirectReg()
 * and XLlTemac_WriteIndirectReg() to guarantee proper access.
 * @{
 */
#ifdef CONFIG_LABX_ETH_LOCALLINK_HARD_MAC
#define XTE_RCW0_OFFSET         (LABX_MAC_REGS_BASE + 0x000) /**< Rx configuration word 0 */
#define XTE_RCW1_OFFSET         (LABX_MAC_REGS_BASE + 0x040) /**< Rx configuration word 1 */
#define XTE_TC_OFFSET           (LABX_MAC_REGS_BASE + 0x080) /**< Tx configuration */
#define XTE_EMMC_OFFSET         (LABX_MAC_REGS_BASE + 0x100) /**< EMAC mode configuration */
#define XTE_MC_OFFSET           (LABX_MAC_REGS_BASE + 0x140) /**< Management configuration */
#else
#define XTE_RCW0_OFFSET         (LABX_MAC_REGS_BASE + 0x000) /**< Rx configuration word 0 */
#define XTE_RCW1_OFFSET         (LABX_MAC_REGS_BASE + 0x004) /**< Rx configuration word 1 */
#define XTE_TC_OFFSET           (LABX_MAC_REGS_BASE + 0x008) /**< Tx configuration */
#define XTE_FCC_OFFSET          XXXXXXXXXX /*0x000002C0*/  /**< Flow control configuration */
#define XTE_EMMC_OFFSET         (LABX_MAC_REGS_BASE + 0x010) /**< EMAC mode configuration */
#define XTE_PHYC_OFFSET         XXXXXXXXXX /*0x00000320*/  /**< RGMII/SGMII configuration */
#define XTE_MC_OFFSET           (LABX_MAC_REGS_BASE + 0x014) /**< Management configuration */
#define XTE_UAW0_OFFSET         XXXXXXXXXX /*0x00000380*/  /**< Unicast address word 0 */
#define XTE_UAW1_OFFSET         XXXXXXXXXX /*0x00000384*/  /**< Unicast address word 1 */
#define XTE_MAW0_OFFSET         XXXXXXXXXX /*0x00000388*/  /**< Multicast address word 0 */
#define XTE_MAW1_OFFSET         XXXXXXXXXX /*0x0000038C*/  /**< Multicast address word 1 */
#define XTE_AFM_OFFSET          XXXXXXXXXX /*0x00000390*/  /**< Address Filter (promiscuous) mode */
#define XTE_TIS_OFFSET          XXXXXXXXXX /*0x000003A0*/  /**< Interrupt status */
#define XTE_TIE_OFFSET          XXXXXXXXXX /*0x000003A4*/  /**< Interrupt enable */
#define XTE_MIIMWD_OFFSET       XXXXXXXXXX /*0x000003B0*/  /**< MII management write data */
#define XTE_MIIMAI_OFFSET       XXXXXXXXXX /*0x000003B4*/  /**< MII management access initiate */
#endif

#define FILTER_0_AW0 0x3000
#define FILTER_0_AW1 0x3004
#define FILTER_0_EN0 0x3010
#define FILTER_0_EN1 0x3014
#define FILTER_1_AW0 0x3020
#define FILTER_1_AW1 0x3024
#define FILTER_1_EN0 0x3030
#define FILTER_1_EN1 0x3034
#define FILTER_2_AW0 0x3040
#define FILTER_2_AW1 0x3044
#define FILTER_2_EN0 0x3050
#define FILTER_2_EN1 0x3054
/*@}*/


/* Register masks. The following constants define bit locations of various
 * control bits in the registers. Constants are not defined for those registers
 * that have a single bit field representing all 32 bits. For further
 * information on the meaning of the various bit masks, refer to the HW spec.
 */

/** @name Reset and Address Filter bits
 *  These bits are associated with the XTE_RAF_OFFSET register.
 * @{
 */
#define XTE_RAF_HTRST_MASK       0x00000001 /**< Hard TEMAC Reset */
#define XTE_RAF_MCSTREJ_MASK     0x00000002 /**< Reject receive multicast destination address */
#define XTE_RAF_BCSTREJ_MASK     0x00000004 /**< Reject receive broadcast destination address */
/*@}*/

/** @name Transmit Pause Frame Register (TPF)
 *  @{
 */
#define XTE_TPF_TPFV_MASK        0x0000FFFF   /**< Tx pause frame value */
/*@}*/

/** @name Transmit Inter-Frame Gap Adjustement Register (TFGP)
 *  @{
 */
#define XTE_TFGP_IFGP_MASK       0x0000007F   /**< Transmit inter-frame gap adjustment value */
/*@}*/

/** @name Interrupt bits
 *  These bits are associated with the XTE_IS_OFFSET, XTE_IP_OFFSET, and
 *  XTE_IE_OFFSET registers.
 * @{
 */
#define XTE_INT_HARDACSCMPLT_MASK 0x00000001 /**< Hard register access complete */
#define XTE_INT_AUTONEG_MASK      0x00000002 /**< Auto negotiation complete */
#define XTE_INT_RC_MASK           0x00000004 /**< Receive complete */
#define XTE_INT_RXRJECT_MASK      0x00000008 /**< Receive frame rejected */
#define XTE_INT_RXFIFOOVR_MASK    0x00000010 /**< Receive fifo overrun */
#define XTE_INT_TC_MASK           0x00000020 /**< Transmit complete */
#define XTE_INT_ALL_MASK          0x0000003f /**< All the ints */
/*@}*/


#define XTE_INT_RECV_ERROR_MASK \
    (XTE_INT_RXRJECT_MASK | XTE_INT_RXFIFOOVR_MASK) /**< INT bits that indicate receive errors */
/*@}*/


/** @name Control Register (CTL)
 *  @{
 */
#define XTE_CTL_WEN_MASK          0x00008000   /**< Write Enable */
/*@}*/


/** @name Ready Status, TEMAC Interrupt Status, TEMAC Interrupt Enable Registers
 * (RDY, TIS, TIE)
 *  @{
 */
#define XTE_RSE_FABR_RR_MASK      0x00000001   /**< Fabric read ready */
#define XTE_RSE_MIIM_RR_MASK      0x00000002   /**< MII management read ready */
#define XTE_RSE_MIIM_WR_MASK      0x00000004   /**< MII management write ready */
#define XTE_RSE_AF_RR_MASK        0x00000008   /**< Address filter read ready*/
#define XTE_RSE_AF_WR_MASK        0x00000010   /**< Address filter write ready*/
#define XTE_RSE_CFG_RR_MASK       0x00000020   /**< Configuration register read ready*/
#define XTE_RSE_CFG_WR_MASK       0x00000040   /**< Configuration register write ready*/
#define XTE_RDY_HARD_ACS_RDY_MASK 0x00010000   /**< Hard register access ready */
#define XTE_RDY_ALL               (XTE_RSE_FABR_RR_MASK | \
                                   XTE_RSE_MIIM_RR_MASK | \
                                   XTE_RSE_MIIM_WR_MASK | \
                                   XTE_RSE_AF_RR_MASK | \
                                   XTE_RSE_AF_WR_MASK | \
                                   XTE_RSE_CFG_RR_MASK | \
                                   XTE_RSE_CFG_WR_MASK | \
                                   XTE_RDY_HARD_ACS_RDY_MASK)
/*@}*/


/** @name Receive Configuration Word 1 (RCW1)
 *  @{
 */
#define XTE_RCW1_RST_MASK         0x80000000   /**< Reset */
#define XTE_RCW1_JUM_MASK         0x40000000   /**< Jumbo frame enable */
#define XTE_RCW1_FCS_MASK         0x20000000   /**< In-Band FCS enable (FCS not stripped) */
#define XTE_RCW1_RX_MASK          0x10000000   /**< Receiver enable */
#define XTE_RCW1_VLAN_MASK        0x08000000   /**< VLAN frame enable */
#define XTE_RCW1_HD_MASK          0x04000000   /**< Half duplex mode */
#define XTE_RCW1_LT_DIS_MASK      0x02000000   /**< Length/type field valid check disable */
#define XTE_RCW1_PAUSEADDR_MASK   0x0000FFFF   /**< Pause frame source address
                                                    bits [47:32]. Bits [31:0]
                                                    are stored in register
                                                    RCW0 */
/*@}*/


/** @name Transmitter Configuration (TC)
 *  @{
 */
#define XTE_TC_RST_MASK           0x80000000   /**< reset */
#define XTE_TC_JUM_MASK           0x40000000   /**< Jumbo frame enable */
#define XTE_TC_FCS_MASK           0x20000000   /**< In-Band FCS enable (FCS not generated) */
#define XTE_TC_TX_MASK            0x10000000   /**< Transmitter enable */
#define XTE_TC_VLAN_MASK          0x08000000   /**< VLAN frame enable */
#define XTE_TC_HD_MASK            0x04000000   /**< Half duplex mode */
#define XTE_TC_IFG_MASK           0x02000000   /**< Inter-frame gap adjustment enable */
/*@}*/


/** @name Flow Control Configuration (FCC)
 *  @{
 */
#define XTE_FCC_FCRX_MASK         0x20000000   /**< Rx flow control enable */
#define XTE_FCC_FCTX_MASK         0x40000000   /**< Tx flow control enable */
/*@}*/


/** @name EMAC Configuration (EMMC)
 * @{
 */
#define XTE_EMMC_LINKSPEED_MASK   0xC0000000  /**< Link speed */
#define XTE_EMMC_RGMII_MASK       0x20000000  /**< RGMII mode enable */
#define XTE_EMMC_SGMII_MASK       0x10000000  /**< SGMII mode enable */
#define XTE_EMMC_GPCS_MASK        0x08000000  /**< 1000BaseX mode enable */
#define XTE_EMMC_HOST_MASK        0x04000000  /**< Host interface enable */
#define XTE_EMMC_TX16BIT          0x02000000  /**< 16 bit Tx client enable */
#define XTE_EMMC_RX16BIT          0x01000000  /**< 16 bit Rx client enable */

#define XTE_EMMC_LINKSPD_10       0x00000000   /**< XTE_EMCFG_LINKSPD_MASK for
                                                     10 Mbit */
#define XTE_EMMC_LINKSPD_100      0x40000000   /**< XTE_EMCFG_LINKSPD_MASK for
                                                     100 Mbit */
#define XTE_EMMC_LINKSPD_1000     0x80000000   /**< XTE_EMCFG_LINKSPD_MASK for
                                                     1000 Mbit */
/*@}*/


/** @name EMAC RGMII/SGMII Configuration (PHYC)
 * @{
 */
#define XTE_PHYC_SGMIILINKSPEED_MASK 0xC0000000	  /**< SGMII link speed */
#define XTE_PHYC_RGMIILINKSPEED_MASK 0x0000000C	  /**< RGMII link speed */
#define XTE_PHYC_RGMIIHD_MASK        0x00000002	  /**< RGMII Half-duplex mode */
#define XTE_PHYC_RGMIILINK_MASK      0x00000001	  /**< RGMII link status */

#define XTE_PHYC_RGLINKSPD_10        0x00000000	  /**< XTE_GMIC_RGLINKSPD_MASK
                                                       for 10 Mbit */
#define XTE_PHYC_RGLINKSPD_100       0x40000000	  /**< XTE_GMIC_RGLINKSPD_MASK
                                                       for 100 Mbit */
#define XTE_PHYC_RGLINKSPD_1000      0x80000000	  /**< XTE_GMIC_RGLINKSPD_MASK
                                                       for 1000 Mbit */
#define XTE_PHYC_SGLINKSPD_10        0x00000000	  /**< XTE_SGMIC_RGLINKSPD_MASK
                                                       for 10 Mbit */
#define XTE_PHYC_SGLINKSPD_100       0x00000004	  /**< XTE_SGMIC_RGLINKSPD_MASK
                                                       for 100 Mbit */
#define XTE_PHYC_SGLINKSPD_1000      0x00000008	  /**< XTE_SGMIC_RGLINKSPD_MASK
                                                       for 1000 Mbit */
/*@}*/


/** @name EMAC Management Configuration (MC)
 * @{
 */
#define XTE_MC_MDIOEN_MASK        0x00000040   /**< MII management enable */
#define XTE_MC_CLOCK_DIVIDE_MAX   0x3F	       /**< Maximum MDIO divisor */
/*@}*/


/** @name EMAC Unicast Address Register Word 1 (UAW1)
 * @{
 */
#define XTE_UAW1_UNICASTADDR_MASK 0x0000FFFF   /**< Station address bits [47:32]
                                                    Station address bits [31:0]
                                                    are stored in register
                                                    UAW0 */
/*@}*/


/** @name EMAC Multicast Address Register Word 1 (MAW1)
 * @{
 */
#define XTE_MAW1_RNW_MASK         0x00800000   /**< Multicast address table register read enable */
#define XTE_MAW1_ADDR_MASK        0x00030000   /**< Multicast address table register address */
#define XTE_MAW1_MULTICADDR_MASK  0x0000FFFF   /**< Multicast address bits [47:32]
                                                    Multicast address bits [31:0]
                                                    are stored in register
                                                    MAW0 */
#define XTE_MAW1_MATADDR_SHIFT_MASK 16	       /**< Number of bits to shift right
                                                    to align with
                                                    XTE_MAW1_CAMADDR_MASK */
/*@}*/


/** @name EMAC Address Filter Mode (AFM)
 * @{
 */
#define XTE_AFM_PM_MASK           0x00010000 /*0x80000000*/   /**< Promiscuous mode enable */
#define XTE_AFM_VLAN_A_MASK       0x00000007
#define XTE_AFM_VLAN_B_MASK       0x00000700
/*@}*/


/** @name Media Independent Interface Management (MIIM)
 * @{
 */
#define XTE_MIIM_REGAD_MASK     0x1F	/**< MII Phy register address (REGAD) */
#define XTE_MIIM_PHYAD_MASK     0x03E0	/**< MII Phy address (PHYAD) */
#define XTE_MIIM_PHYAD_SHIFT    5	/**< MII Shift bits for PHYAD */
/*@}*/


/** @name Checksum offload buffer descriptor extensions
 * @{
 */
/** Byte offset where checksum should begin (16 bit word) */
#define XTE_BD_TX_CSBEGIN_OFFSET  XDMAV3_BD_USR0_OFFSET

/** Offset where checksum should be inserted (16 bit word) */
#define XTE_BD_TX_CSINSERT_OFFSET (XDMAV3_BD_USR0_OFFSET + 2)

/** Checksum offload control for transmit (16 bit word) */
#define XTE_BD_TX_CSCNTRL_OFFSET  XDMAV3_BD_USR1_OFFSET

/** Seed value for checksum calculation (16 bit word) */
#define XTE_BD_TX_CSINIT_OFFSET   (XDMAV3_BD_USR1_OFFSET + 2)

/** Receive frame checksum calculation (16 bit word) */
#define XTE_BD_RX_CSRAW_OFFSET    (XDMAV3_BD_USR5_OFFSET + 2)

/*@}*/

/** @name TX_CSCNTRL bit mask
 * @{
 */
#define XTE_BD_TX_CSCNTRL_CALC_MASK  0x0001  /**< Enable/disable Tx
                                                  checksum */
/*@}*/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
xdbg_stmnt(extern int indent_on);

#define XLlTemac_indent(RegOffset) \
 ((indent_on && ((RegOffset) >= XTE_RAF_OFFSET) && ((RegOffset) <= XTE_RDY_OFFSET)) ? "\t" : "")

#define XLlTemac_reg_name(RegOffset) \
	(((RegOffset) == XTE_RAF_OFFSET) ? "XTE_RAF_OFFSET": \
	((RegOffset) == XTE_TPF_OFFSET) ? "XTE_TPF_OFFSET": \
	((RegOffset) == XTE_IFGP_OFFSET) ? "XTE_IFGP_OFFSET": \
	((RegOffset) == XTE_IS_OFFSET) ? "XTE_IS_OFFSET": \
	((RegOffset) == XTE_IP_OFFSET) ? "XTE_IP_OFFSET": \
	((RegOffset) == XTE_IE_OFFSET) ? "XTE_IE_OFFSET": \
	((RegOffset) == XTE_MSW_OFFSET) ? "XTE_MSW_OFFSET": \
	((RegOffset) == XTE_LSW_OFFSET) ? "XTE_LSW_OFFSET": \
	((RegOffset) == XTE_CTL_OFFSET) ? "XTE_CTL_OFFSET": \
	((RegOffset) == XTE_RDY_OFFSET) ? "XTE_RDY_OFFSET": \
	((RegOffset) == XTE_RCW0_OFFSET) ? "XTE_RCW0_OFFSET": \
	((RegOffset) == XTE_RCW1_OFFSET) ? "XTE_RCW1_OFFSET": \
	((RegOffset) == XTE_TC_OFFSET) ? "XTE_TC_OFFSET": \
	((RegOffset) == XTE_FCC_OFFSET) ? "XTE_FCC_OFFSET": \
	((RegOffset) == XTE_EMMC_OFFSET) ? "XTE_EMMC_OFFSET": \
	((RegOffset) == XTE_PHYC_OFFSET) ? "XTE_PHYC_OFFSET": \
	((RegOffset) == XTE_MC_OFFSET) ? "XTE_MC_OFFSET": \
	((RegOffset) == XTE_UAW0_OFFSET) ? "XTE_UAW0_OFFSET": \
	((RegOffset) == XTE_UAW1_OFFSET) ? "XTE_UAW1_OFFSET": \
	((RegOffset) == XTE_MAW0_OFFSET) ? "XTE_MAW0_OFFSET": \
	((RegOffset) == XTE_MAW1_OFFSET) ? "XTE_MAW1_OFFSET": \
	((RegOffset) == XTE_AFM_OFFSET) ? "XTE_AFM_OFFSET": \
	((RegOffset) == XTE_TIS_OFFSET) ? "XTE_TIS_OFFSET": \
	((RegOffset) == XTE_TIE_OFFSET) ? "XTE_TIE_OFFSET": \
	((RegOffset) == XTE_MIIMWD_OFFSET) ? "XTE_MIIMWD_OFFSET": \
	((RegOffset) == XTE_MIIMAI_OFFSET) ? "XTE_MIIMAI_OFFSET": \
	"unknown")

#define XLlTemac_print_reg_o(BaseAddress, RegOffset, Value) \
	xdbg_printf(XDBG_DEBUG_TEMAC_REG, "%s0x%0x -> %s(0x%0x)\n", \
			XLlTemac_indent(RegOffset), (Value), \
			XLlTemac_reg_name(RegOffset), (RegOffset)) \

#define XLlTemac_print_reg_i(BaseAddress, RegOffset, Value) \
	xdbg_printf(XDBG_DEBUG_TEMAC_REG, "%s%s(0x%0x) -> 0x%0x\n", \
			XLlTemac_indent(RegOffset), XLlTemac_reg_name(RegOffset), \
			(RegOffset), (Value)) \

/****************************************************************************/
/**
 *
 * XLlTemac_ReadReg returns the value read from the register specified by
 * <i>RegOffset</i>.
 *
 * @param    BaseAddress is the base address of the TEMAC channel.
 * @param    RegOffset is the offset of the register to be read.
 *
 * @return   XLlTemac_ReadReg returns the 32-bit value of the register.
 *
 * @note
 * C-style signature:
 *    u32 XLlTemac_mReadReg(u32 BaseAddress, u32 RegOffset)
 *
 *****************************************************************************/
#ifdef DEBUG
#define XLlTemac_ReadReg(BaseAddress, RegOffset) \
({ \
	u32 value; \
	value = XIo_In32(((BaseAddress) + (RegOffset))); \
	XLlTemac_print_reg_i((BaseAddress), (RegOffset), value); \
	value; \
})
#else
#define XLlTemac_ReadReg(BaseAddress, RegOffset) \
	(XIo_In32(((BaseAddress) + (RegOffset))))
#endif

/****************************************************************************/
/**
 *
 * XLlTemac_WriteReg, writes <i>Data</i> to the register specified by
 * <i>RegOffset</i>.
 *
 * @param    BaseAddress is the base address of the TEMAC channel.
 * @param    RegOffset is the offset of the register to be written.
 * @param    Data is the 32-bit value to write to the register.
 *
 * @return   N/A
 *
 * @note
 * C-style signature:
 *    void XLlTemac_mWriteReg(u32 BaseAddress, u32 RegOffset, u32 Data)
 *
 *****************************************************************************/
#ifdef DEBUG
#define XLlTemac_WriteReg(BaseAddress, RegOffset, Data) \
({ \
	XLlTemac_print_reg_o((BaseAddress), (RegOffset), (Data)); \
	XIo_Out32(((BaseAddress) + (RegOffset)), (Data)); \
})
#else
#define XLlTemac_WriteReg(BaseAddress, RegOffset, Data) \
	XIo_Out32(((BaseAddress) + (RegOffset)), (Data))
#endif

/****************************************************************************/
/**
 *
 * XLlTemac_ReadIndirectReg returns the value read from the hard TEMAC register
 * specified by <i>RegOffset</i>.
 *
 * @param    BaseAddress is the base address of the TEMAC channel.
 * @param    RegOffset is the offset of the hard TEMAC register to be read.
 *
 * @return   XLlTemac_ReadIndirectReg returns the 32-bit value of the register.
 *
 * @note
 * C-style signature:
 *    u32 XLlTemac_mReadIndirectReg(u32 BaseAddress, u32 RegOffset)
 *
 *****************************************************************************/
#ifdef DEBUG
extern u32 _xlltemac_rir_value;

#define XLlTemac_ReadIndirectReg(BaseAddress, RegOffset) \
( \
	indent_on = 1, \
	_xlltemac_rir_value = XLlTemac_ReadReg((BaseAddress), (RegOffset)), \
	XLlTemac_print_reg_i((BaseAddress), (RegOffset), _xlltemac_rir_value), \
	indent_on = 0, \
	_xlltemac_rir_value \
)
#else
#define XLlTemac_ReadIndirectReg(BaseAddress, RegOffset) \
( \
	XLlTemac_ReadReg((BaseAddress),(RegOffset)) \
)
#endif

/****************************************************************************/
/**
 *
 * XLlTemac_WriteIndirectReg, writes <i>Data</i> to the hard TEMAC register
 * specified by <i>RegOffset</i>.
 *
 * @param    BaseAddress is the base address of the TEMAC channel.
 * @param    RegOffset is the offset of the hard TEMAC register to be written.
 * @param    Data is the 32-bit value to write to the register.
 *
 * @return   N/A
 *
 * @note
 * C-style signature:
 *    void XLlTemac_WriteIndirectReg(u32 BaseAddress, u32 RegOffset, u32 Data)
 *
 *****************************************************************************/
#ifdef DEBUG
#define XLlTemac_WriteIndirectReg(BaseAddress, RegOffset, Data) \
( \
	indent_on = 1, \
	XLlTemac_print_reg_o((BaseAddress), (RegOffset), (Data)), \
	XLlTemac_WriteReg((BaseAddress), (RegOffset), (Data)), \
	indent_on = 0 \
)
#else
#define XLlTemac_WriteIndirectReg(BaseAddress, RegOffset, Data) \
	XLlTemac_WriteReg((BaseAddress), (RegOffset), (Data))
#endif

#ifdef __cplusplus
  }
#endif

#endif /* end of protection macro */
