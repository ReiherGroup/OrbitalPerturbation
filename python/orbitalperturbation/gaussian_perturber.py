import sys
import time

from orbitalperturbation.perturbation_utils import create_backup, command_exists, execute_command


class GaussianOrbitalPerturber:
    executable_name = "gaussian_perturbation"
    formchk_command = "formchk"
    unfchk_command = "unfchk"

    def __init__(self, checkpoint_file):
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
        execute_command(command_name)

        self.convert_to_unformatted_checkpoint(temporary_file_2, self.checkpoint_file)

    def convert_to_formatted_checkpoint(self, unformatted, formatted):
        execute_command(self.formchk_command + " " + unformatted + " " + formatted)

    def convert_to_unformatted_checkpoint(self, formatted, unformatted):
        execute_command(self.unfchk_command + " " + formatted + " " + unformatted)
