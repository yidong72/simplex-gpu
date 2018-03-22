#ifndef IMLP__CPU_IMPL_H
#define IMLP__CPU_IMPL_H

#include <datastructures/problem.hpp>
#include <datastructures/tableau.hpp>
#include <impl/impl_common.hpp>

#include <vector>

#include <boost/optional.hpp>

namespace simplex {
namespace cpu {

#if __cplusplus >= 201103L
template<typename FloatType>
struct ThetaValuesAndEnteringColumn {
	std::vector<FloatType> theta_values;
	std::vector<FloatType> entering_column;

	ThetaValuesAndEnteringColumn(std::ptrdiff_t height)
		: theta_values((std::size_t)height)
		, entering_column((std::size_t)height)
	{ }

	ThetaValuesAndEnteringColumn(const ThetaValuesAndEnteringColumn&) = default;
	ThetaValuesAndEnteringColumn(ThetaValuesAndEnteringColumn&&) = default;
};
#endif

Tableau<double> create_tableau(const Problem& problem_stmt);

// find smallest also negative value in the first row
boost::optional<VariableID> find_entering_variable(const Tableau<double>& tab);

ThetaValuesAndEnteringColumn<double> get_theta_values_and_entering_column(const Tableau<double>& tab, VariableID entering);

VariableID find_leaving_variable(const ThetaValuesAndEnteringColumn<double>& tvals_and_centering);

#if __cplusplus >= 201103L
Tableau<double> update_leaving_row(Tableau<double>&& tab, const std::vector<double>& entering_column, VariablePair leaving_and_entering);

Tableau<double> update_rest_of_basis(Tableau<double>&& tab, const std::vector<double>& entering_column, VariableID leaving);

Tableau<double> update_entering_column(Tableau<double>&& tab, const std::vector<double>& entering_column, VariablePair leaving_and_entering);
#endif

} // end namespace simplex
} // end namespace cpu

#endif /* IMLP__CPU_IMPL_H */
