#include <stdarg.h>
#include <sbi.h>
#include <stdint.h>

/* Conversion Function for all required base */
char *generic_conv(long n, int b)
{
        char fixed[] = "0123456789ABCDEF";
        static char out[100];
        char *p = (out + sizeof(out) - 1);
        *p = '\0';
        do {
                *--p = fixed[n%b];
                n /= b;
        } while (n);
        return p;
}

int puts(const char *str)
{
        int i = 0;
        while (str[i] != '\0')
                sbi_console_putchar(str[i++]);
        return i;
}

void kprintf(const char *fmt, ...)
{
        char *t, *str;
        va_list arg;
        unsigned int i;

        va_start(arg, fmt);

        /* Collect all the data in a write buffer */
        for (t = (char *)fmt; *t != '\0'; t++) {
                while ((*t != '%') && (*t != '\0')) {
                        sbi_console_putchar(*t);
                        t++;
                }
                if (*t == '\0')
                        break;
                t++;
                switch (*t) {
                        case 'd':
                                i = va_arg(arg, int);
                                if (i < 0) {
                                        sbi_console_putchar('-');
                                        str = generic_conv(-i, 10);
                                } else
                                        str = generic_conv(i, 10);
                                puts(str);
                                break;
                        case 'p' :
                                i = va_arg(arg, unsigned int);
                                puts("0x");
                                puts(generic_conv(i, 16));
                                break;
                        case 'x':
                                i = va_arg(arg, unsigned int);
                                puts(generic_conv(i, 16));
                                break;
                        case 'c' :
                                i = va_arg(arg, int);
                                sbi_console_putchar(i);
                                break;
                        case 's' :
                                str = va_arg(arg, char *);
				puts(str);
				break;
                        default:
                                break;
                }

        }

}

