/**
 * @brief BFS test for shared library advanced interface
 * @file shared_lib_bfs.c
 */

#include <stdio.h>
#include <gunrock/gunrock.h>

int main(int argc, char* argv[]) {
    ////////////////////////////////////////////////////////////////////////////
    struct GRTypes data_t;                 // data type structure
    data_t.VTXID_TYPE = VTXID_INT;         // vertex identifier
    data_t.SIZET_TYPE = SIZET_INT;         // graph size type
    data_t.VALUE_TYPE = VALUE_INT;         // attributes type

    struct GRSetup config;                 // gunrock configurations
    int list[] = {0, 1, 2, 3};             // device to run algorithm
    config.num_devices = sizeof(list) / sizeof(list[0]);  // number of devices
    config.device_list = list;             // device list to run algorithm
    config.source_mode = manually;         // manually setting source vertex
    config.source_vertex = 0;              // source vertex to start
    config.mark_predecessors  = false;     // do not mark predecessors
    config.enable_idempotence = false;     // wether enable idempotence
    config.max_queue_sizing   =  1.0f;     // maximum queue sizing factor

    size_t num_nodes = 7, num_edges = 15;  // number of nodes and edges
    int row_offsets[8]  = {0, 3, 6, 9, 11, 14, 15, 15};
    int col_indices[15] = {1, 2, 3, 0, 2, 4, 3, 4, 5, 5, 6, 2, 5, 6, 6};

    struct GRGraph *graph_i = (struct GRGraph*)malloc(sizeof(struct GRGraph));
    graph_i->num_nodes   = num_nodes;
    graph_i->num_edges   = num_edges;
    graph_i->row_offsets = (void*)&row_offsets[0];
    graph_i->col_indices = (void*)&col_indices[0];

    struct GRGraph *graph_o = (struct GRGraph*)malloc(sizeof(struct GRGraph));

    gunrock_bfs(graph_o, graph_i, config, data_t);

    ////////////////////////////////////////////////////////////////////////////
    int *labels = (int*)malloc(sizeof(int) * graph_i->num_nodes);
    labels = (int*)graph_o->node_value1;
    size_t node; for (node = 0; node < graph_i->num_nodes; ++node)
        printf("Node_ID [%d] : Label [%d]\n", node, labels[node]);

    if (graph_i) free(graph_i);
    if (graph_o) free(graph_o);
    if (labels)  free(labels);

    return 0;
}
