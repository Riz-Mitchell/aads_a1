#include "tree.h"

/**
 * Function: new_branch
 * ------------------
 * Creates a new branch
*/
branch_t*
new_branch(business_t *data) {
  branch_t *temp = (branch_t *)malloc(sizeof(branch_t));
  temp->data = data;
  temp->prefix = string_to_binary(data->trading_name);
  temp->prefix_bits = strlen(temp->prefix);
  temp->branchA = temp->branchB = NULL;
  return temp;
}

// Inorder Traversal
void inorder(struct node *root) {
  if (root != NULL) {
    // Traverse left
    inorder(root->left);

    // Traverse root
    printf("%d -> ", root->key);

    // Traverse right
    inorder(root->right);
  }
}

/**
 * Function: insert
 * ----------------
 * Inserts a node into a tree and returns the new node
*/
branch_t*
insert(branch_t *root, branch_t *inserting, char *inserting_prefix) {
  // Return a new node if the tree is empty
    if (root == NULL) {return new_branch(data);}

    int cond = compare_prefix(root->prefix, inserting_prefix);
    // duplicate place
    if (cond == 0) {

        return root;
    }
    // split
    else if (cond == 1) {
        // change prefix of inserting and the root and create a new node with common prefix
        branch_t *new = split_branches(root, inserting);
        
    }
    // Traverse
    else {
        // change prefix of inserting then traverse
        if ()
    }
  // Condition to check which side to move too
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Driver code
int main() {
  struct node *root = NULL;
  root = insert(root, 8);
  root = insert(root, 3);
  root = insert(root, 1);
  root = insert(root, 6);
  root = insert(root, 7);
  root = insert(root, 10);
  root = insert(root, 14);
  root = insert(root, 4);

  printf("Inorder traversal: ");
  inorder(root);

  printf("\nAfter deleting 10\n");
  root = deleteNode(root, 10);
  printf("Inorder traversal: ");
  inorder(root);
}

/**
 * Function: compare_prefix
 * ------------------------
 * Compares the 2 strings and returns 0 if the strings are the same 1 if they differ at any point
 * and need to be split or -1 if curr_prefix is a substring of insert_prefix and we need to
 * keep going down the tree
*/
int
compare_prefix(char *curr_prefix, char *insert_prefix) {
    // check if equal
    if (strcmp(curr_prefix, insert_prefix) == 0) {
        // duplicate case
        return 0;
    }
    
    for (int i = 0; curr_prefix[i] != '\0' && insert_prefix[i] != '\0'; i++) {
        if (curr_prefix[i] != insert_prefix[i]) {
            printf("at i = %d curr[i] = %c and insert[i] = %c\n\n", i, curr_prefix[i], insert_prefix[i]);
            printf("split in loop");
            return 1;
        }
    }
    // If insert is equal but a substring of curr
    if (strlen(curr_prefix) > strlen(insert_prefix)) {
        printf("split out loop");
        return 1;
    }
    printf("traverse");
    return -1;
}

/**
 * Function: get_common_prefix
 * ---------------------------
 * This function returns the matching substring of the input prefixes
*/
char*
get_common_prefix(char *curr_prefix, char *insert_prefix) {
    int max_size = 50;
    int size = 0;
    char *output = malloc(sizeof(char) * max_size), *temp;
    assert(output);
    for (int i = 0; curr_prefix[i] != '\0' && insert_prefix[i] != '\0'; i++) {
        if (size < max_size) {
            if (curr_prefix[i] == insert_prefix[i]) {
                output[size] = curr_prefix[i];
                size++;
            }
            else {
                break;
            }
        }
        else {
            max_size *= 2;
            output = realloc(output, sizeof(char) * max_size);
            assert(output);
        }
    }
    output[size] = '\0';
    temp = output;
    output = strdup(temp);
    free(temp);
    return output;
}

/**
 * Funbction: remove_bits
 * ----------------------
 * Removes "bits" bits from the prefix and returns the new string
*/
char*
remove_bits(char *prefix, int bits) {
    int len = strlen(prefix), index = 0;
    char *output = malloc(sizeof(char) * len), *temp;
    assert(output);
    for (int i = bits; i < len; i++) {
        output[index] = prefix[i];
        index++;
    }
    output[index] = '\0';
    temp = output;
    output = strdup(temp);
    free(prefix);
    free(temp);
    return output;
}

/**
 * Function: split_branches
 * ------------------------
*/
branch_t*
split_branches(branch_t *curr, branch_t *inserting) {
    branch_t *new = malloc(sizeof(branch_t));
    new->prefix = get_common_prefix(curr->prefix, inserting->prefix);
    new->prefix_bits = strlen(new->prefix);

    /* CHANGE REMAINING PREFIX IN THE "CURR" AND "INSERTING" branchS  m */
    curr->prefix = remove_bits(curr->prefix, new->prefix_bits);
    curr->prefix_bits = strlen(curr->prefix);

    inserting->prefix = remove_bits(inserting->prefix, new->prefix_bits);
    inserting->prefix_bits = strlen(inserting->prefix);

    // Attatch the leaf branchs
    if (curr->prefix[0] == '0') {
        new->branchA = curr;
        new->branchB = inserting;
    }
    else {
        new->branchA = inserting;   // might need to check which leads where
        new->branchB = curr;
    }
    return new;
}