#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void assert_heap_allocation(void *);

struct lnode{
	int val;
	struct lnode *next;
};

struct lnode* create_node(int data){
	struct lnode *node = (struct lnode*) malloc(sizeof(struct lnode));
	assert_heap_allocation(node);
	node->val = data;
	node->next = NULL;

	return node;
}

struct lnode* insert_node(struct lnode *head, struct lnode *node, const int pos){
	if(head == NULL){
		head = node;
		return head;
	}
	
	if(pos == 1){
		node->next = head;
		head = node;
		return head;
	}

	int p = 1;
	struct lnode *curr = head;
		
	while(curr->next != NULL && p < pos){
		p++;
		curr = curr->next;
	}
	
	node->next = curr->next;
	curr->next = node;

	return head;
}

struct lnode* delete_node_with_position(struct lnode *head, const int pos){
	if(head == NULL){
		return head;
	}
	
	int p = 1;
	struct lnode *node_to_free = NULL;

	if(pos == 1){
		node_to_free = head;
		head = head->next;
	}else{
		struct lnode *curr = head;
		while(curr->next != NULL){
			if(p + 1 == pos){
				node_to_free = curr->next;
				curr->next = curr->next->next;
				break;
			}

			p++;
			curr = curr->next;
		}
	}

	if(node_to_free != NULL)
		free(node_to_free);
	
	return head;
}

struct lnode* delete_node_with_data(struct lnode *head, const int data){
	if(head == NULL){
		return head;
	}
	
	struct lnode *node_to_free = NULL;

	if(head->val == data){
		node_to_free = head;
		head = head->next;
	}else{
		struct lnode *curr = head;
		while(curr->next != NULL){
			if(curr->next->val == data){
				node_to_free = curr->next;
				curr->next = curr->next->next;
				break;
			}
			
			curr = curr->next;
		}
	}
	
	if(node_to_free != NULL)
		free(node_to_free);

	return head;
}

struct lnode* create_list(const int* node_values, const int num_nodes){
	struct lnode *head = NULL;

	for(int i = 0; i < num_nodes; i++){
		struct lnode *node = create_node(node_values[i]);
		head = insert_node(head, node, i + 1);
	}
	
	return head;
}

void print_list(struct lnode *head){
	struct lnode* curr = head;
	while(curr != NULL){
		printf("%d ", curr->val);
		curr = curr->next;
	}
	printf("\n");
}

void free_list(struct lnode *head){
	struct lnode *node = NULL;
	while(head != NULL){
		node = head;
		head = head->next;

		free(node);
	}	
}


struct lnode* reverse_list(struct lnode *node){
	if(node == NULL || node->next == NULL)
		return node;

	struct lnode *head = reverse_list(node->next);
	node->next->next = node;
	node->next = NULL;

	return head;
}

struct lnode* reverse_g(struct lnode *node, const int k){
	struct lnode *n_head = NULL, *gnext = node, *prev_g_last = NULL;
	while(gnext != NULL){
		int cnt = 1;
		struct lnode *curr = gnext, *head = gnext;
		while(curr != NULL && cnt < k){
	    		cnt++;
	    		curr = curr->next;
		}
		gnext = curr == NULL ? NULL : curr->next;

		if(curr == NULL){
			prev_g_last->next = head;
			continue;
		}
		
		curr->next = NULL;
	
		struct lnode *new_head = reverse_list(head);
		if(prev_g_last != NULL){
			prev_g_last->next = new_head;
		}else{
			n_head = new_head;
		}
		prev_g_last = head;
	}

	return n_head;
}

void assert_heap_allocation(void *p){
	assert(p != NULL);
}

int main(int argc, char **argv){
	struct lnode *head = NULL;

	int num_nodes, k;
	scanf("%d %d", &num_nodes, &k);

	int nodes[num_nodes];
	for(size_t i = 0; i < num_nodes; i++){
		scanf("%d", nodes + i);
	}

	head = create_list(nodes, num_nodes);
	print_list(head);

	head = reverse_g(head, k);
	print_list(head);
	
	free_list(head);	
	return 0;
}

