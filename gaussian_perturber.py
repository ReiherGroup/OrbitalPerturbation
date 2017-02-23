import os
import sys
import time

from perturbation_utils import create_backup, cmd_exists


class GaussianOrbitalPerturber:
    def __init__(self, checkpoint_file):
        self.executable_name = "gaussian_perturbation"
        self.checkpoint_file = checkpoint_file
        self.check_preconditions()

    def check_preconditions(self):
        if not cmd_exists("formchk") or not cmd_exists("unfchk"):
            print("Gaussian commands formchk and unfchk are not present in the PATH variable")
            sys.exit()

        if not cmd_exists(self.executable_name):
            print("The executable '" + self.executable_name + "' is not present in the PATH variable")
            sys.exit()

    def perturb_orbitals(self):
        create_backup(self.checkpoint_file)
        temporary_file_1 = "checkpoint_" + time.strftime("%Y%m%d%H%M%S") + "_1.FChk"
        temporary_file_2 = "checkpoint_" + time.strftime("%Y%m%d%H%M%S") + "_2.FChk"

        self.convert_to_formatted_checkpoint(self.checkpoint_file, temporary_file_1)

        command_name = self.executable_name + " " + temporary_file_1 + " " + temporary_file_2
        os.system(command_name)

        self.convert_to_unformatted_checkpoint(temporary_file_2, self.checkpoint_file)

    def convert_to_formatted_checkpoint(self, unformatted, formatted):
        os.system("formchk " + unformatted + " " + formatted)

    def convert_to_unformatted_checkpoint(self, formatted, unformatted):
        os.system("unfchk " + formatted + " " + unformatted)
