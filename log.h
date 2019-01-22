#define DEBUG 1
#if DEBUG
#define ALOG(x, a) printf(x, a)
#define LOG(x) printf(x)
#else
#define LOG(x)
#endif
