import sys
from turbomole_perturber import TurbomoleOrbitalPerturber

args = sys.argv
if len(args) != 2:
    print("Usage: python mix_turbomole.py <calculation_directory>")
    sys.exit()

calculation_directory = args[1]
turbomole_perturber = TurbomoleOrbitalPerturber(calculation_directory)
turbomole_perturber.perturb_orbitals()
