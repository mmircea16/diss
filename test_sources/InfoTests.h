/*
 * InfoTests.h
 *
 *  Created on: 30 May 2012
 *      Author: moisem
 */

#include "minunit.h"



#ifndef INFOTESTS_H_
#define INFOTESTS_H_


#endif /* INFOTESTS_H_ */


char* test_has_error()
{
	mu_test_title("Has error");

	_Error* err;
    init_err(err);

	mu_assert("error: init has error",has_error(err)==0);

	err->code=12;
	mu_assert("error: after modification has error failed",has_error(err));

	mu_final();
	return 0;
}

char * test_overflow()
{
	mu_test_title("Overflow setter and getter");

	_Error* err;
	init_err(err);

	mu_assert("error: init overflow",get_overflow(err)==0);

	set_overflow(err);
	mu_assert("error: set overflow",get_overflow(err));

	reset_overflow(err);
    mu_assert("error: reset overflow",get_overflow(err)==0);

	mu_final();
	return 0;
}

char * test_misrepresentation()
{
	mu_test_title("misrepresentation setter and getter");

	_Error* err;
	init_err(err);

	mu_assert("error: init misrepresentation",get_misrepresentation(err)==0);

	set_misrepresentation(err);
	mu_assert("error: set misrepresentation",get_misrepresentation(err));

	reset_misrepresentation(err);
    mu_assert("error: reset misrepresentation",get_misrepresentation(err)==0);

	mu_final();
	return 0;
}

char * all_tests_info() {
     mu_run_test(test_overflow);
     mu_run_test(test_misrepresentation);
     mu_run_test(test_has_error);
     return 0;
 }
