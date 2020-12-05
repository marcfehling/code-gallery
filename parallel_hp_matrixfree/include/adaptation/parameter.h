// ---------------------------------------------------------------------
//
// Copyright (C) 2020 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------

#ifndef adaptation_parameters_h
#define adaptation_parameters_h


#include <deal.II/base/parameter_acceptor.h>


namespace Adaptation
{
  class Parameters : public dealii::ParameterAcceptor
  {
  public:
    Parameters()
      : dealii::ParameterAcceptor("adaptation")
    {
      min_level = 5;
      add_parameter("minlevel", min_level);

      max_level = 10;
      add_parameter("maxlevel", max_level);

      min_degree = 2;
      add_parameter("mindegree", min_degree);

      max_degree = 7;
      add_parameter("maxdegree", max_degree);

      total_refine_fraction = 0.3;
      add_parameter("totalrefinefraction", total_refine_fraction);

      total_coarsen_fraction = 0.03;
      add_parameter("totalcoarsenfraction", total_refine_fraction);

      p_refine_fraction = 0.9;
      add_parameter("prefinefraction", p_refine_fraction);

      p_coarsen_fraction = 0.9;
      add_parameter("pcoarsenfraction", p_coarsen_fraction);
    }

  private:
    unsigned int min_level, max_level;
    unsigned int min_degree, max_degree;

    double total_refine_fraction, total_coarsen_fraction;
    double p_refine_fraction, p_coarsen_fraction;

    template <int dim, typename VectorType, int spacedim>
    friend class h;
    template <int dim, typename VectorType, int spacedim>
    friend class hpFourier;
    template <int dim, typename VectorType, int spacedim>
    friend class hpHistory;
    template <int dim, typename VectorType, int spacedim>
    friend class hpLegendre;
  };
} // namespace Adaptation


#endif
