Parallel hp-adaptive matrix-free FEM
====================================

This program is used as a benchmark to demonstrate the benefits of
parallelization, hp-adaptive methods and matrix-free methods combined.

All results of the following paper have been generated with this
program.
@code{.bib}
@article{parallelhp,
  author  = {},
  title   = {},
  journal = {},
  volume  = {},
  issue   = {},
  year    = {},
  doi     = {}
}
@endcode


Compiling and Running
---------------------

To generate a makefile for this code using CMake, create a build
directory to your liking and type the following command into the
terminal from the build directory

	cmake /path/to/project -DDEAL_II_DIR=/path/to/deal.II

To compile the program with all of the applications, call:

  make
  
Run the program with a parameter file given as a command line argument.
You can use one of the file provided in the `examples` folder, e.g.:

  ./parallel_hp_laplace examples/default.json

If no parameter file is provided, the program will automatically
generate a default parameter file in the folder where the executable is
located, and uses the default parameter set for the current run.


