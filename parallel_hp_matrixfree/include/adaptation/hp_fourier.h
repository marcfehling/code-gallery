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

#ifndef adaptation_hp_fourier_h
#define adaptation_hp_fourier_h


#include <deal.II/distributed/tria.h>

#include <deal.II/dofs/dof_handler.h>

#include <deal.II/fe/fe_series.h>

#include <deal.II/hp/fe_collection.h>
#include <deal.II/hp/q_collection.h>

#include <deal.II/lac/vector.h>
#include <deal.II/lac/la_parallel_vector.h>

#include <adaptation/base.h>
#include <adaptation/parameter.h>


namespace Adaptation
{
  template <int dim, typename VectorType = dealii::LinearAlgebra::distributed::Vector<double>, int spacedim = dim>
  class hpFourier : public Base
  {
  public:
    hpFourier(const Parameters &               prm,
      VectorType & locally_relevant_solution,
      dealii::DoFHandler<dim, spacedim> &                          dof_handler,
      dealii::parallel::distributed::Triangulation<dim, spacedim> &triangulation,
      dealii::hp::FECollection<dim> &                    fe_collection);

    virtual void estimate_mark_refine() override;
    virtual const dealii::Vector<float>& get_error_estimates() const override;
    virtual const dealii::Vector<float>& get_hp_indicators() const override;

  protected:
    const Parameters &prm;

    VectorType & locally_relevant_solution;

    dealii::DoFHandler<dim, spacedim> &                          dof_handler;
    dealii::parallel::distributed::Triangulation<dim, spacedim> &triangulation;

    dealii::hp::QCollection<dim - 1> face_quadrature_collection;

    dealii::FESeries::Fourier<dim> fourier;

    dealii::Vector<float> error_estimates;
    dealii::Vector<float> hp_indicators;
  };
}


#endif
