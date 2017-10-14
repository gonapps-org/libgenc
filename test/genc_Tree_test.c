#include <stdio.h>
#include "../src/genc_Tree.h"
int main() {
    struct node {
        GENC_TREE_NODE(struct node);
        int value;
    };
    
    struct node node1 = {.value = 100};
    struct node node2 = {.value = 200};
    struct node node3 = {.value = 300};

    GENC_TREE_NODE_INIT(&node1, 10);
    GENC_TREE_NODE_INIT(&node2, 10);
    GENC_TREE_NODE_INIT(&node3, 10);

    GENC_TREE_NODE_ADD_CHILD(&node1, node2);
    GENC_TREE_NODE_ADD_CHILD(&node1, node3);

    printf("%d\n", GENC_TREE_NODE_GET_CHILD(&node1, 0).value);
    printf("%d\n", GENC_TREE_NODE_GET_CHILD(&node1, 1).value);


    return 0;
}
