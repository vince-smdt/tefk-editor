#include "Logger.h"

#include <curses.h>

#define RET_IF_ERR(COND) if ((COND) == ERR) {               \
    TEFK_LOG_ERR("An error as occured!"                     \
                 "ERR (-1) was returned.");                 \
    return ERR;                                             \
}

#define RET_IF_NIL(COND) if ((COND) == NULL) {              \
    TEFK_LOG_ERR("An error as occured!"                     \
                 "A null pointer was returned.");           \
    return ERR;                                             \
}
