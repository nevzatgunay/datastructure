/*	Nevzat GÜNAY
	200201062
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "deque.h"

#define SIM_DURATION 30

int main(int argc, char **argv)
{
        srand(time(0));

        struct Deque *q = deque_new();

        int t = 0;
        while (t++ < SIM_DURATION) {
                int action = rand() % 3;
                int r;

                switch (action) {
                case 0: // add random number to queue
                        r = rand() % 10;
                        put_front(q, &r);
                        printf("t = %d: Adding %d to queue, queue size = %d\n",
                               t, r, deque_size(q));
			put_back(q, &r);
			printf("t = %d: Adding %d to queue, queue size = %d\n",
                               t, r, deque_size(q));
                        break;
                case 1: // get the next item
                        if (!deque_is_empty(q)) {
                                get_front(q, &r);
                                printf("t = %d: Took %d from queue, queue size = %d\n",
                                       t, r, deque_size(q));
				get_back(q, &r);
				printf("t = %d: Took %d from queue, queue size = %d\n",
                                       t, r, deque_size(q));
                        } else {
                                printf("t = %d:\n", t);
                        }
                        break;
                default:
                case 2: // do nothing
                        printf("t = %d:\n", t);
                        break;
                }

                fflush(stdout);
                sleep(1);
        }

        deque_free(q);

        return EXIT_SUCCESS;
}

/* Local Variables: */
/* mode: c          */
/* compile-command: "make queue-test" */
/* End:             */
