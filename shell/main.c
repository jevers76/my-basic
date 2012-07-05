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

#ifdef _MSC_VER
#	pragma warning(disable : 4996)
#endif /* _MSC_VER */

#define _MAX_LINE_LENGTH 256
#define _str_eq(__str1, __str2) (_strcmpi(__str1, __str2) == 0)

#define _LINE_INC_STEP 16

typedef struct _code_line_t {
	char** lines;
	int count;
	int size;
} _code_line_t;

static mb_interpreter_t* bas = 0;

static _code_line_t* c = 0;

static _code_line_t* _create_code(void) {
	_code_line_t* result = (_code_line_t*)malloc(sizeof(_code_line_t));
	result->count = 0;
	result->size = _LINE_INC_STEP;
	result->lines = (char**)malloc(sizeof(char*) * result->size);

	return result;
}

static void _destroy_code(_code_line_t* code) {
	int i = 0;
	assert(code);
	for(i = 0; i < code->count; ++i) {
		free(code->lines[i]);
	}
	free(code->lines);
	free(code);
}

static void _clear_code(_code_line_t* code) {
	int i = 0;
	assert(code);
	for(i = 0; i < code->count; ++i) {
		free(code->lines[i]);
	}
	code->count = 0;
}

static void _append_line(_code_line_t* code, char* txt) {
	assert(code && txt);
	if(code->count + 1 == code->size) {
		code->size += _LINE_INC_STEP;
		code->lines = (char**)realloc(code->lines, sizeof(char*) * code->size);
	}
	code->lines[code->count++] = strdup(txt);
}

static char* _get_code(_code_line_t* code) {
	char* result = 0;
	int i = 0;
	assert(code);
	result = (char*)malloc((_MAX_LINE_LENGTH + 2) * code->count + 1);
	result[0] = '\0';
	for(i = 0; i < code->count; ++i) {
		result = strcat(result, code->lines[i]);
		if(i != code->count - 1) {
			result = strcat(result, "\r\n");
		}
	}

	return result;
}

static void _set_code(_code_line_t* code, char* txt) {
	char* cursor = 0;
	char _c = '\0';
	assert(code);
	if(!txt) {
		return;
	}
	_clear_code(code);
	cursor = txt;
	do {
		_c = *cursor;
		if(_c == '\r' || _c == '\n' || _c == '\0') {
			cursor[0] = '\0';
			if(_c == '\r' && *(cursor + 1) == '\n') {
				++cursor;
			}
			_append_line(code, txt);
			txt = cursor + 1;
		}
		++cursor;
	} while(_c);
}

static char* _load_file(const char* path) {
	FILE* fp = 0;
	char* result = 0;
	long curpos = 0;
	long l = 0;
	assert(path);
	fp = fopen(path, "rb");
	if(fp) {
		curpos = ftell(fp);
		fseek(fp, 0L, SEEK_END);
		l = ftell(fp);
		fseek(fp, curpos, SEEK_SET);
		result = (char*)malloc((size_t)(l + 1));
		assert(result);
		fread(result, 1, l, fp);
		fclose(fp);
		result[l] = '\0';
	}

	return result;
}

static int _save_file(const char* path, const char* txt) {
	FILE* fp = 0;
	assert(path && txt);
	fp = fopen(path, "wb");
	if(fp) {
		fwrite(txt, sizeof(char), strlen(txt), fp);
		fclose(fp);

		return 1;
	}

	return 0;
}

static int beep(mb_interpreter_t* s, void** l) {
	int result = MB_FUNC_OK;

	assert(s && l);

	mb_check(mb_attempt_func_begin(s, l));

	putchar('\a');

	return result;
}

static void _on_error(mb_interpreter_t* s, mb_error_e e, char* m, int p, unsigned short row, unsigned short col, int abort_code) {
	if(SE_NO_ERR != e) {
		printf("Error :\n    [POS] %d, [ROW] %d, [COL] %d,\n    [CODE] %d, [MESSAGE] %s, [ABORT CODE] %d\n", p, row, col, e, m, abort_code);
	}
}

static void _on_startup(void) {
	c = _create_code();

	mb_init();

	mb_open(&bas);
	mb_set_error_handler(bas, _on_error);

	mb_reg_fun(bas, beep);
}

