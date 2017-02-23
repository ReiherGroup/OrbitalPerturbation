import os
import re
import sys
from shutil import copyfile
from perturbation_utils import cmd_exists, create_backup

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

    def get_alpha_filename(self):
        return self.alpha_filename

    def get_beta_filename(self):
        return self.beta_filename

    def get_number_alpha_electrons(self):
        return self.number_alpha

    def get_number_beta_electrons(self):
        return self.number_beta

    def get_number_orbitals(self):
        return self.number_orbitals



args = sys.argv
if len(args) != 2:
    print("Usage: python mix_turbomole.py <calculation_directory>")
    sys.exit()

calculation_directory = args[1]
create_backup(calculation_directory + "/alpha")
create_backup(calculation_directory + "/beta")

parser = ControlFileParser(calculation_directory)
parser.parse()

alpha =  parser.get_alpha_filename()
beta = parser.get_beta_filename()
nAlpha = str(parser.get_number_alpha_electrons())
nBeta = str(parser.get_number_beta_electrons())
nOrbitals = str(parser.get_number_orbitals())


script_dir = os.path.dirname(__file__)
command_name = "./" + script_dir + "/turbomoleOrbitalMixer " + alpha + " " + beta + " " + nOrbitals + " " + nAlpha + " " + nBeta
print command_name
os.system(command_name)

print cmd_exists("dscf")
