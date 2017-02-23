import sys

from gaussian_perturber import GaussianOrbitalPerturber

args = sys.argv
if len(args) != 2:
    print("Usage: python mix_gaussian.py <checkpoint_file>")
    sys.exit()
checkpoint_file = args[1]

gaussian_perturber = GaussianOrbitalPerturber(checkpoint_file)
gaussian_perturber.perturb_orbitals()
