import re
import os
import sys
from shutil import copyfile


class Control_File_Parser:
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


def create_orbital_backup(directory):
    """
    Creates .bak files for the orbital files 'alpha' and 'beta'
    :param directory: calculation directory
    """
    copyfile(directory + '/alpha', directory + '/alpha.bak')
    copyfile(directory + '/beta', directory + '/beta.bak')


args = sys.argv
if len(args) != 2:
    print("Usage: python mix_turbomole.py <calculation_directory>")
    sys.exit()

calculation_directory = args[1]
create_orbital_backup(calculation_directory)

parser = Control_File_Parser(calculation_directory)
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
