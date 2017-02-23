#include "SpinAdaptedMatrix.h"

SpinAdaptedMatrix SpinAdaptedMatrix::createRestricted(Eigen::MatrixXd m) {
  SpinAdaptedMatrix matrix;
  matrix.resize(static_cast<unsigned>(m.rows()));
  matrix.setRestrictedMatrix(std::move(m));
  return matrix;
}

SpinAdaptedMatrix SpinAdaptedMatrix::createUnrestricted(Eigen::MatrixXd alpha, Eigen::MatrixXd beta) {
  assert(alpha.size() == beta.size() && "Alpha and beta matrix don't have the same size");
  SpinAdaptedMatrix matrix;
  matrix.resize(static_cast<unsigned>(alpha.rows()));
  matrix.setAlphaMatrix(std::move(alpha));
  matrix.setBetaMatrix(std::move(beta));
  return matrix;
}

void SpinAdaptedMatrix::resize(unsigned nAOs) {
  restrictedMatrix_.resize(nAOs,nAOs);
  alphaMatrix_.resize(nAOs, nAOs);
  betaMatrix_.resize(nAOs, nAOs);
}