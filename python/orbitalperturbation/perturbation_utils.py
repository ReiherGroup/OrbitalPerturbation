import subprocess
from shutil import copyfile


def create_backup(file):
    copyfile(file, file + '.bak')


def command_exists(command_string):
    return execute_command('type ' + command_string) == 0


def execute_command(command_string):
    """ Execute command in shell """
    with subprocess.Popen(command_string, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                          universal_newlines=True) as process:
        process.communicate()
        return process.returncode
