#ifndef ORBITALPERTURBATION_SPINADAPTEDMATRIX_H
#define ORBITALPERTURBATION_SPINADAPTEDMATRIX_H

#include <Eigen/Core>
#include <utility>

namespace OrbitalPerturbation {

/*!
 * Class defining a matrix and which can be used for both spin-restricted and spin-unrestricted formalisms in electronic structure calculation methods.
 * There is only slight overhead if only the restricted formulation is needed.
 */
class SpinAdaptedMatrix {
public:
  using Matrix = Eigen::MatrixXd;

  /*! Construct a SpinAdaptedMatrix with restricted part only from an Eigen::MatrixXd. */
  static SpinAdaptedMatrix createRestricted(Eigen::MatrixXd m);
  /*! Construct a SpinAdaptedMatrix with alpha and beta parts only from two Eigen::MatrixXd. */ 
  static SpinAdaptedMatrix createUnrestricted(Eigen::MatrixXd alpha, Eigen::MatrixXd beta);

  template<typename T> void setRestrictedMatrix(T&& restrictedMatrix);
  template<typename T> void setAlphaMatrix(T&& alphaMatrix);
  template<typename T> void setBetaMatrix(T&& betaMatrix);

  /*! \name Accessors to the underlying matrices by reference.  @{ */
  Matrix& restrictedMatrix();
  const Matrix& restrictedMatrix() const;
  Matrix& alphaMatrix();
  const Matrix& alphaMatrix() const;
  Matrix& betaMatrix();
  const Matrix& betaMatrix() const;
  /*! @} */

  /*! \name Accessors to the matrix elements.
      Using template functions to allow perfect forwarding to the Eigen functions.  @{ */
  template<typename Index> double restricted(Index i, Index j) const;
  template<typename Index> double alpha(Index i, Index j) const;
  template<typename Index> double beta(Index i, Index j) const;
  /*! @} */
  /*! \name Setters for the matrix elements.
      Using template functions to allow perfect forwarding to the Eigen functions.  @{ */
  template<typename Index> void setRestricted(Index i, Index j, double x);
  template<typename Index> void setAlpha(Index i, Index j, double x);
  template<typename Index> void setBeta(Index i, Index j, double x);
  /*! @} */

  /*! Set the size of the matrices (number of atomic orbitals) */
  void resize(unsigned nAOs);
protected:
  Matrix restrictedMatrix_;
  Matrix alphaMatrix_;
  Matrix betaMatrix_;
};

template <typename T>
void SpinAdaptedMatrix::setRestrictedMatrix(T&& restrictedMatrix) {
  restrictedMatrix_ = std::forward<T>(restrictedMatrix);
}

template <typename T>
void SpinAdaptedMatrix::setAlphaMatrix(T&& alphaMatrix) {
  alphaMatrix_ = std::forward<T>(alphaMatrix);
}

template <typename T>
void SpinAdaptedMatrix::setBetaMatrix(T&& betaMatrix) {
  betaMatrix_ = std::forward<T>(betaMatrix);
}

template <typename Index>
double SpinAdaptedMatrix::restricted(Index i, Index j) const {
  return restrictedMatrix_(i, j);
}

template <typename Index>
double SpinAdaptedMatrix::alpha(Index i, Index j) const {
  return alphaMatrix_(i, j);
}

template <typename Index>
double SpinAdaptedMatrix::beta(Index i, Index j) const {
  return betaMatrix_(i, j);
}

template <typename Index>
void SpinAdaptedMatrix::setRestricted(Index i, Index j, double x) {
  restrictedMatrix_(i, j) = x;
}

template <typename Index>
void SpinAdaptedMatrix::setAlpha(Index i, Index j, double x) {
  alphaMatrix_(i, j) = x;
}

template <typename Index>
void SpinAdaptedMatrix::setBeta(Index i, Index j, double x) {
  betaMatrix_(i, j) = x;
}

inline SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::restrictedMatrix() {
  return restrictedMatrix_;
}

inline const SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::restrictedMatrix() const {
  return restrictedMatrix_;
}

inline SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::alphaMatrix() {
  return alphaMatrix_;
}

inline const SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::alphaMatrix() const {
  return alphaMatrix_;
}

inline SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::betaMatrix() {
  return betaMatrix_;
}

inline const SpinAdaptedMatrix::Matrix& SpinAdaptedMatrix::betaMatrix() const {
  return betaMatrix_;
}

} // namespace OrbitalPerturbation

#endif // ORBITALPERTURBATION_SPINADAPTEDMATRIX_H