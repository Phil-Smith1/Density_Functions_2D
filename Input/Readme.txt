This is the directory from which the input to the 2D density functions code can be customised.

The Framework_Parameters file contains parameters such as directories and whether the Brillouin zones should be drawn or not.

The Experiment file contains three lines. The number on the first line is the 1 more than the number of random points to be added to the motif. (1 if no random points to be added.) The number on the second line is the number of Brilllouin zones to be computed, which equates to 1 more than the number of density functions computed. The number on the third line is the number of repetitions of the setup, so should usually be 1, but should be 2 for U+V experiments and x if we want to repeat the experiment for x random point sets.

The v_file contains a list of files, where each file corresponds to a V in the U+V experiments.

The Input file contains a list of files, where each file contains a list of further files that correspond to the cell parameters and the fractional coordinates.