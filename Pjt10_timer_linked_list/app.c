#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "app.h"
#include "timer.h"

void app_list(char *ap) {
	char buf[8], how = 'a';
	struct node *np;

	if(ap)	how = *ap;
	while(1) {
		printf("> ");
		if(fgets(buf, 8, stdin) == NULL)
			break;
		np = get_node();
		np->data = buf[0];
		switch(how) {
			case 'h' 	: insert_node_head(np);	break;
			case 't' 	: insert_node_tail(np);	break;
			case 'd' 	: insert_node_desc(np);	break;
			default  	: insert_node_ascn(np);
		}
	}
	tour_list();
	free_list();
}

void app_timer(char *ap) {
	char		buf[8];
	int			ms;
	struct task tsk;

	while(1) {
		printf(">>");
		if(fgets(buf, 8, stdin) == NULL || (ms = atoi(buf)) == 0)
			break;

		insert_timer(&tsk, ms);
	}
	tour_timer();
	free_timer();
}

void app_add(char *ap) {
	int t1, t2;
    if (ap != NULL) {
        char *bp = strtok(ap, " ");
        if (bp != NULL) {
            t1 = atoi(bp); 
            bp = strtok(NULL, " "); 
            if (bp != NULL) {
                t2 = atoi(bp); 
                printf("add = %d\n", t1 + t2); 
            } else {
                printf("error...\n"); 
            }
        } else {
            printf("error\n"); 
        }
    } else {
        printf("error...\n");
    }
}

