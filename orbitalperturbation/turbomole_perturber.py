import os
import re
import sys

from orbitalperturbation.perturbation_utils import create_backup, execute_command, command_exists


class ControlFileParser:
    def __init__(self, directory):
        self.control_file = os.path.join(directory, "control")
        self.alpha_filename = ""
        self.beta_filename = ""
        self.number_alpha = 0
        self.number_beta = 0
        self.number_orbitals = 0

    def parse(self):
        with open(self.control_file) as f:
            content = f.read()

        match = re.search("uhfmo_alpha\s+file=(.+)", content)
        self.alpha_filename = match.groups()[0]
        match = re.search("uhfmo_beta\s+file=(.+)", content)
        self.beta_filename = match.groups()[0]
        match = re.search("alpha shells\s+a\s+1-(\d+)", content, flags=re.MULTILINE)
        self.number_alpha = match.groups()[0]
        match = re.search("beta shells\s+a\s+1-(\d+)", content, flags=re.MULTILINE)
        self.number_beta = match.groups()[0]
        match = re.search("nbf\(AO\)=(\d+)", content)
        self.number_orbitals = match.groups()[0]


class TurbomoleOrbitalPerturber:
    executable_name = "turbomole_perturbation"

    def __init__(self, calculation_directory):
        self.calculation_directory = calculation_directory
        self.check_preconditions()

    def check_preconditions(self):
        if not command_exists(self.executable_name):
            print("The executable '" + self.executable_name + "' is not present in the PATH variable")
            sys.exit()

    def perturb_orbitals(self):
        parser = ControlFileParser(self.calculation_directory)
        parser.parse()

        create_backup(os.path.join(self.calculation_directory, parser.alpha_filename))
        create_backup(os.path.join(self.calculation_directory, parser.beta_filename))

        command_string = " ".join([self.executable_name, parser.alpha_filename, parser.beta_filename,
                                   parser.number_orbitals, parser.number_alpha, parser.number_beta])

        execute_command(command_string)


if __name__ == '__main__':
    f = ControlFileParser(os.getcwd())
    f.parse()
