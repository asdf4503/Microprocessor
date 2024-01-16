#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "list.h"

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
