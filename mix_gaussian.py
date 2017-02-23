import sys
import os
from perturbation_utils import cmd_exists, create_backup
from shutil import copyfile, move
import time

class GaussianOrbitalPerturber:
    def __init__(self, checkpoint_file):
        self.checkpoint_file = checkpoint_file

    def perturb_orbitals(self):
        create_backup(self.checkpoint_file)
        temporary_file_1 = "checkpoint_" + time.strftime("%Y%m%d%H%M%S") + "_1.FChk"
        temporary_file_2 = "checkpoint_" + time.strftime("%Y%m%d%H%M%S") + "_2.FChk"

        self.convert_to_formatted_checkpoint(checkpoint_file, temporary_file_1)

        script_dir = os.path.dirname(__file__)
        command_name = "./" + script_dir + "/gaussian_orbital_mixer " + temporary_file_1 + " " + temporary_file_2
        os.system(command_name)

        self.convert_to_unformatted_checkpoint(temporary_file_2, checkpoint_file)

    def convert_to_formatted_checkpoint(self, unformatted, formatted):
        os.system("formchk " + unformatted + " " + formatted)

    def convert_to_unformatted_checkpoint(self, formatted, unformatted):
        os.system("unfchk " + formatted + " " + unformatted)


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

