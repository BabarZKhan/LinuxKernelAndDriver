/*************************************************************************\
 *                  Copyright (C) Michael Kerrisk, 2014.                   *
 *                                                                         *
 * This program is free software. You may use, modify, and redistribute it *
 * under the terms of the GNU Affero General Public License as published   *
 * by the Free Software Foundation, either version 3 or (at your option)   *
 * any later version. This program is distributed without any warranty.    *
 * See the file COPYING.agpl-v3 for details.                               *
 \*************************************************************************/

/* t_execve.c

   Demonstrate the use of execve() to execute a program.
   */
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	char *argVec[10];           /* Larger than required */
	char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

	if (argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname\n", argv[0]);

	/* Create an argument list for the new program */

	argVec[0] = strrchr(argv[1], '/');      /* Get basename from argv[1] */
	if (argVec[0] != NULL)
		argVec[0]++;
	else
		argVec[0] = argv[1];
	argVec[1] = "hello world";
	argVec[2] = "goodbye";
	argVec[3] = NULL;           /* List must be NULL-terminated */

	/* Execute the program specified in argv[1] */

	execve(argv[1], argVec, envVec);
	errExit("execve");          /* If we get here, something went wrong */
}
/*
output:
gerryyang@mba:procexec$./t_execve envargs
argv[0] = envargs
argv[1] = hello world
argv[2] = goodbye
environ: GREET=salut
environ: BYE=adieu
gerryyang@mba:procexec$./t_execve ./envargs
argv[0] = envargs
argv[1] = hello world
argv[2] = goodbye
environ: GREET=salut
environ: BYE=adieu
gerryyang@mba:procexec$./t_execve ../../envargs
ERROR [ENOENT No such file or directory] execve
 */
