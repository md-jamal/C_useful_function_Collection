/*
 * (C) Copyright 2000-2004
 * DENX Software Engineering
 * Wolfgang Denk, wd@denx.de
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "image.h"

char *cmdname;

typedef struct table_entry {
	int	val;		/* as defined in image.h	*/
	char	*sname;		/* short (input) name		*/
	char	*lname;		/* long (output) name		*/
} table_entry_t;

table_entry_t arch_name[] = {
    {	IH_CPU_INVALID,		NULL,		"Invalid CPU",	},
    {	IH_CPU_ALPHA,		"alpha",	"Alpha",	},
    {	IH_CPU_ARM,		"arm",		"ARM",		},
    {	IH_CPU_I386,		"x86",		"Intel x86",	},
    {	IH_CPU_IA64,		"ia64",		"IA64",		},
    {	IH_CPU_M68K,		"m68k",		"MC68000",	},
    {	IH_CPU_MICROBLAZE,	"microblaze",	"MicroBlaze",	},
    {	IH_CPU_MIPS,		"mips",		"MIPS",		},
    {	IH_CPU_MIPS64,		"mips64",	"MIPS 64 Bit",	},
    {	IH_CPU_NIOS,		"nios",		"NIOS",		},
    {	IH_CPU_NIOS2,		"nios2",	"NIOS II",	},
    {	IH_CPU_PPC,		"ppc",		"PowerPC",	},
    {	IH_CPU_S390,		"s390",		"IBM S390",	},
    {	IH_CPU_SH,		"sh",		"SuperH",	},
    {	IH_CPU_SPARC,		"sparc",	"SPARC",	},
    {	IH_CPU_SPARC64,		"sparc64",	"SPARC 64 Bit",	},
    {	IH_CPU_BLACKFIN,	"blackfin",	"Blackfin",	},
    {	IH_CPU_AVR32,		"avr32",	"AVR32",	},
    {	-1,			"",		"",		},
};


static	void	usage	(void);
static	int	get_table_entry (table_entry_t *, char *, char *);
static	int	get_arch(char *);

int opt_arch = IH_CPU_PPC;

int
main (int argc, char **argv)
{
	int ifd;
	uint32_t checksum;
	uint32_t addr;
	uint32_t ep;
	struct stat sbuf;
	unsigned char *ptr;
	char *name = "";

	cmdname = *argv;

	addr = ep = 0;

	while (--argc > 0 && **++argv == '-') {
		while (*++*argv) {
			switch (**argv) {
			case 'A':
				if ((--argc <= 0) ||
				    (opt_arch = get_arch(*++argv)) < 0)
					usage ();
				goto NXTARG;
			default:
				usage ();
			}
		}
NXTARG:		;
	}
printf(" opt_arch %d\n",opt_arch);
	exit (EXIT_SUCCESS);
}

void
usage ()
{
	fprintf (stderr, "          -A ==> set architecture to 'arch'\n"
		);
	exit (EXIT_FAILURE);
}

static int get_arch(char *name)
{
	return (get_table_entry(arch_name, "CPU", name));
}

static int get_table_entry (table_entry_t *table, char *msg, char *name)
{
	table_entry_t *t;
	int first = 1;

	for (t=table; t->val>=0; ++t) {
		if (t->sname && strcasecmp(t->sname, name)==0)
			return (t->val);
	}
	fprintf (stderr, "\nInvalid %s Type - valid names are", msg);
	for (t=table; t->val>=0; ++t) {
		if (t->sname == NULL)
			continue;
		fprintf (stderr, "%c %s", (first) ? ':' : ',', t->sname);
		first = 0;
	}
	fprintf (stderr, "\n");
	return (-1);
}
