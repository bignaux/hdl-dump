/*
 * net_io.h
 * $Id: net_io.h,v 1.4 2004/09/26 19:39:40 b081 Exp $
 *
 * Copyright 2004 Bobi B., w1zard0f07@yahoo.com
 *
 * This file is part of hdl_dump.
 *
 * hdl_dump is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * hdl_dump is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with hdl_dump; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#if !defined (_NET_IO_H)
#define _NET_IO_H

#include <stddef.h>


#define NET_HIO_SERVER_PORT 0x8081  /* port where server would listen */

/* commands */
#define CMD_HIO_STAT          0x73746174 /* 'stat'; return HDD unit size in sectors */
#define CMD_HIO_READ          0x72656164 /* 'read'; read sectors from the HDD unit */
#define CMD_HIO_WRITE         0x77726974 /* 'writ'; write sectors to the HDD unit */
#define CMD_HIO_WRITE_NACK    0x7772696e /* 'wrin'; write sectors to the HDD with no ACK */
#define CMD_HIO_WRITE_RACK    0x77726972 /* 'wrir'; send dummy ACK 1st, then write sectors */
#define CMD_HIO_WRITE_QACK    0x77726971 /* 'wriq'; send dummy ACK before decompr. */
#define CMD_HIO_FLUSH         0x666c7368 /* 'flsh'; flush write buff (svr's hio is persistent) */
#define CMD_HIO_G_TCPNODELAY  0x67746e64 /* 'gtnd'; get remote TCP_NODELAY sock option */
#define CMD_HIO_S_TCPNODELAY  0x73746e64 /* 'stnd'; set remote TCP_NODELAY sock option */
#define CMD_HIO_G_ACKNODELAY  0x67616e64 /* 'gand'; get remote ACK_NODELAY sock option */
#define CMD_HIO_S_ACKNODELAY  0x73616e64 /* 'sand'; set remote ACK_NODELAY sock option */
#define CMD_HIO_POWEROFF      0x706f7778 /* 'powx'; poweroff system */

#define HDD_SECTOR_SIZE 512    /* HDD sector size in bytes */
#define HDD_NUM_SECTORS  32    /* number of sectors to write at once */
#define NET_NUM_SECTORS  32    /* max number of sectors to transfer via network at once */
#define NET_IO_CMD_LEN (4 * 4) /* command length in bytes in networking I/O */

#if (NET_NUM_SECTORS > 255)
/* that is because of compression during network transfers */
#  error NET_NUM_SECTORS should fit in a byte (that is < 256).
#endif

#if (HDD_SECTOR_SIZE * NET_NUM_SECTORS + NET_IO_CMD_LEN > 65536)
#  error One should not send more than 64KB via network at once.
#endif


/* pack & unpack doublewords */
unsigned long get_ulong (const void *buffer);

void put_ulong (void *buffer,
		unsigned long val);

void rle_compress (const unsigned char *input,
		   size_t ilength,
		   unsigned char *output,
		   size_t *olength); /* should have at least one byte extra for each 128 bytes */

void rle_expand (const unsigned char *input,
		 size_t ilength,
		 unsigned char *output,
		 size_t *olength);

#endif /* _NET_IO_H defined? */