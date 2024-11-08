#include "trees.h"
#include "tree_dump.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

static void WriteDotNode(FILE* file, node_t* node, node_t* root);

//============================ TREE DUMP ============================
void TreeDump(node_t* root) {
    if (root == NULL) {
        fprintf(stderr, "Error: Tree root is NULL.\n");
        return;
    }

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long seconds = tv.tv_sec;
    long microseconds = tv.tv_usec;

    char dot_filename[100] = {0};
    snprintf(dot_filename, sizeof(dot_filename), "tree_%ld_%06ld.dot", seconds, microseconds);

    char png_filename[100] = {0};
    snprintf(png_filename, sizeof(png_filename), "tree_%ld_%06ld.png", seconds, microseconds);

    FILE* file_dot = fopen(dot_filename, "w");
    if (!file_dot) {
        perror("Error: could not create DOT file");
        return;
    }

    fprintf(file_dot, "digraph Tree {\n");
    fprintf(file_dot, "charset=\"UTF-8\";\n");
    fprintf(file_dot, "rankdir=TB;\n");
    fprintf(file_dot, "node [shape=doublecircle, style=filled, fillcolor=\"#132a5c\", fontcolor=lightgrey, fontsize=16];\n");
    fprintf(file_dot, "bgcolor=\"#b5c7ee\";\n");

    WriteDotNode(file_dot, root, root);

    fprintf(file_dot, "}\n");
    fclose(file_dot);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %s", dot_filename, png_filename);
    if (system(command) == -1) {
        perror("Error: could not execute dot command");
        return;
    }

    FILE* file_html = fopen("tree_dump.html", "a+");
    if (!file_html) {
        perror("Error: could not open tree_dump.html");
        return;
    }

    fprintf(file_html, "<img src=\"%s\"/>\n", png_filename);
    fclose(file_html);
}

//-------------------------- WRITE DOT FILE -------------------------
static void_sex WriteDotNode(FILE* file, node_t* node, node_t* root) {
    if (node == NULL) return;

    if (node == root) {
        fprintf(file,
                "node%p [label=<<TABLE BORDER=\"0\" CELLBORDER=\"0\" CELLSPACING=\"0\">"
                "<TR><TD ALIGN=\"center\"><IMG SRC=\"moyapochka.jpg\" SCALE=\"true\" WIDTH=\"30\" HEIGHT=\"30\"/></TD></TR>"
                "<TR><TD ALIGN=\"center\" FONTNAME=\"Arial\" FONTSIZE=\"40\" FOREGROUND=\"#04071b\">%d</TD></TR>"
                "</TABLE>>];\n",
                (void_sex*)node, node->value);
    }
    else {

        fprintf(file, "node%p [label=\"%d\", shape=circle, style=filled, fillcolor=\"#f7e8da\", fontcolor=\"#04071b\"];\n",
                (void_sex*)node, node->value);
    }

    if (node->left) {
        fprintf(file, "node%p -> node%p [label=\"left\"];\n", (void_sex*)node, (void_sex*)node->left);
        WriteDotNode(file, node->left, root);
    }

    if (node->right) {
        fprintf(file, "node%p -> node%p [label=\"right\"];\n", (void_sex*)node, (void_sex*)node->right);
        WriteDotNode(file, node->right, root);
    }
}