static void _on_exit(void) {
	mb_close(&bas);

	mb_dispose();

	_destroy_code(c);
	c = 0;

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

static int _new_program(void) {
	_clear_code(c);
	return mb_reset(&bas, false);
}

static void _list_program(const char* sn, const char* cn) {
	long lsn = 0;
	long lcn = 0;
	assert(sn && cn);
	lsn = atoi(sn);
	lcn = atoi(cn);
	if(lsn == 0 && lcn == 0) {
		char* txt = _get_code(c);
		printf("%s\n", txt);
		free(txt);
	} else {
		int i = 0;
		int e = 0;
		if(lsn < 1 || lsn > c->count) {
			printf("Line number %d out of bound.\n", lsn);
			return;
		}
		if(lcn < 0) {
			printf("Invalid line count %d.\n", lcn);
			return;
		}
		--lsn;
		e = lcn ? lsn + lcn : c->count;
		for(i = lsn; i < e; ++i) {
			if(i >= c->count) {
				break;
			}
			printf("%s\n", c->lines[i]);
		}
	}
}

static void _edit_program(const char* no) {
	char line[_MAX_LINE_LENGTH];
	long lno = 0;
	assert(no);
	lno = atoi(no);
	if(lno < 1 || lno > c->count) {
		printf("Line number %d out of bound.\n", lno);
		return;
	}
	--lno;
	memset(line, 0, _MAX_LINE_LENGTH);
	printf("%d]", lno + 1);
	gets(line);
	strcpy(c->lines[lno], line);
}

static void _load_program(const char* path) {
	char* txt = _load_file(path);
	if(txt) {
		_new_program();
		_set_code(c, txt);
		free(txt);
		if(c->count == 1) {
			printf("Load done. %d line loaded.\n", c->count);
		} else {
			printf("Load done. %d lines loaded.\n", c->count);
		}
	} else {
		printf("Cannot load file \"%s\"\n", path);
	}
}

static void _save_program(const char* path) {
	char* txt = _get_code(c);
	if(!_save_file(path, txt)) {
		printf("Cannot save file \"%s\"\n", path);
	} else {
		if(c->count == 1) {
			printf("Save done. %d line saved.\n", c->count);
		} else {
			printf("Save done. %d lines saved.\n", c->count);
		}
	}
	free(txt);
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
	printf("  LIST  - List current program\n");
	printf("        - Usage: LIST [l [n]], l is start line number, n is line count\n");
	printf("  EDIT  - Edit a line in current program\n");
	printf("        - Usage: EDIT n, n is line number\n");
	printf("  LOAD  - Load a file as current program\n");
	printf("        - Usage: LOAD *.*\n");
	printf("  SAVE  - Save current program to a file\n");
	printf("        - Usage: SAVE *.*\n");
}

static int _do_line(void) {
	int result = MB_FUNC_OK;
	char line[_MAX_LINE_LENGTH];
	char dup[_MAX_LINE_LENGTH];

	assert(bas);

	memset(line, 0, _MAX_LINE_LENGTH);
	printf("]");
	gets(line);

	memcpy(dup, line, _MAX_LINE_LENGTH);
	strtok(line, " ");

	if(_str_eq(line, "")) {
		/* Do nothing */
	} else if(_str_eq(line, "HELP")) {
		_show_help();
	} else if(_str_eq(line, "BYE")) {
		result = MB_FUNC_BYE;
	} else if(_str_eq(line, "NEW")) {
		result = _new_program();
	} else if(_str_eq(line, "RUN")) {
		char* txt = _get_code(c);
		result = mb_reset(&bas, false);
		result = mb_load_string(bas, txt);
		free(txt);
		result = mb_run(bas);
		printf("\n");
	} else if(_str_eq(line, "CLS")) {
		_clear_screen();
	} else if(_str_eq(line, "LIST")) {
		char* sn = line + strlen(line) + 1;
		char* cn = 0;
		strtok(sn, " ");
		cn = sn + strlen(sn) + 1;
		_list_program(sn, cn);
	} else if(_str_eq(line, "EDIT")) {
		char* no = line + strlen(line) + 1;
		_edit_program(no);
	} else if(_str_eq(line, "LOAD")) {
		char* path = line + strlen(line) + 1;
		_load_program(path);
	} else if(_str_eq(line, "SAVE")) {
		char* path = line + strlen(line) + 1;
		_save_program(path);
	} else {
		_append_line(c, dup);
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
		} while(MB_FUNC_OK == status || MB_FUNC_SUSPEND == status || MB_FUNC_ERR == status || MB_FUNC_END == status);
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
