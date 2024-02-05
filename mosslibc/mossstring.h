#ifndef MOSS_STRING_H
#define MOSS_STRING_H

Size strlen(String str)
{
    Size size = 0;
    while (str[size] != '\0') size++;
    return size;
}

#endif // MOSS_STRING_H
