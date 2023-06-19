#include <stdlib.h>
#include "minishell.h"

t_char_list	*char_list_new_node(int _index, char _type)
{
    t_char_list* new_node = malloc(sizeof(t_char_list));
    if (new_node == NULL)
        exit(5);
    new_node->index = _index;
    new_node->type = _type;
    new_node->next = NULL;

    return (new_node);
}

void	char_list_insert_end(t_char_list **root, int index, char type)
{
    t_char_list *new_node = char_list_new_node(index, type);

    if (new_node == NULL) {
        exit(6);
    }

    if (*root == NULL) {
        *root = new_node;
        return;
    }

    t_char_list* curr = *root;
    while(curr->next != NULL)
        curr = curr->next;
    curr->next = new_node;
}

void	char_list_delete(t_char_list **root)
{
    t_char_list* curr = *root;
    while (curr != NULL) {
        t_char_list* temp = curr;
        curr = curr->next;
        free(temp);
    }
    *root = NULL;
}
