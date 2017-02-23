import os
import time

from mix_gaussian import checkpoint_file
from perturbation_utils import create_backup


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