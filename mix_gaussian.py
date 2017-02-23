import sys

from gaussian_perturber import GaussianOrbitalPerturber
from perturbation_utils import cmd_exists

args = sys.argv
if len(args) != 2:
    print("Usage: python mix_gaussian.py <checkpoint_file>")
    sys.exit()
checkpoint_file = args[1]

if not cmd_exists("formchk") or not cmd_exists("unfchk"):
    print("Gaussian commands formchk and unfchk are not present in the PATH variable")
    sys.exit()

gaussian_perturber = GaussianOrbitalPerturber(checkpoint_file)
gaussian_perturber.perturb_orbitals()

