#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
                if(strncmp(node->line, line, len < node->len ? len : node->len) == 0){
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

void uniq_lines(FILE *fp){
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
                fprintf(stdout, "%7ud %s\n", node->cnt, node->line);
                node = node->next;
        }

        free_list(head);
}

int main(int argc, char **argv){
        if(argc != 2){
                fprintf(stdout, "Usage: %s <filepath>\n", argv[0]);
                exit(1);
        }

        FILE *file;
        file = fopen(argv[1], "r");
        if(file == NULL){
                fprintf(stdout, "%s: no such file\n", argv[1]);
                exit(1);
        }

        uniq_lines(file); 

        fclose(file);
}

