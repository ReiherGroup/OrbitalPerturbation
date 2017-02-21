import re
import sys
from shutil import copyfile


class Control_File_Parser:
    def __init__(self, directory):
        self.control_file = directory + "/control"
        self.alpha_filename = ""
        self.beta_filename = ""

    def parse(self):
        textfile = open(self.control_file, 'r')
        filetext = textfile.read()
        textfile.close()
        matches = re.findall("uhfmo_alpha  *file=(.*)", filetext)
        self.alpha_filename = matches[0]

    def get_alpha_filename(self):
        return self.alpha_filename

    def get_beta_filename(self, structure_number):
        return self.beta_filename


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
print (parser.get_alpha_filename())
