import os
import re

from perturbation_utils import create_backup


class ControlFileParser:
    def __init__(self, directory):
        self.control_file = directory + "/control"
        self.alpha_filename = ""
        self.beta_filename = ""
        self.number_alpha = 0
        self.number_beta = 0
        self.number_orbitals = 0

    def parse(self):
        textfile = open(self.control_file, 'r')
        filetext = textfile.read()
        textfile.close()
        matches = re.findall("uhfmo_alpha  *file=(.*)", filetext)
        self.alpha_filename = matches[0]
        matches = re.findall("uhfmo_beta  *file=(.*)", filetext)
        self.beta_filename = matches[0]
        matches = re.findall("alpha shells *\n a  *1-(\d*)", filetext)
        self.number_alpha = int(matches[0])
        matches = re.findall("beta shells *\n a  *1-(\d*)", filetext)
        self.number_beta = int(matches[0])
        matches = re.findall("nbf\(AO\)=(\d*)", filetext)
        self.number_orbitals = int(matches[0])


class TurbomoleOrbitalPerturber:
    def __init__(self, calculation_directory):
        self.calculation_directory = calculation_directory

    def perturb_orbitals(self):
        parser = ControlFileParser(self.calculation_directory)
        parser.parse()

        alpha = parser.alpha_filename
        beta = parser.beta_filename
        create_backup(self.calculation_directory + "/" + alpha)
        create_backup(self.calculation_directory + "/" + beta)

        nAlpha = str(parser.number_alpha)
        nBeta = str(parser.number_beta)
        nOrbitals = str(parser.number_orbitals)

        script_dir = os.path.dirname(__file__)
        # command_name = "./" + script_dir + "/turbomoleOrbitalMixer " + alpha + " " + beta + " " + nOrbitals + " " + nAlpha + " " + nBeta
        command_name = script_dir + "/turbomoleOrbitalMixer " + alpha + " " + beta + " " + nOrbitals + " " + nAlpha + " " + nBeta
        os.system(command_name)
