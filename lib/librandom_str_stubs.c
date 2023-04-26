/**********************************************************************************/
/* The MIT License (MIT)							  */
/* 										  */
/* Copyright (c) 2022 Muqiu Han							  */
/* 										  */
/* Permission is hereby granted, free of charge, to any person obtaining a copy	  */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights	  */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	  */
/* copies of the Software, and to permit persons to whom the Software is	  */
/* furnished to do so, subject to the following conditions:			  */
/* 										  */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.				  */
/* 										  */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	  */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	  */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	  */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	  */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.									  */
/**********************************************************************************/

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/signals.h>

static uint32_t X = 123456789;
static uint32_t Y = 362436069;
static uint32_t Z = 521288629;
static uint32_t W = 88675123;

uint32_t
xorshift()
  {
    uint32_t t = X ^ (X << 11);
    X = Y;
    Y = Z;
    Z = W;
    W = W ^ (W >> 19) ^ (t ^ (t >> 8));
    return W;
  }

char *
generator(const uint32_t len)
  {
    char * result = malloc((sizeof(char) * len) + 1);
    
    for(uint32_t index = 0; index < len; index ++) {
      const uint32_t r = xorshift();

      if (isdigit(r % 62))
	result[index] = (char)(uint8_t)(r % 10 + 48);
      else if (isalpha(r % 62))
	result[index] = (char)(uint8_t)(r % 26 + 65);
      else
	result[index] = (char)(uint8_t)(r % 26 + 97);

      X = Y;
      Y = Z;
      Z = W;
      W = W ^ (W >> 19) ^ (r ^ (r >> 8));
    }

    result[len + 1] = '\0';

    return result;
  }

value
ocaml_random_str(value ocaml_len)
  {
    CAMLparam1(ocaml_len);
    CAMLlocal1(result);
    const uint32_t len = Int_val(ocaml_len);

    char * random_str = generator(len);
    result = caml_copy_string(random_str);
    free(random_str);
    
    return result;
  }
