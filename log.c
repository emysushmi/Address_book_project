#include "abk.h"

void log_event(const char *msg) {
    FILE *fp = fopen("log.txt", "a");
    if (fp) {
        fprintf(fp, "%s\n", msg);
        fclose(fp);
    }
}
