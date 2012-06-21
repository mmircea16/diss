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
#define mu_test_title(test_title) do{printf("Test #%d:%s\n",tests_run,test_title);} while(0);
#define mu_assert_line(message , line_no , test) do { if (!(test)) {printf("Line number:%d\n",line_no);return message;} } while (0)
#define mu_assert(message , test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;if (message) return message; } while (0)
#define mu_final() printf("Result: OK\n\n")
extern int tests_run;

