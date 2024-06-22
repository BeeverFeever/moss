#include "string.h"
#include <utils/vargs.h>
#include <io/console.h>
#include <utils/printf.h>

bool inline is_digit(char c) { return (c >= '0' && c <= '9'); }

bool s8eql(s8 a, s8 b) {
   if (a.length != b.length) return false;
   for (Size i = 0; i < a.length; i++)
      if (a.ptr[i] != b.ptr[i]) return false;
   return true;
}

Lsize strlen(char* s)
{
   Lsize k;
   for(k = 0; s[k] != '\0'; k++) {}
   return k;
}

void strrev(char* str) {
   Lsize len = strlen(str);
   for (int i = 0, j = len - 1; i <= j; i++, j--) {
      char temp = str[i];
      str[i] = str[j];
      str[j] = temp;
   }
}

u32 digits(u32 n, i32 base) {
   u32 count = 0;
   do {
      n /= base;
      ++count;
   } while (n != 0);
   return count;
}

void itoa(i32 num, i32 base, char buffer[]) {
   if (num == 0) {
      buffer = "0";
      return;
   }

   bool negative = false;

   if (num < 0 && base == 10) {
      negative = true;
      num = -num;
   }

   u32 i = 0;
   while (num != 0) {
      int rem = num % base;
      buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
      num = num / base;
   }

   if (negative)
      buffer[i++] = '-';

   buffer[i] = '\0';

   strrev(buffer);
}

// void sprintf(char* buffer, char* format, ...) {
//    // ii = insert index
//    // ci = current index
//    va_list list;
//    va_start(list);
//
//    Size ii = 0;
//    Usize fmt_length = strlen(format);
//    Usize buf_length = sizeof(buffer); 
//    for (Usize ci = 0; ci < fmt_length && ci < buf_length; ci++, ii++) {
//       if (format[ci] == '%') {
//          ci++;
//          switch(format[ci]) {
//             case '%':
//                buffer[ii] = '%';
//                continue;
//             case 'c':
//                buffer[ii] = va_arg(list, int);
//                continue;
//             case 's':
//                char* temp = va_arg(list, char*);
//                for (Size i = 0; i < strlen(temp); i++) {
//                   buffer[ii] = temp[ii];
//                }
//                continue;
//             case 'd':
//                int num = va_arg(list, int);
//                char buf[10];
//                itoa(num, 10, buf);
//                for (Size i = 0; i < strlen(temp) || buffer[i] == '\0'; i++) {
//                   buffer[ii] = temp[ii];
//                }
//                continue;
//          }
//       } else buffer[ci] = format[ci];
//    }
// }

void s8print(s8 str) {
   for (int i = 0; i < str.length; i++)
      putchar_(str.ptr[i]);
}
