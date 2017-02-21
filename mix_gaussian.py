import sys
import os
from cmd_exists import cmd_exists
from shutil import copyfile, move


def create_checkpoint_backup(checkpoint_file):
    """
    Creates .bak files for the orbital files 'alpha' and 'beta'
    :param directory: calculation directory
    """
    copyfile(checkpoint_file, checkpoint_file + '.bak')

def convert_to_formatted_checkpoint(unformatted, formatted):
    os.system("formchk " + unformatted + " " + formatted)

def convert_to_unformatted_checkpoint(formatted, unformatted):
    os.system("unfchk " + formatted + " " + unformatted)

args = sys.argv
if len(args) != 2:
    print("Usage: python mix_gaussian.py <checkpoint_file>")
    sys.exit()
checkpoint_file = args[1]

if not cmd_exists("formchk") or not cmd_exists("unfchk"):
    print("Gaussian commands formchk and unfchk are not present in the PATH variable")
    sys.exit()


create_checkpoint_backup(checkpoint_file)
formatted_checkpoint_file = "checkpoint.FChk"

convert_to_formatted_checkpoint(checkpoint_file, formatted_checkpoint_file)


script_dir = os.path.dirname(__file__)
command_name = "./" + script_dir + "/gaussian_orbital_mixer " + formatted_checkpoint_file + " temp"
print command_name
os.system(command_name)
move("temp", formatted_checkpoint_file)

convert_to_unformatted_checkpoint(formatted_checkpoint_file, checkpoint_file)
