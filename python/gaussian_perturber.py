import os
import sys
import time

from perturbation_utils import create_backup, command_exists


class GaussianOrbitalPerturber:
    def __init__(self, checkpoint_file):
        self.executable_name = "gaussian_perturbation"
        self.formchk_command = "formchk"
        self.unfchk_command = "unfchk"
        self.checkpoint_file = checkpoint_file
        self.check_preconditions()

    def check_preconditions(self):
        if not command_exists(self.formchk_command) or not command_exists(self.unfchk_command):
            print("Gaussian commands formchk and unfchk are not present in the PATH variable")
            sys.exit()

        if not command_exists(self.executable_name):
            print("The executable '" + self.executable_name + "' is not present in the PATH variable")
            sys.exit()

    def perturb_orbitals(self):
        create_backup(self.checkpoint_file)
        temporary_file_1 = time.strftime("%Y%m%d%H%M%S") + "_original_checkpoint_.FChk"
        temporary_file_2 = time.strftime("%Y%m%d%H%M%S") + "_perturbed_checkpoint_.FChk"

        self.convert_to_formatted_checkpoint(self.checkpoint_file, temporary_file_1)

        command_name = self.executable_name + " " + temporary_file_1 + " " + temporary_file_2
        os.system(command_name)

        self.convert_to_unformatted_checkpoint(temporary_file_2, self.checkpoint_file)

    def convert_to_formatted_checkpoint(self, unformatted, formatted):
        os.system(self.formchk_command + " " + unformatted + " " + formatted)

    def convert_to_unformatted_checkpoint(self, formatted, unformatted):
        os.system(self.unfchk_command + " " + formatted + " " + unformatted)
