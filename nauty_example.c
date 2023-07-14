/* This program prints generators for the automorphism group of an
n-vertex polygon, where n is a number supplied by the user.
This version uses a fixed limit for MAXN.
*/
#define MAXN 1000  /* Define this before including nauty.h */
#include "nauty.h" /* which includes <stdio.h> and other system files */

int main(int argc, char *argv[])
{
    int subgraph_size = 6;
    graph g[subgraph_size];
    graph h[subgraph_size];
    graph cg[subgraph_size];
    graph ch[subgraph_size];
    int lab1[subgraph_size], lab2[subgraph_size], ptn1[subgraph_size], orbits1[subgraph_size], ptn2[subgraph_size], orbits2[subgraph_size];
    optionblk options = {1, FALSE, FALSE, TRUE, TRUE, TRUE, CONSOLWIDTH,
                         NULL, NULL, NULL, NULL, NULL, NULL, NULL, 100, 0, 1, 0, &dispatch_graph, FALSE, NULL};
    statsblk stats;
    int m, k;
    /* Default options are set by the DEFAULTOPTIONS_GRAPH macro above.
    Here we change those options that we want to be different from the
    defaults. writeautoms=TRUE causes automorphisms to be written. */
    options.writeautoms = TRUE;
    /* The nauty parameter m is a value such that an array of
    m setwords is sufficient to hold n bits. The type setword
    is defined in nauty.h. The number of bits in a setword is
    WORDSIZE, which is 16, 32 or 64. Here we calculate
    m = ceiling(n/WORDSIZE). */
    m = SETWORDSNEEDED(subgraph_size);
    k = SETWORDSNEEDED(subgraph_size);
    /* The following optional call verifies that we are linking
    to compatible versions of the nauty routines. */
    nauty_check(WORDSIZE, m, subgraph_size, NAUTYVERSIONID);
    nauty_check(WORDSIZE, k, subgraph_size, NAUTYVERSIONID);
    /* Now we create the cycle. First we zero the graph, than for
    each v, we add the edge (v,v+1), where values are mod n. */
    EMPTYGRAPH(g, m, subgraph_size);
    EMPTYGRAPH(h, k, subgraph_size);

    // G1
    // ADDONEEDGE(g, 0, 3, m);
    // ADDONEEDGE(g, 0, 5, m);
    // ADDONEEDGE(g, 1, 5, m);
    // ADDONEEDGE(g, 1, 2, m);
    // ADDONEEDGE(g, 1, 3, m);
    // ADDONEEDGE(g, 2, 1, m);
    // ADDONEEDGE(g, 2, 3, m);
    // ADDONEEDGE(g, 2, 4, m);
    // ADDONEEDGE(g, 3, 0, m);
    // ADDONEEDGE(g, 3, 1, m);
    // ADDONEEDGE(g, 3, 2, m);
    // ADDONEEDGE(g, 4, 2, m);
    // ADDONEEDGE(g, 4, 2, m);
    // ADDONEEDGE(g, 5, 0, m);
    // ADDONEEDGE(g, 5, 1, m);
    // ADDONEEDGE(g, 5, 4, m);

    // // H
    // ADDONEEDGE(h, 0, 1, k);
    // ADDONEEDGE(h, 0, 2, k);
    // ADDONEEDGE(h, 1, 0, k);
    // ADDONEEDGE(h, 1, 3, k);
    // ADDONEEDGE(h, 2, 0, k);
    // ADDONEEDGE(h, 2, 4, k);
    // ADDONEEDGE(h, 3, 1, k);
    // ADDONEEDGE(h, 3, 4, k);
    // ADDONEEDGE(h, 3, 5, k);
    // ADDONEEDGE(h, 4, 2, k);
    // ADDONEEDGE(h, 4, 3, k);
    // ADDONEEDGE(h, 4, 5, k);
    // ADDONEEDGE(h, 5, 3, k);
    // ADDONEEDGE(h, 5, 4, k);

    // H -without repeat
    ADDONEEDGE(g, 0, 1, k);
    ADDONEEDGE(g, 0, 2, k);
    ADDONEEDGE(g, 0, 5, k);
    ADDONEEDGE(g, 1, 2, k);
    ADDONEEDGE(g, 1, 3, k);
    ADDONEEDGE(g, 2, 4, k);
    ADDONEEDGE(g, 3, 5, k);
    ADDONEEDGE(g, 4, 5, k);

    // // G
    // ADDONEEDGE(g, 0, 1, m);
    // ADDONEEDGE(g, 0, 2, m);
    // ADDONEEDGE(g, 1, 0, m);
    // ADDONEEDGE(g, 1, 2, m);
    // ADDONEEDGE(g, 1, 4, m);
    // ADDONEEDGE(g, 2, 0, m);
    // ADDONEEDGE(g, 2, 1, m);
    // ADDONEEDGE(g, 2, 3, m);
    // ADDONEEDGE(g, 3, 2, m);
    // ADDONEEDGE(g, 3, 5, m);
    // ADDONEEDGE(g, 4, 5, m);
    // ADDONEEDGE(g, 4, 1, m);
    // ADDONEEDGE(g, 5, 3, m);
    // ADDONEEDGE(g, 5, 4, m);

    // H -without repeat
    // ADDONEEDGE(h, 0, 1, m);
    // ADDONEEDGE(h, 0, 2, m);
    // ADDONEEDGE(h, 0, 3, m);
    // ADDONEEDGE(h, 1, 5, m);
    // ADDONEEDGE(h, 2, 4, m);
    // ADDONEEDGE(h, 3, 5, m);
    // ADDONEEDGE(h, 3, 4, m);
    // ADDONEEDGE(h, 4, 5, m);

    // H'
    ADDONEEDGE(h, 0, 4, m);
    ADDONEEDGE(h, 0, 2, m);
    ADDONEEDGE(h, 0, 3, m);
    ADDONEEDGE(h, 4, 5, m);
    ADDONEEDGE(h, 2, 1, m);
    ADDONEEDGE(h, 3, 5, m);
    ADDONEEDGE(h, 3, 1, m);
    ADDONEEDGE(h, 1, 5, m);

    printf("Generators for Aut(C[%d]):\n", subgraph_size);
    /* Since we are not requiring a canonical labelling, the last
    parameter to densenauty() is not required and can be NULL. */
    densenauty(g, lab1, ptn1, orbits1, &options, &stats, k, subgraph_size, cg);
    densenauty(h, lab2, ptn2, orbits2, &options, &stats, m, subgraph_size, ch);
    /* The size of the group is returned in stats.grpsize1 and
    stats.grpsize2. */
    printf("Automorphism group size = ");
    writegroupsize(stdout, stats.grpsize1, stats.grpsize2);
    printf("%d", *ptn1);
    printf("\n");
    exit(0);
}