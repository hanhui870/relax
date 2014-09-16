/**
 * This implementation of local continuations uses the C switch() statement to resume execution of a function
 * somewhere inside the function's body. The implementation is based on the fact that switch() statements are
 * able to jump directly into the bodies of control structures such as if() or while() statmenets.
 */
#include<stdio.h>

typedef unsigned short lc_t;

struct pt {
    lc_t lc;
};

static int protothread1_flag, protothread2_flag;
static int protothread1(struct pt *pt) {
    char PT_YIELD_FLAG = 1;
    switch ((pt)->lc) {
    case 0:
        ;

        while (1) {
            do {
                (pt)->lc = 33;
                case 33: //line number
                ;
                if (!(protothread2_flag != 0)) {
                    return 0;
                }
            } while (0);

            printf("Protothread 1 running\n");
            protothread2_flag = 0;
            protothread1_flag = 1;
        }
    };
    PT_YIELD_FLAG = 0;
    (pt)->lc = 0;
    return 3;
}

static int protothread2(struct pt *pt) {
    char PT_YIELD_FLAG = 1;
    switch ((pt)->lc) {
    case 0:
        ;

        while (1) {
            protothread2_flag = 1;

            do {
                (pt)->lc = 63;
                case 63: //line number
                ;
                if (!(protothread1_flag != 0)) {
                    return 0;
                }
            } while (0);

            printf("Protothread 2 running\n");
            protothread1_flag = 0;
        }
    };
    PT_YIELD_FLAG = 0;
    (pt)->lc = 0;
    ;
    return 3;
}

static struct pt pt1, pt2;
int main(void) {
    pt1.lc = 0;
    pt2.lc = 0;

    while (1) {
        protothread1(&pt1);
        protothread2(&pt2);
    }
}
