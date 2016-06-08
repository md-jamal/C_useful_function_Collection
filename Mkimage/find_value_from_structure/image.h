/*
 * (C) Copyright 2000-2005
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 ********************************************************************
 * NOTE: This header file defines an interface to U-Boot. Including
 * this (unmodified) header file in another file is considered normal
 * use of U-Boot, and does *not* fall under the heading of "derived
 * work".
 ********************************************************************
 */

#ifndef __IMAGE_H__
#define __IMAGE_H__

typedef         unsigned char   uint8_t;
typedef         unsigned short  uint16_t;
typedef         unsigned int    uint32_t;

/*
 * CPU Architecture Codes (supported by Linux)
 */
#define IH_CPU_INVALID		0	/* Invalid CPU	*/
#define IH_CPU_ALPHA		1	/* Alpha	*/
#define IH_CPU_ARM		2	/* ARM		*/
#define IH_CPU_I386		3	/* Intel x86	*/
#define IH_CPU_IA64		4	/* IA64		*/
#define IH_CPU_MIPS		5	/* MIPS		*/
#define IH_CPU_MIPS64		6	/* MIPS	 64 Bit */
#define IH_CPU_PPC		7	/* PowerPC	*/
#define IH_CPU_S390		8	/* IBM S390	*/
#define IH_CPU_SH		9	/* SuperH	*/
#define IH_CPU_SPARC		10	/* Sparc	*/
#define IH_CPU_SPARC64		11	/* Sparc 64 Bit */
#define IH_CPU_M68K		12	/* M68K		*/
#define IH_CPU_NIOS		13	/* Nios-32	*/
#define IH_CPU_MICROBLAZE	14	/* MicroBlaze   */
#define IH_CPU_NIOS2		15	/* Nios-II	*/
#define IH_CPU_BLACKFIN		16	/* Blackfin	*/
#define IH_CPU_AVR32		17	/* AVR32	*/

#endif	/* __IMAGE_H__ */
