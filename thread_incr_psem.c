/*************************************************************************\
 * *                  Copyright (C) Michael Kerrisk, 2022.                   *
 * *                                                                         *
 * * This program is free software. You may use, modify, and redistribute it *
 * * under the terms of the GNU General Public License as published by the   *
 * * Free Software Foundation, either version 3 or (at your option) any      *
 * * later version. This program is distributed without any warranty.  See   *
 * * the file COPYING.gpl-v3 for details.                                    *
 * \*************************************************************************/

/* thread_incr_psem.c
 *
 *    Use a POSIX unnamed semaphore to synchronize access by two threads to
 *       a global variable.
 *
 *          See also thread_incr.c and thread_incr_mutex.c.
 *             
 *                Code addapted by Christan Grant.
 *                */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>

#define GN_NONNEG       01      /* Value must be >= 0 */
#define GN_GT_0         02      /* Value must be > 0 */

/* By default, integers are decimal */
#define GN_ANY_BASE   0100      /* Can use any base - like strtol(3) */
#define GN_BASE_8     0200      /* Value is expressed in octal */
#define GN_BASE_16    0400      /* Value is expressed in hexadecimal */

static int glob = 0;
static sem_t sem;

static long
getNum(const char *fname, const char *arg, int flags, const char *name);

static void *                   /* Loop 'arg' times incrementing 'glob' */
threadFunc(void *arg) {
	int loops = *((int *) arg);
	int loc, j;

	for (j = 0; j < loops; j++) {
		if (sem_wait(&sem) == -1)
			perror("sem_wait");

		loc = glob;
		loc++;
		glob = loc;

		if (sem_post(&sem) == -1)
			perror("sem_post");
	}

	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t1, t2;
	int loops, s;

	loops = (argc > 1) ? getNum("getInt", argv[1], GN_GT_0, "num-loops") : 10000000;

	/* Initialize a semaphore with the value 1 */

	if (sem_init(&sem, 0, 1) == -1)
		perror("sem_init");

	/* Create two threads that increment 'glob' */

	s = pthread_create(&t1, NULL, threadFunc, &loops);
	if (s != 0)
		perror("pthread_create");
	s = pthread_create(&t2, NULL, threadFunc, &loops);
	if (s != 0)
		perror("pthread_create");

	/* Wait for threads to terminate */

	s = pthread_join(t1, NULL);
	if (s != 0)
		perror("pthread_join");
	s = pthread_join(t2, NULL);
	if (s != 0)
		perror("pthread_join");

	printf("glob = %d\n", glob);
	exit(EXIT_SUCCESS);
}


static long getNum(const char *fname, const char *arg, int flags, const char *name) {
	long res;
	char *endptr;
	int base;

	if (arg == NULL || *arg == '\0')
		perror("null or empty string");

	base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
		(flags & GN_BASE_16) ? 16 : 10;

	errno = 0;
	res = strtol(arg, &endptr, base);
	if (errno != 0)
		perror("strtol() failed");

	if (*endptr != '\0')
		perror("nonnumeric characters");

	if ((flags & GN_NONNEG) && res < 0)
		perror("negative value not allowed");

	if ((flags & GN_GT_0) && res <= 0)
		perror("value must be > 0");

	return res;
}
