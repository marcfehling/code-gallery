/* -----------------------------------------------------------------------------
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 * Copyright (C) 2020 by David Schneider
 * Copyright (C) 2020 by Benjamin Uekermann
 *
 * This file is part of the deal.II code gallery.
 *
 * -----------------------------------------------------------------------------
 */

// This program does not use any deal.II functionality and depends only on
// preCICE and the standard libraries.
#include <precice/precice.hpp>

#include <iostream>
#include <sstream>
#include <vector>

// The program computes a time-varying parabolic boundary condition, which is
// passed to preCICE and serves as Dirichlet boundary condition for the other
// coupling participant.

// Function to generate boundary values in each time step
void
define_boundary_values(std::vector<double> &boundary_data,
                       const double         time,
                       const double         end_time)
{
  // Scale the current time value
  const double relative_time = time / end_time;
  // Define the amplitude. Values run from -0.5 to 0.5
  const double amplitude = (relative_time - 0.5);
  // Specify the actual data we want to pass to the other participant. Here, we
  // choose a parabola with boundary values 2 in order to enforce continuity
  // to adjacent boundaries.
  const double n_elements = boundary_data.size();
  const double right_zero = boundary_data.size() - 1;
  const double left_zero  = 0;
  const double offset     = 2;
  for (uint i = 0; i < n_elements; ++i)
    boundary_data[i] =
      -amplitude * ((i - left_zero) * (i - right_zero)) + offset;
}


int
main()
{
  std::cout << "Boundary participant: starting... \n";

  // Configuration
  const std::string configFileName("precice-config.xml");
  const std::string solverName("boundary-participant");
  const std::string meshName("boundary-mesh");
  const std::string dataWriteName("boundary-data");

  // Adjust to MPI rank and size for parallel computation
  const int commRank = 0;
  const int commSize = 1;

  precice::Participant precice(solverName, configFileName, commRank, commSize);

  const int dimensions       = precice.getMeshDimensions(meshName);
  const int numberOfVertices = 6;

  // Set up data structures
  std::vector<double> writeData(numberOfVertices);
  std::vector<int>    vertexIDs(numberOfVertices);
  std::vector<double> vertices(numberOfVertices * dimensions);

  // Define a boundary mesh
  std::cout << "Boundary participant: defining boundary mesh \n";
  const double length = 2;
  const double xCoord = 1;
  const double deltaY = length / (numberOfVertices - 1);
  for (int i = 0; i < numberOfVertices; ++i)
    for (int j = 0; j < dimensions; ++j)
      {
        const unsigned int index = dimensions * i + j;
        // The x-coordinate is always 1, i.e., the boundary is parallel to the
        // y-axis. The y-coordinate is descending from 1 to -1.
        if (j == 0)
          vertices[index] = xCoord;
        else
          vertices[index] = 1 - deltaY * i;
      }

  // Pass the vertices to preCICE
  precice.setMeshVertices(meshName, vertices, vertexIDs);

  // Variables for the time
  const double end_time = 1;
  double       time     = 0;

  // Not used in the configuration by default
  if (precice.requiresInitialData())
    {
      std::cout << "Boundary participant: writing initial data \n";
      define_boundary_values(writeData, time, end_time);
      precice.writeData(meshName, dataWriteName, vertexIDs, writeData);
    }

  // initialize the Participant
  precice.initialize();

  // Start time loop
  while (precice.isCouplingOngoing())
    {
      double dt = precice.getMaxTimeStepSize();
      time += dt;

      // Generate new boundary data
      define_boundary_values(writeData, time, end_time);

      std::cout << "Boundary participant: writing coupling data \n";
      precice.writeData(meshName, dataWriteName, vertexIDs, writeData);

      std::cout << "Boundary participant: advancing in time\n";
      precice.advance(dt);
    }

  std::cout << "Boundary participant: closing...\n";

  return 0;
}
