/*
 * minunit.h
 *
 *  Created on: 24.05.2012
 *      Author: Mircea
 */

/* Credits to Jera Design: http://www.jera.com/techinfo/jtns/jtn002.html */

#ifndef MINUNIT_H_
#define MINUNIT_H_


#endif /* MINUNIT_H_ */
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;if (message) return message; } while (0)
 extern int tests_run;
