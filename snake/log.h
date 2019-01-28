#define DEBUG 0
#if DEBUG
#define ALOG(x, a) printf(x, a)
#define LOG(x) printf(x)
#else
#define ALOG(x, a)
#define LOG(x)
#endif
