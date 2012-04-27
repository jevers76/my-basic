/*
** This source file is part of MY-BASIC
**
** For the latest info, see http://code.google.com/p/my-basic/
**
** Copyright (c) 2011 - 2012 Tony & Tony's Toy Game Development Team
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of
** this software and associated documentation files (the "Software"), to deal in
** the Software without restriction, including without limitation the rights to
** use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
** the Software, and to permit persons to whom the Software is furnished to do so,
** subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
** FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
** COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
** IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
** CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifdef _MSC_VER
#	ifndef _CRT_SECURE_NO_WARNINGS
#		define _CRT_SECURE_NO_WARNINGS
#	endif /* _CRT_SECURE_NO_WARNINGS */
#endif /* _MSC_VER */

#ifdef _MSC_VER
#	include <crtdbg.h>
#	include <conio.h>
#endif /* _MSC_VER */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../core/my_basic.h"

#define _MAX_LINE_LENGTH 256
#define _str_eq(__str1, __str2) (_strcmpi(__str1, __str2) == 0)

static mb_interpreter_t* bas = 0;

static int beep(mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;

	assert(s && l);

	putchar('\a');

	return result;
}

static void _on_error(mb_interpreter_t* s, mb_error_e e, char* m, int p) {
	if(SE_NO_ERR != e) {
		printf("Error : [POS] %d, [CODE] %d, [MESSAGE] %s\n", p, e, m);
	}
}

static void _on_startup(void) {
	mb_init();

	mb_open(&bas);
	mb_set_error_handler(bas, _on_error);

	mb_reg_fun(bas, beep);
}

static void _on_exit(void) {
	mb_close(&bas);

	mb_dispose();

#ifdef _MSC_VER
	if(0 != _CrtDumpMemoryLeaks()) { _asm { int 3 } }
#endif /* _MSC_VER */
}

static void _clear_screen(void) {
#ifdef _MSC_VER
	system("cls");
#else
	system("clear");
#endif
}

static void _show_tip(void) {
	printf("MY-BASIC Interpreter Shell - %s\n", mb_ver_string());
	printf("Copyright (c) 2011 - 2012 Tony's Toy. All Rights Reserved.\n");
	printf("For more information, see http://code.google.com/p/my-basic/\n");
	printf("Input HELP and hint enter to view help information\n");
}

static void _show_help(void) {
	printf("Usage:\n");
	printf("  CLS   - Clear screen\n");
	printf("  NEW   - Clear current program\n");
	printf("  RUN   - Run current program\n");
	printf("  BYE   - Quit interpreter\n");
}

static int _do_line(void) {
	int result = MB_FUNC_OK;
	char line[_MAX_LINE_LENGTH];

	assert(bas);

	printf("]");
	gets(line);

	if(_str_eq(line, "")) {
		/* Do nothing */
	} else if(_str_eq(line, "HELP")) {
		_show_help();
	} else if(_str_eq(line, "BYE")) {
		result = MB_FUNC_END;
	} else if(_str_eq(line, "NEW")) {
		result = mb_reset(&bas, false);
	} else if(_str_eq(line, "RUN")) {
		result = mb_run(bas);
		printf("\n");
	} else if(_str_eq(line, "CLS")) {
		_clear_screen();
	} else {
		result = mb_load_string(bas, line);
	}

	return result;
}

int main(int argc, char* argv[]) {
	int status = 0;

#ifdef _MSC_VER
	_CrtSetBreakAlloc(0);
#endif /* _MSC_VER */

	atexit(_on_exit);

	_on_startup();

	if(argc == 1) {
		_show_tip();
		do {
			status = _do_line();
		} while(MB_FUNC_OK == status || MB_FUNC_SUSPEND == status);
	} else if(argc == 2) {
		if(mb_load_file(bas, argv[1]) == MB_FUNC_OK) {
			mb_run(bas);
		}
	} else {
		printf("Unknown arguments\n");
		_show_tip();
	}

	return 0;
}
