#define DEBUG 1
#if DEBUG
#define LOG(x) printf("%s \r\n", x)
#else
#define LOG(x)
#endif
