#ifdef DEBUG
#define debugf(fmt, ...) \
    fprintf(stderr, "[%s:%d] " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define debugf(fmt, ...) 0
#endif
