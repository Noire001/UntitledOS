int putchar(int ic) {
#if defined(__is_libk)
    char c = ic;
//    terminal_write(&c, sizeof(c))
#else

#endif
    return ic;
}