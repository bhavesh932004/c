#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include "read_line.h"

#define ull unsigned int 
struct line_node {
        char *line;
        ull len;
        ull cnt;
        struct line_node *next;
};

struct line_node *create_line_node(char *line, ull len, ull cnt){
        struct line_node *node = (struct line_node *) malloc(sizeof(struct line_node));
        
        char *str = (char *) malloc(len + 1);
        strncpy(str, line, len + 1);

        node->line = str;
        node->len = len;
        node->cnt = cnt;
        node->next = NULL;

        return node;
}

struct line_node *search_line(struct line_node *head, char *line, ull len){
        struct line_node *node = head;
        while(node != NULL){
                if(strncmp(node->line, line, len + 1) == 0){
                        break;
                }

                node = node->next;
        }

        return node;
}

struct line_node *add_node_at_end(struct line_node *head, struct line_node *node){
        if(head == NULL){
                return node;
        }

        struct line_node *curr = head;
        while(curr->next != NULL){
                curr = curr->next;
        }

        curr->next = node;

        return head;
}

void free_list(struct line_node *head){
        while(head != NULL){
                struct line_node *next = head->next;
                free(head->line);
                free(head);
                head = next;
        }
}

/* print each unique line only once and it's frequency */
void print_uniq_lines(FILE *fp){
        struct line_node *head = NULL;
        for(;;){
                char *line = read_line(fp);
                if(line == NULL){
                        break;
                }
                
                ull len = strlen(line);
                struct line_node *node = search_line(head, line, len);
                if(node == NULL){
                        node = create_line_node(line, len, 1);
                        head = add_node_at_end(head, node);
                }else{
                        node->cnt++;
                }

                free(line);
        }

        struct line_node *node = head;
        while(node != NULL){
                fprintf(stdout, "%7u %s\n", node->cnt, node->line);
                node = node->next;
        }

        free_list(head);
}

/* filter adjacent matching lines and print only one and it's frequency */
void print_uniq_lines_1(FILE *fp){
        char *prev = NULL;
        unsigned long long cnt = 0;
        for(;;){
                char *line = read_line(fp);
                if(line == NULL){
                        if(prev != NULL){
                                fprintf(stdout, "%7llu %s\n", cnt, prev);
                                free(prev);
                        }
                        
                        break;
                }

                if(prev == NULL){
                        prev = line;
                }

                if(strncmp(prev, line, strlen(line) + 1) == 0){
                        cnt++;
                        if(cnt > 1)
                                free(line);
                }else{
                        fprintf(stdout, "%7llu %s\n", cnt, prev);
                        free(prev);
                        prev = line;
                        cnt = 1;
                }
        }
}

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, 0, "%s: no such file", argv[1]);
    }

    print_uniq_lines(fp);
    fclose(fp);
    return 0;
}
